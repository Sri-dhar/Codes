import numpy as np
import pandas as pd
from collections import Counter
from sklearn.datasets import load_iris

def euclidean_distance(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))

class KNN:
    def __init__(self, k=3):
        self.k = k
    
    def fit(self, X_train, y_train):
        self.X_train = X_train
        self.y_train = y_train
    
    def predict_point(self, x):
        distances = [euclidean_distance(x, x_train) for x_train in self.X_train]
        k_indices = np.argsort(distances)[:self.k]
        k_nearest_labels = [self.y_train[i] for i in k_indices]
        most_common = Counter(k_nearest_labels).most_common(1)
        return most_common[0][0]
    
    def predict(self, X_test):
        return np.array([self.predict_point(x) for x in X_test])

def accuracy(y_true, y_pred):
    return np.sum(y_true == y_pred) / len(y_true)

def precision(y_true, y_pred, average='macro'):
    labels = np.unique(y_true)
    precision_values = []
    for label in labels:
        tp = np.sum((y_true == label) & (y_pred == label))
        fp = np.sum((y_true != label) & (y_pred == label))
        precision_values.append(tp / (tp + fp) if (tp + fp) > 0 else 0)
    
    return np.mean(precision_values) if average == 'macro' else precision_values

def recall(y_true, y_pred, average='macro'):
    labels = np.unique(y_true)
    recall_values = []
    for label in labels:
        tp = np.sum((y_true == label) & (y_pred == label))
        fn = np.sum((y_true == label) & (y_pred != label))
        recall_values.append(tp / (tp + fn) if (tp + fn) > 0 else 0)
    
    return np.mean(recall_values) if average == 'macro' else recall_values

def f1_score(y_true, y_pred, average='macro'):
    prec = precision(y_true, y_pred, average)
    rec = recall(y_true, y_pred, average)
    return 2 * (prec * rec) / (prec + rec) if (prec + rec) > 0 else 0

def confusion_matrix(y_true, y_pred):
    labels = np.unique(y_true)
    matrix = np.zeros((len(labels), len(labels)), dtype=int)
    for i, label_true in enumerate(labels):
        for j, label_pred in enumerate(labels):
            matrix[i, j] = np.sum((y_true == label_true) & (y_pred == label_pred))
    return matrix

def evaluate_model(y_true, y_pred):
    print(f"Accuracy: {accuracy(y_true, y_pred):.4f}")
    print(f"Precision: {precision(y_true, y_pred):.4f}")
    print(f"Recall: {recall(y_true, y_pred):.4f}")
    print(f"F1 Score: {f1_score(y_true, y_pred):.4f}")
    print("Confusion Matrix:")
    print(confusion_matrix(y_true, y_pred))

def manual_train_test_split(X, y, test_size=0.2):
    split_index = int((1 - test_size) * len(X))
    X_train, X_test = X[:split_index], X[split_index:]
    y_train, y_test = y[:split_index], y[split_index:]
    return X_train, X_test, y_train, y_test

def manual_label_encoder(y):
    unique_labels = np.unique(y)
    label_map = {label: idx for idx, label in enumerate(unique_labels)}
    y_encoded = np.array([label_map[label] for label in y])
    return y_encoded

if __name__ == "__main__":
    iris = load_iris()
    X = iris.data
    y = iris.target
    
    X_train, X_test, y_train, y_test = manual_train_test_split(X, y, test_size=0.2)
    
    k = 3
    model = KNN(k=k)
    model.fit(X_train, y_train)
    
    y_pred = model.predict(X_test)
    
    evaluate_model(y_test, y_pred)
