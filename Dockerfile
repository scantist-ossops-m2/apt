FROM debian:testing
RUN apt-get update
COPY . /tmp
WORKDIR /tmp
RUN adduser --home /home/travis travis --quiet --disabled-login --gecos "" --uid UID
RUN env DEBIAN_FRONTEND=noninteractive apt-get install build-essential ccache ninja-build expect -q -y
RUN env DEBIAN_FRONTEND=noninteractive ./prepare-release travis-ci
RUN rm -r /tmp/*
