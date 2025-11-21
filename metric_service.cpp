// main.cpp
#include "grafana_controller.h"
#include "kafka_consumer.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    setlocale(0, "");
    std::cout << "=== Grafana Microservice ===" << std::endl;

    // Инициализация
    GrafanaController grafana("http://localhost:3000", "your-api-token");
    KafkaConsumer kafka("localhost:9092", "grafana-commands");

    // Обработчик команд из Kafka
    auto handleCommand = [&grafana](const std::string& command) {
        std::cout << "\n[Kafka] Получена команда: " << command << std::endl;

        json response;

        if (command == "status") {
            bool is_running = grafana.getStatus();
            response["status"] = is_running ? "running" : "stopped";
            response["command"] = "status";
        }
        else if (command == "start") {
            if (grafana.startGrafana()) {
                response["status"] = "started";
                response["command"] = "start";
            }
        }
        else if (command == "stop") {
            if (grafana.stopGrafana()) {
                response["status"] = "stopped";
                response["command"] = "stop";
            }
        }
        else {
            response["error"] = "Unknown command";
            response["command"] = command;
        }

        std::cout << "[Result] " << response.dump(2) << std::endl;
        };

    // Запуск консьюмера
    kafka.startConsuming(handleCommand);

    std::cout << "\n=== Завершение ===" << std::endl;
    return 0;
}
