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

        self.cmb_number = ttk.Combobox(self)
        self.cmb_number["values"] = list(range(1, 10))
        self.cmb_number["state"] = "readonly"
        self.cmb_number.grid(column=0, row=1)

        self.btn_number = tk.Button(self, text="Send", command=self.number_change)
        self.btn_number.grid(column=1, row=1)

    def btn_start_click(self):
        selected_port = self.cmb_ports_text.get()
        if selected_port:
            self.arduino = Arduino(f"/dev/{selected_port}")

    def number_change(self):
        if self.arduino:
            val = str.encode(str(self.cmb_number.get()))
            print(val)
            self.arduino.send(val)


if __name__ == '__main__':
    app = App()
    app.mainloop()



