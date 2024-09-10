#include "ModbusTCP.h"
#include<vector>

ModbusTCP::ModbusTCP()
{	
}

ModbusTCP::~ModbusTCP()
{
	if (ctx)
	{
		modbus_free(ctx);
	}
}

bool ModbusTCP::Modbus_init(const string& address, const int port)
{
	ctx = modbus_new_tcp(address.c_str(), port);
	varMap = {

		{"camera_impuse_singal" , 32768},			// input coil
		{"Ledlight_singal_readcoil", 32768},		// read coil
		{"speedtest_read_regsiter", 32770},			// read register
		{"temputuretest_read_regsiter", 32769}		// holding register
	};

	if (ctx == NULL)
	{
		std::cerr << "Unable to create the libmodbus context" << std::endl;
		return false;
	}
	// 连接到 Modbus 服务器
	if (modbus_connect(ctx) == -1) {
		std::cerr << "Connection failed: " << modbus_strerror(errno) << std::endl;
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::InputCoil_read(const string& var_name, uint8_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}
	if (modbus_read_input_bits(ctx, varAddress->second, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::InputCoil_read(const int& address, uint8_t& value)
{
	if (modbus_read_input_bits(ctx, address, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Coil_read(const string& var_name, uint8_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}
	if (modbus_read_bits(ctx, varAddress->second, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Coil_read(const int& address, uint8_t& value)
{
	if (modbus_read_bits(ctx, address, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
	}
	return true;
}

bool ModbusTCP::Coil_write(const string& var_name, uint8_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}
	if (modbus_write_bits(ctx, varAddress->second, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Coil_write(const int& address, uint8_t& value)
{

	if (modbus_write_bits(ctx, address, 1, &value) == -1)
	{
		std::cerr << "failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::InputRegister_read(const string& var_name, uint16_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}


	int rc = modbus_read_input_registers(ctx, varAddress->second, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::InputRegister_read(const int& address, uint16_t& value)
{
	int rc = modbus_read_input_registers(ctx, address, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Register_read(const string& var_name, uint16_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}


	int rc = modbus_read_registers(ctx, varAddress->second, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Register_read(const int& address, uint16_t& value)
{
	int rc = modbus_read_registers(ctx, address, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Register_write(const string& var_name, uint16_t& value)
{
	auto varAddress = varMap.find(var_name);
	if (varAddress == varMap.end())
	{
		cout << " Cann't find this variable" << endl;
		return false;
	}


	int rc = modbus_write_registers(ctx, varAddress->second, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}

bool ModbusTCP::Register_write(const int& address, uint16_t& value)
{
	int rc = modbus_write_registers(ctx, address, 1, &value);
	if (rc == -1) {
		std::cerr << "Failed to read: " << modbus_strerror(errno) << std::endl;
		modbus_close(ctx);
		modbus_free(ctx);
		return false;
	}
	return true;
}



