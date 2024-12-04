import pandas as pd
import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import Perceptron
from sklearn.model_selection import train_test_split, KFold
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import precision_recall_fscore_support, accuracy_score
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import load_iris, load_breast_cancer
from itertools import product   

class MLClassifiers:
    def __init__(self):
        iris = load_iris()
        breast_cancer = load_breast_cancer()
        self.datasets = {
            'iris': pd.DataFrame(
                data=np.c_[iris.data, iris.target],
                columns=[*iris.feature_names, 'target']
            ),
            'breast_cancer': pd.DataFrame(
                data=np.c_[breast_cancer.data, breast_cancer.target],
                columns=[*breast_cancer.feature_names, 'target']
            )
        }
        self.results = {}
        self.scaler = StandardScaler()

    def prepare_data(self, dataset):
        X = dataset.iloc[:, :-1]
        y = dataset.iloc[:, -1]
        return X, y
    
    def implement_slp(self, X, y, params):
        params = params.copy()
        params['max_iter'] = int(params['max_iter'])
        model = Perceptron(**params)
        return model
    
    def implement_mlp(self, X, y, params):
        params = params.copy()
        params['max_iter'] = int(params['max_iter'])
        model = MLPClassifier(**params)
        return model
    
    def implement_knn(self, X, y, params):
        params = params.copy()
        params['n_neighbors'] = int(params['n_neighbors'])
        model = KNeighborsClassifier(**params)
        return model

    def get_param_combinations(self, param_grid):
        keys = param_grid.keys()
        values = param_grid.values()
        combinations = list(product(*values))
        return [dict(zip(keys, combo)) for combo in combinations]
    
    def tune_hyperparameters(self, model_type, X, y):
        param_grid = {
            'slp': {
                'max_iter': [500, 1000],  # Plain Python integers
                'tol': [1e-3, 1e-4],
                'eta0': [0.1, 0.01]
            },
            'mlp': {
                'hidden_layer_sizes': [(50,), (100,), (50, 50)],
                'activation': ['relu', 'tanh'],
                'learning_rate': ['constant', 'adaptive'],
                'max_iter': [1000]  # Plain Python integer
            },
            'knn': {
                'n_neighbors': [3, 5, 7],  # Plain Python integers
                'weights': ['uniform', 'distance'],
                'metric': ['euclidean', 'manhattan']
            }
        }
        
        best_params = None
        best_score = 0
        
        param_combinations = self.get_param_combinations(param_grid[model_type])
        
        for params in param_combinations:
            kf = KFold(n_splits=3, shuffle=True, random_state=42)
            scores = []
            
            for train_idx, val_idx in kf.split(X):
                X_train, X_val = X.iloc[train_idx], X.iloc[val_idx]
                y_train, y_val = y.iloc[train_idx], y.iloc[val_idx]
                
                try:
                    if model_type == 'slp':
                        model = self.implement_slp(X_train, y_train, params)
                    elif model_type == 'mlp':
                        model = self.implement_mlp(X_train, y_train, params)
                    else:
                        model = self.implement_knn(X_train, y_train, params)
                    
                    model.fit(X_train, y_train)
                    score = model.score(X_val, y_val)
                    scores.append(score)
                except Exception as e:
                    print(f"Error with parameters {params}: {str(e)}")
                    continue
            
            if scores:  # Only update if we got valid scores
                avg_score = np.mean(scores)
                if avg_score > best_score:
                    best_score = avg_score
                    best_params = params.copy()
        
        if best_params is None:
            raise ValueError(f"No valid parameter combination found for {model_type}")
            
        return best_params, best_score
    
    def check_overfitting(self, model, X, y, dataset_name, model_name):
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
        
        train_scores = []
        test_scores = []
        train_sizes = np.linspace(0.1, 1.0, 10)
        
        for size in train_sizes:
            X_subset = X_train[:int(len(X_train) * size)]
            y_subset = y_train[:int(len(y_train) * size)]
            
            model.fit(X_subset, y_subset)
            train_scores.append(model.score(X_subset, y_subset))
            test_scores.append(model.score(X_test, y_test))
        
        plt.figure(figsize=(10, 6))
        plt.plot(train_sizes, train_scores, label='Training score')
        plt.plot(train_sizes, test_scores, label='Test score')
        plt.xlabel('Training set size')
        plt.ylabel('Accuracy')
        plt.title(f'Learning Curves - {model_name} on {dataset_name}')
        plt.legend()
        plt.savefig(f'learning_curves_{dataset_name}_{model_name}.png')
        plt.close()
    
    def evaluate_model(self, model, X, y):
        """Evaluate model using 3-fold cross validation"""
        kf = KFold(n_splits=3, shuffle=True, random_state=42)
        results = []
        
        for train_idx, test_idx in kf.split(X):
            X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
            y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]
            
            model.fit(X_train, y_train)
            y_pred = model.predict(X_test)
            
            precision, recall, _, _ = precision_recall_fscore_support(y_test, y_pred, average='macro')
            accuracy = accuracy_score(y_test, y_pred)
            
            results.append({
                'precision': precision,
                'recall': recall,
                'accuracy': accuracy
            })
        
        return results

    def run_analysis(self):
        for dataset_name, dataset in self.datasets.items():
            print(f"\nAnalyzing {dataset_name} dataset...")
            
            X, y = self.prepare_data(dataset)
            X = pd.DataFrame(self.scaler.fit_transform(X))
            
            dataset_results = {}
            
            for model_name in ['slp', 'mlp', 'knn']:
                print(f"\nTraining {model_name}...")
                try:
                    # Hyperparameter    tuning
                    best_params, best_score = self.tune_hyperparameters(model_name, X, y)
                    print(f"Best parameters: {best_params}")
                    print(f"Best score: {best_score:.4f}")
                    
                    # Train model with best parameters
                    if model_name == 'slp':
                        model = self.implement_slp(X, y, best_params)
                    elif model_name == 'mlp':
                        model = self.implement_mlp(X, y, best_params)
                    else:
                        model = self.implement_knn(X, y, best_params)
                    
                    # Check overfitting
                    self.check_overfitting(model, X, y, dataset_name, model_name)
                    
                    # Evaluate model
                    eval_results = self.evaluate_model(model, X, y)
                    
                    dataset_results[model_name] = {
                        'best_params': best_params,
                        'best_score': best_score,
                        'evaluation': eval_results
                    }
                except Exception as e:
                    print(f"Error training {model_name}: {str(e)}")
                    continue
            
            self.results[dataset_name] = dataset_results
        
        self.export_results()
    
    def export_results(self):
        """Export results to Excel using pandas"""
        with pd.ExcelWriter('ml_analysis_results.xlsx') as writer:
            for dataset_name, dataset_results in self.results.items():
                # Prepare hyperparameter tuning results
                params_data = []
                for model_name, results in dataset_results.items():
                    params_data.append({
                        'Model': model_name,
                        'Best Parameters': str(results['best_params']),
                        'Best Score': results['best_score']
                    })
                
                params_df = pd.DataFrame(params_data)
                params_df.to_excel(writer, sheet_name=f"{dataset_name}_hyperparameters", index=False)
                
                # Prepare performance results
                perf_data = []
                for model_name, results in dataset_results.items():
                    eval_results = results['evaluation']
                    for fold, fold_results in enumerate(eval_results):
                        perf_data.append({
                            'Model': model_name,
                            'Fold': f"Fold {fold+1}",
                            'Precision': fold_results['precision'],
                            'Recall': fold_results['recall'],
                            'Accuracy': fold_results['accuracy']
                        })
                
                perf_df = pd.DataFrame(perf_data)
                perf_df.to_excel(writer, sheet_name=f"{dataset_name}_performance", index=False)

if __name__ == "__main__":
    classifier = MLClassifiers()
    classifier.run_analysis()