#ifndef tdp_qt_utils_Interface_h
#define tdp_qt_utils_Interface_h

#include "tdp_qt_utils/Globals.h"

#include <QDebug>

#if defined(Q_OS_WIN)
#undef interface
#endif

#define TDP_WARN(i)if(!i)tpWarning() << __FILE__ << __LINE__ << "Failed to find interface: " #i

class QString;

namespace tp_utils
{
class StringID;
}

namespace tdp_qt_utils
{

//##################################################################################################
//! This provides a generic way to pass interfaces to different classes
/*!

*/
class TDP_QT_UTILS_SHARED_EXPORT Interface
{
public:
  //################################################################################################
  Interface();

  //################################################################################################
  virtual ~Interface();

  //################################################################################################
  //! Find the interface related to the given stringID
  /*!
  \param stringID - The id of the desired interface
  \return A pointer to the interface or nullptr if nothing is set for stringID
  */
  void* findVoid(const tp_utils::StringID& stringID)const;

  //################################################################################################
  template<class T>
  void find(const tp_utils::StringID& stringID, T** interface)const
  {
    *interface = static_cast<T*>(findVoid(stringID));
  }

  //################################################################################################
  void set(const tp_utils::StringID& stringID, void* interface);

  //################################################################################################
  void clear(const tp_utils::StringID& stringID);

  //################################################################################################
  //! Prevent setting or clearing interfaces
  void lockInterface(bool lock);

private:
  struct Private;
  Private* d;
  friend struct Private;
};

}

#endif
