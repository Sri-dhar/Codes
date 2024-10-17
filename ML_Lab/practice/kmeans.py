import numpy as np
import pandas as pd

# Function to initialize centroids randomly
def init_centroids(X, k):
    return X.sample(n=k).to_numpy()

# Function to assign clusters
def assign_clusters(X, centroids):
    distances = np.linalg.norm(X[:, np.newaxis] - centroids, axis=2)
    return np.argmin(distances, axis=1)

# Function to update centroids
def update_centroids(X, labels, k):
    centroids = np.array([X[labels == i].mean(axis=0) for i in range(k)])
    return centroids

# Function to calculate the silhouette score
def silhouette_score(X, labels, centroids):
    silhouette_vals = []
    for i in range(len(X)):
        # Same cluster points
        same_cluster = X[labels == labels[i]]
        a = np.mean(np.linalg.norm(X[i] - same_cluster, axis=1))  # Mean intra-cluster distance

        # Nearest cluster points
        nearest_cluster_idx = np.argmin([np.linalg.norm(X[i] - c) for j, c in enumerate(centroids) if j != labels[i]])
        nearest_cluster_points = X[labels == nearest_cluster_idx]
        b = np.mean(np.linalg.norm(X[i] - nearest_cluster_points, axis=1))  # Mean nearest-cluster distance

        # Silhouette score for each point
        silhouette_vals.append((b - a) / max(a, b))

    return np.mean(silhouette_vals)

# K-Means algorithm
def k_means(X, k, max_iters=100):
    centroids = init_centroids(X, k)
    for _ in range(max_iters):
        labels = assign_clusters(X.to_numpy(), centroids)
        new_centroids = update_centroids(X.to_numpy(), labels, k)
        if np.all(centroids == new_centroids):
            break
        centroids = new_centroids
    return labels, centroids

# Example usage
if __name__ == "__main__":

    X = pd.DataFrame(np.random.randn(300, 2), columns=["Feature1", "Feature2"])
    
    k = 3
    labels, centroids = k_means(X, k)
    print(centroids.dtype)
    print(f"Centroids: {centroids}")
    print(f"Labels: {labels}")

    
    silhouette_avg = silhouette_score(X.to_numpy(), labels, centroids)
    print(f"Silhouette Score: {silhouette_avg}")
