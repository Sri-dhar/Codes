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
from itertools import product
import logging
import warnings
warnings.filterwarnings('ignore')

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

class MLClassifiers:
    def __init__(self, dataset_paths=None):
        self.datasets = {}
        if dataset_paths:
            for name, path in dataset_paths.items():
                try:
                    self.datasets[name] = pd.read_csv(path)
                    logging.info(f"Successfully loaded dataset: {name}")
                except Exception as e:
                    logging.error(f"Error loading dataset {name}: {str(e)}")
        else:
            from sklearn.datasets import load_iris, load_breast_cancer
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
            logging.info("Using default datasets: iris and breast_cancer")
        
        self.results = {}
        self.scaler = StandardScaler()
        self.param_grids = {
            'slp': {
                'max_iter': [500, 1000, 2000],
                'tol': [1e-3, 1e-4],
                'eta0': [0.1, 0.01, 0.001],
                'penalty': [None, 'l2'],
                'alpha': [0.0001, 0.001]
            },
            'mlp': {
                'hidden_layer_sizes': [(50,), (100,), (50, 50), (100, 50)],
                'activation': ['relu', 'tanh'],
                'learning_rate': ['constant', 'adaptive'],
                'max_iter': [1000, 2000],
                'alpha': [0.0001, 0.001],
                'solver': ['adam', 'sgd']
            },
            'knn': {
                'n_neighbors': [3, 5, 7, 9],
                'weights': ['uniform', 'distance'],
                'metric': ['euclidean', 'manhattan'],
                'algorithm': ['auto', 'ball_tree'],
                'leaf_size': [20, 30, 40]
            }
        }

    def prepare_data(self, dataset):
        X = dataset.iloc[:, :-1]
        y = dataset.iloc[:, -1]
        return X, y

    def implement_slp(self, X, y, params):
        params = params.copy()
        params['max_iter'] = int(params['max_iter'])
        model = Perceptron(**params, random_state=42)
        return model

    def implement_mlp(self, X, y, params):
        params = params.copy()
        params['max_iter'] = int(params['max_iter'])
        model = MLPClassifier(**params, random_state=42)
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
        logging.info(f"Starting hyperparameter tuning for {model_type}")
        param_grid = self.param_grids[model_type]
        best_params = None
        best_score = 0
        all_scores = []

        param_combinations = self.get_param_combinations(param_grid)
        
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
                    logging.warning(f"Error with parameters {params}: {str(e)}")
                    continue
            
            if scores:
                avg_score = np.mean(scores)
                all_scores.append({'params': params, 'score': avg_score})
                if avg_score > best_score:
                    best_score = avg_score
                    best_params = params.copy()

        if best_params is None:
            raise ValueError(f"No valid parameter combination found for {model_type}")

        logging.info(f"Best parameters found for {model_type}: {best_params}")
        return best_params, best_score, all_scores

    def check_overfitting(self, model, X, y, dataset_name, model_name):
        logging.info(f"Checking overfitting for {model_name} on {dataset_name}")
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
        
        train_scores = []
        test_scores = []
        train_sizes = np.linspace(0.1, 1.0, 10)
        
        plt.figure(figsize=(12, 6))
        
        # Learning curves
        plt.subplot(1, 2, 1)
        for size in train_sizes:
            X_subset = X_train[:int(len(X_train) * size)]
            y_subset = y_train[:int(len(y_train) * size)]
            
            model.fit(X_subset, y_subset)
            train_scores.append(model.score(X_subset, y_subset))
            test_scores.append(model.score(X_test, y_test))
        
        plt.plot(train_sizes, train_scores, 'o-', label='Training score', color='blue')
        plt.plot(train_sizes, test_scores, 'o-', label='Test score', color='red')
        plt.xlabel('Training set size')
        plt.ylabel('Accuracy')
        plt.title('Learning Curves')
        plt.legend()
        
        if hasattr(model, 'predict_proba'):
            plt.subplot(1, 2, 2)
            train_probs = model.predict_proba(X_train)
            test_probs = model.predict_proba(X_test)
            
            plt.hist(np.max(train_probs, axis=1), bins=20, alpha=0.5, label='Train', color='blue')
            plt.hist(np.max(test_probs, axis=1), bins=20, alpha=0.5, label='Test', color='red')
            plt.xlabel('Prediction Probability')
            plt.ylabel('Count')
            plt.title('Model Confidence Distribution')
            plt.legend()
        
        plt.tight_layout()
        plt.savefig(f'learning_curves_{dataset_name}_{model_name}.png')
        plt.close()

    def evaluate_model(self, model, X, y):
        kf = KFold(n_splits=3, shuffle=True, random_state=42)
        results = []
        
        for fold, (train_idx, test_idx) in enumerate(kf.split(X)):
            X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
            y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]
            
            model.fit(X_train, y_train)
            y_pred = model.predict(X_test)
            
            precision, recall, _, _ = precision_recall_fscore_support(y_test, y_pred, average=None)
            class_accuracy = []
            for class_label in np.unique(y):
                mask = y_test == class_label
                class_accuracy.append(accuracy_score(y_test[mask], y_pred[mask]))
            
            overall_precision, overall_recall, _, _ = precision_recall_fscore_support(y_test, y_pred, average='macro')
            overall_accuracy = accuracy_score(y_test, y_pred)
            
            results.append({
                'fold': fold + 1,
                'class_precision': precision,
                'class_recall': recall,
                'class_accuracy': class_accuracy,
                'overall_precision': overall_precision,
                'overall_recall': overall_recall,
                'overall_accuracy': overall_accuracy
            })
        
        return results

    def run_analysis(self):
        for dataset_name, dataset in self.datasets.items():
            logging.info(f"\nAnalyzing {dataset_name} dataset...")
            
            X, y = self.prepare_data(dataset)
            X = pd.DataFrame(self.scaler.fit_transform(X))
            
            dataset_results = {}
            
            for model_name in ['slp', 'mlp', 'knn']:
                logging.info(f"\nTraining {model_name}...")
                try:
                    best_params, best_score, all_scores = self.tune_hyperparameters(model_name, X, y)
                    
                    if model_name == 'slp':
                        model = self.implement_slp(X, y, best_params)
                    elif model_name == 'mlp':
                        model = self.implement_mlp(X, y, best_params)
                    else:
                        model = self.implement_knn(X, y, best_params)
                    
                    self.check_overfitting(model, X, y, dataset_name, model_name)
                    eval_results = self.evaluate_model(model, X, y)
                    
                    dataset_results[model_name] = {
                        'best_params': best_params,
                        'best_score': best_score,
                        'all_tuning_scores': all_scores,
                        'evaluation': eval_results
                    }
                    
                except Exception as e:
                    logging.error(f"Error training {model_name}: {str(e)}")
                    continue
            
            self.results[dataset_name] = dataset_results
        
        self.export_results()

    def export_results(self):
        logging.info("Exporting results to Excel...")
        with pd.ExcelWriter('ml_analysis_results.xlsx', engine='openpyxl') as writer:
            for dataset_name, dataset_results in self.results.items():
                params_data = []
                for model_name, results in dataset_results.items():
                    params_data.append({
                        'Model': model_name,
                        'Best Parameters': str(results['best_params']),
                        'Best Score': results['best_score'],
                        'Parameter Grid': str(self.param_grids[model_name])
                    })
                
                params_df = pd.DataFrame(params_data)
                params_df.to_excel(writer, sheet_name=f"{dataset_name[:10]}_params", index=False)
                
                perf_data = []
                for model_name, results in dataset_results.items():
                    eval_results = results['evaluation']
                    for result in eval_results:
                        for class_idx, (prec, rec, acc) in enumerate(zip(
                            result['class_precision'],
                            result['class_recall'],
                            result['class_accuracy']
                        )):
                            perf_data.append({
                                'Model': model_name,
                                'Fold': f"Fold {result['fold']}",
                                'Class': f"Class {class_idx}",
                                'Class Precision': prec,
                                'Class Recall': rec,
                                'Class Accuracy': acc,
                                'Overall Precision': result['overall_precision'],
                                'Overall Recall': result['overall_recall'],
                                'Overall Accuracy': result['overall_accuracy']
                            })
                
                perf_df = pd.DataFrame(perf_data)
                perf_df.to_excel(writer, sheet_name=f"{dataset_name[:10]}_metrics", index=False)
                
                summary_data = []
                for model_name, results in dataset_results.items():
                    eval_results = results['evaluation']
                    summary_data.append({
                        'Model': model_name,
                        'Average Overall Accuracy': np.mean([r['overall_accuracy'] for r in eval_results]),
                        'Average Overall Precision': np.mean([r['overall_precision'] for r in eval_results]),
                        'Average Overall Recall': np.mean([r['overall_recall'] for r in eval_results]),
                        'Best Parameters': str(results['best_params']),
                        'Best Validation Score': results['best_score']
                    })
                
                summary_df = pd.DataFrame(summary_data)
                summary_df.to_excel(writer, sheet_name=f"{dataset_name[:10]}_summary", index=False)

        logging.info("Results exported successfully to ml_analysis_results.xlsx")

if __name__ == "__main__":
    mlc = MLClassifiers()
    mlc.run_analysis()