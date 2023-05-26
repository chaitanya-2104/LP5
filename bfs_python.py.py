import time
queue=[]
def bfs(tree, node, visited):
    visited.add(node)
    queue.append(node)

    while queue:          # Creating loop to visit each node
        m = queue.pop(0) 
        print (m, end = " ") 
        for neighbour in tree[m]:
            if neighbour not in visited:
                visited.add(neighbour)
                queue.append(neighbour)
def parallel_bfs(tree, start_node, visited, num_threads):
    for thread_id in range(num_threads):
        # Get the start node for the current thread.
        start_node_for_thread = start_node + thread_id
        # Perform a breadth first search on the subtree rooted at the current node.
        visited_for_thread = bfs(tree, start_node_for_thread, visited)
        # Merge the results of the subtree searches.
        visited.update(visited_for_thread)
    return visited


def dfs(tree, start_node, visited):
    visited.add(start_node)
    if start_node in tree.keys():
        for child in tree[start_node]:
            if child not in visited:
                dfs(tree, child, visited)

    return visited




def parallel_dfs(tree, start_node, visited, num_threads):
    for thread_id in range(num_threads):
        # Get the start node for the current thread.
        start_node_for_thread = start_node + thread_id
        # Perform a breadth first search on the subtree rooted at the current node.
        visited_for_thread = dfs(tree, start_node_for_thread, visited)
        # Merge the results of the subtree searches.
        visited.update(visited_for_thread)
    return visited


tree = {
7:[2,3],
2: [7,4,5],
3:[7,6,1],
4:[2,8],
5:[2],
6:[3],
1:[3],
8:[4]
}

# Start the breadth first search.
visited = set()
start = time.time()
bfs(tree, 7, visited)
end = time.time()
print("parallel bfs =",end-start)



visited = set()
start = time.time()
q=dfs(tree, 7, visited)
print(q)
end = time.time()
print("parallel dfs =",end-start)
