##load("@rules_cc//cc:defs.bzl", "cc_test")  #load the test target

cc_library(
    name = "utils_lib",
    srcs = [
        "utils.cc",
        ],
    hdrs = [
        "utils.h",
        ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "utils_lib_test",
  size = "small",
  srcs = ["util_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":utils_lib",
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
	deps = [
        ":utils_lib"
    ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "embedding_lib_test",
  size = "small",
  srcs = ["embedding_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":embedding_lib",
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
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "instruction_lib_test",
  size = "small",
  srcs = ["instruction_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":instruction_lib",
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
	deps = [
        ":embedding_lib",
		":utils_lib",
    ],
	visibility = [
		"//visibility:public",
	],
)

cc_test(
  name = "model_lib_test",
  size = "large",
  srcs = ["model_test.cc"],
  deps = [
      "@gtest//:gtest_main",
	  ":model_lib",
      ],
)