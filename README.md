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
  sudo bash udf.sh
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
