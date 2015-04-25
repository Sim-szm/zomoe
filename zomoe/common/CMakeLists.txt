# 要编译的源码文件
SET (SYS_SRCS 
	hello.cc      
)

# 编译库文件
ADD_LIBRARY (zomoe_common ${SYS_SRCS})

# 设置附加链接库
TARGET_LINK_LIBRARIES (zomoe_common pthread)
