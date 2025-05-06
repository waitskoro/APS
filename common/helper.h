#pragma once

#include <QString>
#include <QDateTime>

namespace {

int fromStrToInt(QString str)
{
    bool ok;
    int num = str.toInt(&ok);
    if (ok)
        return num;

    return -1;
}

double fromDateToDouble(QDateTime date)
{
    return double(date.toSecsSinceEpoch()) / double (86400) + 25569;
}

}
