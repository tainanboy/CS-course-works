'''
frank8409252gmail.com
NTU ML HW1 17-PLA
'''
import numpy as np
import matplotlib.pyplot as plt
import random

data = np.loadtxt('data/hw1_15_train.dat.txt')
#print(data)
X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1],data[:,2],data[:,3]]
y = np.c_[data[:,4]]

def h(w,X): 
    return np.sign(w.T.dot(X))

def random_pick(ysize):
    order = list(range(ysize))
    random.shuffle(order)
    return order

def random_PLA(X,y,learning_rate = 0.5):
    w = np.zeros(X[1].size)
    iteration = 0
    while True: 
        find_mistake = False
        for i in random_pick(y.size):
            if h(w,X[i]) != y[i]:
                find_mistake = True
                w = w+ learning_rate * X[i] * y[i]
                iteration+=1
                last_mistake_index = i
                continue
        if not find_mistake:
                break
    return w, iteration, last_mistake_index

iter_updates = []
for i in range(2000):
    random.seed(i+1)
    w, iter, last = random_PLA(X,y)
    iter_updates.append(iter)

print ("Average Number:", np.average(iter_updates))
plt.hist(iter_updates)
plt.ylabel('frequency')
plt.xlabel('number of updates');
plt.show()