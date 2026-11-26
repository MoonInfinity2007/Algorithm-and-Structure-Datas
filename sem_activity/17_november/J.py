n, m  = map(int, input().split())
adj = [
    map(int, input().split()) for _ in range(m)
]

mp = dict()
result = "NO"
for u, v in adj:
    if (u, v) in mp: result = "YES"
    else: mp[(u, v)] = 1
print(result)