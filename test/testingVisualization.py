import serial
import pyqtgraph as pg
import numpy as np
import time
from PyQt5 import QtWidgets
import sys

# Setup
ser = serial.Serial('/dev/cu.usbserial-0001', 115200, timeout=1)
binVal_buffer = np.zeros(32, dtype=np.int64)

app = QtWidgets.QApplication(sys.argv)
win = pg.GraphicsLayoutWidget(show=True, title="Audio Visualization")
plot = win.addPlot(title="Frequency Bins")
plot.setLabel('left', 'Value')
plot.setLabel('bottom', 'Bin')
bargraph = pg.BarGraphItem(x=np.arange(32), height=binVal_buffer, width=0.8)
plot.addItem(bargraph)

while True:
    if ser.in_waiting > 0:
        try:
          line_data = ser.readline().decode('utf-8').strip()
          if line_data:
              # Parse your specific format
              
              bin_vals = line_data.split(',')
              bin_num = int(bin_vals[0])
              if(len(bin_vals) > 1):
                binVal = np.int64(bin_vals[1]) / 1000
              else:
                continue
              print(bin_vals)
              binVal_buffer[bin_num] = binVal

              # Update plot - bar graph
              bargraph.setOpts(height=binVal_buffer)
              app.processEvents()

        except KeyboardInterrupt:
            break
        except ValueError:
            continue  # Skip malformed lines

ser.close()
app.quit()