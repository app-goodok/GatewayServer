[![CMake](https://github.com/k-morozov/GatewayServer/actions/workflows/cmake.yml/badge.svg)](https://github.com/k-morozov/GatewayServer/actions/workflows/cmake.yml)

# gateway-server
### version 1.1.1
Для запуска:

````
docker run -it --network=host -p 7777:7777 registry.gitlab.com/app-goodok/servers/gateway-server:1.1.1  --user="имя_пользователя" --pass="пароль" --name="имя_базы" --host="127.0.0.1"
````
