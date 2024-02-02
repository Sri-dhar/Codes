import pandas as pd

dataset ={
    'name': ['A', 'B', 'C', 'D', 'E'],
    'CPI':  [10, 60, 30, 80, 62]
}

CPIabove60 = pd.DataFrame(dataset)[pd.DataFrame(dataset)['CPI'] > 60]

print(CPIabove60)

df = pd.DataFrame(dataset)
mean_CPI = df['CPI'].mean()
median_CPI = df['CPI'].median()
std_dev_CPI = df['CPI'].std()

print(f"Mean of CPI: {mean_CPI}")
print(f"Median of CPI: {median_CPI}")
print(f"Standard Deviation of CPI: {std_dev_CPI:.3f}")
