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

def logistic(X, y, eta, T):
    N = y.size
    w = np.zeros(X.shape[1])
    for t in range(T):
        g = np.dot(sigmoid(-y*np.dot(X,w))*y, X)/N
        w = w + eta*g
    return w

def Eout(w,X,y):
    return 1-np.sum(np.sign(np.dot(X,w)) == y)/float(len(y))

w = logistic(X, y, 0.001, 2000)
print(w)
print("With η = 0.001, Eout =", Eout(w,tX,ty))

w2 = logistic(X, y, 0.01, 2000)
print(w2)
print("With η = 0.01, Eout =", Eout(w2,tX,ty))