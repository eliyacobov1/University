#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif

#include "Thread.h"

/**
 * Constructor for a Thread object
 * @param tid The id of the thread
 * @param quantum_usecs The pre-defined running
 * time of the Thread (in quantum)
 * @param f The function which represents the initial
 * program counter location of this thread
 */
Thread ::Thread(int tid, int quantum_usecs, void (*f)())
{
    address_t sp, pc;

    sp = (address_t)_stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t)f;
    int ret_val = sigsetjmp(_env, 1);

    if(ret_val != 0)
    {
        return;
    }

    (_env->__jmpbuf)[JB_SP] = translate_address(sp);
    (_env->__jmpbuf)[JB_PC] = translate_address(pc);
    sigemptyset(&_env->__saved_mask);

    _threadID = tid;
    _quantum_usecs = quantum_usecs;
    _totalQuantum = 0;
    _threadState = READY;
}

/**
 * Getter for the Thread's ID
 * @return The thread's ID
 */
int Thread :: getID() const
{
    return _threadID;
}

/**
 * Getter for the end field (sigjmp_buf struct type)
 * @return The thread's current environment
 */
sigjmp_buf& Thread :: getEnvironment()
{
    return _env;
}

/**
 * Getter for the Thread's state
 * @return The thread's state
 */
int Thread :: getState() const
{
    return _threadState;
}

/**
 * Setter for the Thread's state
 */
void Thread :: setState(int state)
{
    _threadState = state;
}

/**
 * Setter for the Thread's quantum
 */
void Thread :: setQuantum(int quantum_usecs)
{
    _quantum_usecs = quantum_usecs;
}

/**
 * Getter for the Thread's current quantum count
 * @return The thread's quantum count
 */
int Thread :: getQuantumCount() const
{
    return _totalQuantum;
}

/**
 * Getter for the Thread's quantum
 * @return The thread's quantum
 */
int Thread :: getQuantum() const
{
    return _quantum_usecs;
}


