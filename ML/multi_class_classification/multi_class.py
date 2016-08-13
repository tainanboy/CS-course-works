import numpy as np
import matplotlib.pyplot as plt
import random
from scipy import optimize
from sklearn.preprocessing import PolynomialFeatures
import scipy.io as sio

data = sio.loadmat('data/ex3data1.mat')
#print(data.keys())
X = np.c_[np.ones((data['X'].shape[0],1)),data['X']]
y = data['y']
#print(X)
#print(y)
#print(X.shape)
#print(y.shape)

def displayData(X):
    sample = np.random.choice(X.shape[0], 10, replace=False)
    #print(sample)
    #print(sample.shape)
    #print(X[sample,1:].shape)
    #print(X[sample,1:].reshape(-1,10).shape)
    plt.imshow(X[sample,1:].reshape(-1,10).T, cmap=plt.cm.gray)
    plt.show()

#displayData(X)

def sigmoid(z):
    return (1/(1+np.exp(-z)))

def h(theta,X):
    return sigmoid(np.dot(X,theta))

def sgd_logistic(X, y, eta, T):
    m = y.size
    w = np.zeros(X.shape[1])
    for t in range(T):
        i = t%m
        g = sigmoid(-y[i]*np.dot(X[i],w))*y[i]*X[i]
        w = w + eta*g
    return w
#w = sgd_logistic(X, y, 0.001, 2000)
#print(w.shape)

def ylabel(k,y):
    m = y.size
    yl = np.c_[np.zeros(m)]
    for i in np.arange(m):
        if y[i] == k:
            yl[i] = 1
        else:
            yl[i] = 0
    return yl
#print(y)
#yl = ylabel(10,y)
#print(yl)

def one_vs_all(X,y,eta,T,k):
    s = (k, X.shape[1])
    w = np.zeros(s) #10*401
    #print(w.shape)
    for i in range(1,k+1):
        #print(i)
        yl = ylabel(i,y)
        w[i-1]= sgd_logistic(X,yl,eta,T)
    return w

w = one_vs_all(X,y,0.0126,5000,10)
print(w.shape)

def predictOneVsAll(all_theta, features):
    probs = sigmoid(X.dot(all_theta.T))
        
    # Adding one because Python uses zero based indexing for the 10 columns (0-9),
    # while the 10 classes are numbered from 1 to 10.
    return(np.argmax(probs, axis=1)+1)

pred = predictOneVsAll(w, X)
print('Training set accuracy: {} %'.format(np.mean(pred == y.ravel())*100))
