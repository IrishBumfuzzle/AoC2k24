program = [2,4,1,5,7,5,4,3,1,6,0,3,5,5,3,0]
a = 0

answer = [0]
for i in range(len(program)):
    prev = []
    for a in answer:
        for j in range(a*8, a*8+8):
            x = (j%8) ^ 5
            if ((x ^ int(j / pow(2, x)) ^ 6) % 8) == program[len(program) -1 - i]:
                prev.append(j)
    answer = prev

def f(a):
    x = (a % 8) ^ 5
    print((x ^ int(a/pow(2, x)) ^ 6 ) % 8, end='')

print(answer[0])