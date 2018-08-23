#include "tdp_qt_utils/Interface.h"
#include "tp_utils/StringID.h"
#include "tp_utils/DebugUtils.h"

#include <QHash>

namespace tdp_qt_utils
{

//##################################################################################################
struct Interface::Private
{
  Interface* q;

  QHash<tp_utils::StringID, void*> interfaces;

  bool lock;

  Private(Interface* q_):
    q(q_),
    lock(false)
  {

  }
};

//##################################################################################################
Interface::Interface():
  d(new Private(this))
{

}

//##################################################################################################
Interface::~Interface()
{
  delete d;
}

//##################################################################################################
void* Interface::findVoid(const tp_utils::StringID& stringID)const
{
  return d->interfaces.value(stringID, nullptr);
}

//##################################################################################################
void Interface::set(const tp_utils::StringID& stringID, void* interface)
{
  if(d->lock)
    tpWarning() << "Interface::clear() Error tried to set on a locked interface!";

  d->interfaces.insert(stringID, interface);
}

//##################################################################################################
void Interface::clear(const tp_utils::StringID& stringID)
{
  if(d->lock)
    tpWarning() << "Interface::clear() Error tried to clear on a locked interface!";

  d->interfaces.remove(stringID);
}

//##################################################################################################
void Interface::lockInterface(bool lock)
{
  d->lock = lock;
}

}
