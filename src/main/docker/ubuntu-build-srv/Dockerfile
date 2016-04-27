FROM ubuntu:latest
MAINTAINER coder.peter.grobarcik@googlemail.com

# Install.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y software-properties-common && \
  apt-get install -y gcc g++ cmake libboost-dev-all && \
  rm -rf /var/lib/apt/lists/*

# Add files.
ADD /usr/local /usr
# Set environment variables.
ENV HOME /root

# Define working directory.
WORKDIR /root

# Define default command.
CMD ["bash"]
