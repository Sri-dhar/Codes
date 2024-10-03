import numpy as np
import pandas as pd

data = {
    "Size": [2100, 1800, 2500, 1900, 2200, 2300, 1700, 2400, 2100, 1950, 2600, 1850, 2150, 2000, 2400, 1750, 2250, 2100, 2300, 1900],
    "Bedrooms": [3, 2, 4, 3, 3, 4, 2, 3, 3, 3, 4, 2, 3, 3, 4, 2, 3, 3, 4, 3],
    "Age": [15, 20, 10, 12, 18, 8, 22, 14, 16, 13, 7, 19, 11, 15, 9, 21, 12, 14, 10, 16],
    "Distance": [2.5, 3.0, 1.8, 3.5, 4.0, 2.2, 3.8, 2.0, 2.7, 3.2, 1.5, 3.3, 2.4, 2.9, 1.9, 4.1, 2.6, 2.8, 2.1, 3.4],
    "Price": [350000, 280000, 400000, 320000, 330000, 375000, 260000, 385000, 340000, 310000, 420000, 290000, 360000, 330000, 390000, 270000, 370000, 345000, 380000, 300000]
}

df = pd.DataFrame(data)

training_split = 0.7
validation_split = 0.2
testing_split = 1 - training_split - validation_split

df = df.sample(frac=1).reset_index(drop=True)

num_samples = len(df)
num_training = int(num_samples * training_split)
num_testing = num_samples - num_training

X_train = df.iloc[:num_training, :-1].values
y_train = df.iloc[:num_training, -1].values
X_test = df.iloc[num_training:, :-1].values
y_test = df.iloc[num_training:, -1].values

X_train = (X_train - X_train.mean(axis=0)) / X_train.std(axis=0)
X_test = (X_test - X_test.mean(axis=0)) / X_test.std(axis=0)

w0 = 1      
w1 = 1
w2 = 1
w3 = 1
w4 = 1

learning_rate = alpha = 0.001
no_of_epochs = 100

def predict(X, w0, w1, w2, w3, w4):
    return w0 + X[0] * w1 + X[1] * w2 + X[2] * w3 + X[3] * w4 %10e5

def linearRegression(X, y, w0, w1, w2, w3, w4):
    global learning_rate
    for _ in range(no_of_epochs):
        for i in range(len(X)):
            y_prediction = predict(X[i], w0, w1, w2, w3, w4)    
            error = y_prediction - y[i]
            w0 -= learning_rate * error
            w1 -= learning_rate * error * X[i][0]
            w2 -= learning_rate * error * X[i][1]
            w3 -= learning_rate * error * X[i][2]
            w4 -= learning_rate * error * X[i][3]
    return w0, w1, w2, w3, w4

def meanSquaredError(X, y, w0, w1, w2, w3, w4):
    total_error = 0
    for i in range(len(X)):
        y_prediction = predict(X[i], w0, w1, w2, w3, w4)
        error = y[i] - y_prediction
        total_error += error**2
    mse = total_error / len(X)
    return mse

range_of_alpha = [0.001, 0.01, 0.1, 1, 10]
range_of_epochs = [100, 1000, 10000, 100000]

def hyperparameterTuning():                 
    min_mse = 1e9
    best_alpha = 0
    best_epochs = 0
    for alpha in range_of_alpha:
        for epochs in range_of_epochs:  
            w0, w1, w2, w3, w4 = 1, 1, 1, 1, 1
            global learning_rate, no_of_epochs
            learning_rate = alpha
            no_of_epochs = epochs
            w0, w1, w2, w3, w4 = linearRegression(X_train, y_train, w0, w1, w2, w3, w4)
            mse = meanSquaredError(X_train, y_train, w0, w1, w2, w3, w4)
            if mse < min_mse:
                min_mse = mse
                best_alpha = alpha
                best_epochs = epochs
    return best_alpha, best_epochs

best_alpha, best_epochs = hyperparameterTuning()
print(f"The best hyperparameters are: ")
print(f"Alpha : {alpha}")
learning_rate = best_alpha
no_of_epochs = best_epochs  

def printCoefficients():
    print(f"The value of coefficients trained by the model are: ")
    print(f" w0 (intercept) : {w0}")
    print(f" w1 : {w1}")
    print(f" w2 : {w2}")
    print(f" w3 : {w3}")
    print(f" w4 : {w4}")

def test():
    size = 2500
    no_of_bedrooms = 4 
    age = 10
    distance = 5
    prediction = predict([size, no_of_bedrooms, age, distance], w0, w1, w2, w3, w4)
    print(f"The parameters on which our model is tested are following: ")
    print(f"size in sq feet : 2500")
    print(f"no_of_bedrooms : 4")
    print(f"age of house : 10")
    print(f"distance to the city : 5")
    print(f"The prediction for the given parameters by our model is : {prediction}")

w0, w1, w2, w3, w4 = linearRegression(X_train, y_train, w0, w1, w2, w3, w4)

training_MSE = meanSquaredError(X_train, y_train, w0, w1, w2, w3, w4)
print(f"The training MSE is : {training_MSE}")

testing_MSE = meanSquaredError(X_test, y_test, w0, w1, w2, w3, w4)
print(f"The testing MSE is: {testing_MSE}")

printCoefficients()
print()             
test()