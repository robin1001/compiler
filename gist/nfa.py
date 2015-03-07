#robin1001, 2014-1-14
import pygraphviz as pgv
#Epsilon:*, start:@, end:#

#out2 mainly used for | epsilon, and *
class Edge:
    def __init__(self, p=None):
        self.ptr = p

#!!!here default param will point to one, so not 
class State:
    def __init__(self, value, idd, out1, out2):
        self.value = value
        self.id = idd
        self.out1 = out1
        self.out2 = out2
        self.str = self.value + ' | ' + str(self.id) 

#head a state, out, out edge
class Frag:
    def __init__(self, head, out):
        self.head = head
        self.out = out

#postfix, thompson algorithm
def build(arrs):
    stack = []
    cur = 1
    while len(arrs) > 0:
        ch = arrs.pop(0)
        if ch == '.':
            s2 = stack.pop()
            s1 = stack.pop()
            s1.out.ptr = s2.head
            stack.append(Frag(s1.head, s2.out))
        elif ch == '*':
            s = stack.pop()
            ss = State('*', cur, Edge(), Edge())
            cur += 1
            ss.out2.ptr = s.head
            s.out.ptr = ss
            stack.append(Frag(ss, ss.out1))
        elif ch == '|':
            s2 = stack.pop()
            s1 = stack.pop()
            ss = State('*', cur, Edge(), Edge())
            cur += 1
            se = State('*', cur, Edge(), Edge())
            cur += 1
            ss.out1.ptr, ss.out2.ptr = s1.head, s2.head
            s1.out.ptr, s2.out.ptr = se, se
            stack.append(Frag(ss, se.out1))
        else:
            s = State(ch, cur, Edge(), Edge())
            cur += 1
            stack.append(Frag(s, s.out1))
    #add start and tail
    frag = stack.pop()
    head, tail = frag.head, frag.out
    ss = State('@', 0, Edge(), Edge())
    se = State('#', cur, Edge(), Edge())
    ss.out1.ptr = head
    tail.ptr = se
    return ss

def plot(head):
    queue = []
    close = set()
    queue.append(head)
    A=pgv.AGraph(rankdir='LR')
    while len(queue) > 0:
        s = queue.pop(0)
        close.add(s)
        print s.value
        if s.out1.ptr is not None:
            A.add_edge(s.str, s.out1.ptr.str)
            if s.out1.ptr not in close: 
                queue.append(s.out1.ptr)
        if s.out2.ptr is not None:
            A.add_edge(s.str, s.out2.ptr.str)
            if s.out1.ptr not in close:
                queue.append(s.out2.ptr)
    print A.string()
    A.write('simple.dot')
    B = pgv.AGraph('simple.dot')
    B.layout('dot')
    B.draw('simple.png')

def postfix(strs):
    pass

if __name__ == '__main__':
    arrs = ['a', 'b', '|', 'c', '*', '.']
    head = build(arrs)
    plot(head)
