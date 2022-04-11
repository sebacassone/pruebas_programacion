resultado = 3 // 6 + 5 * (3 % 6) // 10 + 5 * 6 - (3 ** 1)

print(resultado)

#resultado = 4 // 6 + 5 * (4 % 6) // 8 + 5 * 6 - (4 ** 3)

#print(resultado)

resultado = (5 // 3) * (8 ** 2) * -3
print(resultado)

#resultado = (2 + 14) * (5 ** 2) * -10
#print(resultado)

resultado = int(5.1) * int(2.9) + int(5.5)
print(resultado)

a = -5
a -= 2
a *= a
a //= 3
a *= 8

print("hasta aca", a)

#OAL
x = 6
y = 6
z = -1

res = x + y - z

if x % 2 == 0 or y % 2 == 0 or z % 2 == 0:
    res -= x
if x % 2 != 0 or y % 2 != 0 or z % 2 != 0:
    res *= x
if x % 3 == 0 or y % 3 == 0 or z % 3 == 0:
    res -= y
if x % 3 != 0 or y % 3 != 0 or z % 3 != 0:
    res -= y
if x % 5 == 0 or y % 5 == 0 or z % 5 == 0:
    res -= z
if x % 5 != 0 or y % 5 != 0 or z % 5 != 0:
    res += z

print("res: ", res)

'''
x = 21
y = 6
z = 1

res = x - (y ** z)

if x % 2 == 0 or y % 2 == 0 or z % 2 == 0:
    res += x
if x % 3 == 0 or y % 3 == 0 or z % 3 == 0:
    res -= y
if x % 5 == 0 or y % 5 == 0 or z % 5 == 0:
    res += z
if x % 2 == 0 and y % 2 == 0 and z % 2 == 0:
    res -= x
if x % 3 == 0 and y % 3 == 0 and z % 3 == 0:
    res -= y
if x % 5 == 0 and y % 5 == 0 and z % 5 == 0:
    res += z

print("res: ", res)


a = -6
a -= 3
a *= a
a //= 8
a *= 10
print (a)
'''