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

#include <string>
#include <boost/locale.hpp>

#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include "trihlavWtPushButton.hpp"
#include "trihlavWtKeyListView.hpp"

using std::string;
using boost::locale::translate;
using Wt::WText;
using Wt::WContainerWidget;
using Wt::WHBoxLayout;
using Wt::WVBoxLayout;
using Wt::WLength;
using Wt::WTable;

namespace trihlav {

void WtKeyListView::addTableHeader() {
	WText* myRecId = new WText(translate("Record ID").str());
	itsTable->elementAt(0, 0)->addWidget(myRecId);
	WText* myPublicId = new WText(translate("Public ID").str());
	itsTable->elementAt(0, 1)->addWidget(myPublicId);
	WText* myDescription = new WText(translate("Description").str());
	itsTable->elementAt(0, 2)->addWidget(myDescription);
	WText* myPrivateId = new WText(translate("Private ID").str());
	itsTable->elementAt(0, 3)->addWidget(myPrivateId);
	WText* myUseCounter = new WText(translate("Use counter").str());
	itsTable->elementAt(0, 4)->addWidget(myUseCounter);
	WText* myCounter = new WText(translate("Counter").str());
	itsTable->elementAt(0, 5)->addWidget(myCounter);
}

WtKeyListView::WtKeyListView() {
	itsPanel = new WContainerWidget;
	WHBoxLayout* myBtnsLayout = new WHBoxLayout;
	WVBoxLayout* myTopLayout = new WVBoxLayout;
	itsBtnAdd = new WtPushButton(translate("New key").str());
	itsBtnDel = new WtPushButton(translate("Delete key").str());
	itsBtnReload = new WtPushButton(translate("Reload keys").str());
	itsBtnEdit = new WtPushButton(translate("Edit key").str());
	itsBtnAdd->setWidth(WLength { 6, WLength::FontEm });
	itsBtnEdit->setWidth(WLength { 6, WLength::FontEm });
	itsBtnDel->setWidth(WLength { 6, WLength::FontEm });
	itsBtnReload->setWidth(WLength { 6, WLength::FontEm });
	myBtnsLayout->addWidget(itsBtnAdd);
	myBtnsLayout->addWidget(itsBtnEdit);
	myBtnsLayout->addWidget(itsBtnDel);
	myBtnsLayout->addWidget(itsBtnReload);
	itsTable = new WTable();
	itsTable->setHeaderCount(1);
	itsTable->addStyleClass("table-striped");
	itsTable->setWidth(Wt::WLength("100%"));
	myTopLayout->addLayout(myBtnsLayout);
	myTopLayout->addWidget(itsTable);
	itsPanel->setLayout(myTopLayout);
}

WtKeyListView::~WtKeyListView() {
}

Wt::WWidget* WtKeyListView::getWWidget() {
	return itsPanel;
}

ButtonIface& WtKeyListView::getBtnAddKey() {
	return *itsBtnAdd;
}

ButtonIface& WtKeyListView::getBtnEditKey() {
	return *itsBtnEdit;
}

ButtonIface& trihlav::WtKeyListView::getBtnDelKey() {
	return *itsBtnDel;
}

ButtonIface& trihlav::WtKeyListView::getBtnReload() {
	return *itsBtnReload;
}

void WtKeyListView::clear() {
	itsRowCounter = 0;
	itsTable->clear();
	addTableHeader();
}

void WtKeyListView::addRow(const KeyListRow_t pRow) {
	itsRowCounter++;
	auto myId = new Wt::WText(boost::lexical_cast<std::string>(pRow.get<0>()));
	auto myPrivId = new Wt::WText(pRow.get<1>());
	auto myDescription = new Wt::WText(pRow.get<2>());
	auto myPubId = new Wt::WText(pRow.get<3>());
	auto myCounter = new Wt::WText(boost::lexical_cast<std::string>(pRow.get<5>()));
	auto myUse = new Wt::WText(boost::lexical_cast<std::string>(pRow.get<4>()));
	itsTable->elementAt(itsRowCounter, 0)->addWidget(myId);
	itsTable->elementAt(itsRowCounter, 1)->addWidget(myPrivId);
	itsTable->elementAt(itsRowCounter, 2)->addWidget(myDescription);
	itsTable->elementAt(itsRowCounter, 3)->addWidget(myPubId);
	itsTable->elementAt(itsRowCounter, 4)->addWidget(myUse);
	itsTable->elementAt(itsRowCounter, 5)->addWidget(myCounter);
	itsTable->elementAt(itsRowCounter, 0)->setContentAlignment( Wt::AlignCenter );
	itsTable->elementAt(itsRowCounter, 1)->setContentAlignment( Wt::AlignCenter );
	itsTable->elementAt(itsRowCounter, 2)->setContentAlignment( Wt::AlignCenter );
	itsTable->elementAt(itsRowCounter, 3)->setContentAlignment( Wt::AlignCenter );
	itsTable->elementAt(itsRowCounter, 4)->setContentAlignment( Wt::AlignCenter );
	itsTable->elementAt(itsRowCounter, 5)->setContentAlignment( Wt::AlignCenter );
}

void WtKeyListView::addedAllRows() {
}

} /* namespace trihlav */
