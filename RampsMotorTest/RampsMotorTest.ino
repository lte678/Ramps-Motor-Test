//RampsMotorTest.ino

//Um sich mit dem Ramps zu verbinden, musst du den Code hoch laden, und die serial Console öffnen. 
//Da gibt es eine Einstellung für "line endings", du musst newline aussuchen
//Außerdem ist die serial Geschwindigkeit 115200 Baud
//Wenn du hilfe brauchst tipp einfach mal help oben ein (in der serial Console)

//Hier nichts machen!
//Alle Variablen so lassen

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

String inputString = "";
String parameter1 = "";
bool param = false;

void setup() {
	//Alles hier blieb unverändert, es wird einfach gesagt welche pins Ausgänge und welche Eingänge sind

	Serial.begin(115200);

	pinMode(FAN_PIN, OUTPUT);
	pinMode(HEATER_0_PIN, OUTPUT);
	pinMode(HEATER_1_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);

	pinMode(X_STEP_PIN, OUTPUT);
	pinMode(X_DIR_PIN, OUTPUT);
	pinMode(X_ENABLE_PIN, OUTPUT);

	pinMode(Y_STEP_PIN, OUTPUT);
	pinMode(Y_DIR_PIN, OUTPUT);
	pinMode(Y_ENABLE_PIN, OUTPUT);

	pinMode(Z_STEP_PIN, OUTPUT);
	pinMode(Z_DIR_PIN, OUTPUT);
	pinMode(Z_ENABLE_PIN, OUTPUT);

	pinMode(E_STEP_PIN, OUTPUT);
	pinMode(E_DIR_PIN, OUTPUT);
	pinMode(E_ENABLE_PIN, OUTPUT);

	pinMode(Q_STEP_PIN, OUTPUT);
	pinMode(Q_DIR_PIN, OUTPUT);
	pinMode(Q_ENABLE_PIN, OUTPUT);

	digitalWrite(X_ENABLE_PIN, LOW);
	digitalWrite(Y_ENABLE_PIN, LOW);
	digitalWrite(Z_ENABLE_PIN, LOW);
	digitalWrite(E_ENABLE_PIN, LOW);
	digitalWrite(Q_ENABLE_PIN, LOW);
}





void loop() {
	//Das ist der Code das zum Testen gedacht war, es ist aber zum Großteil unnötig weil wir nur ein Motor und keine andere Geräte haben

	/*
	if (millis() % 1000 <300) {
		digitalWrite(HEATER_0_PIN, HIGH);
		digitalWrite(HEATER_1_PIN, LOW);
		digitalWrite(FAN_PIN, LOW);
	}
	else if (millis() % 1000 <600) {
		digitalWrite(HEATER_0_PIN, LOW);
		digitalWrite(HEATER_1_PIN, HIGH);
		digitalWrite(FAN_PIN, LOW);
	}
	else  {
		digitalWrite(HEATER_0_PIN, LOW);
		digitalWrite(HEATER_1_PIN, LOW);
		digitalWrite(FAN_PIN, HIGH);
	}

	if (millis() % 10000 <5000) {
		digitalWrite(X_DIR_PIN, HIGH);
		digitalWrite(Y_DIR_PIN, HIGH);
		digitalWrite(Z_DIR_PIN, HIGH);
		digitalWrite(E_DIR_PIN, HIGH);
		digitalWrite(Q_DIR_PIN, HIGH);
	}
	else {
		digitalWrite(X_DIR_PIN, LOW);
		digitalWrite(Y_DIR_PIN, LOW);
		digitalWrite(Z_DIR_PIN, LOW);
		digitalWrite(E_DIR_PIN, LOW);
		digitalWrite(Q_DIR_PIN, LOW);
	}


	digitalWrite(X_STEP_PIN, HIGH);
	digitalWrite(Y_STEP_PIN, HIGH);
	digitalWrite(Z_STEP_PIN, HIGH);
	digitalWrite(E_STEP_PIN, HIGH);
	digitalWrite(Q_STEP_PIN, HIGH);
	delay(1);

	digitalWrite(X_STEP_PIN, LOW);
	digitalWrite(Y_STEP_PIN, LOW);
	digitalWrite(Z_STEP_PIN, LOW);
	digitalWrite(E_STEP_PIN, LOW);
	digitalWrite(Q_STEP_PIN, LOW);

	*/

	//Hier fängt der Code an, dieses Program macht nur was wenn es ein Befehl bekommt (dann ist Serial.available() größer als 0)

	if (Serial.available() > 0) {
		char input = (char)Serial.read(); // Wir lesen hier ein Byte (bzw. ein Buchstabe) und speichern es
		if (input != '\n') { // Wenn es kein "newline" Byte ist, dann sind wir noch nicht am ende der Zeile
			if (input == ' ') { // Wenn es ein Leerzeichen ist dann handelt es sich jetzt um ein Parameter ("Step 500" <- parameter nach dem Leerzeichen)
				param = true;
			}
			else {
				if (param) { // Wenn es sich um ein Parameter handelt
					parameter1 += input; // dann wird der Buchstabe zum "String" angehängt
				}
				else {
					inputString += input; // sonst wird es zum anderen "String" angehängt
				}
			}
		}
		else { // Wenn das Befehl fertig ist, bzw. die Zeile zu ende ist wird geprüft was befohlen würde
			if (inputString.equals("led_on")) { // Led soll eingeschaltet werden
				digitalWrite(LED_PIN, HIGH);
				Serial.println("Led on!");
			}
			else if (inputString.equals("led_off")) { //Led soll ausgeschaltet werden
				digitalWrite(LED_PIN, LOW);
				Serial.println("Led off!");
			}
			else if (inputString.equals("step")) { //Der Stepper soll für {parameter1} Schritte an gehen (nur in eine Richtung!)
				
				//Wenn es nicht kompilert weil hier ein Error ist, lösche den Bereich einfach, ich habe es noch nicht getestet
				
				if (parameter1.toInt() >= 0) {
					digitalWrite(Y_DIR_PIN, HIGH); //Diese Zeile hat gefehlt und könnte der Grund sein warum sich nichts bewegt hat (aber vlt. auch nicht...)
				}
				else {
					digitalWrite(Y_DIR_PIN, LOW); //Andere Richtung
				}

				//Hier endet der neue code

				int i = 0;
				while (i < parameter1.toInt()) {
					digitalWrite(Y_STEP_PIN, HIGH); //Den Stepper pin ein und auschaltung für genau i Schritte
					delay(2);
					digitalWrite(Y_STEP_PIN, LOW);
					delay(2);
					i++;
				}

				Serial.println("Stepped " + (String)parameter1 + " steps");
			}
			else if (inputString.equals("fan_on")) { //MOSFET auf D9 ein- und auschalten, du kannst auch irgendwas beliebiges da anschließen
				digitalWrite(FAN_PIN, HIGH);
				Serial.println("Fan on pin " + (String)FAN_PIN + " turned on");
			}
			else if (inputString.equals("fan_off")) {
				digitalWrite(FAN_PIN, LOW);
				Serial.println("Fan on pin " + (String)FAN_PIN + " turned off");
			}
			else if (inputString.equals("help")) { //Sagt dir was für Befehle möglich sind
				Serial.println("led_on");
				Serial.println("led_off");
				Serial.println("fan_on");
				Serial.println("fan_off");
				Serial.println("step <number of steps>");
				Serial.println("help");
			}
			else {
				Serial.println("Type 'help' to list available commands"); //Ein Befehl wurde falsch eingetippt, es sagt dir, dass du den Help Befehl benutzen sollst 
			}

			inputString = ""; //Alle betroffene Variabeln resetten
			parameter1 = "";
			param = false;
		}
	}

}
