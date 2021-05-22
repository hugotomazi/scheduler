
#include <stdlib.h>
#include <stdio.h>
#include "schedulers.h"
#include "list.h"
#include "CPU.h"

int contTid = 0;
struct node **filas[5];

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
    insertOnEnd(filas[newTask->priority - 1], newTask);
}

void schedule() {
    for(int i = 4; i >= 0; --i) {
        //traverse(*filas[i]);
        struct node *atual = *filas[i];
        while(atual != NULL) {
            run(atual->task, QUANTUM);
            atual->task->burst -= QUANTUM;
            if(atual->task->burst <= 0) {
                delete(filas[i], atual->task);
            } else {
                insertOnEnd(filas[i], atual->task);
                delete(filas[i], atual->task);
            }
            atual = atual->next;
        }
    }
}