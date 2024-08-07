#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
{
    // 嵌套使用
    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result();   //如果成员变量是一个protobuf对象的话，直接使用返回的是const类型，无法修改，所以得使用mutable_result
    // rc->set_errcode(1);
    // rc->set_errmsg("登录处理失败了");

    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(0);

    // 列表的使用
    User *user1 = rsp.add_friend_list(); // 新增一个对象，并返回对象的地址
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2 = rsp.add_friend_list();
    user2->set_name("li si");
    user2->set_age(18);
    user2->set_sex(User::MAN);

    std::cout << rsp.friend_list_size() << std::endl;

    // 列表对象的读取
    for (int i = 0; i < rsp.friend_list_size(); i++)
    {
        User user = rsp.friend_list(i);
        std::cout << user.name() << std::endl;
        std::cout << user.age() << std::endl;
        std::cout << user.sex() << std::endl;
    }
    return 0;
}
int main1()
{
    // 封装了login请求对象的数据
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    // 对象数据序列化-> char *
    std::string send_str;
    if (req.SerializeToString(&send_str)) // 序列化
    {
        std::cout << send_str << std::endl;
    }

    // 从send_str反序列化一个login请求对象
    LoginRequest reqB;
    if (reqB.ParseFromString(send_str)) // 反序列化
    {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}