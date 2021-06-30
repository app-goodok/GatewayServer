#!/usr/bin/env bash
docker login registry.gitlab.com
docker build -t registry.gitlab.com/app-goodok/servers/common-env:0.1.1 .
docker push registry.gitlab.com/app-goodok/servers/common-env:0.1.1