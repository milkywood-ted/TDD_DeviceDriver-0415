#include "gmock/gmock.h"
#include "flash_memory_device.h"
#include "device_driver.h"

using namespace ::testing;

class MockFlashMemDevice : public FlashMemoryDevice {
public:
	//  virtual unsigned char read(long address) = 0;
	//	virtual void write(long address, unsigned char data) = 0;
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
public:
	MockFlashMemDevice flashMemDev;

	int testRead(long address) {
		DeviceDriver deviceDriver{ &flashMemDev };
		int readValue = -1;
	
		try {
			readValue = deviceDriver.read(address);
			//EXPECT_EQ(expectedValue, testRead(dummyAddress));
		}
		catch (ReadFailException& e) {
			EXPECT_EQ(std::string{ e.what() }, "Value is unstable from 5times read from the Device");
		}
		return readValue;
	}
};

TEST_F(DeviceDriverFixture, ReadPositiveTC01) {
	int expectedValue = 0xDE;
	long dummyAddress = 0xdeaddead;

	EXPECT_CALL(flashMemDev, read(dummyAddress))
		.Times(5)
		.WillRepeatedly(Return(expectedValue));
	testRead(dummyAddress);
}

TEST_F(DeviceDriverFixture, ReadNegativeTC01) {
	long dummyAddress = 0xdeaddead;
	unsigned char dummyValue = 0xDE;

	EXPECT_CALL(flashMemDev, read(dummyAddress))
		.Times(5)
		.WillOnce(Return(0x1))
		.WillRepeatedly(Return(dummyValue));

	testRead(dummyAddress);
}

/*
TEST(DeviceDriverTS, ReadNegativeTC1) {
	MockFlashMemDevice flashMemDev;
	DeviceDriver deviceDriver{ &flashMemDev };
	long dummyAddress = 0xdeaddead;
	unsigned char dummyValue = 0xDE;

	EXPECT_CALL(flashMemDev, read(dummyAddress))
		.Times(5)
		.WillOnce(Return(0x1))
		.WillRepeatedly(Return(dummyValue));

	unsigned char expected = dummyValue;
	deviceDriver.read(dummyAddress);
	EXPECT_THROW(deviceDriver.read(dummyAddress), ReadFailException);
}
*/


int main() {
	InitGoogleMock();
	return RUN_ALL_TESTS();
}