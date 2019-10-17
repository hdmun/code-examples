#include <iostream>
#include <string>

namespace c_str {

	std::string asNull()
	{
		return "";
	}

	std::string asBool(bool is)
	{
		return is ? "true" : "false";
	}

	std::string asString()
	{
		return std::string("string c_str test");
	}

	void run()
	{
		const char* s = nullptr;

		s = asNull().c_str();
		std::cout << s << std::endl;

		s = asBool(true).c_str();
		std::cout << s << std::endl;

		s = asBool(false).c_str();
		std::cout << s << std::endl;

		s = asString().c_str();
		std::cout << s << std::endl;
	}
}

int main()
{
	c_str::run();
}
