#include "decls.h"
#include "sched.h"
#define MAX_TASK 10

static struct Task Tasks[MAX_TASK];
static struct Task *current;

void sched_init() {
    //La primer tarea debe encontrarse en 'running'
    Tasks[0].status = RUNNING;
    //El resto las pongo como FREE
    for (int i = 1; i < MAX_TASK; i++){
        Tasks[i].status = FREE;
    } 
    //Initialize current
    current = &Tasks[0];

}

void spawn(void (*entry)(void)) {
    //1. Encontrarn el el arreglo global Tasks, una entrada con estado FREE
    struct Task *free_task = NULL;
    for (int i = 1; i < MAX_TASK; i++){
        if(Tasks[i].status == FREE){
            free_task = &Tasks[i];
            break;            
        }
        return;
    } 

    //2. Cambiar su status a READY
    free_task->status = READY;
    if (free_task->status == READY){
        vga_write("Todo bien", 8, 0x70);
    } 
}

void sched(struct TaskFrame *tf) {
    // ...
}
