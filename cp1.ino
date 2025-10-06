// =========================
// Edge Computing - CP1
// Autores: Victor Nunes; Roger Paiva; Guilherme Segolin; Pedro Henrique; Elias Laurentino; 
// =========================

#include <LiquidCrystal.h>   // Biblioteca para uso do display LCD

// Inicializa o LCD com os pinos conectados: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(6, 7, 8, 9, 10, 11, 12); 

// Criação de caracteres personalizados (ícones) para o display LCD
byte garrafa[8] = {
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100,
  B01110
};

byte v[8] = {
  B00000,
  B00000,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,
  B00100
};

byte a[8] = {
  B00000,
  B00000,
  B00100,
  B01010,
  B01110,
  B01010,
  B10001,
  B10001
};

// Definição dos pinos conectados aos componentes
int red = 2;       // LED vermelho no pino digital 2
int green = 4;     // LED verde no pino digital 4
int yellow = 3;    // LED amarelo no pino digital 3
int LDR = A0;      // Sensor LDR na entrada analógica A0
int buzzer = 5;    // Buzzer no pino digital 5

int soma = 0;                // Variável para somar leituras da luminosidade
const int leituras = 10;     // Número de leituras para média
int luminosidade;            // Variável que armazena a luminosidade atual

void setup(){
  // Define os modos dos pinos
  pinMode(LDR, INPUT);       
  pinMode(red, OUTPUT);      
  pinMode(green, OUTPUT);    
  pinMode(yellow, OUTPUT);   

  lcd.begin(16, 2); // Inicializa o LCD com 16 colunas e 2 linhas

  // Cria os caracteres personalizados nos slots 0, 1 e 2 do LCD
  lcd.createChar(0, v);
  lcd.createChar(1, a);
  lcd.createChar(2, garrafa);

  // Mostra os caracteres personalizados na primeira linha do LCD
  lcd.setCursor(8, 0);
  lcd.write(byte(0));  // Mostra o caractere 'v'
  lcd.setCursor(9, 0);
  lcd.write(byte(1));  // Mostra o caractere 'a'
  lcd.setCursor(7, 0);
  lcd.write(byte(2));  // Mostra o caractere 'garrafa'

  delay(3000); // Aguarda 3 segundos

  lcd.clear(); // Limpa o display

  lcd.setCursor(0, 0);
  lcd.print("Seja Bem-Vindo"); // Mensagem de boas-vindas
}

void loop(){
  soma = 0; // Reinicia a soma

  // Faz 10 leituras da luminosidade para tirar a média
  for (int i = 0; i < leituras; i++) {
    int valorLuz = analogRead(LDR);  // Lê valor analógico (0 a 1023)
    luminosidade = map(valorLuz, 0, 1023, 0, 100); // Converte para escala 0–100%
    soma += luminosidade; // Soma os valores
    delay(50); // Pequeno atraso entre as leituras
  }

  float media = soma / (float)leituras; // Calcula a média das leituras

  int inf = 30; // Limite inferior de luminosidade (30%)
  int sup = 60; // Limite superior de luminosidade (60%)

  // Se estiver entre 30% e 60%: luz moderada
  if (luminosidade >= inf && luminosidade <= sup) {
    digitalWrite(red, LOW);    // Desliga LED vermelho
    digitalWrite(green, LOW);  // Desliga LED verde
    digitalWrite(yellow, HIGH);// Liga LED amarelo

    lcd.setCursor(0, 1);
    lcd.print("                "); // Limpa a linha
    lcd.setCursor(0,1);
    lcd.print("Luminosidade:");
    lcd.print(media); // Mostra a média da luminosidade
  }
  
  // Se acima de 60%: muita luz
  else if (luminosidade > sup) {
    digitalWrite(yellow, LOW); // Desliga LED amarelo
    digitalWrite(green, LOW);  // Desliga LED verde
    digitalWrite(red, HIGH);   // Liga LED vermelho

    lcd.setCursor(0, 1);
    lcd.print("                "); // Limpa a linha
    lcd.setCursor(0,1);
    lcd.print("Luminosidade:");
    lcd.print(media); // Mostra a média da luminosidade

    tone(buzzer, 1000); // Emite som com o buzzer (1000 Hz)
    delay(50);          // Aguarda 50 ms
    noTone(buzzer);     // Para o som
  }

  // Se abaixo de 30%: pouca luz
  else {
    digitalWrite(yellow, LOW); // Desliga LED amarelo
    digitalWrite(red, LOW);    // Desliga LED vermelho
    digitalWrite(green, HIGH); // Liga LED verde

    lcd.setCursor(0, 1);
    lcd.print("                "); // Limpa a linha
    lcd.setCursor(0,1);
    lcd.print("Luminosidade:");
    lcd.print(media); // Mostra a média da luminosidade
  }

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}