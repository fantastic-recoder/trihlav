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
#ifndef TRIHLAV_TRIHLAVTESTCOMMONUTILS_HPP
#define TRIHLAV_TRIHLAVTESTCOMMONUTILS_HPP

namespace trihlav {

    class KeyManager;

    class YubikoOtpKeyConfig;

    YubikoOtpKeyConfig createYubikoOtpKeyConfig(KeyManager &pKeyMan);

    constexpr static const int K_TST_CNTR0 = 1;
    constexpr static const int K_TST_RNDM0 = 11;
    constexpr static const char *K_TST_PUBL0 = "ccddccddccdd";
    constexpr static const char *K_TST_SECU0 = "ddeeddeeddeeddeeddeeddeeddeeddee";
    constexpr static const char *K_TST_DESC0 = "Test key 1";
    constexpr static const char *K_TST_PRIV0 = "aabbaabbaabb";

}

#endif //TRIHLAV_TRIHLAVTESTCOMMONUTILS_HPP
