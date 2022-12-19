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
# copy the crontab 
COPY crontab /etc/crontab
# run cron
RUN crontab /etc/crontab
RUN touch /var/log/cron.log
# start the cron service TODO: doesnt work
# copy the start script
COPY entry.sh /entry.sh
# make the script executable
RUN chmod +x /entry.sh
CMD ["/entry.sh"]

