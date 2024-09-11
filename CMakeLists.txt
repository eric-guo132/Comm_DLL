
cmake_minimum_required (VERSION 3.8)

project ("Comm_DLL" VERSION 1.0.1)


# 将源代码添加到此项目的可执行文件。
add_library(Comm_DLL SHARED "ADSComm.cpp" "ADSComm.h" "ModbusTCP.cpp" "ModbusTCP.h")

# 判断是否为 64 位架构
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 位架构 (x64)
    
    # ADS
    target_include_directories(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/Include)
    target_link_libraries(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/x64/lib/TcAdsDll.lib)
    
    add_custom_command(TARGET Comm_DLL POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                      "${CMAKE_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/x64/TcAdsDll.dll"
                       $<TARGET_FILE_DIR:Comm_DLL>)
    
    # Modbus-TCP
    target_include_directories(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x64/include)
    target_link_libraries(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x64/lib/modbus.lib)
    
    add_custom_command(TARGET Comm_DLL POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                      "${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x64/lib/modbus.dll"
                       $<TARGET_FILE_DIR:Comm_DLL>)

else()
    # 32 位架构 (x86)
    
    # ADS
    target_include_directories(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/Include)
    target_link_libraries(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/lib/TcAdsDll.lib)
    
    add_custom_command(TARGET Comm_DLL POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                      "${CMAKE_SOURCE_DIR}/3rdParty/ADS/TcAdsDll/bin/TcAdsDll.dll"
                       $<TARGET_FILE_DIR:Comm_DLL>)
    
    # Modbus-TCP
    target_include_directories(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x86/include)
    target_link_libraries(Comm_DLL PRIVATE ${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x86/lib/modbus.lib)
    
    add_custom_command(TARGET Comm_DLL POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                      "${PROJECT_SOURCE_DIR}/3rdParty/libmodbus/x86/lib/modbus.dll"
                       $<TARGET_FILE_DIR:Comm_DLL>)
endif()

