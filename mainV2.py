# -*- coding: utf-8 -*-
import time
import MFRC522
import signal
import sys
from coapthon.client.helperclient import HelperClient
from subprocess import call

nonstop = True

def stop_node(signal,frame):
    global nonstop
    print "Terminando...\n"
    nonstop = False
    #stop ultrasonic
    #stop servo
    GPIO.cleanup()
    print "Finalizado!\n"

def main():
    argc = len(sys.argv)

    if argc != 3:
        print("Esse script funciona com 2 argumentos: <host> <port>\n")
        print("<host>: endereço IP do servidor\n")
        print("<port>: porta do servidor\n")
        exit(1)

    host = sys.argv[1]
    port = int(sys.argv[2])

    signal.signal(signal.SIGINT, stop_node)

    call(['./src/piio/build/ultrasonic', 'reset', '23', '24'])

    print ("Iniciando sensor ultrassônico...\n")
    return_val = call(['./src/piio/build/ultrasonic', 'setup', '23', '24'])

    print (return_val);
    # ultrasonic_setup()

    # servo_setup()
    # servo_set_angle(0)


    time.sleep(2)

    print "Pressione Ctrl-C para terminar.\n"

    allowed = False

    while nonstop:
        distance1 = call(['./src/piio/build/ultrasonic', 'read', '23', '24'])
        print (distance1+'\n')


# script
main()
