﻿#include "ADSComm.h"
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread> 

ADSCOMM_API vector<int> triggerLabel;

ADSComm::ADSComm()
{
    nAdsState = 0;
    nDeviceState = 0;
    nErr = 0;
    nPort = 0;
    hTriggerNotification = 0;

    pDLLVersion = nullptr;
 
}

ADSComm::~ADSComm()
{
    // 在析构函数中取消通知
    if (hTriggerNotification) {
        nErr = AdsSyncDelDeviceNotificationReq(&Addr, hTriggerNotification);
        if (nErr) {
            std::cerr << "Error removing ADS notification: " << nErr << std::endl;
        }
    }
    if (nPort)
    {
        nErr = AdsPortClose();
        if (nErr)
        {
            cerr << ADS_error(nErr) << endl;
        }
    }
}

int ADSComm::ADS_init(const std::string& address, int port)
{
    long AdxDllVersion = AdsGetDllVersion();

    pDLLVersion = (AdsVersion*)&AdxDllVersion;

    nPort = AdsPortOpen();
    if (nPort)
    {
        cout << "Port" << nPort << "opening OK" << endl;
    }
    else
    {
        cout << "Port" << nPort << "opening failed" << endl;
        return 18;
    }

	//	get ip from string
	std::stringstream ss(address); 
	std::string segment;      
	std::vector<int> segments; 
	while (std::getline(ss, segment, '.')) 
	{
		segments.push_back(std::stoi(segment)); 
	}
	if (segments.size() == 6) 
	{
		for (size_t i = 0; i < 6; ++i) 
		{
			Addr.netId.b[i] = segments[i]; 
		}
	}
	else 
	{
		std::cerr << "The IP address is not in the correct format and cannot be split into 6 segments!" << std::endl;
		return 7;
	}
    Addr.port = port;
	AdsSyncSetTimeout(500);

	auto start_time = std::chrono::steady_clock::now();
	double elapsed_seconds;
	do
	{
        nErr = AdsSyncReadStateReq(&Addr, &nAdsState, &nDeviceState);
		if (nErr)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1)); 
		}
		auto elapsed_time = std::chrono::steady_clock::now() - start_time;
		elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count();

        if (GetAsyncKeyState(VK_F1) & 0x8000) {  // 0x8000 表示按键状态为按下
            break;  // 用户按下 F1 键，中断循环
        }

		if (elapsed_seconds >= 60.0)
		{
			break;
		}

	} while (nErr);

	if (nErr)
	{
		return nErr;
	}

	if (nAdsState == 11001)
	{
		cerr << "Unable to find PLC/ADS system" << endl;
		return 1799;
	}

	if (nAdsState != ADSSTATE_RUN) //&& nDeviceState != ADSSTATE_STOP )
	{
		nErr = AdsSyncWriteControlReq(&Addr, ADSSTATE_RUN, nDeviceState, 0, NULL);
		if (nErr)
		{
			return nErr;
		}	
	}
	return 0;
}


int ADSComm::ADS_register_trigger_callback(int triggerCount)
{
    triggerLabel.resize(triggerCount);

    triggerNotification.cbLength = sizeof(triggerCount);
    triggerNotification.nTransMode = ADSTRANS_SERVERONCHA;
    triggerNotification.nMaxDelay = 10000; // 1ms (unit=0.1us)
    triggerNotification.nCycleTime = 10000; // 1ms (unit=0.1us)

    hUser = 123456;

    ADSDataType dataADS;
    dataADS.var_name = "PRODUCT_FLOW.TRIGGER_LABEL";
    dataADS.dim = sizeof(triggerLabel);

    nErr = ADS_readPara(dataADS.var_name, dataADS.val);
    if (nErr)
    {
        return nErr;
    }
    nErr = AdsSyncAddDeviceNotificationReq(&Addr, ADSIGRP_SYM_VALBYHND, dataADS.handle, &triggerNotification, ADS_callback, hUser, &hTriggerNotification);
    if (nErr)
    {
        return nErr;
    }
    return 0;
}

void _stdcall ADS_callback(AmsAddr* Addr, AdsNotificationHeader* pNotification, ULONG hUser)
{
    memcpy(triggerLabel.data(), pNotification->data, pNotification->cbSampleSize);
}

string ADSComm::ADS_error(int errorValue)
{
    switch (errorValue)
    {
    case 1:
        return("Internal error");
    case 2:
        return("No Rtime");
    case 3:
        return("Allocation locked memory error");
    case 4:
        return("Insert mailbox error");
    case 5:
        return("Wrong receive HMSG");
    case 6:
        return("target port not found");
    case 7:
        return("target machine not found");
    case 8:
        return("Unknown command ID");
    case 9:
        return("Bad task ID");
    case 10:
        return("No IO");
    case 11:
        return("Unknown AMS command");
    case 12:
        return("Win 32 error");
    case 13:
        return("Port not connected");
    case 14:
        return("Invalid AMS length");
    case 15:
        return("Invalid AMS Net ID");
    case 16:
        return("Low Installation level");
    case 17:
        return("No debug available");
    case 18:
        return("Port disabled");
    case 19:
        return("Port already connected");
    case 20:
        return("AMS Sync Win32 error");
    case 21:
        return("AMS Sync Timeout");
    case 22:
        return("AMS Sync AMS error");
    case 23:
        return("AMS Sync no index map");
    case 24:
        return("Invalid AMS port");
    case 25:
        return("No memory");
    case 26:
        return("TCP send error");
    case 27:
        return("Host unreachable");
    case 1280:
        return("Router: no locked memory");
    case 1282:
        return("Router: mailbox full");
    case 1792:
        return("error class <device error>");
    case 1793:
        return("Service is not supported by server");
    case 1794:
        return("invalid index group");
    case 1795:
        return("invalid index offset");
    case 1796:
        return("reading/writing not permitted");
    case 1797:
        return("parameter size not correct");
    case 1798:
        return("invalid parameter value(s)");
    case 1799:
        return("device is not in a ready state");
    case 1800:
        return("device is busy");
    case 1801:
        return("invalid context (must be in Windows)");
    case 1802:
        return("out of memory");
    case 1803:
        return("invalid parameter value(s)");
    case 1804:
        return("not found (files, ...)");
    case 1805:
        return("syntax error in command or file");
    case 1806:
        return("objects do not match");
    case 1807:
        return("object already exists");
    case 1808:
        return("symbol not found");
    case 1809:
        return("symbol version invalid");
    case 1810:
        return("server is in invalid state");
    case 1811:
        return("AdsTransMode not supported");
    case 1812:
        return("Notification handle is invalid");
    case 1813:
        return("Notification client not registered");
    case 1814:
        return("no more notification handles");
    case 1815:
        return("size for watch too big");
    case 1816:
        return("device not initialized");
    case 1817:
        return("device has a timeout");
    case 1818:
        return("query interface failed");
    case 1819:
        return("wrong interface required");
    case 1820:
        return("class ID is invalid");
    case 1821:
        return("object ID is invalid");
    case 1822:
        return("request is pending");
    case 1823:
        return("request is aborted");
    case 1824:
        return("signal warning");
    case 1825:
        return("invalid array index");
    case 1826:
        return("symbol not active -> release handle and try again");
    case 1827:
        return("access denied");
    case 1856:
        return("Error class <client error>");
    case 1857:
        return("invalid parameter at service");
    case 1858:
        return("polling list is empty");
    case 1859:
        return("var connection already in use");
    case 1860:
        return("invoke ID in use");
    case 1861:
        return("timeout elapsed");
    case 1862:
        return("error in win32 subsystem");
    case 1864:
        return("ads-port not opened");
    case 1872:
        return("internal error in ads sync");
    case 1873:
        return("hash table overflow");
    case 1874:
        return("key not found in hash");
    case 1875:
        return("no more symbols in cache");
    case 11001:
        return("Unable to find PLC/ADS system");

    default:
        return("unknown error code!");
    }
}
