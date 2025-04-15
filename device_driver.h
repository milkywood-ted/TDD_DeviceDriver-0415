#pragma once
#include "flash_memory_device.h"
#include <stdexcept>

class ReadFailException : public std::logic_error {
public:
    using _Mybase = logic_error;

    explicit ReadFailException(const std::string& _Message) : _Mybase(_Message.c_str()) {}
    explicit ReadFailException(const char* _Message) : _Mybase(_Message) {}
private:
};
class WriteFailException : public std::logic_error {
public:
    using _Mybase = logic_error;

    explicit WriteFailException(const std::string& _Message) : _Mybase(_Message.c_str()) {}
    explicit WriteFailException(const char* _Message) : _Mybase(_Message) {}
private:
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice *m_hardware;
};
