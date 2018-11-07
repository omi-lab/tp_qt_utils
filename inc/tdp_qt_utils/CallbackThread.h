#ifndef tdp_qt_utils_CallbackThread_h
#define tdp_qt_utils_CallbackThread_h

#include "tdp_qt_utils/Globals.h"

#include <QThread>

#include <functional>
#include <atomic>

namespace tdp_qt_utils
{
//##################################################################################################
//! A class to run a task in a separate thread.
/*!
The purpose of this class is to execute a function, specified in the class constructor, in a
separate thread. Once the function exits, the thread will end execution.
*/
class TDP_QT_UTILS_SHARED_EXPORT CallbackThread: public QThread
{
  std::atomic_bool m_finish{false};
  std::function<void(const std::atomic_bool&)> m_callback;

public:
  //################################################################################################
  //! Constructor
  /*!
  \param opaque - pointer to supply to the \p callback function
  \param callback - function for the thread to perform
  \param name - the thread name
  */
  CallbackThread(std::function<void(const std::atomic_bool&)> callback, const char* name);

  //################################################################################################
  ~CallbackThread() override;

  //################################################################################################
  //! Provide access to QThread::exec()
  int exec();

protected:
  //################################################################################################
  //! Execute the callback function.
  /*!
  Call start() to create the thread and execute the run() function.
  */
  void run()override;
};

}

#endif
