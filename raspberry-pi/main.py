# Servo motor
from gpiozero import Servo
import time
import time
# Communication over the internet
import requests
import json


def getCatWeight():
    # value returns 0 eller 1 according to documentation
    # when it should return an analog value
    # maybe arduino with WiFi shield should be used
    return weight.value


servo = Servo(12)
weight = InputDevice(6)
# remember to change code
url = 'localhost:8080/CODE/weight'

print("Programmet kører")

while True:
    # test of servo
    # servo should only run according to the settings set on website
    servo.min()
    sleep(1)
    servo.mid()
    sleep(1)
    servo.max()
    sleep(1)

    # if cat is on weight
    print("Katten er registreret til at være på vægten.")
    catWeight = getCatWeight()
    print("Katten vejer {}.".format(catWeight))
    dataMessage = {"weight": catWeight, "time": time.time()}
    x = requests.post(url, dataMessage)
    print("Dataen er sendt til serveren (forhåbentligt).")
    print(x.text)
