from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
import numpy as np

def k_means_clustering(data, k, true_labels, max_iter=100):
    unique_classes = np.unique(true_labels)
    centroids = np.zeros((k, data.shape[1]))
    for i in range(k):
        class_samples = data[true_labels == unique_classes[i]]
        centroids[i] = class_samples[0]  

    tol = 1e-4
    
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

iris = load_iris()
data = iris.data

k_values = [2, 3]
results = []
true_labels = iris.target

for k in k_values:
    labels, sse, iterations = k_means_clustering(data, k,true_labels=true_labels)   
    silhouette_avg = silhouette_score(data, labels)
    results.append((k, sse, iterations, silhouette_avg, labels))

print("K\tSSE\tIterations\tSilhouette Score\tCluster Assignments")
for k, sse, iterations, silhouette_avg, labels in results:
    print(f"{k}\t{sse:.3f}\t\t{iterations}\t\t{silhouette_avg:.3f}\t\t\n{labels}\n\n")

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

accuracy = calculating_accuracy(data, labels)
cm = confusion_mat(labels, data)

#saving the image of the plot to the folder
plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[3] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('Silhouette Score')
plt.title('Silhouette Score vs Number of Clusters')
plt.savefig('silhouette_scoreQ2.png')

plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[1] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('SSE')
plt.title('SSE vs Number of Clusters')
plt.savefig('SSEvsClustersQ2.png')

plt.figure(figsize=(12, 6))
plt.plot([result[0] for result in results], [result[2] for result in results], marker='o')
plt.xlabel('Number of Clusters')
plt.ylabel('Iterations')
plt.title('Iterations vs Number of Clusters')
plt.savefig('IterationsvsClustersQ2.png')

