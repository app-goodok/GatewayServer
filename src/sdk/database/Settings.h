//
// Created by focus on 12.06.2021.
//

#ifndef GOODOK_SERVERS_SETTINGS_H
#define GOODOK_SERVERS_SETTINGS_H

#include <string>

namespace goodok::db {
    struct ParamsDb {
        std::string username;
        std::string password;
        std::string host; // @TODO to uint32_t
        std::string name;   // db name
    };

    struct InputSettings {
        std::string clientName;
        std::string clientPassword;
    };
}
#endif //GOODOK_SERVERS_SETTINGS_H
