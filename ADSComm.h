#ifndef ADSCOMM_H
#define ADSCOMM_H

#ifdef _WIN32
#define ADSCOMM_API __declspec(dllexport) // 导出
#else
#define ADSCOMM_API
#endif

#include <string>

#include "TcAdsDef.h"
#include "TcAdsApi.h"

class ADSCOMM_API ADSComm
{
public:
    // 构造函数和析构函数
    ADSComm();
    ~ADSComm();

    // 初始化方法，通常包括设置通信参数
    int ADS_init(const std::string& ip, int port);

    // 连接到 ADS 设备
    bool Connect();

    // 断开连接
    void Disconnect();

    // 读取数据的方法
    bool ReadData(const std::string& variableName, void* buffer, int bufferSize);

    // 写入数据的方法
    bool WriteData(const std::string& variableName, const void* data, int dataSize);

    // 检查连接状态
    bool IsConnected() const;

private:
    AdsVersion* pDLLVersion;
    std::string m_ip; // 设备IP地址
    int m_port;       // 设备端口号
    bool m_isConnected; // 连接状态

    // 私有辅助方法，可以在这里添加内部实现细节
    bool SetupConnection();
};

#endif // ADSCOMM_H
