'''
Implement singlelayer perceptron (SLP) for multi-class classification task using IRIS dataset.
Follow the below-mentioned instructions to implement your own code
a. Tune the hyper-parameters
b. Check overfitting issue
c. Finally report class-wise precision, recall, accuracy and overall accuracy considering
5-fold cross validation.
'''

import numpy as np
import pandas as pd

def load_data():
    data = pd.read_csv('iris.csv')
    X = data.iloc[:, :-1].values
    y = data.iloc[:, -1].values
    return X, y

def encode_labels(y):
    classes = np.unique(y)
    y_encoded = np.zeros((y.shape[0], len(classes)))
    for i in range(len(classes)):
        y_encoded[y == classes[i], i] = 1
    return y_encoded

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def softmax(x):
    return np.exp(x) / np.sum(np.exp(x), axis=1, keepdims = True)

def cross_entropy_loss(y_true, y_pred):
    return -np.sum(y_true * np.log(y_pred))

def accuracy(y_true, y_pred):
    return np.mean(np.argmax(y_true, axis=1) == np.argmax(y_pred, axis=1))

def train(X, y, lr, epochs):
    y = encode_labels(y)
    n_samples, n_features = X.shape
    n_classes = y.shape[1]
    W = np.random.rand(n_features, n_classes)
    b = np.zeros((1, n_classes))
    for epoch in range(epochs):
        linear_output = np.dot(X, W) + b
        y_pred = softmax(linear_output)
        loss = cross_entropy_loss(y, y_pred)
        dW = (1 / n_samples) * np.dot(X.T, (y_pred - y))
        db = (1 / n_samples) * np.sum(y_pred - y)
        W -= lr * dW
        b -= lr * db
        if epoch % 100 == 0:
            print(f'Epoch {epoch}: loss = {loss}')
    return W, b

def predict(X, W, b):
    linear_output = np.dot(X, W) + b
    y_pred = softmax(linear_output)
    return y_pred

def precision(y_true, y_pred):
    TP = np.sum(y_true * y_pred)
    FP = np.sum((1 - y_true) * y_pred)
    return TP / (TP + FP)

def recall(y_true, y_pred):
    TP = np.sum(y_true * y_pred)
    FN = np.sum(y_true * (1 - y_pred))
    return TP / (TP + FN)

def class_wise_metrics(y_true, y_pred):
    classes = y_true.shape[1]
    precision_scores = []
    recall_scores = []
    accuracy_scores = []
    for i in range(classes):
        precision_scores.append(precision(y_true[:, i], y_pred[:, i]))
        recall_scores.append(recall(y_true[:, i], y_pred[:, i]))
        accuracy_scores.append(accuracy(y_true[:, i], y_pred[:, i]))
    return precision_scores, recall_scores, accuracy_scores

def overall_accuracy(y_true, y_pred):
    TP = np.sum(y_true * y_pred)
    TN = np.sum((1 - y_true) * (1 - y_pred))
    return (TP + TN) / y_true.shape[0]

def k_fold_cross_validation(X, y, lr, epochs, k):
    n_samples = X.shape[0]
    fold_size = n_samples // k
    indices = np.random.permutation(n_samples)
    X = X[indices]
    y = y[indices]
    for i in range(k):
        X_train = np.concatenate([X[:i * fold_size], X[(i + 1) * fold_size:]])
        y_train = np.concatenate([y[:i * fold_size], y[(i + 1) * fold_size:]])
        X_val = X[i * fold_size:(i + 1) * fold_size]
        y_val = y[i * fold_size:(i + 1) * fold_size]
        W, b = train(X_train, y_train, lr, epochs)
        y_pred = predict(X_val, W, b)
        acc = accuracy(y_val, y_pred)
        precision_scores, recall_scores, accuracy_scores = class_wise_metrics(y_val, y_pred)
        overall_acc = overall_accuracy(y_val, y_pred)
        print(f'Fold {i + 1}: accuracy = {acc}, precision = {precision_scores}, recall = {recall_scores}, class-wise accuracy = {accuracy_scores}, overall accuracy = {overall_acc}')
        
X, y = load_data()
k_fold_cross_validation(X, y, lr = 0.01, epochs = 1000, k = 5)
