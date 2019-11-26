#include "tp_qt_utils/Progress.h"

#include "tp_utils/MutexUtils.h"


namespace tp_qt_utils
{

//##################################################################################################
struct Progress::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_utils::Progress::Private");
  TP_NONCOPYABLE(Private);
  Private() = default;

  TPMutex mutex{TPM};
  QString description;
  float progress{0.0f};

  bool shouldStop{false};
};

//##################################################################################################
Progress::Progress(QObject* parent):
  QObject(parent),
  d(new Private())
{

}

//##################################################################################################
Progress::~Progress()
{
  delete d;
}

//##################################################################################################
void Progress::setProgress(float percent)
{
  d->mutex.lock(TPM);
  d->progress = percent;
  d->mutex.unlock(TPM);

  emit changed();
}

//##################################################################################################
void Progress::setProgress(float percent, const QString& description)
{
  d->mutex.lock(TPM);
  d->progress = percent;
  d->description = description;
  d->mutex.unlock(TPM);

  emit changed();
}

//##################################################################################################
void Progress::setDescription(const QString& description)
{
  d->mutex.lock(TPM);
  d->description = description;
  d->mutex.unlock(TPM);

  emit changed();
}

//##################################################################################################
QString Progress::description()const
{
  d->mutex.lock(TPM);
  QString description = d->description;
  d->mutex.unlock(TPM);

  return description;
}

//##################################################################################################
float Progress::progress()const
{
  d->mutex.lock(TPM);
  float progress = d->progress;
  d->mutex.unlock(TPM);

  return progress;
}

//##################################################################################################
void Progress::stop(bool shouldStop)
{
  d->mutex.lock(TPM);
  d->shouldStop = shouldStop;
  d->mutex.unlock(TPM);
}

//##################################################################################################
bool Progress::shouldStop()const
{
  d->mutex.lock(TPM);
  bool shouldStop = d->shouldStop;
  d->mutex.unlock(TPM);

  return shouldStop;
}

}
