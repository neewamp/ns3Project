# ns3Project
Swathi and nathan's ns3 repo.

Data Rate is 100mbps forall graphs except the ones with varying data rate.

Throughput is in bytes/s.
=======
Throughput for these graphs is in bytes/s.
=======

This was generated with csmaTest.cc using multiple application containers and will probably be changed when we use another method for how many nodes are in the network.

![application container](graphData/csma3Nodes.png)

This is the method we think is correct it uses a for loop to install nodes. 
![ForLoop](graphData/csma1Withloop.png)


This is a graph for tdma with 3 nodes and varying packet sizes.

![tdmapacketsize](graphData/tdma3NodesVaryingPacketsSize.png)

Graph for tdma with varying nodes and a fixed packet size at 1024 bytes.

![tdmaVaryingNodes](graphData/tdma1024VaryingNodes.png)

Graph for csma with varying nodes and a fixed packet size of 1024 bytes.

![csmaVaryingNodes](graphData/csma1024VaryingNodes.png)

Graph for csma with varying data rates.

![csmaVaryingDataRate](graphData/csmaVaryingDataRate.png)

Graph for tdma with varying data rates.

![tdmaVaryingDataRate](graphData/tdma3VaryingDataRate.png)