#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define PIN            2
#define NUMPIXELS      12

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(7);
decode_results results;

bool neopixelsOn = true;

void setup() {
  Serial.begin(9600);
  strip.begin();
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    switch (results.value) {
      case 16724175: // Button 1 pressed
        colorWipe(strip.Color(18, 58, 68), 50); 
        break;
      case 16718055: // Button 2 pressed
        colorWipe(strip.Color(48, 25, 52), 50); 
        break;
      case 16743045: // Button 3 pressed
        colorWipe(strip.Color(50, 205, 50), 50); 
        break;
      case 16716015: // Button 4 pressed
        theaterChaseRainbow(50);
        break;
      case 16753245:
      turnOffNeopixels();
      break;

    }
    irrecv.resume(); // Receive the next value
  }
}

void turnOffNeopixels() {
  strip.clear(); // Clear all Neopixels
  strip.show(); // Update Neopixel display
  neopixelsOn = false; // Update state variable
}
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(int wait) {
  for (int j = 0; j < 256; j++) { // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0); // turn every third pixel off
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
