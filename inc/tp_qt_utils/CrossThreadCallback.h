#ifndef tp_qt_utils_CrossThreadCallback_h
#define tp_qt_utils_CrossThreadCallback_h

#include "tp_utils/AbstractCrossThreadCallback.h"

#include "tp_qt_utils/Globals.h"

#include <functional>

namespace tp_qt_utils
{

//##################################################################################################
//! A class for calling a callback from a different thread
/*!
This class can be used to call a callback in another thread. Simply construct an instance of the
class in the thread that should receive the callback, then call the call() method from any other
thread.

An event will be sent to the receiving thread that causes the callback to be called.

\warning This requires that the receiving thread has an event loop.
*/
class TP_QT_UTILS_SHARED_EXPORT CrossThreadCallback : public tp_utils::AbstractCrossThreadCallback
{
public:
  //################################################################################################
  /*!
  \param callback The callback that will be called in this thread.
  \param delay If this is zero or positive a timer will be used to collate calls.
  */
  CrossThreadCallback(const std::function<void()>& callback, int delay);

  //################################################################################################
  CrossThreadCallback(const std::function<void()>& callback);

  //################################################################################################
  ~CrossThreadCallback() override;

  //################################################################################################
  void call() override;

private:
  struct Private;
  friend struct Private;
  Private* d;
};

//##################################################################################################
using CrossThreadCallbackFactory = tp_utils::CrossThreadCallbackFactoryTemplate<CrossThreadCallback>;

}

#endif
