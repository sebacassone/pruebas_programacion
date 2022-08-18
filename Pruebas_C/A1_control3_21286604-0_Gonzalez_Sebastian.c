/*
Nombre del autor: Sebastián Andrés González Cassone
Sección: A-1
RUT: 21.286.604-0
Descripción del programa: Este programa se encarga de mostrar el número
aristas que superan el peso promedio de las aristas del grafo, grado
promedio de los nodos del grafo, densidad del grafo, y por último
genera un archivo de salida llamado salida.txt en donde se encuentra el
arbol de cobertura mínima cumpliendo con el formato pedido.
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
	int *info;
	struct nodo *sig;
} nodo;

typedef struct lista{
	nodo *inicio;
	nodo *fin;
} lista;

typedef struct grafo{
	int vertice;
	int arista;
	int **matriz;
} grafo;

nodo *crear_nodo(int *valor){
	nodo *nuevo_nodo;
	nuevo_nodo = (nodo *)malloc(sizeof(nodo));
	nuevo_nodo -> info = valor;
	nuevo_nodo -> sig = NULL;
	return nuevo_nodo;
}

lista *crear_lista(void){
	lista *nueva_lista;
	nueva_lista = (lista *)malloc(sizeof(lista));
	nueva_lista -> inicio = NULL;
	nueva_lista -> fin = NULL;
	return nueva_lista;
}

int **crear_matriz(grafo *grafo_general){
    /*
    Esta función se encarga de crear una matriz de enteros de tamaño
    vertice x vertice, donde cada posición de la matriz representa una
    arista del grafo.
    */
	int **nueva_matriz, *fila;
	// Se crea espacio en memoria para la matriz
	nueva_matriz = (int **)malloc(sizeof(int *) * (grafo_general -> vertice));
	// Se crea espacio en memoria para cada fila
	for(int i = 0; i < (grafo_general -> vertice); i++){
		fila = (int *)malloc(sizeof(int) * (grafo_general -> vertice));
		// Se asignan valores iniciales para fila y columna
		for(int j = 0; j < (grafo_general -> vertice); j++)
			fila[j] = -1;
		// Se agrega cada fila a la matriz
		nueva_matriz[i] = fila;
	}
	return nueva_matriz;
}

grafo *crear_grafo(void){
    /*
    Esta función se encarga de crear un grafo de tipo grafo, donde se
    guardan los datos de vertices y aristas.
    */
	grafo *nuevo_grafo;
	// Se crea en memoria espacio para los vertices y aristas
	// Se asignan valores por defecto
	nuevo_grafo = (grafo *)malloc(sizeof(grafo));
	nuevo_grafo -> vertice = 0;
	nuevo_grafo -> arista = 0;
	nuevo_grafo -> matriz = NULL;
	return nuevo_grafo;
}

void agregar_final_lista(lista *L, int *valor){
    /*
    Esta función se encarga de agregar un nodo al final de la lista.
    */
    nodo *nuevo_nodo;
    nuevo_nodo = crear_nodo(valor);
    if(L -> inicio == NULL){
        L -> inicio = nuevo_nodo;
        L -> fin = nuevo_nodo;
    }
    else{
        L -> fin -> sig = nuevo_nodo;
        L -> fin = nuevo_nodo;
    }
}

nodo *eliminar_inicio_lista(lista *L){
    /*
    Esta función se encarga de eliminar el primer nodo de la lista.
    */
    nodo *aux;
    aux = L -> inicio;
    L -> inicio = L -> inicio -> sig;
    return aux;
}

int vaciar_lista(lista *L){
    /*
    Esta función se encarga de vaciar la lista.
    */
    nodo *aux;
    while(L -> inicio != NULL){
        aux = eliminar_inicio_lista(L);
        free(aux);
    }
    return 1;
}

int largo(lista *L){
    /*
    Esta función se encarga de contar el largo de la lista.
    */
    int largo = 0;
    nodo *aux;
    aux = L -> inicio;
    while(aux != NULL){
        largo++;
        aux = aux -> sig;
    }
    return largo;
}

grafo *leerGrafo(char *nombre){
    /*
    Esta función se encarga de leer el grafo desde un archivo de texto.
    */
	FILE *archivo;
	grafo *grafo_general;
	int i, j, n, a, cont, **G, k;

	//instrucciones para leer archivo
	archivo = fopen(nombre, "r");
	if (archivo == NULL){
		printf("Error al acceder a archivo\n");
		grafo_general -> vertice = -8;
		return grafo_general;
	}else{
		printf("Archivo leido\n");
	}

	// se crea espacio para la estuctura
	grafo_general = crear_grafo();

	//leer datos del archivo
	fscanf(archivo,"%d %d",&n,&a);

	grafo_general -> vertice = n;   //almacenamos la cantidad de nodos
	grafo_general -> arista = a;

	//printf("\nGrafo a leer: %d nodos y %d aristas",n, a);
	
	//crear matriz
	G = crear_matriz(grafo_general);

	//leer aristas
	for(int cont = 0; cont < a; cont++){
		//leer datos del archivo
		fscanf(archivo,"%d %d %d",&i,&j,&k);
		//printf("\nArista leido: (%d,%d) de costo %d",i,j,k);	
		G[i-1][j-1] = k;
		G[j-1][i-1] = k;
	}

	// almacenamos la matriz
	grafo_general -> matriz = G;
	
	printf("\nGrafo leido: %d nodos y %d aristas\n",n, a);

	return grafo_general;
}

float promedio_aristas(grafo *grafo_general){
    /*
    Esta función se encarga de calcular el promedio de aristas del grafo.
    */
    int i, j;
    float acum = 0;
    // Se recorre la matriz para obtener el promedio
    for(i = 0; i < grafo_general -> vertice; i++){
        for(j = 0; j < grafo_general -> vertice; j++){
            if(grafo_general -> matriz[i][j] != -1){
                // Se suma la mitad del costo, debido a que en la
                // matriz se encuentra dos veces el valor del costo
                // y para solucionar ese problema se suma primero una
                // mitad y luego la otra mitad ejemplo: primero sumará
                // la mitad del costo de matriz[i][j] y luego
                // matriz[j][i] y su suma dará el valor del costo.
                acum += ((grafo_general -> matriz[i][j]) * 0.5);
            }
        }
    }
    // Se aplica promedio simple
    return acum / (grafo_general -> arista);
}

int costo_promedio(grafo *grafo_general){
    /*
    Esta función se encarga de calcular el costo promedio del grafo.
    */
    int i, j;
    float promedio, acum = 0;
    // Se obtiene el promedio de los costos
    promedio = promedio_aristas(grafo_general);
    // Se recorre la matriz de adyacencia
    for(i = 0; i < grafo_general -> vertice; i++){
        for(j = 0; j < grafo_general -> vertice; j++){
            // Se verifica si el elemento [i][j] supera el promedio
            if(grafo_general -> matriz[i][j] > promedio){
                acum += 0.5;
            }
        }
    }
    // Se imprime en pantalla
    printf("\nNúmero de aristas que superan el peso promedio: %.0f"
    " aristas sobre el peso promedio (%.2f)", acum, promedio);
    return 1;
}

int grado_promedio(grafo *grafo_general){
    /*
    Esta función se encarga de calcular el grado promedio del grafo.
    */
    int i, j, acum = 0;
    float acum2 = 0;
    // Se recorre la matriz
    for(i = 0; i < grafo_general -> vertice; i++){
        acum = 0;
        for(j = 0; j < grafo_general -> vertice; j++){
            // Si es distinto de -1 es por que el vertice tiene
            // una arista por lo que se le suma suma 1 a acum
            // para cuando termine este ciclo for tener el grado
            // del vertice i.
            if(grafo_general -> matriz[i][j] != -1)
                acum += 1;
        }
        // Comienza a sumar los grafos de los vertices
        acum2 += acum;
    }
    // Se muestra por pantalla el grado promedio
    printf("\nGrados promedio de los nodos: %.2f", (acum2 / (grafo_general -> vertice)));
    return 1;
}

float densidad(grafo *grafo_general){
    /*
    Esta función se encarga de calcular la densidad del grafo.
    */
    float resultado;
    float n, m;
    m = 2 * grafo_general -> arista;
    n = grafo_general -> vertice * (grafo_general -> vertice - 1);
    return m / n;
}

int mostrar_grafo(grafo *grafo_general){
    /*
    Esta función está encargada de imprimir la matriz.
    */
    printf("\n");
    for(int i = 0; i < grafo_general -> vertice; i++){
        for(int j = 0; j < grafo_general -> vertice; j ++)
            printf("%d ", grafo_general -> matriz[i][j]);
        printf("\n");
    }
    return 1;
}

int copiar_matrices(int **G, int **G2, grafo *grafo_general){
    /*
    Esta función está encargada de copiar la matriz original a la
    matriz auxiliar.
    */
    for(int i = 0; i < grafo_general -> vertice; i++){
        for(int j = 0; j < grafo_general -> vertice; j ++)
            G2[i][j] = G[i][j];
    }
    return 1;
}

int arbol(grafo *G, int **matriz){
    /*
    Esta función se encarga de reemplazar los valores de la matriz
    por -1 para que no se pueda acceder a ellos. Además de reemplazar
    los -2 por sus costos correspondientes.
    */
    int i, j;
    for(i = 0; i < G -> vertice; i++){
        for(j = 0; j < G -> vertice; j++){
            if(G -> matriz[i][j] != -2){
                G -> matriz[i][j] = -1;
            }else{
                G -> matriz[i][j] = matriz[i][j];
            }
        }
    }
    return 1;
}

int mayor(grafo *grafo_general){
    /*
    Esta función se encarga de calcular el mayor de los costos
    */
    int i, j, mayor = 0;
    for(i = 0; i < grafo_general -> vertice; i++){
        for(j = 0; j < grafo_general -> vertice; j++){
            if(grafo_general -> matriz[i][j] > mayor){
                mayor = grafo_general -> matriz[i][j];
            }
        }
    }
    return mayor;
}

int *crear_arreglo(grafo *grafo_general){
    /*
    Esta función se encarga de crear un arreglo de enteros.
    */
    int *z;
    z = (int *)malloc(sizeof(int) * grafo_general -> vertice);
    int i;
    for(i = 0; i < grafo_general -> vertice; i++){
        z[i] = 0;
    }
    return z;
}

int arbol_de_cobertura_minima(grafo *grafo_general){
    /*
    Esta función se encarga de calcular el arbol de cobertura minima
    */
    int i, j, **M, menor = 0, k[] = {0,0}, *z;
    lista *visitados, *aux2;
    grafo *aux;
    M = crear_matriz(grafo_general);
    visitados = crear_lista();
    aux2 = crear_lista();
    aux = crear_grafo();
    aux = grafo_general;
    z = crear_arreglo(grafo_general);
    copiar_matrices(grafo_general -> matriz, M, grafo_general);
    // Se agrega la primera fila a la lista de visitados
    agregar_final_lista(visitados, aux -> matriz[0]);
    z[0] = 1;

    while(largo(visitados) != aux -> vertice){
        menor = mayor(grafo_general);
        vaciar_lista(aux2);
        for(i = 0; i < (aux -> vertice); i++){
            agregar_final_lista(aux2, aux -> matriz[i]);
        }
        // Este ciclo varía de acuerdo al largo que vaya a adquerir visitados
        for(i = 0; i < largo(visitados); i++){
            // La duración de este ciclo será fijo ya que aux -> vertice
            // es constante durante la ejecución de la función
            for(j = 0; j < aux -> vertice; j++){
                if(aux2 -> inicio -> info[j] < menor && aux2 -> inicio -> info[j] > 0){
                    if(z[i] == 0 || z[j] == 0){
                        // En caso de encontrar otro costo menor, actualiza el menor
                        menor = aux2 -> inicio -> info[j];
                        // Guarda las posiciones de donde se encontraba el menor
                        k[0] = i;
                        k[1] = j;
                        // Se marca el vertice como visitado
                    }    
                }
            }
            eliminar_inicio_lista(aux2);
        }
        // Se marca como visitado el vertice
        z[k[1]] = 1;
        // Se marca como visitado en la matriz por adyacencia
        aux -> matriz[k[0]][k[1]] = -2;
        aux -> matriz[k[1]][k[0]] = -2;
        // Se agrega a la lista de visitados
        agregar_final_lista(visitados, aux -> matriz[k[1]]);
    }
    // Intercambia los valores de la matriz
    arbol(aux, M);
    aux -> arista = aux -> vertice - 1;
    grafo_general = aux;
    return 1;
}

int costo_minimo(grafo *grafo_general){
    /*
    Se encarga de sumar todos los costos de la matriz del arbol de
    cobertura minima.
    */
    int i, j, acum = 0, **matriz;
    matriz = crear_matriz(grafo_general);
    copiar_matrices(grafo_general -> matriz, matriz, grafo_general);
    for(i = 0; i < grafo_general -> vertice; i++){
        for(j = 0; j < grafo_general -> vertice; j++){
            if(matriz[i][j] != -1){
                acum += matriz[i][j];
                matriz[i][j] = -1;
                matriz[j][i] = -1;
            }
        }
    }
    return acum;
}
   
int archivo_salida(grafo *grafo_general){
    /*
    Esta función se encarga de escribir en un archivo el arbol de
    cobertura minima.
    */
    FILE *archivo;
    int costo;
    costo = costo_minimo(grafo_general);
    archivo = fopen("salida.txt", "w");
    if(archivo == NULL){
        printf("\nError al abrir el archivo");
        return 0;
    }
    fprintf(archivo, "%d %d", grafo_general -> vertice, grafo_general -> arista);
    for(int i = 0; i < grafo_general -> vertice; i++){
        for(int j = 0; j < grafo_general -> vertice; j++){
            if(grafo_general -> matriz[i][j] != -1){
                fprintf(archivo, "\n%d %d %d", i + 1, j + 1, grafo_general -> matriz[i][j]);
                grafo_general -> matriz[i][j] = -1;
                grafo_general -> matriz[j][i] = -1;
            }
        }
    }
    fprintf(archivo, "\n%d", costo);
    fclose(archivo);
    printf("\nEl archivo salida.txt se ha creado con éxito\n");
    return 1;
}

int main(int argc, char *argv[]){
    grafo *G;
    // Entrada de datos
    G = leerGrafo(argv[1]);
    // Proceso de datos
    costo_promedio(G);
    grado_promedio(G);
    printf("\nDensidad: %.3f", densidad(G));
    arbol_de_cobertura_minima(G);
    // Salida de datos
    archivo_salida(G);
    return 0;
}
