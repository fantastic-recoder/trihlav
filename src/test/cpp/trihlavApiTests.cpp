#include <QtCore/QString>
#include <QtCore/QStandardPaths>
#include <QtCore/QTemporaryFile>
#include <QtTest/QtTest>

#include <yubikey.h>
#include <string>

#include "trihlavUTimestamp.hpp"
#include "trihlavYubikoOtpKeyConfig.hpp"

using namespace trihlavApi;

class YuSerTests : public QObject
{
    Q_OBJECT

public:
    YuSerTests();

private:
    
private slots:
    /// @brief Test low level calls to yubikey library
    void testHexToString();
    /// @brief Test the high level calls to yubikey library
    void testGenerateAndParse();
    /// @brief Test the memory layout of the UTimestamp union.
    void testUTimestampMemLayout();
    /// @brief Test loadind and saving of yubikey OTP settings.
    void testLoadAndSaveKeyCfg();
};

QTEST_APPLESS_MAIN (YuSerTests)

/**
 * A do nothing constructor.
 */
YuSerTests::YuSerTests()
{
    qDebug("<--> YuSerTests");
}

/**
 * Test the yubico-c library text to string calls.
 */
void YuSerTests::testHexToString()
{
    qDebug("--> testHexToString()");
    const char* K_TEST0="quantum";
    const size_t K_TEST0_SIZE = strlen(K_TEST0);
    std::string myTest0HexEncoded(K_TEST0_SIZE * 2 + 1, ' ');
    const std::string K_EXPECTED("7175616e74756d\0",K_TEST0_SIZE * 2 + 1);
    yubikey_hex_encode(&myTest0HexEncoded[0],K_TEST0,K_TEST0_SIZE);
    qDebug("Encoded \"%s\" is \"%s\"",K_TEST0,myTest0HexEncoded.c_str());
    QCOMPARE(myTest0HexEncoded,K_EXPECTED);
    qDebug("<-- testHexToString()");
}


inline void qDebug_token( const yubikey_token_st& pToken) {
    std::string myUid(YUBIKEY_UID_SIZE * 2 + 1, ' ');
    yubikey_hex_encode(&myUid[0],reinterpret_cast<const char*>(&pToken.uid),YUBIKEY_UID_SIZE);
    qDebug("yubikey_token_st:{");
    qDebug("   uid  :\"%s\",",myUid.c_str());
    qDebug("   ctr  :\"%d\",",int(pToken.ctr));
    qDebug("   use  :\"%d\",",int(pToken.use));
    qDebug("   rnd  :\"%d\",",int(pToken.rnd));
    qDebug("   tstpl:\"%d\",",int(pToken.tstpl));
    qDebug("   tstph:\"%d\",",int(pToken.tstph));
    qDebug("   crc  :\"%d\"",int(pToken.crc));
    qDebug("}");
}

/**
 * Generate two OTPs, parse them and check token parts
 * @return void
 */
void YuSerTests::testGenerateAndParse() {
    qDebug("--> testGenerateAndParse()");
    /* Decrypt TOKEN using KEY and store output in OUT structure.  Note
     that there is no error checking whether the output data is valid or
     not, use yubikey_check_* for that. */
    const uint8_t   myKey[YUBIKEY_KEY_SIZE]= {
        0xaa,0xff,0x0c,0x00,
        0xa1,0xef,0x1c,0x10,
        0xa2,0xdf,0x3c,0x30,
        0xa3,0xff,0xcc,0x60
    };
    const char K_Y_UID[YUBIKEY_UID_SIZE+1] = "012543";
    /* Generate OTP */
    yubikey_token_st myToken, myTokenBack;
    const size_t K_YBK_TKEN_SZ=sizeof(myToken);
    qDebug("sizeof(time_t)==%d",int(sizeof(time_t)));
    UTimestamp myTstp;
    myTstp.tstp_int =time(0);
    memcpy(&myToken.uid,K_Y_UID,YUBIKEY_UID_SIZE);
    myToken.ctr = 3;
    myToken.use = 4;
    myToken.rnd = 42;
    myToken.tstpl=myTstp.tstp.tstpl;
    myToken.tstph=myTstp.tstp.tstph;
    myToken.crc=0;
    myToken.crc=~yubikey_crc16(reinterpret_cast<uint8_t*>(&myToken),
			      K_YBK_TKEN_SZ-sizeof(myToken.crc));
    memcpy(&myTokenBack,&myToken,sizeof(myToken));
    qDebug_token(myTokenBack);
    char myOtp0[YUBIKEY_OTP_SIZE],myOtp1[YUBIKEY_OTP_SIZE];
    yubikey_generate (&myToken,
                      myKey,
                      myOtp0);
    qDebug("Generated yubikey OTP (0) %s",myOtp0);
    yubikey_parse(reinterpret_cast<uint8_t*>(myOtp0),myKey,&myToken);
    qDebug_token(myToken);
    QCOMPARE(myTokenBack.ctr,myToken.ctr);
    QCOMPARE(myTokenBack.rnd,myToken.rnd);
    QCOMPARE(myTokenBack.use,myToken.use);
    QCOMPARE(myTokenBack.tstph,myToken.tstph);
    QCOMPARE(myTokenBack.tstpl,myToken.tstpl);
    QVERIFY2(strncmp(
    		reinterpret_cast<const char*>(&myTokenBack.uid),
    		reinterpret_cast<char*>(&myToken.uid),
			YUBIKEY_UID_SIZE)==0,
    		"The uid-s are different!");
    uint16_t myCrc = yubikey_crc16(reinterpret_cast<uint8_t*>(&myToken),
		      YUBIKEY_KEY_SIZE);
    qDebug("crc1=%d %d",myCrc,YUBIKEY_CRC_OK_RESIDUE);
    QVERIFY2(yubikey_crc_ok_p(reinterpret_cast<uint8_t*>(&myToken)),"CRC failed!");
    yubikey_generate (&myToken,
                      myKey,
                      myOtp1);
    qDebug("Generated yubikey OTP (1) %s",myOtp1);
    QVERIFY2(strncmp(myOtp0,myOtp1,YUBIKEY_OTP_SIZE)==0,"The (re)generatet keys are different!");
    qDebug("<-- testGenerateAndParse()");
}

void YuSerTests::testUTimestampMemLayout() {
	UTimestamp myTstp;
	myTstp.tstp_int = 0x6789ABCD;
	QVERIFY2(sizeof(myTstp)==4,"Memory alignment is not bytewise!");
    QCOMPARE(int(myTstp.tstp.tstpl),int(0x6789));
    QCOMPARE(int(myTstp.tstp.tstph),int(0xAB));
    QCOMPARE(int(myTstp.tstp.filler),int(0xCD));
}

void YuSerTests::testLoadAndSaveKeyCfg() {
    /*
    QStandardPaths::setTestModeEnabled(true);
    QString myTestDtaPth=QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    */
    QTemporaryFile myTestCfgFile;
    Q_ASSERT(myTestCfgFile.open());
    QString myTestDtaPth=myTestCfgFile.fileName();
    myTestCfgFile.close();
    Q_ASSERT( myTestCfgFile.remove());
    qDebug(QString("Test data location: %1").arg(myTestDtaPth).toLatin1());
    YubikoOtpKeyConfig myTestCfg0(myTestDtaPth);
    myTestCfg0.setPrivateId("010203040506");
    myTestCfg0.setTimestamp(UTimestamp(12345));
    myTestCfg0.setCounter(33);
    myTestCfg0.setRandom(44);
    myTestCfg0.setCrc(55);
    myTestCfg0.setUseCounter(7);
    QCOMPARE(int(myTestCfg0.getToken().uid[0]),1);
    QCOMPARE(int(myTestCfg0.getToken().uid[1]),2);
    QCOMPARE(int(myTestCfg0.getToken().uid[2]),3);
    QCOMPARE(int(myTestCfg0.getToken().uid[3]),4);
    QCOMPARE(int(myTestCfg0.getToken().uid[4]),5);
    QCOMPARE(int(myTestCfg0.getToken().uid[5]),6);
    QCOMPARE(myTestCfg0.getPrivateId(),QString("010203040506"));

    QCOMPARE(int(myTestCfg0.getToken().ctr),33);
    QCOMPARE(int(myTestCfg0.getToken().rnd),44);
    QCOMPARE(int(myTestCfg0.getToken().crc),55);
    QCOMPARE(int(myTestCfg0.getToken().use),7);


    myTestCfg0.save();
    YubikoOtpKeyConfig myTestCfg1(myTestDtaPth);
    myTestCfg1.load();
    QCOMPARE(myTestCfg0.getPrivateId()         ,myTestCfg1.getPrivateId()         );
    QCOMPARE(myTestCfg0.getTimestamp().tstp_int,myTestCfg1.getTimestamp().tstp_int);
    QCOMPARE(myTestCfg0.getCounter()           ,myTestCfg1.getCounter()           );
    QCOMPARE(myTestCfg0.getCrc()               ,myTestCfg1.getCrc()               );
    QCOMPARE(myTestCfg0.getRandom()            ,myTestCfg1.getRandom()            );
    QCOMPARE(myTestCfg0.getUseCounter()        ,myTestCfg1.getUseCounter()        );
}


#include "tst_YuSerTests.moc"
