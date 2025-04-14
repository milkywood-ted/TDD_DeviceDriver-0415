from abc import ABC, abstractmethod

class FlashMemoryDevice(ABC):
    """
    This class represents the interface to a Flash Memory Device. The hardware has only two methods - 'read' and 'write'
    """

    @abstractmethod
    def read(self, address: int) -> int:
        """
        returns the data found at the address given.
        This method is implemented in the actual hardware, this is just a stub showing the interface that method fulfils.
        :type address: int
        :rtype: int
        """
        pass

    @abstractmethod
    def write(self, address: int, data: int) -> None:
        """
        write the data given to the address given.
        This method is implemented in the actual hardware, this is just a stub showing the interface that method fulfils.
        :type address: int
        :type data: int
        """
        pass
