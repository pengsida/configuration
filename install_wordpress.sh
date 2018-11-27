#!/bin/bash

# 1. install LAMP according to http://blog.topspeedsnail.com/archives/4635
# 2. install WordPress according to http://blog.topspeedsnail.com/archives/4646

sudo apt-get install -y mariadb-server mariadb-client
sudo mysql_secure_installation
# Enter current password for root (enter for none): <-- 回车
# Set root password? [Y/n] <-- y
# New password: <-- 设置新root密码
# Re-enter new password: <-- 重复输入密码
# Remove anonymous users? [Y/n] <-- y
# Disallow root login remotely? [Y/n] <-- y
# Reload privilege tables now? [Y/n] <-- y

sudo mysql -u root -p
# quit

sudo apt-get install -y apache2
sudo apt-get install -y php7.0 libapache2-mod-php7.0
sudo systemctl restart apache2
sudo apt-get install -y php7.0-mysql php7.0-curl php7.0-gd php7.0-intl php-pear php-imagick php7.0-imap php7.0-mcrypt php-memcache  php7.0-pspell php7.0-recode php7.0-sqlite3 php7.0-tidy php7.0-xmlrpc php7.0-xsl php7.0-mbstring php-gettext php7.0-zip php-ssh2
sudo systemctl restart apache2

sudo apt-get install php-apcu
sudo systemctl restart apache2

sudo a2enmod ssl
sudo a2ensite default-ssl
sudo systemctl restart apache2

sudo apt-get install phpmyadmin
# Web server to configure automatically: <-- 选择 apache2
# Configure database for phpmyadmin with dbconfig-common? <-- Yes
# MySQL application password for phpmyadmin: <-- 直接回车创建一个随机密码
sudo echo "update user set plugin='' where User='root'; flush privileges;" | sudo mysql --defaults-file=/etc/mysql/debian.cnf mysql
sudo ln -s /usr/share/phpmyadmin /var/www/html

# Then install WordPress according to http://blog.topspeedsnail.com/archives/4646

