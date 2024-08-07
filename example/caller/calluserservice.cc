#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv)
{
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（值初始化一次）
    MprpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;
    // 发起rpc方法的调用  同步（等待返回）的rpc调用过程   实际调用MprpcChannel::CallMethod
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel-->RpcChannel::CallMethod 集中来做所有rpc方法调用的

    // 一次rpc调用完成，读调用结果
    if (response.result().errcode() == 0)
    {
        std::cout << "rpc login response success: " << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
    }

    // 演示调用远程发布的rpc方法Register
    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("666666");

    fixbug::RegisterResponse rsp;

    // 以同步的方式发起rpc调用请求，等待返回结果
    stub.Register(nullptr, &req, &rsp, nullptr);

    if (rsp.result().errcode() == 0)
    {
        std::cout << "rpc register response success: " << rsp.success() << std::endl;
    }
    else
    {
        std::cout << "rpc register response error: " << rsp.result().errmsg() << std::endl;
    }
    return 0;
}