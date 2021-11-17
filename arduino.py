import serial
import threading

class Arduino:
    serial_: serial

    def __init__(self, path, rate=38400, **serial_kwargs):
        try:
            self.serial_ = serial.Serial(path, baudrate=rate, **serial_kwargs)
        except PermissionError as e:
            print(f"Not enough permissions to open {path}: {e}")

        t = threading.Thread(target=self.receive)
        t.start()

    def send(self, message: bytes, read=False):
        print(f"send: |{message}|")
        self.serial_.write(message)
        if read:
            return self.read()

    def receive(self):
        print("started receive")
        while 1:
            print(f"line received: {self.read()}")

    def read(self):
        byte = self.serial_.readline()
        s = ''.join(map(chr, byte))
        return s
