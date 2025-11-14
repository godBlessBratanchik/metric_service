FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    librdkafka-dev \
    nlohmann-json3-dev \
    git

WORKDIR /app
COPY . .

RUN cmake . && make

CMD ["./grafana_service"]