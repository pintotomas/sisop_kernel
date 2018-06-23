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

    //3. Inicializar todos sus registros a cero, excepto %cs, %eip y %eflags.
    //   En particular %eflags debe contener el flag IF, o las interrupciones de reloj
    //   no se habilitarán al entrar la tarea en ejecución.

    struct TaskFrame *tf = free_task->frame;
    tf->edi = 0;
    tf->esi = 0;
    tf->ebp = 0;
    tf->esp = 0;
    tf->ebx = 0;
    tf->edx = 0;
    tf->ecx = 0;
    tf->eax = 0;
    tf->padding = 0;
    //Quedan por inicializar cs,eip,eflags, y la stack dentro de free_task?
    /*
    tf->cs = ;
    tf->eip = ;
    tf->eflags = ;
    */
}

void sched(struct TaskFrame *tf) {
    // ...
}
