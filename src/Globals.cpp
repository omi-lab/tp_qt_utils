#include "tdp_qt_utils/Globals.h"

namespace tdp_qt_utils
{
TDP_DEFINE_ID(     dictionarySID,       "Dictionary");

//##################################################################################################
QStringList convertStringList(const std::vector<std::string>& src)
{
  QStringList dst;
  for(const auto& i : src)
    dst.push_back(QString::fromStdString(i));
  return dst;
}
}
