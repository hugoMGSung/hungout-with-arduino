import serial
import threading
import time
import paho.mqtt.client as mqtt
from threading import Thread, Timer
import datetime as dt
import json

ser = serial.Serial(port='/dev/ttyACM0',
                    baudrate=9600,
                    timeout=1)

line = ''

dev_id = 'IOT_SH'
broker_ip = '192.168.45.190' # '210.119.12.52'
mqttc = None 

def on_connect(mqttc, obj, flags, reason_code, properties):
    print("reason_code: " + str(reason_code))


def on_message(mqttc, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))


def on_publish(mqttc, obj, mid, reason_code, properties):
    print("mid: " + str(mid))


def on_log(mqttc, obj, level, string):
    print(string)


def readThread(ser):
    global line
    global mqttc

    # 스레드 종료될때까지 계속
    while True:
        line = ser.readline().decode('utf8').rstrip()
        if line.startswith('[') and line.endswith(']'):
            print('FROM ARDU=' + line)
            # line을 읽어서 분리
            baseData = dataToDict(line)
            # print(baseData)
            mqttc.publish("pknu/sh01/data", json.dumps(baseData), qos=2)
            line = ''

def dataToDict(line):
    originData = {}
    temps = line.replace('[', '').replace(']', '').split('|')
    # print(type(temps))
    for item in temps:
        middles = item.split(':')
        originData[middles[0]] = middles[1]

    return originData

def main():
    global mqttc
    mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.on_publish = on_publish

    mqttc.connect(broker_ip, 1883, 60)
    mqttc.loop_start()

    thread = threading.Thread(target=readThread, args=(ser,))  # 시리얼 통신받기
    thread.start()
    ser.flush()

    while True:
        data = '[FROM_RPI]'
        ser.write(data.encode())
        time.sleep(1)


if __name__ == '__main__':
    main()