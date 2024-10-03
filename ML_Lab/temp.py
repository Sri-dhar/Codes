import numpy as np
import pandas as pd

df = pd.read_csv("iris_dataset.csv")
# print("First 5 rows of the dataset:")
# print(df.head())

training_split = 0.7
validation_split = 0.2
testing_split = 1 - training_split - validation_split

df = df.sample(frac=1).reset_index(drop=True)

num_samples= len(df)
X = df.iloc[:, :-1].values
y = df.iloc[:, -1].values

num_training = int(num_samples * training_split)
num_testing = num_samples - num_training
num_validation = int(num_samples * validation_split)

X_train = X[:num_training]
y_train = y[:num_training]

X_test = X[num_training:num_training+num_testing]
y_test = y[num_training:num_training+num_testing]

X_validation = X[num_training+num_testing:]
y_validation = y[num_training+num_testing:]

X_train = (X_train - X_train.mean(axis=0)) / X_train.std(axis=0)
X_test = (X_test - X_test.mean(axis=0)) / X_test.std(axis=0)
X_validation = (X_validation - X_validation.mean(axis=0)) / X_validation.std(axis=0)

k_values = [3, 5, 7, 9]

def euclidean_distance(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))

def predict(X_train, y_train, x_test, k):
    distances = [euclidean_distance(x_test, x_train) for x_train in X_train]
    k_indices = np.argsort(distances)[:k]
    k_nearest_labels = [y_train[i] for i in k_indices]
    most_common = np.bincount(k_nearest_labels).argmax()
    return most_common

def k_nearest_neighbors(X_train, y_train, X_test, k):
    predictions = [predict(X_train, y_train, x_test, k) for x_test in X_test]
    return predictions

def accuracy(y_true, y_pred):
    accuracy = np.sum(y_true == y_pred) / len(y_true)
    return accuracy

for k in k_values:
    y_pred = k_nearest_neighbors(X_train, y_train, X_validation, k)
    acc = accuracy(y_validation, y_pred)
    print(f"Validation accuracy for k = {k}: {acc}")
    
best_k = 5
y_pred = k_nearest_neighbors(X_train, y_train, X_test, best_k)
acc = accuracy(y_test, y_pred)
print(f"Test accuracy for best k = {best_k}: {acc}")

