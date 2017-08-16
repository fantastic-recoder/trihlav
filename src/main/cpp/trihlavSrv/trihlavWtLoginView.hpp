/*
 * trihlavWtLoginView.hpp
 *
 *  Created on: Jan 13, 2017
 *      Author: grobap
 */

#ifndef TRIHLAV_WT_LOGIN_VIEW_HPP_
#define TRIHLAV_WT_LOGIN_VIEW_HPP_

#include "trihlavLib/trihlavLoginViewIface.hpp"

#include "trihlavWtDialogView.hpp"

namespace trihlav {

class WtStrEdit;
class WtLabel;

/**
 * Wt based implementation of #LoginViewIface.
 */
class WtLoginView: virtual public WtDialogView, virtual public LoginViewIface {
public:
	WtLoginView();
	virtual StrEditIface& getEdtUserName() override;
	virtual StrEditIface& getEdtPassword() override;
	virtual LabelIface& getLblUserName() override;
	virtual LabelIface& getLblPassword() override;

private:
	WtStrEdit* m_EdtUserName;
	WtStrEdit* m_EdtPassword;
	WtLabel* m_LblUserName;
	WtLabel* m_LblPassword;
};

} /* namespace trihlav */

#endif /* TRIHLAV_WT_LOGIN_VIEW_HPP_ */
