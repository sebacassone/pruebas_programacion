altura = int(input("Ingrese una base: "))
base = int(input("Ingrese una altura: "))
altura += 1

for f in range(base):
    for c in range(altura): 
        for i in range(base):
            if f == base - i - 1 and i + 2 <= c <= altura - i:
                print ("*", end="")
        else:
           print(" ", end="") 
    print("")