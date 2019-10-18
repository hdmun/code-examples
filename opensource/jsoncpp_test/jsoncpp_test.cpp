#include <iostream>
#include <list>
#include <fstream>
#include <future>
#include "json/json.h"

namespace jsoncpp_test {

	void parse(std::string json)
	{
		// Jsoncpp::Reader 사용을 위해 SDL 옵션 끔

		Jsoncpp::Value root;
		Jsoncpp::Reader reader;
		bool bParse = reader.parse(json, root);

		auto memberNames = root.getMemberNames();
		for (const auto& name : memberNames) {

			Jsoncpp::Value node = root[name];
			if (node.isBool()) {
				node.asBool();
				continue;
			}
			if (node.isInt()) {
				node.asInt();
				continue;
			}
			if (node.isString()) {
				node.asString();
				continue;
			}
		}
	}

	void run()
	{
		std::cout << "jsoncpp_test" << std::endl;

		std::list< std::future<void> > futurelist;

		std::ifstream infile("json_text_sample.txt");
		std::string line;
		while (std::getline(infile, line))
		{
			futurelist.push_back(
				std::async(
					std::launch::async
					, [line] {
						parse(line);
					}
				)
			);
		}

		for (const auto& iter : futurelist)
		{
			iter.wait();
		}

		std::cout << "jsoncpp_test done" << std::endl;
	}
}

int main()
{
	jsoncpp_test::run();
}
