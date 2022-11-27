FROM alpine:3.7
# Create user underprivileged with password underprivileged
RUN adduser -D underprivileged && echo "underprivileged:underprivileged" | chpasswd
#install sudo
RUN apk add sudo
# set a complex root password
RUN echo "root:7kuGUK]41n!" | chpasswd
# install python3
RUN apk add python3
# Copy the poem to the /root directory
COPY poem.txt /root 
#make the poem readable by only root
RUN chmod 400 /root/poem.txt
# copy the python script motivational_quote.py to /home/underprivileged/
COPY motivational_quote.py /home/underprivileged/
# make the python script executable by everyone
RUN chmod 755 /home/underprivileged/motivational_quote.py
# allow underprivileged user to execute the python script as root
RUN echo " underprivileged ALL=(root) NOPASSWD: /usr/bin/python3 /home/underprivileged/motivational_quote.py" >> /etc/sudoers
# copy the flag to the /root directory
COPY flag.txt /root

