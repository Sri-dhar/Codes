import numpy as np

# Initialize parameters
learning_rate = 0.1
epochs = 2
w = np.array([1, 1, 1])  # [w0, w1, w2]

# Prepare data
X = np.array([[1, 1, 2],
              [1, 2, 10]])
y = np.array([6, 24])

# Batch gradient descent
for epoch in range(epochs):
    # Calculate predictions
    y_pred = np.dot(X, w)
    
    # Calculate error
    error = y_pred - y
    
    # Calculate gradients
    gradients = np.dot(X.T, error) / len(y)
    
    # Update weights
    w = w - learning_rate * gradients
    
    # Calculate mean squared error
    mse = np.mean(error ** 2)
    
    print(f"Epoch {epoch + 1}:")
    print(f"Weights: {w}")
    print(f"Mean Squared Error: {mse}\n")

# Final model
print("Final model:")
print(f"y = {w[0]:.4f} + {w[1]:.4f}*x1 + {w[2]:.4f}*x2")