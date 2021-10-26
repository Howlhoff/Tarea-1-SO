#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define N 100

/*****
* int check
******
* checkea si string esta dentro de arr
******
* Input:
* char** arr : arreglo de strings
* int n : tamaño de arr
* char* string : string a verificar
******
* Returns:
* int, retorna 1 si esta dentro, retorna 0 si no se encuentra
*****/


int check(char** arr,int n,char* string){
    for(int i = 0; i < n; i++){
        if (arr[i] != NULL){
            if(strcmp(arr[i],string)){
                return 1;
            }
        }
    }
    return 0;
    
}

/*****
* char** buscador
******
* busca los path en los que contiene el archivo "archivo"
******
* Input:
* char* archivo : el nombre del archivo
******
* Returns:
* char**, retorna un arreglo de directorios
*****/

char** buscador(char* archivo){
    char** directorios=(char**)malloc(20);
    char* n1 = (char*)malloc(N);
    char* n2 = (char*)malloc(N);
    char* n3 = (char*)malloc(N);
    char* strings[3]={"1","2","3"};
    int l = 0;
    chdir("Laberinto/");
    for(int i = 0; i < 3; i++){
        ///Nivel 1
        strcpy(n1,strings[i]);
        strcat(n1,"/");
        chdir(n1);            
        for(int j = 0; j < 3; j++){
            ///Nivel 2
            strcpy(n2,strings[j]);
            strcat(n2,"/");
            chdir(n2);
            for(int k = 0; k < 3; k++){
                ///Nivel 3
                strcpy(n3,strings[k]);
                strcat(n3,"/");
                chdir(n3);
                if(!access(archivo,F_OK)){
                    char* path=(char*)malloc(N);
                    directorios[l] = getcwd(path,N);
                    l++;
                }
                chdir("..");
            }
            chdir(".."); 
        }
        chdir("..");    
    }  
    return directorios;
}

/*****
* char* extractor
******
* extrae el string del archivo
******
* Input:
* char* archivo : nombre del archivo
******
* Returns:
* char*, retorna el string dentro del archivo
*****/

char* extractor(char* archivo){
    FILE* fp;
    char* string = (char*)malloc(N);
    fp = fopen(archivo,"r");
    if(fp == NULL){
        printf("El archivo no se pudo abrir\n");
        exit(1);
    }
    else{
        if(!feof(fp)){
            fgets(string,N,fp);
        }
        fclose(fp);
    }
    return string;
}

/*****
* char** sort
******
* retorna el arreglo arr ordenado
******
* Input:
* char** arr: arreglo desordenado
* int n: tamaño del arreglo
******
* Returns:
* char**, retorna el arreglo ordenado en base a una caracteristica del string
*****/

char** sort(char** arr,int n){
    char** new = (char**)malloc(n);
    for(int i = 0; i < n; i++){
        if(arr[i][0]=='1'){
            new[0]=arr[i];
        }
        else if(arr[i][0]=='2'){
            new[1]=arr[i];
        }
        else if(arr[i][0]=='3'){
            new[2]=arr[i];
        }
        else{
            break;
        }
    }
    return new;
}

/*****
* void to_string
******
* imprime por pantalla lo que aparece en el arreglo arr
******
* Input:
* char** arr: arreglo de strings
* int n: tamaño del arreglo
******
* Returns:
* No retorna nada
*****/

void to_string(char** arr, int n){
    for(int i = 0; i < n; i++){
        for(int j = 3; j < strlen(arr[i]); j++){
            putchar(arr[i][j]);
        }
        putchar(' ');
    }
    putchar('\n');
}

int main(){
    char** dir;
    char* archivo = "frase.txt";
    dir = buscador(archivo);
    char* arr[3];
    for(int i = 0; i < 3; i++){
        chdir(dir[i]);
        for(int j = 0; j < 3; j++){
            arr[i]=extractor(archivo);
        }
        chdir("..");
        chdir("..");
        chdir("..");
    }
    char** new = sort(arr,3);
    to_string(new,3);
    free(new);
    for(int i = 0; i < 3; i++){
        free(arr[i]);
    }
    return 0;
}