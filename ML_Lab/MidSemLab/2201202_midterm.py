import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def k_means_clustering(data, k, max_iter=100, tol=1e-3):
    np.random.seed(42)
    
    centroids = data[np.random.choice(data.shape[0], 1, replace=True)]
    
    for _ in range(1, k):
        distances = np.sqrt(np.sum((data[:, np.newaxis] - centroids) ** 2, axis=2))
        min_dis = np.min(distances, axis=1)
        prob = min_dis / np.sum(min_dis)
        centroids = np.vstack([centroids, data[np.random.choice(data.shape[0], 1, p=prob)]])

    for iteration in range(max_iter):
        distances = np.sqrt(np.sum((data[:, np.newaxis] - centroids) ** 2, axis=2))
        labels = np.argmin(distances, axis=1)

        new_centroids = np.array([np.mean(data[labels == i], axis=0) for i in range(k)])

        if np.linalg.norm(centroids - new_centroids) < tol:
            break

        centroids = new_centroids

    sse = np.sum((data - centroids[labels]) ** 2)

    return labels, sse, iteration + 1

def k_means_attempt_2(data, k, max_iter=100):
    np.random.seed(42)
    
    centroids = data[np.random.choice(data.shape[0], k, replace=False)]
    
    for iteration in range(max_iter):
        distances = np.sqrt(np.sum((data[:, np.newaxis] - centroids) ** 2))
        labels = np.argmin(distances, axis=0)  
        new_centroids = np.array([np.mean(data[labels == i], axis=0) for i in range(k)])
        if np.all(centroids == new_centroids):  
            break
        
        centroids = new_centroids

    sse = np.sum((data - centroids[labels]) ** 2) 

    return labels, sse, iteration + 1

def silhoutte_function(a,b):
    return (b-a)/np.maximum(a,b)

def silhouette_score(data, labels):
    n_samples = data.shape[0]
    unique_labels = np.unique(labels)
    a = np.zeros(n_samples)
    b = np.zeros(n_samples)

    for i in range(n_samples):
        same_cluster = data[labels == labels[i]]
        other_clusters = data[labels != labels[i]]

        if len(same_cluster) > 1:
            a[i] = np.mean(np.linalg.norm(same_cluster - data[i], axis=1))
        else:
            a[i] = 0  

        if len(other_clusters) > 0:
            b[i] = np.min([np.mean(np.linalg.norm(other_clusters - data[i], axis=1)) for label in unique_labels if label != labels[i]])
        else:
            b[i] = 0  

    silhouette_values = silhoutte_function(a,b)
    return np.mean(silhouette_values)

df = pd.read_csv("iris_dataset.csv")
df = df.drop(['target'], axis=1)
df = df.iloc[1:]
data = np.array(df)


print("the csv data is:::")
print(df)
print("="*20 +" end of csv data "+"="*20)
print()


k_values = [2, 3, 5, 7, 10, 20]
results = []

for k in k_values:
    labels, sse, iterations = k_means_clustering(data, k)
    silhouette_avg = silhouette_score(data, labels)
    results.append((k, sse, iterations, silhouette_avg, labels))
    
def calculating_accuracy(data, labels):
    n_samples = data.shape[0]
    unique_labels = np.unique(labels)
    a = np.zeros(n_samples)
    b = np.zeros(n_samples)

    for i in range(n_samples):
        same_cluster = data[labels == labels[i]]
        other_clusters = data[labels != labels[i]]

        if len(same_cluster) > 1:
            a[i] = np.mean(np.linalg.norm(same_cluster - data[i], axis=1))
        else:
            a[i] = 0  

        if len(other_clusters) > 0:
            b[i] = np.min([np.mean(np.linalg.norm(other_clusters - data[i], axis=1)) for label in unique_labels if label != labels[i]])
        else:
            b[i] = 0  

    silhouette_values = silhoutte_function(a,b)
    return np.mean(silhouette_values)

def confusion_mat(labels, data):
    n_samples = data.shape[0]
    unique_labels = np.unique(labels)
    a = np.zeros(n_samples)
    b = np.zeros(n_samples)
    for i in range(n_samples):
        same_cluster = data[labels == labels[i]]
        other_clusters = data[labels != labels[i]]
        if len(same_cluster) > 1:
            a[i] = np.mean(np.linalg.norm(same_cluster - data[i], axis=1))
        else:
            a[i] = 0  
        if len(other_clusters) > 0:
            b[i] = np.min([np.mean(np.linalg.norm(other_clusters - data[i], axis=1)) for label in unique_labels if label != labels[i]])
        else:
            b[i] = 0  
    silhouette_values = silhoutte_function(a,b)
    return np.mean(silhouette_values)

print("K\tSSE\tIterations\tSilhouette Score\tCluster Assignments")
for k, sse, iterations, silhouette_avg, labels in results:
    print(f"{k}\t{sse:.3f}\t\t{iterations}\t\t{silhouette_avg:.3f}\t\t\n{labels}\n\n")

acc = calculating_accuracy(data, labels)
cm = confusion_mat(labels, data)

plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[3] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('Silhouette Score')
plt.title('Silhouette Score vs Number of Clusters')
plt.savefig('silhouette_score.png')

plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[1] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('SSE')
plt.title('SSE vs Number of Clusters')
plt.savefig('SSE_vs_clusters.png')

plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[2] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('Iterations')
plt.title('Iterations vs Number of Clusters')
plt.savefig('Iterations_vs_clusters.png')

print(30*"==")
print("Part one of question done")
print(30*"==")

'''or each cluster, select the 25 samples that are closest to the centroid. These selected
samples, along with their class labels, will form the training and validation set for
your logistic regression model. The remaining data will serve as the test set. Apply
Logistic Regression to the selected samples and evaluate the model.
For example, if K-means clustering results in 3 clusters, you would select 25 samples
from each cluster closest to the centroid, yielding 75 samples in total. These 75
samples will be used as the training and validation set (divided in any ratio), while the
remaining data will form the test set. Perform Logistic Regression on these samples
and report the model’s performance outcomes'''


labels, sse, iterations = k_means_clustering(data, 3, 1000, tol=0.001)
print(labels)

training_set = []   
validation_set = []
test_set = []

for i in range(3):
    cluster = data[labels == i]
    centroid = np.mean(cluster, axis=0)
    distances = np.linalg.norm(cluster - centroid, axis=1)
    indices = np.argsort(distances)
    training_set.extend(cluster[indices[:25]])
    validation_set.extend(cluster[indices[25:50]])
    test_set.extend(cluster[indices[50:]])
    
training_set = np.array(training_set)
validation_set = np.array(validation_set)
test_set = np.array(test_set)

print("=="*20)
print("Training Set :\n")
print(training_set)
print("\nValidation Set :\n")
print(validation_set)
print("\nTesting Set :\n")
print(test_set)
print("=="*20)

print("Training Set Shape:", training_set.shape)
print("Validation Set Shape:", validation_set.shape)
print("Test Set Shape:", test_set.shape)

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def logistic_regression(X, y, learning_rate=0.01, max_iter=1000, tol=1e-3):
    X = np.hstack([np.ones((X.shape[0], 1)), X])
    theta = np.zeros(X.shape[1])
    
    for iteration in range(max_iter):
        z = np.dot(X, theta)
        h = sigmoid(z)
        gradient = np.dot(X.T, (h - y)) / y.size
        theta -= learning_rate * gradient
        
        if np.linalg.norm(learning_rate * gradient) < tol:
            break
            
    return theta

def predict(X, theta):
    X = np.hstack([np.ones((X.shape[0], 1)), X])
    return sigmoid(np.dot(X, theta))

X_train = training_set[:, :-1]
y_train = training_set[:, -1]

theta = logistic_regression(X_train, y_train)

X_val = validation_set[:, :-1]
y_val = validation_set[:, -1]

predictions = predict(X_val, theta)
predictions = np.where(predictions >= 0.5, 1, 0)

accuracy = np.mean(predictions == y_val)
print("Accuracy on Validation set:", accuracy)

X_test = test_set[:, :-1]
y_test = test_set[:, -1]

predictions = predict(X_test, theta)
predictions = np.where(predictions >= 0.5, 1, 0)

accuracy = np.mean(predictions == y_test)
print("Accuracy on Testing Set:", accuracy)

print(30*"==")
print("Part two of question done")
print(30*"==")
