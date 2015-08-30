/*
 * App.hpp
 *
 *  Created on: 30.08.2015
 *      Author: grobap
 */

#ifndef SRC_TRIHLAVSRV_TRIHLAVAPP_HPP_
#define SRC_TRIHLAVSRV_TRIHLAVAPP_HPP_

#include <Wt/WApplication>

namespace Wt {
	class WEnvironment;
	class WLineEdit;
	class WText;
}

namespace trihlav {

class App : public Wt::WApplication {
public:
	App(const Wt::WEnvironment& pEnv);
	virtual ~App();
	static App *createApplication(const Wt::WEnvironment& pEnv);
private:
	Wt::WLineEdit *nameEdit_;
	Wt::WText *greeting_;

    void check();
};

} /* namespace trihlav */

#endif /* SRC_TRIHLAVSRV_TRIHLAVAPP_HPP_ */
