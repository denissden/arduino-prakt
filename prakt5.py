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
        # start button
        self.btn_start = tk.Button(self, text="Send message", command=self.btn_start_click)
        self.btn_start.grid(column=1, row=0)

        # port selector
        self.cmb_ports = ttk.Combobox(self, textvariable=self.cmb_ports_text)
        self.ports = get_ports()
        self.cmb_ports["values"] = self.ports
        self.cmb_ports["state"] = "readonly"
        self.cmb_ports.grid(column=0, row=0)

        # led on button
        self.btn_start = tk.Checkbutton(self, text="Led on", command=self.cbtn_led_click, variable=self.led_var)
        self.btn_start.grid(column=0, row=1)

    def btn_start_click(self):
        selected_port = self.cmb_ports_text.get()
        if selected_port:
            self.arduino = Arduino(f"/dev/{selected_port}")

    def cbtn_led_click(self):
        state = self.led_var.get()
        if self.arduino:
            self.arduino.send(b"ledon" if state else b'ledoff', read=False)


if __name__ == '__main__':
    app = App()
    app.mainloop()



