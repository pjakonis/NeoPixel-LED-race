#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN_1 2
#define BUTTON_PIN_1 15
#define DATA_PIN_2 4
#define BUTTON_PIN_2 14
#define BUZZER_PIN 12

#define NOTE_C5 523
#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_C6 1047

#define CAR_LENGTH 3


int melody[] = {
    NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6
};

int noteDurations[] = {
    16, 16, 16, 16 
};

void playVictoryMelody() {
    for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30; 
        delay(pauseBetweenNotes);
        noTone(BUZZER_PIN); 
    }
}

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int position1 = 0;
int position2 = 0;
bool gameActive = false;  
bool previousButtonState_1 = LOW;
bool previousButtonState_2 = LOW;

void setup() {
  pinMode(BUTTON_PIN_1, INPUT);  // Changed to INPUT
  pinMode(BUTTON_PIN_2, INPUT);  // Changed to INPUT
  FastLED.addLeds<WS2812, DATA_PIN_1, GRB>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN_2, GRB>(leds2, NUM_LEDS);
  introEffect();  // Start with the rainbow intro effect
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (!gameActive) {
    if (digitalRead(BUTTON_PIN_1) == HIGH && digitalRead(BUTTON_PIN_2) == HIGH) {
      while (digitalRead(BUTTON_PIN_1) == HIGH || digitalRead(BUTTON_PIN_2) == HIGH);
      resetGame();
    }
  } else {
    bool currentButtonState_1 = digitalRead(BUTTON_PIN_1);
    if (currentButtonState_1 == HIGH && previousButtonState_1 == LOW && position1 < NUM_LEDS - 1) {
      advanceCar(leds1, &position1, CRGB::Red);
      delay(10);
    }
    previousButtonState_1 = currentButtonState_1;

    bool currentButtonState_2 = digitalRead(BUTTON_PIN_2);
    if (currentButtonState_2 == HIGH && previousButtonState_2 == LOW && position2 < NUM_LEDS - 1) {
      advanceCar(leds2, &position2, CRGB::Blue);
      delay(10);
    }
    previousButtonState_2 = currentButtonState_2;

    checkWin();
  }
}

void introEffect() {
  while (digitalRead(BUTTON_PIN_1) == LOW || digitalRead(BUTTON_PIN_2) == LOW) {
    rainbowEffect();
    delay(50); 
  }
}

void rainbowEffect() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds1[i] = CHSV((hue + i * 20) % 256, 255, 200);
    leds2[i] = CHSV((hue + i * 10) % 256, 255, 200);
  }
  FastLED.show();
  hue += 10; 
}

void advanceCar(CRGB* leds, int* position, const CRGB& color) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for (int i = 0; i < CAR_LENGTH; i++) {
    int newPos = *position + i;
    if (newPos < NUM_LEDS) {
      leds[newPos] = color;
    }
  }
  *position += 1;
  FastLED.show();
}

void checkWin() {
    if (position1 == NUM_LEDS - 1) {
        gameActive = false;
        displayWin(leds1, CRGB::Red);
    } else if (position2 == NUM_LEDS - 1) {
        gameActive = false;
        displayWin(leds2, CRGB::Blue);
    }
}

void displayWin(CRGB* winnerLeds, const CRGB& winnerColor) {
    for (int i = 0; i < 5; i++) {
        fill_solid(leds1, NUM_LEDS, winnerColor);
        fill_solid(leds2, NUM_LEDS, winnerColor);
        FastLED.show();
        playVictoryMelody();
        fill_solid(leds1, NUM_LEDS, CRGB::Black);
        fill_solid(leds2, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(300);
    }

    unsigned long startTime = millis();
    while (millis() - startTime < 2000) {
        if (digitalRead(BUTTON_PIN_1) == HIGH || digitalRead(BUTTON_PIN_2) == HIGH) {
            return;
        }
        delay(10);
    }
    introEffect();
}

void resetGame() {
  trafficLightCountdown();
  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  position1 = 0;
  position2 = 0;
  leds1[position1] = CRGB::Red;  
  leds2[position2] = CRGB::Blue; 
  gameActive = true;  
  FastLED.show();
}

void trafficLightCountdown() {
  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000); 
  
  fill_solid(leds1, NUM_LEDS, CRGB::Red);
  fill_solid(leds2, NUM_LEDS, CRGB::Red);
  FastLED.show();
  tone(BUZZER_PIN, 1000, 1000);
  delay(1000);

  noTone(BUZZER_PIN); 

  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000);


  fill_solid(leds1, NUM_LEDS, CRGB::Orange);
  fill_solid(leds2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  tone(BUZZER_PIN, 1000, 1000);
  delay(1000);

  noTone(BUZZER_PIN); 

  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000); 


  fill_solid(leds1, NUM_LEDS, CRGB::Green);
  fill_solid(leds2, NUM_LEDS, CRGB::Green);
  FastLED.show();
  tone(BUZZER_PIN, 2500, 1000);
  delay(1000);

  noTone(BUZZER_PIN); 

  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
