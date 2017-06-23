import mathlib
import sys
import cProfile, pstats
pr = cProfile.Profile()
def calculate(numbers):
    pr.enable()
    N = len(numbers)
    sequenceSum = 0
    avg = mathlib.div(sum(numbers),N)
    for i in range(N):
        sequenceSum=mathlib.sum(sequenceSum, mathlib.pow(numbers[i]-avg,2))
    s=mathlib.root(2, mathlib.mul(mathlib.div(1,N),sequenceSum))
    pr.disable()

if len(sys.argv) < 2:
    print("Number expected")
    sys.exit(1)
toRead = int(sys.argv[1])
numbers = []
for i in range(toRead):
    line = sys.stdin.readline()
    if line == "":
        print("Not enough lines at stdin")
        sys.exit(1)
    numbers.append(float(line.replace("\n","")))

calculate(numbers)
sortby = 'cumtime'
ps = pstats.Stats(pr).sort_stats(sortby)
ps.print_stats()
