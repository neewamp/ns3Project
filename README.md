# ns3Project
Swathi and nathan's ns3 repo.

CSMA code is implemented in two ways , "for" loop or the application container. We are getting different outputs for the two methods.
Please can we know What is the purpose of application container?. We are not able to figure out the difference between using multiple application containers and a for loop for installing nodes.

We think that using the method - for loop in csma.cc is the correct way to do it. This is because when increasing the number of nodes using two application containers the throughput went up.  With the for loop method in csma.cc throughput went down as expected.

This was generated with csmaTest.cc using multiple application containers and will probably be changed when we use another method for how many nodes are in the network.

![application container](graphData/csma3Nodes.png)
![ForLoop](graphData/csma1Withloop.png)