//Sensor TCS3200

#include <LiquidCrystal.h>
 
//Pinos de conexao do modulo
const int s0 = 0;
const int s1 = 1;
const int s2 = 6;
const int s3 = 7;
const int out = 13;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
//Pinos do led RGB
int pinoledverm = 9;
int pinoledverd = 10;
int pinoledazul = 8;
 
//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;

void setup()
{
  lcd.begin(16, 2);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(pinoledverm, OUTPUT);
  pinMode(pinoledverd, OUTPUT);
  pinMode(pinoledazul, OUTPUT);

  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}
 
void loop()
{
  //Detecta a cor
  color();
  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(red, DEC);
  Serial.print(" Verde : ");
  Serial.print(green, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue, DEC);
  Serial.println();

  //Verifica se a cor vermelha foi detectada
  if (red < blue && red < green && red < 100)
  {
    Serial.println("Vermelho");
    lcd.clear();
    // Print a message to the LCD.
    lcd.print("COR IDENTIFICADA");
    lcd.setCursor(0,1);
    lcd.print("COR: ");
    lcd.print("VERMELHO");   
    
    digitalWrite(pinoledverm, HIGH); //Acende o led vermelho
    digitalWrite(pinoledverd, LOW);
    digitalWrite(pinoledazul, LOW);
  }
 
  //Verifica se a cor azul foi detectada
  else if (blue < red && blue < green && blue < 1000)
  {
    Serial.println("Azul");
    lcd.clear();
    // Print a message to the LCD.
    lcd.print("COR IDENTIFICADA");
    lcd.setCursor(0,1);
    lcd.print("COR: ");
    lcd.print("AZUL");
    
    digitalWrite(pinoledverm, LOW);
    digitalWrite(pinoledverd, LOW);
    digitalWrite(pinoledazul, HIGH); //Acende o led azul
  }
 
  //Verifica se a cor verde foi detectada
  else if (green < red && green < blue)
  {
    Serial.println("Verde");
    lcd.clear();
    // Print a message to the LCD.
    lcd.print("COR IDENTIFICADA");
    lcd.setCursor(0,1);
    lcd.print("COR: ");
    lcd.print("VERDE");
    
    digitalWrite(pinoledverm, LOW);
    digitalWrite(pinoledverd, HIGH); //Acende o led verde
    digitalWrite(pinoledazul, LOW);
  }
  Serial.println();
 
  //Delay para apagar os leds e reiniciar o processo
  delay(50);
  digitalWrite(pinoledverm, LOW);
  digitalWrite(pinoledverd, LOW);
  digitalWrite(pinoledazul, LOW);
}
 
void color()
{
  //Rotina que le o valor das cores
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
