import numpy as np
import pandas as pd

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def compute_cost(X, y, theta, regularization_lambda):
    m = len(y)  # Number of training examples
    h = sigmoid(np.dot(X, theta))
    cost = -(1 / m) * np.sum(y * np.log(h) + (1 - y) * np.log(1 - h))
    reg_term = (regularization_lambda / (2 * m)) * np.sum(np.square(theta[1:]))
    return cost + reg_term

def gradient_descent(X, y, theta, learning_rate, num_iterations, regularization_lambda):
    m = len(y)  # Number of training examples
    cost_history = []  # To store cost at each iteration

    for i in range(num_iterations):
        h = sigmoid(np.dot(X, theta))  # Hypothesis function
        gradient = (1 / m) * np.dot(X.T, (h - y)) + (regularization_lambda / m) * np.r_[[0], theta[1:]]
        theta -= learning_rate * gradient  # Update weights
        cost_history.append(compute_cost(X, y, theta, regularization_lambda))  # Store the cost

    return theta, cost_history

def predict(X, theta):
    h = sigmoid(np.dot(X, theta))
    return (h >= 0.35).astype(int)  # Classify as 1 if h >= 0.5, else 0

def evaluate_model(X, y, theta):
    y_pred = predict(X, theta)
    accuracy = np.mean(y_pred == y)  # Calculate accuracy
    return accuracy, y_pred

data = pd.DataFrame({
    'x1': [5.1, 4.9, 4.7, 4.6, 5.0, 5.4, 4.6, 5.0, 4.4, 4.9, 5.4, 4.8, 4.8, 4.3, 5.8, 5.7, 5.4, 5.1, 5.7, 5.1],
    'x2': [3.5, 3.0, 3.2, 3.1, 3.6, 3.9, 3.4, 3.4, 2.9, 3.1, 3.7, 3.4, 3.0, 3.0, 4.0, 4.4, 3.9, 3.5, 3.8, 3.8],
    'x3': [1.4, 1.4, 1.3, 1.5, 1.4, 1.7, 1.4, 1.5, 1.4, 1.5, 1.5, 1.6, 1.4, 1.1, 1.2, 1.5, 1.3, 1.4, 1.7, 1.5],
    'x4': [0.2, 0.2, 0.2, 0.2, 0.2, 0.4, 0.3, 0.2, 0.2, 0.1, 0.2, 0.2, 0.1, 0.1, 0.2, 0.4, 0.4, 0.3, 0.3, 0.3]
})

X = data[['x1', 'x2', 'x3']]
y = (data['x4'] > 0.2).astype(int)

X = np.hstack((np.ones((X.shape[0], 1)), X))  # Add intercept (bias term) to feature matrix

theta = np.zeros(X.shape[1])  # Initialize theta to zero

learning_rate = 0.01
num_iterations = 1000
regularization_lambda = 0.1

theta, cost_history = gradient_descent(X, y, theta, learning_rate, num_iterations, regularization_lambda)

accuracy, y_pred = evaluate_model(X, y, theta)

print(f'Final Cost: {cost_history[-1]:.4f}')
print(f'Accuracy: {accuracy:.2f}')

cluster_0 = data[y_pred == 0]
cluster_1 = data[y_pred == 1]

print("\nCluster 0 (Predicted as 0):")
print(cluster_0)

print("\nCluster 1 (Predicted as 1):")
print(cluster_1)
