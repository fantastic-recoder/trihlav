#!/bin/bash
set -ex
export TRH_VER=$(date +%Y%m%d)
echo Pushing version $TRH_VER.
make -C ../../trihlav-build package
rm -f trihlav-OpenSuSE-tumbleweed/trihlav-0.0.1-Linux.rpm
cp ../../trihlav-build/trihlav-0.0.1-Linux.rpm trihlav-OpenSuSE-tumbleweed
docker build -t opensuse/tumbleweed:v1 docker-containers-build/docker
docker build -t gcr.io/trihlav-1/trihlav-1-node:$TRH_VER trihlav-OpenSuSE-tumbleweed
set +e
kubectl delete deployment,service trihlav-1-node
#kubectl delete service trihlav-1-node
gcloud docker push gcr.io/trihlav-1/trihlav-1-node:$TRH_VER
kubectl run trihlav-1-node --image=gcr.io/trihlav-1/trihlav-1-node:$TRH_VER --port=32899 --expose --service-overrides='{ "spec": { "type": "LoadBalancer" } }'
kubectl get pods
