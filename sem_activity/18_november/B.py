import sys
sys.setrecursionlimit(100000)
 
def dfs(v, c):
    global used, g
    used[v] = True
    colour[v] = c
    for u in g[v]:
        if (not colour[u]): dfs(u, c)

g = {}
N, M = map(int, input().split())
used = [0 for i in range(N)]
colour = [0 for i in range(N)]
for i in range(M):
    v, u = map(int, input().split())
    v -= 1
    u -= 1
    if not (v in g): g[v] = []
    g[v].append(u)
    if not (u in g): g[u] = []
    g[u].append(v)
col = 0
for i in range(N):
    if not i in g:
        col += 1
        colour[i] = col
    elif colour[i] == 0:
        col += 1
        dfs(i, col)
print(col)
print(*colour)