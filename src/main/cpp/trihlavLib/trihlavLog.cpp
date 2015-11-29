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

}
