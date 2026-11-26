def dfs(v, c):
    global g, ans, used
    used[v] = c
    for u in g[v]:
        if (0 == used[u]): dfs(u, 3 - c)
        elif used[v] == used[u]: ans = False
ans = True

g = {}
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
for v in g:
    if used[v] == 0: dfs(v, 1)
if ans: print("YES")
else: print("NO")