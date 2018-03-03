#ifndef YUSERWRONGCONFIGVALUE_HPP
#define YUSERWRONGCONFIGVALUE_HPP

#include <stdexcept>

namespace trihlav {


    class WrongConfigValue : virtual public std::invalid_argument {
    public:
        enum EValNames {
            EYbkPrivateId,
            ENoValSpecified,
            EYbkSecretKey
        };

        enum EReason {
            EWrongSize,
            ENoReasonSet
        };

        WrongConfigValue(const EValNames pValName, const size_t pExpected, const std::string &pReal);

        size_t getExpected() const;

        void setExpected(const size_t &value);

        const std::string &getReal() const;

        void setReal(const size_t &value);

        EValNames getValName() const;

        void setValName(const EValNames &value);

        EReason getReason() const;

        void setReason(const EReason &value);

        const char *what() const throw();

        static const std::string &getReasonStr(const EReason pReason);

        static const std::string &getValNameStr(const EValNames pValName);

        virtual ~WrongConfigValue() throw() {}

    private:
        EValNames m_ValName;
        EReason m_Reason;
        size_t m_Expected;
        std::string m_Real;
        std::string m_Msg;
    };

}

#endif // YUSERWRONGCONFIGVALUE_HPP
