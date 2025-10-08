#include "main.hpp" 

auto main( ) -> int {
    /*
    Json::Value config;
    config["compiler"] = "gcc";
    config["standard"] = "c++23";
    config["sources"] = Json::arrayValue;
    config["sources"].append("main.cpp");
    config["output"] = "bin/app";
    config["args"] = Json::arrayValue;
    config["args"].append("-O2");
    config["args"].append("-Wall");

    sde::compilers::gcc_t gcc;
    auto result = gcc.compile( config );
    if ( !result.exit_code )
        std::printf( "build success\n" );
    else
        std::printf( "build failure\n" );
    */

    sde::ui_t ui( "Shit Development Environment" );
    ui.add_interface( [ & ] -> bool {
        if ( ImGui::Begin( "sde", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar ) ) {
            if ( ImGui::BeginMenuBar( ) ) {
                if ( ImGui::BeginMenu( "File" ) ) {
                    ImGui::MenuItem("New File", "Ctrl+N", false);
                    ImGui::MenuItem("New Window", "Ctrl+Shift+N", false);
                    ImGui::Separator();
                    
                    ImGui::MenuItem("Open File", "Ctrl+O", false);
                    ImGui::MenuItem("Open Project", "Ctrl+Shift+O", false);
                    if (ImGui::BeginMenu("Open Recent")) {
                        ImGui::MenuItem("None", "", false);
                        
                        ImGui::EndMenu();
                    }
                    ImGui::Separator();

                    ImGui::MenuItem("Save", "Ctrl+S", false);
                    ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false);
                    ImGui::MenuItem("Save All", "", false);
                    ImGui::Separator();

                    ImGui::MenuItem("Close File", "Ctrl+W", false);
                    ImGui::MenuItem("Close Project", "", false);
                    ImGui::Separator();

                    ImGui::MenuItem("Close SDE", "Alt+F4", false);

                    ImGui::EndMenu();
                }
                
                if ( ImGui::BeginMenu( "Edit" ) ) {
                    ImGui::MenuItem("Undo", "Ctrl+Z", false);
                    ImGui::MenuItem("Redo", "Ctrl+Y", false);
                    ImGui::Separator();

                    ImGui::MenuItem("Cut", "Ctrl+X", false);
                    ImGui::MenuItem("Copy", "Ctrl+C", false);
                    ImGui::MenuItem("Paste", "Ctrl+V", false);
                    ImGui::Separator();

                    ImGui::MenuItem("Find", "Ctrl+F", false);
                    ImGui::MenuItem("Replace", "Ctrl+H", false);
                    ImGui::Separator();

                    ImGui::MenuItem("Find in Files", "Ctrl+Shift+F", false);
                    ImGui::MenuItem("Replace in Files", "Ctrl+Shift+H", false);
                    
                    ImGui::EndMenu();
                }
                
                if ( ImGui::BeginMenu( "View" ) ) {
                    ImGui::MenuItem("Explorer", "", false);
                    ImGui::MenuItem("Search", "", false);
                    ImGui::MenuItem("Symbols", "", false);
                    ImGui::Separator();
                    
                    ImGui::MenuItem("Output", "", false);
                    ImGui::MenuItem("Terminal", "", false);
                    ImGui::MenuItem("Problems", "", false);
                    ImGui::Separator();

                    if (ImGui::BeginMenu("Layout")) {
                        ImGui::MenuItem("Save", "", false);
                        ImGui::MenuItem("Load", "", false);
                        ImGui::MenuItem("Reset", "", false);
                        
                        ImGui::EndMenu();
                    }
                    
                    if ( ImGui::BeginMenu("Themes" ) ) {
                        ImGui::MenuItem("Light (Default)", "", false);
                        ImGui::MenuItem("Dark (Default)", "", false);
                        ImGui::MenuItem("Dracula (Default)", "", false);
                        
                        ImGui::EndMenu();
                    }
                    
                    ImGui::EndMenu();
                }
                
                if ( ImGui::BeginMenu("Project" ) ) {
                    ImGui::MenuItem( "New Project", "", false );
                    ImGui::MenuItem( "Open Project", "", false );
                    ImGui::MenuItem( "Close Project", "", false );
                    ImGui::Separator( );

                    ImGui::MenuItem( "Build", "", false );
                    ImGui::MenuItem( "Rebuild", "", false );
                    ImGui::MenuItem( "Clean", "", false );
                    ImGui::Separator( );

                    ImGui::MenuItem("Run", "", false);
                    
                    if ( ImGui::BeginMenu( "Debugger" ) ) {
                        ImGui::MenuItem("Start", "F5", false);
                        ImGui::MenuItem("Stop", "Ctrl+F5", false);
                        ImGui::Separator( );

                        ImGui::MenuItem("Continue", "", false);
                        ImGui::MenuItem("Step Into", "", false);
                        ImGui::MenuItem("Step Over", "", false);
                        ImGui::MenuItem("Step Out", "", false);
                        ImGui::Separator( );

                        ImGui::MenuItem("Toggle Breakpoint", "", false);

                        if ( ImGui::BeginMenu( "New Breakpoint" ) ) {
                            ImGui::MenuItem("Conditional", "", false);
                            ImGui::MenuItem("Log", "", false);
                            ImGui::MenuItem("Inline", "", false);
                            ImGui::MenuItem("Triggered", "", false);
                            
                            ImGui::EndMenu();
                        }

                        ImGui::Separator( );

                        ImGui::MenuItem("Enable All Breakpoints", "", false);
                        ImGui::MenuItem("Disable All Breakpoints", "", false);
                        ImGui::MenuItem("Remove All Breakpoints", "", false);

                        ImGui::EndMenu();
                    }
                    ImGui::Separator( );

                    ImGui::MenuItem("Project Config", "", false);

                    ImGui::EndMenu( );
                }

                if ( ImGui::BeginMenu( "Settings" ) ) {
                    ImGui::MenuItem("???", "", false);

                    ImGui::EndMenu();
                }
                
                if ( ImGui::BeginMenu( "Help" ) ) {
                    ImGui::MenuItem("Website", "", false);
                    ImGui::MenuItem("Documentation", "", false);
                    ImGui::Separator( );

                    ImGui::MenuItem("Check for Updates", "", false);

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar( );
            }

            // ...
        }

        ImGui::End();
        return true;
        } );

    // gotta stop this while true loop after an event
    while ( ui.is_rendering( ) )
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
 
    return 0;
}