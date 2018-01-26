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

#ifndef TRIHLAV_WT_LIST_MODEL_HPP_
#define TRIHLAV_WT_LIST_MODEL_HPP_

#include <string>

#include <Wt/WAbstractTableModel.h>
#include <Wt/WModelIndex.h>
#include <Wt/WAny.h>

#include "trihlavLib/trihlavRec2StrVisitor.hpp"
#include "trihlavLib/trihlavTupleList.hpp"

namespace trihlav {

/**
 * @brief A list of records.
 *
 * Stores a list of records in memory.
 *
 */
template<typename ... Columns_t>
class WtListModel: public Wt::WAbstractTableModel, public TupleList< Columns_t ... > {
public:
	typedef std::vector<std::string> Captions_t;
	typedef TupleList<Columns_t...> TupleList_t;

	/**
	 *
	 * @param pCaptions column captions
	 */
	WtListModel(const std::vector<std::string>& pCaptions) :
			m_Captions(pCaptions) {
	}

	/**
	 * @brief Returns the table row count (only for the invalid parent!)
	 */
	virtual int rowCount(const Wt::WModelIndex &pParent =
			Wt::WModelIndex()) const override {
		if (!pParent.isValid())
			return TupleList_t::getRowCount();
		return 0;
	}

	/**
	 * @brief Returns the table column count (only for the invalid parent!)
	 */
	int columnCount(const Wt::WModelIndex &pParent = Wt::WModelIndex()) const
			override {
		if (!pParent.isValid())
			return m_Captions.size();
		return sizeof...(Columns_t);
	}

	/**
	 * @param pIndex parent index
	 * @param pRole what will be done with the return value eg. it will be displayed
	 * @return the value of the cell
	 */
	virtual Wt::cpp17::any data(const Wt::WModelIndex &pIndex, Wt::ItemDataRole pRole =
	Wt::ItemDataRole::Display) const override {
		const int myColumn = pIndex.column();
		if (pRole == Wt::ItemDataRole::Display) {
			if (myColumn > sizeof ... (Columns_t)) {
				return Wt::cpp17::any::any();
			} else {
				return boost::apply_visitor(Rec2StrVisitor(),
						TupleList_t::get(pIndex.row(),myColumn));
			}
		}
		return Wt::cpp17::any::any();
	}

	int getIdOfRow(size_t pRow) {
		return TupleList_t::get(0,pRow);
	}

	/**
	 * @brief Returns the header data for a column
	 */
	Wt::cpp17::any headerData(int pSection, Wt::Orientation pOrientation =
	Wt::Orientation::Horizontal, Wt::ItemDataRole pRole = Wt::ItemDataRole::Display) const override {
		if (pOrientation == Wt::Orientation::Horizontal) {
			if (pRole == Wt::ItemDataRole::Display) {
				if (pSection >= m_Captions.size()) {
					return Wt::cpp17::any("-");
				}
				return m_Captions[pSection];
			}
		}
		return Wt::cpp17::any();
	}

	virtual void clear() {
		const size_t myRows{TupleList_t::getRowCount()};
		beginRemoveRows(Wt::WModelIndex(),0,myRows);
		TupleList_t::clear();
		endRemoveRows();
	}

	virtual void addRow(const typename TupleList_t::Row_t pRow) {
		const size_t myRows{TupleList_t::getRowCount()};
		beginInsertRows(Wt::WModelIndex(),myRows,myRows+1);
		insertRow(myRows);
		TupleList_t::addRow(pRow);
		endInsertRows();
	}

	virtual void doReset() {
		reset();
		dataChanged().emit(createIndex(0,0,0UL),createIndex(rowCount(),columnCount(),0UL));
	}
private:
	const Captions_t m_Captions;
};

}

#endif /* TRIHLAV_WT_LIST_MODEL_HPP_ */
