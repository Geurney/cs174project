# cs174project
Encrypted Database Aggregation UDF

## Usage
### MySQL Server
* After logging in the MySQL Server instance, download the build.sh script:
```
  wget https://raw.githubusercontent.com/Geurney/cs174project/release/build.sh 
```
* Then run the script: 
```
  sudo bash build.sh
```
* Configuration
```
  cd cs174project/udf
  sudo -s
  bash udf.sh
  mysql -u root --password="cs174\$" -e "GRANT ALL ON project.* TO MaLi@'ClientIP' IDENTIFIED BY 'cs174\$';"
```

### Client
* After logging in the Client instance, download the build-client.sh script:
```
  wget https://raw.githubusercontent.com/Geurney/cs174project/release/build-client.sh 
```
* Then run the script: 
```
  sudo bash build-client.sh
```
* Configuration
```
  cd cs174project/client
  sudo -s
  In main.c, change the host to Server IP, user name as MaLi.
  make
```
*  Generate Key
```
  ./genkey
  Copy pubkey to server as ~/cs174project/udf/pubkey
```
* Start Client
```
  ./main
```
## [Install GMP on CentOS](https://opensourcedbms.com/dbms/installing-mysql-5-6-on-cent-os-6-3-redhat-el6-fedora/)
```
  wget http://dev.mysql.com/get/Downloads/MySQL-5.6/MySQL-shared-5.6.14-1.el6.x86_64.rpm
  wget http://dev.mysql.com/get/Downloads/MySQL-5.6/MySQL-client-5.6.14-1.el6.x86_64.rpm
  rpm -ivh MySQL-shared-5.6.14-1.el6.x86_64.rpm
  rpm -ivh MySQL-client-5.6.14-1.el6.x86_64.rpm
```
