import subprocess

cmd = 'py rcarrol2_TM.py'
path = 'wordhashword.tm'
verbose = False

test_cases = {
    '1001#1001': 'Accepted!',
    '1111#1111': 'Accepted!',
    '11#1001': 'Rejected.',
    'a#a': 'Malformed.',
}

incorrect = []

for k, v in test_cases.items():
    command = '{} {} "{}" {}'.format(cmd, path, k, ('verbose' if verbose else ''))
    print(command)
    p = subprocess.Popen(command,
                         shell=True,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
    for line in p.stdout.readlines():
        if line.decode("utf-8").strip() == v:
            print(v, '\t', 'PASS!')
        else:
            incorrect.append(k)
            print(line.decode("utf-8").strip(), 'should be', v)

    retval = p.wait()

if len(incorrect) > 0:
    print('The following did not pass:', '\n'.join(incorrect))
else:
    print('All passed!')



