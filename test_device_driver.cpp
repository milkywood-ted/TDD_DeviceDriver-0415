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
protected:
	void SetUp() {
		//deviceDriver = DeviceDriver{ &flashMemDev };
	}
public:
	MockFlashMemDevice flashMemDev;

	int testRead(long address) {
		DeviceDriver deviceDriver{ &flashMemDev };
		return deviceDriver.read(address);
	}

	void testWrite(long address, int data) {
		DeviceDriver deviceDriver{ &flashMemDev };
		deviceDriver.write(address, data);
	}
};

TEST_F(DeviceDriverFixture, ReadPositiveTC01) {
	int expectedValue = 0xDE;
	long dummyAddress = 0xdeaddead;

	EXPECT_CALL(flashMemDev, read(_))
		.Times(5)
		.WillRepeatedly(Return(expectedValue));
	testRead(dummyAddress);
}

TEST_F(DeviceDriverFixture, ReadNegativeTC01) {
	long dummyAddress = 0xdeaddead;
	unsigned char dummyValue = 0xDE;

	EXPECT_CALL(flashMemDev, read(_))
		.Times(5)
		.WillOnce(Return(0x1))
		.WillRepeatedly(Return(dummyValue));
	try {
		testRead(dummyAddress);
	}
	catch (ReadFailException& e) {
		EXPECT_EQ(std::string{ e.what() }, "Value is unstable from 5times read from the Device");
	}
}

TEST_F(DeviceDriverFixture, WritePositiveTC01) {
	int expectedReadValue = 0xFF, writeValue = 0xDADA;
	long dummyAddress = 0xdeaddead;

	EXPECT_CALL(flashMemDev, read(_))
		.WillRepeatedly(Return(expectedReadValue));
	EXPECT_CALL(flashMemDev, write(dummyAddress, writeValue))
		.Times(1);

	testWrite(dummyAddress, writeValue);
}
TEST_F(DeviceDriverFixture, WriteNegaitiveTC01) {
	int expectedReadValue = 0xFE, writeValue = 0xDADA;
	long dummyAddress = 0xdeaddead;

	EXPECT_CALL(flashMemDev, read(_))
		.WillRepeatedly(Return(expectedReadValue));
	EXPECT_CALL(flashMemDev, write(dummyAddress, writeValue))
		.Times(0);
	try {
		testWrite(dummyAddress, writeValue);
	}
	catch (WriteFailException& e) {
		EXPECT_EQ(std::string{ e.what() }, "Value is already writtine in");
	}
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

#include "application.cpp"
TEST_F(DeviceDriverFixture, AppReadTC) {
	DeviceDriver deviceDriver{ &flashMemDev };
	Application app{ &deviceDriver };
	long dummyAddress = 0xdeadead;

	EXPECT_CALL(flashMemDev, read(_))
		.Times(25)
		.WillRepeatedly(Return(10));
;
	app.readAndPrint(0xa0, 0xa4);
}

TEST_F(DeviceDriverFixture, AppWriteTC) {
	DeviceDriver deviceDriver{ &flashMemDev };
	Application app{ &deviceDriver };

	EXPECT_CALL(flashMemDev, read(_))
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMemDev, write(_,_))
		.Times(5);
	app.writeAll(0x11);
}


int main() {
	InitGoogleMock();
	return RUN_ALL_TESTS();
}
