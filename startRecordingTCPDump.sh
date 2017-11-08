#!/bin/bash

SERVER_HOST_NAME=uw1-320-00
PORT_NUMBER=12721


tcpdump -vtt host $SERVER_HOST_NAME and port $PORT_NUMBER and tcp  > tcpdump.out 
