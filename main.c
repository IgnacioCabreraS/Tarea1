#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

List * cargar();
List * importar();
const char*get_csv_field (char *, int);

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
    char linea [1024];
    int i;
    int cont = 0;
    while (fgets (linea, 1023, file) != NULL) {
        Cancion * cancion = (Cancion*) malloc (sizeof(Cancion));
        for(i = 0; i < 4; i++){
            const char *aux = get_csv_field(linea, i); // Se obtiene el nombre
            if(i == 0){
                cancion->nombre = (char *)aux;
                printf("%s\n",cancion->nombre);
            }
            
            if(i == 1) cancion->banda = (char *)aux;
            if(i == 2) cancion->genero = (char *)aux;
            if(i == 3) cancion->anno = (char *)aux;
            if(i == 4) cancion->list_rep = (char *)aux;
        }

        if(vacio(L)){
            pushFront(L, cancion);
            firstList(L);
        }else{
            pushBack(L, cancion);
        }
        cont++; 
        if(cont == 69) break;
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

    return L;
}

void *buscarNombre (List * L, Cancion * nuevaCancion){
    Cancion * l = firstList(L);

    while(l->nombre != nuevaCancion->nombre){
        
    }
    /*
    while(stricmp(nuevaCancion->nombre,l->nombre)!=0){
        l=nextList(L);
        if(!l)break;
        if(stricmp(nuevaCancion->nombre,l->nombre) == 0){
            printf("Esta cancion ya existe\n");
            return NULL;
        }
    } 
    */
    return l;
    
}

void agregarCancion (List * L){
    Cancion * nuevaCancion = (Cancion*) malloc (sizeof(Cancion));
    printf("Ingrese el nombre de su cancion: ");
    scanf("%s",&nuevaCancion->nombre);

    Cancion * l;
    Cancion * cancion = firstList(L);
    l = buscarNombre(L, nuevaCancion);

}

void buscarPorNombre (List * L){

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
        printf("3. BuscarPorNombre\n");
        printf("4. Buscar cancion por nombre\n");
        printf("5. Buscar cancion por artista\n");
        printf("6. Buscar cancion por genero\n");
        printf("7. Mostrar nombres de las listas de reproduccion\n");
        printf("8. Mostrar lista de reproduccion\n");
        printf("9. Mostrar todas las canciones\n");
        printf("0. Salir del programa\n");
        scanf("\n%d",&opcion);

        switch(opcion){
            case 1:agregarCancion(L);break;
            case 2:printf("Eliminar cancion (no hecha)\n");break;
            case 3:buscarPorNombre(L);break;
            case 4:printf("Buscar cancion por nombre (no hecha)\n");break;
            case 5:printf("Buscar cancion por artista (no hecha)\n");break;
            case 6:printf("Buscar cancion por genero (no hecha)\n");break;
            case 7:printf("Mostrar nombres de las listas de reproduccion (no hecha)[n");break;
            case 8:printf("Mostrar lista de reproduccion (no hecha)\n");break;
            case 9:printf("Mostrar todas las canciones (no hecha)\n");break;
            
        }
    }
    return 0;
}