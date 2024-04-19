import random
import numpy as np
import time

num_cities = 10
distance_matrix = np.random.randint(1, 100, (num_cities, num_cities))
np.fill_diagonal(distance_matrix, 0)

print("Distance matrix:")
print(distance_matrix)
print()
population_size = 50
mutation_rate = 0.01
num_generations = 100

def generate_population(size):
    population = []
    for _ in range(size):
        individual = list(range(distance_matrix.shape[0]))
        random.shuffle(individual)
        population.append(individual)
    return population

def calculate_fitness(individual):
    total_distance = 0
    for i in range(len(individual)):
        current_city = individual[i]
        next_city = individual[(i + 1) % len(individual)]
        total_distance += distance_matrix[current_city][next_city]
    return 1 / total_distance

def mutate(individual):
    for i in range(len(individual)):
        if random.random() < mutation_rate:
            j = random.randint(0, len(individual) - 1)
            individual[i], individual[j] = individual[j], individual[i]
    return individual

def crossover(parent1, parent2):
    child = [-1] * len(parent1)
    start_index = random.randint(0, len(parent1) - 1)
    end_index = random.randint(start_index, len(parent1) - 1)
    child[start_index:end_index + 1] = parent1[start_index:end_index + 1]
    for i in range(len(parent2)):
        if parent2[i] not in child:
            for j in range(len(child)):
                if child[j] == -1:
                    child[j] = parent2[i]
                    break
    return child

def select_parents(population):
    parents = []
    for _ in range(2):
        tournament = random.sample(population, 5)
        tournament_fitness = [calculate_fitness(individual) for individual in tournament]
        best_individual = tournament[np.argmax(tournament_fitness)]
        parents.append(best_individual)
    return parents

def genetic_algorithm():
    population = generate_population(population_size)
    best_solution = None
    best_fitness = 0
    start_time = time.time()
    for generation in range(num_generations):
        new_population = []
        for _ in range(population_size // 2):
            parent1, parent2 = select_parents(population)
            child1 = crossover(parent1, parent2)
            child2 = crossover(parent2, parent1)
            child1 = mutate(child1)
            child2 = mutate(child2)
            new_population.extend([child1, child2])
        population = new_population
        population_fitness = [calculate_fitness(individual) for individual in population]
        best_individual = population[np.argmax(population_fitness)]
        best_fitness = max(best_fitness, calculate_fitness(best_individual))
        best_solution = best_individual
    end_time = time.time()
    computational_time = end_time - start_time
    return best_solution, best_fitness, computational_time

best_solution, best_fitness, computational_time = genetic_algorithm()

print("Best solution:", best_solution)
print("Best fitness:", best_fitness)
print("Computational time:", computational_time)