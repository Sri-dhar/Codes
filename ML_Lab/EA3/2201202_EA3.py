import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def load_data():
    data = pd.read_csv('iris.csv')
    X = data.iloc[:, :-1].values
    y = data.iloc[:, -1].values
    return X, y

def encode_labels(y):
    classes = np.unique(y)
    y_encoded = np.zeros((y.shape[0], len(classes)))
    for i, cls in enumerate(classes):
        y_encoded[y == cls, i] = 1          
    return y_encoded

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def softmax(x):
    exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))
    return exp_x / np.sum(exp_x, axis=1, keepdims=True)

def cross_entropy_loss(y_true, y_pred):
    return -np.sum(y_true * np.log(y_pred + 1e-9)) / y_true.shape[0]

def accuracy(y_true, y_pred):
    return np.mean(np.argmax(y_true, axis=1) == np.argmax(y_pred, axis=1))      

def tune_hyperparameters(X, y):
    param_grid = {
        'lr': [0.001, 0.01, 0.1],
        'epochs': [500, 1000, 1500]
    }
    best_params = {'lr': 0.01, 'epochs': 1000}
    best_score = 0

    for lr in param_grid['lr']:
        for epochs in param_grid['epochs']:
            accuracies, _, _, _ = k_fold_cross_validation(X, y, lr, epochs, k=5)
            avg_accuracy = np.mean(accuracies)
            if avg_accuracy > best_score:
                best_score = avg_accuracy
                best_params = {'lr': lr, 'epochs': epochs}

    return best_params

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
        db = (1 / n_samples) * np.sum(y_pred - y, axis=0, keepdims=True)
        W -= lr * dW
        b -= lr * db
    return W, b

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
        db = (1 / n_samples) * np.sum(y_pred - y, axis=0, keepdims=True)
        W -= lr * dW
        b -= lr * db
        if epoch % 100 == 0 and epoch == 0:
            print(f'Epoch   {epoch}: loss = {loss}')
        elif epoch % 100 == 0:
            print(f'Epoch {epoch}: loss = {loss}')
    return W, b
    

def predict(X, W, b):
    linear_output = np.dot(X, W) + b
    y_pred = softmax(linear_output)
    return y_pred

def precision(y_true, y_pred):
    TP = np.sum(y_true * y_pred)
    FP = np.sum((1 - y_true) * y_pred)
    return TP / (TP + FP + 1e-9)

def recall(y_true, y_pred):
    TP = np.sum(y_true * y_pred)
    FN = np.sum(y_true * (1 - y_pred))
    return TP / (TP + FN + 1e-9)

def class_wise_metrics(y_true, y_pred):
    classes = y_true.shape[1]
    precision_scores = []
    recall_scores = []
    accuracy_scores = []
    for i in range(classes):
        precision_scores.append(precision(y_true[:, i], y_pred[:, i]))
        recall_scores.append(recall(y_true[:, i], y_pred[:, i]))
        accuracy_scores.append(accuracy(y_true[:, [i]], y_pred[:, [i]])) 
    return precision_scores, recall_scores, accuracy_scores

def overall_accuracy(y_true, y_pred):
    return accuracy(y_true, y_pred)

def k_fold_cross_validation(X, y, lr, epochs, k):
    fold_size = len(X) // k
    accuracies = []
    overall_accuracies = []
    precision_scores_list = []
    recall_scores_list = []

    for i in range(k):
        X_train = np.concatenate([X[:i * fold_size], X[(i + 1) * fold_size:]])
        y_train = np.concatenate([y[:i * fold_size], y[(i + 1) * fold_size:]])
        X_val = X[i * fold_size:(i + 1) * fold_size]
        y_val = y[i * fold_size:(i + 1) * fold_size]
        W, b = train(X_train, y_train, lr, epochs)
        y_val_encoded = encode_labels(y_val)
        y_pred = predict(X_val, W, b)
        acc = accuracy(y_val_encoded, y_pred)

        accuracies.append(acc)
    
    return accuracies, overall_accuracies, precision_scores_list, recall_scores_list
   
def k_fold_cross_validation_print(X, y, lr, epochs, k):
    fold_size = len(X) // k
    accuracies = []
    overall_accuracies = []
    precision_scores_list = []
    recall_scores_list = []

    for i in range(k):
        X_train = np.concatenate([X[:i * fold_size], X[(i + 1) * fold_size:]])
        y_train = np.concatenate([y[:i * fold_size], y[(i + 1) * fold_size:]])
        X_val = X[i * fold_size:(i + 1) * fold_size]
        y_val = y[i * fold_size:(i + 1) * fold_size]
        W, b = train(X_train, y_train, lr, epochs)
        y_val_encoded = encode_labels(y_val)
        y_pred = predict(X_val, W, b)
        acc = accuracy(y_val_encoded, y_pred)
        precision_scores, recall_scores, accuracy_scores = class_wise_metrics(y_val_encoded, y_pred)
        overall_acc = overall_accuracy(y_val_encoded, y_pred)

        accuracies.append(acc)
        overall_accuracies.append(overall_acc)
        precision_scores_list.append(precision_scores)
        recall_scores_list.append(recall_scores)

        print(f'Fold {i + 1}:')
        print(f'  Accuracy: {acc:.4f}')
        print(f'  Overall Accuracy: {overall_acc:.4f}')
        print('  Class-wise Metrics:')
        for cls in range(len(precision_scores)):
            print(f'    Class {cls}:')
            print(f'      Precision: {precision_scores[cls]:.4f}')
            print(f'      Recall: {recall_scores[cls]:.4f}')
        print('\n')

    
    return accuracies, overall_accuracies, precision_scores_list, recall_scores_list   

   
X, y = load_data()
best_params = tune_hyperparameters(X, y)
print(f"\nBest hyperparameters: {best_params}\n")

accuracies, overall_accuracies, precision_scores_list, recall_scores_list = k_fold_cross_validation_print(X, y, lr=0.01, epochs=1000, k=5)
k = 5
plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.plot(range(1, k + 1), accuracies, marker='o', label='Accuracy')
plt.title('Accuracy per Fold')
plt.xlabel('Fold')
plt.ylabel('Accuracy')
plt.legend()

plt.subplot(2, 2, 2)
plt.plot(range(1, k + 1), overall_accuracies, marker='o', label='Overall Accuracy')
plt.title('Overall Accuracy per Fold')
plt.xlabel('Fold')
plt.ylabel('Overall Accuracy')
plt.legend()

plt.subplot(2, 2, 3)
for cls in range(len(precision_scores_list[0])):
    plt.plot(range(1, k + 1), [precision_scores_list[i][cls] for i in range(k)], marker='o', label=f'Class {cls}')
plt.title('Precision per Fold')
plt.xlabel('Fold')
plt.ylabel('Precision')
plt.legend()

plt.subplot(2, 2, 4)
for cls in range(len(recall_scores_list[0])):
    plt.plot(range(1, k + 1), [recall_scores_list[i][cls] for i in range(k)], marker='o', label=f'Class {cls}')
plt.title('Recall per Fold')
plt.xlabel('Fold')
plt.ylabel('Recall')
plt.legend()

plt.tight_layout()
plt.savefig('k_fold_cross_validation.png')