#pragma once
#include <google/protobuf/service.h>
#include <string>

class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();
    // 重置
    void Reset();
    // 返回状态
    bool Failed() const;
    // 返回err信息
    std::string ErrorText() const;
    // 设置错误
    void SetFailed(const std::string &reason);

    // 目前未实现具体的功能
    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool m_failed;  // RPC方法执行过程中的状态
    std::string m_errText;  // RPC方法执行过程中的错误信息
};