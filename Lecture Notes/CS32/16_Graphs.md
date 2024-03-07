# Graphs
A graph is an ADT that stores a set of entities and also tracks the relationships between them. 

**Nodes**: Represent our entities. They can be anything - some type of object you create.
**Edges**: Represent our relationships. Relationships can be bidirectional (friends) or unidirectional (one-way) and also have attributes (like a weight associated to them).

Different Types of Graphs
- Directed Graph: edges are unidirectional, going from one node to another only in that specific direction
- Undirected Graph: all edges are bidirectional, you can go either way along a given edge

## Representation of Graphs

### 2-D Array and the Adjacency Matrix Method
An easy way to represent graphs is a 2-dimensional array. The size of both dimensions of the array is going to be equal to the number of nodes in the graph. For example, if there are
5 nodes in your graph, instantiating it would look like `bool graph[5][5];`. Each element in your array will indicate whether or not there is an edge between vertex i and vertex j. Whenever
you set `array[i][j]` to true, it represents a **directed** edge from vertex i to vertex j. This is called an **adjacency matrix**. (If you want to represent an undirected graph, that just
means that if there is a given edge between nodes i and j then `array[i][j] = true;` and `array[j][i] = true;` as well. This will make the matrix symmetrical with respect to the diagonal)

**The Neato Effect**: An interesting property of the adjacency matrix is when you multiply the matrix by itself once, it will show you which nodes are exactly two edges apart. If you
multiply it by itself again, it will show you which nodes are 3 edges apart.

### Map and Adjacency List Method
You can represent a directed graph by using a map that associates each source node with a list of its adjacent nodes: `map<int, list<int>> node_to_neighbors;`. Performing the operation
`node_to_neighbors[src].push_back(target);` indicates that there is an edge from vertex src to vertex target. This is alled an **adjacency list**.

## Deciding on which representation to use
You want to use whatever option costs the less. For example, take the following scenarios...

**Scenario 1: you've got 10 million users where each user is friends with a few hundred other people.**

Option A: Adjacency Matrix (Cost: a 10 million by 10 million adjacency matrix would be 100 trillion cells)

Option B: Adjacency List (Cost: 10 million linked lists, each holding 500 items per say, would be 5 billion items)

Clearly option B is more efficient!

**Scenario 2: We've got 1,000 cities, with airlines offering flights from every city to almost every other city.

Option A: Adjacency Matrix (Cost: a 1,000 by 1,000 adjacency matrix would be 1 million cells)
Option B: Adjacency List (Cost: 1,000 linked lists, each holding roughly 1000 items would be 1 million items)

Both options are the same size. So in this situation, pick the easier one to implement.


