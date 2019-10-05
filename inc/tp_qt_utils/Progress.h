#ifndef tp_qt_utils_Progress_h
#define tp_qt_utils_Progress_h

#include "tp_qt_utils/Globals.h"

#include <QObject>

namespace tp_qt_utils
{

//##################################################################################################
//! A class for logging error messages
/*!

*/
class tp_qt_UTILS_SHARED_EXPORT Progress: public QObject
{
  Q_OBJECT
public:
  //################################################################################################
  Progress(QObject* parent=nullptr);

  //################################################################################################
  virtual ~Progress();

  //################################################################################################
  //! Set the progress
  /*!
  \param percent - A value between 0 and 100
  */
  void setProgress(float percent);

  //################################################################################################
  //! Set the progress and the description of what is being processes
  /*!
  \param percent - A value between 0 and 100
  */
  void setProgress(float percent, const QString& description);

  //################################################################################################
  //! Returns the current progress
  float progress()const;

  //################################################################################################
  //! Sets the description of the task that is being performed
  /*!
  This should be updated to describe what is happening at each stage of a process, this should be a
  short string that will be hisplayed to the user.

  \param description - The new description
  */
  void setDescription(const QString& description);

  //################################################################################################
  //! Returns the descripton of the current stage of the task.
  QString description()const;

  //################################################################################################
  //! Returs true if this task should stop
  bool shouldStop()const;

  //################################################################################################
  //! Use this to stop the task
  void stop(bool shouldStop);

signals:
  //################################################################################################
  void changed();

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
