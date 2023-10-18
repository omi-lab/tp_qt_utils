#ifndef tp_qt_utils_Throttler_h
#define tp_qt_utils_Throttler_h

#include "tp_qt_utils/Globals.h"

namespace tp_qt_utils
{

//##################################################################################################
class TP_QT_UTILS_SHARED_EXPORT Throttler
{
public:
  //################################################################################################
  Throttler(const std::function<void()>& callback);

  //################################################################################################
  ~Throttler();

  //################################################################################################
  void start();

  //################################################################################################
  void stop();

  //################################################################################################
  bool shouldYield() const;

private:
  struct SharedData;
  friend struct SharedData;
  static SharedData& instance();
  const std::function<void()> m_callback;
};
    
}
    
#endif
