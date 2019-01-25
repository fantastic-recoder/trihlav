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

#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>

#include "trihlavLib/trihlavVersion.hpp"
#include "trihlavLib/trihlavSettings.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"

namespace {
    const char *const K_OPT_HELP = "help";
    const char *const K_OPT_LIST = "list";
    const char *const K_OPT_GEN = "generate";
    const char *const K_OPT_KEY = "key";
}

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::setw;
using trihlav::Version;
using trihlav::Settings;
using trihlav::KeyManager;
using trihlav::YubikoOtpKeyConfig;

namespace po = boost::program_options;

int main(int pArgC, char *pArgV[]) {
    cout << pArgV[0] << " version " << Version::getVersion() << endl;

    // Declare the supported options.
    po::options_description myOpts("Allowed options");
    myOpts.add_options()
            ((K_OPT_HELP + string(",h")).c_str(), "produce help message")
            ((K_OPT_LIST + string(",l")).c_str(), "list keys")
            ((K_OPT_GEN + string(",g")).c_str(), "generate")
            ((K_OPT_KEY + string(",k")).c_str(), po::value<string>(), "keyname");

    po::variables_map vm;
    po::store(po::parse_command_line(pArgC, pArgV, myOpts), vm);
    po::notify(vm);

    if (vm.count(K_OPT_HELP)) {
        cout << myOpts << "\n";
        return 1;
    }
    static Settings theSettings;
    static KeyManager theKeyManager(theSettings);
    if (vm.count(K_OPT_LIST)) {
        const size_t myKeyCnt = theKeyManager.loadKeys();
        cout << "Stored keys, (count=" << myKeyCnt << "):" << endl;
        for (size_t i = 0; i < myKeyCnt; ++i) {
            auto myKeyKonfig = theKeyManager.getKey(i);
            cout << setw(6) << i << "\t:\t" << myKeyKonfig.getPublicId() << "\t-\t:";
            cout << myKeyKonfig.getDescription() << endl;
        }
        return 0;
    }
    static string theKeyId;
    if (vm.count(K_OPT_KEY)) {
        theKeyId = vm[K_OPT_KEY].as<string>();
    }
    if (vm.count(K_OPT_GEN)) {
        if (theKeyId.empty()) {
            cerr << K_OPT_GEN << " needs a key id (name)!" << endl;
            return 2;
        }
        YubikoOtpKeyConfig *pCfg = theKeyManager.getKeyByPublicId(theKeyId);
        if (!pCfg) {
            cerr << "Invalid key id \"" << theKeyId << "\"!" << endl;
            return 3;
        }
        cout << "Generating OTP for \"" << theKeyId << "\"." << endl;
        cout << pCfg->generateOtp();
    }
    return 0;
}
