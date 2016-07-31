import itertools
import operator
import string

# lenght of longest suffix of i that is prefix of j
'''def overlap(a, b):
    l = []
    j = 0
    for i in range(0, min(len(a), len(b))):
        if a[i] == b[j]:
            l.append(a[i])
            j += 1
    print(len(l)) 
    l = ''.join(l)
    r = s1[:-len(l)]+s2
    print(l)
    print(r)
'''
'''def overlap(l): #'GAG', 'GAT' won't woek'
    a = l[0]
    b = l[1]
    length = min(len(a), len(b))+1
    result = []
    try: 
        for min_length in range(1, length):
            start = a.find(b[:min_length])
            if start != -1: 
                print(b[:min_length])
                print(start)
                print(a[start:])
                if b.startswith(a[start:]):
                    print('true')
                    result.append(a[start:])
        #result.sort(key=len, reverse=True)
        print(result[0])
        return len(result[0])
    except: 
        return 0
'''
def overlap(l): 
    #l is a list of two strings
    a = l[0]
    b = l[1]
    min_length = 1
    start = 1
    while True:
        start = a.find(b[:min_length],start)
        #print(a.find(b[:min_length],start))
        if start == -1:
            return 0
        elif b.startswith(a[start:]):
            return len(a)-start
        start +=1

# read lines into a list of nodes
def readline():
    nodes = [line.rstrip('\n') for line in open('test.reads.txt')]
    #nodes = [w.replace('_', '}') for w in nodes]
    #print(lines)
    return nodes

def nodePairs(node):
    pairs = list(itertools.permutations(node, 2))
    return pairs

#use dict to store node-(in, out)
def buildGraph(node):
    d = dict((el, [0, 0]) for el in node)
    #for k,v in d.items():
    #    print(k, v)
    return d

#edge list to store a list of tuples
def buildEdge(nodepairs):
    edge = []
    for n in nodepairs:
        edge.append((n, overlap(n)))
    edge = sorted(edge, key=lambda x: x[1], reverse=False)
    return edge

def adjancyList(node):
    edge = buildEdge(nodePairs(node))
    d = {}
    for n in node:
        d[n] =  [item for item in edge if item[0][0] == n]
    #print(d['GAT'])
    #for i in d['GAT']:
    #    print(i[0][0])
    #    print(i[0][1])
    #   print(i[1])
    return d 


def weight(tuple):
    lowerdict = {}
    lowerdict['_'] = 30
    score = 0
    for index, letter in enumerate(string.ascii_lowercase):
        lowerdict[letter] = index + 1
    for letters in tuple:
        for alph in letters:
            #print(alph)
            score = score + lowerdict[alph]
            #print(score)
    return score

# pass in a tuple, return compressed chain
def combine(l):
    key = l[0]
    val = l[1]
    r = key[0]+key[1][val:]
    return r

'''
def combine(a, b):
    val = overlap([a, b])
    r = a+b[val:]
    return r
'''
def SCS():
    e = buildEdge(nodePairs(readline())) #edge list
    n = readline() #node list
    print(n)
    print(e)
    while(len(n)-1):
        r = e.pop()
        n.remove(r[0][0])
        n.remove(r[0][1])
        n.append(combine(r))
        e = buildEdge(nodePairs(n))
        print(n)
        print(e)
    return str(n)

'''def SCS():
    e = buildEdge(nodePairs(readline())) #edge list
    n = readline() #node list
    print(n)
    print(e)
    visited = [] #visit sequence
    r = e.pop()
    visited.append(r[0][0])
    visited.append(r[0][1])
    while(len(visited) < len(n)):
        r = e.pop()
        if (r[0][1] not in visited):
            visited.append(r[0][1])
    print(visited)
    #print(combine(visited[0], visited[1]))
    i = 0
    for n in range(len(visited)-1):
        visited[i+1] = combine(visited[i], visited[i+1])
        i += 1
    print(visited.pop())
'''
'''
def SCS():
    e = buildEdge(nodePairs(readline())) #edge list as increaing weight queue, ((u,v), weight)
    n = readline() #node list
    d = buildGraph(readline())
    ad = adjancyList(readline())
    #print(n)
    print(e)
    #print(d)
    #print(ad)
    visited = []
    r = e.pop() #first edge (u,v)
    n.remove(r[0][0])
    visited.append(r[0][0])
    visited.append(r[0][1])
    i = d[r[0][0]][0] #in(u)
    o = d[r[0][0]][1] #out(u)
    o += 1 #out(u)+1
    d[r[0][0]] = (i, o) #update u (in, out)
    i = d[r[0][1]][0] #in(v)
    i += 1 
    o = d[r[0][1]][1]
    d[r[0][1]] = (i, o)
    while(len(n)-1):
        #r = e.pop()
        #r = e[-1]
        cur = r[0][1]
        print(cur)
        possible = []
        #print(visited)
        for p in ad[cur]:
            if p[0][1] not in visited:
                possible.append(p)
        #possible = sorted(possible, key=lambda x: x[1], reverse=False)
        #possible = sorted(possible, key=lambda x:(-x[1],lowerdict[a] for a in x[0]), reverse=True)
        #possible = sorted(possible, key=lambda x:[lowerdict[a] for a in x[0]], reverse=True)
        possible = sorted(possible, key=lambda x:(x[1], x[0]), reverse=False)
        #possible = sorted(possible, reverse=False)
        #possible = sorted(sorted(possible, key = lambda x : x[0]), key = lambda x : x[1], reverse = True) 
        print(possible)
        #print(n)
        #print(e)
        #print(d)
        r = next(x for x in possible if x[1] == possible[-1][1])
        #possible.remove(r)
        #r = possible.pop()
        #r = possible[0]
        #possible.remove(r)
        print(r)
        if(d[r[0][0]][1] == 0 and d[r[0][1]][0] ==0 and r[0][1] in n):
            n.remove(r[0][0])
            visited.append(r[0][1])
            i = d[r[0][0]][0]
            o = d[r[0][0]][1]
            o += 1 #out(u)
            d[r[0][0]] = (i, o)
            i = d[r[0][1]][0] #in(v)
            i += 1
            o = d[r[0][1]][1]
            d[r[0][1]] = (i, o)
    #print(visited)
    i = 0
    for n in range(len(visited)-1):
        visited[i+1] = combine(visited[i], visited[i+1])
        i += 1
    return visited.pop()
'''

if __name__ == '__main__':
    #print(readline())
    #buildGraph()
    #buildEdge()
    ans = 'the quick brown fox jumps over the lazy dog'
    print(len(ans))
    print(SCS())
    print(len(SCS()))
    #weight(('the_l', 'ps_ove'))
    #adjancyList(readline())
    #list = [(('er_the', 'ck_bro'), 0), (('er_the', 'lazy_'), 0), (('er_the', 'n_fox_'), 0), (('er_the', 'ox_ju'), 0), (('er_the', 'rown'), 0), (('er_the', 'uic'), 0), (('er_the', 'ump'), 0), (('er_the', 'wn_f'), 0), (('er_the', 'zy_dog'), 0), (('er_the', 'e_lazy'), 1), (('er_the', 'e_qui'), 1), (('er_the', 'the_l'), 3), (('er_the', 'the_qu'), 3)]
    #tmp = transform(list)
    #print(tmp)

