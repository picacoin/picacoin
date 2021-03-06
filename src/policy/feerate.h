// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Picacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PICACOIN_POLICY_FEERATE_H
#define PICACOIN_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

const std::string CURRENCY_UNIT = "PIC"; // One formatted unit
const std::string CURRENCY_ATOM = "pio"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    PIC_KVB,      //!< Use PIC/kvB fee rate unit
    SAT_VB,       //!< Use pio/vB fee rate unit
};

/**
 * Fee rate in picaro per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nPicarosPerK; // unit is picaro-per-1,000-bytes

public:
    /** Fee rate of 0 picaro per kB */
    CFeeRate() : nPicarosPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nPicarosPerK): nPicarosPerK(_nPicarosPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }
    /** Constructor for a fee rate in picaro per kvB (pio/kvB). The size in bytes must not exceed (2^63 - 1).
     *
     *  Passing an nBytes value of COIN (1e8) returns a fee rate in picaro per vB (pio/vB),
     *  e.g. (nFeePaid * 1e8 / 1e3) == (nFeePaid / 1e5),
     *  where 1e5 is the ratio to convert from PIC/kvB to pio/vB.
     *
     *  @param[in] nFeePaid  CAmount fee rate to construct with
     *  @param[in] nBytes    size_t bytes (units) to construct with
     */
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    /**
     * Return the fee in picaro for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
    /**
     * Return the fee in picaro for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK < b.nPicarosPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK > b.nPicarosPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK == b.nPicarosPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK <= b.nPicarosPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK >= b.nPicarosPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nPicarosPerK != b.nPicarosPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nPicarosPerK += a.nPicarosPerK; return *this; }
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::PIC_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nPicarosPerK); }
};

#endif //  PICACOIN_POLICY_FEERATE_H
