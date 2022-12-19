mkdir /opt
gcc -o /opt/manage_accounts /home/accountant/banking.c
chown root:root /opt/manage_accounts && chmod u+s /opt/manage_accounts