#pragma once
#include <exception>
#include <stdexcept>
#include <string>
class E_runtime_exception : public std::exception
{
public:
	
	


	E_runtime_exception(const std::string& what, const std::string& file, const int& line)
	{
		message = "Exception: " + what + " in " + file + " at line " + std::to_string(line);
	}
	
	const char* what() const noexcept override {
		return message.c_str();
	}

private:
	std::string message = "";//message
	



};