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

    /**
     * @brief Initializes the ADS communication connection.
     *
     * This function is used to establish an ADS communication connection with the specified IP address and port.
     *
     * @param ip  The IP address of the target device. The default value is "192.168.2.200.1.1".
     * @param port  The port number of the target device. The default value is AMSPORT_R0_PLC_RTS1.
     *
     * @return bool  Returns true if the initialization is successful; false indicates failure.
     *              The error code can be further interpreted using the ADS_error function.
     *
     */
    bool ADS_init(const string& ip = "192.168.2.200.1.1", int port = AMSPORT_R0_PLC_RTS1);

    /**
     * @brief Reads a parameter from the ADS device and stores it in the provided variable.
     *
     * This function reads a parameter with the specified name from the ADS device and stores the result in the provided variable of type `T`.
     *
     * @tparam T  The type of the variable in which the parameter value will be stored.
     *
     * @param parameter  The name of the parameter to read from the ADS device.
     * @param value  The reference to a variable where the read value will be stored.
     *
     * @return bool  Returns true if the parameter is successfully read and stored in `value`.
     *               Returns false if there is an error during the read operation.
     *
     * @note Ensure that the type `T` is compatible with the parameter being read from the ADS device.
     *       The parameter name must be valid and accessible in the ADS device.
     */
    template <typename T>
    bool ADS_readPara(const string& parameter, T& value);

    /**
     * @brief Writes a value to the specified parameter on the ADS device.
     *
     * This function writes the provided value of type `T` to the parameter with the specified name on the ADS device.
     *
     * @tparam T  The type of the value to be written to the ADS device.
     *
     * @param parameter  The name of the parameter to which the value will be written.
     * @param value  The reference to the value that will be written to the parameter.
     *
     * @return bool  Returns true if the value is successfully written to the ADS device.
     *               Returns false if there is an error during the write operation.
     *
     * @note Ensure that the type `T` is compatible with the parameter being written to the ADS device.
     *       The parameter name must be valid and writable on the ADS device.
     */
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
