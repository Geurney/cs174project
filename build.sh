#!/bin/bash
# Modify /etc/mysql/my.cnf
echo 'Configuring MySql...'
private_ip=`ifconfig | head | awk '/inet addr/{print substr($2,6)}'`
perl -i -pe "s/127.0.0.1/$private_ip/g" /etc/mysql/my.cnf
/etc/init.d/mysql restart > /dev/null
echo "Creating Test Database..."
mysql -u root --password="cs174\$" -e "DROP DATABASE IF EXISTS test; CREATE DATABASE test; GRANT ALL ON test.* TO DQ@'ResNet-6-228.resnet.ucsb.edu' IDENTIFIED BY 'cs174\$'; USE test; CREATE TABLE users(id INTEGER, name TEXT, password TEXT, PRIMARY KEY (id)); INSERT INTO users VALUES (1 ,'Dongqiao Ma', '100'); INSERT INTO users VALUES (2 ,'Yanying Li', '200'); INSERT INTO users VALUES (3 ,'Talor Swift', '300'); SELECT * FROM users;"
# Install GMP
echo 'Installing GMP...This may take a while.'
wget -q  https://gmplib.org/download/gmp/gmp-6.1.0.tar.bz2
tar jxf gmp-6.1.0.tar.bz2 > /dev/null
cd gmp-6.1.0
apt-get -y install m4 > /dev/null
./configure > /dev/null
apt-get -y install make > /dev/null
make &> /dev/null
make install &> /dev/null
cd ..
rm gmp-6.1.0.tar.bz2
# Git Clone
echo 'Cloning git repo...'
apt-get -y install git > /dev/null
git clone -q https://github.com/Geurney/cs174project.git
git config --global user.name "Geurney"
git config --global user.email dongqiao.ma@gmail.com
git config --global push.default simple
# Install MySql C API needed libraries
echo 'Installing MySql C API libraries...'
apt-get -y install libmysqlclient-dev > /dev/null
apt-get -y install zlib1g-dev > /dev/null
echo 'Done!'
