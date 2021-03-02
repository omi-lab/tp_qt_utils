#include "tp_qt_utils/BinaryUtils.h"

#include <QByteArray>
#include <QString>
#include <QMap>

namespace tp_qt_utils
{

//##################################################################################################
QString binaryDebug(const QByteArray& data, size_t maxLen)
{
  const char* c = data.constData();

  int iMax = tpMin(size_t(data.size()), maxLen);

  QString result;
  result.reserve(iMax+32);

  for(int i=0; i<iMax; i++)
  {
    if(*c>=32 && *c<=126)
      result.append(*c);
    else
      result.append(' ');

    c++;
  }

  result.prepend(QString("(%1, \"").arg(data.size()));
  result.append("\")");

  return result;
}

//##################################################################################################
QString binaryNumericDebug(const QByteArray& data, size_t maxLen)
{
  const auto* c = reinterpret_cast<const uint8_t*>(data.constData());

  int iMax = tpMin(size_t(data.size()), maxLen);

  QString result;
  result.reserve(iMax+32);

  for(int i=0; i<iMax; i++)
  {
    result.append(QString::number(*c));
    result.append(' ');
    c++;
  }

  return result;
}

namespace
{
char cleanChar(char ch)
{
  return (ch>=' ' && ch<='~')?ch:'_';
}
}

//##################################################################################################
QString summaryBinaryDebug(const QByteArray& data)
{
  QString result = QString::number(data.size());

  result += " (";

  int iMax = data.size();
  if(iMax<30)
    for(int i=0; i<iMax; i++)
      result.append(cleanChar(data.at(i)));
  else
  {
    for(int i=0; i<10; i++)
      result.append(cleanChar(data.at(i)));

    result += " ~~~ ";

    for(int i=iMax-11; i<iMax; i++)
      result.append(cleanChar(data.at(i)));
  }

  result += ")";

  return result;
}


//##################################################################################################
QByteArray replaceTokens(const QByteArray& data, const QMap<QByteArray, QByteArray>& tokens, char start, char end)
{
  QByteArray result;
  result.reserve(data.size());

  const char* tokenStart = nullptr;
  int tokenLen = 0;

  const char* d = data.constData();
  const char* dMax = d+(data.size());
  for(; d<dMax; d++)
  {
    char dc = (*d);

    if(!tokenStart)
    {
      if(dc == start)
        tokenStart = d+1;
      else
        result.append(dc);
    }
    else
    {
      if(dc == end)
      {
        if(tokenLen==0)result.append(start);
        else           result.append(tokens.value(QByteArray(tokenStart, tokenLen)));
        tokenStart = nullptr;
        tokenLen = 0;
      }
      else
        tokenLen++;
    }
  }

  return result;
}

}
