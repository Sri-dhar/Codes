import random
import math

def tsp_simulated_annealing(cities, distances, initial_temperature, cooling_rate, num_iterations):
    num_cities = len(cities)
    current_tour = random.sample(cities, num_cities)
    best_tour = current_tour.copy()
    current_distance = calculate_tour_distance(current_tour, distances)
    best_distance = current_distance

    temperature = initial_temperature

    for iteration in range(num_iterations):
        new_tour = current_tour.copy()
        i, j = random.sample(range(num_cities), 2)
        new_tour[i], new_tour[j] = new_tour[j], new_tour[i]

        new_distance = calculate_tour_distance(new_tour, distances)
        delta = new_distance - current_distance

        if delta < 0 or random.random() < math.exp(-delta / temperature):
            current_tour = new_tour
            current_distance = new_distance

        if current_distance < best_distance:
            best_tour = current_tour.copy()
            best_distance = current_distance

        temperature *= cooling_rate

    return best_tour, best_distance

def calculate_tour_distance(tour, distances):
    num_cities = len(tour)
    distance = 0

    for i in range(num_cities):
        distance += distances[tour[i]][tour[(i + 1) % num_cities]]

    return distance

cities = ['A', 'B', 'C', 'D']
distances = {
    'A': {'A': 0, 'B': 10, 'C': 15, 'D': 20},
    'B': {'A': 10, 'B': 0, 'C': 35, 'D': 25},
    'C': {'A': 15, 'B': 35, 'C': 0, 'D': 30},
    'D': {'A': 20, 'B': 25, 'C': 30, 'D': 0}
}

initial_temperature = 1000
cooling_rate = 0.99
num_iterations = 10000

best_tour, best_distance = tsp_simulated_annealing(cities, distances, initial_temperature, cooling_rate, num_iterations)

print("Best tour:", best_tour)
print("Best distance:", best_distance)