import sys
import random


# Create node class for cfg.
class Node:
    def __init__(self, value):
        self.value = value
        self.productions, self.terminals = [], []

    def update_terminals(self, t):
        for i in t:
            if i in self.productions:
                self.productions.remove(i), self.terminals.append(i)

    def expand(self, h, l):
        if not self.productions:
            return random.choice(self.terminals)
        if not self.terminals:
            return random.choice(self.productions)
        return random.choices([random.choice(self.productions), random.choice(self.terminals)],
                              weights=[(((h - 0) / (l - 0)) - 1) * -0.5, ((((h - 0) / (l - 0)) - 1) * -0.5) - 1])

    def __str__(self):
        return 'Node: {}\tProductions: {}\tTerminals: {}'.format(self.value, self.productions, self.terminals)


class CfgGenerator:
    def __init__(self, file, n):
        self.file, self.n = file, int(n)
        self.cfg, self.nodes, self.string = {}, [], []
        self.head, self.curr = None, None

        # Get lines
        lines = [i.strip('\n') for i in open(self.file, 'r').readlines()]
        self.cfg.update({'terminals': lines[1].split(',')})
        self.cfg.update({'start': lines[-1]})

        # Create Nodes
        for i in lines[0].split(','):
            self.nodes.append(Node(i))

        # Create productions/terminals
        for i in lines[2:-1]:
            node = self.get_node(i.split(' -> ')[0])
            node.productions.append(i.split(' -> ')[1])
            node.update_terminals(self.cfg.get('terminals'))

    def debug(self, enabled):
        if enabled:
            print(self.curr)
            print('\t', str(self.head).rjust(len(''.join(self.string[:self.head])) + (4 * self.head) + 3))
            print('\t', str('▼').rjust(len(''.join(self.string[:self.head])) + (4 * self.head) + 3))
            print('\t', self.string)

    def get_node(self, value):
        for i in self.nodes:
            if i.value == value:
                return i
        return None

    def append_string(self, string):
        self.string.pop(self.head)
        for s in reversed(string.split(' ')):
            self.string.insert(self.head, s)

    def move_head(self):
        while self.head < len(self.string):
            if self.string[self.head] in self.cfg.get('terminals'):
                self.head += 1
            else:
                break

    def generate(self):
        # Reset
        self.string.clear()
        self.head = 0

        # Generate CFG
        self.curr = self.get_node(self.cfg.get('start'))
        self.string.append(self.curr.value)
        for i in range(0, 100):
            self.append_string(self.curr.expand(self.head, len(self.string)))
            self.move_head()
            if self.head == len(self.string):
                return ' '.join(self.string)
            self.curr = self.get_node(self.string[self.head])
            self.debug(True)

    def batch(self):
        sentences = []
        while len(sentences) < self.n:
            s = self.generate()
            if s not in sentences:
                sentences.append(s)

        # Print results
        for idx, s in enumerate(sentences, start=1):
            print('({}) {}'.format(idx, s))


# Run the generator
cfg = CfgGenerator(sys.argv[1], sys.argv[2])
cfg.batch()

