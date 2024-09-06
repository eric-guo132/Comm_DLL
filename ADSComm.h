#ifndef ADSCOMM_H
#define ADSCOMM_H

#ifdef _WIN32
#define ADSCOMM_API __declspec(dllexport) // 导出
#else
#define ADSCOMM_API
#endif

#include <string>
#include <iostream>
#include <windows.h>
#include <any>
#include <mutex>

#include "TcAdsDef.h"
#include "TcAdsApi.h"

using namespace std;


struct ADSDataType
{
    std::string var_name;        
    unsigned long handle = 0;    
    unsigned int dim = 0;        
    void* val;                

    // 构造函数
    ADSDataType() = default;

    // 带参数的构造函数
    ADSDataType(const std::string& name, unsigned long h, unsigned int d)
        : var_name(name), handle(h), dim(d), val(nullptr) {}

    // 析构函数，确保释放 val
    ~ADSDataType() {
        reset();  // 释放 val
    }
    void reset() {
        if (val)
        {
            free(val);
            val = nullptr;  // 重置为 nullptr
        }
        var_name.clear();
        handle = 0;
        dim = 0;
    }
};

class ADSCOMM_API ADSComm
{
public:
    // 构造函数和析构函数
    ADSComm();
    ~ADSComm();

    //
    bool ADS_init(const string& ip = "192.168.2.200.1.1", int port = AMSPORT_R0_PLC_RTS1);
    template <typename T>
    bool ADS_readPara(const string& parameter, T& value);
    template <typename T>
    bool ADS_writePara(const string& parameter, T& value);
private:
    string ADS_error(int);

public:
    USHORT          nAdsState;	
    USHORT          nDeviceState;

    AmsAddr         Addr;
    long            nErr;
    long            nPort;
    AdsVersion*     pDLLVersion;
private:
    std::mutex      mtx;
    ADSDataType     dataADS;
};

#endif // ADSCOMM_H
