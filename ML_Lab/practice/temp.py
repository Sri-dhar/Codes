import pandas as pd
import numpy as np

data = pd.read_csv('iris_dataset.csv')
X = data.iloc[:, :-1].values  
y = data.iloc[:, -1].values  

class KMeans:
    def __init__(self, n_clusters, max_iter=300):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centroids = None

    def fit(self, X):
        n_samples, _ = X.shape
        random_indices = np.random.choice(n_samples, self.n_clusters, replace=False)
        self.centroids = X[random_indices]

        for _ in range(self.max_iter):
            distances = np.linalg.norm(X[:, np.newaxis] - self.centroids, axis=2)
            labels = np.argmin(distances, axis=1)

            new_centroids = np.array([X[labels == i].mean(axis=0) for i in range(self.n_clusters)])
            if np.all(new_centroids == self.centroids):
                break
            self.centroids = new_centroids

        return labels

class LogisticRegression:
    def __init__(self, learning_rate=0.01, n_iter=1000):
        self.learning_rate = learning_rate
        self.n_iter = n_iter
        self.weights = None
        self.bias = None

    def fit(self, X, y):
        n_samples, n_features = X.shape
        self.weights = np.zeros(n_features)
        self.bias = 0

        y_encoded = pd.get_dummies(y).values

        for _ in range(self.n_iter):
            linear_model = np.dot(X, self.weights) + self.bias
            y_predicted = self.sigmoid(linear_model)

            dw = (1 / n_samples) * np.dot(X.T, (y_predicted - y_encoded))
            db = (1 / n_samples) * np.sum(y_predicted - y_encoded)

            self.weights -= self.learning_rate * dw
            self.bias -= self.learning_rate * db

    def predict(self, X):
        linear_model = np.dot(X, self.weights) + self.bias
        y_predicted = self.sigmoid(linear_model)
        return np.argmax(y_predicted, axis=1)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

kmeans = KMeans(n_clusters=3)
labels = kmeans.fit(X)

closest_samples = []
for i in range(kmeans.n_clusters):
    cluster_indices = np.where(labels == i)[0]
    cluster_samples = X[cluster_indices]
    centroid = kmeans.centroids[i]
    distances = np.linalg.norm(cluster_samples - centroid, axis=1)
    closest_indices = np.argsort(distances)[:25]
    closest_samples.extend(cluster_indices[closest_indices])

train_val_data = data.iloc[closest_samples]
train_val_X = train_val_data.iloc[:, :-1].values
train_val_y = train_val_data.iloc[:, -1].values

split_index = int(len(train_val_X) * 0.7)
X_train, X_val = train_val_X[:split_index], train_val_X[split_index:]
y_train, y_val = train_val_y[:split_index], train_val_y[split_index:]

model = LogisticRegression(learning_rate=0.01, n_iter=1000)
model.fit(X_train, y_train)

y_pred = model.predict(X_val)

accuracy = np.mean(y_pred == np.argmax(pd.get_dummies(y_val).values, axis=1))
print("Accuracy on validation set:", accuracy)

conf_matrix = pd.crosstab(pd.Series(y_val), pd.Series(y_pred), rownames=['Actual'], colnames=['Predicted'])
print("Confusion Matrix:\n", conf_matrix)
