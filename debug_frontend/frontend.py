import matplotlib.pyplot as plt
import numpy as np
import serial_data_fetch
from multiprocessing import Process, Pipe


# pyserial needed
# installation: pip3 install pyserial


def ui_thread(pipe):
    x = [0,1,2,3,4,5,6,7,8,9]
    y = np.zeros([10])
    
    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    line1, = ax.plot(x, y, color='tab:blue')


    # set the limits
    ax.set_xlim([0, 9])
    ax.set_ylim([0,255])
    ax.set_title('line plot with data points')

    
    while True:
        data = pipe.recv()
        print("got deta :)")
        ax.set_xlim([0, len(data)])
        line1.set_xdata(np.arange(len(data)))
        line1.set_ydata(data)
        fig.canvas.draw()
        fig.canvas.flush_events()


if __name__ == '__main__':
    parent_conn, child_conn = Pipe()
    p = Process(target=serial_data_fetch.serial_data_parser, args=(child_conn,))
    p.start()
    ui_thread(parent_conn)