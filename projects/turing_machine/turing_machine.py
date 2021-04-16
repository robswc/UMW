from typing import List


class TuringMachine:
    def __init__(self, path):
        # load turing machine variables
        lines: List[str] = [i.strip('\n') for i in open(path, 'r').readlines()]
        self.start, self.accept, self.reject = lines[-3], lines[-2], lines[-1]
        self.symbols, self.tape, self.states = lines[1].split(','), lines[2].split(','), {}
        [self.states.update({s: {}}) for s in lines[0].split(',')]
        # load transition function
        for l in lines[3:-3]:
            line = l.replace('(', '').replace(')', '').split('->')
            state, symbol = line[0].split(',')[0], line[0].split(',')[1]
            t = line[1].split(',')
            self.states.get(state).update({symbol: [t[0], t[1], t[2]]})

    def run(self, string, verbose=False):
        string = list(string)
        curr_state, read_head = self.start, 0
        for i in string:
            if i not in self.symbols:
                return 'Malformed.'
        while True:
            if read_head >= len(string):
                string.append('_')
            if read_head < 0:
                string.insert(0, '_')
            if verbose:
                print(' '.join(string[:read_head]), curr_state, ' '.join(string[read_head:]))
            if curr_state == self.reject:
                return 'Rejected.'
            if curr_state == self.accept:
                return 'Accepted!'
            new_state, new_symbol, direction = self.states.get(curr_state).get(string[read_head])
            string[read_head], curr_state = new_symbol, new_state
            if string[read_head] == '_' and direction == 'L':
                string.pop()
            read_head += +1 if direction == 'R' else -1


if __name__ == '__main__':
    tm = TuringMachine('inputs/wordhashword.tm')
    # a few test cases
    print(tm.run('1101#1101', verbose=False))
    print(tm.run('1101#1111', verbose=False))
    print(tm.run('1111#1111', verbose=False))
    print(tm.run('0000#0000', verbose=False))
    print(tm.run('aaaa#aaaa', verbose=False))
    print(tm.run('101#101', verbose=True))
