+++
title = "Über das Projekt"

type = "blog"
+++

## Problemstellung
Beim Bau eines Holzmusikinstrumentes muss Holz ausgewählt werden, dessen Materialeigenschaften besitzt, de sich positiv auf die akustische Qualität auswirken.
Im Holzhandel müssen somit aus einer Vielzahl von verschiedener Stücken, einige passende auszuwählt werden.
Um die Besten Stücke zu identifizieren, haben sich über die Jahre verschiedene Heuristiken entwickelt. Relativ bekannt sind verschiedene
"Klopftests", bei denen ein Stück Holz z.B. zwischen zwei Fingern an einem Schwingungsknoten einer Eigenmode gehalten 
und mit der Hand "angeklopft" wird. Der vom Holz abgestrahlte Klang wird dann anhand der gewonnenen Erfahrung subjektiv bewertet.
Das "geschulte Ohr" ist dann in der Lage, eine Bewertung über die Eignung des Holzes für den Instrumentenbau zu liefern.

Auch bei der Ausarbeitung des Materials ist es wichtig, darauf zu achten, dass später ein akustsich gutes Instrument entsteht. 
So ist bei Gitarren und Streichinstrumenten die Ausarbeitung der Materialstärken der Decke und deren Bebalkung von essenzieller Bedeutung. https://www.thisisclassicalguitar.com/bracing-styles-for-classical-guitars/
Das Werkstück wird dabei immer wieder auf Merkmale geprüft, welche später die akustische Qualität beeinflussen.
Es wird zum Beispiel mit den Händen geprüft, wie biegsam das Werkstück ist oder wie sich der Klang beim klopfen an einer bestimmten Stelle anhört.

Es ist offensichtlich, dass in der Bewertung und Bearbeitung von Holz, die subjektive Erfahrung eine große Rolle spielt.
Währenddessen wird in der Werkstofftechnik seit längerem mit Ultraschall gearbeitet, um Werkstoffe auf Fehler zu prüfen oder Materialeigenschaften bestimmen zu können.
Es soll der Versuch unternommen werden, Verfahren aus dieser Domäne im Instrumentenbau anzuwenden.

## Das Luccimeter
Es gibt bereits ein Gerät, welches Ulraschallimpulse in ein Stück holz einbringt und diese dann wieder abnimmt.
Zusammen mit der eigegebenen Länge des Holzstückes kann dann die Schallgeschwindigkeit im Material bestimmt werden.
Es findet aktuell hauptsächlich in der Bewertung von Bogenholz, aber auch in der Auswahl und Ausarbeitung von Geigen- und Gitarrenholz Verwendung.
Das Gerät ist in der Lage, die Schallgeschwindigkeit im Material zu messen, kann aber über die wieder aufgenommenen Schallwellen keine weiteren Aussagen treffen. 
(see https://www.lucchimeter.com/)

## Zielsetzung
Ziel des Projektes ist, ein Gerät zu entwickeln, welches Mithilfe von Ultraschall Materialeigenschaften des Holzes bestimmen und damit die oben beschriebenen
Techniken unterstützen und gegebenfalls eine Grundlage zur Bewertung von Holz darstellen kann.
Dabei ist es wichtig, dass Messungen einfach und schnell durchgeführt werden können und
das Gerät dabei portabel und gleichzeitg kostengünstig ist. 
Die Messergebnisse sollten möglichst einfach auszuwerten sein, am Besten mittels errechneten "Scores" für verschiedene Eigenschaften.
Dabei sind absolute Werte weninger von Interesse als die Möglichkeit verschiedene Holzstücke miteinander zu vergleichen und Verhältnisse zwischen Messpunkten bestimmen zu können.
Das Gerät soll ähnlich wie das oben beschriebene Luccimeter funktionieren, allerdings über die Messung der Schallgeschwindigkeit hinaus, auch die abegenommenen Wellen weiter analysieren.
Es sollen idealerweise Aussagen über die Dämpfung und die Elastizität des Materials getroffen werden.

## Bisherige Arbeit
Bisher wurden 2 Prototypen gebaut. Der ersten Prototyp ist ein Nachbau, des oben beschriebenen Luccimeter, welches zur Zeit 
bei F.W. Geigenbu in Bremen im Einsatz ist und dort zur Vermessung von Bogen- und Geigenholz genutzt wird. 
Es verfügt über 2 40kHz Piezo-Elemente, welche den Ultraschall in das Material einbringen und wieder abnehmen.
Ein Atmega-8 Microcontroller wertet dann aus, wie lang der Schall benötigt hat um das Material zu durchqueren.
Zusammen mit der eingegebenen Länge wird die Schallgeschwindigkeit im Material gemessen. 


Der zweite Prototyp arbeitet mit dem selben Piezo-Wandlern, allerdings wurden die Schaltungen für 
die Signalerzeugung und -verstärkung mit Hile von Thomas XXXX, einem pensionierten Elektrotechnisker überarbeitet. 
Es wurde ebenfalls ein Bildschirm und ein leistungsstarker Teensy 4.0 Microcontroller verbaut.
Da dieser über einen 1MSP/S ADC verfügt, können die 40kHz Schallwellen nun abgenommen und digital verarbeitet werden.


Der Prototyp ist in der Lage Schallwellen von 40kHz zu erzeugen, in das Material einzubringen, dann wieder abzunehmen, analog zu verstärken und anschließend auf einem kleinen Display anzuzeigen.

Es fehlt aber noch ein vernünftiges Bewertungsverfahren, welches die abegommenen Schallwellen auswertet. Dabei muss berücksichtigt werden, dass die die Piezos mit der Hand an das Werkstück gehalten werden und die Ergebnisse somit je nach Anpressdruck und -winkel mitunter stark variieren. Gleichzeitig sind die verwendeten Piezos vermutlich nicht die optimale Wahl für die beschriebene Anwendung, es konnten allerdings keine
passenderen Elemente mit dem zur Verfügung stehenden Budget organisiert werden. Es stellt sich außerdem die Frage ob sich 40kHz als Frequenz zur Durschschallung von Feststoffen eignet.
Außerdem muss ein Weg gefunden Werten, einen Piezo Treiber zu betreiben, der möglichst Hohe Spannungsamplitunden liefern, gleichzeitig aber mit einem 5V Akku bereiben werden kann, 