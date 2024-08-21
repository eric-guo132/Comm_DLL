# CMakeList.txt: Comm_DLL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Comm_DLL")


# 将源代码添加到此项目的可执行文件。
add_library(Comm_DLL "ADSComm.cpp" "TCPModbusComm.cpp")


# 设置目标的包含目录
target_include_directories(Comm_DLL PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/ADS/TcAdsDll/Include)

# 链接库文件
target_link_libraries(Comm_DLL PRIVATE ${CMAKE_SOURCE_DIR}/ThirdParty/ADS/TcAdsDll/x64/lib/TcAdsDll.lib)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Comm_DLL PROPERTY CXX_STANDARD 20)
endif()

# 复制 TcAdsDll.dll 到输出目录
add_custom_command(TARGET Comm_DLL POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/ThirdParty/ADS/TcAdsDll/x64/lib/TcAdsDll.dll"
                   $<TARGET_FILE_DIR:Comm_DLL>)
