#!/bin/bash
# Install GMP
echo 'Installing GMP...This may take a while.'
wget -q  https://gmplib.org/download/gmp/gmp-6.1.0.tar.bz2
tar jxf gmp-6.1.0.tar.bz2 > /dev/null
cd gmp-6.1.0
apt-get -y install m4 > /dev/null
./configure --prefix="/usr" > /dev/null
apt-get -y install make > /dev/null
make &> /dev/null
make install &> /dev/null
cd ..
rm gmp-6.1.0.tar.bz2
# Git Clone
echo 'Cloning git repo...'
apt-get -y install git > /dev/null
git clone -q -b release https://github.com/Geurney/cs174project.git
git config --global user.name "Geurney"
git config --global user.email dongqiao.ma@gmail.com
git config --global push.default simple
# Install MySql C API needed libraries
echo 'Installing MySql C API libraries...'
apt-get -y install libmysqlclient-dev > /dev/null
apt-get -y install zlib1g-dev > /dev/null
echo 'Done!'
