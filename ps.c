#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <dirent.h>
#include "stat.h"

#define PROC_PATH "/proc/"
#define BUFF_LINE 128
#define PRINT(p_id, p_name) printf("%s \t %s \n", p_id, p_name)

//remove ()
void smarten(char str[]) {

	memmove(str, str + 1, strlen(str));
	str[strlen(str) - 1] = '\0';

}


int get_status(char path[BUFF_LINE]){

    Stat *stat = malloc(sizeof(Stat ));

    sprintf(path, "%s%s", path, "/stat");

    int fd;
    char buff[BUFF_LINE] ="";

    fd = open(path,O_RDONLY);

    if(fd == -1){
        fprintf(stderr, "error while opening the file \n");
        return -1;
    }

    read(fd,buff,BUFF_LINE);
    sscanf(buff,"%s %s %*s",stat->proc_id, stat->proc_name );

    smarten(stat->proc_name);
    PRINT(stat->proc_id,stat->proc_name);
    
    close(fd);
    free(stat);
}

int get_pid(){
    char full_path[BUFF_LINE]="";
    
    DIR *dir;
    struct dirent *dirent;

    dir = opendir(PROC_PATH);

    if(dir == NULL){
        printf("error while open dir \n");
        return -1;
    }

    while((dirent = readdir(dir)) != NULL){
        if(atoi(dirent->d_name) != 0){
            memset(full_path,0,BUFF_LINE);

            sprintf(full_path, "%s%s", PROC_PATH, dirent->d_name);
            get_status(full_path);    
        }
        
    }
     closedir(dir);
     
     return 0;
}

int main(void){
    printf("PID \t NAME\n");
    get_pid();

    return 0;
}
