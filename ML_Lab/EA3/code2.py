import numpy as np
import pandas as pd

def load_data():
    data = pd.read_csv('iris.csv')
    X = data.iloc[:, :-1].values
    y = data.iloc[:, -1].values
    return X, y 