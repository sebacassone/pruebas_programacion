def palindromo(arreglo):
    """
    Funcion que recibe un arreglo y devuelve True si es palindromo, False en caso contrario.
    """
    if(len(arreglo) == 0 or len(arreglo) == 1):
        return True
    if(arreglo[0] != arreglo[-1]):
        return False
    arreglo.pop(0)
    arreglo.pop(-1)
    return palindromo(arreglo)

arreglo = ["a","b","a"]
if(palindromo(arreglo)):
    print("Es palindromo")