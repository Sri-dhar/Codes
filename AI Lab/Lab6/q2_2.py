'''
Implement the Simulated Annealing algorithm to solve the Travelling Salesman Problem
(TSP) for a given set of cities and their distances.
Requirements:
(a) Given a set of cities and their distances, define a function to represent the TSP objective.
(b) Implement the Simulated Annealing algorithm to find the shortest tour that visits each city
exactly once and returns to the starting city.
(c) Experiment with a different initial temperature, cooling rate and number of iterations to
observe their effects on the algorithm’s performance.
'''

import random
import math

def objective_fn(cities, distances):
    distance = 0
    for i in range(len(cities)-1):
        distance += distances[cities[i]][cities[i+1]]

    distance += distances[cities[-1]][cities[0]]
    return distance

def simulated_annealing(distances, cities, initial_temperature, cooling_rate, iterations):
    current_ans = cities
    current_cost = objective_fn(cities, distances)
    best_ans = current_ans
    best_cost = current_cost
    temperature = initial_temperature
    for i in range(iterations):
        new_ans = current_ans.copy()
        a = random.randint(0, len(cities)-1)
        b = random.randint(0, len(cities)-1)
        new_ans[a], new_ans[b] = new_ans[b], new_ans[a]
        new_cost = objective_fn(new_ans, distances)
        delta = new_cost - current_cost
        if delta < 0 or (temperature > 0 and random.random() < math.exp(-delta/temperature)):
            current_ans = new_ans
            current_cost = new_cost
            if new_cost < best_cost:
                best_ans = new_ans
                best_cost = new_cost
        temperature *= cooling_rate
    return best_ans, best_cost

if __name__ == "__main__":
    cities = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    distances = [
        [0, 29, 20, 21, 16, 31, 100, 12, 4, 31],
        [29, 0, 15, 29, 28, 40, 72, 21, 29, 41],
        [20, 15, 0, 15, 14, 25, 81, 9, 23, 27],
        [21, 29, 15, 0, 4, 12, 92, 12, 25, 13],
        [16, 28, 14, 4, 0, 16, 94, 9, 20, 16],
        [31, 40, 25, 12, 16, 0, 95, 24, 36, 3],
        [100, 72, 81, 92, 94, 95, 0, 90, 101, 99],
        [12, 21, 9, 12, 9, 24, 90, 0, 15, 25],
        [4, 29, 23, 25, 20, 36, 101, 15, 0, 35],
        [31, 41, 27, 13, 16, 3, 99, 25, 35, 0]
    ]
    initial_temperature = 1000
    cooling_rate = 0.99
    iterations = 100000
    best_tour, best_distance = simulated_annealing(distances, cities, initial_temperature, cooling_rate, iterations)
    print("Best tour: ", best_tour)
    print("Best tour distance: ", best_distance)