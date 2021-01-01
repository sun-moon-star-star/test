/**
 * @file json_test.h
 * @author sun-moon-star-star
 */

#include <iostream>
#include <string>

#include "json/json.h" // jsoncpp

int main() {
    Json::Value root;
    Json::Value data;
    constexpr bool shouldUseOldWay = false;
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;
    root["test"] = "";

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);
    std::cout << json_file << std::endl;

    return 0;
}
