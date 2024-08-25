#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void createfile() {
    FILE *fp;
    char command[256];
    char file_path[256];
    
    snprintf(command, sizeof(command), "zenity --file-selection --save --confirm-overwrite --filename=novo_arquivo.txt");
    FILE *fp_zenity = popen(command, "r");
    if (fp_zenity == NULL) {
        perror("popen");
        return;
    }

    if (fgets(file_path, sizeof(file_path), fp_zenity) != NULL) {
        file_path[strcspn(file_path, "\n")] = 0;
    } else {
        printf("Nenhum arquivo selecionado.\n");
        pclose(fp_zenity);
        return;
    }
    pclose(fp_zenity);

    fp = fopen(file_path, "w");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    fclose(fp);

}

void openfile() {
    char command[256];
    char file_path[256];
    FILE *fp_zenity;
    FILE *fp;
    long file_size;
    unsigned char *buffer;

    snprintf(command, sizeof(command), "zenity --file-selection --title=\"Selecionar um arquivo\"");
    fp_zenity = popen(command, "r");
    if (fp_zenity == NULL) {
        perror("popen");
        return;
    }

    if (fgets(file_path, sizeof(file_path), fp_zenity) != NULL) {
        file_path[strcspn(file_path, "\n")] = 0;
    } else {
        printf("Nenhum arquivo selecionado.\n");
        pclose(fp_zenity);
        return;
    }
    pclose(fp_zenity);

    fp = fopen(file_path, "rb");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL) {
        perror("malloc");
        fclose(fp);
        return;
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);
    
    buffer[file_size] = '\0';

    printf("Conteúdo do arquivo (%ld bytes):\n%s\n", file_size, buffer);

    free(buffer);
}

