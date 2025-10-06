#pragma once

#define OPENGL
#define LENIENT_ERRORS

#include <thread>
#include <string>
#include <format>
#include <functional>
#include <stdexcept>

#include <imgui.h>
#include <imgui_internal.h>

#if defined(VULKAN)
    // todo: add vulkan support

    #include <imgui_impl_vulkan.h>
#elif defined(OPENGL)
    #include <GL/gl.h>
    #include <GLFW/glfw3.h>
    #include <GLFW/glfw3native.h>

    #include <imgui_impl_glfw.h>
    #include <imgui_impl_opengl2.h>
#else
    #error no renderer specified for build
#endif

using render_t = std::function< bool( ) >;

auto error_callback( int error, const char* message ) -> void {
    #ifdef LENIENT_ERRORS
        std::printf( "opengl error: %s\n", message );
    #else
        throw std::runtime_error( std::string( "opengl error: %s\n", message ) ); // gotta fix later
    #endif
}

auto get_fps_from_glfw( double& oldest_time ) -> float {
    auto delta = ( glfwGetTime( ) - oldest_time );
    return ( delta <= 0.0 ) ? 0.f : ( oldest_time = oldest_time + delta, ( 1.f / static_cast< float >( delta ) ) );
}

namespace sde {
    struct ui_t {
    private:
        bool rendering = true; // set this to true because we dont know when it starts lowk

    public:
        auto is_rendering( ) const -> bool {
            return rendering;
        }

        ui_t( render_t render ) {
            // ...

            auto ui_thread = std::thread( [ & ] {
                glfwSetErrorCallback( error_callback ); // error setup

                // glfw init
                if ( !glfwInit( ) )
                    throw std::runtime_error( "couldn't initialize GLFW for ui." );

                // gl version
                glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 ); // misc
                glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 ); // misc
            
                // glfw window
                auto main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor( glfwGetPrimaryMonitor( ) );
                auto* window = glfwCreateWindow( 640, 480, "SDE", NULL, NULL );
                if ( !window )
                    throw std::runtime_error( "couldn't create GLFW window for ui." );

                auto oldest_time = glfwGetTime( );
                glfwMakeContextCurrent( window );
                glfwSwapInterval( 0 ); // vsync

                // imgui context & io
                IMGUI_CHECKVERSION( );
                ImGui::CreateContext( );

                auto& io = ImGui::GetIO( ); ( void )( io );
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

                ImGui::StyleColorsDark( );

                auto clear_color = ImVec4(0.f, 0.f, 0.f, 1.f);

                auto& style = ImGui::GetStyle( );
                style.ScaleAllSizes( main_scale );
                style.FontScaleDpi = main_scale;

                // imgui init
                ImGui_ImplGlfw_InitForOpenGL( window, true );
                ImGui_ImplOpenGL2_Init( );

                // render loop
                while ( !glfwWindowShouldClose( window ) ) {
                    glfwPollEvents( );
                    if ( glfwGetWindowAttrib( window, GLFW_ICONIFIED ) != 0 ) {
                        ImGui_ImplGlfw_Sleep( 10 );
                        continue;
                    }

                    ImGui_ImplOpenGL2_NewFrame();
                    ImGui_ImplGlfw_NewFrame();
                    ImGui::NewFrame();

                    auto* viewport = ImGui::GetMainViewport( );
                    ImGui::SetNextWindowPos( viewport->Pos );
                    ImGui::SetNextWindowSize( viewport->Size );

                    if ( !render( ) )
                        break;

                    ImGui::Render( );
                    
                    int display_w, display_h;
                    glfwGetFramebufferSize( window, &display_w, &display_h );
                    glViewport( 0, 0, display_w, display_h );
                    glClearColor( clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w );
                    glClear( GL_COLOR_BUFFER_BIT );

                    ImGui_ImplOpenGL2_RenderDrawData( ImGui::GetDrawData( ) );

                    glfwMakeContextCurrent( window );
                    glfwSwapBuffers( window );

                    auto fps = get_fps_from_glfw( oldest_time );
                    glfwSetWindowTitle(
                        window,
                        std::string(
                            std::vformat(
                                "SDE - FPS: {:.2f}", 
                                std::make_format_args( 
                                    fps
                                ) 
                            ) 
                        ).c_str( ) 
                    );
                }

                // destroy imgui
                ImGui_ImplOpenGL2_Shutdown( );
                ImGui_ImplGlfw_Shutdown( );
                ImGui::DestroyContext( );

                // destroy glfw
                glfwDestroyWindow( window );
                glfwTerminate( );
                
                // set rendering boolean
                rendering = false;
                } );

            ui_thread.detach( ); // im gonna fuck my self if this crashes
        }
    };
}