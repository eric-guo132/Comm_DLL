# COMM_DLL

基于常用通信进行二次开发的动态库。目前包含ADS、Modbus-TCP。

Version : 1.0.1

***
## ADSComm (ADS模块)
### 接口说明
####  int ADS_init(const string& address = "192.168.2.100.1.1", int port = AMSPORT_R0_PLC_TC3);
##### 说明:
		尝试与设备建立通讯
##### 输入：
		address 设备ip，必须是被"."分割成6部份数字的字符串，比如默认的 "192.168.2.100.1.1" ;
		port	端口，  默认AMSPORT_R0_PLC_TC3（851）;
##### 返回值：
		int类型  0 表示成功，11 表示ads端口打开失败，22 表示ip格式错误，无法分割成6部分数字， 其他数字是建立连接失败的错误码；


#### bool ADS_readePara(const string& para_name, T& value)
##### 说明：
		通过变量名称读取对应的值，测试过的类型：bool, int, float
##### 输入：
		para_name  变量名称，需读取的变量名称;
		value	   变量值，  读取成功获取的值;
##### 返回值：
		bool类型	true表示读取成功， false表明读取失败；


#### bool ADS_writePara(const string& para_name, T& value)
##### 说明：
		通过变量名称写入相应的值，测试过的类型：bool, int, float
##### 输入：
		para_name  变量名称，需写入的变量名称;
		value	   变量值，  需写入的变量值;
##### 返回值：
		bool类型	true表示写入成功， false表明写入失败；		

### 使用说明
类进行实例化后，与设备尝试连接，连接成功后即可通过变量名进行读写操作

##### 示例
	ADSComm test;
	if (test.ADS_init())
	{
		cout << " Success to connect the device " << endl;
	}
	else
	{
		cout << " Failed to connect the device" << endl;
	}
	bool OutputBelt_Run = true;
	if (test.ADS_readPara(".EN_OutputBelt_Run", OutputBelt_Run))
	{
		cout << OutputBelt_Run << endl;
	}
***
## ModbusTCP (ModbusTCP模块)