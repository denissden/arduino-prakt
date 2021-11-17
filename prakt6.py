import tkinter as tk
from tkinter import ttk
import serial.tools.list_ports
from arduino import Arduino


def get_ports():
    return [p.name for p in serial.tools.list_ports.comports()]


class App(tk.Tk):
    arduino: Arduino = None

    def __init__(self):
        super().__init__()

        self.geometry('300x200')
        self.resizable(False, False)
        self.title('Combobox Widget')

        self.cmb_ports_text = tk.StringVar()
        self.led_var = tk.IntVar()

        self.create_widgets()

    def create_widgets(self):
        # connect button
        self.btn_start = tk.Button(self, text="Connect", command=self.btn_start_click)
        self.btn_start.grid(column=1, row=0)

        # port selector
        self.cmb_ports = ttk.Combobox(self, textvariable=self.cmb_ports_text)
        self.ports = get_ports()
        self.cmb_ports["values"] = self.ports
        self.cmb_ports["state"] = "readonly"
        self.cmb_ports.grid(column=0, row=0)

        btn_number = tk.Button(self, text=1, command=lambda: self.cbtn_led_click(1))
        btn_number.grid(column=0, row=2)

        btn_number = tk.Button(self, text=2, command=lambda: self.cbtn_led_click(2))
        btn_number.grid(column=0, row=3)

        btn_number = tk.Button(self, text=3, command=lambda: self.cbtn_led_click(3))
        btn_number.grid(column=0, row=4)

        btn_number = tk.Button(self, text=4, command=lambda: self.cbtn_led_click(4))
        btn_number.grid(column=0, row=5)

        btn_number = tk.Button(self, text=5, command=lambda: self.cbtn_led_click(5))
        btn_number.grid(column=0, row=6)

    def btn_start_click(self):
        selected_port = self.cmb_ports_text.get()
        if selected_port:
            self.arduino = Arduino(f"/dev/{selected_port}")

    def cbtn_led_click(self, led_number):
        print(led_number)
        if self.arduino:
            val = str.encode(str(led_number))
            print(val)
            self.arduino.send(val)


if __name__ == '__main__':
    app = App()
    app.mainloop()



