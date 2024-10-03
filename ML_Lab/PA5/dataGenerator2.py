import pandas as pd
import numpy as np

np.random.seed(42)

n_entries = 200

age = np.random.randint(18, 80, n_entries)
monthly_charges = np.random.uniform(20, 200, n_entries).round(2)
contract_types = np.random.choice(['Monthly', 'One year', 'Two year'], n_entries)
tenure = np.random.randint(1, 72, n_entries)

def churn_probability(age, monthly_charges, contract_type, tenure):
    prob = 0.1  # Base probability
    if age < 30:
        prob += 0.1
    elif age > 60:
        prob += 0.05
    
    if monthly_charges > 100:
        prob += 0.15
    
    if contract_type == 'Monthly':
        prob += 0.2
    elif contract_type == 'One year':
        prob += 0.05
    
    if tenure < 12:
        prob += 0.15
    elif tenure > 36:
        prob -= 0.1
    
    return min(max(prob, 0), 1)  # Ensure probability is between 0 and 1

def churn_type(prob):
    if prob < 0.3:
        return 'No Churn'
    elif prob < 0.6:
        return 'Voluntary Churn'
    else:
        return 'Involuntary Churn'

churn_probs = [churn_probability(a, m, c, t) for a, m, c, t in zip(age, monthly_charges, contract_types, tenure)]
churn_types = [churn_type(p) for p in churn_probs]

df = pd.DataFrame({
    'Age': age,
    'MonthlyCharges': monthly_charges,
    'ContractType': contract_types,
    'Tenure': tenure,
    'ChurnType': churn_types
})

print(df.head())
print("\nDataset Info:")
print(df.info())
print("\nDataset Description:")
print(df.describe())

print("\nChurn Distribution:")
print(df['ChurnType'].value_counts(normalize=True))

df.to_csv('customer_churn_dataset2.csv', index=False)
print("\nDataset saved as 'customer_churn_dataset2.csv'")