import numpy as np
import matplotlib.pyplot as plt

#hours of study, score in exams
# 1 2
# 2 4
# 3 6
# 4 8
# 5 10

data = np.array([[1,2],[2,4],[3,6],[4,8],[5,10]])
x = data[:,0]
y = data[:,1]

x_train = x[:3]
y_train = y[:3]

x_test = x[3:]
y_test = y[3:]

print(f"x : {x}")
print(f"y : {y}")

print(f"x_train : {x_train}")
print(f"y_train : {y_train}")

print(f"x_test : {x_test}")
print(f"y_test : {y_test}")

def h_x(w0, w1, x):
    return w0 + w1*x

def cost(w0, w1, x, y):
    return 1/(2*len(x)) * np.sum((h_x(w0, w1, x) - y)**2)

def gradient_descent(w0, w1, x, y, alpha):
    w0_new = w0 - alpha * 1/len(x) * np.sum(h_x(w0, w1, x) - y)
    w1_new = w1 - alpha * 1/len(x) * np.sum((h_x(w0, w1, x) - y) * x)
    return w0_new, w1_new

def train(x, y, alpha, epochs):
    w0 = 1
    w1 = 1
    for i in range(epochs):
        w0, w1 = gradient_descent(w0, w1, x, y, alpha)
        print(f"epoch : {i+1}, cost : {cost(w0, w1, x, y)}")
    return w0, w1

w0, w1 = train(x_train, y_train, 0.1, 1000)
print(f"w0 : {w0}, w1 : {w1}")

w0_GD = w0
w1_GD = w1

def stochastic_gradient_descent(w0, w1, x, y, alpha):
    for i in range(len(x)):
        w0 = w0 - alpha * (h_x(w0, w1, x[i]) - y[i])
        w1 = w1 - alpha * (h_x(w0, w1, x[i]) - y[i]) * x[i]
    return w0, w1

def train_stochastic(x, y, alpha, epochs):
    w0 = 1
    w1 = 1
    for i in range(epochs):
        w0, w1 = stochastic_gradient_descent(w0, w1, x, y, alpha)
        print(f"epoch : {i+1}, cost : {cost(w0, w1, x, y)}")
    return w0, w1

w0, w1 = train_stochastic(x_train, y_train, 0.1, 1000)
print(f"w0 : {w0}, w1 : {w1}")

w0_SGD = w0
w1_SGD = w1

# no_of_decimal_places = 4

# w0_GD = w0_GD.__round__(no_of_decimal_places)
# w1_GD = w1_GD.__round__(no_of_decimal_places)
# w0_SGD = w0_SGD.__round__(no_of_decimal_places)
# w1_SGD = w1_SGD.__round__(no_of_decimal_places)


print(f"w0_GD : {w0_GD}, w1_GD : {w1_GD}")
print(f"The equation for GD is y = {w0_GD} + {w1_GD}x")
print()
print(f"w0_SGD : {w0_SGD}, w1_SGD : {w1_SGD}")
print(f"The equation for SGD is y = {w0_SGD} + {w1_SGD}x")

def test(w0, w1, x, y):
    y_pred = h_x(w0, w1, x)
    return 1/(2*len(x)) * np.sum((y_pred - y)**2)

def predict(w0, w1, x):
    return h_x(w0, w1, x)

print("predicting using the GD model")
for i in range(len(x_test)):
    print(f"Actual : {y_test[i]}, Predicted : {predict(w0_GD, w1_GD, x_test[i])}")
print()

print("predicting using the SGD model")
for i in range(len(x_test)):
    print(f"Actual : {y_test[i]}, Predicted : {predict(w0_SGD, w1_SGD, x_test[i])}")
print()


cost_GD = test(w0_GD, w1_GD, x_test, y_test)
cost_SGD = test(w0_SGD, w1_SGD, x_test, y_test)

print(f"Cost for GD : {cost_GD}")
print(f"Cost for SGD : {cost_SGD}")

plt.scatter(x, y, color='red')
plt.plot(x, h_x(w0_GD, w1_GD, x), color='blue')
plt.plot(x, h_x(w0_SGD, w1_SGD, x), color='green')