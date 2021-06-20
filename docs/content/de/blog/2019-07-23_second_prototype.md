+++
title = "Der zweite Prototyp"
subtitle = ""
date = 2019-07-23

description = "Aufbau und Funktionsweise des zweiten Prototypes"
banner = ''
[[pic]]
  url = "/img/prototype_2/prototype_vertical.jpg"
  label = "Gesamtansicht"
  height = "250px"
[[pic]]
  url = "/img/prototype_2/prototype_backside.jpg"
  label = "Rückseite der Platine"
  height = "250px"
[[pic]]
  url = "/img/prototype_2/prototype_horizontal_use_case.jpg"
  label = "Möglicher Anwendungsfall"
  height = "250px"
[[pic]]
  url = "/img/prototype_2/prototype_waves_on_display.jpg"
  label = "Anzeige der Rohdaten auf dem Display"
  height = "250px"
+++

Der zweite Prototyp arbeitet mit dem selben Piezo-Wandlern, allerdings wurden die Schaltungen für 
die Signalerzeugung und -verstärkung mit Hile von Thomas XXXX, einem pensionierten Elektrotechnisker überarbeitet. 
Es wurde ebenfalls ein Bildschirm und ein leistungsstarker Teensy 4.0 Microcontroller verbaut.
Da dieser über einen 1MSP/S ADC verfügt, können die 40kHz Schallwellen nun abgenommen und digital verarbeitet werden.


Der Prototyp ist in der Lage Schallwellen von 40kHz zu erzeugen, in das Material einzubringen, dann wieder abzunehmen, analog zu verstärken und anschließend auf einem kleinen Display anzuzeigen.

Es fehlt aber noch ein vernünftiges Bewertungsverfahren, welches die abegommenen Schallwellen auswertet. Dabei muss berücksichtigt werden, dass die die Piezos mit der Hand an das Werkstück gehalten werden und die Ergebnisse somit je nach Anpressdruck und -winkel mitunter stark variieren. Gleichzeitig sind die verwendeten Piezos vermutlich nicht die optimale Wahl für die beschriebene Anwendung, es konnten allerdings keine
passenderen Elemente mit dem zur Verfügung stehenden Budget organisiert werden. Es stellt sich außerdem die Frage ob sich 40kHz als Frequenz zur Durschschallung von Feststoffen eignet.
Außerdem muss ein Weg gefunden Werten, einen Piezo Treiber zu betreiben, der möglichst Hohe Spannungsamplitunden liefern, gleichzeitig aber mit einem 5V Akku bereiben werden kann, 