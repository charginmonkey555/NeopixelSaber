#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>

// -------------------- PIN CONFIG --------------------
#define LED1_PIN 2
#define LED2_PIN 3
#define BUTTON_PIN 6

// DFPlayer uses hardware serial on Nano
#define DF_RX 0   // DFPlayer TX → Arduino RX0
#define DF_TX 1   // DFPlayer RX → Arduino TX1

// -------------------- LED CONFIG --------------------
#define NUM_LEDS 60
Adafruit_NeoPixel strip1(NUM_LEDS, LED1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_LEDS, LED2_PIN, NEO_GRB + NEO_KHZ800);

// -------------------- DFPLAYER ----------------------
DFRobotDFPlayerMini df;

// -------------------- TRACK NUMBERS -----------------
#define TRACK_IGNITION      1
#define TRACK_HUM           2
#define TRACK_SHUTDOWN      3
#define TRACK_THEME1        4
#define TRACK_THEME2        5
#define TRACK_THEME3        6

// -------------------- VOLUME ------------------------
#define VOL_HUM   25
#define VOL_SFX   30

// -------------------- TIMINGS (ms) ------------------
const uint32_t IGNITION_TIME = 2000;
const uint32_t IGNITION_BLADE = 1051;

const uint32_t SHUTDOWN_TIME = 1721;
const uint32_t SHUTDOWN_BLADE = 1229;
const uint32_t SHUTDOWN_START = 492;

const uint32_t HUM_FADE_AFTER_THEME = 1020;

const uint32_t THEME1_LEN = 38928;
const uint32_t THEME2_LEN = 24408;
const uint32_t THEME3_LEN = 16896;

const uint32_t MULTIPRESS_WINDOW = 500;
const uint32_t COLOR_WIPE_TIME = 1051;

// -------------------- STATES ------------------------
enum SaberState {
  STATE_OFF,
  STATE_IGNITING,
  STATE_HUM,
  STATE_SHUTTING_DOWN,
  STATE_THEME1,
  STATE_THEME2,
  STATE_THEME3
};

SaberState state = STATE_OFF;

// -------------------- BUTTON ------------------------
bool lastButton = HIGH;
uint32_t lastButtonChange = 0;
uint32_t lastPressTime = 0;
uint8_t pressCount = 0;

// -------------------- TIMERS ------------------------
uint32_t ignitionStart = 0;
uint32_t shutdownStart = 0;
uint32_t themeStart = 0;
uint32_t colorWipeStart = 0;

// -------------------- COLOURS ------------------------
uint32_t currentColor = 0x0000FF; // default BLUE
uint32_t targetColor = 0x0000FF;
bool colorWipeActive = false;

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
  return strip1.Color(r, g, b);
}

const uint32_t COLOR_THEME1 = 0x0000FF; // blue
const uint32_t COLOR_THEME2 = 0x00FF00; // green
const uint32_t COLOR_THEME3 = 0xFF0000; // red

// -------------------- LED HELPERS --------------------
void setBladeInstant(uint32_t c) {
  currentColor = c;
  targetColor = c;
  colorWipeActive = false;
  for (int i = 0; i < NUM_LEDS; i++) {
    strip1.setPixelColor(i, c);
    strip2.setPixelColor(i, c);
  }
  strip1.show();
  strip2.show();
}

void startColorWipe(uint32_t newColor) {
  targetColor = newColor;
  colorWipeStart = millis();
  colorWipeActive = true;
}

void updateColorWipe() {
  if (!colorWipeActive) return;

  uint32_t now = millis();
  uint32_t elapsed = now - colorWipeStart;

  if (elapsed >= COLOR_WIPE_TIME) {
    setBladeInstant(targetColor);
    return;
  }

  float progress = (float)elapsed / COLOR_WIPE_TIME;
  int lit = progress * NUM_LEDS;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < lit) {
      strip1.setPixelColor(i, targetColor);
      strip2.setPixelColor(i, targetColor);
    } else {
      strip1.setPixelColor(i, currentColor);
      strip2.setPixelColor(i, currentColor);
    }
  }

  strip1.show();
  strip2.show();
}

// -------------------- IGNITION -----------------------
void updateIgnition() {
  uint32_t now = millis();
  uint32_t elapsed = now - ignitionStart;

  if (elapsed > IGNITION_BLADE) elapsed = IGNITION_BLADE;

  float progress = (float)elapsed / IGNITION_BLADE;
  int lit = progress * NUM_LEDS;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < lit) {
      strip1.setPixelColor(i, currentColor);
      strip2.setPixelColor(i, currentColor);
    } else {
      strip1.setPixelColor(i, 0);
      strip2.setPixelColor(i, 0);
    }
  }

  strip1.show();
  strip2.show();

  if (millis() - ignitionStart >= IGNITION_TIME) {
    df.play(TRACK_HUM);
    df.volume(VOL_HUM);
    state = STATE_HUM;
  }
}

// -------------------- SHUTDOWN -----------------------
void updateShutdown() {
  uint32_t now = millis();
  uint32_t elapsed = now - shutdownStart;

  if (elapsed < SHUTDOWN_START) {
    for (int i = 0; i < NUM_LEDS; i++) {
      strip1.setPixelColor(i, currentColor);
      strip2.setPixelColor(i, currentColor);
    }
    strip1.show();
    strip2.show();
    return;
  }

  uint32_t bladeElapsed = elapsed - SHUTDOWN_START;
  if (bladeElapsed > SHUTDOWN_BLADE) bladeElapsed = SHUTDOWN_BLADE;

  float progress = (float)bladeElapsed / SHUTDOWN_BLADE;
  int off = progress * NUM_LEDS;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < NUM_LEDS - off) {
      strip1.setPixelColor(i, currentColor);
      strip2.setPixelColor(i, currentColor);
    } else {
      strip1.setPixelColor(i, 0);
      strip2.setPixelColor(i, 0);
    }
  }

  strip1.show();
  strip2.show();

  if (elapsed >= SHUTDOWN_TIME) {
    df.stop();
    setBladeInstant(0);
    state = STATE_OFF;
  }
}

// -------------------- THEMES -------------------------
void updateTheme(uint32_t themeLen) {
  if (millis() - themeStart >= themeLen) {
    df.play(TRACK_HUM);
    df.volume(VOL_HUM);
    state = STATE_HUM;
  }
}

// -------------------- BUTTON -------------------------
void handleButton() {
  bool reading = digitalRead(BUTTON_PIN);
  uint32_t now = millis();

  if (reading != lastButton) {
    lastButtonChange = now;
    lastButton = reading;
  }

  if ((now - lastButtonChange) > 30) {
    if (reading == LOW) {
      if (now - lastPressTime > MULTIPRESS_WINDOW) {
        pressCount = 0;
      }
      pressCount++;
      lastPressTime = now;
    }
  }

  if (pressCount > 0 && (now - lastPressTime) > MULTIPRESS_WINDOW) {
    uint8_t count = pressCount;
    pressCount = 0;

    switch (state) {
      case STATE_OFF:
        if (count == 1) {
          state = STATE_IGNITING;
          ignitionStart = millis();
          df.play(TRACK_IGNITION);
          df.volume(VOL_SFX);
        }
        break;

      case STATE_HUM:
        if (count == 1) {
          state = STATE_SHUTTING_DOWN;
          shutdownStart = millis();
          df.play(TRACK_SHUTDOWN);
          df.volume(VOL_SFX);
        }
        else if (count == 3) {
          state = STATE_THEME1;
          themeStart = millis();
          df.play(TRACK_THEME1);
          df.volume(VOL_SFX);
          startColorWipe(COLOR_THEME1);
        }
        else if (count == 4) {
          state = STATE_THEME2;
          themeStart = millis();
          df.play(TRACK_THEME2);
          df.volume(VOL_SFX);
          startColorWipe(COLOR_THEME2);
        }
        else if (count == 5) {
          state = STATE_THEME3;
          themeStart = millis();
          df.play(TRACK_THEME3);
          df.volume(VOL_SFX);
          startColorWipe(COLOR_THEME3);
        }
        break;

      default:
        break;
    }
  }
}

// -------------------- SETUP --------------------------
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  strip1.begin();
  strip2.begin();
  strip1.show();
  strip2.show();

  Serial.begin(9600);
  df.begin(Serial);
  df.volume(VOL_HUM);

  state = STATE_OFF;
}

// -------------------- LOOP ---------------------------
void loop() {
  handleButton();
  updateColorWipe();

  switch (state) {
    case STATE_IGNITING:       updateIgnition(); break;
    case STATE_HUM:            break;
    case STATE_SHUTTING_DOWN:  updateShutdown(); break;
    case STATE_THEME1:         updateTheme(THEME1_LEN); break;
    case STATE_THEME2:         updateTheme(THEME2_LEN); break;
    case STATE_THEME3:         updateTheme(THEME3_LEN); break;
    default: break;
  }
}
