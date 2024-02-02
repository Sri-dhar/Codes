import matplotlib.pyplot as plt
import pandas as pd

img = plt.imread('image.jpg')

df = pd.DataFrame(img.reshape(-1, 3), columns=['R', 'G', 'B'])

df.to_csv('image_matrix.csv')   

print(df)

print("\n\nImporting Excel data from the .csv file excluding the last row and last column")

df = pd.read_csv('image_matrix.csv', index_col=0)

df = df.iloc[:-1, :-1]

print(df.head())    