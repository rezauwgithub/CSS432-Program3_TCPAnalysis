#!/bin/bash




SERVERHOSTNAME=$1
PORTNUMBER=$2

MESSAGELENGTH=64
NUMBERMESSAGES=1048576

for TRYNUMBER in 1 2 3 4 5 6 7 8 9 10
do

    echo "Processing Try Number:" $TRYNUMBER 
		echo "MESSAGELENGTH:" $MESSAGELENGTH 
		echo "NUMBERMESSAGE:" $NUMBERMESSAGE
  
  
    netstat -st | grep segments
    
    ./ttcp -t -l$MESSAGELENGTH -n$NUMBERMESSAGE $SERVERHOSTNAME -p$PORTNUMBER > /dev/null
    
    netstat -st | grep segments
    
    
    echo ""
    
done


