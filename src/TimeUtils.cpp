#include "tdp_qt_utils/TimeUtils.h"
#include "tp_utils/MutexUtils.h"

#include <QObject>
#include <QDateTime>
#include <QDebug>

#include <chrono>

namespace tdp_qt_utils
{

namespace
{
struct TimeDetails_lt
{
  QString name;
  int total{0};
  int recent{0};
};
}

//##################################################################################################
int64_t currentTime()
{
  return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

//##################################################################################################
int64_t currentTimeMS()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

//##################################################################################################
QDateTime currentDateTime()
{
  return QDateTime::fromMSecsSinceEpoch(currentTime()*1000ll,Qt::UTC);
}

//##################################################################################################
QString currentTimeString()
{
  return currentDateTime().toString();
}

//##################################################################################################
QString timeString(int64_t time)
{
  return QDateTime::fromMSecsSinceEpoch(time*1000ll,Qt::UTC).toString();
}

//##################################################################################################
QString timeDiff()
{
  static TPMutex mutex{TPM};
  static int64_t previousTime=0;

  TP_MUTEX_LOCKER(mutex);

  int64_t timeMS = currentTimeMS();

  QString time = QString::number(timeMS);
  QString diff = (previousTime<1) ? QString() : QString::number(timeMS-previousTime);

  while(diff.size()<10)
    diff.prepend(' ');

  previousTime = timeMS;

  return QString("%1 %2").arg(diff, time);
}

//################################################################################################
int64_t toMinute(int64_t secsSinceEpoch)
{
  int64_t secs = secsSinceEpoch % 60;
  return secsSinceEpoch - secs;
}

//################################################################################################
int64_t toMinute(const QString& secsSinceEpoch)
{
  return toMinute(secsSinceEpoch.toLongLong());
}

//################################################################################################
int64_t toHour(int64_t secsSinceEpoch)
{
  int64_t secs = secsSinceEpoch % 3600;
  return secsSinceEpoch - secs;
}

//################################################################################################
int64_t toHour(const QString& secsSinceEpoch)
{
  return toHour(secsSinceEpoch.toLongLong());
}

//################################################################################################
int64_t toDay(int64_t secsSinceEpoch)
{
  int64_t secs = secsSinceEpoch % 86400;
  return secsSinceEpoch - secs;
}

//################################################################################################
int64_t toDay(const QString& secsSinceEpoch)
{
  return toDay(secsSinceEpoch.toLongLong());
}

//################################################################################################
int64_t toWeek(int64_t secsSinceEpoch)
{
  const QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(toDay(secsSinceEpoch)*1000, Qt::UTC);
  return dateTime.addDays(dateTime.date().dayOfWeek() - 1).toMSecsSinceEpoch()/1000;
}

//################################################################################################
int64_t toMonth(int64_t secsSinceEpoch)
{
  QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(toDay(secsSinceEpoch)*1000, Qt::UTC);
  dateTime.setDate(QDate(dateTime.date().year(), dateTime.date().month(), 1));
  return dateTime.toMSecsSinceEpoch()/1000;
}

//################################################################################################
QDateTime toDateTime(int64_t secsSinceEpoch)
{
  return QDateTime::fromMSecsSinceEpoch(1000ll*secsSinceEpoch, Qt::UTC);
}

//################################################################################################
QDateTime toDateTime(const QString& secsSinceEpoch)
{
  return toDateTime(secsSinceEpoch.toLongLong());
}

//##################################################################################################
QString fixedWidthKeepRight(const QString& data, int len, char pad)
{
  if(data.size()>=len)
    return data.right(len);

  QString d(data);
  while(d.size()<len)
    d.prepend(pad);

  return d;
}

//##################################################################################################
struct TimingStats::Private
{
  TPMutex mutex{TPM};
  QMap<QString, TimeDetails_lt> timeDetails;
};

//##################################################################################################
void TimingStats::logTime(const char* name, const char* file, int line, int time)
{
  Private* d = instance();
  TP_MUTEX_LOCKER(d->mutex);

  QString index = QString("%1:%2").arg(file).arg(line);
  TimeDetails_lt& timeDetails = d->timeDetails[index];

  timeDetails.name = QString("%1:%2").arg(name, fixedWidthKeepRight(index, 100-((int) strlen(name)), ' '));
  timeDetails.total  += time;
  timeDetails.recent += time;
}

//##################################################################################################
QString TimingStats::takeResults()
{
  Private* d = instance();
  TP_MUTEX_LOCKER(d->mutex);

  QString result = tdp_qt_utils::currentTimeString() + "\n";

  //-- Sort the mutexes by total -------------------------------------------------------------------
  QList<TimeDetails_lt*> sortedTimeDetails;
  Q_FOREACH(const QString& key, d->timeDetails.keys())
  {
    TimeDetails_lt* timeDetails = &(d->timeDetails[key]);

    int c=0;
    while(c<sortedTimeDetails.size() && sortedTimeDetails.at(c)->total>=timeDetails->total)
      c++;

    sortedTimeDetails.insert(c, timeDetails);
  }

  //-- Print the results out -----------------------------------------------------------------------
  Q_FOREACH(TimeDetails_lt* timeDetails, sortedTimeDetails)
  {
    QString name   = timeDetails->name;
    QString recent = fixedWidthKeepRight(QString::number(timeDetails->recent), 10, ' ');
    QString total  = fixedWidthKeepRight(QString::number(timeDetails->total),  10, ' ');
    result.append(QString("%1: Recent=%2 Total=%3\n").arg(name, recent, total));
  }

  result.append('\n');

  //-- Sort the mutexes by recent ------------------------------------------------------------------
  sortedTimeDetails.clear();
  Q_FOREACH(const QString& key, d->timeDetails.keys())
  {
    TimeDetails_lt* timeDetails = &(d->timeDetails[key]);

    int c=0;
    while(c<sortedTimeDetails.size() && sortedTimeDetails.at(c)->recent>=timeDetails->recent)
      c++;

    sortedTimeDetails.insert(c, timeDetails);
  }

  //-- Print the results out -----------------------------------------------------------------------
  Q_FOREACH(TimeDetails_lt* timeDetails, sortedTimeDetails)
  {
    QString name   = timeDetails->name;
    QString recent = fixedWidthKeepRight(QString::number(timeDetails->recent), 10, ' ');
    QString total  = fixedWidthKeepRight(QString::number(timeDetails->total),  10, ' ');
    result.append(QString("%1: Recent=%2 Total=%3\n").arg(name, recent, total));

    timeDetails->recent=0;
  }


  return result;
}

//##################################################################################################
TimingStats::Private* TimingStats::instance()
{
  static TimingStats::Private instance;
  return &instance;
}

}
