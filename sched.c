#include "decls.h"
#include "sched.h"

#define MAX_TASK 10

static struct Task Tasks[MAX_TASK];
static struct Task *current;

void sched_init() {
    /*Esta función debe inicializar la variable global current al primer elemento del arreglo global de tareas, 
    y poner su estado en RUNNING.*/
    //Tasks[0].estado = RUNNING; 
}

void spawn(void (*entry)(void)) {
    // ...
}

void sched(struct TaskFrame *tf) {
    // ...
}

