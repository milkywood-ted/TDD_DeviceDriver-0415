from unittest import TestCase
from unittest.mock import Mock
from hardware_interface import FlashMemoryDevice
from device_driver import DeviceDriver

class DeviceDriverTest(TestCase):
    def test_successful_read(self):
        hardware: FlashMemoryDevice = Mock()
        driver = DeviceDriver(hardware)
        self.assertEqual(0x0, driver.read(0xFF))
