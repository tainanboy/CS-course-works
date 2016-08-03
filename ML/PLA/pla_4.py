'''
frank8409252gmail.com
NTU ML HW1 19-PLA
'''
import numpy as np
#import matplotlib.pyplot as plt
import random

data = np.loadtxt('data/hw1_18_train.dat.txt')
#print(data)
X = np.c_[np.ones(data.shape[0]),data[:,0],data[:,1],data[:,2],data[:,3]]
y = np.c_[data[:,4]]

test = np.loadtxt('data/hw1_18_test.dat.txt')
tX = np.c_[np.ones(data.shape[0]),test[:,0],test[:,1],test[:,2],test[:,3]]
ty = np.c_[test[:,4]]

def h(w,X): 
    return np.sign(w.T.dot(X))

def random_pick(ysize):
    order = list(range(ysize))
    random.shuffle(order)
    return order

def verify(w,Vx,Vy):
    n = Vy.size
    error = 0
    for i in np.arange(n):
        if h(w,Vx[i]) != Vy[i]:
            error +=1
    er_rate = error / n
    return er_rate

def random_PLA(X,y,update_num,learning_rate = 1.0):
    w = np.zeros(X[1].size)
    iteration = 0
    while iteration<update_num: 
        for i in random_pick(y.size):
            if h(w,X[i]) != y[i]:
                w = w+ learning_rate * X[i] * y[i]
                iteration+=1
                last_mistake_index = i
                continue
    return w, iteration, last_mistake_index

def main():
    test_error_rates = []
    for i in range(2000):
        random.seed(i)
        w, iter, last = random_PLA(X,y,50)
        test_error_rates.append(verify(w,tX,ty))
    print ("Average Error:", np.average(test_error_rates))

if __name__ == '__main__':
    main()