##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_binary(
    name = "q0",
    srcs = [
        "q0.cc",
    ],
    copts = [
        "-std=c++17",
    ],
    data = glob(["data/q0*"]),
    linkopts = ["-pthread"],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:model_lib",
        "//lib:operation_lib",
    ],
)

cc_binary(
    name = "format",
    srcs = [
        "format.cc",
    ],
    copts = [
        "-std=c++17",
    ],
)

cc_binary(
    name = "q1",
    srcs = [
        "q1.cc",
    ],
    copts = [
        "-std=c++17",
    ],
    data = glob(["data/q1*"]),
    linkopts = ["-pthread"],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:operation_lib",
    ],
)

cc_binary(
    name = "q2",
    srcs = [
        "q2.cc",
    ],
    copts = [
        "-std=c++17",
    ],
    data = glob(["data/q2*"]),
    linkopts = ["-pthread"],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:model_lib",
        "//lib:operation_lib",
    ],
)

cc_binary(
    name = "q3",
    srcs = [
        "q3.cc",
    ],
    copts = [
        "-std=c++17",
    ],
    data = glob(["data/q3*"]),
    linkopts = ["-pthread"],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:model_lib",
        "//lib:operation_lib",
    ],
)

cc_binary(
    name = "q4",
    srcs = [
        "q4.cc",
    ],
    copts = [
        "-std=c++17",
    ],
    data = glob(["data/q4*"]),
    linkopts = ["-pthread"],
    deps = [
        "//lib:embedding_lib",
        "//lib:instruction_lib",
        "//lib:model_lib",
        "//lib:operation_lib",
    ],
)

cc_test(
    name = "benchmark",
    size = "small",
    srcs = ["benchmark.cc"],
    copts = [
        "-O3",
        "-std=c++17",
    ],
    data = glob(["data/*"]),
    linkopts = ["-pthread"],
    deps = [
        "@gbench//:benchmark",
    ],
)
