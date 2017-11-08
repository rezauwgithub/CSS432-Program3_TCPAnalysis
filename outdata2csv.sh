#!/bin/bash



cat test2.out | grep ttcp-rbyte > test2.txt
cat test2with-D.out | grep ttcp-rbyte > test2with-D.txt
cat test3.out | grep ttcp-rbyte > test3.txt
cat test4.out | grep ttcp-rbyte > test4.txt
cat test4with-D.out | grep ttcp-rbyte > test4with-D.txt
cat test5.out | grep ttcp-rbyte > test5.txt
cat test5with-D.out | grep ttcp-rbyte > test5with-D.txt


for file in test2.txt test2with-D.txt test3.txt test4.txt test4with-D.txt test5.txt test5with-D.txt;
do
  sed -i -e 's/ttcp-rbytes=//g' "${file}"    #Replace all "ttcp-rbyte=" with ""
  sed -i -e 's/ time=/,/g' "${file}"          #Replace all " time=" with ","
  sed -i -e 's/ Mbps=/,/g' "${file}"          #Replace all " Mbps=" with ","
  sed -i -e 's/ I\/Ocalls=/,/g' "${file}"      #Replace all " I/Ocalls=" with ","
  
  echo 'ttcp-rbytes,time,Mbps,I/O calls' | cat - "${file}" > tmp && mv tmp "${file}"
  
  mv "${file}" "${file/%.txt/.csv}"
     
done





