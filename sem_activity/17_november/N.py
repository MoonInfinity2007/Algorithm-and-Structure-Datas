n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

ans1 = [0 for _ in range(n)]
ans2 = [0 for _ in range(n)]
st = []
so = []
for i in range(n): 
    ans1[i] = sum(adj[i])
    ans2[i] = sum([adj[j][i] for j in range(n)])
    if (ans2[i] == 0): so.append(i + 1)
    if (ans1[i] == 0): st.append(i + 1)
print(len(so))
if (so != []): print(*so, sep="\n")
print(len(st))
if (st != []): print(*st, sep="\n")