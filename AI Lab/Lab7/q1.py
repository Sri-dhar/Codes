import random

def fitness_function(x):
    return 2 * x**2 + 1

def genetic_algorithm():
    population_size = 10
    population = [random.uniform(0, 6) for _ in range(population_size)]

    num_generations = 100

    for generation in range(num_generations):
        fitness_scores = [fitness_function(x) for x in population]

        tournament_size = 2
        parents = []
        for _ in range(population_size):
            tournament = random.sample(range(population_size), tournament_size)
            tournament_fitness = [fitness_scores[i] for i in tournament]
            winner = tournament[tournament_fitness.index(max(tournament_fitness))]
            parents.append(population[winner])

        offspring = []
        for _ in range(population_size):
            parent1 = random.choice(parents)
            parent2 = random.choice(parents)
            child = (parent1 + parent2) / 2  
            child += random.uniform(-0.1, 0.1)  
            offspring.append(child)

        population = offspring

    best_individual = max(population, key=fitness_function)
    best_fitness = fitness_function(best_individual)

    return best_individual, best_fitness

best_solution, best_fitness = genetic_algorithm()

print("Best solution:", best_solution)
print("Best fitness:", best_fitness)