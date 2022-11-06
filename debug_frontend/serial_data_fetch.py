import serial

port = serial.Serial("/dev/ttyACM1", baudrate=115200, timeout=3.0)

# do not change!
symbol_len = 4
start_symbol = b'DATA'
end_symbol = b'ENDE'

def serial_data_parser(pipe):
    in_data_block = False
    symbol = b''
    data = []
    while True:
        rcv = port.read()
        symbol = symbol + rcv
        if len(symbol) > symbol_len:
            symbol = symbol[-symbol_len:]
        if in_data_block:
            data.append(int.from_bytes(rcv, "big"))
        if not in_data_block and symbol == start_symbol:
            in_data_block = True
            symbol = b''
            data = []
            print("in block :)")
        elif in_data_block and symbol == end_symbol:
            in_data_block = False
            symbol = b''
            pipe.send(data[:-symbol_len])
            print("out block :(")