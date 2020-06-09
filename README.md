# AskSinSniffer328P

Sketch für den Arduino (Pro Mini, Nano), um Telegramme für den
[AskSin Analyzer](https://github.com/jp112sdl/AskSinAnalyzer) oder
[AskSin Analyzer XS](https://github.com/psi-4ward/AskSinAnalyzerXS) zu sniffen.

Dieser Fork von [AskSinSniffer328P](https://github.com/jp112sdl/AskSinAnalyzer/tree/master/AskSinSniffer328P)
bietet die Möglichkeit, ein 0.91" Dipsplay zu verwenden, um darauf den aktuellen Signalpegel
anzuzeigen. Eine dynamische Pegelanzeige ist ebenfalls implementiert, um Ändereungen zu visualisieren.

Zudem wird der Arduino Nano unterstützt.

![AskSin-Analyzer Pegel](https://github.com/der-pw/AskSinAnalyzer/blob/master/Images/Sniffer_Display.jpg "AskSin-Analyzer Pegel")

* **Bei Verwendung des Arduino Nano wird der LED-PIN `8` verwendet** (PCB von TomMajor).
* Für den Pro-Mini wird die LED auf PIN `4` angenommen. Ggf. ist dies im Sketch anzupassen.

## Flashen

Es gibt verschiedene Möglichkeiten, den Sketch zu flashen.
Grundlagen können auf [asksinpp.de](https://asksinpp.de/Grundlagen/02_software.html) nachgelsesen werden.  
Eine Anpassung der `DeviceInfo` Konfiguration ist **nicht** notwendig, da der Sniffer nicht an einer CCU angelernt wird.

### Arduino IDE

Benötigte Bibliotheken: `AskSinPP`, `Low-Power`, `EnableInterrupt` und bei Verwendung des OLED-Displays `Adafruit GFX Library` und `Adafruit SSD1306`. **Der LED-PIN (default 4) und die Unterstützung des OLED-Display (default aus) muss ggf. im Sketch angepasst werden.

### avrdude

Direktes Flashen der HEX-Datei über avrdude.  
Die Firmware kann unter [Releases](https://github.com/psi-4ward/AskSinAnalyzer-Sniffer/releases/latest)
heruntergeladen werden. Die Parameter wie Port und Datei sind entsprechend anzupassen.
Für den Pro-Mini ist ENV der LED-PIN `4` gesetzt, für den Nano `8`.

```bash
# Pro-Mini
avrdude -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:pro-mini.hex:i
```

### PlatformIO

Dem Projekt liegt eine `platformio.ini` bei. Für den Pro-Mini ist per ENV der LED-PIN `4` gesetzt, für den Nano `8`.
Sollte ein eine andere Belegung gewünscht sein ist der Sketch anzupassen.

Um die Bibliotheken zu laden, den Sketch zu kompilieren und hochzuladen, reicht ein einziger Befehl:

```bash
# Für Arduino Pro-Mini (328P)
pio run -e pro-mini -t upload

# Für Arduino Pro-Mini mit OLED
pio run -e pro-mini-oled -t upload

# Für Ardino Nano (zB AskSin-Analyzer-XS PCB von TomMajor)
pio run -e nano -t upload

# Für Arduino Nano mit OLED-Display
pio run -e nano-oled -t upload
```

```bash
# Serial monitor
pio device monitor
```


## Authors

* [Jérôme Pech](https://github.com/jp112sdl)
* [Patrick Wulfert](https://github.com/der-pw)
* [Christoph Wiechert](https://github.com/der-pw)


## License

CC BY-NC-SA 3.0
