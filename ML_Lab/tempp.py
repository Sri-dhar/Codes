import pandas as pd
from sklearn.datasets import load_iris
import numpy as np

def k_means_clustering(data, k, max_iter=100, tol=1e-4):
    np.random.seed(42)
    
    centroids = data[np.random.choice(data.shape[0], 1, replace=False)]
    for _ in range(1, k):
        distances = np.sqrt(np.sum((data[:, np.newaxis] - centroids) ** 2, axis=2))
        min_distances = np.min(distances, axis=1)
        probabilities = min_distances / np.sum(min_distances)
        centroids = np.vstack([centroids, data[np.random.choice(data.shape[0], 1, p=probabilities)]])

    for iteration in range(max_iter):
        distances = np.sqrt(np.sum((data[:, np.newaxis] - centroids) ** 2, axis=2))
        labels = np.argmin(distances, axis=1)

        new_centroids = np.array([np.mean(data[labels == i], axis=0) for i in range(k)])

        if np.linalg.norm(centroids - new_centroids) < tol:
            break

        centroids = new_centroids

    sse = np.sum((data - centroids[labels]) ** 2)

    return labels, sse, iteration + 1

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

    silhouette_values = (b - a) / np.maximum(a, b)
    return np.mean(silhouette_values)

iris = load_iris()
data = iris.data

k_values = [2, 3, 4, 5, 6]
results = []

for k in k_values:
    labels, sse, iterations = k_means_clustering(data, k)
    silhouette_avg = silhouette_score(data, labels)
    results.append((k, sse, iterations, silhouette_avg, labels))

print("K\tSSE\tIterations\tSilhouette Score\tCluster Assignments")
for k, sse, iterations, silhouette_avg, labels in results:
    print(f"{k}\t{sse:.3f}\t\t{iterations}\t\t{silhouette_avg:.3f}\t\t\n{labels}\n\n")
