FROM ubuntu:latest
MAINTAINER coder.peter.grobarcik@googlemail.com

# Install.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y software-properties-common && \
  apt-get install -y   libboost-log1.58.0 libboost-system1.58.0 \
  libboost-regex1.58.0 libboost-locale1.58.0 libyubikey0 libboost-thread1.58.0 \
  libboost-filesystem1.58.0 libicu55 libboost-random1.58.0 \
  libboost-date-time1.58.0 libssl1.0.0 libboost-program-options1.58.0 && \
  rm -rf /var/lib/apt/lists/*

# Add files.
ADD /usr/local /usr
ADD trihlav-0.0.1-Linux.deb /root
# Set environment variables.
ENV HOME /root

# Define working directory.
WORKDIR /root
RUN dpkg -i trihlav-0.0.1-Linux.deb
EXPOSE 32899

# Define default command.
CMD ["/usr/bin/trihlavsrv"]
