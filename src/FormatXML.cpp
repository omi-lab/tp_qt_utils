#include "tp_qt_utils/FormatXML.h"

#include <QByteArray>

namespace tp_qt_utils
{

//##################################################################################################
QByteArray formatXML(const QByteArray& xml)
{
  int indentation=0;
  bool indent=false;
  bool moreThan=true;
  bool closed=false;

  QByteArray result;

  const char* data = xml.constData();
  const char* dataMax = data + xml.size();

  for(; data<dataMax; data++)
  {
    if(!moreThan && (*data)=='<')
    {
      moreThan=true;

      if(closed)
        indent=true;

      if((dataMax-data)>1 && (*(data+1))=='/')
      {
        indentation=tpMax(indentation-1, 0);
        closed=true;
      }
      else
        closed = false;

      if(!closed)
        indent=true;
    }

    if(moreThan && (*data)=='>')
    {
      moreThan=false;

      if(!closed)
        indentation++;

      if((dataMax-data)>2 && (*(data+1))=='<' && (*(data+2))!='/')
        indent=true;
    }
    else if(indent)
    {
      indent=false;
      result+='\n';

      for(int i=indentation*4; i>0; i--)
        result+=' ';

      if((dataMax-data)>1 && (*(data+1))=='<' && (*(data+1))=='/')
        indentation++;
    }
    result+=(*data);
  }

  return result;
}

}
