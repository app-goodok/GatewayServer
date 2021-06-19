FROM docker.pkg.github.com/app-goodok/gatewayserver/common-env:0.1.1
MAINTAINER Konstantin Morozov <morozov-kst@yandex.ru>
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /server

ADD ./gateway-server /server

CMD ["/server/gateway-server"]

EXPOSE 7777
EXPOSE 5432