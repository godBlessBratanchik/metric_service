#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class KafkaConsumer {
private:
    std::string broker;
    std::string topic;

public:
    KafkaConsumer(const std::string& broker_addr, const std::string& topic_name);
    ~KafkaConsumer();

    void startConsuming(std::function<void(const std::string&)> callback);
    json parseMessage(const std::string& message);
};
