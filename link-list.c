#include "a2.h"

FDtable* new_FD_node()
{
    FDtable *new_node=NULL;
    new_node = (FDtable *)calloc(1, sizeof(FDtable));
    new_node->PID = 0;
    new_node->FD = 0;
    strcpy(new_node ->Filename, "");
    new_node->Inode = 0;
    new_node -> next = NULL;
    return(new_node);    
}

FDtable* insert(FDtable *head, int pid, int fd, char filename[MAX_STR_LEN], int inode){
    FDtable *table = new_FD_node();
    table->PID = pid;
    table->FD = fd;
    strcpy(table->Filename, filename);
    table->Inode = inode;
    if(head == NULL)
    {
        head = table;
    }
    else
    {
        FDtable *cur = head;
        while(cur->next != NULL)
        {
        cur = cur->next;
        }
        cur->next = table;
    }
  return head;
}

FDtable *find_pid(){
    FDtable *head1 = NULL;
    uid_t my_uid = getuid(); 
    uid_t other_uid; 

    DIR* dir = opendir("/proc");
    if (dir == NULL) {
        return NULL;
    }
    
    struct dirent* p;
    char file_path[MAX_STR_LEN];
    while ((p = readdir(dir)) != NULL) {
        if (p->d_type == DT_DIR) {
            sprintf(file_path, "/proc/%s/status", p->d_name);

            FILE* f = fopen(file_path, "r");
            if (f == NULL) {
                continue;
            }
            char line[MAX_STR_LEN];
            while (fgets(line, sizeof(line), f) != NULL) {
                if (strncmp(line, "Uid:", 4) == 0) {
                    other_uid = atoi(line+ 5);
                    break;
                }
            }
            fclose(f);
            if(my_uid == other_uid){
                int pid = atoi(p->d_name);
                char path[MAX_STR_LEN];
                snprintf(path, sizeof(path), "/proc/%d/fd", pid);
                
                struct dirent* q;
                DIR *fd_dir = opendir(path);
                if (fd_dir == NULL) {
                    continue;
                }
                
                 while ((q = readdir(fd_dir)) != NULL) {
                    snprintf(path, sizeof(path), "/proc/%d/fd/%s", pid, q->d_name);
                    int fd = atoi(q->d_name);
                    long int Inode = 0;
                    struct stat st;
                    if (stat(path, &st) == 0) {
                        ino_t inode = st.st_ino;
                        Inode = inode;
                    }

                    char filename[MAX_STR_LEN];
                    ssize_t len = readlink(path, filename, sizeof(filename)-1);
                    if (len == -1) {
                        continue;
                    }
                    filename[len] = '\0';
                    head1 = insert(head1, pid, fd, filename, Inode);
                }

                closedir(fd_dir);
            }
        }
    }
    closedir(dir);
    return head1;
}

FDtable* delete_list(FDtable *head){
    FDtable *p = NULL;
    FDtable *q = NULL;
    p = head;

    while(p != NULL)
    {
        q = p -> next;
        free(p);
        p = q;
    }
    return p;
}