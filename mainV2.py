# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO
import time
import MFRC522
import signal
import sys
from coapthon.client.helperclient import HelperClient
from subprocess import call

nonstop = True

def stop_node (signal,frame):
    global nonstop
    print "Terminando...\n"
    nonstop = False
    #stop ultrasonic
    #stop servo
    GPIO.cleanup()
    print "Finalizado!\n"

def open_gate () :
    print ('Abrindo portão...\n')
    call(['./src/piio/build/servo', 'rotate', '90'])
    time.sleep(3)
    print ('Fechando portão...\n')
    call(['./src/piio/build/servo', 'rotate', '0'])

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
    GPIO.cleanup()

    call(['./src/piio/build/ultrasonic', 'reset', str(trig1), str(echo1)])
    call(['./src/piio/build/ultrasonic', 'reset', str(trig2), str(echo2)])
    call(['./src/piio/build/servo', 'reset'])



    #setup sensors/actuators
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

    print ('Iniciando RFID...\n')
    MIFAREReader = MFRC522.MFRC522()

    call(['./src/piio/build/servo', 'rotate', '0'])

    time.sleep(1)
    allowed = False

    print ('Iniciado.Pressione Ctrl-C para terminar.\n')

    while nonstop:

        (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)

        if status == MIFAREReader.MI_OK:
            print ('RFID detectado...\n')
            (status,uid) = MIFAREReader.MFRC522_Anticoll()
            if status == MIFAREReader.MI_OK:
                key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]
                MIFAREReader.MFRC522_SelectTag(uid)

                status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)

                if status == MIFAREReader.MI_OK:
                    MIFAREReader.MFRC522_Read(8)
                    MIFAREReader.MFRC522_StopCrypto1()

                    client = HelperClient(server=(host, port))
                    payload = str(uid[0])+"."+str(uid[1])+"."+str(uid[2])+"."+str(uid[3])
                    path = '/rfid'

                    response = client.put (path, payload)

                    client.stop ()

                    if response.payload == '1':
                        print ('RFID conhecido...\n')
                        open_gate ()

                    if response.payload == '0':
                        print ('RFID não conhecido...\n')


        distance1 = call(['./src/piio/build/ultrasonic', 'read', str(trig1), str(echo1)])
        distance2 = call(['./src/piio/build/ultrasonic', 'read', str(trig2), str(echo2)])
        if (distance1 < 20.0) and (distance2 < 20.0):
            print ('Carro detectado...\n')

            print ('Capturando imagem...\n')
            #capturar imagem
            client = HelperClient(server=(host, port))
            payload = 'updated'
            path = '/img'
            response = client.put (path, payload)
            client.stop ()

            open_gate ()

# script
main ()
