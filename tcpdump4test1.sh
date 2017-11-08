#!/bin/bash


PORT_NUMBER=12721
CLIENT_HOST_NAME=uw1-320-00


echo "tcpdump -vtt host $CLIENT_HOST_NAME and port $PORT_NUMBER and tcp > test1.out"
tcpdump -vtt host $CLIENT_HOST_NAME and port $PORT_NUMBER and tcp > test1.out


