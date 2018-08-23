#ifndef tdp_qt_utils_EventDebug_h
#define tdp_qt_utils_EventDebug_h

#include "tdp_qt_utils/Globals.h"

#include <QObject>
#include <QEvent>

namespace tdp_qt_utils
{

//##################################################################################################
//! A class that prents out all of the events that pass through Qt
/*!

*/
class TDP_QT_UTILS_SHARED_EXPORT EventDebug: public QObject
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
