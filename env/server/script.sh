#!/usr/bin/env bash
docker pull docker.pkg.github.com/app-goodok/gatewayserver/common-env:0.1.1
docker build -t docker.pkg.github.com/app-goodok/gatewayserver/gateway-server:0.1.1 .
docker push docker.pkg.github.com/app-goodok/gatewayserver/gateway-server:0.1.1