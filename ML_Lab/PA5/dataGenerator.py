import pandas as pd
import numpy as np

# Set random seed for reproducibility
np.random.seed(42)

# Generate 200 entries
n_entries = 200

# Generate data for each feature
age = np.random.randint(18, 80, n_entries)
monthly_charges = np.random.uniform(20, 200, n_entries).round(2)
contract_types = np.random.choice(['Monthly', 'One year', 'Two year'], n_entries)
tenure = np.random.randint(1, 72, n_entries)

# Calculate churn probability based on features
def churn_probability(age, monthly_charges, contract_type, tenure):
    prob = 0.1  # Base probability
    
    # Age factor
    if age < 30:
        prob += 0.1
    elif age > 60:
        prob += 0.05
    
    # Monthly charges factor
    if monthly_charges > 100:
        prob += 0.15
    
    # Contract type factor
    if contract_type == 'Monthly':
        prob += 0.2
    elif contract_type == 'One year':
        prob += 0.05
    
    # Tenure factor
    if tenure < 12:
        prob += 0.15
    elif tenure > 36:
        prob -= 0.1
    
    return min(max(prob, 0), 1)  # Ensure probability is between 0 and 1

# Generate churn based on probabilities
churn_probs = [churn_probability(a, m, c, t) for a, m, c, t in zip(age, monthly_charges, contract_types, tenure)]
churn = np.random.binomial(1, churn_probs)

# Create the DataFrame
df = pd.DataFrame({
    'Age': age,
    'MonthlyCharges': monthly_charges,
    'ContractType': contract_types,
    'Tenure': tenure,
    'Churn': churn
})

# Display the first few rows and basic statistics
print(df.head())
print("\nDataset Info:")
print(df.info())
print("\nDataset Description:")
print(df.describe())

# Display churn distribution
print("\nChurn Distribution:")
print(df['Churn'].value_counts(normalize=True))

# Optional: Save the dataset to a CSV file
df.to_csv('customer_churn_dataset.csv', index=False)
print("\nDataset saved as 'customer_churn_dataset.csv'")