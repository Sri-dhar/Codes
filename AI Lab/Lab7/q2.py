import random
import time

total_time = 0

mutation_probability = random.random()
crossover_probability = random.random()

for _ in range(5):

    start_time = time.time()
    file = open("performance.txt", "a")

    def calculate_diversity(group):
        diversity = 0
        for i in range(len(group)):
            for j in range(i+1, len(group)):
                diversity += (abs(group[i] - group[j]))**2
        return diversity

    def fitness(chromosome, marks, k):
        groups = [[] for _ in range(k)]
        for i, group in enumerate(chromosome):
            groups[group].append(marks[i])
        return 1 / sum(calculate_diversity(group) for group in groups)

    def selection(population, fitnesses):
        return random.choices(population, weights=fitnesses, k=len(population))

    def crossover(parent1, parent2):
        if random.random() < crossover_probability:
            point = random.randint(1, len(parent1)-1)
            return parent1[:point] + parent2[point:], parent2[:point] + parent1[point:]
        else:
            return parent1, parent2

    def mutation(chromosome, k):
        if random.random() < mutation_probability:
            index = random.randrange(len(chromosome))
            group = random.randrange(k)
            new_chromosome = list(chromosome)
            new_chromosome[index] = group
            return new_chromosome
        else:
            return chromosome

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

    n = random.randint(10, 100)
    k = random.randint(2, 10)
    marks = [random.randint(1, 100) for i in range(n)]

    print("The number of students are:", n)
    print("The number of groups are:", k)
    print("The marks are:", marks)

    groups = genetic_algorithm(marks, n, k)
    print("The groups are:", groups)

    end_time = time.time()

    print()
    print("Time taken:", end_time - start_time)

    file.write("Number of students: " + str(n) + "\n")
    file.write("Number of groups: " + str(k) + "\n")
    file.write("Marks: " + str(marks) + "\n")
    file.write("Mutation Probability: " + str(mutation_probability) + "\n")
    file.write("Crossover Probability: " + str(crossover_probability) + "\n")
    file.write("Groups: " + str(groups) + "\n")
    file.write("Technique used: Genetic Algorithm\n\n")
    file.write("Mutation Operator: Random Mutation\n")
    file.write("Crossover Operator: Single Point Crossover\n")
    file.write("\nTime taken: " + str(end_time - start_time) + "\n\n\n")
    file.close()
    total_time += end_time - start_time

print("Average time taken:", total_time / 5)

file = open("performance.txt", "a")
file.write("Average time taken: " + str(total_time / 5) + "\n\n")