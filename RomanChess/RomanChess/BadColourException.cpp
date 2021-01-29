#include "BadColourException.h"

BadColourException::BadColourException(const std::string& message) {
	SetErrorMessage(message);
}

inline void BadColourException::SetErrorMessage(const std::string& message) {
	error_message_ = message;
}