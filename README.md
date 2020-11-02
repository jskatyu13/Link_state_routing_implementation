# Link_state_routing_implementation
This program contains a program, mylinkstate, for a
link-state-routing algorithms to determine the shorest
distance from a target node to all other nodes.  The 
dijkstra algorithm is implemented in the program to solove 
this routing problem.  The program reads the node information
from specific testing cases (test10nodes and test100nodes
in the testing stage) to convert into a 2D array which can
be used to calculate the node-to-node shortest distance.
The immediate and final results are shown under flag seletion,
where flag 0 would only show the forwarding table and total 
execution time in ms, and flag 1 would also show the steps
for the dijkstra algorithms for routing problem.
