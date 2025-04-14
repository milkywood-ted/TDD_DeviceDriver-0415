from hardware_interface import FlashMemoryDevice

class DeviceDriver:
    """
    This class is used by the operating system to interact with the hardware 'FlashMemoryDevice'.
    """

    def __init__(self, device: FlashMemoryDevice):
        """
        :type device: hardware_interface.FlashMemoryDevice
        """
        self.__device = device

    def write(self, address: int, data: int) -> None:
        # TODO: implement this method
        pass

    def read(self, address: int) -> int:
        # TODO: implement this method
        return 0
