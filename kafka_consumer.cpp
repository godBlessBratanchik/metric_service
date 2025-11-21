#include "kafka_consumer.h"

KafkaConsumer::KafkaConsumer(const std::string& broker_addr, const std::string& topic_name)
    : broker(broker_addr), topic(topic_name) {}

KafkaConsumer::~KafkaConsumer() {}

void KafkaConsumer::startConsuming(std::function<void(const std::string&)> callback) {
    std::cout << "[Kafka] Подключение к " << broker << ", тема: " << topic << std::endl;

    callback("status");
    callback("start");
    callback("stop");
}

json KafkaConsumer::parseMessage(const std::string& message) {
    json parsed;
    try {
        parsed = json::parse(message);
    }
    catch (...) {
        parsed["command"] = message;
        parsed["type"] = "simple";
    }
    return parsed;
}
