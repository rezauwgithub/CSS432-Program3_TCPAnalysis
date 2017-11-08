#!/bin/bash




SERVER_HOST_NAME=$1
PORT_NUMBER=$2

MESSAGE_LENGTH=64
NUMBER_MESSAGES=1048576

for TRYNUMBER in 1 2 3 4 5 6 7 8 9 10
do

    echo "Processing Try Number with -D:" $TRY_NUMBER 
		echo "MESSAGE LENGTH:" $MESSAGE_LENGTH 
		echo "NUMBER MESSAGE:" $NUMBER_MESSAGE
  
  
    netstat -st | grep segments
 
   echo "./ttcp -t -l$MESSAGE_LENGTH -n$NUMBER_MESSAGE $SERVER_HOST_NAME -p$PORT_NUMBER -D > /dev/null"
    ./ttcp -t -l$MESSAGE_LENGTH -n$NUMBER_MESSAGE $SERVER_HOST_NAME -p$PORT_NUMBER -D > /dev/null
    
    netstat -st | grep segments
    
    
    echo ""
    
done


