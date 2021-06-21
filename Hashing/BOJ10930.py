import sys;
import hashlib;

# sys.stdin = open("input1.txt", 'r');

print(hashlib.sha256(input().encode()).hexdigest());
