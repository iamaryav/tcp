import socket

def tcp_server():
    host = socket.gethostname()
    ip = socket.gethostbyname(host)
    port = 20001
    buffer_size = 1024
    print(f"Host: {host}, IP: {ip}, Port: {port}")

    # Configuring socket
    server_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(2) # Client server can listen simultaneuously
    conn, address = server_socket.accept() #Accepts new connection
    print("Accepting connection from: " + str(address))

    while True:
        data = conn.recv(buffer_size).decode()
        if not data:
            # if no data received break the connection
            break
        print(f"From user: -> {data}")

        data = input("-> ")
        conn.send(data.encode()) #send data to the client
    conn.close()



if __name__ == '__main__':
    tcp_server()
