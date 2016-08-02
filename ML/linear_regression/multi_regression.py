'''
Andrew Ng ML course assignment 1: Linear regression with multiple variable
'''
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d, Axes3D 

data = np.loadtxt('data/ex1data2.txt', delimiter=',')
#print(data)
X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1]]
y = np.c_[data[:,2]]
#print(X)
#print(y)
#print(X.shape)
def featurenormalize(X):
    Xnorm = X.copy()
    means = []
    stds = []
    for i in np.arange(Xnorm.shape[1]):
        means.append(np.mean(Xnorm[:,i]))
        stds.append(np.std(Xnorm[:,i]))
        if not i: continue
        Xnorm[:,i] = (Xnorm[:,i] - means[-1])/stds[-1]
    return (means, stds, Xnorm)

means, stds, Xnorm = featurenormalize(X)
'''
#Quick visualize the feature-normalized data
plt.grid(True)
plt.xlim([-5,5])
dummy = plt.hist(Xnorm[:,0],label = 'col1')
dummy = plt.hist(Xnorm[:,1],label = 'col2')
dummy = plt.hist(Xnorm[:,2],label = 'col3')
plt.title('Feature Normalization Accomplished')
plt.xlabel('Column Value')
plt.ylabel('Counts')
dummy = plt.legend()
plt.show()
'''
def h(theta,X): 
    return np.dot(X,theta)
def computeCost(X,y, theta = np.zeros((X.shape[1],1))):
    m = y.size
    J = 1/(2*m)*np.sum(np.square(h(theta,X)-y))    
    return J

def gradientDescent(X, y, theta=np.zeros((X.shape[1],1)), alpha=0.01, num_iters=1500):
    m = y.size
    iterJ =  np.zeros(num_iters)
    for i in np.arange(num_iters):
        theta = theta - alpha*(1/m)*(X.T.dot(h(theta,X)-y))
        iterJ[i] = computeCost(X, y, theta)
    return (theta, iterJ)

ftheta , J = gradientDescent(Xnorm, y)
print(ftheta)

def finaltheta(X, y):
    piX = np.linalg.pinv(X)
    theta = piX.dot(y)
    return theta
w = finaltheta(Xnorm, y)
print(w)
'''
plt.plot(J)
plt.ylabel('Cost of J')
plt.xlabel('Iterations');
#plt.show()
'''
# Check of result: What is price of house with 1650 square feet and 3 bedrooms?
print ("Check of result: What is price of house with 1650 square feet and 3 bedrooms?")
test = np.array([1650,3])
#To "undo" feature normalization, we "undo" 1650 and 3, then plug it into our hypothesis
testscaled = [(test[x]-means[x+1])/stds[x+1] for x in range(len(test))]
testscaled.insert(0,1)
print ("$%0.2f" % float(h(ftheta,testscaled)))
print (h(ftheta,testscaled))