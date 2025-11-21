#pragma once

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

class GrafanaController {
private:
    std::string grafana_url;
    std::string api_token;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

public:
    GrafanaController(const std::string& url, const std::string& token);
    ~GrafanaController();

    bool getStatus();
    bool startGrafana();
    bool stopGrafana();
    json getGrafanaInfo();
};
