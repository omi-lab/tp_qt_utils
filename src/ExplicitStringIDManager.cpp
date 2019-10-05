#include "tp_qt_utils/ExplicitStringIDManager.h"

#include "tp_utils/StringID.h"
#include "tp_utils/MutexUtils.h"
#include "tp_utils/DebugUtils.h"

#include <QMap>
#include <QHash>
#include <QDataStream>
#include <QtEndian>
#include <QDebug>

namespace tp_qt_utils
{
//##################################################################################################
struct ExplicitStringIDManager::Private
{
  TPMutex mutex{TPM};
  QMap<std::string, int64_t> keys;
  QHash<int64_t, std::string> stringKeys;
};

//##################################################################################################
ExplicitStringIDManager::ExplicitStringIDManager():
  d(new Private())
{

}

//##################################################################################################
ExplicitStringIDManager::~ExplicitStringIDManager()
{
  delete d;
}

//##################################################################################################
void ExplicitStringIDManager::addKeys(const QList<QPair<std::string, int64_t> >& sids)
{
  d->mutex.lock(TPM);
  for(const auto& sid : sids)
  {
    d->keys.insert(sid.first, sid.second);
    d->stringKeys.insert(sid.second, sid.first);
  }
  d->mutex.unlock(TPM);
}

//##################################################################################################
int64_t ExplicitStringIDManager::key(const std::string& keyString)
{
  if(keyString.empty())
    return 0;

  d->mutex.lock(TPM);
  int64_t key = d->keys.value(keyString, 0);

  if(!key)
    tpWarning() << "ExplicitStringIDManager::key() Failed to find key for: " << keyString;

  d->mutex.unlock(TPM);

  return key;
}

//##################################################################################################
std::string ExplicitStringIDManager::keyString(int64_t key)
{
  d->mutex.lock(TPM);
  std::string keyString = d->stringKeys.value(key);
  d->mutex.unlock(TPM);

  return keyString;
}

}
