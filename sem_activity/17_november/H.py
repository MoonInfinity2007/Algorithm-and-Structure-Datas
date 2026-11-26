n, m  = map(int, input().split())
adj = [
    map(int, input().split()) for _ in range(m)
]

ans = [[0 for _ in range(n)] for __ in range(n)]
for u, v in adj:
    ans[u-1][v-1] = 1
print("\n".join(" ".join(map(str, elem)) for elem in ans))