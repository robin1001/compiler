import os
import sys

class Arc(object):
    def __init__(self, ilabel, next_state):
        self.ilabel = ilabel
        self.next_state = next_state
    

class State(object):
    def __init__(self):
        self.index = 0
        self.arcs = [] #output arcs
    def add_arc(self, arc):
        self.arcs.append(arc)
    def add_epsilon_arc(state):
        self.add_arc(Arc(None, state))

class Nfa(object):
    def __init__(self):
        self.states = []
        self.count = 0
        self.start = None
        self.final = None
    def add_state(self, state):
        state.index = self.count
        self.states.append(state)
        self.count += 1
    def add_states(self, states):
        for s in states:
            self.add_state(s)

def nfa_symbol(ch):
    nfa = Nfa()
    start, final = State(), State()
    start.add_arc(Arc(ch, final))
    nfa.add_states([start, final])
    nfa.start, nfa.final = start, final
    return nfa

def nfa_concat(nfa1, nfa2):
    nfa = Nfa()
    nfa1.final.add_epsilon_arc(nfa2.start)
    nfa.start, nfa.final = nfa1.start, nfa2.final
    nfa.add_states(nfa1.states)
    nfa.add_states(nfa2.states)
    return nfa

def nfa_alter(nfa1, nfa2):
    nfa = Nfa()
    start, final = State(), State()
    start.add_epsilon_arc(nfa1.start)
    start.add_epsilon_arc(nfa2.start)
    nfa1.final.add_epsilon_arc(final)
    nfa2.final.add_epsilon_arc(final)
    nfa.add_states([start, final])
    nfa.add_states(nfa1.states)
    nfa.add_states(nfa2.states)
    nfa.start, nfa.final = start, final
    return nfa

def nfa_kleen(nfa1):
    nfa = Nfa()
    start, final = State(), State()
    start.add_epsilon_arc(nfa1.start)
    nfa1.final.add_epsilon_arc(final)
    nfa1.final.add_epsilon_arc(nfa1.start)
    nfa.add_states([start, final])
    nfa.add_states(nfa1.states)
    nfa.start, nfa.final = start, final
    return nfa
