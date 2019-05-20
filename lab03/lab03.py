#João Gabriel Segato Kruse RA:218615

P1 = float(input())
P2 = float(input())
MI = float(input())
Mp = ((2*P1)+(3*P2))/5
if Mp <5 or MI< 5:
    M = min(Mp, 4.9)
    if 2.5 <= M < 5:
        E = float(input())
        F = (M+E)/2
    else:
        F = M

else:
    M = ((3*Mp)+(2*MI))/5
    F = M

print("%.1f" %Mp)
print("%.1f" %M)
print("%.1f" %F)

