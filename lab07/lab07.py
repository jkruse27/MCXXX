#João Gabriel Segato Kruse RA:218615
n = int(input())
marcador = 0
s = ""
for i in range(1, n+1):
    for j in range(1, n+1):
        if j%i == 0 or i%j == 0:
            s = s + "*"
            marcador += 1
        else:
            s = s + "-"
    print(s)
    s=""
print(marcador)


