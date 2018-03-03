/*
 * trihlavIKeyListView.cpp
 *
 *  Created on: 18.01.2016
 *      Author: grobap
 */

#include "trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavKeyListViewIface.hpp"

namespace trihlav {

    KeyListViewIface::KeyRow_t KeyListViewIface::createRow( //
            int pRowIdx, //
            const YubikoOtpKeyConfig &pFromKey) const {
        return KeyRow_t(pRowIdx, //< Row index
                        pFromKey.getPublicId(), //< keys public id
                        pFromKey.getDescription(), //< description
                        pFromKey.getPrivateId(), //< private id
                        pFromKey.getUseCounter(), //< my use counter
                        pFromKey.getCounter());
    }


} /* namespace trihlav */
