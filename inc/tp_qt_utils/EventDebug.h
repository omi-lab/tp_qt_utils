#ifndef tp_qt_utils_EventDebug_h
#define tp_qt_utils_EventDebug_h

#include "tp_qt_utils/Globals.h"

#include <QObject>
#include <QEvent>

namespace tp_qt_utils
{

//##################################################################################################
//! A class that prents out all of the events that pass through Qt
/*!

*/
class tp_qt_UTILS_SHARED_EXPORT EventDebug: public QObject
{
public:
  //################################################################################################
  EventDebug(QObject* watched);

  //################################################################################################
  static std::string eventTypeString(QEvent::Type type);

protected:
  //################################################################################################
  virtual bool eventFilter(QObject* watched, QEvent* event);
};

}

#endif
