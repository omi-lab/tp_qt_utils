#ifndef tp_qt_utils_Thread_h
#define tp_qt_utils_Thread_h

#include "tp_qt_utils/Globals.h"

#include <QObject>
#include <QThread>

namespace tp_qt_utils
{

//##################################################################################################
// Auto-start and auto-destruct thread class, designed to be stored in a QPointer, not a std pointer
// because of auto-destruct functionality.
class TP_QT_UTILS_SHARED_EXPORT Thread: public QThread
{
  Q_OBJECT

public:
  //################################################################################################
  Thread();

private:
};

}
    
#endif
