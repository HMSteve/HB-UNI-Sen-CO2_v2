# HB-UNI-Sen-CO2 - Version 2

![HB-UNI-Sen-CO2](https://github.com/HMSteve/HB-UNI-Sen-CO2/blob/main/Images/dev_front.jpg)

Eine Erweiterung meines AskSinPP-basierten [Innenraum-CO2-Sensor](https://github.com/HMSteve/HB-UNI-Sen-CO2).
Die neue Version kann neben dem Sensirion SCD30 nun auch den Sensirion SCD41 nutzen. Vorteil ist eine deulich verlaengerte Betriebszeit mit einer Akkuladung von mind. einem Monat.

Auf Grund der jedoch deutlich hoeheren Spitzenstromaufnahme des SCD41 ist ein anderer Step-Up-Wandler (MCP1640) und damit eine neue Platine notwendig. Gehaeuse, CCU-Addon-Version und Bedienung sind gegenueber der Ursprungsversion unveraendert. Damit gelten die entsprechenden Informationen in der Dokumentation zu dieser Version weiterhin.


## Platine

Auf der Platine sind drei I2C-Steckplaetze fuer Sensoren vorgesehen. Neben dem [Sensirion SCD30](https://sensirion.com/products/catalog/SCD30/) bzw. [SCD41](https://sensirion.com/products/catalog/SCD41/) bietet sich ein moeglichst 4-poliges, notfalls auch 6-poliges BME280- oder BMP280-Modul zur Luftdruck-Kompensation an. Der Drucksensor ist auch in der Firmware vorgesehen. Der dritte Steckplatz ist aktuell frei.
Als Display findet ein [1.54" Waveshare-E-Paper-Modul](https://www.waveshare.com/1.54inch-e-Paper-Module.htm) Verwendung.

[Schaltplan](https://github.com/HMSteve/HB-UNI-Sen-CO2_v2/blob/main/PCB/HB-Uni-Sen-CO2_v2_Schematic.pdf)

Zum Schutz vor dem Auftreten einer Reset-Schleife in Foge der hohen Einschaltstromspitze der Peripherie des Controllers (CC1101 und SCD41) muss der zum Schalten genutzte MOSFET etwas "gebremst" werden. Das fiel leider erst nach Herstellung der Platine v2 auf, kann aber leicht gemaess

![Schaltplan v2.1](https://github.com/HMSteve/HB-UNI-Sen-CO2_v2/blob/main/PCB/HB-Uni-Sen-CO2_v2p1_Schematic.pdf)

oder an Hand des Fotos

![diesem Foto](https://github.com/HMSteve/HB-UNI-Sen-CO2_v2/blob/main/Images/pcb_bott_corr.jpg)

mittels 10nF-Kondensator C19 (1), 100k-Widerstand R29 (2) und Lackdrahtbruecke (3) korrigiert werden.

Fuer den SCD41 ist das entsprechende [Breakout-Board](SCD41_Breakout_v1_TopPlace.pdf) zu nutzen. Dessen Loetung ist nur per reflow, jedoch ohne Probleme mit Heissluft oder Buegeleisen von unten moeglich. Eine Schablone zur Pastenauftrag bietet sich jedoch an.

![PCB mit Breakout](https://github.com/HMSteve/HB-UNI-Sen-CO2_v2/blob/main/Images/pcb_incl_breakout.jpg)


## Software

### Addon zur Geraeteunterstuetzung

Sofern noch nicht vorhanden oder nicht aktuell, ist das [Addon](https://github.com/HMSteve/SG-HB-Devices-Addon/raw/master/CCU_RM/sg-hb-devices-addon.tgz) auf der CCU zu installieren. Der Sensor benoetigt mindestens Version 1.23.

### Firmware

Es wird ein ATMega1284p verwendet, da der Speicherplatz des ATMega328p nicht ausreicht. Deshalb ist bei Nutzung der Arduino IDE zunaechst eine zusaetzliche sog. Boardverwalter-URL (https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json) in den Voreinstellungen zu hinterlegen. Folgende Boardeinstellungen sind dann auszuwaehlen:

![Boardeinstellungen](https://github.com/HMSteve/HB-UNI-Sen-CO2/blob/main/Images/arduino_board_config.jpg)

Danach kann der Bootloader geflashed werden.

Um die Firmware zu kompilieren, muessen sich die .ino sowie die .h Dateien im gleichen Verzeichnis befinden, das ./sensors-Verzeichnis darunter. Zudem muss eine Reihe von Bibliotheken ueber den Library Manager eingebunden werden:
- AskSinPP
- EnableInterrupt
- LowPower
- SparkFun SCD30 Arduino Library bzw. SparkFun SCD4x Arduino Library
- Adafruit BME280 Library
- GxEPD
- Adafruit GFX

Bei neueren Versionen des verwendeten Displays sind Inkompatibilitaeten mit der GxEPD-Implementierung zu beobachten. Das Display wird im Zeitverlauf immer blasser und letztlich unlesbar. Dieser [Fix](https://github.com/ZinggJM/GxEPD/pull/82) loest das Problem.

Die Pindefinitionen im Sketch sind je nach verwendeter Platine ggf. anzupassen und mittels der #defines am Anfang der genutzte Sensor auszuwaehlen.

Anschliessend sollte die Firmware problemlos kompilierbar und das Device nach dem Flashen anlernbar sein.


## Bedienung

Die Bedienung ist in der [ersten Projektversion](https://github.com/HMSteve/HB-UNI-Sen-CO2) beschrieben.


## Gehaeuse

Es wird das Gehaeuse der [ersten Projektversion](https://github.com/HMSteve/HB-UNI-Sen-CO2) verwendet.


## Disclaimer

Die Nutzung der hier veroeffentlichten Inhalte erfolgt vollstaendig auf eigenes Risiko und ohne jede Gewaehr.


## Lizenz

**Creative Commons BY-NC-SA**<br>
Give Credit, NonCommercial, ShareAlike

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
