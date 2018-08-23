#ifndef tdp_qt_utils_Globals_h
#define tdp_qt_utils_Globals_h

#include "tp_utils/StringID.h"

#include <QStringList>

#include <QtCore/qglobal.h>

#ifndef TDP_QT_UTILS_SHARED_EXPORT
#if defined(TDP_QT_UTILS_LIBRARY)
#  define TDP_QT_UTILS_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define TDP_QT_UTILS_SHARED_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef TDP_CPP_VERSION
#define TDP_CPP_VERSION 11
#endif

//##################################################################################################
//TDP_NODISCARD
#define TDP_NODISCARD __attribute__((warn_unused_result))

//##################################################################################################
//TDP_DEPRECATED
#if TDP_CPP_VERSION>=14
#define TDP_DEPRECATED(typ, func) [[deprecated]] typ func
#else
#ifdef __GNUC__
#define TDP_DEPRECATED(typ, func) typ func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define TDP_DEPRECATED(typ, func) typ __declspec(deprecated) func
#else
#define TDP_DEPRECATED(typ, func) typ func
#endif
#endif

//##################################################################################################
//TDP_FALLTHROUGH
#if TDP_CPP_VERSION>=17
#  define TDP_FALLTHROUGH [[fallthrough]]
#elif __GNUC__>=7
#  define TDP_FALLTHROUGH [[gnu::fallthrough]]
#elif defined __CLANG__
#  define TDP_FALLTHROUGH [[clang::fallthrough]]
#else
#  define TDP_FALLTHROUGH
#endif

//##################################################################################################
//TDP_SIZEOF
template<int s> struct __TDP_SIZEOF;
//! Use this to show the size of objects at compile time, will fail at the line it is used.
#define TDP_SIZEOF(o)__TDP_SIZEOF<sizeof(o)> __tdp_sizeof;

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

#endif
