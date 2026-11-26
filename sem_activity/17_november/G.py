n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

dp = [[] for i in range(n)]
cnt = 0
for i in range(n):
    for j in range(n):
        if adj[i][j] == 1: dp[i].append(j)
for i in range(n):
    if (dp[i] != []):
        for elem in dp[i]:
            print(i + 1, elem + 1)