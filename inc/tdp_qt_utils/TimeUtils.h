#ifndef tdp_qt_utils_TimeUtils_h
#define tdp_qt_utils_TimeUtils_h

#include "tdp_qt_utils/Globals.h"

#include <QDateTime>
#include <QElapsedTimer>

namespace tdp_qt_utils
{

//##################################################################################################
//! Returns the current time as a 64 bit Unix time stamp
/*!
\return the current time as a 64 bit Unix time stamp
*/
int64_t TDP_QT_UTILS_SHARED_EXPORT currentTime();

//##################################################################################################
//! Returns the current time as ms since SinceEpoch
/*!
\return the current time as ms since since the epoch
*/
int64_t TDP_QT_UTILS_SHARED_EXPORT currentTimeMS();

//##################################################################################################
//! Returns the current time as a QDateTime, in UTC.
/*!
\return the current time as a QDateTime
*/
QDateTime TDP_QT_UTILS_SHARED_EXPORT currentDateTime();

//##################################################################################################
//! Returns the current time, in UTC, as a string.
QString TDP_QT_UTILS_SHARED_EXPORT currentTimeString();

//##################################################################################################
//! Returns a Unix time converted to local time, as a string.
QString TDP_QT_UTILS_SHARED_EXPORT timeString(int64_t time);

//##################################################################################################
//! For debug, returns the current time as a string and a diff between that and the previous call
QString TDP_QT_UTILS_SHARED_EXPORT timeDiff();

//##################################################################################################
//! The start of the minute for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toMinute(int64_t secsSinceEpoch);

//##################################################################################################
//! The start of the minute for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toMinute(const QString& secsSinceEpoch);

//##################################################################################################
//! The start of the hour for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toHour(int64_t secsSinceEpoch);

//##################################################################################################
//! The start of the hour for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toHour(const QString& secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the day for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toDay(int64_t secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the day for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toDay(const QString& secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the week (Monday) for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toWeek(int64_t secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the week (Monday) for the given time, secs since epoch
int64_t TDP_QT_UTILS_SHARED_EXPORT toMonth(int64_t secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the month for the given time, secs since epoch
QDateTime TDP_QT_UTILS_SHARED_EXPORT toDateTime(int64_t secsSinceEpoch);

//##################################################################################################
//! Using UTC, the start of the month for the given time, secs since epoch
QDateTime TDP_QT_UTILS_SHARED_EXPORT toDateTime(const QString& secsSinceEpoch);

//##################################################################################################
class TDP_QT_UTILS_SHARED_EXPORT TimingStats
{
public:
  static void logTime(const char* name, const char* file, int line, int time);

  static QString takeResults();

private:
  struct Private;
  static Private* instance();
};


}
#ifdef TDP_ENABLE_TIMING_STATS
#define TDP_START_TIMER(name)QElapsedTimer name##_timer; name##_timer.start()
#define TDP_LOG_TIMER(name)tdp_qt_utils::TimingStats::logTime(#name, __FILE__, __LINE__, name##_timer.elapsed())
#else
#define TDP_START_TIMER(name)
#define TDP_LOG_TIMER(name)
#endif

#endif
