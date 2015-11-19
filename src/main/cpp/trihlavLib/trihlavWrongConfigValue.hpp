#ifndef YUSERWRONGCONFIGVALUE_HPP
#define YUSERWRONGCONFIGVALUE_HPP

#include <stdexcept>

namespace trihlav {


class WrongConfigValue : virtual public std::invalid_argument
{
public:
    enum EValNames {
        EYbkPrivateId,
        ENoValSpecified
    };

    enum EReason {
        EWrongSize,
        ENoReasonSet
    };

    WrongConfigValue(const EValNames pValName, const size_t pExpected, const size_t pReal );

    size_t getExpected() const;

    void setExpected(const size_t &value);

    size_t getReal() const;

    void setReal(const size_t &value);

    EValNames getValName() const;

    void setValName(const EValNames &value);

    EReason getReason() const;

    void setItsReason(const EReason &value);

    const char* what() const throw();

    static const std::string& getReasonStr(const EReason pReason);

    static const std::string& getValNameStr(const EValNames pValName);

    virtual ~WrongConfigValue() throw() {}
private:
    EValNames itsValName;
    EReason itsReason;
    size_t itsExpected;
    size_t itsReal;
    std::string itsMsg;
};

}

#endif // YUSERWRONGCONFIGVALUE_HPP
