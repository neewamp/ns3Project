import os
out = open('ns3Project/graphData/newGraphs/','w')

for i in range(1,30):
    
    inp = open('in.txt','w')
    #print(inp.readlines())
    print(str(i), file=inp,end='')
    throughput = os.popen("./waf --run firstTdma <in.txt 2>&1 > /dev/null | grep 'received' > out.txt ;./through.py")
    through = 0
    for line in throughput:
        through = line
        #print(through)
    print(str(i), through, file=out, end='')

#os.system("cut output.txt -c3- | cat > output.txt")
