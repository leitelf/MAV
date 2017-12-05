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

    trig1 = 23
    echo1 = 24

    trig2 = 27
    echo2 = 22
    #stop GPIOs useds
    call(['./src/piio/build/ultrasonic', 'reset', str(trig1), str(echo1)])
    call(['./src/piio/build/ultrasonic', 'reset', str(trig2), str(echo2)])
    call(['./src/piio/build/servo', 'reset'])

    print ('Iniciando sensor ultrassônico...\n')
    if 1 != call(['./src/piio/build/ultrasonic', 'setup', str(trig1), str(echo1)]) :
        print ('Falha ao iniciar ultrassônico 1.\n')
        return -1
    if 1 != call(['./src/piio/build/ultrasonic', 'setup', str(trig2), str(echo2)]) :
        print ('Falha ao iniciar ultrassônico 2.\n')
        return -1

    print ('Iniciando motor servo...\n')
    if 1 != call(['./src/piio/build/servo', 'setup']) :
        print ('Falha ao iniciar motor servo.\n')
        return -1

    time.sleep(1)
    allowed = False

    print ('Iniciado.Pressione Ctrl-C para terminar.\n')

    while nonstop:
        distance1 = call(['./src/piio/build/ultrasonic', 'read', str(trig1), str(echo1)])
        distance2 = call(['./src/piio/build/ultrasonic', 'read', str(trig2), str(echo2)])
        if (distance1 < 20.0) and (distance2 < 20.0):
            print ('Carro detectado...\n')
            print ('Capturando imagem...\n')
            #capturar imagem

            print ('Abrindo portão...\n')
            call(['./src/piio/build/servo', 'rotate', '90'])
            time.sleep(3)
            print ('Fechando portão...\n')
            call(['./src/piio/build/servo', 'rotate', '0'])

# script
main()
