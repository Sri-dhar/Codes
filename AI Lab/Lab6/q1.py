import random

def f(x):
    return x**2

def hill_climbing(start, step_size, range_min, range_max):
    current = start
    while True:
        neighbors = [(current + step_size), (current - step_size)]
        neighbors = [x for x in neighbors if range_min <= x <= range_max]
        if not neighbors:
            break
        next_val = max(neighbors, key=lambda x: f(x))
        if f(next_val) <= f(current):
            break
        current = next_val
    return current

print("=================================================")
print("=================================================")

print("Testcase One")


range_min = -10
range_max = 10
start = random.uniform(range_min, range_max)
step_size = 0.1

max_value = hill_climbing(start, step_size, range_min, range_max)
print("Range :", range_min, " to ", range_max)
print("Maximum value found:", f(max_value))


print("=================================================")
print("Testcase Two")
range_min = -20
range_max = 20
start = random.uniform(range_min, range_max)
max_value = hill_climbing(start, step_size, range_min, range_max)
print("Range :", range_min, " to ", range_max)
print("Maximum value found:", f(max_value))
print("=================================================")
print("Testcase Three")

range_min = -30
range_max = 30
start = random.uniform(range_min, range_max)
max_value = hill_climbing(start, step_size, range_min, range_max)
print("Range :", range_min, " to ", range_max)
print("Maximum value found:", f(max_value))

print("=================================================")
print("=================================================")

