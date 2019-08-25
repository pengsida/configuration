## Introduction

General graph neural network

1. Input: a graph = {V, E}, where V and E are the sets of nodes and edges.
2. For each node v, we have a input feature vector and a hidden state at time step t.
3. Graph neural network is a dynamic model. During evolution, we use a function to compute the message that node v receives from its neighbors, and then update the node's hidden state.
4. The final prediction can be at the node or at the graph level.

## Variants of GNNs

1. Graph convolutional networks, GraphSAGE: [Tutorial](http://snap.stanford.edu/proj/embeddings-www/files/nrltutorial-part2-gnns.pdf)
2. Message aggregation functions: [ResEdgeConv, ResGIN, ResGraphSAGE, ResMRGCN](https://docs.google.com/presentation/d/1L82wWymMnHyYJk3xUKvteEWD5fX0jVRbCbI65Cxxku0/edit#slide=id.g56294d0603_0_531)

