FROM ubuntu:19.04
MAINTAINER Billy
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install ssh -y
RUN apt-get install qemu-system-x86 -y
RUN useradd -m knote
RUN echo "knote:knote" | chpasswd
RUN sed -i 's/\/home\/knote:\/bin\/sh/\/home\/knote:\/home\/knote\/run\.sh/' /etc/passwd 
COPY ./share /home/knote
RUN chmod 774 /tmp
RUN chmod -R 774 /var/tmp
RUN chmod -R 774 /dev
RUN chmod -R 774 /run
RUN chmod 1733 /tmp /var/tmp /dev/shm
RUN chown -R root:root /home/knote
RUN mkdir /run/sshd
CMD ["/usr/sbin/sshd", "-D"]
