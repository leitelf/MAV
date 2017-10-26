import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

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



#RFID pinouts

TRIG1 = 23 #pin 16
ECHO1 = 24 #pin 18

TRIG2 = 14 #pin 8
ECHO2 = 15 #pin 10

MOTOR = 16 #pin 36

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



while True:

    distance1 = getDistance(TRIG1, ECHO1)
    distance2 = getDistance(TRIG2, ECHO2)

    if (distance1 < 20.0) and (distance2 < 20.0):
        print "Car Waiting"
        setAngle(0, MOTOR, PWM) #open
        time.sleep(10)
        setAngle(90, MOTOR, PWM) #close
    else:
        print "No car waiting"

GPIO.cleanup()
