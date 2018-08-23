#include "tdp_qt_utils/FileUtils.h"

#include "tp_utils/DebugUtils.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTemporaryDir>
#include <QCoreApplication>

#if !defined(Q_OS_IOS) && !defined(Q_OS_WINRT)
#include <QProcess>
#endif


namespace tdp_qt_utils
{
//##################################################################################################
QString readFile(const QString& fileName)
{
  QFile file(fileName);
  if(!file.open(QIODevice::ReadOnly))
    return QString();

  return QTextStream(&file).readAll();
}

//##################################################################################################
QByteArray readBinaryFile(const QString& fileName)
{
  QFile file(fileName);

  if(!file.open(QIODevice::ReadOnly))
    return QByteArray();

  return file.readAll();
}

//##################################################################################################
bool writeTextFile(const QString& fileName, const QString& textOutput)
{
  // Try and open a file for output
  QFile outputFile(fileName);

  // Check it opened OK
  if(!outputFile.open(QIODevice::WriteOnly))
    return false;

  outputFile.write(textOutput.toLatin1());
  return true;
}

//##################################################################################################
bool writeBinaryFile(const QString& fileName, const QByteArray& data)
{
  // Try and open a file for output
  QFile outputFile(fileName);

  // Check it opened OK
  if(!outputFile.open(QIODevice::WriteOnly))
    return false;

  outputFile.write(data);
  return true;
}

//##################################################################################################
QMap<QString, QString> parseConfigFile(const QString& fileName)
{
  return parseConfigFiles({fileName});
}

//##################################################################################################
QMap<QString, QString> parseConfigFiles(const QStringList& fileNames)
{
  QMap<QString, QString> results;

  QStringList lines;

  for(const QString& fileName : fileNames)
  {
    QString  content = readFile(fileName);
    content.remove(QChar('\r'));
    lines.append(content.split(QChar('\n')));
  }

  int ln=1;
  Q_FOREACH(QString line, lines)
  {
    ln++;

    int commentIndex = line.indexOf(QChar('#'));
    if(commentIndex != -1)
      line = line.left(commentIndex);

    line = line.simplified();

    if(line.isEmpty())
      continue;

    int colonIndex = line.indexOf(QChar(':'));

    if(colonIndex<1)
    {
      for(const QString& fileName : fileNames)
        tpWarning() << "Parse error! " << fileName.toStdString();
      tpWarning()   << " --  Line:\n" << line.toStdString();
      continue;
    }

    QString left = line.left(colonIndex);
    QString right = line.right(line.size() - (colonIndex+1));

    results.insert(left.simplified().toLower(), right.simplified());
  }

  return results;
}

//##################################################################################################
QMap<QString, QString> parseCommandLine()
{
  QMap<QString,QString> parameters;

  QStringList args = QCoreApplication::arguments();
  for(int i=1; i<args.size(); i++)
  {
    QStringList parts = args.at(i).split('=');

    if(parts.size() == 2)
      parameters.insert(parts.first().toLower(), parts.last());
  }

  return parameters;
}

#if !defined(Q_OS_IOS) && !defined(Q_OS_WINRT)
//##################################################################################################
bool createZip(const QString& fileName, const QByteArray& data, QByteArray& zippedData)
{
  //-- Get a temporary directory to hold the working files -----------------------------------------
  QTemporaryDir dir;
  if (!dir.isValid())
  {
    tpWarning() << "Invalid temporary directory.";
    return false;
  }


  //-- Get the path to the temp source file --------------------------------------------------------
  QString srcPath;
  {
    srcPath = dir.path();
    if(!srcPath.endsWith('/'))
      srcPath.append('/');

    srcPath.append(fileName);
  }


  //-- Get the path tothe temp zip file ------------------------------------------------------------
  QString dstPath;
  {
    dstPath = dir.path();
    if(!dstPath.endsWith('/'))
      dstPath.append('/');

    dstPath.append("out.zip");
  }

  //-- Create the temporary source file ------------------------------------------------------------
  if(!tdp_qt_utils::writeBinaryFile(srcPath, data))
  {
    tpWarning() << "Failed to write file to: " << srcPath.toStdString();
    return false;
  }


  //-- Zip the file --------------------------------------------------------------------------------
  {
    QProcess process;
    // -j = Don't add the full path
    const QStringList zipArgs = QStringList{dstPath, "-j", srcPath};

    process.start("zip", zipArgs);

    process.waitForStarted();
    process.waitForFinished();

    if(process.error()!=QProcess::UnknownError)
    {
      tpWarning() << "Zip process error: " << process.errorString().toStdString();
      return false;
    }

    if(process.exitCode())
    {
      tpWarning() << "Zip process exit code: " << process.exitCode();
      return false;
    }
  }


  //-- Read the data from the zip file -------------------------------------------------------------
  zippedData = tdp_qt_utils::readBinaryFile(dstPath);

  return true;
}
#endif

//##################################################################################################
QString guessImageFormat(const QByteArray& data, const QString& name)
{
  if(data.startsWith("\xFF\xD8\xFF"))
    return "jpg";

  if(data.startsWith("\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"))
    return "png";

  if(data.startsWith("GIF87a") || data.startsWith("GIF89a"))
    return "gif";

  if(data.startsWith("\x49\x49\x2A\x00") || data.startsWith("\x4D\x4D\x00\x2A"))
    return "tiff";

  if(data.startsWith("BM"))
    return "bmp";

  if(data.startsWith("RIFF") || data.startsWith("WEBP"))
    return "webp";

  if(data.startsWith("\x00\x00\x01\x00") || data.startsWith("\x00\x00\x02\x00"))
    return "ico";

  return name.split('.').last();
}
}

