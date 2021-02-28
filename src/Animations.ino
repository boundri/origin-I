void fillanimation(uint32_t color, int wait) {
  uint32_t blue = strip.Color(0, 0, 50, 0);
  uint32_t red = strip.Color(50, 0, 0, 0);

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    strip.setBrightness(100);
  }
}

void startanimation(uint32_t color, int wait) {
  uint32_t blue = strip.Color(0, 0, 50, 0);
  uint32_t red = strip.Color(50, 0, 0, 0);

  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    strip.setBrightness(100);
    delay(wait);
  }
}
