FROM opensuse/tumbleweed:v1
MAINTAINER coder.peter.grobarcik@googlemail.com
RUN zypper --gpg-auto-import-keys ref -s
RUN zypper ar -f -n repo-update http://download.opensuse.org/update/tumbleweed/ repo-update
RUN zypper ar -f -n repo-oss http://download.opensuse.org/tumbleweed/repo/oss repo-oss
RUN zypper -n in wt wt-dbo sqlite3 openssh
ENV INSTDIR /tmp/trihlav-inst
RUN mkdir $INSTDIR && rm -rfv $INSTDIR/*
COPY trihlav-0.0.1-Linux.rpm $INSTDIR
RUN zypper in -y /tmp/trihlav-inst/trihlav-0.0.1-Linux.rpm
RUN zypper up -y

