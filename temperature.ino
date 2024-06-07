#include <LiquidCrystal.h>

// Initialisation de la bibliothèque pour l'écran LCD avec les broches utilisées
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;  // Broche du capteur TMP36
const int greenLedPin = 8; // Broche de la LED verte
const int redLedPin = 9;   // Broche de la LED rouge
const int buzzerPin = 10;  // Broche du buzzer

void setup() {
  // Initialisation de l'écran LCD
  lcd.begin(16, 2);
  lcd.print("Temperature:");

  // Initialisation des broches des LEDs et du buzzer
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialisation de la communication série pour le débogage
  Serial.begin(9600);
}

void loop() {
  // Lecture de la valeur analogique du capteur TMP36
  int sensorValue = analogRead(sensorPin);

  // Conversion de la valeur analogique en tension
  float voltage = sensorValue * (5.0 / 1023.0);

  // Conversion de la tension en température en degrés Celsius
  float temperatureC = (voltage - 0.5) * 100.0;

  // Affichage pour le débogage
  Serial.print("Température: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Affichage de la température sur l'écran LCD
  lcd.setCursor(0, 1); // Positionner le curseur à la deuxième ligne
  lcd.print("T: ");
  lcd.print(temperatureC);
  lcd.print(" C       "); // Espaces supplémentaires pour effacer les caractères précédents

  // Contrôle des LEDs et du buzzer en fonction de la température
  if (temperatureC < 21) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin); // Désactiver le buzzer
  } else if (temperatureC >= 21 && temperatureC < 24) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    noTone(buzzerPin); // Désactiver le buzzer
  } else if (temperatureC >= 24) {
    digitalWrite(greenLedPin, LOW);
    // Activer le buzzer avec une fréquence de 1000 Hz
    tone(buzzerPin, 1000); // Activer le buzzer passif

    // Faire clignoter la LED rouge pendant 10 secondes
    for (int i = 0; i < 10; i++) {
      digitalWrite(redLedPin, HIGH);
      delay(500); // Allumer pendant 500 ms
      digitalWrite(redLedPin, LOW);
      delay(500); // Éteindre pendant 500 ms
    }
    
    noTone(buzzerPin); // Désactiver le buzzer
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin); // Désactiver le buzzer
  }

  // Délai avant la prochaine lecture
  delay(10000); // Mesure toutes les 10 secondes
}