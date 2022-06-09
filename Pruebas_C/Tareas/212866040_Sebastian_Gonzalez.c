#include<stdio.h>
#include<stdlib.h>

struct nodo{
    char info;
    struct nodo *ant;
    struct nodo *sig;
};

struct lista{
    struct nodo *inicio;
    struct nodo *fin;
};

struct nucleotidos{
    struct lista *L;
    int cantidad;
    int pliegue;
    int libre;
};

struct nucleotidos* crear_nucleotidos(void){
    // Se crea una nueva variable de tipo nucleotidos
    struct nucleotidos *nuevo;
    // Se le asigna memoria de manera dinamica a nuevo
    nuevo = (struct nucleotidos *)malloc(sizeof(struct nucleotidos));
    // Se le asignan valores por defecto
    nuevo -> cantidad = 0;
    nuevo -> pliegue = 0;
    nuevo -> libre = 0;
    nuevo -> L = NULL;
    // Se retorna nuevo
    return nuevo;
}

struct nodo* crear_nodo(char info){
    // Se crea una nueva variable de tipo nodo
    struct nodo *nuevo;
    // Se le asigna memoria de manera dinamica a nuevo
    nuevo = (struct nodo *)malloc(sizeof(struct nodo));
    // Se le asigna valores por defecto al nodo
    nuevo -> info = info;
    nuevo -> sig = NULL;
    nuevo -> ant = NULL;
    // Se retorna el nuevo nodo
    return nuevo;
}

struct lista* crear_lista(void){
    // Se crea una nueva variable de tipo lista
    struct lista *nuevo;
    // Se le asigna memoria de manera dinamica a nuevo
    nuevo = (struct lista *)malloc(sizeof(struct lista));
    // Se le asignan valores por defecto a la lista
    nuevo -> inicio = NULL;
    nuevo -> fin = NULL;
    // Se retorna la lista
    return nuevo;
}

int vacio(struct lista *L){
    if(L -> inicio == NULL && L -> fin == NULL){
        return 1;
    }else{
        return 0;
    }
}

struct lista* agregar_elemento(struct lista *L, char elemento){
    // Se inicializa variable
    struct nodo *n, *aux;
    // Se verifica que si L es una lista vacia
    if(!vacio(L)){
        // Se crea un nuevo nodo
        n = crear_nodo(elemento);
        aux = L -> fin;
        L -> fin -> sig = n;
        L -> fin = n;
        L -> fin -> ant = aux;
    }else{
        // Se inicializa variable
        // Se crea un nuevo nodo
        n = crear_nodo(elemento);
        L -> fin = n;
        L -> inicio = n;
    }
    return L;
}

struct lista* eliminar_inicio(struct lista *L){
    L -> inicio = L -> inicio -> sig;
    return L;
}

struct lista* eliminar_final(struct lista *L){
    L -> fin = L -> fin -> ant;
    L -> fin -> sig == NULL;
    return L;
}

struct nucleotidos* leer_archivo(char *nombre_archivo){
    // Se inicializan variables
    char car;
    struct nodo *n;
    FILE *archivo;
    struct lista *List;
    struct nucleotidos *N;
    // Se crea la lista L y nucleotidos N
    List = crear_lista();
    N = crear_nucleotidos();
    // Se abre el archivo
    archivo = fopen(nombre_archivo, "r");
    // Se obtiene la cantidad de elementos
    fscanf(archivo, "%d", &(N -> cantidad));
    // Se comienza a obtener la cadena de caracteres
    while(fscanf(archivo, "%c" , &car) != EOF){
        if(car != '\n')
            List = agregar_elemento(List, car);
    }
    // Una vez teniendo la lista se agrega a la estructura nucleotidos
    N -> L = List;
    // Se cierra el archivo
    fclose(archivo);
    // Se retorna N
    return N;
}

struct nucleotidos* cantidad_nucleotidos(struct nucleotidos *N){
    char inicio, fin;
    struct lista *aux;
    aux = N -> L;
    while(aux -> inicio -> sig != NULL && aux -> inicio != NULL){
        inicio = aux -> inicio -> info;
        fin = aux -> fin -> info;
        if((inicio == 'a' && fin == 'u') || (inicio == 'u' && fin == 'a')){
            N -> pliegue += 1;
        }else if((inicio == 'c' && fin == 'g') || (inicio == 'g' && fin == 'c')){
            N -> pliegue += 1;
        }else{
            N -> libre = N -> cantidad - 2 * N -> pliegue;
            return N; 
        }
        aux = eliminar_inicio(aux);
        aux = eliminar_final(aux);
    }
    return N;
}

int main(int argc, char *argv[]){
    // Se declara una variable para almacenar la dirección del primer
    // caracter de la cadena de caracteres que será este el nombre del
    // archivo
    char *nombre_archivo;
    struct nucleotidos *n;
    nombre_archivo = argv[1];
    n = leer_archivo(nombre_archivo);
    n = cantidad_nucleotidos(n);
    printf("El largo de la secuencia es %d nucleótidos\n"
    "Nucleotidos pliegue: %d\nNucleotidos libres: %d\n"
    , n ->cantidad, n->pliegue, n->libre);
    return 0;
}
