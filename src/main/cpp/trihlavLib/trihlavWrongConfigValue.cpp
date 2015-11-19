#include "trihlavWrongConfigValue.hpp"

#include <string>
#include <vector>

using namespace std;

namespace trihlav {

static const string K_NO_REASON_SET("no-reason-set");
static const string K_WRONG_SIZE("wrong size");
static const string K_YBK_PRIVATE_ID("yubiko private ID");
static const string K_NO_VAL_SPECIFIED("no value specified");
static const string K_FAILED_FORMAT_MSG("Failed to format the error message.");

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

size_t WrongConfigValue::getReal() const {
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

void WrongConfigValue::setItsReason(const WrongConfigValue::EReason &value) {
	itsReason = value;
}

WrongConfigValue::WrongConfigValue(const WrongConfigValue::EValNames pValName,
		const size_t pExpected, const size_t pReal) :
		itsValName(pValName), itsReason(EWrongSize), itsExpected(pExpected), itsReal(
				pReal),invalid_argument(K_FAILED_FORMAT_MSG.c_str())
{
	try {
		itsMsg=string("Config value \"")
						+ WrongConfigValue::getValNameStr(itsValName)
						+ "\" has wrong size, expected " + to_string(int(itsExpected))
						+ ", but got " + to_string(int(itsReal));
	} catch (...) {
		itsMsg=K_FAILED_FORMAT_MSG.c_str();
	}
}

static vector<string> msgs;

const char* WrongConfigValue::what() const throw() {
	return itsMsg.c_str();
}

} // end namespace YuSerApi
