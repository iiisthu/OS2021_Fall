# Remote Memory Management Service

In this project, you will upgrade your memory manager from Project 3 and turn it into an in-memory storage server.   The server allows multiple clients to access it using RPC.  Specifically, we will use **grpc**, an open-source RPC system developed by Google. 

The project's main goal is to let you get some hands-on experience on RPC.  You will learn how the framework works in general and similarities/differences from local procedure calls. 

The server you develop will allow clients to create a "remote ArrayList", and use it using the same function calls as the local array in your project 3. 

Your RPC client can allocate, access, and release memory from applications as requests to the server (i.e., manage `ArrayList` like `mma` in project 3); Moreover, there should be an RPC server holding the `mma` to receive and process these requests. 

gRPC (gRPC Remote Procedure Calls), also known as Google Remote Procedure Call, is an open-source remote procedure call (RPC) system initially developed at Google. You can find a basic tutorial of grpc at 

https://grpc.io/docs/languages/cpp/quickstart/ . 

You can also download source codes from 
https://github.com/grpc/grpc 
for more details about grpc. 

In this project, we will build and utilize grpc source codes by Bazel.  We have already added the necessary dependencies in your WORKSPACE file.  You do not need to change them.  Note that it might take a while to download all these dependencies the first time you build the project, but subsequent builds will be fast. 

We can define a gRPC service (and its message structure) in a `.proto` file and automatically generate client and server codes. We use the proto3 version of the protocol buffers language in this project. You can find out more about protobuf at 

https://developers.google.com/protocol-buffers/docs/proto3 

and learn how to generate codes from a `.proto` file in 

https://developers.google.com/protocol-buffers/docs/reference/cpp-generated 

In this project, you do not have to manually generate and compile the protobuf's, as the Bazel rules will build them for you.  We have provided a  HelloWorld demo in the `demo` folder to help you understand the Bazel `BUILD` rules for a protobuf application.

## Codebase Introduction

The basic workload in this project is similar to the ones in project 3. The only difference is that the application `Allocate` and `Free` an `ArrayList` via your gRPC client instead of the `mma` directly. Similarly, an `ArrayList` should `read` / `write` its corresponding memory via the client. On the other hand, each test will set up a gRPC server initially listening to the local port 50051. This server will create a `mma` instance in its lifetime to manage local memory space. Your gRPC server should support two basic management interfaces: `RunServerUL` for server setup and `ShutdownServer` to close the server. We provide a basic skeleton of client/server in `mma_client.h` and `mma_server.h`. You can find more interfaces utilization examples in `mma_test.cc`.


## TODO

## Q1

The first four tests in `mma_test.cc` are the same as in Project 3. Implement your gRPC client/server to pass these four tests. The page replacement algorithm should be the clock algorithm. First, you can copy your `mma` codes from project 3 to the `lib/`folder. Adjust some interfaces in your original implementation to adapt the `MemoryManager` and `ArrayList` implementation to RPC. To generate gRPC client/server codes, you should define your memory management service in `proto/mma.proto`. Your implementation should be thread-safe and support concurrency.  

## Q2

When the virtual memory space in use is far larger than the physical memory space of `mma`, thrashing happens and hurts system performance. To avoid thrashing, the memory management service should limit the virtual memory size and reject new incoming `Allocate` requests when existing virtual memory usage reaches the limits. Correspondingly, the client should wait and retry if its `Allocate` request fails until the required memory segment has been registered in the server. Implement this optimization and support an additional management interface: `RunServerL` for server setup with a given threshold of maximum virtual memory size. Pass the fifth test and observe its differences with `task4`.



## Grading

We will use extra workloads to test your codes, so your implementation should not rely on `mma_test.cc`. We grade with the following three requirements:

1. Correctness: pass all tests in  `mma_test.cc` and extra tests;
2. Performance: we will consider the time it takes to pass the tests. Your implementation should not be order-wisely slower than our basic benchmark.  

We should apply your diff file to commit `fc85448` directly; otherwise, the TAs will not grade it. 
