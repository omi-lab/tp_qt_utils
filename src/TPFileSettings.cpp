#include "tp_qt_utils/TPFileSettings.h"

#include "tp_utils/FileUtils.h"

#include <QSettings>
#include <QStandardPaths>

namespace tp_qt_utils
{

//##################################################################################################
struct TPFileSettings::Private
{
  std::string rootPath{tp_utils::pathAppend(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString(), "settings")};

  //################################################################################################
  Private()
  {
    if(!tp_utils::exists(rootPath))
    {
      tp_utils::mkdir(rootPath, TPCreateFullPath::Yes);
      initFromQSettiongs();
    }
  }

  //################################################################################################
  std::string path(const std::string& key)
  {
    return tp_utils::pathAppend(rootPath, key + ".dat");
  }

  //################################################################################################
  void write(const std::string& key, const std::string& value)
  {
    tp_utils::writeBinaryFile(path(key), value);
  }

  //################################################################################################
  void initFromQSettiongs()
  {
    QSettings settings;
    for(const auto& key : settings.allKeys())
      write(key.toStdString(), settings.value(key).toString().toStdString());
  }
};

//##################################################################################################
TPFileSettings::TPFileSettings():
  d(new Private())
{

}

//##################################################################################################
TPFileSettings::~TPFileSettings()
{
  delete d;
}

//##################################################################################################
std::string TPFileSettings::value(const std::string& key)
{
  return tp_utils::readBinaryFile(d->path(key));
}

//##################################################################################################
void TPFileSettings::setValue(const std::string& key, const std::string& value)
{
  d->write(key, value);
}

//##################################################################################################
std::vector<std::string> TPFileSettings::keys()
{
  std::vector<std::string> keys = tp_utils::listFiles(d->rootPath, {"*.dat"});

  for(auto& key : keys)
  {
    key = tp_utils::filename(key);
    if(key.size()>4)
      key.resize(key.size()-4);
  }

  return keys;
}
}
