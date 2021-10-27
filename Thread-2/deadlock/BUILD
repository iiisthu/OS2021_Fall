##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_binary(
    name = "main",
    srcs = [
        "main.cc"
            ],
    deps = [
        "//lib:resource_manager_lib",
        "//lib:utils_lib",
        "//lib:workload_lib",
        "//lib:thread_manager_lib"
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-pthread",
    ]
)