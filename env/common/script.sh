#!/usr/bin/env bash
docker build -t docker.pkg.github.com/app-goodok/gatewayserver/common-env:0.1.1 .
docker push docker.pkg.github.com/app-goodok/gatewayserver/common-env:0.1.1