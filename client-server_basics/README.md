# TCP Client-Server Calculator in C

## Project Overview

This project implements a simple TCP client-server application in C where a client sends arithmetic operations to a server, and the server computes the result and sends it back. The focus is on understanding basic socket programming, request-response communication, and process interaction over TCP/IP.

The server listens on a TCP port, accepts a client connection, receives an operation and two operands, computes the result, and returns it to the client. The client reads input from the user, sends the request to the server, and displays the response.

---

## Features

- TCP socket communication using IPv4 (`AF_INET`) and streaming sockets (`SOCK_STREAM`)
- Basic calculator operations:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`) with simple division-by-zero handling
- Interactive client:
  - User enters operation and two numbers (e.g. `+ 2 3`)
  - Special operation `q` to quit the client
- Graceful error handling and informative console messages
- Easily extendable to support additional operations

---

## Project Structure

| File       | Description                                   |
|-----------|-----------------------------------------------|
| `server.c`| TCP server implementation (calculator logic)  |
| `client.c`| TCP client implementation (user interface)    |

You can keep both files in the same folder for simplicity.

---

## How It Works

### Server

- Creates a TCP socket and binds it to port `8080`.
- Enables address reuse with `SO_REUSEADDR` to avoid “address already in use” when restarting quickly.
- Listens for incoming connections and accepts a single client.
- In a loop:
  - Receives a string request from the client.
  - Parses the request in the format:  
    `<operation> <operand1> <operand2>`  
    e.g. `+ 2 3`
  - Performs the calculation.
  - Sends the result back to the client as a string.

### Client

- Creates a TCP socket.
- Connects to the server (default: `127.0.0.1:8080`).
- In a loop:
  - Asks the user to input: operation and two numbers.
  - Sends the request string to the server.
  - Waits for the response and prints the result.
  - Exits when the operation entered is `q` or `Q`.

---

## Build and Run (Same Machine)

Requirements:
- GCC or another C compiler
- A terminal (Linux, macOS, WSL, or similar)

### 1. Compile

```bash
gcc -Wall -Wextra -O2 -o server server.c
gcc -Wall -Wextra -O2 -o client client.c
```

### 2. Run the Server

Open a first terminal:

```bash
./server
```

Expected output (example):

```bash
Server listening on port 8080...
Client connected.
```


### 3. Run the Client

Open a second terminal in the same directory:

```bash
./client
```

Example interaction:

```bash
Connected to server on 127.0.0.1:8080
Operations: + - * /
Type 'q' as operation to quit.

Enter operation and two numbers (e.g. + 2 3): + 2 3
Result from server: 5.0000

Enter operation and two numbers (e.g. + 2 3): * 10 4
Result from server: 40.0000

Enter operation and two numbers (e.g. + 2 3): q
Exiting client.
```


---

## Running on Different Machines

This project also works when the server and client run on different machines, as long as there is network connectivity between them (same local network, VPN, etc.).

### 1. On the Server Machine

1. Find the server machine IP address (on the same network):
   - Linux/macOS:
     ```
     ip addr    # or: ifconfig
     ```
   - Windows (PowerShell/CMD):
     ```
     ipconfig
     ```
2. Identify the IPv4 address (e.g. `192.168.0.10`).

3. Start the server:

```bash
./server
```

Make sure:
- Port `8080` is allowed in the firewall, or temporarily disabled for testing.
- The server is listening on `INADDR_ANY` (already implemented), so it accepts connections from any interface.

### 2. On the Client Machine

In `client.c`, change the line where the server IP is set:

```c
// Original:
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

// Change "127.0.0.1" to the server's LAN IP, e.g.:
inet_pton(AF_INET, "192.168.0.10", &serv_addr.sin_addr);
```

Recompile the client on the client machine (gcc -Wall -Wextra -O2 -o client client.c)and then run './client'.


Now all operations sent from the client machine are processed by the server machine over the network.

Note:
- Ensure both machines are on the same network and able to reach each other (e.g. ping the server from the client).
- On some systems, you may need to open port 8080 in the OS firewall.

---

## Protocol Format

The basic text protocol between client and server is:

- Request (from client to server):
  - A line of text:  
    `<operation> <operand1> <operand2>`
  - Example:  
    `+ 2 3`

- Response (from server to client):
  - A line of text containing the result (or an error message):  
    `5.0000`  
    or  
    `Invalid format. Use: <op> <num1> <num2>`

This simple text-based protocol makes the system easy to test and debug.

---

## What I Learned

Building this project helped practice:

- Basic socket programming in C:
  - `socket`, `bind`, `listen`, `accept`, `connect`, `read`, `send`, `close`
- TCP/IP fundamentals and client-server interaction
- Simple text-based application protocols
- Error handling and resource management in network programs
- Separating computation logic (the calculator) from communication logic (sockets)

---

## Possible Improvements

- Support additional operations (exponentiation, modulo, etc.)
- Handle division by zero with proper error responses
- Allow multiple concurrent clients (using `fork`, `pthread`, or `select`)
- Add a simple menu-based client UI
- Add TLS/SSL encryption for secure communication
- Create a Makefile for easier build automation

---

## Author

Paulo Fonseca  
Information Systems student, Universidade Federal de Uberlândia  
GitHub: [github.com/paulo-fonseca28](https://github.com/paulo-fonseca28)


