FROM alpine:3.7
# Create user underprivileged with password underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
# set a complex root password
RUN echo "root:7kuGUK]41n!" | chpasswd
#install sudo
RUN apk add sudo
# allow underprivileged user to run /usr/bin/vi as root
RUN echo "underprivileged ALL=(root) NOPASSWD: /usr/bin/vi" >> /etc/sudoers
# copy the flag to the /root directory
COPY flag.txt /root

