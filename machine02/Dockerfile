FROM alpine:3.7
# Create user underprivileged with password underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
#install sudo
RUN apk add sudo
# set a complex root password
RUN echo "root:7kuGUK]41n!" | chpasswd
# copy the flag to the /root directory
COPY flag.txt /root
# copy the script to the opt directory
COPY empty_tmp.sh /opt/
# make the script writable by everyone : this is a bad idea! 
RUN chmod 777 /opt/empty_tmp.sh
# execute the script every minute as a cron job
RUN echo "* * * * * /opt/empty_tmp.sh" >> /etc/crontabs/root
# make /etc/crontabs/root readable by everyone: this is a security risk!
RUN chmod 644 /etc/crontabs/root
# start the cron service TODO: doesnt work
CMD ["/entry.sh"]

