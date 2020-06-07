//- -----------------------------------------------------------------------------------------------------------------------
// AskSin++
// 2020-02-15 der-pw Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
// 2020-02-15 jp112sdl Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------

#ifndef SSD1306_H_
#define SSD1306_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


template <uint8_t PEAK_THRESH = 5, uint8_t ADDRESS = 0x3C>
class DisplayType {
private:
  Adafruit_SSD1306 d;
  uint8_t peakrssi;
  uint8_t peakhold_val;
  uint8_t peakhold_thresh_val;
public:
  DisplayType () : d(128, 32, &Wire), peakrssi(0), peakhold_val(100), peakhold_thresh_val(0)  {}
  virtual ~DisplayType () {}

  void init() {
    d.begin(SSD1306_SWITCHCAPVCC, ADDRESS);
    delay(1000);
    d.ssd1306_command(SSD1306_SETCONTRAST);
    d.ssd1306_command(10);              // set brightness 0-255
    d.setRotation(3);
    d.clearDisplay();
    d.display();
  }

  void printRSSI(uint8_t rssi, bool update=true) {
    d.clearDisplay();
    d.setTextSize(1);                   // tiny display needs tiny font
    d.setCursor(rssi < 100 ? 8 : 5, 0);

    d.setTextColor(WHITE, BLACK);       // print the rssi value
    d.print("-");
    d.print(rssi);
    d.setCursor(8, 9);
    d.print("dBm");

    if (update) d.display();
  }

  void drawRSSIGraph(uint8_t rssi, bool update=true) {
    d.drawRoundRect(9,  19,  15,  107, 2, 1);   // draw the rectangle

    uint8_t barh = map(rssi, 120, 20, 100, 0);  // map the rssi values to 0-100
    if (barh > 100) barh = 100;
    d.fillRect(12, 22+barh, 9, 101-barh, 1);    // an build the bar

    if ((rssi < peakrssi) || (peakhold_thresh_val > PEAK_THRESH)) {   // peakhold
      peakrssi = rssi;
      peakhold_val = barh;
      peakhold_thresh_val = 1;
    } else {
      peakhold_thresh_val++;
    }
    d.drawFastHLine(12, peakhold_val+22, 9, 1); // draw a peak hold line

    if (update) d.display();
  }

  void printFull(uint8_t rssi) {
    printRSSI(rssi, false);
    drawRSSIGraph(rssi, false);
    d.display();
  }
};

#endif /* SSD1306_H_ */