import numpy as np
import pandas as pd
from collections import defaultdict
from typing import Tuple, List

class StandardScaler:
    """Custom implementation of StandardScaler using only NumPy"""
    def __init__(self):
        self.mean_ = None
        self.std_ = None
        
    def fit_transform(self, X: np.ndarray) -> np.ndarray:
        self.mean_ = np.mean(X, axis=0)
        self.std_ = np.std(X, axis=0)
        return (X - self.mean_) / self.std_
    
    def transform(self, X: np.ndarray) -> np.ndarray:
        return (X - self.mean_) / self.std_

class KMeans:
    def __init__(self, n_clusters: int, max_iters: int = 100, random_state: int = None):
        """
        Initialize K-means clustering algorithm
        
        Parameters:
        -----------
        n_clusters: int
            Number of clusters
        max_iters: int
            Maximum number of iterations for convergence
        random_state: int
            Random seed for reproducibility
        """
        self.n_clusters = n_clusters
        self.max_iters = max_iters
        self.random_state = random_state
        self.centroids = None
        self.labels_ = None
        self.inertia_ = None
        
    def _initialize_centroids(self, X: np.ndarray) -> np.ndarray:
        """Initialize centroids using random points from the dataset"""
        if self.random_state is not None:
            np.random.seed(self.random_state)
        
        n_samples = X.shape[0]
        random_indices = np.random.choice(n_samples, self.n_clusters, replace=False)
        return X[random_indices]
    
    def _assign_clusters(self, X: np.ndarray) -> np.ndarray:
        """Assign each point to the nearest centroid"""
        distances = np.sqrt(((X - self.centroids[:, np.newaxis])**2).sum(axis=2))
        return np.argmin(distances, axis=0)
    
    def _update_centroids(self, X: np.ndarray, labels: np.ndarray) -> np.ndarray:
        """Update centroids based on mean of points in each cluster"""
        new_centroids = np.array([X[labels == k].mean(axis=0) for k in range(self.n_clusters)])
        return new_centroids
    
    def _calculate_inertia(self, X: np.ndarray) -> float:
        """Calculate the sum of squared distances of samples to their closest centroid"""
        distances = np.sqrt(((X - self.centroids[self.labels_])**2).sum(axis=1))
        return np.sum(distances**2)
    
    def fit(self, X: np.ndarray) -> 'KMeans':
        """Fit K-means clustering to the data"""
        # Initialize centroids
        self.centroids = self._initialize_centroids(X)
        
        for _ in range(self.max_iters):
            # Store old centroids
            old_centroids = self.centroids.copy()
            
            # Assign clusters
            self.labels_ = self._assign_clusters(X)
            
            # Update centroids
            self.centroids = self._update_centroids(X, self.labels_)
            
            # Check convergence
            if np.all(old_centroids == self.centroids):
                break
                
        # Calculate inertia
        self.inertia_ = self._calculate_inertia(X)
        return self
    
    def predict(self, X: np.ndarray) -> np.ndarray:
        """Predict cluster labels for new data"""
        return self._assign_clusters(X)

def calculate_silhouette_score(X: np.ndarray, labels: np.ndarray) -> float:
    """
    Calculate silhouette score using only NumPy
    
    Parameters:
    -----------
    X: np.ndarray
        Input data
    labels: np.ndarray
        Cluster labels
        
    Returns:
    --------
    float
        Silhouette score
    """
    n_samples = X.shape[0]
    n_clusters = len(np.unique(labels))
    
    # Calculate pairwise distances
    distances = np.sqrt(((X[:, np.newaxis] - X)**2).sum(axis=2))
    
    silhouette_scores = []
    
    for i in range(n_samples):
        # Get current sample's cluster
        current_cluster = labels[i]
        
        # Calculate a (mean distance to points in same cluster)
        same_cluster_mask = labels == current_cluster
        same_cluster_mask[i] = False  # Exclude current point
        
        if np.sum(same_cluster_mask) > 0:
            a = np.mean(distances[i][same_cluster_mask])
        else:
            a = 0
            
        # Calculate b (mean distance to points in nearest different cluster)
        b_values = []
        for cluster in range(n_clusters):
            if cluster != current_cluster:
                other_cluster_mask = labels == cluster
                if np.sum(other_cluster_mask) > 0:
                    b_values.append(np.mean(distances[i][other_cluster_mask]))
        
        b = min(b_values) if b_values else 0
        
        # Calculate silhouette score for current point
        if a == 0 and b == 0:
            silhouette_scores.append(0)
        else:
            silhouette_scores.append((b - a) / max(a, b))
    
    return np.mean(silhouette_scores)

def evaluate_kmeans(X: np.ndarray, kmeans: KMeans) -> dict:
    """
    Evaluate K-means clustering using various metrics
    """
    metrics = {}
    
    # Calculate silhouette score
    metrics['silhouette_score'] = calculate_silhouette_score(X, kmeans.labels_)
    
    # Calculate inertia (within-cluster sum of squares)
    metrics['inertia'] = kmeans.inertia_
    
    # Calculate cluster sizes
    unique, counts = np.unique(kmeans.labels_, return_counts=True)
    metrics['cluster_sizes'] = dict(zip(unique, counts))
    
    return metrics

# Example usage
def main():
    # Generate sample data
    np.random.seed(42)
    X = np.concatenate([
        np.random.normal(0, 1, (100, 2)),
        np.random.normal(4, 1, (100, 2)),
        np.random.normal(-4, 1, (100, 2))
    ])
    
    # Create DataFrame
    df = pd.DataFrame(X, columns=['feature1', 'feature2'])
    
    # Standardize the features
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    # Initialize and fit K-means
    kmeans = KMeans(n_clusters=3, random_state=42)
    kmeans.fit(X_scaled)
    
    # Get evaluation metrics
    metrics = evaluate_kmeans(X_scaled, kmeans)
    
    # Print results
    print("K-means Clustering Results:")
    print("-" * 30)
    print(f"Silhouette Score: {metrics['silhouette_score']:.3f}")
    print(f"Inertia: {metrics['inertia']:.3f}")
    print("\nCluster Sizes:")
    for cluster, size in metrics['cluster_sizes'].items():
        print(f"Cluster {cluster}: {size} samples")
    
    # Add cluster labels to DataFrame
    df['Cluster'] = kmeans.labels_
    print("\nFirst few rows of clustered data:")
    print(df.head())

if __name__ == "__main__":
    main()