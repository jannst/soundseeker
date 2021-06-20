+++
title = "Der erste Prototyp"
subtitle = ""
date = 2017-08-01

description = "Kurze Beschreibung des ersten Prototypen mit Erläuterung der Arbeitsweise"
banner = ''

[[pic]]
  url = "/img/prototype_1/prototype_1.jpg"
  label = "Gesamtansicht"
  height = "250px"

[[pic]]
  url = "/img/prototype_1/prototype_1_inside.jpg"
  label = "Innenansicht"
  height = "250px"
[[pic]]
  url = "/img/prototype_1/prototype_1_use_case.jpg"
  label = "Messung der Schallgeschwindigkeit in Cello Deckenholz"
  height = "250px"
[[pic]]
  url = "/img/prototype_1/prototype_1_horizontal.jpg"
  label = "Gesamtansicht"
  height = "250px"
+++

Der erste Prototyp ist ein Nachbau, des [Luccimeters](https://www.lucchimeter.com/), welches zur Zeit 
bei F.W. Geigenbu in Bremen im Einsatz ist. Dort  wird es zur Vermessung von Bogen- und Geigenholz genutzt. 


Es verfügt über 2 40kHz Piezo-Elemente, welche den Ultraschall in das Material einbringen und wieder abnehmen. Das Signal wird dann verstärkt und
durch einen Atmega-8 Microcontroller wird ausgewertet, wie lang der Schall benötigt hat um das Material zu durchqueren.
Zusammen mit der eingegebenen Länge wird die Schallgeschwindigkeit im Material gemessen. 