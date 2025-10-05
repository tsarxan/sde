#include "main.hpp" 

auto main( ) -> int {
    ui_t ui( [ & ] -> bool {
        // todo: create a ui w/ imgui

        return true;
        } );

    while ( true )
        std::this_thread::sleep_for( std::chrono::seconds( 69 ) );

    return 0;
}