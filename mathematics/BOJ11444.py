import sys;

# FIBONACCI_LEN = 3;
MOD = 1000000007;

def mulMatrix(A : list, B : list) -> list:
    return [[((A[0][0] * B[0][0]) + (A[0][1] * B[1][0])) % MOD,
             ((A[0][0] * B[0][1]) + (A[0][1] * B[1][1])) % MOD],
            [((A[1][0] * B[0][0]) + (A[1][1] * B[1][0])) % MOD,
             ((A[1][0] * B[0][1]) + (A[1][1] * B[1][1])) % MOD]];

# sys.stdin = open("input1.txt", 'r');

N = int(sys.stdin.readline());

"""
fibonacciList = [0, 1, 1];

if (N < FIBONACCI_LEN):
    print(fibonacciList[N]);
    sys.exit(0);

for k in range(FIBONACCI_LEN, N + 1):
    fibonacciList[k % FIBONACCI_LEN] = (fibonacciList[(k + 1) % FIBONACCI_LEN] + fibonacciList[(k + 2) % FIBONACCI_LEN]) % MOD;

print(fibonacciList[N % FIBONACCI_LEN]);
"""

(answerMatrix, baseMatrix) = ([[1, 0], [0, 1]], [[1, 1], [1, 0]]);

for curDigit in bin(N - 1)[ : : -1]:
    if (curDigit == '1'):
        answerMatrix = mulMatrix(answerMatrix, baseMatrix);

    baseMatrix = mulMatrix(baseMatrix, baseMatrix);

print(answerMatrix[0][0]);
