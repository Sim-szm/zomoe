# 要编译的源码文件
SET (SYS_SRCS 
	hello.cc      
	socket_base.cc

)

# 编译库文件
#ADD_LIBRARY (zomoe_network ${SYS_SRCS})

#可执行文件
ADD_EXECUTABLE(zomoe_network ${SYS_SRCS})

# 设置附加链接库
TARGET_LINK_LIBRARIES (zomoe_network pthread)
