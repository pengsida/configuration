!/bin/bash

sudo apt-get install vsftpd

sudo vi /etc/vsftpd.conf

# userlist_deny=NO
# userlist_file=/etc/vsftpd.userlist
# local_root=/mnt/ftp/
# local_enable=YES
# write_enable=YES
# utf8_filesystem=YES
# allow_writeable_chroot=YES
# local_umask=0002

sudo vi /etc/vsftpd.userlist
# add users into /etc/vsftpd.userlist
sudo service vsftpd restart

# change ftp commands for a specific user
# authority list: https://en.wikipedia.org/wiki/List_of_FTP_commands
# user_config_dir=/etc/vsftpd_user_conf
# add a user file like /etc/vsftpd_user_conf/pengsida
# write allowed commands in the user file: cmds_allowed=ABOR,CWD,LIST,MDTM,MKD,NLST,PASS,PASV,PORT,PWD,QUIT,RETR,RNFR,RNTO,SIZE,STOR,TYPE,USER,REST,CDUP,HELP,MODE,NOOP,REIN,STAT,STOU,STRU,SYST,FEAT
# or write denied commands in the user file: cmds_denied=DELE,RNFR,RNTO,XRMD,RMD

# forbid ftp user to login server via ssh
# sudo usermod -s /usr/sbin/nologin username
# add /usr/sbin/nologin into /etc/shells

# add anonymous user
# anonymous_enable=YES
# anon_root=/mnt/ftp

