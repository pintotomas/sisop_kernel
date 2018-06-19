#include "decls.h"

#define COUNTLEN 20
#define TICKS (1ULL << 15)
#define DELAY(x) (TICKS << (x))
#define USTACK_SIZE 4096

static volatile char *const VGABUF = (volatile void *) 0xb8000;

static uintptr_t esp;
static uint8_t stack1[USTACK_SIZE] __attribute__((aligned(4096)));
static uint8_t stack2[USTACK_SIZE] __attribute__((aligned(4096)));


static void yield() {
    if (esp)
        task_swap(&esp);
}

static void contador_yield(unsigned lim, uint8_t linea, char color) {
    char counter[COUNTLEN] = {'0'};  // ASCII digit counter (RTL).

    while (lim--) {
        char *c = &counter[COUNTLEN];
        volatile char *buf = VGABUF + 160 * linea + 2 * (80 - COUNTLEN);

        unsigned p = 0;
        unsigned long long i = 0;

        //while (i++ < DELAY(6))  // Usar un entero menor si va demasiado lento.
            //;

        while (counter[p] == '9') {
            counter[p++] = '0';
        }

        if (!counter[p]++) {
            counter[p] = '1';
        }

        while (c-- > counter) {
            *buf++ = *c;
            *buf++ = color;
        }

        yield();
    }
}


void contador_run() {
    
        // Inicializar al *tope* de cada pila.
    uintptr_t *a = (uintptr_t*) (stack1+USTACK_SIZE);
    uintptr_t *b = (uintptr_t*) (stack2+USTACK_SIZE);
    //uintptr_t *bb = NULL;
    // Actualizar la variable estática ‘esp’ para que apunte
    // al del segundo contador.
      //push %EBX
      //push %EDI
      //push %ESI 
      //push %EDX
    
    /*
    *(--b) = 0x4F;
    bb = b;
    *(--b) = 1;  
    *(--b) = 100;
        *(--b) = 0x000b8118;

        *(--b) = 0x00000000;
        *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = *bb;
    *(--b) = 0x00000064;
    */

//0x10aff0 <stack1+4080>:
    *(--b) = 0x0000004f;
    *(--b) = 0x00000001;
    *(--b) = 0x00000064;
    *(--b) = 0x00100099;    
//0x10afe0 <stack1+4064>:
    *(--b) = 0x00101f90;
    *(--b) = 0x00009500;
    *(--b) = 0x00101f98;
    *(--b) = 0x00101fcc;    
//0x10afd0 <stack1+4048>:
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
//0x10afc0 <stack1+4032>:
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000031;    
//0x10afb0 <stack1+4016>:
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x000b8280;    
//0x10afa0 <stack1+4000>:
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x00000000; 
//0x10af90 <stack1+3984>: 
    *(--b) = 0x00000000;
    *(--b) = 0x00000000;
    *(--b) = 0x0010b000;
    *(--b) = 0x001003e7;
    


//0x10af90 <stack1+3984>:	0x001003e7	0x0010b000	0x00000000	0x00000000
//0x10afa0 <stack1+4000>:	0x00000000	0x00000000	0x00000000	0x00000000
//0x10afb0 <stack1+4016>:	0x000b8078	0x00000000	0x00000000	0x00000000
//0x10afc0 <stack1+4032>:	0x00000031	0x00000000	0x00000000	0x00000000
//0x10afd0 <stack1+4048>:	0x00000000	0x00000000	0x00000000	0x00000000
//0x10afe0 <stack1+4064>:	0x00101fcc	0x00101f98	0x00009500	0x00101f90
//0x10aff0 <stack1+4080>:	0x00100099	0x00000064	0x00000000	0x0000002f
    
    

              esp = (uintptr_t) b;
    
    
    //Ahora estamos en el tope de la pila y se que 'crece hacia arriba'
    //Paso los stacks de manera inversa
    *(--a) = 0x2F; 
    *(--a) = 0;    
    *(--a) = 100; 
    // Lanzar el primer contador con task_exec.
    task_exec((uintptr_t) contador_yield, (uintptr_t) a);

    //contador_yield(100, 0, 0x2F);
    //contador_yield(100, 1, 0x4F);
}
