#include "main.hpp" 

auto main( ) -> int {
    auto test = std::thread( [ & ]( ) {
        std::println( "Hello, from sde!" );
        } );

    test.detach( );

    while ( true )
        std::this_thread::sleep_for( std::chrono::seconds( 69 ) );

    return 0;
}