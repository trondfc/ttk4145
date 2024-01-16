Exercise 1 - Theory questions
-----------------------------

### Concepts

What is the difference between *concurrency* and *parallelism*?
> Concurrency is running multiple tasks on one single processing unit. This is done by content switching. Concurrency will increase the amount of work finished in a given time, as it swaps between tasks to minimize processor cycles with no task.
Parallelism is when multiple processors share work, and do computations in parallell. This increases the total amount of computational power.

What is the difference between a *race condition* and a *data race*? 
> A data race happens when one thread acceses a shared variable while another thread is writing to it, while a race condition is when the timing or order of events effects the correctnes of the result.
 
*Very* roughly - what does a *scheduler* do, and how does it do it?
> A sceduler assigns different tasks processing time. The tasks are often categorized with priority. The scheduler will pick the task with highest priority. The different threads can yield their cpu-access when programmed cooperative, or the scheduler can force yield the cpu-access when programmed preemptive.


### Engineering

Why would we use multiple threads? What kinds of problems do threads solve?
> using multiple threads solves problems where multiple opperations neads to happen at once, eg. multiple different whaits for events or simular.

Some languages support "fibers" (sometimes called "green threads") or "coroutines"? What are they, and why would we rather use them over threads?
> A fiber is much like a thread. Unlike threads, fibers are cooperative, and yield themselves. Because a fiber yields itself, it does not have the same problem with synchronisation as a thread that is preemptive. This ease of synchronisation is a good reason to use fibers instead of threads.

Does creating concurrent programs make the programmer's life easier? Harder? Maybe both?
> Creating a concurrent program can make the programmer's life both harder and easier harder if the scope of the code is small and/or the events neads to be done sequentially. but makes it easier with bigger scopes and multiple processes/tasks that can happen concurently. 

What do you think is best - *shared variables* or *message passing*?
> Currently message passing seams to be the best (atleast in go) as this makes the setup and syncronisation easyer. 


