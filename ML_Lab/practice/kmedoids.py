import numpy as np
import pandas as pd

def init_medoids(X, k):
    return X.sample(n=k).to_numpy()

def assign_clusters(X, medoids):
    distances = np.linalg.norm(X[:, np.newaxis] - medoids, axis=2)
    return np.argmin(distances, axis=1)

def update_medoids(X, labels, k):
    medoids = []
    for i in range(k):
        cluster_points = X[labels == i]
        if len(cluster_points) > 0:
            distances_sum = np.sum(np.linalg.norm(cluster_points[:, np.newaxis] - cluster_points, axis=2), axis=1)
            medoids.append(cluster_points[np.argmin(distances_sum)])
    return np.array(medoids)

def silhouette_score(X, labels, medoids):
    silhouette_vals = []
    for i in range(len(X)):
        same_cluster = X[labels == labels[i]]
        a = np.mean(np.linalg.norm(X[i] - same_cluster, axis=1))  # Mean intra-cluster distance

        nearest_cluster_idx = np.argmin([np.linalg.norm(X[i] - m) for j, m in enumerate(medoids) if j != labels[i]])
        nearest_cluster_points = X[labels == nearest_cluster_idx]
        b = np.mean(np.linalg.norm(X[i] - nearest_cluster_points, axis=1))  # Mean nearest-cluster distance

        silhouette_vals.append((b - a) / max(a, b))

    return np.mean(silhouette_vals)

def k_medoids(X, k, max_iters=100):
    medoids = init_medoids(X, k)
    for _ in range(max_iters):
        labels = assign_clusters(X.to_numpy(), medoids)
        new_medoids = update_medoids(X.to_numpy(), labels, k)
        if np.all(medoids == new_medoids):
            break
        medoids = new_medoids
    return labels, medoids

if __name__ == "__main__":
    X = pd.DataFrame(np.random.randn(300, 2), columns=["Feature1", "Feature2"])
    
    k = 3
    labels, medoids = k_medoids(X, k)
    silhouette_avg = silhouette_score(X.to_numpy(), labels, medoids)
    print(f"Silhouette Score: {silhouette_avg}")
