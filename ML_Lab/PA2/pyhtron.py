# %% [markdown]
# # Libraries

# %%
import pandas as pd
import numpy as np

# %% [markdown]
# # Question 1
# Create a dataset of size 30x2, where the first column represents the number of hours
# of sunshine and the second column represents the number of ice creams sold.

# %%
data = {
    "Hours of Sunshine": [5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 7, 6, 4, 9, 2, 10, 5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 6],
    "Ice Creams Sold": [150, 200, 100, 180, 210, 130, 220, 90, 250, 160, 190, 110, 230, 170, 120, 240, 80, 260, 140, 210, 95, 175, 220, 125, 230, 85, 255, 155, 205, 105, 140]
}

df = pd.DataFrame(data)
df.to_csv('sunshine_ice_cream_data.csv', index=False)


# %% [markdown]
# Importing the data

# %%
data = pd.read_csv("sunshine_ice_cream_data.csv")
print(data)

# %% [markdown]
# Displaying the first five rows

# %%
print(data.head(5))


# %% [markdown]
# Print the total number of
# rows and columns in the dataset, and the range of each feature’s values.

# %%
np_data = np.array(data)

print(f"rows: {data.shape[0]-1}")
print(f"columns: {data.shape[1]}")

output_column = np_data[:, -1]
output_range = (np.min(output_column), np.max(output_column))
print(f"Range of Output : {output_range}")



# %% [markdown]
# # Question 1.ii
# Write a Python program to randomly split the dataset into training and testing
# sets using the following ratios: 70-30,80-20,90-10.

# %%
x_splits = [.7, .8, .9]
x_splits = np.array(x_splits)

def splitter(data, x): 
    y = 1-x                  
    size = data.shape[0]
    train_size = int(size * x)
    test_size = int(size * y)
    train_data = data[:train_size, :]
    test_data = data[train_size:train_size+test_size, :]
    return train_data, test_data

for x in x_splits:
    train_data, test_data = splitter(np_data, x)
    print(f"Train data size: {train_data.shape[0]}")
    print(f"Test data size: {test_data.shape[0]}")
    print()



# %% [markdown]
# # Question 1.iii 
# Apply Simple Linear Regression to predict the number of ice creams sold based
# on the number of hours of sunshine. Report which training and testing split
# yields the best results.Validate your model using the Mean Squared Error (MSE).

# %%
import numpy as np

# Data
X = np.array([5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 7, 6, 4, 9, 2, 10, 5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 6])
Y = np.array([150, 200, 100, 180, 210, 130, 220, 90, 250, 160, 190, 110, 230, 170, 120, 240, 80, 260, 140, 210, 95, 175, 220, 125, 230, 85, 255, 155, 205, 105, 140])

# Shuffle the data
indices = np.arange(len(X))
np.random.shuffle(indices)
X = X[indices]
Y = Y[indices]

# Split into training and testing sets
split_index = int(0.7 * len(X))
X_train, X_test = X[:split_index], X[split_index:]
Y_train, Y_test = Y[:split_index], Y[split_index:]

mean_X_train = np.mean(X_train)
std_X_train = np.std(X_train)
mean_Y_train = np.mean(Y_train)
std_Y_train = np.std(Y_train)

X_train_scaled = (X_train - mean_X_train) / std_X_train
Y_train_scaled = (Y_train - mean_Y_train) / std_Y_train
X_test_scaled = (X_test - mean_X_train) / std_X_train
Y_test_scaled = (Y_test - mean_Y_train) / std_Y_train


# %% [markdown]
# Implementing Simple Linear Regression

# %%
def simple_linear_regression(X, Y):
    n = len(X)
    X_mean = np.mean(X)
    Y_mean = np.mean(Y)
    
    numerator = np.sum((X - X_mean) * (Y - Y_mean))
    denominator = np.sum((X - X_mean) ** 2)
    
    w_1 = numerator / denominator
    w_0 = Y_mean - w_1 * X_mean
    
    return w_0, w_1

w_0, w_1 = simple_linear_regression(X_train, Y_train)


# %% [markdown]
# Predicting Values
# 

# %%
def predict(X, w_0, w_1):
    return w_0 + w_1 * X

Y_pred_train = predict(X_train, w_0, w_1)
Y_pred_test = predict(X_test, w_0, w_1)


# %% [markdown]
# Calculating Mean Squared Error

# %%
def mean_squared_error(Y, Y_pred):
    return np.mean((Y - Y_pred) ** 2)

mse_train = mean_squared_error(Y_train, Y_pred_train)
mse_test = mean_squared_error(Y_test, Y_pred_test)

print(f'MSE for Training Data: {mse_train}')
print(f'MSE for Testing Data: {mse_test}')


# %% [markdown]
# # Evaluating the splits

# %% [markdown]
# without using np.polyfit
# 

# %%
import numpy as np

X = np.array([5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 7, 6, 4, 9, 2, 10, 5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 6])
Y = np.array([150, 200, 100, 180, 210, 130, 220, 90, 250, 160, 190, 110, 230, 170, 120, 240, 80, 260, 140, 210, 95, 175, 220, 125, 230, 85, 255, 155, 205, 105, 140])

indices = np.arange(len(X))
np.random.shuffle(indices)
X = X[indices]
Y = Y[indices]

def simple_linear_regression(X, Y, standardized=False):
    if not standardized:
        X_mean = np.mean(X)
        X_std = np.std(X, ddof=1)  
        Y_mean = np.mean(Y)
        Y_std = np.std(Y, ddof=1)
        
        X = (X - X_mean) / X_std
        Y = (Y - Y_mean) / Y_std

    XY_sum = np.sum(X * Y)
    X2_sum = np.sum(X ** 2)
    w_1 = XY_sum / X2_sum
    w_0 = 0  

    return w_0, w_1

def predict(X, w_0, w_1):
    return w_0 + w_1 * X

def mean_squared_error(Y, Y_pred):
    return np.mean((Y - Y_pred) ** 2)

def evaluate_split(split_ratio):
    split_index = int(split_ratio * len(X))
    X_train, X_test = X[:split_index], X[split_index:]
    Y_train, Y_test = Y[:split_index], Y[split_index:]

    mean_X_train = np.mean(X_train)
    std_X_train = np.std(X_train, ddof=1)
    mean_Y_train = np.mean(Y_train)
    std_Y_train = np.std(Y_train, ddof=1)

    X_train_scaled = (X_train - mean_X_train) / std_X_train
    Y_train_scaled = (Y_train - mean_Y_train) / std_Y_train
    X_test_scaled = (X_test - mean_X_train) / std_X_train
    Y_test_scaled = (Y_test - mean_Y_train) / std_Y_train

    w_0, w_1 = simple_linear_regression(X_train_scaled, Y_train_scaled, standardized=True)

    Y_pred_train_scaled = predict(X_train_scaled, w_0, w_1)
    Y_pred_test_scaled = predict(X_test_scaled, w_0, w_1)

    Y_pred_train = Y_pred_train_scaled * std_Y_train + mean_Y_train
    Y_pred_test = Y_pred_test_scaled * std_Y_train + mean_Y_train

    mse_train = mean_squared_error(Y_train, Y_pred_train)
    mse_test = mean_squared_error(Y_test, Y_pred_test)

    print(f'Split Ratio: {split_ratio}')
    print(f'  Training MSE: {mse_train}')
    print(f'  Testing MSE: {mse_test}')

for ratio in [0.7, 0.8, 0.9]:
    evaluate_split(ratio)
    print('---')


# %% [markdown]
# using np.polyfit

# %%
import numpy as np

def standardize_data(X, Y):
    X_mean = np.mean(X)
    X_std = np.std(X, ddof=1)
    Y_mean = np.mean(Y)
    Y_std = np.std(Y, ddof=1)
    
    X_scaled = (X - X_mean) / X_std
    Y_scaled = (Y - Y_mean) / Y_std
    
    return X_scaled, Y_scaled, X_mean, X_std, Y_mean, Y_std

def fit_linear_regression(X, Y, degree=1):
    coefficients = np.polyfit(X, Y, degree)
    return coefficients

def predict(X, coefficients):
    return np.polyval(coefficients, X)

def mean_squared_error(Y, Y_pred):
    return np.mean((Y - Y_pred) ** 2)

def evaluate_split(split_ratio):
    split_index = int(split_ratio * len(X))
    X_train, X_test = X[:split_index], X[split_index:]
    Y_train, Y_test = Y[:split_index], Y[split_index:]

    X_train_scaled, Y_train_scaled, X_mean, X_std, Y_mean, Y_std = standardize_data(X_train, Y_train)
    X_test_scaled = (X_test - X_mean) / X_std
    
    coefficients = fit_linear_regression(X_train_scaled, Y_train_scaled)

    Y_pred_train_scaled = predict(X_train_scaled, coefficients)
    Y_pred_test_scaled = predict(X_test_scaled, coefficients)
    
    Y_pred_train = Y_pred_train_scaled * Y_std + Y_mean
    Y_pred_test = Y_pred_test_scaled * Y_std + Y_mean
    
    mse_train = mean_squared_error(Y_train, Y_pred_train)
    mse_test = mean_squared_error(Y_test, Y_pred_test)

    print(f'Split Ratio: {split_ratio}')
    print(f'  Training MSE: {mse_train}')
    print(f'  Testing MSE: {mse_test}')

X = np.array([5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 7, 6, 4, 9, 2, 10, 5, 8, 3, 6, 7, 4, 9, 2, 10, 5, 8, 3, 6])
Y = np.array([150, 200, 100, 180, 210, 130, 220, 90, 250, 160, 190, 110, 230, 170, 120, 240, 80, 260, 140, 210, 95, 175, 220, 125, 230, 85, 255, 155, 205, 105, 140])

indices = np.arange(len(X))
np.random.shuffle(indices)
X = X[indices]
Y = Y[indices]

for ratio in [0.7, 0.8, 0.9]:
    evaluate_split(ratio)
    print('---')



