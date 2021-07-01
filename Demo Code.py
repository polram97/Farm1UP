import requests
from bs4 import BeautifulSoup
import time

#Initial code
#This code try to get the weather information and use it to make a prediction

ciudad = input("Ingrese la ciudad: ")
busqueda = "weather in " + ciudad
URL = f"https://www.google.com/search?q={busqueda}"
while True:
    #bm = "weather in " + ciudad + "tomorrow"
    #URLm = f"https://www.google.com/search?q={bm}"

    req = requests.get(URL)
    sav = BeautifulSoup(req.text, "html.parser")

    #reqm = requests.get(URLm)
    #savm = BeautifulSoup(reqm.text, "html.parser")

    update = sav.find("div", class_="BNeawe").text
    #updatem = savm.find("div", class_="BNeawe").text

    print("La temperatura es de: " + update)
    time.sleep(30)
