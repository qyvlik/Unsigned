import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    files: [
        "main.cpp",
        "unsigned.cpp",
        "unsigned.h",
        "unsigned_algorithm.cpp",
        "unsigned_algorithm.h",
    ]
    cpp.cxxFlags: "-std=c++11"
    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

