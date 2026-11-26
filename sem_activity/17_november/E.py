# n = int(input())
# adj = [
#     list(map(int, input().split())) for _ in range(n)
# ]

# dp = [[] for i in range(n)]
# cnt = 0
# for i in range(n):
#     for j in range(n):
#         if adj[i][j] == 1: dp[i].append(j)
# for i in range(n):
#     print(i + 1, *dp[i])


n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

ans = []
for i in range(n):
    for j in range(i, n):
        if adj[i][j] == 1: ans.append((i + 1, j + 1))
print("\n".join(f"{u} {v}" for u, v in ans))