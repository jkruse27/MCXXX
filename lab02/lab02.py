#João Gabriel Segato Kruse 218615

vi=float(input())
xi=float(input())
yi=float(input())
xf=float(input())
yf=float(input())
t=float(input())
cd=float(input())
pr=float(input())

d = (xf - xi) + (yf - yi)
VC = vi + d * t
VD = max(cd, (VC*pr/100))
VF = VC - VD
print("%.2f" %VF)

