n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

cnt = 0
for i in range(n):
    for j in range(i, n):
        if adj[i][j] == 1: cnt += 1
print(cnt)