### Please follow the steps to run and test the MongoDB server


1. On the host device, pull and run the docker image of `mongo`. After successfully running this step, a MongoDB server with <local_ip_address>:27019 will be running.

```
docker pull mongo:5.0.9
sudo docker run -itd --name mongo -p 27019:27017 mongo:5.0.9
```

2. Download the [sample code](https://auperatechvancouver.sharepoint.com/:u:/g/EWre-78TGFhCrsmA6juDm1IB4jVoxW4QyukLc2L5WHKU5Q?e=aNEHt9) and put it inside the Aupera smart edge box docker. Then, unzip and compile the sample code inside the docker. A sample code program `mongo_client` will be generated.

```
unzip 08.mongodb_client
cd 08.mongodb_client
make
```

3. Inside the Aupera smart edge box docker, run the following command to test with the `mongo_client` (replace the <local-ip-address> with the actual local IP address). This program will connect to the MongoDB server and send test notifications to the "test_db" database and "test_collection" collection.  

```
./mongo_client "mongodb://<local-ip-address>:27019" "test_db" "test_collection"
```


4. It proves that the MongoDB server is set up correctly on the host and all the needed files for the mongo_notification node are inside the docker if you the following contents are shown after executing step 3

```
Insert success
Insert success
{ "_id" : "control_port_58881_0", "number" : { "$numberInt" : "0" }, "string" : "test string", "vector" : [ [ { "$numberInt" : "1" }, { "$numberInt" : "2" } ], [ { "$numberInt" : "3" }, { "$numberInt" : "4" } ], [ { "$numberInt" : "5" }, { "$numberInt" : "6" } ] ] }
{ "_id" : "control_port_58881_1", "number" : { "$numberInt" : "1" }, "string" : "test string", "vector" : [ [ { "$numberInt" : "1" }, { "$numberInt" : "2" } ], [ { "$numberInt" : "3" }, { "$numberInt" : "4" } ], [ { "$numberInt" : "5" }, { "$numberInt" : "6" } ] ] }
count of all = 2
count of {"number":1} = 1
update success
{ "_id" : "control_port_58881_0", "number" : { "$numberInt" : "0" }, "string" : "test string", "vector" : [ [ { "$numberInt" : "1" }, { "$numberInt" : "2" } ], [ { "$numberInt" : "3" }, { "$numberInt" : "4" } ], [ { "$numberInt" : "5" }, { "$numberInt" : "6" } ] ] }
{ "_id" : "control_port_58881_1", "number" : { "$numberInt" : "1" }, "string" : "update string", "vector" : [ [ { "$numberInt" : "1" }, { "$numberInt" : "2" } ], [ { "$numberInt" : "3" }, { "$numberInt" : "4" } ], [ { "$numberInt" : "5" }, { "$numberInt" : "6" } ] ], "update_flag" : true }

```
