import operator as op

def isnum(strs):
    try: int(strs)
    except:
        try: float(strs)
        except: return False
    return True

def lex(exp):
    exp = exp.replace('(', ' ( ')
    exp = exp.replace(')', ' ) ')
    exp = exp.replace('+', ' + ')
    exp = exp.replace('-', ' - ')
    exp = exp.replace('*', ' * ')
    exp = exp.replace('/', ' / ')
    return exp.split()

class Node:
    def __init__(self, value, lchild=None, rchild=None):
        self.value = value
        self.lchild = lchild
        self.rchild = rchild

    def trans(self, node):
        if node is None:
            return
        print node.value
        self.trans(node.lchild)
        self.trans(node.rchild)

    def pre(self):
        self.trans(self)

#expression = term {("+"|"-") term} .
#term = factor {("*"|"/") factor} . 
#factor = number | "(" expression ")" .

class Parser:
    def __init__(self, arrs):
        self.cur=0
        self.arrs = arrs

    def next(self):
        self.cur += 1

    def get(self):
        return self.arrs[self.cur]
        
    def factor(self):
        ch = self.get()
        if isnum(ch):
            print 'factor-->num'
            self.next()
            return Node(ch)
        elif ch == '(':
            self.next()
            print 'factor-->( exp )'
            node = self.expression()
            if self.get() != ')':
                raise SyntaxError("parenthesis not match")
            self.next()
            return node
        else:
            raise SyntaxError("fatal error")

    def term(self):
        print 'term->factor'
        node = self.factor()
        while self.cur < len(self.arrs) and (self.get() == '/' or self.get() == '*'):
            print 'term-> */ factor'
            ch = self.get()
            self.next()
            _node = self.factor()
            node = Node(ch, node, _node)
        return node
    
    def expression(self):
        print 'exp-->term'
        node = self.term()
        while self.cur < len(self.arrs) and (self.get() == '+' or self.get() == '-'):
            print 'exp--> +- term'
            ch = self.get()
            self.next()
            _node = self.term()
            node = Node(ch, node, _node)
        return node


if __name__ == '__main__':
    while True:
        arrs = lex(raw_input("calc>>"))
        print arrs
        parser = Parser(arrs)
        node = parser.expression()
        node.pre()
