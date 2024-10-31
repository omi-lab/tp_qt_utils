#include "tp_qt_utils/TPQSettings.h"

#include <QSettings>

namespace tp_qt_utils
{

//##################################################################################################
struct TPQSettings::Private
{
  QSettings settings;
};

//##################################################################################################
TPQSettings::TPQSettings():
  d(new Private())
{

}

//##################################################################################################
TPQSettings::~TPQSettings()
{
  delete d;
}

//##################################################################################################
std::string TPQSettings::value(const std::string& key)
{
  return d->settings.value(QString::fromStdString(key)).toString().toStdString();
}

//##################################################################################################
void TPQSettings::setValue(const std::string& key, const std::string& value)
{
  d->settings.setValue(QString::fromStdString(key), QString::fromStdString(value));
}

//##################################################################################################
std::vector<std::string> TPQSettings::keys()
{
  std::vector<std::string> keys;

  QStringList allKeys = d->settings.allKeys();
  keys.reserve(size_t(allKeys.size()));
  for(const auto& key : allKeys)
    keys.push_back(key.toStdString());

  return keys;
}
}
