import random
import time
import numpy as np

def calculate_diversity(group):
    diversity = 0
    for i in range(len(group)):
        for j in range(i+1, len(group)):
            diversity += abs(group[i] - group[j])
    return diversity

def fitness(groups, marks, k):
    return -sum(calculate_diversity([marks[i] for i in range(len(groups)) if groups[i] == j]) for j in range(k))

class Particle:
    def __init__(self, n, k):
        self.position = np.random.randint(k, size=n)
        self.velocity = np.random.rand(n)
        self.pbest_position = self.position
        self.pbest_value = float('inf')

    def update_velocity(self, gbest_position):
        w = 0.5
        c1 = 1
        c2 = 2
        self.velocity = w*self.velocity + c1*random.random()*(self.pbest_position - self.position) + c2*random.random()*(gbest_position - self.position)

    def update_position(self, k):
        self.position = np.clip(self.position + self.velocity, 0, k-1).astype(int)

def pso(marks, n, k, num_particles=100, max_iter=100):
    particles = [Particle(n, k) for _ in range(num_particles)]
    gbest_value = float('inf')
    gbest_position = None

    for _ in range(max_iter):
        for particle in particles:
            fitness_candidate = fitness(particle.position, marks, k)
            if fitness_candidate < particle.pbest_value:
                particle.pbest_value = fitness_candidate
                particle.pbest_position = particle.position

            if fitness_candidate < gbest_value:
                gbest_value = fitness_candidate
                gbest_position = particle.position

        for particle in particles:
            particle.update_velocity(gbest_position)
            particle.update_position(k)

    return gbest_position

n = random.randint(10, 100)
k = random.randint(2, 10)
marks = [random.randint(1, 100) for i in range(n)]

start_time = time.time()
groups = pso(marks, n, k)
end_time = time.time()


print("The marks array is:", marks)
print("The groups are:", groups)
print("Time taken:", end_time - start_time)