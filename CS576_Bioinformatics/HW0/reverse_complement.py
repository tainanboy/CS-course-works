import sys

def reverse_complement():
    #print(str(sys.argv[1:]))
    string = str(sys.argv[1:])
    r = []
    for i in range(len(string)):
        if string[i] == 'A':
            r.append('T')
        elif string[i] == 'C':
            r.append('G')
        elif string[i] == 'G':
            r.append('C')
        elif string[i] == 'T':
            r.append('A')
    r = r[::-1]
    o = ''.join(r)
    print(o)

if __name__ == '__main__':
    reverse_complement()