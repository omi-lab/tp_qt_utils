#ifndef tdp_qt_utils_EventLatency_h
#define tdp_qt_utils_EventLatency_h

#include "tdp_qt_utils/Globals.h"

#include <QObject>
#include <QEvent>

namespace tdp_qt_utils
{

//##################################################################################################
//! Times the processing latency of the event queue.
class TDP_QT_UTILS_SHARED_EXPORT EventLatency: public QObject
{
public:
  //################################################################################################
  EventLatency(const std::string& name);

  //################################################################################################
  ~EventLatency() override;

  //################################################################################################
  static std::unordered_map<std::string, int> results();

  //################################################################################################
  static std::string takeResults();

protected:
  //################################################################################################
  void timerEvent(QTimerEvent *event) override;

  //################################################################################################
  void customEvent(QEvent *event) override;

private:
  struct Private;
  friend struct Private;
  Private* d;
};

}

#endif
