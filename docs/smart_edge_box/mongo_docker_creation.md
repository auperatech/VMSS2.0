1. Please pull the docker image of `mongo` at first

```
docker pull mongo:5.0.9
```
```
sudo docker run -itd --name mongo -p 27017:27017 mongo:5.0.9
```

2. Compile the sample code

```
make
```
3. Connect to the database and test

```
./mongo_client "mongodb://172.16.1.7:27017" "test_db" "test_collection"
```
