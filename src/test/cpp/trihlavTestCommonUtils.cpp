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

#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyListViewIface.hpp"
#include "trihlavLib/trihlavLog.hpp"

#include "trihlavTestCommonUtils.hpp"

namespace trihlav {

    YubikoOtpKeyConfig createYubikoOtpKeyConfig(KeyManager &pKeyMan) {
        int myTimer = 333;
        trihlav::YubikoOtpKeyConfig myCfg0(pKeyMan);
        myCfg0.setDescription(K_TST_DESC0);
        myCfg0.setPrivateId(K_TST_PRIV0);
        myCfg0.setPublicId(K_TST_PUBL0);
        myCfg0.setCounter(K_TST_CNTR0);
        myCfg0.setRandom(K_TST_RNDM0);
        myCfg0.setSecretKey(K_TST_SECU0);
        myCfg0.setTimestamp(myTimer);
        myCfg0.save();
        myCfg0.computeCrc();
        logDebug_token(myCfg0.getToken());
        return myCfg0;
    }
}