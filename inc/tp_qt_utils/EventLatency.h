#ifndef tp_qt_utils_EventLatency_h
#define tp_qt_utils_EventLatency_h

#include "tp_qt_utils/Globals.h"

#include <QObject>
#include <QEvent>

#include <unordered_map>

namespace tp_qt_utils
{

//##################################################################################################
//! Times the processing latency of the event queue.
class TP_QT_UTILS_SHARED_EXPORT EventLatency: public QObject
{
  Q_OBJECT
public:
  //################################################################################################
  EventLatency(const std::string& name);

  //################################################################################################
  ~EventLatency() override;

  //################################################################################################
  static std::unordered_map<std::string, int> results();

  //################################################################################################
  static std::string takeResults();

  //################################################################################################
  static std::map<std::string, size_t> keyValueResults();

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
