#pragma once
#define OPENGL true

#include <thread>
#include <string>
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

using render_t = std::function< bool( ) >;

struct ui_t {
private:
    // ...

public:
    // ...

    ui_t( render_t render ) {
        auto ui_thread = std::thread( [ & ] {
            // todo: create ui (cross-platform) & init imgui stuff
            
            while ( true ) {
                // todo: render loop start

                if ( !render( ) )
                    break;

                // todo: render loop end
            }
            } );

        ui_thread.detach( );
    }
};
