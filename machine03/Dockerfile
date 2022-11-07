FROM alpine:3.7
# Create user underprivileged with password underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
#install sudo
RUN apk add sudo
# set root password to larisa : password can be found in the rockyou.txt database line 3300
RUN echo "root:larisa" | chpasswd
# allow /etc/passwd to be read by everyone
RUN chmod 644 /etc/passwd
# allow /etc/shadow to be read by everyone : this is a security risk!
RUN chmod 644 /etc/shadow
# copy the flag to the /root directory
COPY flag.txt /root

