#!/bin/bash
# Modify /etc/mysql/my.cnf
private_ip=`ifconfig | head | awk '/inet addr/{print substr($2,6)}'`
perl -i -pe "s/127.0.0.1/$private_ip/g" /etc/mysql/my.cnf
/etc/init.d/mysql restart
mysql -u root --password="cs174\$" -e "DROP DATABASE IF EXISTS mytest; CREATE DATABASE mytest; GRANT ALL ON mytest.* TO DQ@'ResNet-6-228.resnet.ucsb.edu' IDENTIFIED BY 'cs174\$'; USE mytest; CREATE TABLE MyTable(id INTEGER, content TEXT, PRIMARY KEY (id)); INSERT INTO MyTable VALUES (1 ,'Hello There'); INSERT INTO MyTable VALUES (2 ,'How are you'); INSERT INTO MyTable VALUES (3 ,'I am fine'); SELECT * FROM MyTable;"
# Install GMP
wget https://gmplib.org/download/gmp/gmp-6.1.0.tar.bz2
tar jxf gmp-6.1.0.tar.bz2
cd gmp-6.1.0
apt-get -y install m4
./configure
apt-get -y install make
make
make install
cd ..
rm gmp-6.1.0.tar.bz2
# Git Clone
apt-get -y install git
git clone https://github.com/Geurney/cs174project.git
cd cs174project
# Install MySql C API needed libraries
apt-get -y install libmysqlclient-dev
apt-get -y install zlib1g-dev
