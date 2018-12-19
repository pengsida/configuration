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

sudo apt-get install -y php-apcu
sudo systemctl restart apache2

sudo a2enmod ssl
sudo a2ensite default-ssl
sudo systemctl restart apache2

sudo apt-get install -y phpmyadmin
# Web server to configure automatically: <-- 选择 apache2
# Configure database for phpmyadmin with dbconfig-common? <-- Yes
# MySQL application password for phpmyadmin: <-- 直接回车创建一个随机密码
sudo echo "update user set plugin='' where User='root'; flush privileges;" | sudo mysql --defaults-file=/etc/mysql/debian.cnf mysql
sudo ln -s /usr/share/phpmyadmin /var/www/html

# Then, install WordPress according to http://blog.topspeedsnail.com/archives/4646

sudo mysql -u root -p
# Enter password:
# MariaDB [(none)]> CREATE DATABASE wordpress;
# MariaDB [(none)]> GRANT ALL ON wordpress.* TO 'myword'@'localhost' IDENTIFIED BY 'test1234';
# MariaDB [(none)]> FLUSH PRIVILEGES;
# MariaDB [(none)]> quit

echo '' | sudo tee -a /etc/apache2/apache2.conf
echo '<Directory /var/www/html/>' | sudo tee -a /etc/apache2/apache2.conf
echo '    AllowOverride All' | sudo tee -a /etc/apache2/apache2.conf
echo '</Directory>' | sudo tee -a /etc/apache2/apache2.conf
echo '' | sudo tee -a /etc/apache2/apache2.conf

sudo a2enmod rewrite
sudo apache2ctl configtest
sudo systemctl restart apache2

cd /tmp
wget https://cn.wordpress.org/wordpress-5.0.1-zh_CN.tar.gz
tar xzvf wordpress-5.0.1-zh_CN.tar.gz
touch /tmp/wordpress/.htaccess
chmod 660 /tmp/wordpress/.htaccess
cp /tmp/wordpress/wp-config-sample.php /tmp/wordpress/wp-config.php

sudo rm -rf /var/www/html/*
sudo cp -a /tmp/wordpress/. /var/www/html
sudo chown -R root:www-data /var/www/html
sudo chmod 777 -R /var/www/html

cd /var/www/html
sed -i '/\<DB_NAME\>/s/database_name_here/wordpress/g' wp-config.php
sed -i '/\<DB_USER\>/s/username_here/myword/g' wp-config.php
sed -i '/\<DB_PASSWORD\>/s/password_here/test1234/g' wp-config.php

echo "" | sudo tee -a wp-config.php
echo "define('FS_METHOD', 'direct');" | sudo tee -a wp-config.php
echo "" | sudo tee -a wp-config.php

sed -i '/\<AUTH_KEY\>/s/^/\/\/ /' wp-config.php
sed -i '/\<SECURE_AUTH_KEY\>/s/^/\/\/ /' wp-config.php
sed -i '/\<LOGGED_IN_KEY\>/s/^/\/\/ /' wp-config.php
sed -i '/\<NONCE_KEY\>/s/^/\/\/ /' wp-config.php
sed -i '/\<AUTH_SALT\>/s/^/\/\/ /' wp-config.php
sed -i '/\<SECURE_AUTH_SALT\>/s/^/\/\/ /' wp-config.php
sed -i '/\<LOGGED_IN_SALT\>/s/^/\/\/ /' wp-config.php
sed -i '/\<NONCE_SALT\>/s/^/\/\/ /' wp-config.php

curl -s https://api.wordpress.org/secret-key/1.1/salt/ | sudo tee -a wp-config.php
echo "" | sudo tee -a wp-config.php

