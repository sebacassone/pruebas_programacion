#include<stdio.h>
#include<stdlib.h>

// Se declaran variables globales correspondiente a la cantidad filas
// y columnas de la matriz.
typedef struct matriz{
    char **M;
    int filas, columnas;
} estructura_matriz;

// Variables globales para filas y columnas
int n, m;

estructura_matriz *crear_matriz(){
    // Se crea una variable de tipo estructura_matriz
    estructura_matriz *nueva_matriz;
    // Se crea un nuevo espacio en memoria para la estructura
    // recientemente creada
    nueva_matriz = (estructura_matriz *)malloc(sizeof(estructura_matriz));
    // Se le asigna la cantidad de filas y columnas a la estructura
    // apuntada por nueva_matriz
    nueva_matriz -> filas = n;
    nueva_matriz -> columnas = m;
    // Se asigna espacio en memoria para un arreglo de punteros, que
    // estos a su vez apuntarán a las filas de la matriz que estamos
    // creando, para esto se usará el puntero doble M
    (*nueva_matriz).M = (char **)malloc(sizeof(char *) * n);
    // Se recorre el arreglo de punteros recien creado para asignarle
    // la dirección de una lista de enteros que representa las filas de
    // la matriz
    for(int i = 0; i < n; i++){
        (*nueva_matriz).M[i] = (char *)malloc(sizeof(char) * m);
    }
    // Se retorna el puntero que apunta a la esctructura
    return nueva_matriz;
}

estructura_matriz *leer_archivo(char *nombre){
    // Se declaran variables
    FILE *archivo;
    estructura_matriz *matriz;
    int aux;
    // Se abre el archivo, siendo el nombre pasado como parámetro por
    // consola, correspondiendo al primer elemento del arreglo apuntado
    // por argv.
    
    archivo = fopen(nombre,"r");
    // Se leen las dimensiones de la matriz y se guardan en la
    // estructura apuntada por matriz.
    fscanf(archivo, "%d %d", &n, &m);
    
    // Se crea el espacio en memoria de forma dinamica para la matriz
    matriz = crear_matriz();
    
    // Se le asigna valores al contenido de la matriz
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m + 1; j++){
            fscanf(archivo, "%c", &aux);
            matriz -> M[i][j] = aux;
        }
    }
    // Se cierra el archivo
    fclose(archivo);
    // Se retorna el puntero que apunta a la esctructura
    return matriz;
}

int encontrar_camino(int i, int j, estructura_matriz *matriz, int entrada, char *instrucciones, int k){
    // Se crea el caso base para la función recursiva para cuando ya se
    // esté llegando a la salida para terminar el programa.
    if(matriz -> M[i][j] == 's'){
        return 1;
    }
    // Comienza el programa en la entrada "e", y partiendo de ahí
    // comienza a recorrer hacia la izquierda, derecha, arriba, o abajo
    // de manera recursiva
    else if(matriz -> M[i][j] == 'e'){
        // Se verifica que solo  se ejecute una sola vez en todo el
        // programa para no volver a "e"
        if(entrada){
            // Hacia abajo
            if(encontrar_camino(i + 1, j, matriz, 0, instrucciones, k)){
                (instrucciones)[k] = 'D';
                k += 1;
                return 1;
            }
            // Hacia arriba
            if(encontrar_camino(i - 1, j, matriz, 0, instrucciones, k)){
                (instrucciones)[k] = 'T';
                k += 1;
                return 1;
            }
            // Hacia el lado derecho
            if(encontrar_camino(i, j + 1, matriz, 0, instrucciones, k)){
                (instrucciones)[k] = 'R';
                k += 1;
                return 1;
            }
            // Hacia la izquierda
            if(encontrar_camino(i, j - 1, matriz, 0, instrucciones, k)){
                (instrucciones)[k] = 'L';
                k += 1;
                return 1;
            }
        }
    }
    // Al comenzar a recorrer el laberinto a partir de la entrada debe
    // verificar que en la dirección que recorre hay solo "o" de lo
    // contario podrá haber "x" o estar "s"
    else if(matriz->M[i][j] == 'o'){
        // Hacia abajo
        if(encontrar_camino(i + 1, j, matriz, 0, instrucciones, k)){
            (instrucciones)[k] = 'D';
            k += 1;
            return 1;
        }
        // Hacia arriba
        if(encontrar_camino(i - 1, j, matriz, 0, instrucciones, k)){
            (instrucciones)[k] = 'T';
            k += 1;
            return 1;
        }
        // Hacia el lado derecho
        if(encontrar_camino(i, j + 1, matriz, 0, instrucciones, k)){
            (instrucciones)[k] = 'R';
            k += 1;
            return 1;
        }
        // Hacia la izquierda
        if(encontrar_camino(i, j - 1, matriz, 0, instrucciones, k)){
            (instrucciones)[k] = 'L';
            k += 1;
            return 1;
        }
    }
    // En caso de que al recorrer el laberinto se encuentre con una "x"
    // se retornará 0
    return 0;
}

int main(int argc, char *argv[]){
    // Se crea una variable de tipo estructura que contendrá a la
    // matriz
    estructura_matriz *matriz;
    char *instrucciones;
    int posicion_n_e, posicion_m_e, entrada = 0, fin = 0, k = 0, contador = 0;
    // Se obtiene la matriz leida del archivo
    matriz = leer_archivo(argv[1]);
    
    // Se encuentra la posición de la entrada "e" de la matriz
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matriz->M[i][j] == 'e'){
                posicion_n_e = i;
                posicion_m_e = j;
                entrada = 1;
            }
        }
    }
    // Se crea un espacio en memoria para almacenar las instrucciones
    // para resolver el laberinto para n * m elementos (el caso donde
    // se ocupan todos los espacios)
    instrucciones = (char *)calloc(1,sizeof(char) * (n * m));
    if(entrada)
        fin = encontrar_camino(posicion_n_e, posicion_m_e, matriz, 1, instrucciones, k);
    if(fin){
        for(int l = 0; instrucciones[l] != 0; l++){
            contador += 1;
        }
        printf("Un camino para %s es: ", argv[1]);
        for(int i = 0; i < contador; i ++){
            printf("%c", instrucciones[i]);
        }
    }
    else
        printf("%s no tiene salida\n", argv[1]);
    return 0;
}
