#ifndef tp_qt_utils_FormatNumbers_h
#define tp_qt_utils_FormatNumbers_h

#include "tp_qt_utils/Globals.h"

namespace tp_qt_utils
{

//##################################################################################################
QByteArray padLeft(QByteArray arg, int width);

//##################################################################################################
QString padLeft(QString arg, int width);

//##################################################################################################
//! Format a number as B, kB, MB, ...
QByteArray formatSizeBytes(int64_t size, bool alignRight=true);

//##################################################################################################
//! Format a number as B, KiB, MiB, ...
QByteArray formatSizeBinaryBytes(int64_t size, bool alignRight=true);

}

#endif
