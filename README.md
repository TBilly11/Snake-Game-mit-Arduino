# Verkehrssignalanlagen (CODESYS)
<h1>1 Spielidee</h1>
 Es wird mit einem Arduino UNO den Klassiker Snake programmieren. Das Spiel soll
 aber nicht über den Computerbildschirm ausgegeben werden, sondern über zwei 8x8 LED
 Matrizen.
 Die Anforderungen an das Spiel sind folgende: Die Schlange soll sich in die vier Richtungen
 oben, unten, links und rechts bewegen können. Neben der Schlange befindet sich auf dem
 Display das Essen, was von der Schlange gegessen werden muss. Isst die Schlange das Essen,
 vergrößert sie sich. Zudem wird die Position des Essens neu bestimmt und die Geschwindig
keit der Schlange erhöht sich. Darüber hinaus sollen die Ränder der Matrizen keine Grenzen
 für die Schlange darstellen. Bewegt sie sich beispielsweise rechts aus der Matrix raus, er
scheint sie wieder links. Das Spiel ist zu Ende, wenn sich die Schlange selbst berührt. Dann
 soll die Punktzahl ausgegeben werden. Die Kommunikation zwischen dem Computer und
 dem Benutzer soll dabei über den seriellen Monitor erfolgen.​


<h1> 2 Spielumgebung </h2>
<h2> 2.1 Software</h2>
<h3> 2.1.1 Arduino IDE</h3>
<br />
<br />
<img src="https://i.imgur.com/tstUSon.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<h3> 2.1.2 Serieller Monitor</h3>
<br />
<br />
<img src="https://i.imgur.com/nkcV33F.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<h2> 2.2 Hardware</h2>
<h3> 2.2.1 Arduino UNO</h3>
<br />
<br />
<img src="https://i.imgur.com/6wXkHpj.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br /> 

<h3>  2.2.2 8x8 LED Matrix mit MAX7219</h3>
<br />
<br />
<img src="https://i.imgur.com/siKNn66.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br /> 

<h3>  2.2.3 Joystick</h3>
<br />
<br />
<img src="https://i.imgur.com/kZnzVf6.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br /> 

<h3>   2.2.4 Spielaufbau</h3>
<br />
<br />
<img src="https://i.imgur.com/af6Yt23.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>

<br />
<h2> 3 Programmablauf</h2>
 Wird das Programm gestartet, erfolgt die Erzeugung des Display Objektes „lc“ und allen weiteren benötigten Variablen. Dann wird die setup() Funktion
 aufgerufen. Hier werden einmalig die LEDs des Displays sicherheitshalber ausgeschalten.
 Zudem wird die Helligkeit der LEDs eingestellt und falls sich die Matrizen im Energiespar
modus befinden, werden sie aufgeweckt. Darüber hinaus werden Einstellungen für die serielle
 Schnittstelle festgelegt und die Analogpins für den Joystick als Inputs deklariert.
 Aus Sicht des Benutzers erfolgt der erste Schritt im seriellen Monitor. Dort wird der User
 aufgefordert des Spiel mit einer Joystickbewegung zu starten. Nach erfolgter Eingabe beginnt
 das Spiel. Die Schlange, die nur aus einem Element besteht, und das Essen werden zufällig
 auf den Displays ausgegeben. Die Schlange bewegt sich noch nicht. Erst wenn der Benutzer
 eine Richtung vorgibt, setzt sie sich in Bewegung.
 Wurde das Spiel gestartet, werden nacheinander folgende Schritte ausgeführt: Je nach Rich
tung der Schlange werden in einer Funktion die Koordinaten (x, y und Display) der einzelnen
 Schlangenelemente geändert, damit die Schlange sich fortbewegt. Danach werden alle LEDs
 der Displays ausgeschalten, damit die Schlange ihre Größe behält. Direkt im Anschluss wer
den die aktualisierte Schlange und das Essen ausgegeben. Zudem wird in einer Funktion
 überprüft ob die Schlange des Essen gegessen hat. Ist dies der Fall vergrößert sie sich, die
 Geschwindigkeit steigt und das Essen wird neu positioniert. Zudem wird gecheckt ob die
 Schlange sich selbst getroffen hat und deswegen das Spiel abgebrochen werden muss. Danach
 erfolgt eine Delay-Funktion. Die Verzögerung ist von der aktuellen Bewegungsgeschwindig
keit der Schlange abhängig. Je geringer der Wert der Geschwindigkeitsvariable ist, desto
 schneller werden die gerade beschriebenen Funkionen aufgerufen, was zu einer schnelleren
 Bewegung der Schlange führt. Solange das Spiel läuft, werden die gerade genannten Schritte
 immer wieder durchgeführt. Außerdem wird dauerhaft, unabhängig von dem Delay, über
prüft in welcher Position der Joystick steht und speichert je nach Position die Richtung in
 einer Variablen.
 Trifft die Schlange sich selber wird die Schleife verlassen. Die LEDs werden ausgeschaltet. Es
 wird die erreichte Punktzahl des Benutzers auf dem seriellen Monitor sowie auf den Matri
zen ausgegeben. Wurde das Spiel schon mal gespielt, wird der Highscore aus dem EEPROM
 des Arduino gelesen. Ist die erreichte Punktzahl größer als der Highscore, wird diese in den
 EEPROM gespeichert. Wurde der Highscore nicht übertroffen, geschieht nichts.
 Danach kann der Benutzer durch eine Joystickbewegung das Spiel erneut starten und das
 Programm beginnt wieder von vorne zu laufen.
<br />
<br />
<img src="https://i.imgur.com/mO39alt.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />

