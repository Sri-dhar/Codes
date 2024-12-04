import numpy as np
import pandas as pd

def load_iris_2 ():
    data = np.genfromtxt('iris.csv', delimiter=',', dtype=None, encoding=None)
    X = np.array([list(map(float, row[:-1])) for row in data])
    y = np.array([0 if row[-1] == 'Iris-setosa' else 1 if row[-1] == 'Iris-versicolor' else 2 for row in data])
    return X, y

def load_iris():
    data = pd.read_csv('iris.csv')
    X = data.iloc[:, :-1].values
    y = data.iloc[:, -1].values
    return X, y
    

def one_hot_encode(y, num_classes):
    return np.eye(num_classes)[y]

class SingleLayerPerceptron:
    def __init__(self, input_dim, num_classes, learning_rate=0.01):
        self.weights = np.random.rand(input_dim, num_classes) * 0.01
        self.bias = np.zeros((1, num_classes))
        self.learning_rate = learning_rate

    def softmax(self, logits):
        exp_scores = np.exp(logits - np.max(logits, axis=1, keepdims=True))
        return exp_scores / np.sum(exp_scores, axis=1, keepdims=True)

    def predict(self, X):
        logits = np.dot(X, self.weights) + self.bias
        return np.argmax(self.softmax(logits), axis=1)

    def train(self, X, y_one_hot, epochs=100):
        for epoch in range(epochs):
            logits = np.dot(X, self.weights) + self.bias
            probs = self.softmax(logits)
            
            error = probs - y_one_hot
            dW = np.dot(X.T, error) / X.shape[0]
            db = np.sum(error, axis=0, keepdims=True) / X.shape[0]
            
            self.weights -= self.learning_rate * dW
            self.bias -= self.learning_rate * db

def k_fold_split(X, y, k=5):
    indices = np.arange(X.shape[0])
    np.random.shuffle(indices)
    fold_size = len(indices) // k
    folds = [(indices[i * fold_size:(i + 1) * fold_size], 
              np.concatenate((indices[:i * fold_size], indices[(i + 1) * fold_size:]))) for i in range(k)]
    return folds

def calculate_metrics(y_true, y_pred, num_classes):
    precision = np.zeros(num_classes)
    recall = np.zeros(num_classes)
    accuracy = np.mean(y_true == y_pred)

    for c in range(num_classes):
        tp = np.sum((y_pred == c) & (y_true == c))
        fp = np.sum((y_pred == c) & (y_true != c))
        fn = np.sum((y_pred != c) & (y_true == c))
        
        precision[c] = tp / (tp + fp) if tp + fp > 0 else 0
        recall[c] = tp / (tp + fn) if tp + fn > 0 else 0

    return precision, recall, accuracy

def main():
    X, y = load_iris()
    num_classes = len(np.unique(y))
    X = (X - np.mean(X, axis=0)) / np.std(X, axis=0)  # Standardize the data
    y_one_hot = one_hot_encode(y, num_classes)
    
    learning_rate = 0.01
    epochs = 200
    k = 5

    folds = k_fold_split(X, y, k)
    overall_precisions, overall_recalls, overall_accuracies = [], [], []

    for fold_idx, (train_idx, test_idx) in enumerate(folds):
        X_train, X_test = X[train_idx], X[test_idx]
        y_train, y_test = y[train_idx], y[test_idx]
        y_train_one_hot = y_one_hot[train_idx]
        
        slp = SingleLayerPerceptron(input_dim=X.shape[1], num_classes=num_classes, learning_rate=learning_rate)
        slp.train(X_train, y_train_one_hot, epochs=epochs)

        y_pred = slp.predict(X_test)

        precision, recall, accuracy = calculate_metrics(y_test, y_pred, num_classes)
        overall_precisions.append(precision)
        overall_recalls.append(recall)
        overall_accuracies.append(accuracy)

        print(f"Fold {fold_idx + 1} - Precision: {precision}, Recall: {recall}, Accuracy: {accuracy:.4f}")

    avg_precision = np.mean(overall_precisions, axis=0)
    avg_recall = np.mean(overall_recalls, axis=0)
    avg_accuracy = np.mean(overall_accuracies)

    print(f"\nAverage Precision: {avg_precision}")
    print(f"Average Recall: {avg_recall}")
    print(f"Overall Accuracy: {avg_accuracy:.4f}")

main()

