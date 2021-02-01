"""
Builds file compatible with:
http://ivanzuzak.info/noam/webapps/fsm_simulator/
"""


class DFAGen:
    def __init__(self, dfa):
        self.dir = 'dfa/'
        self.states = ['s{}'.format(i) for i in open('{}{}'.format(self.dir, dfa)).readline().rstrip().split(',')]
        self.alphabet = open('{}{}'.format(self.dir, dfa)).readlines()[1].rstrip().split(',')
        self.reset_state = open('{}{}'.format(self.dir, dfa)).readlines()[2].rstrip()
        self.accept_states = open('{}{}'.format(self.dir, dfa)).readlines()[3].rstrip().split(',')
        self.t_functions_raw = [t.rstrip() for t in open('{}{}'.format(self.dir, dfa)).readlines()[4:]]

    def __str__(self):
        print('#states')
        print('\n'.join(['s{}'.format(i) for i in range(0, len(self.states))]))
        print('#initial')
        print('s{}'.format(self.reset_state[1:]))
        print('#accepting')
        print('\n'.join(['s{}'.format(i[1:]) for i in self.accept_states]))
        print('#alphabet')
        print('\n'.join(self.alphabet))
        print('#transitions')
        translated = [t.replace('(', '').replace(')', '').replace(',', ':').replace('->', '>').replace('q', 's') for t in self.t_functions_raw]
        print('\n'.join(translated))


# Load dfa file.
dfa = DFAGen('silly.dfa')
print(dfa)
"""
Template: 

q0,q1,bob,q3
a,b
q0
q1,q3
(q0,a)->q1
(q0,b)->q0
(q1,a)->q1
(q1,b)->q3
(bob,a)->q3
(bob,b)->q3
(q3,a)->q3
(q3,b)->bob

"""