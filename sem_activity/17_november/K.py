n = int(input())
adj = [
    list(map(int, input().split())) for _ in range(n)
]

ans1 = [0 for _ in range(n)]
ans2 = [0 for _ in range(n)]
for i in range(n): 
    ans1[i] = sum(adj[i])
    ans2[i] = sum([adj[j][i] for j in range(n)])
    print(ans2[i])
    print(ans1[i])