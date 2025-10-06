#include "main.hpp" 

auto main( ) -> int {
    sde::ui_t ui( [ & ] -> bool {
        if ( ImGui::Begin( "SDE", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse ) ) {
            ImGui::Button( "Sex Button" );
        }
        
        ImGui::End();
        return true;
        } );
    
    // gotta stop this while true loop after an event
    while ( ui.is_rendering( ) )
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

    return 0;
}