n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

mp = [set() for _ in range(n)]
for i in range(n):
    for j in range(n):
        if adj[i][j] == 1: mp[i].add(j)
result = "YES"
for i in range(n):
    for u in mp[i]:
        for v in mp[u]:
            if (i != u) and (u != v) and (i != v):
                if v not in mp[i]: result = "NO"
print(result)