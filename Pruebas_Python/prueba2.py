altura = int(input("Ingrese una base: "))
base = int(input("Ingrese una altura: "))
altura += 2

for f in range(base):
    for c in range(altura): 
        for i in range(base):
            if f == base and i  <= c <= altura - i:
                print ("*", end="")
            elif f == base - i  and i < c < altura - i:
                print ("*", end="")
        else:
           print(" ", end="") 
    print("")