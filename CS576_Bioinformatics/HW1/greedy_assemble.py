import itertools

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
    nodes = [line.rstrip('\n') for line in open('ebola_full_genome.reads.txt')]
    #print(lines)
    return nodes

def nodePairs(node):
    pairs = list(itertools.permutations(node, 2))
    return pairs

#use dict to store node-edge
def buildGraph():
    node = nodePairs(readline())
    d = dict((el, overlap(el)) for el in node)
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

# pass in a tuple, return compressed chain
def combine(l):
    key = l[0]
    val = l[1]
    r = key[0]+key[1][val:]
    return r

def SCS():
    e = buildEdge(nodePairs(readline())) #edge list
    n = readline() #node list
    #print(n)
    #print(e)
    while(len(n)-1):
        r = e.pop()
        n.remove(r[0][0])
        n.remove(r[0][1])
        n.append(combine(r))
        e = buildEdge(nodePairs(n))
        #print(n)
        #print(e)
    print(n)


if __name__ == '__main__':
    #readline()
    #buildGraph()
    #buildEdge()
    SCS()

