n, m  = map(int, input().split())
adj = [
    map(int, input().split()) for _ in range(m)
]

result = "YES"
ans1 = [set() for _ in range(n)]
ans2 = [set() for _ in range(n)]
for u, v in adj:
    ans1[u - 1].add(v - 1)
    ans2[v - 1].add(u - 1)
for i in range(n):
    if (len(ans1[i] | ans2[i]) < (n - 1) ): result = "NO"
print(result)