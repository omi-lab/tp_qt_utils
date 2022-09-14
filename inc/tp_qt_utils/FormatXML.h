#ifndef tp_qt_utils_FormatXML_h
#define tp_qt_utils_FormatXML_h

#include "tp_qt_utils/Globals.h" // IWYU pragma: keep

namespace tp_qt_utils
{

//##################################################################################################
//! Prettify an XML string
QByteArray formatXML(const QByteArray& xml);

}

#endif
