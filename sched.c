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
    int iFree = findTaskStatus(0, FREE);
    free_task = &Tasks[iFree];

    //2. Cambiar su status a READY
    free_task->status = READY;
    if (free_task->status == READY){
        vga_write("Todo bien", 8, 0x70);
    } 

    
    uint8_t* stackEnd = &(free_task->stack[4096]);

    size_t sizeTaskFrame = sizeof(struct TaskFrame);  
    uint8_t* taskMem = stackEnd - sizeTaskFrame; //Decremento en la memoria el tamaño del struct
    struct TaskFrame* tf = (struct TaskFrame *) (taskMem);
    
    //3. Inicializar todos sus registros a cero, excepto %cs, %eip y %eflags.
    //   En particular %eflags debe contener el flag IF, o las interrupciones de reloj
    //   no se habilitarán al entrar la tarea en ejecución.

    
    free_task->frame = tf;
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
    
    tf->eflags = 0x200; // noveno bit encendido comenzando desde el bit 0
    tf->eip = (uint32_t) entry;
    /*
    Supongo hay que seguir respetando esta aclaración en inerrupts.c
    // Multiboot siempre define "8" como el segmento de código.
    // (Ver campo CS en `info registers` de QEMU.)
    static const uint8_t KSEG_CODE = 8;
    */

    tf->cs = 8;
    
}

int findRR(){
    int iRunning = findTaskStatus( 0, RUNNING );
    int index = findTaskStatus( iRunning, READY );

    return (index == MAX_TASK)? -1 : index;
}


int findTaskStatus(int index, enum TaskStatus status){
    int initialIndex = index;
    while(Tasks[index].status != status && index < MAX_TASK) index++;
    if(initialIndex > 0 && index == MAX_TASK){
        index=0;
        while(Tasks[index].status != status && index < initialIndex) index++;
    }
    return index;
}

void sched(struct TaskFrame *tf) {
    struct Task *new = 0;
    struct Task *old = current;


    vga_write("SCHEDULING......", 8, 0x80);
    int iNext = findRR();
    if ( iNext >= 0 ){
        new = &Tasks[iNext];


        old->status = READY;
        old->frame =tf;

        current = new;
        current->status = RUNNING;

        asm volatile("movl %0, %%esp\n"
        "popa\n"
        "iret\n"
        :
        : "g"(current->frame)
        : "memory");      
    }


    
}
