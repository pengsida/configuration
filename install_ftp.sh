!/bin/bash

sudo apt-get install vsftpd

sudo vi /etc/vsftpd.conf

# userlist_deny=NO
# userlist_enable=YES
# userlist_file=/etc/allowed_users
# seccomp_sandbox=NO
# local_root=/home/uftp/
# local_enable=YES
# write_enable=YES
# utf8_filesystem=YES

sudo vi /etc/allowed_users
sudo service vsftpd restart

