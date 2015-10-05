
#include "trihlavApi.hpp"

#include "yubikey.h"

using namespace std;

namespace trihlavApi {

    /**
     * @param pPasswd
     * @return true if the password has been valid.
     */
    bool check(const std::string &pPasswd) {
        uint8_t myToken[YUBIKEY_BLOCK_SIZE] ;
        uint8_t myKey[YUBIKEY_KEY_SIZE];
        yubikey_token_t myOutToken;
        yubikey_parse (myToken,myKey,myOutToken);

        return false;
    }
}
