#pragma once

#define OPENGL
#define LENIENT_ERRORS

#include <mutex>
#include <thread>
#include <string>
#include <format>
#include <stdexcept>
#include <functional>

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

using interface_t = std::function< bool( ) >;

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

    template< typename type_t >
    class table_t {
    private:
        std::vector< type_t > local_vector = { };    
        mutable std::mutex local_mutex;

    public:
        auto get_raw_vector( ) const -> std::vector< type_t > {
            return local_vector;
        }

        auto get_raw_mutex( ) const -> std::mutex {
            return local_mutex;
        }

        auto add_element( const type_t& element ) -> void {
            std::scoped_lock lock( local_mutex );
            local_vector.push_back( element );
        }

        auto add_element( type_t&& element ) -> void {
            std::scoped_lock lock( local_mutex );
            local_vector.push_back( std::move( element ) );
        }

        [[ nodiscard ]] auto get_element( const size_t position ) const -> std::optional< type_t > {
            std::scoped_lock lock( local_mutex );

            if ( position >= local_vector.size( ) )
                return std::nullopt;

            return local_vector[ position ];
        }

        [[ nodiscard ]] auto size( ) const noexcept -> size_t {
            std::scoped_lock lock( local_mutex );
            return local_vector.size( );
        }

        [[nodiscard]] auto snapshot() const -> std::vector< type_t > {
            std::scoped_lock lock( local_mutex );
            return local_vector;
        }

        auto clear( ) -> void {
            std::scoped_lock lock( local_mutex );
            local_vector.clear( );
        }

        table_t( ) = default;
        table_t( const table_t& ) = delete;
        table_t& operator=( const table_t& ) = delete;
    };

    struct ui_t {
    private:
        const std::string window_name;
        table_t< interface_t > interfaces{ };
        std::atomic< bool > rendering = true; // set this to true because we dont know when it starts lowk

    public:
        auto is_rendering( ) const -> bool {
            return rendering;
        }

        auto add_interface( interface_t interface ) -> bool {
            interfaces.add_element( interface );
            return true;
        }

        ui_t( std::string_view window_name ) : window_name( window_name ) {
            // ...

            auto ui_thread = std::thread( [ this ] {
                glfwSetErrorCallback( error_callback ); // error setup

                // glfw init
                if ( !glfwInit( ) )
                    throw std::runtime_error( "couldn't initialize GLFW for ui." );

                // gl version
                glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 ); // misc
                glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 ); // misc
            
                // glfw window
                auto main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor( glfwGetPrimaryMonitor( ) );
                auto* window = glfwCreateWindow( 640, 480, "default_title", NULL, NULL );
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
                io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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

                    for ( auto interface : this->interfaces.snapshot( ) ) {
                        ImGui::SetNextWindowPos( viewport->Pos );
                        ImGui::SetNextWindowSize( viewport->Size );

                        if ( !interface( ) )
                            throw std::runtime_error( "imgui window had a failure or sum" );
                    }

                    ImGui::Render( );
                    
                    int display_w, display_h;
                    glfwGetFramebufferSize( window, &display_w, &display_h );
                    glViewport( 0, 0, display_w, display_h );
                    glClearColor( clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w );
                    glClear( GL_COLOR_BUFFER_BIT );

                    ImGui_ImplOpenGL2_RenderDrawData( ImGui::GetDrawData( ) );

                    glfwMakeContextCurrent( window );
                    glfwSwapBuffers( window );

                    const auto title = std::format( "{} - FPS: {:.2f}", this->window_name, get_fps_from_glfw( oldest_time ) );
                    glfwSetWindowTitle( window, title.c_str( ) );
                }

                // destroy imgui
                ImGui_ImplOpenGL2_Shutdown( );
                ImGui_ImplGlfw_Shutdown( );
                ImGui::DestroyContext( );

                // destroy glfw
                glfwDestroyWindow( window );
                glfwTerminate( );
                
                // set rendering boolean
                this->rendering = false;
                } );

            ui_thread.detach( ); // im gonna fuck myself if this crashes
        }
    };

}