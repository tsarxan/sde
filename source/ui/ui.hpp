#pragma once

#include <thread>
#include <string>
#include <functional>

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
