from nfa import *


class ReParser:
    def __init__(self):
    
        pass 
    def parse(restr):
        cur = 0
        stack = []
        while cur < len(restr):
           ch = restr[cur]
           if ch == '.':
           elif ch == '*':
           elif ch == '+':
           elif ch == '|':
           elif ch == '(':
           elif ch == ')':
           elif ch == '\\': #escape character
              cur += 1
              ch2 = restr[cur]
              if True:
              else:
                 raise Exception('out of vocabulary') 
           else:


if __name__ == '__main__':
    for i in range(10):
        print i
