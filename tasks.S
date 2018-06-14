.text
.globl task_exec
task_exec:
        push %ebp
        movl %esp, %ebp
        movl 8(%ebp), %esp
        call *12(%ebp)
        movl %ebp, %esp
        leave
        ret
