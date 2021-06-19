#!/usr/bin/env bash
docker pull docker.pkg.github.com/app-goodok/gatewayserver/common-env:0.1.1
docker build -t ghcr.io/app-goodok/gatewayserver/common-env:0.1.1 .
docker push ghcr.io/app-goodok/gatewayserver/common-env:0.1.1