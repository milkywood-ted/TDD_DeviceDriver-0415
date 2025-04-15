#include "device_driver.h"
#include <iostream>
#include <string>

class Application {
public:
	Application(DeviceDriver* deviceDriver) : deviceDriver_{ deviceDriver } {}
	void readAndPrint(long startAddr, long endAddr) {
		long readAddr = startAddr;

		while (readAddr <= endAddr)
			std::cout << deviceDriver_->read(readAddr++);
	}

	void writeAll(int value) {
		long addrs[] = { 0x0, 0x1, 0x2, 0x3, 0x4 };
		for(auto& addr : addrs)
			deviceDriver_->write(addr, value);
	}
private:
	DeviceDriver* deviceDriver_;
};