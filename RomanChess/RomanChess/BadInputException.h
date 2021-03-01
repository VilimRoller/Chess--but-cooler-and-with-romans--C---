#pragma once
#include <exception>
#include <string>

class BadInputException: 
	public std::exception
{
public:
	BadInputException(const std::string& message) {
		SetErrorMessage(message);
	}

	virtual const char* what() const throw () {
		return error_message_.c_str();
	}

	void SetErrorMessage(const std::string& message) {
		error_message_ = message;
	}

private:
	std::string error_message_;
};

