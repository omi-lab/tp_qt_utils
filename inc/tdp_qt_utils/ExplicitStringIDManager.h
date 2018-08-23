#ifndef tdp_qt_utils_ExplicitStringIDManager_h
#define tdp_qt_utils_ExplicitStringIDManager_h

#include "tdp_qt_utils/Globals.h"
#include "tp_utils/StringIDManager.h"

#include <QString>
#include <QPair>

namespace tdp_qt_utils
{

class TDP_QT_UTILS_SHARED_EXPORT ExplicitStringIDManager: public tp_utils::StringIDManager
{
public:
  //################################################################################################
  ExplicitStringIDManager();

  //################################################################################################
  virtual ~ExplicitStringIDManager();

  //################################################################################################
  void addKeys(const QList<QPair<std::string, int64_t> >& sids);

  //################################################################################################
  int64_t key(const std::string& keyString) override;

  //################################################################################################
  std::string keyString(int64_t key) override;

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
