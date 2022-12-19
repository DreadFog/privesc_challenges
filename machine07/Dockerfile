FROM alpine:3.7
RUN apk add sudo
RUN apk add gcc
RUN apk add musl-dev
# underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
COPY welcome.txt /home/underprivileged/
RUN echo "underprivileged ALL=(accountant) NOPASSWD: /usr/bin/vi /home/accountant/user_info/underprivileged.info" >> /etc/sudoers
# root
RUN echo "root:7kuGUK]41n!" | chpasswd
COPY flag.txt /root
# accountant
RUN adduser -D accountant && echo "accountant:kGI%401f&" | chpasswd
COPY password_for_app.txt /home/accountant/
COPY user_info /home/accountant/user_info/
COPY user.txt /home/accountant/
COPY banking.c /home/accountant/
COPY bank /var/log/bank
COPY entry.sh /entry.sh
# create the opt directory and copile the banking app
RUN mkdir /opt
RUN gcc /home/accountant/banking.c -o /opt/manage_accounts
RUN chown root:root /opt/manage_accounts && chmod u+s /opt/manage_accounts

