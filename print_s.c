#include "a2.h"

void print_threshold(FDtable *head, int input){
    FDtable* curr = head;
    while (curr != NULL) {
        int count = 1;
        while (curr->next != NULL && curr->PID == curr->next->PID) {
            count++;
            curr = curr->next;
        }
        if(count > input){
            printf("%d(%d) ", curr->PID, count);
        }
        curr = curr->next;
    }
    printf("\n");
}

void print_composite(FDtable *head, int pid, int num){
    int i = 0;
    FDtable *cur = head;
    printf("            PID   FD     Filename                Inode\n");
    printf("           ============================================\n");
    
    if(num == 1){
        while(cur != NULL){
            if(cur->PID == pid){
                printf("%-8d%-8d%-8d%-24s%ld\n", i, cur->PID, cur->FD, cur->Filename, cur->Inode);
            }
            cur= cur->next;
            i++;
        }
    }
    else{
            while(cur != NULL){
            printf("%-8d%-8d%-8d%-24s%ld\n", i, cur->PID, cur->FD, cur->Filename, cur->Inode);
            cur= cur->next;
            i++;
        }
    }
}

void print_per_process(FDtable *head, int pid, int num){
    int i = 0;
    FDtable *cur = head;
    printf("            PID   FD\n");
    printf("           ==========\n");    
    
    if(num == 1){
        while(cur != NULL){
            if(cur->PID == pid){
                printf("%-8d%-8d%-8d\n", i, cur->PID, cur->FD);
            }
            cur= cur->next;
            i++;
        }
    }
    else{
            while(cur != NULL){
            printf("%-8d%-8d%-8d\n", i, cur->PID, cur->FD);
            cur= cur->next;
            i++;
        }
    }
}

void print_systemWide(FDtable *head, int pid, int num){
   int i = 0;
    FDtable *cur = head;
    printf("            PID   FD     Filename\n");
    printf("           ================================\n");
    
    if(num == 1){
        while(cur != NULL){
            if(cur->PID == pid){
                printf("%-8d%-8d%-8d%-24s\n", i, cur->PID, cur->FD, cur->Filename);
            }
            cur= cur->next;
            i++;
        }
    }
    else{
            while(cur != NULL){
            printf("%-8d%-8d%-8d%-24s\n", i, cur->PID, cur->FD, cur->Filename);
            cur= cur->next;
            i++;
        }
    }      

}

void print_Vnodes(FDtable *head , int pid, int num){
    int i = 0;
    FDtable *cur = head;
    printf("            Inode\n");
    printf("           ========\n");
    
    if(num == 1){
        while(cur != NULL){
            if(cur->PID == pid){
                printf("%-8d %ld\n", i, cur->Inode);
            }
            cur= cur->next;
            i++;
        }
    }
    else{
            while(cur != NULL){
            printf("%-8d %ld\n", i, cur->Inode);
            cur= cur->next;
            i++;
        }
    } 
}

void text_file(FDtable *head, int pid, int num){
    int i = 0;
    FDtable *cur = head;
    char filename[MAX_STR_LEN];
    sprintf(filename, "compositeTable.txt");
    FILE *f = fopen(filename, "w");
    fprintf(f, "%s", "            PID   FD     Filename                Inode\n");
    fprintf(f, "%s","           ============================================\n");
    if(num == 1){
        while(cur != NULL){
            if(cur->PID == pid){
                fprintf(f,"%d          %d   %d     %s                   %ld\n", i, cur->PID, cur->FD, cur->Filename, cur->Inode);
            }
            cur= cur->next;
            i++;
        }
    }
    else{
            while(cur != NULL){
            fprintf(f,"%d          %d   %d     %s                   %ld\n", i, cur->PID, cur->FD, cur->Filename, cur->Inode);
            cur= cur->next;
            i++;
        }
    }
    fclose(f);
}

void bin_file(FDtable *head, int pid, int num){
    int i = 0;
    FDtable *cur = head;
    char filename[MAX_STR_LEN];
    sprintf(filename, "compositeTable.bin");
    FILE *f = fopen(filename, "wb");

    const char *header1 = "            PID   FD     Filename                Inode\n";
    const char *header2 = "           ============================================\n";
    fwrite(header1, sizeof(char), strlen(header1), f);
    fwrite(header2, sizeof(char), strlen(header2), f);
    
    if(num == 1) {
        while(cur != NULL){
            if(cur->PID == pid) {
                fwrite(&i, sizeof(int), 1, f);
                fwrite(&(cur->PID), sizeof(int), 1, f);
                fwrite(&(cur->FD), sizeof(int), 1, f);
                fwrite(cur->Filename, sizeof(char), strlen(cur->Filename) + 1, f);
                fwrite(&(cur->Inode), sizeof(long), 1, f);
            }
            cur = cur->next;
            i++;
        }
    }
    else {
        while(cur != NULL){
            fwrite(&i, sizeof(int), 1, f);
            fwrite(&(cur->PID), sizeof(int), 1, f);
            fwrite(&(cur->FD), sizeof(int), 1, f);
            fwrite(cur->Filename, sizeof(char), strlen(cur->Filename) + 1, f);
            fwrite(&(cur->Inode), sizeof(long), 1, f);
            cur = cur->next;
            i++;
        }
    }
    
    fclose(f);
}