#pragma once
#include <exception>
#include <string>

class BadColourException: 
	public std::exception
{
public:
	BadColourException(const std::string& message);
	virtual const char* what() const throw () {
		return error_message_.c_str();
	}

	void SetErrorMessage(const std::string& message);

private:
	std::string error_message_;
};

