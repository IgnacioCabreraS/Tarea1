#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct{
    const char * Cancion;
    const char * Banda;
    const char * Genero;
    int anno[4];
    int lista[7];
}Cancion;

int main(){
    
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
        printf("0. Salir del programa\n");
        scanf("\n%d",&opcion);

        switch(opcion){
            case 1:printf("Agregar cancion (no hecha)\n");break;
            case 2:printf("Eliminar cancion (no hecha)\n");break;
            case 3:printf("Buscar cancion por nombre (no hecha)\n");break;
            case 4:printf("Buscar cancion por artista (no hecha)\n");break;
            case 5:printf("Buscar cancion por genero (no hecha)\n");break;
            case 6:printf("Mostrar nombres de las listas de reproduccion (no hecha)[n");break;
            case 7:printf("Mostrar lista de reproduccion (no hecha)\n");break;
            case 8:printf("Mostrar todas las canciones (no hecha)\n");break;
            
        }
    }

    return 0;
}

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

