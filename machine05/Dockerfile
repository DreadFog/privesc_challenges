FROM alpine:3.7
# Create user underprivileged with password underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
#install sudo
RUN apk add sudo
# set a complex root password
RUN echo "root:7kuGUK]41n!" | chpasswd
# copy the source code of the password manager 
COPY password-manager.c /home/underprivileged/password-manager.c
# compile the password manager
RUN gcc -o /home/underprivileged/password-manager /home/underprivileged/password-manager.c
# remove the source code of the password manager
RUN rm /home/underprivileged/password-manager.c
# copy the flag to the /root directory
COPY flag.txt /root

