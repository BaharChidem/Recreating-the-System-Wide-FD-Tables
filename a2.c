#include <stdio.h>
#include <stdlib.h>
#include "a2.h"

int main(int argc, char *argv[]) {
    FDtable *head = find_pid();
    int threshold = 0;
    int number = 0;
    int num = 0;
    int per_process = 0;
    int systemWide = 0;
    int vnodes = 0;
    int composite = 0;
    int input = 0;
    int txt = 0;
    int bin = 0;

    for(int i=0; i<argc; i++){
        if(strcmp(argv[i], "--per-process") == 0){
            per_process = 1;
        }
        else if(strcmp(argv[i], "--systemWide") == 0){
            systemWide = 1;
        }
         else if(strcmp(argv[i], "--Vnodes") == 0){
            vnodes = 1;
        }
         else if(strcmp(argv[i], "--composite") == 0){
            composite = 1;
         
        }
         else if(sscanf(argv[i], "--threshold=%d",&input) == 1){
            threshold = 1;
        }
        else if(atoi(argv[i]) != 0){
            number = atoi(argv[i]);
            num = 1;
        }
        else if(strcmp(argv[i], "--output_TXT") == 0){
            txt = 1;
        }
        else if(strcmp(argv[i], "--output_binary") == 0){
            bin = 1;
            
        }
        
    }

    if(argc == 1){ 
        print_composite(head, number, num);
    }
    if(per_process == 1){
        print_per_process(head, number, num);
    }
    if(systemWide == 1){
        print_systemWide(head, number, num);
    }
    if(vnodes == 1){
        print_Vnodes(head, number, num);
    }
    if(composite == 1){
        print_composite(head, number, num);
    }
    if(threshold == 1){
        if(composite == 0){
            print_composite(head, number, num);
        }
        print_threshold(head, input);
    }
    if(txt == 1){
        text_file(head, number, num);
    }
    if(bin == 1){
        bin_file(head, number, num);
    }
    delete_list(head);
    return 0;
}