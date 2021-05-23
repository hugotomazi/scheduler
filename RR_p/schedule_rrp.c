
#include <stdlib.h>
#include <stdio.h>
#include "schedulers.h"
#include "list.h"
#include "CPU.h"

int contTid = 0;
struct node **filas[5];

void allocTask(Task *task) {
    insertOnEnd(filas[task->priority-1], task);
}

void add(char *name, int priority, int burst) {
    if(contTid == 0) {
        for(int i = 0; i < 5; ++i) {
            struct node **lista = malloc(sizeof(struct node));
            filas[i] = lista;
        }
    }

    struct task *newTask = malloc(sizeof(struct task)); 

    newTask->name = name;
    newTask->tid = ++contTid;
    newTask->priority = priority;
    newTask->burst = burst;
    allocTask(newTask);
}

Task * getNextTask() {
    Task *next = NULL;
    
    for(int i = 4; i >= 0; --i) {
        if(*filas[i] != NULL) {
            next = (*filas[i])->task;
            break;
        }
    }
    return next;
}

void schedule() {
    Task *atual;
    while( (atual = getNextTask()) ) {
        run(atual, QUANTUM);
        atual->burst -= QUANTUM;

        if(atual->burst <= 0) {
            delete(filas[atual->priority - 1], atual);
            continue;
        }

        allocTask(atual);
        delete(filas[atual->priority-1], atual);
    }
}