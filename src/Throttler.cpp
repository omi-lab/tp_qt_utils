#include <tp_qt_utils/Throttler.h>

#include "tp_utils/TimeUtils.h"

#include <limits>

namespace tp_qt_utils
{

//################################################################################################
Throttler::Throttler(int64_t timeOutMS)
    : m_timeOutMS(timeOutMS)
{
  m_timer.setSingleShot(true);
  QObject::connect(&m_timer, &QTimer::timeout, this, &Throttler::execNextStep, Qt::DirectConnection);
  m_timer.start(timeOutMS);
}

//################################################################################################
void Throttler::execNextStep()
{
  step();
  if(!finished())
    m_timer.start(m_timeOutMS);
  else // finished()
    deleteLater();
}

//################################################################################################
ThrottlerProcessVector::ThrottlerProcessVector(std::size_t vecSize, std::size_t maxNToProcess, int64_t timeOutMS)
    : Throttler(timeOutMS)
    , m_vecSize(vecSize)
    , m_maxNToProcess(maxNToProcess)
    , m_offset(0)
{
}

//################################################################################################
void ThrottlerProcessVector::step()
{
  TP_FUNCTION_TIME("ThrottlerProcessVector::step");
  std::size_t nextOffset = std::min<std::size_t>(m_offset + m_maxNToProcess, m_vecSize);
  processChunk(m_offset, nextOffset-m_offset);
  m_offset = nextOffset;
}
    
}
