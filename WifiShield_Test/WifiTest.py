# -*-coding:utf-8 -*-

import socket

HOST = '192.168.0.208' #아두이노에 연결된 라즈베리파이의 ip
PORT = 9090 #통신 포트

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #소켓 TCP 설정

sock.bind((HOST,PORT))

print("server wait......")

sock.listen(1) #접속 기다림
conn, addr = sock.accept() #접속 승인
print(addr) #연결된 IP와 포트

while True:
        data = conn.recv(1024) #데이터 수신
        print(data)

conn.close()