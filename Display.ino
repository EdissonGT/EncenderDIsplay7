// Definición de los pines a utilizar.
const int rightButton = 2;
const int leftButton = 3;
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDigit1 = 11;

void setup() {
  // Configuración de los pines de la pantalla en modo de salida
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDigit1, OUTPUT);
  Serial.begin(9600);
}

void showNumber(int num) {
  // Tabla para mostrar los números en el display de 7 segmentos.
  // Cada elemento de la matriz corresponde a los pines A, B, C, D, E, F y G, respectivamente..
  int tabla[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
  };

  if (num >= 0 && num <= 9) {
    digitalWrite(pinA, tabla[num][0]);
    digitalWrite(pinB, tabla[num][1]);
    digitalWrite(pinC, tabla[num][2]);
    digitalWrite(pinD, tabla[num][3]);
    digitalWrite(pinE, tabla[num][4]);
    digitalWrite(pinF, tabla[num][5]);
    digitalWrite(pinG, tabla[num][6]);
  }
}

void showAscendente() {
  for (int i = 0; i <= 9; i++) {
    showNumber(i);
    digitalWrite(pinDigit1, HIGH);
    delay(400);
    digitalWrite(pinDigit1, LOW);
    delay(400);
  }
}

void showDescendente() {
  for (int i = 9; i >= 0; i--) {
    showNumber(i);
    digitalWrite(pinDigit1, HIGH);
    delay(400);
    digitalWrite(pinDigit1, LOW);
    delay(400);
  }
}
void loop() {
  // Compruebe el estado del botón derecho.
  if (digitalRead(leftButton) == HIGH) {
    for (int i = 0; i < 10; i++) {
      showNumber(i);
      delay(400); //retraso para evitar lecturas incorrectas.
    }
  }

  // Compruebe el estado del botón izquierdo.
  if (digitalRead(rightButton) == HIGH) {
    for (int i = 9; i >= 0; i--) {
      showNumber(i);
      delay(400); //retraso para evitar lecturas incorrectas.
    }
  }

  // Compruebe si se ha recibido un número del monitor serie.
  if (Serial.available() > 0) {
    int number = Serial.parseInt();
    // Verifica que el número sea de un solo dígito
    if (number >= 0 && number <= 9) {
      showNumber(number);
    }
  }
}