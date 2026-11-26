import sys
sys.setrecursionlimit(10000)
def dfs(v):
    global g, used, path, res
    used[v] = 1
    path.append(v)
    for u in g[v]:
        if (not used[u]): dfs(u)
    if len(res) < len(path): res = path[::]
    path.pop()

g = {}
N = int(input())
used = [0 for i in range(N)]
path, res = [], []
for i in range(N - 1):
    v, u = map(int, input().split())
    v -= 1
    u -= 1
    if not (v in g): g[v] = []
    g[v].append(u)
    if not (u in g): g[u] = []
    g[u].append(v)
dfs(0)
used = [0 for i in range(N)]
dfs(res[-1])
print(len(res))