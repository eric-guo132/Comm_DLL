#ifndef COMMBASE_H
#define COMMBASE_H

#include <string>

class CommBase
{
public:
    virtual ~CommBase() {}

    // ��ʼ��ͨѶ�ӿ�
    virtual bool init(const std::string& ip, int port) = 0;

    // ��ȡ����
    template <typename T>
    virtual bool readPara(const std::string& parameter, T& value) = 0;

    // д�����
    template <typename T>
    virtual bool writePara(const std::string& parameter, const T& value) = 0;
};

#endif // COMMBASE_H
