import numpy as np
import pandas as pd
from typing import Tuple, List, Dict
from collections import defaultdict

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

class KMedoids:
    def __init__(self, n_clusters: int, max_iters: int = 100, random_state: int = None):
        """
        Initialize K-medoids clustering algorithm
        
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
        self.medoids_indices = None
        self.medoids = None
        self.labels_ = None
        self.inertia_ = None
        
    def _calculate_distance_matrix(self, X: np.ndarray) -> np.ndarray:
        """Calculate pairwise distance matrix using Manhattan distance"""
        n_samples = X.shape[0]
        distances = np.zeros((n_samples, n_samples))
        
        for i in range(n_samples):
            distances[i] = np.sum(np.abs(X - X[i]), axis=1)
            
        return distances
    
    def _initialize_medoids(self, n_samples: int) -> np.ndarray:
        """Initialize medoids randomly"""
        if self.random_state is not None:
            np.random.seed(self.random_state)
            
        return np.random.choice(n_samples, self.n_clusters, replace=False)
    
    def _assign_clusters(self, distances: np.ndarray) -> np.ndarray:
        """Assign each point to the nearest medoid"""
        return np.argmin(distances[:, self.medoids_indices], axis=1)
    
    def _update_medoids(self, X: np.ndarray, distances: np.ndarray, labels: np.ndarray) -> Tuple[np.ndarray, float]:
        """Update medoids by selecting the point that minimizes total distance within each cluster"""
        new_medoids_indices = np.array(self.medoids_indices)
        total_cost = np.inf
        
        for cluster_idx in range(self.n_clusters):
            cluster_points = np.where(labels == cluster_idx)[0]
            
            if len(cluster_points) == 0:
                continue
                
            # Calculate total distance for each point in cluster as potential medoid
            cluster_distances = distances[cluster_points][:, cluster_points]
            costs = np.sum(cluster_distances, axis=1)
            
            # Select point with minimum total distance as new medoid
            best_point_idx = cluster_points[np.argmin(costs)]
            new_medoids_indices[cluster_idx] = best_point_idx
            
        # Calculate total cost with new medoids
        new_distances = distances[:, new_medoids_indices]
        new_labels = np.argmin(new_distances, axis=1)
        new_total_cost = np.sum(np.min(new_distances, axis=1))
        
        return new_medoids_indices, new_total_cost
    
    def fit(self, X: np.ndarray) -> 'KMedoids':
        """Fit K-medoids clustering to the data"""
        n_samples = X.shape[0]
        
        # Calculate distance matrix
        distances = self._calculate_distance_matrix(X)
        
        # Initialize medoids
        self.medoids_indices = self._initialize_medoids(n_samples)
        best_cost = np.inf
        
        for _ in range(self.max_iters):
            # Assign clusters
            self.labels_ = self._assign_clusters(distances)
            
            # Update medoids
            new_medoids_indices, new_cost = self._update_medoids(X, distances, self.labels_)
            
            # Check for convergence
            if new_cost >= best_cost:
                break
                
            self.medoids_indices = new_medoids_indices
            best_cost = new_cost
        
        # Store final medoids and inertia
        self.medoids = X[self.medoids_indices]
        self.inertia_ = best_cost
        
        return self
    
    def predict(self, X: np.ndarray) -> np.ndarray:
        """Predict cluster labels for new data"""
        distances = np.array([np.sum(np.abs(X - medoid), axis=1) for medoid in self.medoids])
        return np.argmin(distances, axis=0)

def calculate_silhouette_score(X: np.ndarray, labels: np.ndarray) -> float:
    """Calculate silhouette score using Manhattan distance"""
    n_samples = X.shape[0]
    n_clusters = len(np.unique(labels))
    
    # Calculate pairwise distances
    distances = np.zeros((n_samples, n_samples))
    for i in range(n_samples):
        distances[i] = np.sum(np.abs(X - X[i]), axis=1)
    
    silhouette_scores = []
    
    for i in range(n_samples):
        current_cluster = labels[i]
        
        # Calculate a (mean distance to points in same cluster)
        same_cluster_mask = labels == current_cluster
        same_cluster_mask[i] = False
        
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

def evaluate_kmedoids(X: np.ndarray, kmedoids: KMedoids) -> Dict:
    """Evaluate K-medoids clustering using various metrics"""
    metrics = {}
    
    # Calculate silhouette score
    metrics['silhouette_score'] = calculate_silhouette_score(X, kmedoids.labels_)
    
    # Calculate inertia (sum of distances to medoids)
    metrics['inertia'] = kmedoids.inertia_
    
    # Calculate cluster sizes
    unique, counts = np.unique(kmedoids.labels_, return_counts=True)
    metrics['cluster_sizes'] = dict(zip(unique, counts))
    
    return metrics

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
    
    # Initialize and fit K-medoids
    kmedoids = KMedoids(n_clusters=3, random_state=42)
    kmedoids.fit(X_scaled)
    
    # Get evaluation metrics
    metrics = evaluate_kmedoids(X_scaled, kmedoids)
    
    # Print results
    print("K-medoids Clustering Results:")
    print("-" * 30)
    print(f"Silhouette Score: {metrics['silhouette_score']:.3f}")
    print(f"Inertia: {metrics['inertia']:.3f}")
    print("\nCluster Sizes:")
    for cluster, size in metrics['cluster_sizes'].items():
        print(f"Cluster {cluster}: {size} samples")
    
    # Add cluster labels to DataFrame
    df['Cluster'] = kmedoids.labels_
    print("\nFirst few rows of clustered data:")
    print(df.head())
    
    # Print medoid indices
    print("\nMedoid Indices:")
    print(kmedoids.medoids_indices)

if __name__ == "__main__":
    main()