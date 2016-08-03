'''
frank8409252gmail.com
NTU ML HW1 18-POCKET
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

def verify(w,Vx,Vy):
    n = Vy.size
    error = 0
    for i in np.arange(n):
        if h(w,Vx[i]) != Vy[i]:
            error +=1
    er_rate = error / n
    return er_rate

def pocket(X,y,update_num,seed,learning_rate=1.0):
    w = np.zeros(X[1].size)
    m = y.size
    np.random.seed(seed)
    iteration = 0
    while iteration < update_num: 
        #idx = random.sample(range(m), m)
        i = np.random.randint(0,m) #return a number from 0~m-1, based on seed
        if h(w,X[i]) != y[i]:
            wnew = w+ learning_rate * X[i] * y[i]
            if verify(wnew,X,y) < verify(w,X,y):
                iteration+=1
                w = wnew
    return w

def main():
    test_error_rates = []            
    for s in range(300):
        w=pocket(X,y,50,s)
        test_error_rates.append(verify(w,tX,ty))
    print ("Average Error Rate:", np.average(test_error_rates))
    #plt.hist(test_error_rates)
        
if __name__ == '__main__':
    main()