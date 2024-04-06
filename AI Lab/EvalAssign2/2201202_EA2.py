import random
import time

NUM_QUESTIONS = 10
POPULATION_SIZE = 15
MAX_GENERATIONS = 30
CROSSOVER_PROBABILITY = 0.6
MUTATION_PROBABILITY = 0.5


def fitness(chromosome):
    return sum(chromosome)


def roulette_wheel_selection(population):
    total_fitness = sum(fitness(c) for c in population)
    fitness_probs = [fitness(c) / total_fitness for c in population]

    parents = []
    for _ in range(2):
        spin = random.random()
        prob_sum = 0
        for i, prob in enumerate(fitness_probs):
            prob_sum += prob
            if prob_sum >= spin:
                parents.append(population[i])
                break
    return parents


def multi_point_crossover(parent1, parent2):
    crossover_points = sorted(random.sample(range(1, NUM_QUESTIONS - 1), 2))
    child1 = (
        parent1[: crossover_points[0]]
        + parent2[crossover_points[0] : crossover_points[1]]
        + parent1[crossover_points[1] :]
    )
    child2 = (
        parent2[: crossover_points[0]]
        + parent1[crossover_points[0] : crossover_points[1]]
        + parent2[crossover_points[1] :]
    )
    return child1, child2


# Bit Flip Mutation
def bit_flip_mutation(chromosome):
    for i in range(NUM_QUESTIONS):
        if random.random() < MUTATION_PROBABILITY:
            chromosome[i] = int(not chromosome[i])
    return chromosome


def main():
    population = [
        [random.randint(0, 1) for _ in range(NUM_QUESTIONS)]
        for _ in range(POPULATION_SIZE)
    ]

    all_times = []
    all_solutions = []
    for _ in range(5):
        start_time = time.process_time()

        for gen in range(MAX_GENERATIONS):
            parents = [
                roulette_wheel_selection(population)
                for _ in range(POPULATION_SIZE // 2)
            ]

            offspring = []
            for p1, p2 in parents:
                if random.random() < CROSSOVER_PROBABILITY:
                    child1, child2 = multi_point_crossover(p1, p2)
                    offspring.append(child1)
                    offspring.append(child2)
                else:
                    offspring.append(p1)
                    offspring.append(p2)

            for individual in offspring:
                individual = bit_flip_mutation(individual)

            best_parent = max(population, key=fitness)
            population = offspring[: POPULATION_SIZE - 1] + [best_parent]

        best_individual = max(population, key=fitness)
        solution_quality = fitness(best_individual)
        all_times.append(time.process_time() - start_time)
        all_solutions.append(best_individual)

    avg_time = sum(all_times) / len(all_times)
    print(f"\nCombined Computation Time: {sum(all_times):.6f} seconds")
    print(f"Average Computation Time: {avg_time:.6f} seconds")
    print(f"\nSolution Quality (over 5 runs):\n")
    for solution in all_solutions:
        print(solution)
        print(f"The fitness quality is : {fitness(solution)} \n")


if __name__ == "__main__":
    main()
