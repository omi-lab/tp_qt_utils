#ifndef tdp_qt_utils_CrossThreadCallback_h
#define tdp_qt_utils_CrossThreadCallback_h

#include "tdp_qt_utils/Globals.h"

#include <functional>

namespace tdp_qt_utils
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
class TDP_QT_UTILS_SHARED_EXPORT CrossThreadCallback
{
  struct Private;
  Private* d;
public:
  //################################################################################################
  CrossThreadCallback(const std::function<void()>& callback);

  //################################################################################################
  ~CrossThreadCallback();

  //################################################################################################
  void call();

  //################################################################################################
  const std::function<void()>* callFunctor();
};

}

#endif
