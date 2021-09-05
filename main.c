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
    char * genero;
    const char * anno;
    const char * list_rep;
}Cancion;

/*
    Funcion que recibe una linea, la lee hasta la coma y retorna lo leido, todo esto hasta llegar al final de la linea
*/
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

/*  
    Funcion que lee una linea de un archivo, crea un tipo de dato "Cancion", trabaja la linea en la funcion "get_csv_field"
    para obtener cada palabra hasta la "," con lo que rellenar los campos el dato tipo "Cancion" e insertarlo en la lista
    anteriormente creada, todo esto hasta que se acabe la linea y hasta que se lea el archivo por completo
*/
List * cargar(FILE * file, List* L){
    char lineaArchivo[1024];
    int i;
    int cont = 0;
    while (fgets (lineaArchivo, 1024, file) != NULL) {
        Cancion * cancion = (Cancion*) malloc (sizeof(Cancion));
        for(i = 0; i <= 4; i++){
            const char *aux = get_csv_field(lineaArchivo, i); // Se obtiene el nombre
            if(i == 0) cancion->nombre = (char *)aux;
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
        if(cont == 70) break;
    } 
}

/*
    Funcion para leer el archivo csv y crear la lista
*/
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

/* 
    Funcion encargada de buscar un nombre de cancion donde en base a una variable l tipo cancion recorremos la lista, 
    esto lo hacemos con un ciclo while el cual funciona hasta el final de la lista, ademas dentro de este comprobamos 
    si el nombre de cancion ingresada por patanlla es igual a alguno que se encuentre en nuestra lista printfteamos sus datos.
    y el contador para verificar si existe el artista a buscar.
*/
void buscarPorNombre (List * L){
    // otorgamos memoria a la variableque se  ingresara por pantalla
    char * tema = (char*) malloc(30*sizeof(char));
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
    if(contador == 0)printf("No se encuentra el nombre a buscar\n");
    printf("\n");
}

/* 
    Funcion encargada de buscar al artista donde en base a una variable l tipo cancion recorremos la lista, esto lo hacemos
    con un ciclo while el cual funciona hasta el final de la lista, ademas dentro de este comprobamos si la banda/artista 
    ingresada por patanlla es igual a alguno que se encuentre en nuestra lista printfteamos sus datos. y el contador para
    verificar si existe el artista a buscar.
*/
void buscarPorArtista(List* L){
    char * band = (char*) malloc(30*sizeof(char));
    printf("Ingrese el nombre del artista/banda: ");
    scanf(" %[^\n]s", band);
    int contador = 0;
    Cancion * l = firstList(L);
    
    while(l->banda != NULL){
        // se usa strcmp para verificar si en la lista se encuentra la banda/artista
        if(strcmp(l->banda, band) == 0){
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
    if(contador == 0)printf("No se encuentra el artista/banda a buscar\n");
    printf("\n");
}

/*
    Funcion encargada de sacar la cantidad de generos
*/
int cntG(Cancion * m){
    int cont = 0; 
    // funcion strtok para sacar la cadena por palabras
    char* token = strtok(m->genero, ", "); 
    while(token != NULL){
        cont++;
        token = strtok(NULL, ", ");
    }
    return cont;
}

/* 
    Funcion enargada de buscar el genero donde utilizamos una variable l para recorrer la lista y ademas utilizando dos funciones, 
    las cuales nos separa por coma las palabras que se encuentra en el campo de genero y la otra funcion que cuenta la cantidad
    de generos que hay. Posterior a esto recorremos con un for para verificar si alguno de los generos es igual al ingresado por pantalla
    y se imprime por pantalla.

*/

void buscarPorGenero (List * L){
    char* gener = (char*)malloc(30*sizeof(char));
    printf("keremo la weaita\n");
    scanf(" %[^\n]s]", gener);
    Cancion* l = (Cancion*)malloc(30*sizeof(Cancion));
    l = firstList(L);
    l = nextList(L);
    char* token;
    token = strtok(l->genero, ",");
    while(token){
        printf("%s -",token);
        token = strtok(NULL, ",");
    }
    //int cantGeneros = cntG(l);
    /*
    for(int i = 0 ; i < cantGeneros ; i++){
        if(cantGeneros == 1){
            if(strcmp(l->genero, gener) == 0){
                printf("\nNombre dez la cancion: %s\n", l->nombre);
            }
        }else{
            char* token;
            token = strtok(l->genero, ",");
            //if(strcmp(l->genero, gener) == 0){
                //printf("si");
            //}
            while(token){
                printf("%s -",token);
                token = strtok(NULL, ",");
            }
        }
    }*/


}




    /*
        for(int i = 0; l->genero[i] != "\0"; i++){
            if(l->genero[i] == ","){
                printf("i");
            }else{
                if(strcmp(l->genero, gener) == 0){
                    printf("\nNombre de la cancion: %s\n", l->nombre);
                }
            }
        }
    */

/*
    Funcion que crea una nueva lista en donde por medio de ciclos, se obtendran todos los nombres de las listas de reproduccion
    que hayan en la primera lista (la cual tiene todas las canciones tanto del csv como las agregadaas por el usuario) para luego
    nuevamente por medio de ciclos y contadores obtener cuantas canciones tiene cada lista y mostrarlo por pantalla
*/
void listaCuantosTemas (List * L){

    Cancion * x = (Cancion*) malloc(sizeof(Cancion));

    const char * nombre;
    int esta=0, cont=0;

    x = firstList(L);
    nombre = x->list_rep;
    List * N = createList();
    pushFront (N, nombre);
    firstList (N);
    x = nextList (L);

    while (x != NULL)
    {
        esta=0;
        nombre = firstList (N);
        while (nombre != NULL)
        {
            if (strcmp (x->list_rep, nombre) == 0)
            {
                esta = 1;
                nombre = nextList (N);
            }
            else
            {
                nombre = nextList (N);
            }
        }

        if (esta == 0)
        {
            pushBack (N, x->list_rep);
            x = nextList (L);
        }
        else
        {
            x = nextList (L);
        }
    }

    nombre = firstList (N);
    while (nombre != NULL)
    {
        cont = 0;
        x = firstList (L);
        while (x != NULL)
        {
            if (strcmp (nombre, x->list_rep) == 0)
            {
                cont++;
                x = nextList (L);
            }
            else
            {
                x = nextList (L);
            }
        }

        if (cont != 0)
        {
            printf ("Nombre de la lista: %s\n", nombre);
            printf ("Cantidad de canciones: %d\n", cont);
        }

        nombre = nextList (N);
    }
}

/*
    Funcion que crea un tipo de dato "Cancion", pide el nombre de una cancion, verifica que esta no esta en la lista,
    y va pidiendo los otros datos de la cancion (banda, genero, año y lista de reproduccion) para luego agregar la cancion
    a la lista la cual tiene todas las canciones del archivo csv anteriormente cargado
*/
void * agregarCancion (List * L){
    Cancion * nuevaCancion = (Cancion*) malloc (sizeof(Cancion));
    char * nombre = (char*) malloc(30*sizeof(char));

    printf("Ingrese el nombre de su cancion: ");
    scanf(" %[^\n]s", nombre);
    nuevaCancion->nombre=nombre;
    Cancion * cancion = firstList(L);
    
    while(cancion->nombre != NULL){
        
        if(strcmp(cancion->nombre, nuevaCancion->nombre)==0){
            printf("Esta cancion ya existe.\n");
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

/*
    La funcion mostrar lista lo que hace es que el usuario ingrese el nombre de la lista, despues se muestra por pantalla 
    las canciones con todos sus datos que pertenezcan a esa lista, en caso de que la lista ingresada no existe
    se mostrara un mensaje de que la lista ingresada no existe. 
*/ 
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

 /*
    Funcion encargada de eliminar el elemnto ingresado por pantalla, en esta funcion creamos una varible tipo cancion
    para recorrer la lista, ademas utilizamos el strcmp para verificar si la palabra ingresada se encuentra en el campo
    de nuestro struct. Ademas, verificamos que si no se encuentra regrese por pantalla que no se encuentra en nuestra lista
    de canciones.
 */
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

/*
    Funcion encargada de recorrer la lista y mostrar cada uno de los campos que compone
    para ello utilizamos una variable tipo cancion que nos ayudara a recorrer nuestra lista
    hasta que esta llega a null y un nexlist para ir avaznando.
*/
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

/*
    La funcion de exportarCanciones lo que hace es crear un archivo, pedir por pantalla el nombre de el archivo, 
    si este es igual al a "Canciones", se muestra por pantalla que ya existe ese archivo e ingrese otro nombre,
    si no, se muestra el nombre por pantalla junto con la extension "csv", se abre el archivo y se recorre la lista
    escribiendo en el archivo cada cancion con todos sus datos
*/
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

/*
    Cuerpo principal del programa, donde se crea un dato tipo "Lista" el cual se trabajara mediante funciones para ser una lista con
     todos las canciones del archivo csv, y ademas se muestra el menu del programa con todas sus funciones
*/
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
            case 5:buscarPorGenero(L);break; //arreglando, faltan demas generos
            case 6:listaCuantosTemas(L);break;
            case 7:mostrarLista(L);break;
            case 8:mostrarCanciones(L);break;
            case 9:exportarCanciones(L);break;
        }
    }
    return 0;
}