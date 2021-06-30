//
// Created by focus on 23.06.2021.
//

#ifndef GOODOK_SERVERS_CONSOLEPARAMS_H
#define GOODOK_SERVERS_CONSOLEPARAMS_H

#include "sdk/common/log/Logger.h"
#include "sdk/database/Settings.h"

#include <boost/program_options.hpp>

#include "version.h"

namespace goodok::params {

    constexpr const char* dbUserOpt = "user";
    constexpr const char* dbPassOpt = "pass";
    constexpr const char* dbHostOpt = "host";
    constexpr const char* dbNameOpt = "name";
    constexpr const char* versionOpt = "version";

    struct Params
    {
        db::ParamsDb db;
        bool onlyOutputVersion = false;
        // log level
    };

    std::string getVersion()
    {
        return std::to_string(PROJECT_VERSION_MAJOR) + '.' + std::to_string(PROJECT_VERSION_MINOR) + '.' + std::to_string(PROJECT_VERSION_PATCH);
    }

    bool checkParams(Params const& params)
    {
        bool result = true;
        if (params.db.username.empty())
        {
            log::write(log::Level::error, "checkParams", boost::format("need set username in db, use --%1%") % dbUserOpt);
            result = false;
        }
        if (params.db.password.empty())
        {
            log::write(log::Level::error, "checkParams", boost::format("need set password in db, use --%1%") % dbPassOpt);
            result = false;
        }
        if (params.db.name.empty())
        {
            log::write(log::Level::error, "checkParams", boost::format("need set db name, use --%1%") % dbNameOpt);
            result = false;
        }
        return result;
    }

    Params setParameters(int argc, char** argv) {
        namespace po = boost::program_options;

        Params params;
        try {
            po::options_description desc("Allowed options");

            desc.add_options()
                    ("help, h", "produce help message")
                    ("version, v", "get server version")
                    (dbUserOpt, po::value<std::string>(), "username")
                    (dbPassOpt, po::value<std::string>(), "password")
                    (dbHostOpt, po::value<std::string>()->default_value("127.0.0.1"), "host basic database")
                    (dbNameOpt, po::value<std::string>(), "database name")
                    ;

            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            if (vm.count(versionOpt) != 0U) {
                params.onlyOutputVersion = true;
            }
            if (vm.count(dbUserOpt) != 0U) {
                params.db.username = vm[dbUserOpt].as<std::string>();
            }
            if (vm.count(dbPassOpt) != 0U) {
                params.db.password = vm[dbPassOpt].as<std::string>();
            }
            if (vm.count(dbHostOpt) != 0U) {
                params.db.host = vm[dbHostOpt].as<std::string>();
            }
            if (vm.count(dbNameOpt) != 0U) {
                params.db.name = vm[dbNameOpt].as<std::string>();
            }
        }
        catch(...)
        {
            std::cerr << "Failed parse params" << std::endl;
            log::write(log::Level::error, "setParameters", "failed parse params");
        }

        return params;
    }


}

#endif //GOODOK_SERVERS_CONSOLEPARAMS_H
