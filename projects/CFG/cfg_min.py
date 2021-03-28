import sys
import random


# This is just mostly for 'fun' ;)
class Node:
    def __init__(self, value):
        self.value = value, self.productions, self.terminals = value, [], []

    def update_terminals(self, t):
        for i in t:
            if i in self.productions:
                self.productions.remove(i), self.terminals.append(i)

    def expand(self, h, l):
        if not self.productions: return random.choice(self.terminals)
        if not self.terminals: return random.choice(self.productions)
        return random.choices([random.choice(self.productions), random.choice(self.terminals)],
                              weights=[(((h - 0) / (l - 0)) - 1) * -0.5, ((((h - 0) / (l - 0)) - 1) * -0.5) - 1])


class CfgGenerator:
    def __init__(self, file, n):
        self.file, self.n = file, int(n)
        self.cfg, self.nodes, self.string, self.head, self.curr = {}, [], [], None, None
        self.cfg.update({'terminals': [i.strip('\n') for i in open(self.file, 'r').readlines()][1].split(',')})
        [self.nodes.append(Node(i)) for i in [i.strip('\n') for i in open(self.file, 'r').readlines()][0].split(',')]
        for i in [i.strip('\n') for i in open(self.file, 'r').readlines()][2:-1]:
            node = self.get_node(i.split(' -> ')[0])
            node.productions.append(i.split(' -> ')[1])
            node.update_terminals(self.cfg.get('terminals'))

    def get_node(self, value):
        for i in self.nodes:
            if i.value == value:
                return i

    def append_string(self, string):
        self.string.pop(self.head)
        [self.string.insert(self.head, s) for s in reversed(string.split(' '))]

    def move_head(self):
        while self.head < len(self.string):
            if self.string[self.head] in self.cfg.get('terminals'):
                self.head += 1
            else:
                break

    def generate(self):
        self.string.clear()
        self.head, self.curr = 0, self.get_node([i.strip('\n') for i in open(self.file, 'r').readlines()][-1])
        self.string.append(self.curr.value)
        for i in range(0, 100):
            self.append_string(self.curr.expand(self.head, len(self.string)))
            self.move_head()
            if self.head == len(self.string): return ' '.join(self.string)
            self.curr = self.get_node(self.string[self.head])

    def batch(self):
        sentences = []
        while len(sentences) < self.n:
            s = self.generate()
            if s not in sentences:
                sentences.append(s)
        for idx, s in enumerate(sentences, start=1):
            print('({}) {}'.format(idx, s))


cfg = CfgGenerator(sys.argv[1], sys.argv[2])
cfg.batch()
