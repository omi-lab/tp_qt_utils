#ifndef tp_qt_utils_TPFileSettings_h
#define tp_qt_utils_TPFileSettings_h

#include "tp_utils/TPSettings.h"

namespace tp_qt_utils
{

//##################################################################################################
class TPFileSettings final : public tp_utils::SettingsStore
{
  TP_DQ;
public:
  //################################################################################################
  TPFileSettings();

  //################################################################################################
  ~TPFileSettings() override;

  //################################################################################################
  std::string value(const std::string& key) override;

  //################################################################################################
  void setValue(const std::string& key, const std::string& value) override;

  //################################################################################################
  std::vector<std::string> keys() override;
};
}

#endif
