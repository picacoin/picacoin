// Copyright (c) 2016-2019 The Picacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PICACOIN_UTIL_RBF_H
#define PICACOIN_UTIL_RBF_H

#include <cstdint>

class CTransaction;

static const uint32_t MAX_BIP125_RBF_SEQUENCE = 0xfffffffd;

// Check whether the sequence numbers on this transaction are signaling
// opt-in to replace-by-fee, according to BIP 125
bool SignalsOptInRBF(const CTransaction &tx);

#endif // PICACOIN_UTIL_RBF_H
