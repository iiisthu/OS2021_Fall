# Deadlock Prevention

Real-world computation tasks usually requires different resources to run, e.g.
GPUs, disk spaces for caching dataset. When multiple workloads comes with different
resource requirements, deadlocks may happen and no progress will be made.
In this experiment, you should try to prevent deadlocks or detect and resolve them.

## Codebase Introduction

We consider four types of resources: GPU, Network, Memory, Disk.
We provide a simple thread-safe implementation of a resource manager
`lib/resource_manager.h`, which holds a certain amount of resources for
workloads. We can access the resources with the `request` and `release` method.
However, you should not manipulate the resource outside the `workload` function
to solve this problem.

In `lib/workload.h` we define the workloads used in this experiment. For each
workload, it will request two types of resources for some time-consuming
calculation. For each resource type, it will request all the amount it claims.
Note that the request order of the resources and the calculation time can be random.
Inspect the code for details. In this experiment, you should not modify the
`workload` function (e.g. add a line to release all resources right after
requesting them) to bypass the deadlock problem.

## TODO

Given the initial amount of resources and the instructions (i.e. workload
arguments, see `main.cc` for example usage), your job is to run these
instructions in parallel without deadlocks. The order of the instructions can be
arbitrary -- you can start them simultaneously or sequentially, as long as they
are thread safe. You may prevent the deadlock from happening or recover from
deadlocked threads. In some cases where two instructions cannot run in parallel,
you can run them sequentially. However, in general cases, you should make full
use of multi-threading. You will get penalized if all instructions are executed
sequentially even when it is apparently parallelizable (e.g. two instructions
without any overlap on resource requests). We guarantee that all the
instructions can finish when executed sequentially.

## Grading

We will time the total execution time of your program under
different input instructions.
