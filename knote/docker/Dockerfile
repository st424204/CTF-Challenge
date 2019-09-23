FROM ubuntu:19.04
MAINTAINER Billy
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install xinetd -y
RUN apt-get install qemu-system-x86 -y
RUN apt-get install socat
RUN useradd -m knote
COPY ./share /home/knote
COPY ./xinetd /etc/xinetd.d/knote
RUN chmod 774 /tmp
RUN chmod -R 774 /var/tmp
RUN chmod -R 774 /dev
RUN chmod -R 774 /run
RUN chmod 1733 /tmp /var/tmp /dev/shm
RUN chown -R root:root /home/knote
CMD ["/bin/bash","-c","/home/knote/start.sh"]
