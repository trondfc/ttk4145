Exercise 1 - Theory questions
-----------------------------

### Concepts

What is the difference between *concurrency* and *parallelism*?
> Concurrency is running multiple tasks on one single processing unit. This is done by content switching. Concurrency will increase the amount of work finished in a given time, as it swaps between tasks to minimize processor cycles with no task.
Parallelism is when multiple processors share work, and do computations in parallell. This increases the total amount of computational power.

What is the difference between a *race condition* and a *data race*? 
> *Your answer here* 
 
*Very* roughly - what does a *scheduler* do, and how does it do it?
> A sceduler assigns different tasks processing time. The tasks are often categorized with priority. The scheduler will pick the task with highest priority. The different threads can yield their cpu-access when programmed cooperative, or the scheduler can force yield the cpu-access when programmed preemptive. 


### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?
> *Your answer here*

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?
> A fiber is much like a thread. Unlike threads, fibers are cooperative, and yield themselves. Because a fiber yields itself, it does not have the same problem with synchronisation as a thread that is preemptive. This ease of synchronisation is a good reason to use fibers instead of threads.

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?
> *Your answer here*

What do you think is best - *shared variables* or *message passing*?
> *Your answer here*


