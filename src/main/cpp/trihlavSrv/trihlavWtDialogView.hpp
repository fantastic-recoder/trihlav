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

#ifndef TRIHLAV_WT_DIALOG_VIEW_HPP_
#define TRIHLAV_WT_DIALOG_VIEW_HPP_

#include <Wt/WDialog.h>

#include "trihlavLib/trihlavDialogViewIface.hpp"

namespace Wt {
    class WDialog;
}

namespace trihlav {

    class WtPushButton;

    class WtDialogView : virtual public DialogViewIface, virtual public Wt::Core::observable {
    private:
        WtPushButton *m_CancelBtn;
        WtPushButton *m_OkBtn;
        std::unique_ptr<Wt::WDialog> m_Dlg;
    public:
        WtDialogView();

        virtual ~WtDialogView();

        virtual const ButtonIface &getBtnCancel() const override;

        const Wt::WDialog &getDlg() const {
            return *m_Dlg;
        }

        virtual Wt::WDialog &getDlg();

        virtual ButtonIface &getBtnCancel() override;

        virtual const ButtonIface &getBtnOk() const override;

        virtual ButtonIface &getBtnOk() override;

        virtual void show() override;

    private:
        virtual void finishedSlot(Wt::DialogCode pCode);

    };
}

#endif //TRIHLAV_WT_DIALOG_VIEW_HPP_
