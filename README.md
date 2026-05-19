`#ff __Still in Developing - Not finish__

# Versatron
Der Name ist ein Acronym das Ausgeschrieben __Versatile Training Electronic Node__ heißt und übersetzt im Deutschen für Vielseitig, Training und Elektronik-Knoten.
<img width="1600" height="900" alt="grafik" src="https://github.com/user-attachments/assets/8e6e77a3-fdb1-4827-8fd8-9b9f1aee7ac4" />
<img width="1600" height="900" alt="grafik" src="https://github.com/user-attachments/assets/faec482a-1be3-4321-8a94-b8e1a5f749be" />


### Wofür?
Der Praktische Nutzen liegt in der Übung sich mit der Hardware und den Schnittstellen auseinander zu setzen. 
Zusätzlich in die Programmiersprache C++ weiter zu bilden, daher ist der Code nicht mit KI Generiert. Jedoch nutze ich KI als Unterstützung, um mehr über die C++ Syntax und Abhängigkeit in erfahrung zu bringen.
Die Ursprungsidee war, ein kleines Gerät zu bauen, dass nur als Hilfsmittel für meine Sportlichen Aktivitäten mit Workout zu Kordinieren. Man könnte auch das Smartphone und eine entsprechende App verwenden, aber dann würde ich nicht lernen, was ich bei der Entwicklung einer Workout Anwendung brauche.

### Anwendungsideen
* Workout Helper
* Camera (Einfache Kamera Entwicklung)
* Picture Viewer (Damit man die erstellten Bilder mit der Camera ansehen kann)
* WiFi Scanner (Nur auflisten, welche WLANs in der Umgebung empfangbar sind)
* Bluetooth Scanner (Nur auflisten, welche oder Anzahl Bluetooth Geräte in der Umgebung)
* Sense (Sensoren wie Temperatur, Feuchtigkeit, Luftdruck und weitere Sensoren. Idee ist eine Sensor Array zu bauen, dass über Bluetooth mit dem Versatron verbunden wird.)

### Gehäuse Entwurf
Das Gehäuse habe ich unüblicherweise in Blender Moduliert. 
Die fertigen STL Dateien habe ich noch nicht veröffentlicht, da noch nicht alle Teile ihre endliche Form haben. An einigen Stellen kann sich das Gehäuse noch zu sehr verformen oder Komponenten wirken noch wackelig angebracht.
<img width="720" height="609" alt="grafik" src="https://github.com/user-attachments/assets/8add1af7-3133-4231-b632-970e730927a4" />
<img width="720" height="609" alt="grafik" src="https://github.com/user-attachments/assets/dd7ab049-98e8-462c-8011-67ed10302647" />

### Elektronik
Für die Verkabelung reichen dünne Leitungen, um die Komponenten mit einander zu verbinden.
Folgende Teile verwende ich:
* ESP32-S3 Sense (Ist mit Kamera und SD Karten Slot)
* 2x Potitiometer
* 3x Buttons
* 1x Antenne
* Rundes TFT Display 240x240 (GC9A01)
Eigentlich war gedacht, noch Sensoren einzubringen über die Schnittstelle I²C, jedoch sind aktuell keine Pins mehr frei. Hier evaluiere ich noch, ob für SPI der Pin für CS und Reset wirklich gebraucht werden.
<img width="1600" height="900" alt="grafik" src="https://github.com/user-attachments/assets/03b0929d-b26b-428c-bb3d-2f76c28787e7" />
