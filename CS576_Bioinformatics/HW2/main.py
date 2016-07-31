import sys
import math
import numpy as np
from numpy import inf

def readfile():
    lines = [line.rstrip('\n') for line in open(sys.argv[1])]
    return lines # a list of lines

def readscore():
    return tuple(sys.argv[2:]) #return sore parameters tuple

def makeMatrix(list):
    lenX = len(list[0])
    lenY = len(list[1])
    return np.zeros((lenX+1, lenY+1)) #take in a list of two sequences, return np matrix

def scor(Xi, Yj):
    if (Xi == Yj):
        return 1
    else:
        return -1

def overlap_align():
    lines = readfile()
    x = lines[0]
    y = lines[1]
    M = makeMatrix(lines)
    X = makeMatrix(lines)
    Y = makeMatrix(lines)    
    (match, mismatch, gap, space) = readscore()
    #initialize
    for i in range(1, len(x)+1):
        M[i][0] = -inf
        X[i][0] = 0
        Y[i][0] = -inf
    for j in range(1, len(y)+1):
        M[0][j] = -inf
        X[0][j] = -inf
        Y[0][j] = float(space) + j*float(gap)
    M[0][0] = 0
    #print(M)
    #print(X)
    #print(Y)
    for i in range(1, len(x)):
        for j in range(1, len(y)):
            M[i][j] = max(
                    M[i-1][j-1]+scor(x[i],y[j]),
                    scor(x[i],y[j]) + X[i-1][j-1],
                    scor(x[i],y[j]) + Y[i-1][j-1]
            )
            X[i][j] = max(
                    float(gap) + float(space) + M[i-1][j],
                    float(gap) + X[i-1][j],
            )
            Y[i][j] = max(
                    float(gap) + float(space) + M[i][j-1],
                    float(gap) + Y[i][j-1]
            )
    opt = max(M[len(x)][len(y)], X[len(x)][len(y)], Y[len(x)][len(y)])
    print(opt)
    print(M)
    print(X)
    print(Y)
if __name__ == '__main__':
    overlap_align()