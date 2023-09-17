#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h> 
#include<pwd.h>
#include<errno.h>
#include<dirent.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

#define MAX_STR_LEN 1024            // maximum string length

#ifndef __A2_header
#define __A2_header

typedef struct fdTable_struct
{
    int PID;    // PID
    int FD;     // FD
    char Filename[MAX_STR_LEN]; // Filename
    long Inode; // Inode
    struct fdTable_struct *next; // pointer to the next node
    
} FDtable;

/*Creates a new node for the link list and returns the new node 'new_node'*/
FDtable* new_FD_node();

/*Inserts the new_node 'new_node' created by the given arguments inserts at the tail of the linked list*/
FDtable* insert(FDtable *head, int pid, int fd, char filename[MAX_STR_LEN], int inode);

/*Creates a whole linked list according to the information from /proc directory*/
FDtable *find_pid();

/*Dletes the FDtable linked list*/
FDtable* delete_list(FDtable *head);

/*Prints the FD table that has more number of FDs than given input*/
void print_threshold(FDtable *head, int input);

/*Print the FD table as composite i.e. prints PID, FD, Filename, Inode*/
void print_composite(FDtable *head, int pid, int num);

/*Prints the FD table according to the process PID number. 
It prints PID, FD, Filenodes, Inodes according to given pid*/
void print_per_process(FDtable *head, int pid, int num);

/*Prints the FD table as system wide i.e. PID, FD, Filename*/
void print_systemWide(FDtable *head, int pid, int num);

/*Prints the FD table that includes only PID, Inode*/
void print_Vnodes(FDtable *head , int pid, int num);

/*Saves the FD table in composite formst into a .txt file i.e. text file*/
void text_file(FDtable *head, int pid, int num);

/*Saves the FD table in composite format into a .bin file i.e. binary file*/
void bin_file(FDtable *head, int pid, int num);

#endif
