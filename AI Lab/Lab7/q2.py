import random

def calculate_diversity(group):
    diversity = 0
    for i in range(len(group)):
        for j in range(i+1, len(group)):
            diversity += abs(group[i] - group[j])
    return diversity

def fitness(chromosome, marks, k):
    groups = [[] for _ in range(k)]
    for i, group in enumerate(chromosome):
        groups[group].append(marks[i])
    return 1 / sum(calculate_diversity(group) for group in groups)

def selection(population, fitnesses):
    return random.choices(population, weights=fitnesses, k=len(population))

def crossover(parent1, parent2):
    point = random.randint(1, len(parent1)-1)
    return parent1[:point] + parent2[point:], parent2[:point] + parent1[point:]

def mutation(chromosome, k):
    index = random.randrange(len(chromosome))
    group = random.randrange(k)
    new_chromosome = list(chromosome)
    new_chromosome[index] = group
    return new_chromosome

def genetic_algorithm(marks, n, k, pop_size=100, gen_limit=100):
    population = [[random.randrange(k) for _ in range(n)] for _ in range(pop_size)]
    for _ in range(gen_limit):
        fitnesses = [fitness(chromosome, marks, k) for chromosome in population]
        population = selection(population, fitnesses)
        new_population = []
        for i in range(0, len(population), 2):
            offspring1, offspring2 = crossover(population[i], population[i+1])
            new_population.append(mutation(offspring1, k))
            new_population.append(mutation(offspring2, k))
        population = new_population
    best_chromosome = max(population, key=lambda chromosome: fitness(chromosome, marks, k))
    return best_chromosome

n = int(input("Enter the no. of students : "))
k = int(input("Enter the no. of groups : "))
marks = [int(input(f"Enter the marks for student {i+1}: ")) for i in range(n)]
groups = genetic_algorithm(marks, n, k)
print("The groups are:", groups)