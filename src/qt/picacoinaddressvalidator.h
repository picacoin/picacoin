// Copyright (c) 2011-2020 The Picacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PICACOIN_QT_PICACOINADDRESSVALIDATOR_H
#define PICACOIN_QT_PICACOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class PicacoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PicacoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Picacoin address widget validator, checks for a valid picacoin address.
 */
class PicacoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PicacoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // PICACOIN_QT_PICACOINADDRESSVALIDATOR_H
