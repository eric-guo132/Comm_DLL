#ifndef COMMBASE_H
#define COMMBASE_H

#include <string>

class CommBase
{
public:
    virtual ~CommBase() {}

    // 初始化通讯接口
    virtual bool init(const std::string& ip, int port) = 0;

    // 读取参数
    template <typename T>
    virtual bool readPara(const std::string& parameter, T& value) = 0;

    // 写入参数
    template <typename T>
    virtual bool writePara(const std::string& parameter, const T& value) = 0;
};

#endif // COMMBASE_H
