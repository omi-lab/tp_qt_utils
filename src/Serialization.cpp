#include "tdp_qt_utils/Serialization.h"

#include "tp_utils/DebugUtils.h"

namespace tdp_qt_utils_private
{
////##################################################################################################
//DataStream_lt::DataStream_lt(QByteArray* byteArray, QIODevice::OpenMode flags, tp_utils::StringIDManager* manager):
//  QDataStream(byteArray, flags),
//  m_manager(manager)
//{
//  lock();
//  instances().insert(this);
//  unlock();
//}

////##################################################################################################
//DataStream_lt::~DataStream_lt()
//{
//  lock();
//  instances().remove(this);
//  unlock();
//}

////##################################################################################################
//DataStream_lt* DataStream_lt::cast(QDataStream* dataStream)
//{
//  DataStream_lt* result = static_cast<DataStream_lt*>(dataStream);
//  bool instancesContains;

//  lock();
//  instancesContains = instances().contains(result);
//  unlock();

//  return instancesContains ? result : nullptr;
//}

////##################################################################################################
//void DataStream_lt::lock()
//{
//  instancesMutex().lock();
//}

////##################################################################################################
//void DataStream_lt::unlock()
//{
//  instancesMutex().unlock();
//}

////##################################################################################################
//QSet<DataStream_lt*>& DataStream_lt::instances()
//{
//  static QSet<DataStream_lt*> instances;
//  return instances;
//}

////##################################################################################################
//TPMutex& DataStream_lt::instancesMutex()
//{
//  static TPMutex instancesMutex(TPMutex::Recursive);
//  return instancesMutex;
//}
}

////##################################################################################################
//QDataStream& operator<<(QDataStream& dataStream_, const tp_utils::StringID& stringID)
//{
//  tdp_qt_utils_private::DataStream_lt* dataStream = tdp_qt_utils_private::DataStream_lt::cast(&dataStream_);
//  Q_ASSERT(dataStream);
//
//  dataStream_ << int64_t(stringID.key(dataStream->m_manager));
//
//  return dataStream_;
//}
//
////##################################################################################################
//QDataStream& operator>>(QDataStream& dataStream_, tp_utils::StringID& stringID)
//{
//  int64_t id;
//
//  tdp_qt_utils_private::DataStream_lt* dataStream = tdp_qt_utils_private::DataStream_lt::cast(&dataStream_);
//  Q_ASSERT(dataStream);
//
//  dataStream_ >> id;
//
//  stringID = tp_utils::StringID(dataStream->m_manager, id);
//
//  return dataStream_;
//}

namespace tdp_qt_utils
{

//##################################################################################################
void registerMetaTypes()
{
  registerType<QByteArrayList>          ("QByteArrayList"         );
  registerType<Int64StringHash>         ("Int64StringHash"         );
  registerType<Int64Int64Hash>          ("Int64Int64Hash"          );
  registerType<Int64List>               ("Int64List"               );
  registerType<IntList>                 ("IntList"                 );
  //registerType<StringIDVariantHash>     ("StringIDVariantHash"     );
  //registerType<StringIDStringHash>      ("StringIDStringHash"      );
  registerType<IntList>                 ("IntList"                 );
  //registerType<tp_utils::StringID>      ("StringID"                );
  //registerType<StringIDVariantPair>     ("StringIDVariantPair"     );
  registerType<QStringQVariantPair>     ("QStringQVariantPair"     );
  registerType<QStringQVariantPairsList>("QStringQVariantPairsList");
  //registerType<StringIDStringHashList>  ("StringIDStringHashList"  );
  registerType<QStringListList>         ("QStringListList"         );
  registerType<FloatVectorList>         ("FloatVectorList"         );
  registerType<UInt8VectorList>         ("UInt8VectorList"         );
}

//##################################################################################################
QByteArray escape(const QByteArray& input)
{
  //Calculate the destination size
  int destinationSize = 0;
  {
    const char* i = input.constData();
    const char* iMax = i + input.size();

    while(i<iMax)
    {
      switch(*i)
      {
      case '*':
      case '#':
      case '@':
        destinationSize+=2;
        break;
      default:
        destinationSize++;
        break;
      }
      i++;
    }
  }

  QByteArray output(destinationSize, Qt::Initialization::Uninitialized);
  {
    const char* i = input.constData();
    const char* iMax = i + input.size();

    char* o = output.data();

    while(i<iMax)
    {
      if((*i)=='*')
      {
        (*o)='*';
        o++;
        (*o)='0';
      }
      else if((*i)=='#')
      {
        (*o)='*';
        o++;
        (*o)='1';
      }
      else if((*i)=='@')
      {
        (*o)='*';
        o++;
        (*o)='2';
      }
      else
        (*o)=(*i);

      o++;
      i++;
    }
  }

  return output;
}

//##################################################################################################
QByteArray unescape(const QByteArray& input)
{
  QByteArray output(input.size(), Qt::Initialization::Uninitialized);

  const char* i = input.constData();
  char* o = output.data();

  const char* iMax = i + input.size();

  while(i<iMax)
  {
    if((*i)=='*')
    {
      i++;
      if((*i)=='0')
        (*o)='*';
      else if((*i)=='1')
        (*o)='#';
      else
        (*o)='@';
    }
    else
      (*o)=(*i);

    o++;
    i++;
  }

  return output.left(int(o-output.constData()));
}

//##################################################################################################
QByteArray escapePacket(const SerialMessage& message)
{
  QByteArray data;
  data.append('@');
  data.append(message.command);
  data.append(escape(message.data));
  data.append('#');
  return data;
}

//##################################################################################################
PartialPacket::PartialPacket(int bufferSize):
  m_bufferSize(bufferSize),
  m_commandBuffer(new char[bufferSize])
{

}

//##################################################################################################
PartialPacket::~PartialPacket()
{
  delete[] m_commandBuffer;
}

//##################################################################################################
void PartialPacket::addData(const QByteArray& input)
{
  const char* c = input.constData();
  const char* cMax = c+input.size();

  for(; c<cMax; c++)
  {
    int_fast8_t character = *c;
    if(!m_gotStart)
    {
      if(character == '@')
        m_gotStart = true;
    }
    else
    {
      if(character == '#')
      {
        //We should now have a complete message
        if(m_index>=1)
        {
          char command = m_commandBuffer[0];
          QByteArray data = unescape(QByteArray::fromRawData(m_commandBuffer+1, int(m_index-1)));

          m_messages.append(SerialMessage(command, data));
        }
        m_index = 0;
        m_gotStart = false;
      }
      else
      {
        if(m_index>=m_bufferSize)
        {
          tpWarning() << "Warning! PartialPacket::addChar() Overflow!";
          m_index = 0;
          m_gotStart = false;
        }
        else
        {
          m_commandBuffer[m_index] = character;
          m_index++;
        }
      }
    }
  }
}

//##################################################################################################
bool PartialPacket::hasMessage()const
{
  return !m_messages.isEmpty();
}

//##################################################################################################
QList<SerialMessage> PartialPacket::takeMessages()
{
  QList<SerialMessage> messages = m_messages;
  m_messages.clear();
  return messages;
}

}
