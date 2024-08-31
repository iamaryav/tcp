import socket


def tcp_client():
    host = socket.gethostname()
    port = 20001 # port where server is listening/Running
    bufferSize = 1024

    client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    client_socket.connect((host, port))

    message = input("-> ")

    while message.lower().strip() != "close":
        client_socket.send(message.encode())
        data = client_socket.recvfrom(bufferSize)
        message = data[0]

        print(f"Received From server: {message}")

        message = input("-> ")
    client_socket.close()


if __name__ == '__main__':
    tcp_client()
