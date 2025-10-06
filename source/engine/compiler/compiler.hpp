#pragma once

namespace sde {
    enum class compilers_t: int {
        automatic = 0,
        gcc = 1, // GNU Compiler
        clang = 2, // LLVM/Clang
        msvc = 3 // WILL ADD LATER
    };

    enum class arch_t: int {
        automatic = 0,
        x32 = 1,
        x64 = 2,
        // will figure out others later
    };

    struct compiler_t {
    private:
        compilers_t compiler = compilers_t::automatic;
        arch_t arch = arch_t::automatic;

    public:
        auto build( const bool debug, const bool run ) -> bool {
            // todo: write compiler for each option

            switch ( compiler ) { 
            case compilers_t::gcc:
                break;

            case compilers_t::clang:
                break;

            case compilers_t::msvc:
                break;
            default:
                break;
            }

            return true;
        };

        compiler_t( compilers_t compiler, arch_t arch ) {
            if ( arch == arch_t::automatic )
                arch = ( [ & ] -> arch_t {
                    // todo: get arch based on host os's arch
                    return arch_t::x64;
                    }( ) );

            if ( compiler == compilers_t::automatic )
                compiler = ( [ & ] -> compilers_t {
                    // todo: scan for all compilers on system and pick one
                    return compilers_t::gcc;
                    }( ) );

            // will look for other things to initialize too
        }
    };
}