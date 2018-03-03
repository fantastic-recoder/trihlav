/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/locale/message.hpp>

#include "trihlavLib/trihlavKeyListPresenter.hpp"

#include "trihlavButtonIface.hpp"
#include "trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"

#include "trihlavKeyListViewIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"

namespace trihlav {

    KeyListPresenter::KeyListPresenter(FactoryIface &pFactory) :
            KeyListPresenterIface(pFactory), //
            CanOsAuthPresenter(pFactory), //
            m_YubikoOtpKeyPresenter(0) //
    {
    }

    void KeyListPresenter::disableKeyListBtns() {
        if (m_KeyListView == 0) {
            getView();
            return;
        }
        getView().getBtnAddKey().setEnabled(false);
        getView().getBtnDelKey().setEnabled(false);
        getView().getBtnEditKey().setEnabled(false);
        getView().getBtnReload().setEnabled(false);
    }

    KeyListViewIface &KeyListPresenter::getView() {
        if (m_KeyListView == 0) {
            m_KeyListView = getFactory().createKeyListView();
            getView().getBtnAddKey().pressedSig.connect([=] { addKey(); });
            getView().getBtnReload().pressedSig.connect([=] { reloadKeyList(); });
            getView().getBtnEditKey().pressedSig.connect([=] { editKey(); });
            getView().getBtnDelKey().pressedSig.connect([=] { deleteKey(); });
            getView().selectionChangedSig.connect(
                    [=](int pIdx) { selectionChanged(pIdx); });
            disableKeyListBtns();
        }
        return *m_KeyListView;
    }

    KeyListPresenter::~KeyListPresenter() {
        delete m_YubikoOtpKeyPresenter;
    }

    void KeyListPresenter::addKey() {
        getYubikoOtpKeyPresenter().addKey();
    }

    YubikoOtpKeyPresenter &KeyListPresenter::getYubikoOtpKeyPresenter() {
        if (m_YubikoOtpKeyPresenter == 0) {
            m_YubikoOtpKeyPresenter = new YubikoOtpKeyPresenter(getFactory());
            m_YubikoOtpKeyPresenter->saved.connect([=] { reloadKeyList(); });
        }
        return *m_YubikoOtpKeyPresenter;
    }

    void KeyListPresenter::reloadKeyList() {
        BOOST_LOG_NAMED_SCOPE("YubikoOtpKeyPresenter::reloadKeyList");
        KeyManager &myKeyMan(getFactory().getKeyManager());
        const size_t myKeySz = myKeyMan.loadKeys();
        getView().clear();
        for (int myRow = 0; myRow < myKeySz; ++myRow) {
            const auto &myKey = myKeyMan.getKey(myRow);
            getView().addRow(getView().createRow(myRow, myKey));
        }
        getView().addedAllRows();
        getView().selectionChangedSig(-1);
    }

    void KeyListPresenter::doProtectedAction(bool pStatus) {
        if (pStatus) {
            getView().getBtnAddKey().setEnabled(true);
            getView().getBtnReload().setEnabled(true);
            reloadKeyList();
        } else {
            getView().getBtnAddKey().setEnabled(false);
            getView().getBtnDelKey().setEnabled(false);
            getView().getBtnEditKey().setEnabled(false);
            getView().getBtnReload().setEnabled(false);
        }
    }

    bool KeyListPresenter::checkSelection() const {
        if (m_SelectedKey == -1) {
            BOOST_LOG_TRIVIAL(warning) << "KeyListPresenter edit/delete "
                        "called without proper selection.";
            return false;
        }
        return true;
    }

    void KeyListPresenter::editKey() {
        BOOST_LOG_NAMED_SCOPE("KeyListPresenter::editKey");
        if (checkSelection()) {
            KeyManager &myKeyMan(getFactory().getKeyManager());
            getYubikoOtpKeyPresenter().editKey(myKeyMan.getKey(m_SelectedKey));
        }
    }

    void KeyListPresenter::deleteKey() {
        BOOST_LOG_NAMED_SCOPE("KeyListPresenter::deleteKey");
        if (checkSelection()) {
            KeyManager &myKeyMan(getFactory().getKeyManager());
            getYubikoOtpKeyPresenter().deleteKey(myKeyMan.getKey(m_SelectedKey));
        }
    }

    void KeyListPresenter::selectionChanged(int pIdx) {
        BOOST_LOG_NAMED_SCOPE("KeyListPresenter::selectionChange");
        if (pIdx == -1) {
            getView().getBtnDelKey().setEnabled(false);
            getView().getBtnEditKey().setEnabled(false);
        } else {
            getView().getBtnDelKey().setEnabled(true);
            getView().getBtnEditKey().setEnabled(true);
        }
        m_SelectedKey = pIdx;
        BOOST_LOG_TRIVIAL(debug) << "Curently selected " << m_SelectedKey;
    }

}
/* namespace trihlav */
