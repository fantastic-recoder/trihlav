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

#include <Wt/WAbstractTableModel>
#include <Wt/WModelIndex>

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
			itsCaptions(pCaptions) {
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
			return itsCaptions.size();
		return sizeof...(Columns_t);
	}

	/**
	 * @param pIndex parent index
	 * @param pRole what will be done with the return value eg. it will be displayed
	 * @return the value of the cell
	 */
	virtual boost::any data(const Wt::WModelIndex& pIndex, int pRole =
			Wt::DisplayRole) const override {
		const int myColumn = pIndex.column();
		if (pRole == Wt::DisplayRole) {
			if (myColumn > sizeof ... (Columns_t)) {
				return boost::any();
			} else {
				return boost::apply_visitor(Rec2StrVisitor(),
						TupleList_t::get(pIndex.row(),myColumn));
			}
		}
		return boost::any();
	}

	int getIdOfRow(size_t pRow) {
		return TupleList_t::get(0,pRow);
	}

	/**
	 * @brief Returns the header data for a column
	 */
	boost::any headerData(int pSection, Wt::Orientation pOrientation =
			Wt::Horizontal, int pRole = Wt::DisplayRole) const override {
		if (pOrientation == Wt::Horizontal) {
			switch (pRole) {
				case Wt::DisplayRole:
				if (pSection >= itsCaptions.size()) {
					return boost::any("-");
				}
				return itsCaptions[pSection];
				default:
				return boost::any();

			}
		}
		return boost::any();
	}

	virtual void clear() {
		TupleList_t::clear();
	}

private:
	const Captions_t itsCaptions;
};

}

#endif /* TRIHLAV_WT_LIST_MODEL_HPP_ */
