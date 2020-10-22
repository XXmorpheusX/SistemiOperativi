#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void readRecursive(char *path, char *nome);
char *createPath(char * path, char *nome);
int isRegFile(const char *path);

int main(int argc, char *argv[]){

    DIR           *dp;
    struct dirent *dirp;
    char *path;

    if( argc != 2 )
        exit(1);

    if((dp = opendir(argv[1])) == NULL)
        exit(2);

    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name, "..")==0)continue;
        printf("|> %s::%s\n", argv[1], dirp->d_name);
        readRecursive(argv[1], dirp->d_name);
    }

    closedir(dp);
    exit(0);
}

/*
* Crea il nuovo path: createpath(path, nome)
* Termina se è un file, continua se è un direttorio: if(isRegFile(newPath))return;
* cicla sui sottodirettori, stampa cartella scoperta e ricorre
* ritorno a fine ciclo
*/
void readRecursive(char *path, char *nome){
    DIR           *dp;
    struct dirent *dirp;
    char          *newPath;

    newPath = createPath(path, nome);
    if(isRegFile(newPath))return;
    newPath = createPath(newPath, "/");

    if((dp = opendir(newPath)) == NULL){
        fprintf(stderr, "Nome non riesce ad essere aperto.\n");
        exit(2);
    }

    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name, "..")==0)continue;
        printf("|> [%s]-> %s\n", newPath, dirp->d_name);
        readRecursive(newPath, dirp->d_name);
    }

    return;
}

/*
* Concateno <path> con <nome>
* ritorno: "%s%s", "<path><nome>"
*/
char *createPath(char *path, char *nome){
    char *res;
    
    res = calloc(strlen(path)+strlen(nome)+1, sizeof(char));
    sprintf(res, "%s%s", path, nome);
    return res;
}

/*
* Controllo se è un file normale o un direttorio
* ritorno: 1->file, 0->direttorio
*/
int isRegFile(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
