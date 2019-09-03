FROM ubuntu:19.04
MAINTAINER Billy
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install xinetd -y
RUN useradd -m nosyscall
RUN chmod 774 /tmp
RUN chmod -R 774 /var/tmp
RUN chmod -R 774 /dev
RUN chmod -R 774 /run
RUN chmod 1733 /tmp /var/tmp /dev/shm
RUN chown -R root:root /home/nosyscall
CMD ["/usr/sbin/xinetd","-dontfork"]
