#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

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

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText     *greeting_;

    void greet();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
HelloApplication::HelloApplication(const Wt::WEnvironment& env)
        : WApplication(env)
{
    setTitle("Hello world");                            // application title

    root()->addWidget(Wt::cpp14::make_unique<Wt::WText>("Your name, please ? ")); // show some text

    nameEdit_ = root()->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // allow text input
    nameEdit_->setFocus();                              // give focus

    auto button = root()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Greet me."));
    // create a button
    button->setMargin(5, Wt::Side::Left);                   // add 5 pixels margin

    root()->addWidget(Wt::cpp14::make_unique<Wt::WBreak>());    // insert a line break
    greeting_ = root()->addWidget(Wt::cpp14::make_unique<Wt::WText>()); // empty text

    /*
     * Connect signals with slots
     *
     * - simple Wt-way: specify object and method
     */
    button->clicked().connect(this, &HelloApplication::greet);

    /*
     * - using an arbitrary function object, e.g. useful to bind
     *   values with std::bind() to the resulting method call
     */
    nameEdit_->enterPressed().connect(std::bind(&HelloApplication::greet, this));

    /*
     * - using a lambda:
     */
    button->clicked().connect([=]() {
        std::cerr << "Hello there, " << nameEdit_->text() << std::endl;
    });
}

void HelloApplication::greet()
{
    /*
     * Update the text, using text input into the nameEdit_ field.
     */
    greeting_->setText("Hello there, " + nameEdit_->text());
}


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
        myServer.addEntryPoint(EntryPointType::Application, &App::createApplication,"/trihlav");
		// create the auth REST resource
		WtAuthResource myAuthResource;
		myServer.addResource(&myAuthResource,K_AUTH_URL);
		if (myServer.start()) {
            int sig = WServer::waitForShutdown();
			BOOST_LOG_TRIVIAL(error) << "Shutdown (signal = " << sig << ")" << std::endl;
			myServer.stop();
			if (sig == SIGHUP)
                WServer::restart(argc, argv, envp);
		}
	} catch (WServer::Exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	} catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << "\n";
		return 1;
	}
}
