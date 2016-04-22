import os


from sys import stdin



lnum = 0
words = os.popen("wc out.txt")
headntail = os.popen("(head -n1 && tail -n1) < out")
for word in words:
    lnum = int(word[2:4])

delay = []
for line in headntail:
    delay.append(float(line[:-1].split(" ")[2][:-1]))
delay = delay[1] - delay[0]
throughput = (1024 * lnum) / delay

print(throughput)
    
