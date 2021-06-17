import socket
from _thread import*
host = '127.0.0.1'
port = 8080
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
try:
    s.bind((host, port))
    print ('Connected ....')
except socket.error as msg:
    print ('Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1])
    exit()

s.listen(5)

def handle_client (conn1 , addr1):

    while True:
         msg = conn1.recv(1024).decode()
         
         if not msg or msg == 'close':
             print('Lost connection with client', addr1)
             conn1.close()

         else:
            print('client 1  %s says' % str(addr1), msg)
            if msg == 'up1':
                conn1.send(str.encode('UP'))
                print("Sent UP")

            elif msg == 'down1':
                conn1.send(str.encode('DOWN'))

            elif msg == 'right1':
                conn1.send(str.encode('RIGHT'))

            elif msg == 'left1':
                conn1.send(str.encode('LEFT'))

            else:
                continue


print ('Listening for incoming connections...')

while True:
    conn1, addr1 = s.accept()
    print('client1', addr1, 'has been connected')

    start_new_thread(handle_client, (conn1, addr1), )


