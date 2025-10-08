#pragma once

#include <string>
#include <thread>
#include <vector>

#include <json/json.h>

namespace sde {
    
    struct compiler_result_t {
        int exit_code = 0;

        std::string output;
        std::string errors;
    };

    struct compiler_template_t {
    private:
        // ...

    public:
        virtual auto name( ) const -> std::string = 0;
        virtual auto version( ) const -> std::string = 0;

        virtual auto compile( const Json::Value& config ) -> compiler_result_t = 0;

        virtual auto is_available( ) const -> bool = 0;

        virtual ~compiler_template_t( ) = default;
    };

    namespace compilers {

        struct gcc_t: public compiler_template_t {
        public:
            auto compile( const Json::Value& config ) -> compiler_result_t override {
                std::ostringstream cmd;
                cmd << "g++";

                if (config.isMember("standard"))
                    cmd << " -std=" << config["standard"].asString();

                if (config.isMember("defines"))
                    for (const auto& def : config["defines"])
                        cmd << " -D" << def.asString();

                if (config.isMember("include_dirs"))
                    for (const auto& dir : config["include_dirs"])
                        cmd << " -I" << dir.asString();

                if (config.isMember("args"))
                    for (const auto& arg : config["args"])
                        cmd << " " << arg.asString();

                if (config.isMember("sources"))
                    for (const auto& src : config["sources"])
                        cmd << " " << src.asString();

                if (config.isMember("output"))
                    cmd << " -o " << config["output"].asString();

                auto command_str = cmd.str();

                int exit_code = std::system(command_str.c_str());

                compiler_result_t result;
                result.exit_code = exit_code;
                result.output = "compilation completed";
                result.errors = (exit_code != 0) ? "compilation failed" : "";

                return result;
            }

            gcc_t( ) {
                // todo: setup toolkit
            }
        };

        struct clang_t: public compiler_template_t {
        public:
            auto compile( const Json::Value& config ) -> compiler_result_t override {
                // ...

                std::system( "" ); // ...
            }

            clang_t( ) {
                // todo: setup toolkit
            }
        };

    }

}