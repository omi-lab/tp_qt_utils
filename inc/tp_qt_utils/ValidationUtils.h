#ifndef tp_qt_utils_ValidationUtils_h
#define tp_qt_utils_ValidationUtils_h

#include "tp_qt_utils/Globals.h"

#include <QString>

namespace tp_qt_utils
{

//##################################################################################################
//! Validate an email address
/*!
This method returns true if the text is in the correct format to be an email addess, it does not
attempt to check if the address actually exists.

\param text - The text to validate.
\returns - True if the text is in the correct format to be an email address.
*/
bool tp_qt_UTILS_SHARED_EXPORT validateEmail(const QString& text);


//##################################################################################################
//! Validate that a string contains only letters characters
/*!
This method returns true if the text is made up of only letters.

\param text - The text to validate.
\returns - True if the text contains only letters.
*/
bool tp_qt_UTILS_SHARED_EXPORT validateAlpha(const QString& text);


//##################################################################################################
//! Validate that a string contains only alpha numeric characters
/*!
This method returns true if the text is made up of only alpha numeric characters.

\param text - The text to validate.
\returns - True if the text is alpha numeric.
*/
bool tp_qt_UTILS_SHARED_EXPORT validateAlphaNumeric(const QString& text);
}

#endif
