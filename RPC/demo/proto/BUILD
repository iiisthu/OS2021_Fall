package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")



cc_grpc_library(
    name = "hw_grpc",
    srcs = [":hw_proto"],
    grpc_only = True,
    deps = [":hw_cc_proto"],
)
 
cc_proto_library(
    name = "hw_cc_proto",
    deps = [":hw_proto"],
)
 
proto_library(
    name = "hw_proto",
	srcs = ["helloworld.proto"],
)