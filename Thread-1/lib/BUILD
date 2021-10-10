##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_library(
    name = "utils_lib",
    srcs = [
        "utils.cc",
    ],
    hdrs = [
        "utils.h",
    ],
    copts = [
        "-std=c++17",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "utils_lib_test",
    size = "small",
    srcs = ["util_test.cc"],
    copts = [
        "-std=c++17",
    ],
    deps = [
        ":utils_lib",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "embedding_lib",
    srcs = [
        "embedding.cc",
    ],
    hdrs = [
        "embedding.h",
    ],
    copts = [
        "-std=c++17",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":utils_lib",
    ],
)

cc_test(
    name = "embedding_lib_test",
    size = "small",
    srcs = ["embedding_test.cc"],
    copts = [
        "-std=c++17",
    ],
    deps = [
        ":embedding_lib",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "instruction_lib",
    srcs = [
        "instruction.cc",
    ],
    hdrs = [
        "instruction.h",
    ],
    copts = [
        "-std=c++17",
    ],
    visibility = [
        "//visibility:public",
    ],
)

cc_test(
    name = "instruction_lib_test",
    size = "small",
    srcs = ["instruction_test.cc"],
    copts = [
        "-std=c++17",
    ],
    deps = [
        ":instruction_lib",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "model_lib",
    srcs = [
        "model.cc",
    ],
    hdrs = [
        "model.h",
    ],
    copts = [
        "-std=c++17",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":embedding_lib",
        ":utils_lib",
    ],
)

cc_test(
    name = "model_lib_test",
    size = "large",
    srcs = ["model_test.cc"],
    copts = [
        "-std=c++17",
    ],
    deps = [
        ":model_lib",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "operation_lib",
    srcs = [
        "operation.cc",
    ],
    hdrs = [
        "operation.h",
    ],
    copts = [
        "-std=c++17",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":embedding_lib",
        ":instruction_lib",
        ":model_lib",
        ":utils_lib",
    ],
)
