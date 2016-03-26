#!/bin/bash
make -C ../../trihlav-build package
rm -f trihlav-OpenSuSE-tumbleweed/trihlav-0.0.1-Linux.rpm
cp ../../trihlav-build/trihlav-0.0.1-Linux.rpm trihlav-OpenSuSE-tumbleweed
docker build -t opensuse/tumbleweed:v1 docker-containers-build/docker
docker build -t gcr.io/trihlav-1/trihlav-1-node:v4 trihlav-OpenSuSE-tumbleweed
