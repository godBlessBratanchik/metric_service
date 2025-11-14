#include <gtest/gtest.h>
#include "grafana_controller.h"
#include "kafka_consumer.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GrafanaControllerTest : public ::testing::Test {
protected:
    GrafanaController controller{ "http://localhost:3000", "test-token" };
};

TEST_F(GrafanaControllerTest, StartGrafanaReturnsTrueTest) 
{
    EXPECT_TRUE(controller.startGrafana());
}

TEST_F(GrafanaControllerTest, StopGrafanaReturnsTrueTest) 
{
    EXPECT_TRUE(controller.stopGrafana());
}

TEST_F(GrafanaControllerTest, GetGrafanaInfoReturnsJsonTest) 
{
    json info = controller.getGrafanaInfo();
    EXPECT_TRUE(info.contains("url"));
    EXPECT_EQ(info["url"], "http://localhost:3000");
}

class KafkaConsumerTest : public ::testing::Test {
protected:
    KafkaConsumer kafka{ "localhost:9092", "test-topic" };
};

TEST_F(KafkaConsumerTest, ParseMessageReturnsJsonTest) 
{
    json result = kafka.parseMessage("status");
    EXPECT_TRUE(!result.empty());
}
