CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (socx CXX)

# 默认以 Debug 模式编译
IF (NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

# 设置编译参数
SET (CXX_FLAGS
	-Wall
	-Wextra
	-Werror
	-Wconversion
	-Wno-unused-parameter
	-Woverloaded-virtual
	-Wpointer-arith
	-Wshadow
	-Wwrite-strings
	-march=native
	-rdynamic
	-std=c++11
)

# 设置编译选项
SET (CMAKE_CXX_COMPILER "g++")
SET (CMAKE_CXX_FLAGS_DEBUG "-O0")
SET (CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 替换默认编译选项
STRING (REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")
STRING (TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
MESSAGE (STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

# 头文件包含目录
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR})

# 添加代码子目录
ADD_SUBDIRECTORY (zomoe)

