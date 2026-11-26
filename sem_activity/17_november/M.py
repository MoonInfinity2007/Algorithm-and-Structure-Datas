n, m  = map(int, input().split())
adj = [
    map(int, input().split()) for _ in range(m)
]

ans1 = [0 for _ in range(n)]
ans2 = [0 for _ in range(n)]
for u, v in adj:
    ans1[u - 1] += 1
    ans2[v - 1] += 1
for i in range(n):
    print(ans2[i])
    print(ans1[i])