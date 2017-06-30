FROM debian:testing
COPY . /tmp
WORKDIR /tmp
RUN sed -i s#deb.debian.org#ftp.de.debian.org# /etc/apt/sources.list
RUN apt-get update
RUN adduser --home /home/travis travis --quiet --disabled-login --gecos "" --uid 1000
RUN env DEBIAN_FRONTEND=noninteractive apt-get install build-essential ccache ninja-build expect curl git -q -y
RUN env DEBIAN_FRONTEND=noninteractive ./prepare-release travis-ci
RUN dpkg-reconfigure ccache
RUN rm -r /tmp/*
