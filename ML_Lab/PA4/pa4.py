import numpy as np

x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
y = np.array([2, 4, 6, 8, 10, 12, 14, 15, 16, 20])

indices = np.random.permutation(len(x))
x_shuffled = x[indices]
y_shuffled = y[indices]

print("Shuffled x:", x_shuffled)
print("Shuffled y:", y_shuffled)

train_size = 0.6
val_size = 0.2
test_size = 0.2

train_idx = int(len(x) * train_size)
val_idx = int(len(x) * (train_size + val_size))

X_train = np.array([[1, xi] for xi in x[:train_idx]])
y_train = y[:train_idx]
X_val = np.array([[1, xi] for xi in x[train_idx:val_idx]])
y_val = y[train_idx:val_idx]
X_test = np.array([[1, xi] for xi in x[val_idx:]])
y_test = y[val_idx:]

print(f"Training data: {X_train}")
print(f"Training labels: {y_train}")
print(f"Validation data: {X_val}")
print(f"Validation labels: {y_val}")
print(f"Test data: {X_test}")
print(f"Test labels: {y_test}")

def compute_cost(X, y, theta):
    m = len(y)
    h = X.dot(theta)
    J = np.sum((h - y) ** 2) / (2 * m)
    return J

def gradient_descent(X, y, alpha, epochs):
    m = len(y)
    theta = np.zeros(X.shape[1])
    costs = []

    for i in range(epochs):
        h = X.dot(theta)
        theta = theta - (alpha / m) * X.T.dot(h - y)
        cost = compute_cost(X, y, theta)
        costs.append(cost)

    return theta, costs

best_alpha = None
best_val_error = float('inf')
epochs = 1000   # Number of iterations  

for temp_alpha in [0.001, 0.01, 0.1, 1.0]:
    theta, cost_history = gradient_descent(X_train, y_train, temp_alpha, epochs)
    h_val = X_val.dot(theta)
    val_error = np.sum((h_val - y_val) ** 2) / (2 * len(y_val))     
    print(f"Validation error for alpha={temp_alpha:.3f}: {val_error:.2f}")

    if val_error < best_val_error:
        best_alpha = temp_alpha
        best_val_error = val_error

print(f"Best alpha: {best_alpha:.3f}")
print(f"Best validation error: {best_val_error:.2f}")
print()

theta, cost_history = gradient_descent(X_train, y_train, best_alpha, epochs)
print("Theta:", theta)
# print("Cost history:", cost_history)

print(f"The predicted equation is : y = {theta[0]:.2f} + {theta[1]:.2f}x")

h_test = X_test.dot(theta)
test_error = np.sum((h_test - y_test) ** 2) / (2 * len(y_test))
print(f"Test error: {test_error:.2f}")
