enum TaskStatus {
    FREE = 0,
    READY = 1,
    RUNNING = 2,
    DYING = 3
};

struct TaskFrame {

    
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    /* below here defined by x86 hardware */
    uint32_t eip;
    uint16_t cs;
    uint16_t padding;
    uint32_t eflags;
    uint32_t kill_fn;

} __attribute__((packed));


struct Task {
    uint8_t stack[4096];
    enum TaskStatus status;
    struct TaskFrame *frame;
};

void sched_init();
