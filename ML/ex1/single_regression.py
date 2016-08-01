'''
Andrew Ng ML course assignment 1: Linear regression with one variable
'''
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('data/ex1data1.txt', delimiter=',')

X = np.c_[np.ones(data.shape[0]),data[:,0]]
y = np.c_[data[:,1]]
#print(X)
#print(y)
#plot 
plt.plot(X[:,1],y[:,0],'rx',markersize=10)
plt.grid(True) #Always plot.grid true!
plt.ylabel('Profit in $10,000s')
plt.xlabel('Population of City in 10,000s')
#plt.show()
#cost function J(theta)
def h(theta,X): 
    return np.dot(X,theta)
def computeCost(X,y, theta = [[0],[0]]):
    m = y.size
    J = 1/(2*m)*np.sum(np.square(h(theta,X)-y))    
    return J
#initial_t = np.zeros((X.shape[1],1)) #(theta is a vector with n rows and 1 columns (if X has n features) )
print(computeCost(X,y))
def gradientDescent(X, y, theta=[[0],[0]], alpha=0.01, num_iters=1500):
    m = y.size
    iterJ =  np.zeros(num_iters)
    for i in np.arange(num_iters):
        theta = theta - alpha*(1/m)*(X.T.dot(h(theta,X)-y))
        iterJ[i] = computeCost(X, y, theta)
    return(theta, iterJ)

ftheta , J = gradientDescent(X, y)
print(ftheta)
print(J)
'''
plt.plot(J)
plt.ylabel('Cost of J')
plt.xlabel('Iterations');
#plt.show()
'''
xx = np.arange(5,23)
yy = ftheta[0]+ftheta[1]*xx

# Plot gradient descent
plt.scatter(X[:,1], y, s=30, c='r', marker='x', linewidths=1)
plt.plot(xx,yy, label='Linear regression')
plt.show()


# Predict profit for a city with population of 35000 and 70000
print(ftheta.T.dot([1, 3.5])*10000)
print(ftheta.T.dot([1, 7])*10000)
