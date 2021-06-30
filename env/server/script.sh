#!/usr/bin/env bash
docker build -t registry.gitlab.com/app-goodok/servers/gateway-server:1.1.1 .
docker push registry.gitlab.com/app-goodok/servers/gateway-server:1.1.1