#include <yubikey.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

namespace trihlav {

    namespace attrs = boost::log::attributes;
    namespace expr = boost::log::expressions;
    namespace keywords = boost::log::keywords;
    namespace src = boost::log::sources;


    void initLog() {
        boost::log::add_common_attributes();
        boost::shared_ptr<boost::log::core> p_core = boost::log::core::get();
        p_core->add_global_attribute("Scope", attrs::named_scope());
        /* log formatter:
         * [TimeStamp] [ThreadId] [Severity Level] [Scope] Log message
         */
        auto fmtTimeStamp = boost::log::expressions::format_date_time<
                boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
        auto fmtThreadId = boost::log::expressions::attr<
                boost::log::attributes::current_thread_id::value_type>("ThreadID");
        auto fmtSeverity = boost::log::expressions::attr<
                boost::log::trivial::severity_level>("Severity");
        auto fmtScope = boost::log::expressions::format_named_scope("Scope",
                                                                    boost::log::keywords::format = "%n",
                                                                    boost::log::keywords::iteration = boost::log::expressions::reverse,
                                                                    boost::log::keywords::depth = 2);
        boost::log::formatter logFmt = boost::log::expressions::format(
                "[%1%] (%2%) [%3% \t] [%4%] %5%") % fmtTimeStamp % fmtThreadId
                                       % fmtSeverity % fmtScope % boost::log::expressions::smessage;
        /* console sink */
        auto consoleSink = boost::log::add_console_log(std::clog);
        consoleSink->set_formatter(logFmt);
    }

    void logDebug_token(const yubikey_token_st &pToken) {
        BOOST_LOG_NAMED_SCOPE("logDebug_token");
        std::__cxx11::string myUid(YUBIKEY_UID_SIZE * 2 + 1, ' ');
        yubikey_hex_encode(&myUid[0], reinterpret_cast<const char *>(&pToken.uid),
                           YUBIKEY_UID_SIZE);
        BOOST_LOG_TRIVIAL(debug) << "yubikey_token_st:{";
        BOOST_LOG_TRIVIAL(debug) << "   uid  :\"" << myUid.c_str() << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   ctr  :\"" << int(pToken.ctr) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   use  :\"" << int(pToken.use) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   rnd  :\"" << int(pToken.rnd) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   tstpl:\"" << int(pToken.tstpl) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   tstph:\"" << int(pToken.tstph) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "   crc  :\"" << int(pToken.crc) << "\"";
        BOOST_LOG_TRIVIAL(debug) << "}";
    }
}
