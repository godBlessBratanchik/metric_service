#include "grafana_controller.h"

size_t GrafanaController::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

GrafanaController::GrafanaController(const std::string& url, const std::string& token)
    : grafana_url(url), api_token(token) {}

GrafanaController::~GrafanaController() {}

bool GrafanaController::getStatus() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string response;
    std::string auth_header = "Authorization: Bearer " + api_token;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, auth_header.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, (grafana_url + "/api/health").c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        json j = json::parse(response);
        return res == CURLE_OK && j.contains("status") && j["status"] == "ok";
    }
    catch (...) {
        return false;
    }
}

bool GrafanaController::startGrafana() {
    std::cout << "[INFO] Команда: запустить Grafana на " << grafana_url << std::endl;
    json response;
    response["action"] = "start";
    response["timestamp"] = std::time(nullptr);
    std::cout << "[Response] " << response.dump(2) << std::endl;
    return true;
}

bool GrafanaController::stopGrafana() {
    std::cout << "[INFO] Команда: остановить Grafana" << std::endl;
    json response;
    response["action"] = "stop";
    response["timestamp"] = std::time(nullptr);
    std::cout << "[Response] " << response.dump(2) << std::endl;
    return true;
}

json GrafanaController::getGrafanaInfo() {
    json info;
    info["url"] = grafana_url;
    info["version"] = "9.0.0";
    return info;
}
