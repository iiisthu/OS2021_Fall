# Deadlock Prevention

Real-world computation tasks usually require different resources to run, e.g.
GPUs, disk spaces for caching dataset. When multiple workloads come with different
resource requirements, deadlocks may happen and thus makes no progress.
In this experiment, you should simulate a deadlock situation and either prevent it or detect and recover from it. 

## Codebase Introduction

We consider four types of resources: GPU, Network, Memory, Disk.
We provide a simple thread-safe implementation of a resource manager
`lib/resource_manager.h`, which holds a certain number of instances of each resource type. The resource manager assigns the resources to each user task (a thread). 
A user task, before/after any resource use, should call the resource manager 
with the `request` and `release` methods to register.  
 
Other than the resource requests that might cause a deadlock, 
these tasks are independent, and you do not need to consider other synchronization among these tasks.  
(Of course, the resource manager itself should be thread-safe). 

In `lib/workload.h`,  we provide an example workload with two resources.  Each
user task requests two types of resources and uses them for an extended time period. 
For each resource type, it will request all the amount it claims.
Note that the requested order of the resources and the calculation time can be random.
Inspect the code for details. In this experiment, you should not modify the
`workload` function (e.g., add a line to release all resources right after
requesting them).

## TODO

Given the initial number of instances of each resource type and the definition of each user task, 
your job is to run these
tasks concurrently without deadlocks. 
Each user task is defined as a sequence of the operations (i.e., workload
arguments, see `main.cc` as an example), 

The order of different tasks are
arbitrary -- you can start them simultaneously or sequentially, as long as they are thread-safe. 

You may prevent the deadlock from happening or recover from
deadlocked threads. 

If you use a prevention method, in cases where two tasks cannot run concurrently, 
the resource manager should deny 
requests to a task, and the task that does not get the resource should wait until it gets
the requested resource.  

If you use a detection-and-recover scheme, the resource manager should detect deadlocks and recover by killing a thread.  You can assume that all the threads are recoverable, 
as long as you correctly reclaim all resources managed by the resource manager. 

Your method should maximize the concurrency level to shorten the overall execution time and increase system utilization.  That is, you should do your best to allow
all possible concurrently executable threads to run concurrently. 

You do not need to consider failure cases (i.e., a task fails in the middle because of user logic errors). 
I.e., you can safely assume that all tasks, if not deadlocked, will finish correctly and return the resource
to the resource manager. 

## Grading

We will use a mixture of user tasks to test your scheduler for the following two requirements:
1) Correctness: all the tasks should eventually finish without deadlocks;
2) Performance: we will consider the time it takes for all the tasks. It should be significantly faster than running all tasks sequentially - and quite close to the theoretically best performance (i.e., an offline schedule that knows all the task behaviors previously and carefully schedule them so that no deadlock can happen).  
