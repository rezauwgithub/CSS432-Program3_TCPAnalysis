#!/bin/bash




SERVER_HOST_NAME=$1
PORT_NUMBER=$2


function pause() {
  read -p "$*"
}


pause 'Stop the server, if it is running, and Start it again with the -D flag. Press the "Enter" key here when done...'

echo "Processing script Test2 with -D..."
echo "./test2with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test2with-D.out"
./test2with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test2with-D.out

echo "Processing script Test4 with -D..."
echo "./test4with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test4with-D.out"
./test4with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test4with-D.out

echo "Processing script Test5 with -D..."
echo "./test5with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test5with-D.out"
./test5with-D.sh $SERVER_HOST_NAME $PORT_NUMBER &> test5with-D.out


pause 'Stop the server, if it is running, and Start it again WITHOUT the -D flag. Press the "Enter" key here when done...'

echo "Processing script Test2..."
echo "./test2.sh $SERVER_HOST_NAME $PORT_NUMBER &> test2.out"
./test2.sh $SERVER_HOST_NAME $PORT_NUMBER &> test2.out

echo "Processing script Test4..."
echo "./test4.sh $SERVER_HOST_NAME $PORT_NUMBER &> test4.out"
./test4.sh $SERVER_HOST_NAME $PORT_NUMBER &> test4.out

 echo "Processing script Test5..."
 echo "./test5.sh $SERVER_HOST_NAME $PORT_NUMBER &> test5.out"
./test5.sh $SERVER_HOST_NAME $PORT_NUMBER &> test5.out


pause 'Stop the server, if it is running, and Start it again with the -D flag. Run tcpdump also, and then press the "Enter" key here when done...'

echo "Processing script Test3 ..."
echo "./test3.sh $SERVER_HOST_NAME $PORT_NUMBER &> test3.out"
./test3.sh $SERVER_HOST_NAME $PORT_NUMBER &> test3.out