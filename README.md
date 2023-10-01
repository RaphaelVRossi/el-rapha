# El Rapha

A diy stream deck project using arduino UNO and [edu-ifsp shield](https://embarcados.com.br/shield-edu-ifsp/)

using [obs-websocket](https://github.com/obsproject/obs-websocket)

## Installation

```sh
make setup
```

## Running

### Websocket Server

```sh
make run-server
```

or 

```sh
python web-socket-server.py $(ls /dev/tty.* | grep serial) ws://localhost:4444
```

