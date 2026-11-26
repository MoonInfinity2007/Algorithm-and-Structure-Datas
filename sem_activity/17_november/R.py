n, m  = map(int, input().split())
adj = [
    map(int, input().split()) for _ in range(m)
]

result = "YES"
mp = [set() for _ in range(n)]
for u, v in adj:
    mp[u - 1].add(v - 1)
for i in range(n):
    for u in mp[i]:
        for v in mp[i]:
            if (u != v) and (v not in mp[u]): result = "NO"
print(result)