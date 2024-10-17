import numpy as np
import pandas as pd

def init_membership(X, k):
    membership_matrix = np.random.rand(len(X), k)
    membership_matrix = membership_matrix / membership_matrix.sum(axis=1, keepdims=True)
    return membership_matrix

def update_centroids(X, membership_matrix, m):
    powered_membership = membership_matrix ** m
    centroids = np.dot(powered_membership.T, X) / np.sum(powered_membership.T, axis=1, keepdims=True)
    return centroids

def update_membership(X, centroids, m):
    distances = np.linalg.norm(X[:, np.newaxis] - centroids, axis=2)
    distances = np.fmax(distances, np.finfo(np.float64).eps)
    inverted_distances = 1.0 / distances
    membership_matrix = (inverted_distances ** (2 / (m - 1))) / np.sum(inverted_distances ** (2 / (m - 1)), axis=1, keepdims=True)
    return membership_matrix

def calculate_objective(X, centroids, membership_matrix, m):
    powered_membership = membership_matrix ** m
    distances = np.linalg.norm(X[:, np.newaxis] - centroids, axis=2) ** 2
    return np.sum(powered_membership * distances)

def fuzzy_c_means(X, k, m=2, max_iters=100, tolerance=1e-4):
    membership_matrix = init_membership(X, k)
    for _ in range(max_iters):
        centroids = update_centroids(X, membership_matrix, m)
        
        new_membership_matrix = update_membership(X, centroids, m)
        
        if np.linalg.norm(new_membership_matrix - membership_matrix) < tolerance:
            break
        
        membership_matrix = new_membership_matrix
    
    return membership_matrix, centroids

def fuzzy_silhouette_score(X, membership_matrix, centroids):
    silhouette_vals = []
    for i in range(len(X)):
        cluster_membership = membership_matrix[i]
        
        a = np.sum(cluster_membership * np.linalg.norm(X[i] - centroids, axis=1))
        
        nearest_cluster_idx = np.argmin([np.linalg.norm(X[i] - c) for j, c in enumerate(centroids)])
        b = np.linalg.norm(X[i] - centroids[nearest_cluster_idx])
        
        silhouette_vals.append((b - a) / max(a, b))
    
    return np.mean(silhouette_vals)

if __name__ == "__main__":
    X = pd.DataFrame(np.random.randn(300, 2), columns=["Feature1", "Feature2"]).to_numpy()
    
    k = 3 # Number of clusters
    m = 2 # Fuzziness parameter
    membership_matrix, centroids = fuzzy_c_means(X, k, m)
    
    silhouette_avg = fuzzy_silhouette_score(X, membership_matrix, centroids)
    print(f"Silhouette Score: {silhouette_avg}")
