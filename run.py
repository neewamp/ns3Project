#!/usr/bin/python3 
import os
out = open('ns3Project/graphData/newGraphs/delayPacketSize/Csma','w')

for i in range(1,50):
   # i /= 10
    i *= 1024#Use me for packet size
    inp = open('in.txt','w')
    print(str(i), file=inp ,end='')
    throughput = os.popen("./waf --run csmaTest <in.txt 2>&1 > /dev/null | grep 'received' > out.txt ;./through.py")
    through = 0
    for line in throughput:
        through = line
    if through != 0:
        print(str(i), through, file=out, end='')

#os.system("cut output.txt -c3- | cat > output.txt")
