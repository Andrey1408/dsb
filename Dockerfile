FROM --platform=arm64 ubuntu:trusty-14.04

LABEL name="ds"
LABEL lab.number ="1"

RUN "apt" "-y update"
RUN "apt" "-y --allow-unauthenticated install clang \
make \ clang-tidy"

RUN "mkdir" "/app"
WORKDIR /app
COPY ./ /app