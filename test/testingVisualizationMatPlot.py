import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


ser = serial.Serial('/dev/ttyUSB0', 115200, timeout = 1)


num_bins = 32
bin_vals = np.zeros(num_bins, dtype=np.int64)

fig, ax = plt.subplots()
bars = ax.bar(np.arange(num_bins), bin_vals)
ax.set_ylim(0, 100)
ax.set_xlabel("Bin")
ax.set_ylabel("Value")
ax.set_title("Frequency Bins")

# --- Update function ---
def update(frame):
    global bin_vals

    while ser.in_waiting > 0:
        try:
            line = ser.readline().decode("utf-8").strip()
            if not line:
                continue

            parts = line.split(",")
            if len(parts) < 2:
                continue

            bin_num = int(parts[0])
            bin_val = float(parts[1])

            print("(", bin_num, ", ", bin_val, ")")

            if 0 <= bin_num < num_bins:
                bin_vals[bin_num] = bin_val

        except ValueError:
            continue  # skip malformed lines

    # Update bar heights
    for bar, h in zip(bars, bin_vals):
        bar.set_height(h)

    return bars

# --- Animate ---
ani = animation.FuncAnimation(fig, update, interval=50, blit=False)
plt.show()

ser.close()
