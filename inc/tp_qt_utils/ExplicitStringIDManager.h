#ifndef tp_qt_utils_ExplicitStringIDManager_h
#define tp_qt_utils_ExplicitStringIDManager_h

#include "tp_qt_utils/Globals.h"
#include "tp_utils/StringIDManager.h"

#include <QString>
#include <QPair>

namespace tp_qt_utils
{

class TP_QT_UTILS_SHARED_EXPORT ExplicitStringIDManager: public tp_utils::StringIDManager
{
public:
  //################################################################################################
  ExplicitStringIDManager();

  //################################################################################################
  virtual ~ExplicitStringIDManager();

  //################################################################################################
  void addKeys(const QList<QPair<std::string, int64_t> >& sids);

  //################################################################################################
  int64_t key(const std::string& toString) override;

  //################################################################################################
  std::string toString(int64_t key) override;

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
