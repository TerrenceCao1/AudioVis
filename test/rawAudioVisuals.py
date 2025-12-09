import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

POINTS = 128
REFRESH_MS = 1

ser = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)

plt.style.use('seaborn-v0_8-darkgrid')
fig, ax = plt.subplots()
x_data = np.arange(POINTS)
y_data = np.zeros(POINTS)
(line,) = ax.plot(x_data, y_data, lw=1.5)

ax.set_ylim(-5, 5)
ax.set_xlim(0, POINTS - 1)
ax.set_title("what am i doing with my life")
ax.set_xlabel("index")
ax.set_ylabel("amp")

def update(frame):
    global y_data

    new_vals = np.zeros(POINTS)
    read_count = 0

    while read_count < POINTS:
        line_raw = ser.readline().decode("utf-8", errors="ignore").strip()
        if not line_raw:
            break

        try:
            idx_str, val_str = line_raw.split(",")
            idx = int(idx_str)
            val = float(val_str)
            if 0 <= idx < POINTS:
                new_vals[idx] = val
                read_count += 1
            print(str(idx) + ", " + str(val))
        except ValueError:
            continue

    if read_count > 0:
        y_data = new_vals
        line.set_ydata(y_data)

    return (line,)

ani = animation.FuncAnimation(fig, update, interval=REFRESH_MS, blit=True)
plt.show()
