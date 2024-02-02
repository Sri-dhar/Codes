import pandas as pd

dirty_data = {
    'Name': ['A', 'B', 'C', 'D', 'E'],
    'Age':  [10, 60, 30, 80, 62],
    'Salary': [-10, 60, 30, -80, 62]
}

df = pd.DataFrame(dirty_data)
print(df)


print("\nAfter removing the dirty data:")
df = df[(df['Age'] >= 18) & (df['Salary'] >= 0)]
print(df)
