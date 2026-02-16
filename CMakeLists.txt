cmake_minimum_required(VERSION 3.15)
project(learning-cxx CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# 设置编码
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")

# 获取项目根目录
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# 定义 __XMAKE__ 宏（兼容 xmake 定义）
string(REPLACE "\\" "/" XMAKE_ROOT ${PROJECT_ROOT})
add_compile_definitions(__XMAKE__="${XMAKE_ROOT}")

# ============================================
# 创建 test 静态库
# ============================================
add_library(test STATIC
    learn/test.cpp
)

target_include_directories(test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ============================================
# 创建 learn 可执行文件
# ============================================
add_executable(learn
    learn/learn.cpp
)

target_link_libraries(learn PRIVATE
    test
)

target_include_directories(learn PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ============================================
# 创建 summary 可执行文件
# ============================================
add_executable(summary
    learn/summary.cpp
)

target_link_libraries(summary PRIVATE
    test
)

target_include_directories(summary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ============================================
# 添加 exercises 子目录
# ============================================
add_subdirectory(exercises)

