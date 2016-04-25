#!/usr/bin/python3

import os


#from sys import stdin

lnum = 0
words = os.popen("wc out.txt")
headntail = os.popen("(head -n1 && tail -n1) < out.txt")
for word in words:
  #lnum = int(word.split(" ")[1])
  list = word.split(" ")
  newList = []
  for elem in list:
    if elem != '':
      newList.append(elem)
  lnum = int(newList[0])

delay = []
for line in headntail:
  delay.append(float(line[:-1].split(" ")[2][:-1]))
delay = delay[1] - delay[0]
throughput = (1024 * lnum) / delay
#throughput = (lnum) / delay
print(throughput)
#print(delay)    
