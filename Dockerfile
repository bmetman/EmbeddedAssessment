FROM ubuntu:16.04

RUN apt-get update && \
	apt-get clean

ARG USER_UID
ARG USER

#RUN groupadd -g $USER_UID $USER && \
#    useradd -r -u $USER_UID -g $USER $USER -m -s /bin/bash && \
#    echo $USER:$USER | chpasswd && \
#    echo "$USER ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
#USER $USER

ENV SRC_DIR=/home/$USER/main
RUN mkdir -p $SRC_DIR
WORKDIR $SRC_DIR

#USER root
#RUN chown -R $USER:$USER /home/$USER/*
#USER $USER

#CMD sleep infinity

