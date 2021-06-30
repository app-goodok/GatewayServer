//
// Created by focus on 02.05.2021.
//


#include <protocol/protocol.h>

#include "sdk/common/MakeSharedHelper.h"
#include "sdk/context/AsyncContext.h"
#include "sdk/network/AcceptProcess.h"
#include "sdk/network/session/ClientSession.h"
#include "sdk/database/WrapperPg.h"

#include "ConsoleParams.h"



int main(int argc, char *argv[])
{
    using namespace goodok;

    try {
        log::configure(goodok::log::Level::debug);

        auto params = params::setParameters(argc, argv);
        if (params.onlyOutputVersion) {
            log::write(log::Level::info, "main", boost::format("gateway-server version: %1%") % params::getVersion());
            return 0;
        }
        if (!params::checkParams(params))
        {
            log::write(log::Level::error, "main","need set all params");
            return 1;
        }

        std::shared_ptr<db::IDatabase> db = std::make_shared<db::WrapperPg>();
        if (db->connect(params.db)) {
            log::write(log::Level::info, "main",boost::format("connect to pgsql successfully: host=%1%, name db=%2%")
                % params.db.host % params.db.name);
        } else {
            log::write(log::Level::error, "main",boost::format("failed to connect db. close server: host=%1%, name db=%2%")
                                                % params.db.host % params.db.name);
            return 1;
        }

        auto managerUsers = std::make_shared<UserManager>(db);
        auto managerChannels = std::make_shared<ChannelsManager>(managerUsers, db);
        enginePtr engine = std::make_shared<QueryEngine>(managerUsers, managerChannels);

        auto ctx = std::make_shared<AsyncContext>();
        auto queue = std::make_shared<ThreadSafeQueue>();

        using AcceptType = AcceptProcess<goodok::ClientSession>;
        auto nwk = std::make_shared<MakeSharedHelper<AcceptType>>(ctx, engine, 7777, queue);

        log::write(log::Level::info, "main","server ready to work.");
        queue->start(4);
        nwk->run();
    } catch (std::exception & ex) {
        log::write(log::Level::fatal, "main", ex.what());
    }

}