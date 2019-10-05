#ifndef tp_qt_utils_Serialization_h
#define tp_qt_utils_Serialization_h

#include "tp_qt_utils/Globals.h"
#include "tp_qt_utils/SerialMessage.h"

#include "tp_utils/StringID.h"
#include "tp_utils/StringIDManager.h"
#include "tp_utils/MutexUtils.h"

#include <QByteArray>
#include <QVariant>
#include <QDataStream>
#include <QMetaType>
#include <QHash>
#include <QList>
#include <QSet>

#include <vector>
#include <stdint.h>

namespace tp_qt_utils_private
{
////##################################################################################################
//class TP_QT_UTILS_SHARED_EXPORT DataStream_lt: public QDataStream
//{
//public:
//  DataStream_lt(QByteArray* byteArray, QIODevice::OpenMode flags, tp_utils::StringIDManager* manager);
//  ~DataStream_lt();
//  static DataStream_lt* cast(QDataStream* dataStream);
//
//  tp_utils::StringIDManager* m_manager;
//
//  static void lock();
//  static void unlock();
//private:
//  static QSet<DataStream_lt*>& instances();
//  static TPMutex& instancesMutex();
//};
}

//##################################################################################################
typedef QHash<qint64, QString> Int64StringHash;
typedef QHash<qint64, qint64> Int64Int64Hash;
typedef QList<qint64> Int64List;
typedef QList<int> IntList;
typedef QHash<tp_utils::StringID, QVariant> StringIDVariantHash;
typedef QHash<tp_utils::StringID, QString> StringIDStringHash;
typedef QPair<tp_utils::StringID, QVariant> StringIDVariantPair;
typedef QPair<QString, QVariant> QStringQVariantPair;
typedef QList<QStringQVariantPair> QStringQVariantPairsList;
typedef QList<QHash<tp_utils::StringID, QString> > StringIDStringHashList;
typedef QList<QStringList> QStringListList;
typedef QList<QVector<float>> FloatVectorList;
typedef QList<QVector<uint8_t>> UInt8VectorList;

//##################################################################################################
Q_DECLARE_METATYPE(Int64StringHash)
Q_DECLARE_METATYPE(Int64Int64Hash)
Q_DECLARE_METATYPE(Int64List)
Q_DECLARE_METATYPE(IntList)
Q_DECLARE_METATYPE(StringIDVariantHash)
Q_DECLARE_METATYPE(StringIDStringHash)
Q_DECLARE_METATYPE(StringIDVariantPair)
Q_DECLARE_METATYPE(QStringQVariantPair)
Q_DECLARE_METATYPE(QStringQVariantPairsList)
Q_DECLARE_METATYPE(StringIDStringHashList)
Q_DECLARE_METATYPE(QStringListList)
Q_DECLARE_METATYPE(FloatVectorList)
Q_DECLARE_METATYPE(UInt8VectorList)

////##################################################################################################
//QDataStream TP_QT_UTILS_SHARED_EXPORT & operator<<(QDataStream& dataStream_, const tp_utils::StringID& stringID);
//
////##################################################################################################
//QDataStream TP_QT_UTILS_SHARED_EXPORT & operator>>(QDataStream& dataStream_, tp_utils::StringID& stringID);

namespace tp_qt_utils
{
////! A guide to serializing data into byte arrays.
///*!
//\defgroup Serialization

//This page describes how serialization should be performed.
//*/

//##################################################################################################
template<typename T>
void registerType(const char * typeName)
{
  qRegisterMetaType<T>(typeName);
  qRegisterMetaTypeStreamOperators<T>(typeName);
}

//##################################################################################################
void TP_QT_UTILS_SHARED_EXPORT registerMetaTypes();

////##################################################################################################
//template<class T>
//QByteArray  serialize(tp_utils::StringIDManager* manager, const T& data)
//{
//  QByteArray byteArray;
//
//  {
//    tp_qt_utils_private::DataStream_lt dataStream(&byteArray, QIODevice::WriteOnly, manager);
//    dataStream << data;
//  }
//
//  return byteArray;
//}

////##################################################################################################
//template<class T>
//QByteArray  serialize(const T& data)
//{
//  QByteArray byteArray;
//  {
//    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
//    dataStream << data;
//  }
//  return byteArray;
//}

////##################################################################################################
//template<class T>
//void deserialize(tp_utils::StringIDManager* manager, const QByteArray& byteArray, T& data)
//{
//  tp_qt_utils_private::DataStream_lt dataStream(const_cast<QByteArray*>(&byteArray), QIODevice::ReadOnly, manager);
//  dataStream >> data;
//}

////##################################################################################################
//template<class T>
//void deserialize(const QByteArray& byteArray, T& data)
//{
//  QDataStream dataStream(const_cast<QByteArray*>(&byteArray), QIODevice::ReadOnly);
//  dataStream >> data;
//}

////##################################################################################################
//template<class T>
//QByteArray serializeStandAlone(const T& data)
//{
//  tp_utils::StringIDManager stringIDManager;
//
//  QByteArray serializedData = serialize(&stringIDManager, data);
//
//  QMap<QString, QVariant> map;
//  map.insert("StringID's", QByteArray::fromStdString(stringIDManager.saveState()));
//  map.insert("Data", serializedData);
//
//  //We should not use the stringIDManager now because it has already been saved, so we do our own
//  //serialization here.
//  QByteArray byteArray;
//  {
//    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);
//    dataStream << map;
//  }
//
//  return byteArray;
//}
//
////##################################################################################################
//template<class T>
//void deserializeStandAlone(const QByteArray& byteArray, T& data)
//{
//  QMap<QString, QVariant> map;
//  {
//    QDataStream dataStream((QByteArray*)&byteArray, QIODevice::ReadOnly);
//    dataStream >> map;
//  }
//
//  std::string stringIDsData = map.value("StringID's").toByteArray().toStdString();
//  tp_utils::StringIDManager stringIDManager(stringIDsData);
//  tp_qt_utils::deserialize(&stringIDManager, map.value("Data").toByteArray(), data);
//}

//##################################################################################################
//! Escape a binary string.
QByteArray escape(const QByteArray& input);

//##################################################################################################
//! Unescape an escaped binary string.
QByteArray unescape(const QByteArray& input);

//##################################################################################################
//! Escape a binary message.
QByteArray escapePacket(const SerialMessage& message);

//##################################################################################################
class PartialPacket
{
  int_fast8_t m_gotStart{false};
  int_fast32_t m_index{0};
  int_fast32_t m_bufferSize;
  char* m_commandBuffer;
  QList<SerialMessage> m_messages;
public:
  //################################################################################################
  PartialPacket(int bufferSize);

  //################################################################################################
  ~PartialPacket();

  //################################################################################################
  void addData(const QByteArray& input);

  //################################################################################################
  bool hasMessage()const;

  //################################################################################################
  QList<SerialMessage> takeMessages();
};

}

#endif
