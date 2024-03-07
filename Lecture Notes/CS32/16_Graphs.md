# Graphs
A graph is an ADT that stores a set of entities and also tracks the relationships between them. 

**Nodes**: Represent our entities. They can be anything - some type of object you create.
**Edges**: Represent our relationships. Relationships can be bidirectional (friends) or unidirectional (one-way) and also have attributes (like a weight associated to them).

Different Types of Graphs
- Directed Graph: edges are unidirectional, going from one node to another only in that specific direction
- Undirected Graph: all edges are bidirectional, you can go either way along a given edge

## Representation of Graphs

### 2-D Array and Adjacency Matrix Method
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
- Option A: Adjacency Matrix (Cost: a 10 million by 10 million adjacency matrix would be 100 trillion cells)
- Option B: Adjacency List (Cost: 10 million linked lists, each holding 500 items per say, would be 5 billion items)

Clearly option B is more efficient!

**Scenario 2: We've got 1,000 cities, with airlines offering flights from every city to almost every other city.**
- Option A: Adjacency Matrix (Cost: a 1,000 by 1,000 adjacency matrix would be 1 million cells)
- Option B: Adjacency List (Cost: 1,000 linked lists, each holding roughly 1000 items would be 1 million items)

Both options are the same size. So in this situation, pick the easier one to implement.

### For a more systematic approach to deciding which representation to use...
- Use an **Adjacency Matrix** if you have a **dense** graph - a lot of edges between a few nodes (< 10,000 nodes).
  Ex. Caltech student friendships on Facebook
- Use an **Adjacency List** if you have a **sparse** graph - a few edges between nodes and a lot of nodes (> 10,000 nodes)
  Ex. High-school dating habits, Intra-website links, Street maps

## Trees vs. Graphs
Trees never have cycles while graphs may have cycles. This will make graph traversals a bit more difficult.

We have two ways of traversing through graphs:
1. **Depth-First**: Keep moving forward until hitting a dead-end or a previously-visited vertex...then backtracks and tries another path.

Implementation using traversal. Is similar to pre-order tree traversal.
```
void depth_first(map<int, list<int>> &graph, int cur_vertex, set<int>& visited) {
  if (visited.find(cur_vertex) != visited.end())
    return;

  visited.insert(cur_vertex);

  cout << "Process " << cur_vertex << "!" << endl;

  list<int>::iterator it;
  for (it = graph[cur_vertex].begin(); it != graph[cur_vertex].end(); it++)
    depth_first(graph, *it, visited);
} 
```
Implementation using a stack (_in pseudocode_).
```
Depth-First-Search-With-Stack(start_room)
  Push start_room on the stack
  While the stack is not empty...
    Pop the top item off the stack and put in variable c
    If c hasn't been visited yet...
      Drop a breadcrumb (we've visited the current room)
        For each door d leaving the room...
        If the room r behind door d hasn't been visited
          Push r onto the stack.  
```
2. **Breadth-First**: Explore the graph in growing concentric circles, exploring all vertices 1 away from the start, then 2 away, then 3 away, etc.

Implementation using queue
```
Breadth-First-Search(startVertex) {
  Add the starting vertex to our queue
  Mark the starting vertex as "discovered"
  While the queue is not empty...
    Dequeue the top vertex from the queue and place in c
    Process vertex c (e.g. print its contents out)
    For each vertex v directly reachable from c
      If v has not yet been "discovered"
        Mark v as "discovered"
        Insert vertex v into the queue
}
```
## Graphs with weighted edges and Dijkstra's Algorithm

Dijkstra's Algorithm takes a graph in as input along with a starting node. It will then output the optimal distances from the starting node to every other node in the graph.

**How it works**: I personally learned it before using the following video (https://www.youtube.com/watch?v=XB4MIexjvY0&t=820s) but here is the gist...

1. Create two distinct sets to separate the nodes:
  - **Unsettled nodes**: Nodes that we don't know the optimal distance to from the starting node
  - **Settled nodes**: Nodes that we do know the optimal distance to from the starting node

     _All nodes will start out as unsettled, and the algorithm will finish once all the nodes are in the settled set._

2. Assume all nodes are infinitely far away at first. Starting at the starting node, fill in the distance for reaching itself (which should be zero).
3. See which unsettled nodes you can reach directly from the node you are on and fill in the distances to reach them. Add them to the settled list.
4. Travel/Go to the settled node that is closest to you.
5. Repeat process 3 and 4 until all nodes are settled.

### Implementing Dijktra's Algorithm
The implementation uses 2 data structures:
1. An array called "Dist" that holds the current best known cost to get from the starting node to every other node in the graph
   - Each node `i` in `Dist[i]` starts out with a value of
     - 0 if it is the starting node
     - Infinity for all other nodes
2. An array called "Done" that holds `true` for each node that has been fully processed, and `false` otherwise.
   - Each node `i` in `Done[i]` starts out with the value `false`

Mix of psuedocode and actual code
```
While there are still unprocessed nodes:
  Set u, the closest unprocessed node, = to the starting node
  Mark node u as processed: Done [u]
  We now know how to reach u optimally from s
  Loop through all unprocessed nodes:
    Set v = the next unporcessed node
    If there's an edge from u to v then compare:
      a. the previously computed path from s to v (i.e. Dist[v]) OR b. the path from s to u, and then from u to v (i.e. Dist[u] + weight(u,v))
      If the new cost is less than the old cost then set Dist[v] = Dist[u] + weight(u,v)
```




