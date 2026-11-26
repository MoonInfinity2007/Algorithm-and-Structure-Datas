g = {}
circle = 0
def dfs(v):
    global used, g, circle
    if (circle): return
    colour[v] = 1
    for u in g[v]:
        if (colour[u] == 1): circle = 1
        if (not colour[u] and u in g): dfs(u)
    colour[v] = 2 

N = int(input())
colour = [0 for i in range(N)]
for i in range(N):
    l = list(map(int, input().split()))
    for j in range(len(l)):
        if l[j]:
            v = i
            u = j
            if not (v in g): g[v] = []
            g[v].append(u)

for i in range(N):
    if colour[i] == 0 and i in g:
        dfs(i)
print(circle)