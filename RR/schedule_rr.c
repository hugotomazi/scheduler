
#include <stdlib.h>
#include <stdio.h>

#include "schedulers.h"
#include "list.h"
#include "CPU.h"

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
    insertOnEnd(lista, newTask);
}

void schedule() {
    struct node *atual = *lista;

    while(atual != NULL) {
        run(atual->task, QUANTUM);
        atual->task->burst -= QUANTUM;
        if(atual->task->burst <= 0) {
            delete(lista, atual->task);
        } else {
            insertOnEnd(lista, atual->task);
            delete(lista, atual->task);
        }
        atual = atual->next;
    }
}