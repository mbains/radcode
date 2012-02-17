import os

f = file('out.txt', 'r')


os.dup2(f.fileno(), 0)
import sys
print sys.stdin.read()
f.close()

