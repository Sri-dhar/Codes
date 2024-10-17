import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

# Sigmoid function
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# Logistic Regression Model class
class LogisticRegression:
    def __init__(self, learning_rate=0.01, max_iters=1000):
        self.learning_rate = learning_rate
        self.max_iters = max_iters
        self.weights = None
        self.bias = None
    
    # Fit model to training data
    def fit(self, X, y):
        n_samples, n_features = X.shape
        
        # Initialize weights and bias
        self.weights = np.zeros(n_features)
        self.bias = 0
        
        # Gradient descent
        for i in range(self.max_iters):
            # Linear model
            linear_model = np.dot(X, self.weights) + self.bias
            # Apply sigmoid function
            y_predicted = sigmoid(linear_model)
            
            # Compute gradients
            dw = (1 / n_samples) * np.dot(X.T, (y_predicted - y))
            db = (1 / n_samples) * np.sum(y_predicted - y)
            
            # Update weights and bias
            self.weights -= self.learning_rate * dw
            self.bias -= self.learning_rate * db

            # (Optional) Print loss every 100 iterations for debugging
            if i % 100 == 0:
                loss = -np.mean(y * np.log(y_predicted + 1e-15) + (1 - y) * np.log(1 - y_predicted + 1e-15))
                print(f"Iteration {i}, Loss: {loss:.4f}")
    
    # Predict probabilities
    def predict_proba(self, X):
        linear_model = np.dot(X, self.weights) + self.bias
        return sigmoid(linear_model)
    
    # Predict binary classes
    def predict(self, X, threshold=0.35):
        y_pred_proba = self.predict_proba(X)
        y_pred = [1 if i >= threshold else 0 for i in y_pred_proba]
        return np.array(y_pred)

# Accuracy metrics
def accuracy(y_true, y_pred):
    return np.sum(y_true == y_pred) / len(y_true)

def precision(y_true, y_pred):
    tp = np.sum((y_true == 1) & (y_pred == 1))
    fp = np.sum((y_true == 0) & (y_pred == 1))
    return tp / (tp + fp) if (tp + fp) > 0 else 0

def recall(y_true, y_pred):
    tp = np.sum((y_true == 1) & (y_pred == 1))
    fn = np.sum((y_true == 1) & (y_pred == 0))
    return tp / (tp + fn) if (tp + fn) > 0 else 0

def f1_score(y_true, y_pred):
    prec = precision(y_true, y_pred)
    rec = recall(y_true, y_pred)
    return 2 * (prec * rec) / (prec + rec) if (prec + rec) > 0 else 0

# Confusion matrix
def confusion_matrix(y_true, y_pred):
    tp = np.sum((y_true == 1) & (y_pred == 1))
    tn = np.sum((y_true == 0) & (y_pred == 0))
    fp = np.sum((y_true == 0) & (y_pred == 1))
    fn = np.sum((y_true == 1) & (y_pred == 0))
    
    return np.array([[tn, fp], [fn, tp]])

# Load data and preprocess (this function can be modified for different datasets)
def load_and_preprocess_data(filepath):
    df = pd.read_csv(filepath)
    # Replace this with actual preprocessing steps for your dataset
    df = df.dropna()  # Drop missing values
    X = df.iloc[:, :-1].values  # Features (everything except last column)
    y = df.iloc[:, -1].values   # Labels (last column)
    
    # Normalize features (optional but often useful)
    X = (X - np.mean(X, axis=0)) / np.std(X, axis=0)
    
    return X, y

# Evaluate model performance
def evaluate_model(y_true, y_pred):
    print(f"Accuracy: {accuracy(y_true, y_pred):.4f}")
    print(f"Precision: {precision(y_true, y_pred):.4f}")
    print(f"Recall: {recall(y_true, y_pred):.4f}")
    print(f"F1 Score: {f1_score(y_true, y_pred):.4f}")
    print("Confusion Matrix:")
    print(confusion_matrix(y_true, y_pred))

# Example usage
if __name__ == "__main__":
    # Load and preprocess data (replace 'your_dataset.csv' with your actual file path)
    X, y = load_and_preprocess_data('dataset.csv')
    
    # Split dataset into training and testing (80% train, 20% test)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    
    # Train Logistic Regression model
    model = LogisticRegression(learning_rate=0.01, max_iters=1000)
    model.fit(X_train, y_train)
    
    # Predict on test set
    y_pred = model.predict(X_test)
    
    # Evaluate performance
    evaluate_model(y_test, y_pred)
    
    # Print the clusters (i.e., data points predicted as 0 and 1)
    cluster_0 = X_test[y_pred == 0]
    cluster_1 = X_test[y_pred == 1]

    print("\nCluster 0 (Predicted as Class 0):")
    print(cluster_0)
    
    print("\nCluster 1 (Predicted as Class 1):")
    print(cluster_1)

