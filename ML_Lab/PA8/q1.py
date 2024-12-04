# Implement the perceptron learning algorithm for AND logic gate with 2-bit binary
# input. Finally report the overall accuracy on training samples (no separate splitting is
# necessary for train/test/validation).

import numpy as np
import random
import matplotlib.pyplot as plt

def perceptron_learning_algorithm(X, Y, w, b, alpha, epochs):
    for epoch in range(epochs):
        for i in range(len(X)):
            y_pred = np.dot(X[i], w) + b
            if y_pred > 0:
                y_pred = 1
            else:
                y_pred = 0
            w = w + alpha * (Y[i] - y_pred) * X[i]
            b = b + alpha * (Y[i] - y_pred)
    return w, b

def main():
    X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
    Y = np.array([0, 0, 0, 1])
    w = np.array([random.random(), random.random()])
    b = random.random()
    alpha = 0.1
    epochs = 1000
    w, b = perceptron_learning_algorithm(X, Y, w, b, alpha, epochs)
    print("Weights: ", w)
    print("Bias: ", b)
    print("Accuracy: ", 1 - np.sum(np.abs(Y - np.dot(X, w) - b)) / len(Y))
    plt.scatter(X[:, 0], X[:, 1], c=Y)
    plt.plot(np.linspace(0, 1, 100), (-w[0] / w[1]) * np.linspace(0, 1, 100) - b / w[1])
    plt.show()
    plt.savefig('q1.png')   
    
if __name__ == "__main__":
    main()