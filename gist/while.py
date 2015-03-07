import sys

program = '''
while ( 5 )
{ {
	
} }
'''

class Lexer:
	def __init__(self, program):
		self.tokens = self.lex(program)
		self.cur = 0

	def lex(self, program):
		return program.split()

	def consume(self, s):
		if self.tokens[self.cur] == s:
			self.cur += 1
		else:
			print "%s expected, but %s given !!!" % (s, self.tokens[self.cur])
			sys.exit(-1)

	def get_token(self):
		return self.tokens[self.cur]

	def next(self):
		self.cur += 1

def parser(lexer):
	tree = []

	lexer.consume("while")
	tree.append("while")
	lexer.consume("(")
	n = int(lexer.get_token())
	tree.append(n)
	lexer.next()

	lexer.consume(")")
	lexer.consume("{")
	lexer.consume("}")

	return tree

def intepreter(tree):
	i = 0
	while i < tree[1]:
		print i
		i += 1

if __name__ == '__main__':
	lexer = Lexer(program)
	tree = parser(lexer)
	intepreter(tree)
