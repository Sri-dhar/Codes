import numpy as np
import pandas as pd
from typing import Tuple, Dict, List
import warnings

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

class FuzzyCMeans:
    def __init__(self, n_clusters: int, m: float = 2.0, max_iters: int = 100, 
                 error_threshold: float = 1e-5, random_state: int = None):
        """
        Initialize Fuzzy C-means clustering algorithm
        
        Parameters:
        -----------
        n_clusters: int
            Number of clusters
        m: float
            Fuzziness coefficient (m > 1)
        max_iters: int
            Maximum number of iterations for convergence
        error_threshold: float
            Minimum improvement in objective function to continue iterations
        random_state: int
            Random seed for reproducibility
        """
        self.n_clusters = n_clusters
        self.m = m
        self.max_iters = max_iters
        self.error_threshold = error_threshold
        self.random_state = random_state
        self.centroids = None
        self.membership_matrix = None
        self.labels_ = None
        self.inertia_ = None
        self.n_iters_ = 0
        
    def _initialize_membership_matrix(self, n_samples: int) -> np.ndarray:
        """Initialize random membership matrix with constraints"""
        if self.random_state is not None:
            np.random.seed(self.random_state)
            
        membership_matrix = np.random.rand(n_samples, self.n_clusters)
        
        # Normalize rows to sum to 1
        row_sums = membership_matrix.sum(axis=1)
        membership_matrix = membership_matrix / row_sums[:, np.newaxis]
        
        return membership_matrix
    
    def _calculate_centroids(self, X: np.ndarray, membership_matrix: np.ndarray) -> np.ndarray:
        """Calculate cluster centroids using membership matrix"""
        # Calculate weights
        weights = membership_matrix ** self.m
        
        # Calculate weighted sum of points
        weighted_sum = np.dot(weights.T, X)
        weight_sums = weights.sum(axis=0)
        
        # Avoid division by zero
        weight_sums[weight_sums == 0] = 1
        
        # Calculate centroids
        centroids = weighted_sum / weight_sums[:, np.newaxis]
        return centroids
    
    def _calculate_distances(self, X: np.ndarray, centroids: np.ndarray) -> np.ndarray:
        """Calculate Euclidean distances between points and centroids"""
        distances = np.zeros((X.shape[0], self.n_clusters))
        
        for i in range(self.n_clusters):
            distances[:, i] = np.sum((X - centroids[i]) ** 2, axis=1)
            
        return distances
    
    def _update_membership_matrix(self, distances: np.ndarray) -> np.ndarray:
        """Update membership matrix using distances"""
        power = -2 / (self.m - 1)
        distances = np.power(distances, power)
        
        # Handle zero distances
        zero_distances = (distances == np.inf)
        if np.any(zero_distances):
            distances[zero_distances] = 1
            distances[~zero_distances] = 0
        else:
            # Normalize
            distances = distances / distances.sum(axis=1)[:, np.newaxis]
            
        return distances
    
    def _calculate_objective_function(self, X: np.ndarray, membership_matrix: np.ndarray, 
                                    centroids: np.ndarray) -> float:
        """Calculate objective function value"""
        distances = self._calculate_distances(X, centroids)
        weighted_distances = (membership_matrix ** self.m) * distances
        return np.sum(weighted_distances)
    
    def fit(self, X: np.ndarray) -> 'FuzzyCMeans':
        """Fit Fuzzy C-means clustering to the data"""
        n_samples = X.shape[0]
        
        # Initialize membership matrix
        self.membership_matrix = self._initialize_membership_matrix(n_samples)
        
        prev_objective = np.inf
        
        for iteration in range(self.max_iters):
            # Calculate centroids
            self.centroids = self._calculate_centroids(X, self.membership_matrix)
            
            # Calculate distances
            distances = self._calculate_distances(X, self.centroids)
            
            # Update membership matrix
            self.membership_matrix = self._update_membership_matrix(distances)
            
            # Calculate objective function
            current_objective = self._calculate_objective_function(X, self.membership_matrix, 
                                                                self.centroids)
            
            # Check convergence
            if abs(prev_objective - current_objective) < self.error_threshold:
                break
                
            prev_objective = current_objective
            self.n_iters_ = iteration + 1
            
        # Set final attributes
        self.labels_ = np.argmax(self.membership_matrix, axis=1)
        self.inertia_ = current_objective
        
        return self
    
    def predict(self, X: np.ndarray) -> np.ndarray:
        """Predict cluster membership for new data"""
        distances = self._calculate_distances(X, self.centroids)
        membership_matrix = self._update_membership_matrix(distances)
        return np.argmax(membership_matrix, axis=1)
    
    def predict_proba(self, X: np.ndarray) -> np.ndarray:
        """Predict cluster membership probabilities for new data"""
        distances = self._calculate_distances(X, self.centroids)
        return self._update_membership_matrix(distances)

def calculate_partition_coefficient(membership_matrix: np.ndarray) -> float:
    """Calculate partition coefficient (PC) index"""
    return np.mean(membership_matrix ** 2)

def calculate_partition_entropy(membership_matrix: np.ndarray) -> float:
    """Calculate partition entropy (PE) index"""
    with warnings.catch_warnings():
        warnings.simplefilter("ignore")
        log_memberships = np.log(membership_matrix)
        log_memberships[np.isneginf(log_memberships)] = 0
    return -np.mean(membership_matrix * log_memberships)

def calculate_xie_beni_index(X: np.ndarray, membership_matrix: np.ndarray, 
                           centroids: np.ndarray) -> float:
    """Calculate Xie-Beni index for cluster validation"""
    n_samples = X.shape[0]
    
    # Calculate minimum distance between centroids
    min_centroid_distance = np.inf
    for i in range(len(centroids)):
        for j in range(i + 1, len(centroids)):
            dist = np.sum((centroids[i] - centroids[j]) ** 2)
            min_centroid_distance = min(min_centroid_distance, dist)
    
    if min_centroid_distance == 0:
        return np.inf
    
    # Calculate sum of weighted squared distances
    distances = np.zeros((n_samples, len(centroids)))
    for i, centroid in enumerate(centroids):
        distances[:, i] = np.sum((X - centroid) ** 2, axis=1)
    
    weighted_distances = (membership_matrix ** 2) * distances
    total_variation = np.sum(weighted_distances)
    
    return total_variation / (n_samples * min_centroid_distance)

def evaluate_fuzzy_cmeans(X: np.ndarray, fcm: FuzzyCMeans) -> Dict:
    """Evaluate Fuzzy C-means clustering using various metrics"""
    metrics = {}
    
    # Calculate partition coefficient
    metrics['partition_coefficient'] = calculate_partition_coefficient(fcm.membership_matrix)
    
    # Calculate partition entropy
    metrics['partition_entropy'] = calculate_partition_entropy(fcm.membership_matrix)
    
    # Calculate Xie-Beni index
    metrics['xie_beni_index'] = calculate_xie_beni_index(X, fcm.membership_matrix, fcm.centroids)
    
    # Calculate inertia
    metrics['inertia'] = fcm.inertia_
    
    # Calculate number of iterations
    metrics['n_iterations'] = fcm.n_iters_
    
    # Calculate cluster sizes (based on highest membership)
    unique, counts = np.unique(fcm.labels_, return_counts=True)
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
    
    # Initialize and fit Fuzzy C-means
    fcm = FuzzyCMeans(n_clusters=3, random_state=42)
    fcm.fit(X_scaled)
    
    # Get evaluation metrics
    metrics = evaluate_fuzzy_cmeans(X_scaled, fcm)
    
    # Print results
    print("Fuzzy C-means Clustering Results:")
    print("-" * 30)
    print(f"Partition Coefficient: {metrics['partition_coefficient']:.3f}")
    print(f"Partition Entropy: {metrics['partition_entropy']:.3f}")
    print(f"Xie-Beni Index: {metrics['xie_beni_index']:.3f}")
    print(f"Inertia: {metrics['inertia']:.3f}")
    print(f"Number of Iterations: {metrics['n_iterations']}")
    
    print("\nCluster Sizes:")
    for cluster, size in metrics['cluster_sizes'].items():
        print(f"Cluster {cluster}: {size} samples")
    
    # Add cluster labels and membership probabilities to DataFrame
    df['Cluster'] = fcm.labels_
    membership_probs = pd.DataFrame(
        fcm.membership_matrix,
        columns=[f'Cluster_{i}_Probability' for i in range(fcm.n_clusters)]
    )
    df = pd.concat([df, membership_probs], axis=1)
    
    print("\nFirst few rows of clustered data with membership probabilities:")
    print(df.head())

if __name__ == "__main__":
    main()