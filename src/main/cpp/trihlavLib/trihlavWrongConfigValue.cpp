/*
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 * 
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 * 
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *	Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 *	der GNU General Public License, wie von der Free Software Foundation,
 *	Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 *	veröffentlichten Version, weiterverbreiten und/oder modifizieren.
 * 
 *	Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 *	OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 *	Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 *	Siehe die GNU General Public License für weitere Details.
 * 
 *	Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 *	Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */


#include "trihlavWrongConfigValue.hpp"

#include <string>
#include <vector>

#include <boost/locale.hpp>

using namespace std;

namespace trihlav {

static const string K_NO_REASON_SET("no-reason-set");
static const string K_WRONG_SIZE("wrong size");
static const string K_YBK_PRIVATE_ID(boost::locale::translate("Yubiko private ID"));
static const string K_YBK_SEC_KEY(boost::locale::translate("Yubiko secret key"));
static const string K_NO_VAL_SPECIFIED(boost::locale::translate("no value specified"));
static const string K_FAILED_FORMAT_MSG(boost::locale::translate("Failed to format the error message."));

const string& WrongConfigValue::getReasonStr(
    const WrongConfigValue::EReason pReason) {
    switch (pReason) {
    case EWrongSize:
        return K_WRONG_SIZE;
    case ENoReasonSet:
    default:
        return K_NO_REASON_SET;
    }
}

const string& WrongConfigValue::getValNameStr(
    const WrongConfigValue::EValNames pValName) {
    switch (pValName) {
    case EYbkPrivateId:
        return K_YBK_PRIVATE_ID;
    case EYbkSecretKey:
        return K_YBK_SEC_KEY;
    case ENoValSpecified:
    default:
        return K_NO_VAL_SPECIFIED;
    }
}

size_t WrongConfigValue::getExpected() const {
    return itsExpected;
}

void WrongConfigValue::setExpected(const size_t &value) {
    itsExpected = value;
}

const string& WrongConfigValue::getReal() const {
    return itsReal;
}

void WrongConfigValue::setReal(const size_t &value) {
    itsReal = value;
}

WrongConfigValue::EValNames WrongConfigValue::getValName() const {
    return itsValName;
}

void WrongConfigValue::setValName(const WrongConfigValue::EValNames &value) {
    itsValName = value;
}

WrongConfigValue::EReason WrongConfigValue::getReason() const {
    return itsReason;
}

void WrongConfigValue::setReason(const WrongConfigValue::EReason &value) {
    itsReason = value;
}

WrongConfigValue::WrongConfigValue(const WrongConfigValue::EValNames pValName,
                                   const size_t pExpected, const std::string& pReal) :
    itsValName(pValName), itsReason(EWrongSize), itsExpected(pExpected), itsReal(
        pReal),invalid_argument(K_FAILED_FORMAT_MSG.c_str())
{
    try {
        itsMsg=string("Config value \"")
               + WrongConfigValue::getValNameStr(itsValName)
               + "\" has wrong size, expected " + to_string(int(itsExpected))
               + ", but got " + to_string(int(itsReal.size()))+"(\""+itsReal+"\")";
    } catch (...) {
        itsMsg=K_FAILED_FORMAT_MSG.c_str();
    }
}

static vector<string> msgs;

const char* WrongConfigValue::what() const throw() {
    return itsMsg.c_str();
}

} // end namespace YuSerApi
