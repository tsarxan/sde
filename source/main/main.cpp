#include "main.hpp" 

auto main( ) -> int {
    ui_t ui( [ & ] -> bool {
        if ( ImGui::Begin( "SDE" ) ) {
            // ...
        }

        ImGui::End( );

        return true;
        } );
    
    // gotta stop this while true loop after an event
    while ( true )
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    return 0;
}