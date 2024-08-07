# cmake文件不改动，makefile不变，所以在目录中添加文件检测不到会报错，得rm一下中间文件，重新cmake
aux_source_directory(. SRC_LIST)
#set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcheader.pb.cc rpcprovider.cc)

# SHARED 生成动态库
#add_library(mprpc SHARED ${SRC_LIST})
# 生成静态库 
add_library(mprpc ${SRC_LIST})
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)