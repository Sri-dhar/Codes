def initialize_distance_vector(nodes, links, source):
    inf = float('inf')
    distance_vector = {node: inf for node in nodes}
    distance_vector[source] = 0
    for neighbor in links.get(source, {}):
        distance_vector[neighbor] = links[source][neighbor]
    return distance_vector

def exchange_and_update(nodes, links, distance_vectors):
    new_vectors = {node: dict(vector) for node, vector in distance_vectors.items()}
    for node in nodes:
        for neighbor in links.get(node, {}):
            for target in nodes:
                new_cost = distance_vectors[node][target] + links[node][neighbor]
                if new_cost < new_vectors[neighbor][target]:
                    new_vectors[neighbor][target] = new_cost
    return new_vectors

def simulate_distance_vector_protocol(nodes, links, source):
    distance_vectors = {node: initialize_distance_vector(nodes, links, node) for node in nodes}
    print(f"Initial distance vector of {source}: {distance_vectors[source]}")  # Print initial vector of A
    
    iterations = 0
    while True:
        new_vectors = exchange_and_update(nodes, links, distance_vectors)
        if all(new_vectors[node] == distance_vectors[node] for node in nodes):
            break
        distance_vectors = new_vectors
        iterations += 1
        print(f"After {iterations} iteration(s), Distance vector of {source}: {distance_vectors[source]}")
    print(f"Final distance vector at {source}: {distance_vectors[source]}")


nodes = ['A', 'B', 'C', 'D', 'E', 'F', 'G']

links = {
    'A': {'B': 1, 'C': 1, 'E': 1},
    'B': {'A': 1, 'C': 1},
    'C': {'A': 1, 'B': 1, 'D': 1},
    'D': {'C': 1, 'G': 1},
    'E': {'A': 1},
    'F': {'A': 1, 'G': 1},
    'G': {'D': 1, 'F': 1}
}

simulate_distance_vector_protocol(nodes, links, 'A')
                