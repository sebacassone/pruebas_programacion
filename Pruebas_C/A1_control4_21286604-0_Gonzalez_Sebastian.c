#include<stdio.h>
#include<stdlib.h>

typedef struct arreglo{
    int *A; // El arreglo estático
    int n, max; // Cantidad de elementos actuales y máximo
} arreglo;

typedef struct nodo{
    int info;
    struct nodo *hijoizquierdo;
    struct nodo *hermanoderecho;
} nodo;

typedef struct nodo2{
    int info;
    struct nodo2 *izquierda;
    struct nodo2 *derecha;
} nodo2;

arreglo *crear_arreglo(int *cantidad){
    arreglo *nuevo_arreglo;
    int i;
    // Se asigna espacio en memoria para la estructura
    nuevo_arreglo = (arreglo *)malloc(sizeof(arreglo));
    // Se le asigna la cantidad de nodos a la estuctura
    nuevo_arreglo -> max = (* cantidad);
    // Se le asigna la cantidad de nodos actuales
    nuevo_arreglo -> n = 0;
    // Se asigna espacio en memoria para el arreglo
    nuevo_arreglo -> A = (int *)malloc(sizeof(int) * nuevo_arreglo -> max);
    // Se inicializa en cero el arreglo
    for(i = 0; i < nuevo_arreglo -> max; i++)
        nuevo_arreglo -> A[i] = 0;
    return nuevo_arreglo;
}

nodo *crear_arbol(void){
    nodo *nuevo_nodo;
    nuevo_nodo = (nodo *)malloc(sizeof(nodo));
    nuevo_nodo -> hermanoderecho = NULL;
    nuevo_nodo -> hijoizquierdo = NULL;
    return nuevo_nodo;
}

nodo2 *crear_arbol_binario(void){
    nodo2 *nuevo_nodo;
    nuevo_nodo = (nodo2 *)malloc(sizeof(nodo2));
    nuevo_nodo -> izquierda = NULL;
    nuevo_nodo -> derecha = NULL;
    return nuevo_nodo;
}

arreglo *leer_archivo(char *nombre){
    arreglo *arbol;
    int cantidad, elemento, posicion = 0;
    FILE *archivo;
    // Se abre el archivo
    archivo = fopen(nombre, "r");
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
        arbol = NULL;
        return arbol;
    }else{
        printf("\nSe ha abierto el archivo con éxito");
    }
    // Se obtiene la cantidad de nodos del arbol
    fscanf(archivo, "%d", &cantidad);
    // Se crea el arreglo
    arbol = crear_arreglo(&cantidad);
    // Se comienza a recorrer el archivo
    while(fscanf(archivo, "%d", &elemento) != EOF){
        // Se le asigna el elemento leido del archivo al arreglo
        arbol -> A[posicion] = elemento;
        arbol -> n = posicion;
        posicion++;
    }
    fclose(archivo);
    return arbol;
}

int mostrar_arreglo(arreglo *arbol){
    int i;
    for(i = 0; i < arbol -> max; i++)
        printf("\n%d", arbol -> A[i]);
}

arreglo *profundidad(arreglo *arbol){
    arreglo *prof;
    int i, contador, temp;
    // Se crea arreglo
    prof = crear_arreglo(&(arbol -> max));
    // Se comienza a recorrer el arreglo desde el último elemento
    for(i = (arbol -> max) - 1; i > 0; i--){
        temp = i;
        // Se reinicia el contador
        contador = 0;
        // Si el último elemento elegido como pivote no es la raiz
        // se asigna como pivote el padre del nodo.
        while(arbol -> A[i] != -1){
            i = (arbol -> A[i]);
            contador++;
        }
        i = temp;
        // Se agrega el contador a la lista de profundidad
        prof -> A[i] = contador; 
    }
    return prof;
}

int **crear_matriz(int n){
    int i, j;
    int **matriz;
    // Se crea la matriz
    matriz = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++){
        matriz[i] = (int *)malloc(sizeof(int) * n);
    }
    // Se inicializa la matriz
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

int **transformar(arreglo *arbol){
    int i, j, **M;
    M = crear_matriz(arbol -> max);
    // Se crea una lista de adyacencia para la lista de hijos
    for(i = 0; i < arbol -> max; i++){
        for(j = i + 1; j < arbol -> max; j++){
            if(i == (arbol -> A[j])){
                M[i][j] = 1;
            }
        }
    }
    return M;
}

int vaciar_vector(int *vector, int n){
    int i;
    for(i = 0; i < n; i++){
        vector[i] = 0;
    }
}

int sumatoria_fila(int **M, int n, int fila){
    int i, suma = 0;
    for(i = 0; i < n; i++){
        suma += M[fila][i];
    }
    return suma;
}

int sumatoria_matriz(int **M, int n){
    int i, j, suma = 0;
    for(i = 0; i < n; i++){
        suma += sumatoria_fila(M, n, i);
    }
    return suma;
}

nodo *transformar2(int **M, int n){
    nodo *aux;
    nodo *nuevo_nodo;
    int i = 0, K[n], j, l;
    nuevo_nodo = crear_arbol();
    aux = nuevo_nodo;
    vaciar_vector(K, n);
    while(sumatoria_matriz(M, n) != 0){
        for(j = 0; j < n; j++){
            if(M[i][j] == 1){
                if(K[i] = 1){
                    // Asignar hermano derecho
                    aux -> hermanoderecho -> info = j;
                    aux = aux -> hermanoderecho;
                    M[i][j] = 0;
                }else{
                    // Se marca el nodo como visitado
                    K[i] = 1;
                    l = j;
                    // Asignar hijo izquierdo
                    // Crear nodo hijo izquierdo
                    aux -> hijoizquierdo -> info = j;
                    aux = aux -> hijoizquierdo; 
                    M[i][j] = 0;
                }
            }
        }
        aux = aux -> hijoizquierdo;
        i = l;       
        if(sumatoria_fila(M, n, i) == 0){
            aux = nuevo_nodo -> hijoizquierdo;
            i = 0;
            // Asigna i a una fila donde la sumatoria no sea cero
            for(int j = 0; j < n; j++){
                if(M[i][j] == 1){
                    i = j;
                    j = 0;
                    break;
                }
            }
        }
    }
    return nuevo_nodo;
}

nodo2 *arreglo_a_arbol(arreglo *arbol, nodo2 *nuevo_nodo, int i){
    nuevo_nodo -> info = i++;
    if((arbol -> n) != 0){
        if(i % 2 == 0){
            nuevo_nodo -> derecha = crear_arbol_binario();
            nuevo_nodo -> derecha -> info = i;
            (arbol -> n)--;
            arreglo_a_arbol(arbol, nuevo_nodo -> derecha, i++);
        }else{
            nuevo_nodo -> izquierda = crear_arbol_binario();
            nuevo_nodo -> izquierda -> info = i;
            (arbol -> n)--;
            arreglo_a_arbol(arbol, nuevo_nodo -> izquierda, i++);  
        }
    }
    return nuevo_nodo;
}

int preorden(nodo *node){
    if(node != NULL){
        printf("%d ", node -> info);
        preorden(node -> hijoizquierdo);
        preorden(node -> hermanoderecho);
    }
}

int inorden(nodo *node){
    if(node != NULL){
        inorden(node -> hijoizquierdo);
        printf("%d ", node -> info);
        inorden(node -> hermanoderecho);
    }
}

int postorden(nodo *node){
    if(node != NULL){
        postorden(node -> hijoizquierdo);
        postorden(node -> hermanoderecho);
        printf("%d ", node -> info);
    }
}

int preorden2(nodo2 *node){
    if(node != NULL){
        printf("%d ", node -> info);
        preorden2(node -> izquierda);
        preorden2(node -> derecha);
    }
}

int inorden2(nodo2 *node){
    if(node != NULL){
        inorden2(node -> izquierda);
        printf("%d ", node -> info);
        inorden2(node -> derecha);
    }
}

int postorden2(nodo2 *node){
    if(node != NULL){
        postorden2(node -> izquierda);
        postorden2(node -> derecha);
        printf("%d ", node -> info);
    }
}

int mostrar_matriz(int **M, int n){
    int i, j;
    printf("\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("\n%d", M[i][j]);
        }
        printf("\n");
    }
}

int profundidad_nodo(arreglo *prof){
    int i;
    for(i = 0; i < prof -> max; i++){
        printf("\nProfundidad del nodo %d: %d", i, prof -> A[i]);
    }
    return 1;
}

int nodos_por_nivel(arreglo *prof){
    int i, j, k, l, nivel = 0, contador_nivel = 0;
    // Determina la cantidad de niveles
    for(i = 0; i < prof -> max; i++){
        if(prof -> A[i] >= nivel){
            nivel = prof -> A[i];
        }
    }
    printf("\n\nNodos por nivel:");
    for(i = 0; i < nivel + 1; i++){
        // Determina la cantiad de nodos en un nivel
        for(j = 0; j < prof -> max; j++){
            if(prof -> A[j] == i){
                contador_nivel++;
            }
        }
        printf("\nNivel %d: ", i);
        for(j = 0; j < prof -> max; j++){
            if(i == prof -> A[j]){
                if(j == contador_nivel - 1){
                    printf("%d", j);
                }else{
                    printf("%d - ", j);
                }
            }
        }
    }
}

int main(int argv, char *argc[]){
    arreglo *arbol, *prof;
    nodo2 *arbol_nodo;
    int **M, i = 0;
    arbol = leer_archivo(argc[1]);
    if(arbol != NULL){
        prof = profundidad(arbol);
        profundidad_nodo(prof);
        /*
        Lo que intenté hacer fue crear una matriz de adyacencia, para un arbol m-ario algo
        similar a lo que se hace en grafos debido que la listas de adyacencia
        me daba error al momento de crear el arbol.
        Por lo que decidí hacerlo de esta manera, sin embargo, por alguna razón
        desconocida del más allá, no funcionó. (Segmentación de memoria de C).
        En este programa tardé más de 12 horas, me quedé corto de tiempo y entregué uno
        para árboles binarios, que tampoco quedó como lo que esperaba.
        */
        // M = transformar(arbol);
        // arbol_nodo = transformar2(M, arbol -> max);
        // preorden(arbol_nodo);
        // inorden(arbol_nodo);
        // postorden(arbol_nodo);
        arbol -> n = arbol -> max;
        arbol_nodo = crear_arbol_binario();
        arbol_nodo = arreglo_a_arbol(arbol, arbol_nodo, i);
        printf("\nRecorrido en preorden: ");
        preorden2(arbol_nodo);
        printf("\nRecorrido en inorden: ");
        inorden2(arbol_nodo);
        printf("\nRecorrido en postorden: ");
        postorden2(arbol_nodo);
        nodos_por_nivel(prof);
    }
    return 0;
}
