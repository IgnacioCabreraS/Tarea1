#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

List * cargar();
List * importar();
const char*get_csv_field (char *, int);
typedef struct listStruct list;


typedef struct{
    const char * nombre;
    const char * banda;
    const char * genero;
    const char * anno;
    const char * list_rep;
}Cancion;

const char*get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc(100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}

List * cargar(FILE * file, List* L){
    char lineaArchivo[1024];
    int i;
    int cont = 0;
    while (fgets (lineaArchivo, 1024, file) != NULL) {
        Cancion * cancion = (Cancion*) malloc (sizeof(Cancion));
        for(i = 0; i <= 4; i++){
            const char *aux = get_csv_field(lineaArchivo, i); // Se obtiene el nombre
            if(i == 0){
                cancion->nombre = (char *)aux;
                //printf("%s\n",cancion->nombre);
            }
            
            if(i == 1){
                cancion->banda = (char *)aux;
            } 

            if(i == 2){
                cancion->genero = (char *)aux;
                //printf("%s\n",cancion->genero);
            } 

            if(i == 3){
                cancion->anno = (char *)aux;
                //printf("%s\n",cancion->anno);
            } 

            if(i == 4){
                cancion->list_rep = (char *)aux;
                //printf("%s\n",cancion->list_rep);
            } 

        }
        
        if(vacio(L)){
            pushFront(L, cancion);
            firstList(L);
        }else{
            pushBack(L, cancion);
        }
        cont++; 
        if(cont == 70) break;
    } 
}

List * importar(){
    char archivo[101];
    FILE *file;

    do{
      printf("Ingresar nombre archivo: ");
      scanf("%s", &archivo);
      strcat(archivo, ".csv");
      file  = fopen(archivo, "r");
    }while(!file);
    List * L = createList();
    cargar(file,L);
    fclose(file);
    return L;
}

void buscarPorNombre (List * L){
    char * tema = (char*) malloc(40*sizeof(char));
    printf("Ingrese la cancion\n");
    scanf(" %[^\n]s]", tema);
    int contador = 0;

    Cancion* l = firstList(L);

    while(l->nombre != NULL){
        if(strcmp(l->nombre, tema) == 0){
            printf("\nNombre de la cancion: %s\n", l->nombre);
            printf("\nNombre de la banda o artista: %s\n", l->banda);
            printf("\nTipo de genero: %s\n", l->genero);
            printf("\nYear: %s\n", l->anno);
            printf("\nLista de reproduccion: %s\n", l->list_rep);
            contador++;
        }
        l=nextList(L);
        if(!l)break;
    } 
    printf("\n");
    if(contador == 0)printf("no ta manito\n");
    printf("\n");
}

void buscarPorArtista(List* L){
    char * band = (char*) malloc(30*sizeof(char));
    printf("Ingrese el nombre del artista/banda: ");
    scanf(" %[^\n]s", band);

    Cancion * l = firstList(L);
    
    while(l->banda != NULL){
        if(strcmp(l->banda, band) == 0){
            printf("\nNombre de la cancion: %s\n", l->nombre);
            //printf("\nNombre de la banda o artista: %s\n", l->banda);
            printf("\nTipo de genero: %s\n", l->genero);
            printf("\nYear: %s\n", l->anno);
            printf("\nLista de reproduccion: %s\n", l->list_rep);
        }
        l=nextList(L);
        if(!l)break;
    }
    printf("\n");
}

void buscarPorGenero (List * L){
    char * gener = (char*) malloc(40*sizeof(char));
    printf("Ingrese la cancion\n");
    scanf(" %[^\n]s]", gener);
    int contador = 0;
    Cancion* l = firstList(L);

    while(l->genero != NULL){
        if(strcmp(l->genero, gener) == 0){
            printf("\nNombre de la cancion: %s\n", l->nombre);
            printf("\nNombre de la banda o artista: %s\n", l->banda);
            printf("\nNombre del genero: %s\n", l->genero);
            printf("\nYear: %s\n", l->anno);
            printf("\nLista de reproduccion: %s\n", l->list_rep);
            contador++;
        }
        l=nextList(L);
        if(!l)break;
    } 
    printf("\n");
    if(contador == 0)printf("no ta manito\n");
    printf("\n");
}

void * agregarCancion (List * L){
    Cancion * nuevaCancion = (Cancion*) malloc (sizeof(Cancion));
    char * nombre = (char*) malloc(30*sizeof(char));

    printf("Ingrese el nombre de su cancion: ");
    scanf(" %[^\n]s", nombre);
    nuevaCancion->nombre=nombre;
    Cancion * cancion = firstList(L);
    
    while(cancion->nombre != NULL){
        
        if(strcmp(cancion->nombre, nuevaCancion->nombre)==0){
            printf("Esta cancion ya existe manito -_- .\n");
            nuevaCancion->nombre = "0";
            break;
        }
        cancion=nextList(L);
        if(!cancion){
            break;
        }
    }
    
    if(nuevaCancion->nombre == "0"){
        return NULL;
    }

    char * banda = (char*) malloc(30*sizeof(char));
    char * anno= (char*) malloc(4*sizeof(char));
    char * genero= (char*) malloc(30*sizeof(char));
    char * lista = (char*) malloc(30*sizeof(char));
    

    printf("\nNombre cancion nueva: %s\n", nuevaCancion->nombre);

    printf("Ingrese la banda de su cancion: ");
    scanf(" %[^\n]s",banda);
    nuevaCancion->banda=banda;
    printf("\nBanda cancion nueva: %s\n", nuevaCancion->banda);

    printf("Ingrese el/los genero/s de su cancion: ");
    scanf(" %[^\n]s",genero);
    nuevaCancion->genero=genero;
    printf("\nGenero cancion nueva: %s\n", nuevaCancion->genero);

    printf("Ingrese el año de su cancion: ");
    scanf(" %[^\n]s",anno);
    nuevaCancion->anno=anno;
    printf("\nAnno cancion nueva: %s\n", nuevaCancion->anno);

    printf("Ingrese la lista en la que desea ingresar su cancion: ");
    scanf(" %[^\n]s]",lista);
    nuevaCancion->list_rep=lista;
    printf("\nLista cancion nueva: %s\n", nuevaCancion->list_rep);
    pushBack(L,nuevaCancion);

    
    printf("Nueva cancion agregada.\n");
}

void mostrarLista (List * L){

    Cancion * x = (Cancion*) malloc(sizeof(Cancion));

    char nombreLista[100];
    int existe=0;

    printf ("Ingrese el nombre de la lista a buscar: ");
    scanf (" %[^\n]s]", &nombreLista);
    printf ("\n");
    x = firstList (L);
    while (x != NULL)
    {
        if (strcmp (x->list_rep, nombreLista) == 0)
        {
            printf ("%s, %s, %s, %s, %s\n", x->nombre, x->banda, x->genero, x->anno, x->list_rep);
            existe = 1;
            x = nextList (L);
        }
        else
        {
            x = nextList (L);
        }
    }

    if (existe == 0)
    {
        printf ("No existe la lista ingresada\n");
    }

    printf ("\n");
}

void Eliminar(List * L){
    char * canElimn = (char*) malloc(30*sizeof(char));
    int contador = 0;
    printf("Ingrese la cancion a eliminar\n");
    scanf(" %[^\n]s]", canElimn);

    Cancion* l = firstList(L);

    while(l->nombre != NULL){
        if(strcmp(l->nombre, canElimn) == 0){
            popCurrent(L);
            contador++;
            break;
        }
        l=nextList(L);
        if(!l)break;
    } 
    if(contador == 0) printf("\nNo existe la cancion a eliminar\n");
    else printf("\nCancion eliminada\n");
}

void mostrarCanciones(List * L){
    Cancion * x = (Cancion*) malloc(sizeof(Cancion));
    x = firstList (L);
    printf ("%s, %s, %s, %s, %s\n", x->nombre, x->banda, x->genero, x->anno, x->list_rep);
    x = nextList (L);
    while (x != NULL)
    {
        printf ("%s, %s, %s, %s, %s\n", x->nombre, x->banda, x->genero, x->anno, x->list_rep);
        x = nextList (L);
    }
    
}


void exportarCanciones (List * L){
    char * nombreArchivo = (char*) malloc(30*sizeof(char));
    FILE * nuevoFile;

    do{
        printf("Ingrese el nombre de su nuevo archivo .csv: ");
        scanf(" %[^\n]s", nombreArchivo);
        if(nombreArchivo == "Canciones"){
            printf("Este archivo .csv ya existe, intente con otro nombre.\n");
        }
    }while(nombreArchivo == "Canciones");
    
    printf("Nombre de su archivo: %s.csv\n",nombreArchivo);
    
    nombreArchivo = strcat(nombreArchivo,".csv");
    nuevoFile=fopen(nombreArchivo,"w+");

    Cancion * cancion = (Cancion*)malloc(sizeof(Cancion));
    cancion = firstList(L);

    while(cancion!=NULL){
        fprintf(nuevoFile,"%s,%s,%s,%s,%s\n",cancion->nombre,cancion->banda,cancion->genero,cancion->anno,cancion->list_rep);
        cancion = nextList(L);
    }
}

int main(){
    List * L;
    L = importar();

    /////////////////////////MENU/////////////////////////////
    int opcion=1;
    printf("----------------- CANCIONES ------------------\n\n");
    while (opcion!=0){
        printf("1. Agregar cancion\n");
        printf("2. Eliminar cancion\n");
        printf("3. Buscar cancion por nombre\n");
        printf("4. Buscar cancion por artista\n");
        printf("5. Buscar cancion por genero\n");
        printf("6. Mostrar nombres de las listas de reproduccion\n");
        printf("7. Mostrar lista de reproduccion\n");
        printf("8. Mostrar todas las canciones\n");
        printf("9. Exportar canciones a un archivo csv nuevo.\n");
        printf("0. Salir del programa\n");
        scanf("\n%d",&opcion);

        switch(opcion){
            case 1:agregarCancion(L);break;
            case 2:Eliminar(L);break;
            case 3:buscarPorNombre(L);break;
            case 4:buscarPorArtista(L);break;
            case 5:buscarPorGenero(L);break;
            case 6:break;
            case 7:mostrarLista(L);break;
            case 8:mostrarCanciones(L);break;
            case 9:exportarCanciones(L);break;
        }
    }
    return 0;
}