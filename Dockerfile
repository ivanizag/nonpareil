FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -y scons flex bison libgtk2.0-dev libxml2-dev libsdl1.2-dev netpbm && \
    apt clean

WORKDIR /src

CMD ["scons"]

