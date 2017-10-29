import RPi.GPIO as GPIO
import time
import MFRC522
import signal

GPIO.setmode(GPIO.BOARD)

nonstop = True

def stop_node(signal,frame):
    global nonstop
    print "Ctrl+C captured, ending read."
    nonstop = False
    GPIO.cleanup()

def getDistance(trig, echo):
    GPIO.output(trig, True)
    time.sleep(0.00001)
    GPIO.output(trig, False)
    while GPIO.input(echo)==0:
        pulse_start = time.time()

    while GPIO.input(echo)==1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    distance = pulse_duration * 17150
    distance = round(distance, 2)

    return distance

def setAngle(angle, pin, pwm):
    duty = angle/18 + 2
    GPIO.output(pin, True)
    pwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(pin, False)
    pwm.ChangeDutyCycle(0)


signal.signal(signal.SIGINT, stop_node)

MIFAREReader = MFRC522.MFRC522()


#RFID pinouts

TRIG1 = 16 #pin 16, GPIO 23
ECHO1 = 18 #pin 18, GPIO 24

TRIG2 = 8 #pin 8, GPIO 14
ECHO2 = 10 #pin 10, GPIO 15

MOTOR = 36 #pin 36, GPIO 16

GPIO.setup(TRIG1, GPIO.OUT)
GPIO.setup(TRIG2, GPIO.OUT)

GPIO.setup(ECHO1, GPIO.IN)
GPIO.setup(ECHO2, GPIO.IN)

GPIO.setup(MOTOR, GPIO.OUT)

PWM=GPIO.PWM(MOTOR, 50)
PWM.start(0)

setAngle(90, MOTOR, PWM)

GPIO.output(TRIG1, False)
GPIO.output(TRIG2, False)

time.sleep(2)


print "Press Ctrl-C to stop."

allowed = False

while nonstop:

    #allowed = checkRFID(getRFID())
    (status,TagType) = MIFAREReader.MFRC522_Request(MIFAREReader.PICC_REQIDL)

    if status == MIFAREReader.MI_OK:
        print "Card detected"

    (status,uid) = MIFAREReader.MFRC522_Anticoll()

    if status == MIFAREReader.MI_OK:
        print "Card read UID: "+str(uid[0])+","+str(uid[1])+","+str(uid[2])+","+str(uid[3])
        # This is the default key for authentication
        key = [0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]

        # Select the scanned tag
        MIFAREReader.MFRC522_SelectTag(uid)

        # Authenticate
        status = MIFAREReader.MFRC522_Auth(MIFAREReader.PICC_AUTHENT1A, 8, key, uid)

        # Check if authenticated
        if status == MIFAREReader.MI_OK:
            MIFAREReader.MFRC522_Read(8)
            MIFAREReader.MFRC522_StopCrypto1()
            #send uid to server
            #server return if is valid

            #for test
            if uid[0] == 192:
                allowed = True
        else:
            print "Authentication error"


    if allowed:
        setAngle(0, MOTOR, PWM) #open
        time.sleep(8)
        setAngle(90, MOTOR, PWM) #close
        allowed = False

    distance1 = getDistance(TRIG1, ECHO1)
    distance2 = getDistance(TRIG2, ECHO2)

    if (distance1 < 20.0) and (distance2 < 20.0):
        print "Car Waiting"
        #if !allowed
            #getPicture
            #sendToServer

        setAngle(0, MOTOR, PWM) #open
        time.sleep(6)
        setAngle(90, MOTOR, PWM) #close
    else:
        print "No car waiting"
