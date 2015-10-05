#include "trihlavYubikoOtpKeyConfig.hpp"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "yubikey.h"
#include "trihlavWrongConfigValue.hpp"

namespace trihlavApi {

static const size_t K_YBK_PRIVATE_ID_LEN(YUBIKEY_UID_SIZE*2);
static const QString K_NM_PRIV_ID("privateId");
static const QString K_NM_TIMESTAMP("timestamp");
static const QString K_NM_SES_CNTR("counter");
static const QString K_NM_USE_CNTR("use");
static const QString K_NM_RANDOM("random");
static const QString K_NM_CRC("crc");
static const QString K_NM_KEY("key");

/**
  * ResDium's Yubikey Server API settings.
  */
QSettings theYuSerApiSettings("ResDium","yuSerApi");

/**
 * Just init fields, does not loads the data.
 * @param pDataPathDir Where the config data will be stored.
 */
YubikoOtpKeyConfig::YubikoOtpKeyConfig(const QString& pPath2KeyKonfig)
    :  itsChangedFlag(false)
    ,  itsFilename(pPath2KeyKonfig)
{
    memset(&itsToken,0,sizeof(yubikey_token_st));
}

/**
 * Getter.
 *
 * @return Hex-encoded string representing the private id Yubikey token part.
 */
const QString YubikoOtpKeyConfig::getPrivateId() const {
    QByteArray myRetVal(K_YBK_PRIVATE_ID_LEN+1,'\0');
    yubikey_hex_encode( myRetVal.data(), reinterpret_cast<const char*>(&itsToken.uid), YUBIKEY_UID_SIZE );
    return QString(myRetVal);
}

/**
 * Setter.
 *
 * @param pPrivateId Hex-encoded string representing the private id Yubikey token part.
 */
void YubikoOtpKeyConfig::setPrivateId(const QString &pPrivateId) {
    const QString myPrivateId(pPrivateId.trimmed());
    const QByteArray myPrivateIdBts(myPrivateId.toLatin1());
    if(myPrivateIdBts.size()!=K_YBK_PRIVATE_ID_LEN) {
        throw new WrongConfigValue(WrongConfigValue::EYbkPrivateId,K_YBK_PRIVATE_ID_LEN,myPrivateId.size());
    }
    if(getPrivateId() !=pPrivateId) {
        yubikey_hex_decode(reinterpret_cast<char*>(itsToken.uid),myPrivateIdBts.data(),YUBIKEY_UID_SIZE);
        itsChangedFlag=true;
    }
}

void
YubikoOtpKeyConfig::load()
{
    QFile myInFile(getFilename()+".json");
    if (!myInFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    const QByteArray myData = myInFile.readAll();
    const QJsonDocument myJsonDoc(QJsonDocument::fromJson(myData));
    const QJsonObject myCfgObj=myJsonDoc.object();
    setPrivateId(myCfgObj[K_NM_PRIV_ID].toString());
    setTimestamp(UTimestamp(myCfgObj[K_NM_TIMESTAMP].toInt()));
    itsChangedFlag=false;
}

void YubikoOtpKeyConfig::save() {
    QFile myOutFile(getFilename()+".json");

       if (!myOutFile.open(QIODevice::WriteOnly)) {
           qWarning("Couldn't open save file.");
           return;
       }

       QJsonObject myJsonCfgObject;
       myJsonCfgObject[K_NM_PRIV_ID]=getPrivateId();
       myJsonCfgObject[K_NM_TIMESTAMP]=getTimestamp().tstp_int;
       QJsonDocument myJsonOutDoc(myJsonCfgObject);
       myOutFile.write(myJsonOutDoc.toJson());
       itsChangedFlag=false;
}

YubikoOtpKeyConfig::~YubikoOtpKeyConfig() {
    if(itsChangedFlag) {
        save();
    }
}


void YubikoOtpKeyConfig::setFilename(const QString &value)
{
    itsFilename = value;
}


} // end namespace yuSerApi

