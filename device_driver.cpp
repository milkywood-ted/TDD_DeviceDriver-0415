#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    //return (int)(m_hardware->read(address));

    int readValues[5] = { -1 };

    for (auto& r : readValues)
        r = m_hardware->read(address);

    int readValue = readValues[0];
    for (auto& r : readValues) {
        if (readValue != r)
            throw ReadFailException("Value is unstable from 5times read from the Device");
    }
    
    return readValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    //m_hardware->write(address, (unsigned char)data);

    int value = read(address);

    if (value != 0xFF)
        throw WriteFailException("Value is already writtine in");

    m_hardware->write(address, data);
}
