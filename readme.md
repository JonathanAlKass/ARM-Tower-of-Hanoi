# Spielanleitung

## Singleplayer
* Taster 1 &nbsp;>&nbsp; Anzahl der Schreiben
* Taster 2  &nbsp;>&nbsp; Geschwindigkeit:
  <table style="width:100%">
    <tr>
      <td>Index</td>
      <td>Zeit pro Zug</td>
      <td>Pause</td>
      <td>Level</td>
    </tr>
    <tr>
      <td>1</td>
      <td>4s</td>
      <td>2s</td>
      <td>Anfänger</td>
    </tr>
    <tr>
      <td>2</td>
      <td>3s</td>
      <td>1.5s</td>
      <td>Easy</td>
    </tr>
    <tr>
      <td>3</td>
      <td>2s</td>
      <td>1s</td>
      <td>Normal</td>
    </tr>
    <tr>
      <td>4</td>
      <td>1s</td>
      <td>500ms</td>
      <td>Hard</td>
    </tr>
    <tr>
      <td>5</td>
      <td>600ms</td>
      <td>300ms</td>
      <td>Speedrunner</td>
    </tr>
    <tr>
      <td>6</td>
      <td>200ms</td>
      <td>100ms</td>
      <td>Impossible</td>
    </tr>
    
  </table>

* Taster 3  &nbsp;>&nbsp; Start
* Taster 4  &nbsp;>&nbsp; Modus (Single / Multi-player)
#### Ablauf
Nach dem Start Blinken alle LEDs 3x auf. Danach wird der Algorithmus gestartet. Am Ende Blinken die LEDs, auf dessen Position die Scheiben liegen.
Während des Spiels, muss die Scheibe von der Position der Roten LED auf die Position der grünen LED verschoben werden.
<br>
<br>
## Multiplayer
* Taster 1 &nbsp;>&nbsp; unbenutzt
* Taster 2 &nbsp;>&nbsp; Spieleranzahl
* Taster 3 &nbsp;>&nbsp; Start
* Taster 4  &nbsp;>&nbsp; Modus (Single / Multi-player)

#### Ablauf
Sobald die Einstellungen durch Start bestätigt wurden, fängt der erste Spieler an. Hier muss der Start button erneut für 500ms gedrückt werden. Nach 3 Sekunden leuchten alle LEDs auf und das Spiel beginnt. Hier muss nun der Algorithmus selbst gelöst werden. Sobald alle Scheiben in richtiger Position in der Mitte liegen, muss auf den Startbutton gedrückt werden. Danach ist der zweite Spieler dran. Sollten die Einstellungen für 3 Spieler getroffen worden sein, hat dieser danach auch noch seinen Zug. Am Ende wird der Gewinner ermittelt und die LEDs des Gewinners blinken.


