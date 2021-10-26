#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define N 100

/*****
* void laberintoMaykr
******
* Crea el laberinto de carpeta
******
* Input:
* Sin parametros
******
* Returns:
* Sin retorno
*****/

void laberintoMaykr(){
    char* strings[4] = {"Laberinto","1","2","3"};
    char* s1,*s2,*s3;
    s1 = (char*) malloc(N);
    s2 = (char*) malloc(N);
    s3 = (char*) malloc(N);
    /*Nivel 0*/
    mkdir(strings[0],0700);
    /*Nivel 1*/
    strcpy(s1,strings[0]);
    strcat(s1,"/");
    chdir(s1);
    for(int i = 1; i<4;i++){
        mkdir(strings[i],0700);
    }
    /*Nivel 2*/
    for(int i = 1; i < 4;i++){
        strcpy(s2,strings[i]);
        strcat(s2,"/");
        chdir(s2);
        for(int j = 1; j < 4; j++){
            mkdir(strings[j],0700);
        }
        /*Nivel 3*/
        for(int j = 1;j < 4; j++){
            strcpy(s3,strings[j]);
            strcat(s3,"/");
            chdir(s3);
            for(int k=1;k < 4;k++){
                mkdir(strings[k],0700);
            }
            chdir("..");
        }
        chdir("..");
    }
    free(s1);
    free(s2);
    free(s3);
}

/*****
* int strArrCheck
******
* Sirve para saber si un path esta en la blacklist
******
* Input:
* char** arr : arreglo a revisar
* char* elem : elemento a comprobar si esta en el arreglo
* int size : tamaño del arreglo
******
* Returns:
* int, retorna 1 si el elemento esta en la blacklist y 0 en cualquier otro caso
*****/

int strArrCheck(char** arr, char* elem, int size){
	if (strcmp(arr[0],"")){
		return 0;
	}
	
	for (int i = 0; i<size; i++){
		if (strcmp(arr[i],elem)){
			return 1;
		}
	}
	return 0;
}

/*****
* int randint
******
* Retorna un numero aleatorio entre 0 y max - 1
******
* Input:
* int max : numero maximo a retornar
******
* Returns:
* int, retorna un numero aleatorio entre 0 y max - 1
*****/

int randint(int max){
	return rand() % (max);
}

/*****
* void textfileMaykr
******
* Coloca aleatoriamente un archivo en un directorio de carpeta
******
* Input:
* Sin parametros
******
* Returns:
* Sin retorno
*****/

void textfileMaykr(){
	char* msgs[3] = {"1, Los hurones del","2, profesor de sistemas operativos son","3, grandes ayudantes que dejarian a sus alumnos usar C++ en la tarea 1 y posteriores"};
	char* folds[3] = {"1","2","3"};
	
	char** blacklist;
	blacklist = (char**)malloc(N);
	
	char *path = (char*)malloc(7);
	
	
	for (int i = 0; i < 3; i++){
		
		strcat(path,folds[randint(3)]);
		strcat(path,"/");
		strcat(path,folds[randint(3)]);
		strcat(path,"/");
		strcat(path,folds[randint(3)]);
		strcat(path,"/");
		
		
		
		while (i != 0){
			if(strArrCheck(blacklist, path, N) == 0){
				blacklist[i] = path;
				break;
			} else {
				strcpy(path,"");			
				strcat(path,folds[randint(3)]);
				strcat(path,"/");
				strcat(path,folds[randint(3)]);
				strcat(path,"/");
				strcat(path,folds[randint(3)]);
				strcat(path,"/");
			}
		}
		
		
		chdir(path);
		
		
		FILE * fp = fopen("frase.txt","w");
		fputs(msgs[i],fp);
		fclose(fp);
		
		strcpy(path,"");
		chdir("..");
		chdir("..");
		chdir("..");
	}
	free(path);
	free(blacklist);
}

int main(){
	srand(time(NULL));
	laberintoMaykr();
	textfileMaykr();
	
	return 0;
}