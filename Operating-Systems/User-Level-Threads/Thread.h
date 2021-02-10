#ifndef EX2_THREAD_H
#define EX2_THREAD_H
#include <csignal>
#include <setjmp.h>

#define SECOND 1000000
#define STACK_SIZE 4096

#define RUNNING 0
#define READY 1
#define BLOCKED -1

#define SYS_CALL_ERROR 1

class Thread {
public:
    /**
     * Constructor for a Thread object
     */
    Thread(int tid, int quantum_usecs, void (*f)()= nullptr);

    /**
     * Getter for the Thread's ID
     */
    int getID () const;

    /**
     * Getter for the end field (sigjmp_buf struct type)
     */
    sigjmp_buf& getEnvironment();

    /**
     * Increase the Thread's total quantum by 1
     */
    inline void increaseQuantum()
    {
        _totalQuantum++;
    }

    /**
     * Getter for the Thread's state
     */
    int getState() const;

    /**
     * Getter for the Thread's quantum
     * @return The thread's quantum
     */
    int getQuantum() const;

    /**
     * Setter for the Thread's state
     */
    void setState(int state);

    /**
     * Setter for the Thread's quantum
     */
    void setQuantum(int quantum_usecs);

    /**
     * Getter for the Thread's current quantum count
     * @return The thread's quantum count
     */
    int getQuantumCount() const;

private:
    /** the thread's id */
    int _threadID;

    /** the thread's current state (ready, running or blocked) */
    int _threadState;

    /**
     * the thread's pre defined time to stay at running
     * state (defined according to it's priority)
     */
    int _quantum_usecs;

    /** total time (in quantum) */
    int _totalQuantum;

    /** the thread's environment */
    sigjmp_buf _env;

    /** the thread's stack */
    char _stack[STACK_SIZE];
};


#endif //EX2_THREAD_H
