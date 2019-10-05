#include "tp_qt_utils/FormatNumbers.h"

#include <QByteArray>
#include <QString>
#include <QList>

namespace tp_qt_utils
{

//##################################################################################################
QByteArray padLeft(QByteArray arg, int width)
{
  while(arg.size()<width)arg.prepend(' ');
  return arg;
}

//##################################################################################################
QString padLeft(QString arg, int width)
{
  while(arg.size()<width)arg.prepend(' ');
  return arg;
}

//##################################################################################################
QByteArray formatSizeBytes(int64_t size, bool alignRight)
{
  static const QList<const char*> suffixes={"  B", " kB", " MB", " GB", " TB", " PB", " EB", " ZB", " YB"};

  int i=0;
  while(abs(size)>4000 && i<suffixes.size()-1)
  {
    i++;
    size = size / 1000;
  }

  QByteArray result = QByteArray::number(qint64(size))+suffixes.at(i);
  return (alignRight)?padLeft(result, 8):result;
}

//##################################################################################################
QByteArray formatSizeBinaryBytes(int64_t size, bool alignRight)
{
  static const QList<const char*> suffixes={"   B", " KiB", " MiB", " GiB", " TiB", " PiB", " EiB", " ZiB", " YiB"};

  int i=0;
  while(abs(size)>4096 && i<suffixes.size()-1)
  {
    i++;
    size = size / 1024;
  }

  QByteArray result = QByteArray::number(qint64(size))+suffixes.at(i);
  return (alignRight)?padLeft(result, 8):result;
}

}
