#ifndef tp_qt_utils_Globals_h
#define tp_qt_utils_Globals_h

#include "tp_utils/StringID.h"
#include "tp_utils/CallbackCollection.h"

#if defined(TP_QT_UTILS_LIBRARY)
#  define TP_QT_UTILS_SHARED_EXPORT TP_EXPORT
#else
#  define TP_QT_UTILS_SHARED_EXPORT TP_IMPORT
#endif

#include <QStringList>
#include <QDebug>
#include <QObject>

#include <QtCore/qglobal.h>

#include <ostream>

//##################################################################################################
//! Qt classes used throughout the rest of tp Toolkit.
/*!
This module provides a set of general purpose classes that form the core of tp Toolkit.
*/
namespace tp_qt_utils
{
TP_DECLARE_ID(     dictionarySID,       "Dictionary");

//##################################################################################################
QStringList convertStringList(const std::vector<std::string>& src);

//##################################################################################################
template<typename T>
class QObjectCallback;

//##################################################################################################
template<typename R, typename... Args>
class QObjectCallback<R(Args...)> : public QObject, public tp_utils::Callback<R(Args...)>
{
  public:
  //################################################################################################
  QObjectCallback() = delete;

  //################################################################################################
  template<typename F>
  QObjectCallback(QObject* parent,
                  tp_utils::CallbackCollection<R(Args...)>& collection,
                  const F& callback):
    QObject(parent),
    tp_utils::Callback<R(Args...)>(callback)
  {
    tp_utils::Callback<R(Args...)>::connect(collection);
  }
};

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

#if QT_VERSION < 0x060000
inline std::ostream& operator<<(std::ostream& os, const QList<V>& v){return detail::print(os, v);}
#endif

inline std::ostream& operator<<(std::ostream& os, const QString& v){return detail::print(os, v);}
inline std::ostream& operator<<(std::ostream& os, const QByteArray& v){return detail::print(os, v);}

#endif
