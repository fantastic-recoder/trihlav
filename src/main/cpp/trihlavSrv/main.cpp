#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include <Wt/WContainerWidget.h>

#include "trihlavApp.hpp"
#include "trihlavWtAuthResource.hpp"
#include "trihlavLib/trihlavLogApi.hpp"


#include "trihlavLib/trihlavConstants.hpp"

#if defined(__unix__)

#include <signal.h>

#endif

#if defined(__WIN32) || defined(__WIN64)
#include <process.h>
#endif

#ifdef ANDROID
#include "Android.h"
#endif

using namespace trihlav;
using namespace Wt;

static const char *K_TRIHLAV_WT_HTTPD_CFG = "/etc/trihlav/wt_httpd.ini";

int main(int argc, char **argv, char **envp) {
    try {
        // use argv[0] as the application name to match a suitable entry
        // in the Wt configuration file, and use the default configuration
        // file (which defaults to /etc/wt/wt_config.xml unless the environment
        // variable WT_CONFIG_XML is set)
        WServer myServer(argv[0]);
        // WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
        myServer.setServerConfiguration(argc, argv, K_TRIHLAV_WT_HTTPD_CFG);
        // add a single entry point, at the default location (as determined
        // by the server configuration's deploy-path)
        myServer.addEntryPoint(EntryPointType::Application, &App::createApplication, "/trihlav");
        // create the auth REST resource
        WtAuthResource myAuthResource;
        myServer.addResource(&myAuthResource, K_AUTH_URL);
        if (myServer.start()) {
            int sig = WServer::waitForShutdown();
            BOOST_LOG_TRIVIAL(error) << "Shutdown (signal = " << sig << ")" << std::endl;
            myServer.stop();
            if (sig == SIGHUP)
                WServer::restart(argc, argv, envp);
        }
    } catch (WServer::Exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
        return 1;
    }
}
