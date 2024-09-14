# COMM_DLL

基于常用通信进行二次开发的动态库。目前包含ADS、Modbus-TCP。

Version : 1.0.1

目前仅支持生成X64的dll

***
## ADSComm (ADS模块)
### 接口说明
####  int ADS_init(const string& address = "192.168.2.100.1.1", int port = AMSPORT_R0_PLC_TC3);
##### 说明:
		尝试与设备建立通讯，
		成功返回零，失败返回错误码，使用“ ADS_error(errorValue)”获取详细的错误信息
##### 输入：
		address 设备ip，必须是被"."分割成6部份数字的字符串，比如默认的 "192.168.2.100.1.1" ;
		port	端口，  默认AMSPORT_R0_PLC_TC3（851）;
##### 返回值：
		int类型  0 表示成功， 其他数字为错误码,表示失败


#### int ADS_readePara(const string& para_name, T& value)
##### 说明：
		通过变量名称读取对应的值，测试过的类型：bool, int, float；
		成功返回零，失败返回错误码，使用“ ADS_error(errorValue)”获取详细的错误信息
##### 输入：
		para_name  变量名称，需读取的变量名称;
		value	   变量值，  读取成功获取的值;
##### 返回值：
		int类型	 0 表示成功， 其他数字为错误码,表示失败


#### int ADS_writePara(const string& para_name, T& value)
##### 说明：
		通过变量名称写入相应的值，测试过的类型：bool, int, float
		成功返回零，失败返回错误码，使用“ ADS_error(errorValue)”获取详细的错误信息
##### 输入：
		para_name  变量名称，需写入的变量名称;
		value	   变量值，  需写入的变量值;
##### 返回值：
		int类型	 0 表示成功， 其他数字为错误码,表示失败	


#### int ADSComm::ADS_register_trigger_callback(int triggerCount)
##### 说明：
		注册trigger的通知，析构函数中自动取消trigger的通知，对应的值放在全局变量 vector<int> triggerLabel;
		成功返回零，失败返回错误码，使用“ ADS_error(errorValue)”获取详细的错误信息
##### 输入：
		triggerCount  trigger的总数;
		
##### 返回值：
		int类型	 0 表示成功， 其他数字为错误码,表示失败	
		

#### string ADS_error(int errorValue);
##### 说明：
		根据错误码返回详细的错误信息
##### 输入：
		errorValue  错误码
##### 返回值：
		string类型	 详细的错误信息

### 使用说明
类进行实例化后，与设备尝试连接，连接成功后即可通过变量名进行读写操作

##### 示例
	ADSComm test;
	int nErr =test.ADS_init();
	if (nErr)
	{
		cout << ADS_error(nErr) << endl;
	}
	else
	{
		cout << " Success to connect the device" << endl;
	}

	bool OutputBelt_Run = true;
	nErr = test.ADS_readPara(".EN_OutputBelt_Run", OutputBelt_Run);
	if (test.ADS_readPara(".EN_OutputBelt_Run", OutputBelt_Run))
	{
		cout << ADS_error(nErr) << endl;
	}
***
## ModbusTCP (ModbusTCP模块)