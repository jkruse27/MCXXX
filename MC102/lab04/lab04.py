#João Gabriel Segato Kruse RA:218615

C = int(input())
i = 1
while i != 0:
    i = int(input())
    if i > 0:
        if (C-i) >= 0:
            C = C - i
            print("Seja bem-vindo! Capacidade restante: %d" %C)
        else:
            print("Veiculo muito grande! Capacidade restante: %d" %C)
    if i < 0:
        C = C - i
        print("Volte sempre! Capacidade restante: %d" %C)

~                                                    
