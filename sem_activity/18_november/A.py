g = {}
def dfs(v):
    global used, g
    used[v] = True
    for v in g[v]:
        if (not used[v]): dfs(v)

N, M = map(int, input().split())
used = [0 for i in range(N)]
for i in range(M):
    v, u = map(int, input().split())
    v -= 1
    u -= 1
    if not (v in g): g[v] = []
    g[v].append(u)
    if not (u in g): g[u] = []
    g[u].append(v)
dfs(0)
if sum(used) == N: print("YES")
else: print("NO")