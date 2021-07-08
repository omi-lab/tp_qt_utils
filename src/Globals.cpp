#include "tp_qt_utils/Globals.h"

namespace tp_qt_utils
{
TP_DEFINE_ID(     dictionarySID,       "Dictionary");

//##################################################################################################
QStringList convertStringList(const std::vector<std::string>& src)
{
  QStringList dst;
  dst.reserve(src.size());
  for(const auto& i : src)
    dst.push_back(QString::fromStdString(i));
  return dst;
}

}
