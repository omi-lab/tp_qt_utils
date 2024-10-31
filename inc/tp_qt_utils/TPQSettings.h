#ifndef tp_qt_utils_TPQSettings_h
#define tp_qt_utils_TPQSettings_h

#include "tp_utils/TPSettings.h"

namespace tp_qt_utils
{

//##################################################################################################
class TPQSettings final : public tp_utils::SettingsStore
{
  TP_DQ;
public:
  //################################################################################################
  TPQSettings();

  //################################################################################################
  ~TPQSettings() override;

  //################################################################################################
  std::string value(const std::string& key) override;

  //################################################################################################
  void setValue(const std::string& key, const std::string& value) override;

  //################################################################################################
  std::vector<std::string> keys() override;
};
}

#endif
