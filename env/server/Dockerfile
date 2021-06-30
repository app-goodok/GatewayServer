FROM ubuntu:focal
MAINTAINER Konstantin Morozov <morozov-kst@yandex.ru>
ENV DEBIAN_FRONTEND=noninteractive

#ARG user
WORKDIR /server

ADD ./goodok-servers-*.*.*-Linux.deb /server

RUN apt-get install -y /server/goodok-servers-*.*.*-Linux.deb

ENTRYPOINT ["/usr/local/bin/goodok/gateway-server"]
CMD ["arg1", "arg2", "arg3", "arg4"]

EXPOSE 7777
EXPOSE 5432