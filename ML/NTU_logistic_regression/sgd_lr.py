import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('hw3_train.dat.txt')
X = np.c_[np.ones(data.shape[0]),data[:,:-1]]
y = data[:,-1]
#print(X.shape)
#print(y.shape)

test_data = np.loadtxt('hw3_test.dat.txt')
tX = np.c_[np.ones(data.shape[0]),data[:,:-1]]
ty = data[:,-1]

def sigmoid(z):
    return (1/(1+np.exp(-z)))

def h(theta,X):
    return sigmoid(np.dot(X,theta))

def sgd_logistic(X, y, eta, T):
    N = y.size
    w = np.zeros(X.shape[1])
    for t in range(T):
        i = t%N
        g = sigmoid(-y[i]*np.dot(X[i],w))*y[i]*X[i]
        w = w + eta*g
    return w

def Eout(w,X,y):
    return 1-np.sum(np.sign(np.dot(X,w)) == y)/float(len(y))

w = sgd_logistic(X, y, 0.001, 2000)
print(w)
print("With η = 0.001, Eout =", Eout(w,tX,ty))

w = sgd_logistic(X, y, 0.126, 2000)
print(w)
print("With η = 0.126, Eout =", Eout(w,tX,ty))