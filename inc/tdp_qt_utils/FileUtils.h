#ifndef tdp_qt_utils_FileUtils_h
#define tdp_qt_utils_FileUtils_h

#include "tdp_qt_utils/Globals.h"

#include <QString>
#include <QMap>

namespace tdp_qt_utils
{
//##################################################################################################
//! Reads a file to a string
/*!
Reads all of a file into a string.

\param fileName - The name of the file to load.
\returns - The contents of the file, or an empty string.
*/
QString TDP_QT_UTILS_SHARED_EXPORT readFile(const QString& fileName);

//##################################################################################################
//! Reads a file to a byte array
/*!
Reads all of a file into a byte array.

\param fileName - The name of the file to load.
\returns - The contents of the file, or an empty byte array.
*/
QByteArray TDP_QT_UTILS_SHARED_EXPORT readBinaryFile(const QString& fileName);

//##################################################################################################
//! Writes a string to a file
/*!
\param fileName
\param textOutput
\return True if the file was written, else false.
 */
bool TDP_QT_UTILS_SHARED_EXPORT writeTextFile(const QString& fileName, const QString& textOutput);

//##################################################################################################
//! Write binary data to a file
/*!
\param fileName - The name of the file to write to.
\param data - The binary data to write out
\return True if the file was written, else false.
*/
bool TDP_QT_UTILS_SHARED_EXPORT writeBinaryFile(const QString& fileName, const QByteArray& data);

//##################################################################################################
//! Reads a config file into a map
/*!
This will read a config file into a map, all keys will be lower case, keys and values will be
separated by colons, and a hash makes the rest of the line a comment. Later lines will overwrite
replace earlier lines.

\param fileName - The file to read config from
\return
*/
QMap<QString, QString> TDP_QT_UTILS_SHARED_EXPORT parseConfigFile(const QString& fileName);

//##################################################################################################
//! Reads multiple config file into a map
/*!
This will read a config file into a map, all keys will be lower case, keys and values will be
separated by colons, and a hash makes the rest of the line a comment. Later lines will overwrite
replace earlier lines.

\param fileNames - The files to read config from later files
\return
*/
QMap<QString, QString> TDP_QT_UTILS_SHARED_EXPORT parseConfigFiles(const QStringList& fileNames);

//##################################################################################################
QMap<QString, QString> parseCommandLine();

//##################################################################################################
//! Create a zip file containing a single file
/*!
This will zip a single file using the standard .zip file format and return the zipped data.

\warning Currently this only works for Linux.

\param fileName - The name of the file inside the zip
\param data - The data inside the file
\param zippedData - The zipped archive data (out)
\return True if ok
*/
bool TDP_QT_UTILS_SHARED_EXPORT createZip(const QString& fileName, const QByteArray& data, QByteArray& zippedData);

//##################################################################################################
//! This tries to guess the image type from the image data
/*!
This tries to guess the image type from the image data, if that fails it will try to use the name.

\param data - The image data.
\param name - The file name of the image where available.
\return The guessed type.
*/
QString guessImageFormat(const QByteArray& data, const QString& name=QString());


}

#endif
