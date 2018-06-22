from flask import Flask, render_template, request
from flask_socketio import SocketIO
from threading import Thread

import requests
import serial
import time
import datetime

port = "COM11"
baud = 115200
ser = serial.Serial(port, baud, timeout=None)

#Creating a log file under logs folder with the name "log-date.txt"
log_file_name = 'logs/log-' + str(datetime.date.today()) + '.txt'

#Flask and SocketIO initilization
app = Flask(__name__)
socketio = SocketIO(app)

#Dictionary with the data of all the nodes in real time
all_nodes_data = {
    0: [0, '000', 0, time.time(), datetime.datetime.now()],  # master node
    1: [1, '303', 0, time.time(), datetime.datetime.now()],
    2: [2, '303', 0, time.time(), datetime.datetime.now()],
    3: [3, '303', 0, time.time(), datetime.datetime.now()],
    4: [4, '303', 0, time.time(), datetime.datetime.now()],

    5: [5, 'Temperature', 22.23, time.time(), datetime.datetime.now()],
    # [node_number, room_number, state, timestamp in Unix format, timestamp]
}

sample_packet = '000-11.12\n'

#Send a string to the master node
def send_to_master(string):
    if ser.isOpen():
        for char in string:
            # print "Sent character: " + char
            ser.write(char)
    else:
        print "Send-Serial not open!"

#Get the string from serial communication
def read_from_master(timeout_at=1):
    received = None #Default string if nothing is received
    timeout_time = time.clock() + timeout_at
    if ser.isOpen():
        loop_time = time.clock()
        while ser.in_waiting == 0 and loop_time < timeout_time:
            loop_time = time.clock()
        if loop_time > timeout_time:
            pass
            print "timeout!"
        else:
            received = ser.readline()
            print "Received: " + received

    else:
        print "Read-Serial not open!"

    return received

#Establish the connection with node
def establish_connection():
    while True:
        if ser.in_waiting > 0 :     #If data available on serial
            received = read_from_master()   #Get the string
            if received == 'Sync\n':        #If "Sync is received this from node"
                send_to_master('A')         #Node accepts this and starts
                break


@app.route('/', methods=['GET', 'POST'])
def index():
    return render_template('/WebGUI.html')


@socketio.on('event_response')
def transmit_to_GUI(data):
    socketio.emit('event_response', data, broadcast=True)
    print "Sent to GUI!: ", data

#Read data from serial and send to GUI
def read_and_transmit_to_GUI():
    while True:
        received_string = read_from_master()
        print received_string

        if received_string is None: #Default string if nothing is received
            continue

        #Parse string: sample_packet = '000-0\n' (node number-received state)
        if len(received_string) == len(sample_packet) and received_string[3] == '-':
        #if True:
            node_number, temperature = received_string.split('-')    #Split received data into node number and temperature

            print "Node number: " + node_number + ", Temperature: " + temperature

            node_number = int(node_number)
            temperature = float(temperature)

            print "Node number: " + str(node_number) + ", Temperature: " + str(temperature)

            node_data = all_nodes_data[node_number] #Select which node
            # node_data = [node_number, room_number, state, timestamp in Unix format, timestamp]

            #node_data[2] = temperature   #State of the selected node
            #node_data[3] = time.time()  #Time since start of program
            #node_data[4] = datetime.datetime.now()  #Date and Time of update(current time and date)

            #all_nodes_data[node_number] = node_data     #Update the data

            #transmit_to_GUI(node_data[0:4])

            #Write data to log file
            #with open(log_file_name, 'a') as log_file:
            #    log_file.write('Room: ' + str(node_data[1]) + ', Node number: ' + str(node_data[0]) + ', ' + str(node_data) + '\n')

#Establish_connection with master and then move ahead
establish_connection()
print "connection with master established!"


if __name__ == '__main__':
    read_and_transmit_to_GUI()

    '''
    loop_thread = Thread(target=read_and_transmit_to_GUI)
    loop_thread.setDaemon(True)

    loop_thread.start()

    socketio.run(app)
    '''