'''
NTU ML HW1 15-PLA
'''
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('data/hw1_15_train.dat.txt')
#print(data)
X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1],data[:,2],data[:,3]]
y = np.c_[data[:,4]]
#print(X)
#print(y)
#print(y.size)
#print(X[0].size)

def h(w,X): 
    return np.sign(w.T.dot(X))
'''
def pick(w,X,y):
    result = None
    for i in np.arange(y.size):
        if h(w,X[i]) != y[i]:
            result = (X[i],y[i])
            break
    return result

def naive_PLA(X,y):
    w = np.zeros(X[1].size)
    iteration = 0
    while pick(w,X,y) is not None:
        iteration+=1
        Xi, yi = pick(w,X,y)
        w += yi * Xi
    return w, iteration
'''

def naive_PLA(X,y):
    w = np.zeros(X[1].size)
    iteration = 0
    while True: 
        find_mistake = False
        for i in np.arange(y.size):
            if h(w,X[i]) != y[i]:
                find_mistake = True
                w = w+ X[i] * y[i]
                iteration+=1
                last_mistake_index = i
                continue
        if not find_mistake:
                break
    return w, iteration, last_mistake_index

w, iter, last = naive_PLA(X,y)
print(w)
print(iter)
print(last)