#include <FastLED.h>

#define NUM_LEDS 29
#define DATA_PIN_1 2
#define BUTTON_PIN_1 0  // Adjust if necessary
#define DATA_PIN_2 4
#define BUTTON_PIN_2 5  // Adjust if necessary

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int position1 = 0;
int position2 = 0;
bool gameActive = false;  // Start with the game inactive
bool previousButtonState_1 = HIGH;
bool previousButtonState_2 = HIGH;

void setup() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  FastLED.addLeds<WS2812, DATA_PIN_1, GRB>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN_2, GRB>(leds2, NUM_LEDS);
  introEffect();  // Start with the rainbow intro effect
}

void loop() {
  if (!gameActive) {
    // Wait for both buttons to be pressed to start the game
    if (digitalRead(BUTTON_PIN_1) == LOW && digitalRead(BUTTON_PIN_2) == LOW) {
      while (digitalRead(BUTTON_PIN_1) == LOW || digitalRead(BUTTON_PIN_2) == LOW);  // Wait for both buttons to be released
      resetGame();  // Initialize the game state with a countdown
    }
  } else {
    // Player 1's logic
    bool currentButtonState_1 = digitalRead(BUTTON_PIN_1);
    if (currentButtonState_1 == LOW && previousButtonState_1 == HIGH && position1 < NUM_LEDS - 1) {
      advanceCar(leds1, &position1, CRGB::Red);
      delay(80);
    }
    previousButtonState_1 = currentButtonState_1;

    // Player 2's logic
    bool currentButtonState_2 = digitalRead(BUTTON_PIN_2);
    if (currentButtonState_2 == LOW && previousButtonState_2 == HIGH && position2 < NUM_LEDS - 1) {
      advanceCar(leds2, &position2, CRGB::Blue);
      delay(80);
    }
    previousButtonState_2 = currentButtonState_2;

    checkWin();
  }
}

void introEffect() {
  while (digitalRead(BUTTON_PIN_1) == HIGH || digitalRead(BUTTON_PIN_2) == HIGH) {
    rainbowEffect();
    delay(20);  // Delay to control the speed of the rainbow effect
  }
}

void rainbowEffect() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds1[i] = CHSV((hue + i * 20) % 256, 255, 255);
    leds2[i] = CHSV((hue + i * 10) % 256, 255, 255);
  }
  FastLED.show();
  hue++;
}

void advanceCar(CRGB* leds, int* position, const CRGB& color) {
  fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear the strip
  *position += 1; // Advance the car
  leds[*position] = color; // Light up new position
  FastLED.show();
}

void checkWin() {
  if (position1 == NUM_LEDS - 1) {
    gameActive = false;
    displayWin(leds1, leds2);
  } else if (position2 == NUM_LEDS - 1) {
    gameActive = false;
    displayWin(leds2, leds1);
  }
}

void displayWin(CRGB* winnerLeds, CRGB* loserLeds) {
  for (int i = 0; i < 5; i++) {  // Flash 5 times
    fill_solid(winnerLeds, NUM_LEDS, CRGB::Green);
    fill_solid(loserLeds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(300);
    fill_solid(winnerLeds, NUM_LEDS, CRGB::Black);
    fill_solid(loserLeds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(300);
  }

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) { // 5 seconds wait
    if (digitalRead(BUTTON_PIN_1) == LOW || digitalRead(BUTTON_PIN_2) == LOW) {
      return; // Exit the function if any button is pressed
    }
    delay(10); // Short delay to prevent constant pin reading
  }

  // Transition to introEffect only if no button was pressed during the 5 seconds
  introEffect();
}

void resetGame() {
  trafficLightCountdown();  // Start with the traffic light countdown
  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  position1 = 0;
  position2 = 0;
  leds1[position1] = CRGB::Red;  // Reset player 1's car
  leds2[position2] = CRGB::Blue; // Reset player 2's car
  gameActive = true;  // Reactivate the game after the countdown
  FastLED.show();
}

void trafficLightCountdown() {
  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000); // Wait for 1 second

  // Red Light - Fill the whole strip with red
  fill_solid(leds1, NUM_LEDS, CRGB::Red);
  fill_solid(leds2, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000); // Wait for 1 second

  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000); // Wait for 1 second

  // Yellow Light - Fill the whole strip with yellow
  fill_solid(leds1, NUM_LEDS, CRGB::Orange);
  fill_solid(leds2, NUM_LEDS, CRGB::Orange);
  FastLED.show();
  delay(1000); // Wait for 1 second

  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000); // Wait for 1 second

  // Green Light - Fill the whole strip with green
  fill_solid(leds1, NUM_LEDS, CRGB::Green);
  fill_solid(leds2, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(2000); // Wait for 1 second

  // Clear the lights for the start of the game
  fill_solid(leds1, NUM_LEDS, CRGB::Black);
  fill_solid(leds2, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
