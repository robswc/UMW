import sys
import os
import random
import subprocess


# Driver code
# Example: python dfa_code.py dfa/silly.dfa

alphabet = open(sys.argv[2]).readlines()[1].rstrip().split(',')


def gen_strings():
    n_alphabet = 'abcdefghijklmnopqrstuvwxyz'
    strings = []
    strings.append(random.choice(n_alphabet))
    for a in alphabet:
        strings.append(a)

    for i in range(0, 50):
        a_list = [random.choice(alphabet) for i in range(0, random.randint(1, 10))]
        s = ''.join(a_list)
        strings.append(s)

    return strings


if '.py' in sys.argv[1]:
    p_type = 'python'
elif '.java' in sys.argv[1]:
    p_type = 'java'
else:
    print('program type not defined!')
    sys.exit(-1)

strings = gen_strings()
for i in range(0, 25):
    rnd_string = random.choice(strings)
    try:
        cmd = subprocess.check_output('{} {} {} {}'.format(p_type, sys.argv[1], sys.argv[2], rnd_string), shell=True)
        print('{0:20}\t{1}'.format(rnd_string, str(cmd).replace("b'", "").replace('\\r', '').replace("\\n'", '')))
    except:
        print('>>>Failed on:', rnd_string)


