.text
.globl task_exec
task_exec:
        push %ebp
        movl %esp, %ebp
        movl 12(%ebp), %esp
        call *8(%ebp)
        movl %ebp, %esp
        leave
        ret

.globl task_swap
task_swap:
//guardar, en el stack de la tarea actual, los registros que son callee-saved
    push %ebp
    push %esi
    push %edi
    push %ebx
//cargar en %esp el stack de la nueva tarea, y guardar en la variable esp el valor previo de %esp
    movl 20(%esp), %eax
    movl %esp, %ecx
    movl (%eax), %esp
    movl %ecx, (%eax)
//restaurar, desde el nuevo stack, los registros que fueron guardados por una llamada previa a task_swap(), y retornar (con la instrucción ret) a la nueva tarea.
    pop %ebx
    pop %edi
    pop %esi
    pop %ebp

    ret
