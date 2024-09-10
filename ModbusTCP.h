#pragma once

#include <iostream>
#include <modbus.h>
#include <string>
#include <unordered_map>

#ifdef _WIN32
#ifdef MODBUS_TCP_EXPORTS
#define MODBUS_TCP_API __declspec(dllexport)
#else
#define MODBUS_TCP_API __declspec(dllimport)
#endif
#else
#define MODBUS_TCP_API
#endif

using namespace std;

class MODBUS_TCP_API ModbusTCP
{
public:
    ModbusTCP();
    ~ModbusTCP();
    bool Modbus_init(const string& address = "192.168.2.100", const int port = 502);

    bool InputCoil_read(const string& var_name, uint8_t& value);
    bool InputCoil_read(const int& address, uint8_t& value);
    bool Coil_read(const string& var_name, uint8_t& value);
    bool Coil_read(const int& address, uint8_t& value);

    bool Coil_write(const string& var_name, uint8_t& value);
    bool Coil_write(const int& address, uint8_t& value);

    bool InputRegister_read(const string& var_name, uint16_t& value);
    bool InputRegister_read(const int& address, uint16_t& value);
    bool Register_read(const string& var_name, uint16_t& value);
    bool Register_read(const int& address, uint16_t& value);

    bool Register_write(const string& var_name, uint16_t& value);
    bool Register_write(const int& address, uint16_t& value);

private:

public:
    unordered_map<string, int> varMap;
    modbus_t* ctx;
};
