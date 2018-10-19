#ifndef tdp_qt_utils_Globals_h
#define tdp_qt_utils_Globals_h

#include "tp_utils/StringID.h"

#if defined(TDP_QT_UTILS_LIBRARY)
#  define TDP_QT_UTILS_SHARED_EXPORT TP_EXPORT
#else
#  define TDP_QT_UTILS_SHARED_EXPORT TP_IMPORT
#endif

#include <QStringList>
#include <QDebug>

#include <QtCore/qglobal.h>

#include <ostream>

//##################################################################################################
//! Qt classes used throughout the rest of Tdp Toolkit.
/*!
This module provides a set of general purpose classes that form the core of Tdp Toolkit.
*/
namespace tdp_qt_utils
{
TDP_DECLARE_ID(     dictionarySID,       "Dictionary")

//##################################################################################################
QStringList convertStringList(const std::vector<std::string>& src);

}

//##################################################################################################
namespace detail
{
template<typename T>
std::ostream& print(std::ostream& os, const T& v)
{
  QString str;
  {
    QDebug{&str} << v;
  }

  os << str.toStdString();

  return os;
}
}

template <typename K, typename V>
inline std::ostream& operator<<(std::ostream& os, const QMap<K,V>& v){return detail::print(os, v);}
template <typename V>
inline std::ostream& operator<<(std::ostream& os, const QVector<V>& v){return detail::print(os, v);}
template <typename V>
inline std::ostream& operator<<(std::ostream& os, const QList<V>& v){return detail::print(os, v);}
inline std::ostream& operator<<(std::ostream& os, const QString& v){return detail::print(os, v);}
inline std::ostream& operator<<(std::ostream& os, const QByteArray& v){return detail::print(os, v);}

#endif
