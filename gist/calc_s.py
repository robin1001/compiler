import operator as op
opts = {'+':op.add, '-':op.sub, '*':op.mul, '/':op.div}

def calc(exp):
    if not isinstance(exp, list):#number
        return float(exp)
    return opts[exp[0]](calc(exp[1]), calc(exp[2]))

#parse to list type(+ 1 1) --> ['+', '1', '1']
def to_list(arrs):
    ch = arrs.pop(0)
    if ch == '(':
        lis = []
        while arrs[0] != ')':
            lis.append(to_list(arrs))
        arrs.pop(0)
        return lis
    elif ch == ')':
        raise SyntaxError('unexpected )')
    else:
        return ch
    
def parse(exp):
    arrs = exp.replace('(', ' ( ').replace(')', ' ) ').split()
    return to_list(arrs)

if __name__ == '__main__':
    while True:
        #print parse(raw_input("calc>>"))
        print calc(parse(raw_input("calc>>")))
