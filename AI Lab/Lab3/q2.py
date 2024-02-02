import pandas as pd

IIIT_Library = {
    'Subjects': ['A', 'B', 'C', 'D', 'E', 'A', 'B'],
    'Book_authors':['X', 'Y', 'Z', 'P', 'Q','AB','CD'],
    'No_of_books': [10, 60, 30, 80, 62,10,20]
}

df = pd.DataFrame(IIIT_Library)
total_books = df.groupby('Subjects')['No_of_books'].sum()

print(total_books)