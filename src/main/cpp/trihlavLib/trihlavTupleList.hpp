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

#ifndef TRIHLAV_TUPLE_LIST_HPP_
#define TRIHLAV_TUPLE_LIST_HPP_

#include <stdexcept>
#include <vector>
#include <string>
#include <tuple>

#include <boost/variant.hpp>

namespace trihlav {

/**
 * A list of tuples-records.
 */
template<typename ... Columns_t>
class TupleList {
public:
	typedef std::tuple<Columns_t ...> Row_t;
	typedef std::vector<Row_t> RowList_t;

	constexpr static const size_t K_COL_CNT = sizeof...(Columns_t);

	void addRow(const Row_t pRowNum) {
		itsRows.push_back(pRowNum);
	}

	const Row_t& getRow(size_t pRowNum) const {
		const size_t mySz { itsRows.size() };
		if (pRowNum >= mySz) {
			throw std::out_of_range(
					"Row " + std::to_string(pRowNum) + " out of range [0.."
							+ std::to_string(mySz) + "].");
		}
		return itsRows[pRowNum];
	}

	const auto get(size_t pRowNum, size_t pColNum) const {
		return get_intern<0>(pRowNum,pColNum);
	}

	const size_t getRowCount() const {
		itsRows.size();
	}

	void clear() {
		itsRows.clear();
	}

private:

	template<size_t I>
	const boost::variant<Columns_t ...> get_intern(size_t pRowNum, size_t pColNum) const {
		if (pColNum == I) {
			return std::get < I > (getRow(pRowNum));
		} else if (I >= K_COL_CNT) {
			throw std::out_of_range("Tuple element out of range. Column "
					+std::to_string(pColNum)+" > "+std::to_string(K_COL_CNT)+".");
		}
		return this->get_intern<(I < K_COL_CNT-1 ? I+1 : 0)>(pRowNum,pColNum);
	}

	RowList_t itsRows;

};

}

#endif /* TRIHLAV_TUPLE_LIST_HPP_ */
