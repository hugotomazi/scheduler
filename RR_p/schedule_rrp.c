
#include "schedulers.h"
#include "list.h"

int contTid = 0;
struct node **lista;

void add(char *name, int priority, int burst) {
    if(contTid == 0) {
        lista = malloc(sizeof(struct node));
    }

    struct task *newTask = malloc(sizeof(struct task)); 

    newTask->name = name;
    newTask->tid = ++contTid;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(lista, newTask);

}

void schedule() {
    
    traverse(*lista);

}