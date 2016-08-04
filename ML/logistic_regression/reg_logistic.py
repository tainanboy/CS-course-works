import numpy as np
import matplotlib.pyplot as plt
import random
from scipy import optimize
from sklearn.preprocessing import PolynomialFeatures


data = np.loadtxt('data/ex2data2.txt', delimiter=',')
#print(data.shape)
#X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1]]
X = np.c_[data[:,0],data[:,1]]
y = np.c_[data[:,2]]

def plotData(X,y):
    pos = np.array([X[i] for i in range(X.shape[0]) if y[i] == 1])
    neg = np.array([X[i] for i in range(X.shape[0]) if y[i] == 0])
    #print(pos)
    #print(neg)
    plt.plot(pos[:,0],pos[:,1],'k+',label='accepted')
    plt.plot(neg[:,0],neg[:,1],'yo',label='rejected')
    plt.xlabel('Microchip Test 1')
    plt.ylabel('Microchip Test 2')
    plt.legend()
    plt.grid(True)
    #plt.show()
    
#plotData(X,y)
def sigmoid(z):
    return (1/(1+np.exp(-z)))

def h(theta,X):
    return sigmoid(np.dot(X,theta))

def mapFeuture(X):
    poly = PolynomialFeatures(6)
    Xt = poly.fit_transform(X)
    #print(Xt.shape)
    #print(Xt)
    return Xt

def computeCost(theta,X,y,l=0):
    m = y.size
    term1 = np.dot(-np.array(y).T,np.log(h(theta,X)))
    term2 = np.dot((1-np.array(y)).T,np.log(1-h(theta,X)))
    regterm = (l/2) * np.sum(np.dot(theta[1:].T,theta[1:]))
    J = float((1./m) * (np.sum(term1 - term2) + regterm))
    #print(J)
    return J

def gradient(theta,X,y):
    m = y.size
    h = sigmoid(X.dot(theta.reshape(-1,1)))
    grad =(1/m)*X.T.dot(h-y)
    return grad.flatten()

def optimizeRegularizedTheta(mytheta,myX,myy,mylambda=0.):
    result = optimize.minimize(computeCost, mytheta, args=(myX, myy, mylambda),  method='BFGS', options={"maxiter":500, "disp":False} )
    return np.array([result.x]), result.fun
    
def plotBoundary(mytheta, myX, myy, mylambda=0.):
    """
    Function to plot the decision boundary for arbitrary theta, X, y, lambda value
    Inside of this function is feature mapping, and the minimization routine.
    It works by making a grid of x1 ("xvals") and x2 ("yvals") points,
    And for each, computing whether the hypothesis classifies that point as
    True or False. Then, a contour is drawn with a built-in pyplot function.
    """
    theta, mincost = optimizeRegularizedTheta(mytheta,myX,myy,mylambda)
    xvals = np.linspace(-1,1.5,50)
    yvals = np.linspace(-1,1.5,50)
    zvals = np.zeros((len(xvals),len(yvals)))
    for i in range(len(xvals)):
        for j in range(len(yvals)):
            new = np.column_stack((np.array([xvals[i]]),np.array([yvals[j]])))
            myfeaturesij = mapFeuture(new)
            zvals[i][j] = np.dot(theta,myfeaturesij.T)
    zvals = zvals.transpose()

    u, v = np.meshgrid( xvals, yvals )
    mycontour = plt.contour( xvals, yvals, zvals, [0])
    #Kind of a hacky way to display a text on top of the decision boundary
    myfmt = { 0:'Lambda = %d'%mylambda}
    plt.clabel(mycontour, inline=1, fontsize=15, fmt=myfmt)
    plt.title("Decision Boundary")


def main():
    mX = mapFeuture(X)
    initial_theta = np.zeros((mX.shape[1],1))
    computeCost(initial_theta,mX,y)
    theta, mincost = optimizeRegularizedTheta(initial_theta,mX,y)
    plt.figure(figsize=(12,10))
    plt.subplot(221)
    plotData(X,y)
    plotBoundary(theta,mX,y,0.)
    plt.subplot(222)
    plotData(X,y)
    plotBoundary(theta,mX,y,1.)

    plt.subplot(223)
    plotData(X,y)
    plotBoundary(theta,mX,y,10.)

    plt.subplot(224)
    plotData(X,y)
    plotBoundary(theta,mX,y,100.)
    plt.show()

if __name__ == '__main__':
    main()