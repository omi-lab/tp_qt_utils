#ifndef tdp_qt_utils_BinaryUtils_h
#define tdp_qt_utils_BinaryUtils_h

#include "tdp_qt_utils/Globals.h"

class QByteArray;
class QString;

namespace tdp_qt_utils
{
//##################################################################################################
//! Converts binary data into a format that prints nicely.
/*!
This will replace all non printable characters with spaces and then return the results along with
the original size, the number of characters that are printed can be limited with maxLen.

\param data - The source data.
\param maxLen - The maximum number of characters.

\returns - A printable version of the data surrounded by brackets and prefixed with its length.
*/
QString TDP_QT_UTILS_SHARED_EXPORT binaryDebug(const QByteArray& data, int maxLen = 30);

//##################################################################################################
QString TDP_QT_UTILS_SHARED_EXPORT binaryNumericDebug(const QByteArray& data, int maxLen = 30);

//##################################################################################################
QString TDP_QT_UTILS_SHARED_EXPORT summaryBinaryDebug(const QByteArray& data);

//##################################################################################################
QByteArray TDP_QT_UTILS_SHARED_EXPORT replaceTokens(const QByteArray& data, const QMap<QByteArray, QByteArray>& tokens, char start='$', char end='$');

}

#endif
