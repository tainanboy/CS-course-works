import numpy as np
import matplotlib.pyplot as plt
import random
from scipy import optimize

data = np.loadtxt('data/ex2data1.txt', delimiter=',')
#print(data.shape)
X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1]]
y = np.c_[data[:,2]]

def plotData(X,y):
    pos = np.array([X[i] for i in range(X.shape[0]) if y[i] == 1])
    neg = np.array([X[i] for i in range(X.shape[0]) if y[i] == 0])
    #print(pos)
    #print(neg)
    plt.plot(pos[:,1],pos[:,2],'k+',label='Admitted')
    plt.plot(neg[:,1],neg[:,2],'yo',label='Not admitted')
    plt.xlabel('Exam 1 score')
    plt.ylabel('Exam 2 score')
    plt.legend()
    plt.grid(True)
    #plt.show()
    
#plotData(X,y)

def sigmoid(z):
    return (1/(1+np.exp(-z)))

def h(theta,X):
    return sigmoid(np.dot(X,theta))

def computeCost(theta,X,y,l=0):
    m = y.size
    term1 = np.dot(-np.array(y).T,np.log(h(theta,X)))
    term2 = np.dot((1-np.array(y)).T,np.log(1-h(theta,X)))
    regterm = (l/2) * np.sum(np.dot(theta[1:].T,theta[1:]))
    J = float((1./m) * (np.sum(term1 - term2) + regterm))
    return J

def gradient(theta,X,y):
    m = y.size
    h = sigmoid(X.dot(theta.reshape(-1,1)))
    grad =(1/m)*X.T.dot(h-y)
    return grad.flatten()

def optimizeTheta(mytheta,myX,myy,mylambda=0.):
    result = optimize.fmin(computeCost, x0=mytheta, args=(myX, myy, mylambda), maxiter=400, full_output=True)
    return result[0], result[1]

def prediction(theta, X):
    return h(theta,X) >= 0.5

def validation(theta,X,y):
    pos = np.array([X[i] for i in range(X.shape[0]) if y[i] == 1])
    neg = np.array([X[i] for i in range(X.shape[0]) if y[i] == 0])
    pre_pos = float(np.sum(prediction(theta,pos)))
    pre_neg = float(np.sum(np.invert(prediction(theta,neg))))
    tot = len(pos)+len(neg)
    percent = float(pre_pos+pre_neg)/tot
    return percent

def main():
    initial_theta = np.zeros((X.shape[1],1))
    theta, mincost = optimizeTheta(initial_theta,X,y)
    print (h(theta,np.array([1, 45.,85.])))
    print(validation(theta,X,y))
    #print(computeCost(theta,X,y))
    boundary_xs = np.array([np.min(X[:,1]), np.max(X[:,1])])
    boundary_ys = (-1./theta[2])*(theta[0] + theta[1]*boundary_xs)
    plotData(X,y)
    plt.plot(boundary_xs,boundary_ys,'b-',label='Decision Boundary')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    main()