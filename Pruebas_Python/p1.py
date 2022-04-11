'''
Estos programas que siguen no hacen nada más que dibujar uwu
'''


for c in range(5):
    for f in range(5): 
        if c < f:
            print("", end = "")
        else:
            print("*", end = "")
    print("")

print("")

for c in range(5):
    for f in range(5): 
        if (0 < f < 4) and (0 < c < 4):
            print(" ", end = "")
        else:
            print("*", end = "")
    print("")

print("")

for c in range(5):
    for f in range(6):
        if c % 2 == 0:
            if f % 2 == 0:
                print("*", end="")
            else:
                print(" ", end="")
        else:
            if f % 2 == 0:
                print(" ", end="")
            else:
                print("*", end="")
    print("")

print("")

for c in range(5):
    for f in range(5): 
        if f == c:
            print("*", end = "")
        elif (f + c) == 4:
            print("*", end = "")
        else:
            print(" ", end = "")
    print("")

print("")

for f in range(5):
    for c in range(10): 
        if f == 5 and 0 <= c <= 10:
            print ("*", end="")
        elif f == 4 and 0 < c < 10: 
            print ("*", end="")
        elif f == 3 and 1 < c < 9: 
            print ("*", end="")
        elif f == 2 and 2 < c < 8: 
            print ("*", end="")
        elif f == 1 and 3 < c < 7: 
            print ("*", end="")
        elif f == 0 and 4 < c < 6: 
            print ("*", end="")
        else:
            print(" ", end="")
    print("")