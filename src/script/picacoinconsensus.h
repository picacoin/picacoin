// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Picacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PICACOIN_SCRIPT_PICACOINCONSENSUS_H
#define PICACOIN_SCRIPT_PICACOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_PICACOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/picacoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBPICACOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PICACOINCONSENSUS_API_VER 1

typedef enum picacoinconsensus_error_t
{
    picacoinconsensus_ERR_OK = 0,
    picacoinconsensus_ERR_TX_INDEX,
    picacoinconsensus_ERR_TX_SIZE_MISMATCH,
    picacoinconsensus_ERR_TX_DESERIALIZE,
    picacoinconsensus_ERR_AMOUNT_REQUIRED,
    picacoinconsensus_ERR_INVALID_FLAGS,
} picacoinconsensus_error;

/** Script verification flags */
enum
{
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    picacoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = picacoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | picacoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               picacoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | picacoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               picacoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | picacoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int picacoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, picacoinconsensus_error* err);

EXPORT_SYMBOL int picacoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, picacoinconsensus_error* err);

EXPORT_SYMBOL unsigned int picacoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // PICACOIN_SCRIPT_PICACOINCONSENSUS_H
