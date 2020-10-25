#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void readRecursive(char *path);
char *createPath(char * path, char *nome);
int isDir(const char *path);

/**
 * Main: controllo parametri passati come argomento
 * Ricorsione
 * Chiusura e ritorno
*/
int main(int argc, char *argv[]){
    DIR           *dp;

    if( argc != 2 )
        exit(1);

    if((dp = opendir(argv[1])) == NULL)
        exit(2);

    readRecursive(argv[1]);

    closedir(dp);
    exit(0);
}

/**
 * Apertura direttorio -> dp
 * Lettura ciclica -> dirp:
 *  se . o .. continua
 *  stampa path/dirp->d_name
 *  se non file ordinario -> ricorri
 */
void readRecursive(char *path){
    DIR           *dp;
    struct dirent *dirp;
    char          *newPath;

    if((dp = opendir(path)) == NULL){
        fprintf(stderr, "Nome non riesce ad essere aperto.\n");
        exit(2);
    }

    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name, "..")==0)continue;
        printf("|> [%s]-> %s\n", path, dirp->d_name);
        if(isDir(newPath = createPath(path, dirp->d_name))){
            readRecursive(newPath);
        }
    }

    closedir(dp);

    return;
}

/*
* Concateno <path> con <nome>
* ritorno: "%s/%s", "<path>/<nome>"
*/
char *createPath(char *path, char *nome){
    char *res;
    
    res = calloc(strlen(path)+1+strlen(nome)+1, sizeof(char));
    sprintf(res, "%s/%s", path, nome);
    return res;
}

/*
* Controllo se è un file normale o un direttorio
* ritorno: 1->direttorio, 0->file
*/
int isDir(const char *path){
    struct stat path_stat;
    lstat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}
