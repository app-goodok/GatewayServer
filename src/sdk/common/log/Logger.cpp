//
// Created by focus on 03.05.2021.
//

#include "Logger.h"
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/utility/setup/file.hpp>

namespace goodok::log {

    namespace logging = boost::log;
    namespace sinks = boost::log::sinks;
    namespace src = boost::log::sources;
    namespace expr = boost::log::expressions;
    namespace attrs = boost::log::attributes;
    namespace keywords = boost::log::keywords;

    void configure(boost::log::trivial::severity_level lvl)
    {
        logging::add_file_log
        (
                keywords::file_name = "log_%3N.txt",
                keywords::open_mode = std::ios_base::app,
                keywords::rotation_size = 10 * 1024 * 1024,
                keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
                keywords::format = "%LineID%: [%TimeStamp%]<%Severity%>: %Message%",
                keywords::auto_flush = true
        );
        logging::add_console_log(std::cout, boost::log::keywords::format =
                "%LineID%: [%TimeStamp%]<%Severity%>: %Message%"
                );
        boost::log::core::get()->set_filter(boost::log::trivial::severity >= lvl);
        logging::add_common_attributes();
    }

    void write(boost::log::trivial::severity_level lvl, std::string const& location, boost::format const& text)
    {
        write(lvl, location, text.str());
    }

    void write(boost::log::trivial::severity_level lvl, boost::format const& location, boost::format const& text)
    {
        write(lvl, location.str(), text.str());
    }

    void write(boost::log::trivial::severity_level lvl, boost::format const& location, std::string const& text)
    {
        write(lvl, location.str(), text);
    }

    void write(boost::log::trivial::severity_level lvl, std::string const& location, std::string const& text)
    {
        using level = boost::log::trivial::severity_level;

        auto logMsg = "[" + location + "] " + text;
        switch (lvl) {
            case level::trace:
                BOOST_LOG_TRIVIAL(trace) << logMsg;
                break;
            case level::debug:
                BOOST_LOG_TRIVIAL(debug) << logMsg;
                break;
            case level::info:
                BOOST_LOG_TRIVIAL(info) << logMsg;
                break;
            case level::warning:
                BOOST_LOG_TRIVIAL(warning) << logMsg;
                break;
            case level::error:
                BOOST_LOG_TRIVIAL(error) << logMsg;
                break;
            case level::fatal :
                BOOST_LOG_TRIVIAL(fatal) << logMsg;
                break;
            default:
                break;
        }
    }

} // end namespace goodok::log