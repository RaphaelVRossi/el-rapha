#!/usr/bin/python

import asyncio
import json
import sys

import serial
import websockets


def validate_args():
    if len(sys.argv) < 3:
        print(f"uses: python {sys.argv[0]} /dev/tty.usbserial-xxx ws://localhost:4444")
        exit(1)


async def main():
    validate_args()

    serial_port = sys.argv[1]
    websocket_host = sys.argv[2]

    ser = serial.Serial(
        port=serial_port,
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=0,
    )

    ws = await websockets.connect(websocket_host, max_size=2**24)
    await ws.send('{"d":{"obsWebSocketVersion":"5.2.3","rpcVersion":1},"op":1}')
    line = []
    while True:
        for i in ser.read():
            c = chr(i)
            line.append(c)
            if c == "\n":
                print("".join(line))
                a = "".join(line)

                body = json.loads(a)
                muteMic = body.get("muteMic", False)
                if muteMic:
                    await ws.send(
                        '{"op": 6, "d": {"requestType": "ToggleInputMute", "requestId": "1234", "requestData":{"inputName": "Mic/Aux"}}}'
                    )

                volume = body.get("volume")

                if volume is not None:
                    volume = f"{volume}"
                    await ws.send(
                        '{"op": 6, "d": {"requestType": "SetInputVolume", "requestId": "1234", "requestData":{"inputName": "Mic/Aux", "inputVolumeMul": '
                        + volume
                        + "}}}"
                    )
                line = []
                break


asyncio.get_event_loop().run_until_complete(main())
asyncio.get_event_loop().run_forever()

ser.close()
