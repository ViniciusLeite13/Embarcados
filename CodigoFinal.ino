//Programa: Datalogger com Arduino, modulo RTC DS3231, cartao SD
// Os sensores utilizados foram: TMP36, SENSOR PRESSAO, SENSOR UMIDADE


#include <DS3232RTC.h> // inclusao da biblioteca para o modulo timer
#include <Adafruit_Sensor.h> // inclusão da biblioteca para o sensor BME280
#include <Adafruit_BME280.h> // inclusão da biblioteca para o sensor BME280
#include <Streaming.h>
#include <Time.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
 
//Pino CS do modulo cartao SD
int CS_PIN = 4;

// Define os pinos do disply LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


File file;
 
void setup(void)
{
  Serial.begin(9600);
  //Inicializa o cartao SD
  inicia_SD();
  
  //Inicializa o display LCD
  lcd.begin(16, 2);
  
  //Inicializa o sensor de umidade
  dht.begin();
  
  //Inicializa o sensor BME280
  status = bme.begin();
 
  //Sincroniza a biblioteca Time com o RTC a cada 5 minutos
  setSyncProvider(RTC.get);
  Serial << F("Sincronizando com o RTC...");
  if (timeStatus() != timeSet) Serial << F(" Falha!");
  Serial << endl;
}
 
void loop(void)
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;
 
  //Verifica se foi setado um novo horario
  //Formato: ano, mês, dia, hora, minuto, segundo
  if (Serial.available() >= 12) {
    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial<<F("Erro: Ano deve ter dois ou quatro digitos!") <<endl;
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    //(y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      RTC.set(t);
      setTime(t);
      Serial << F("Horario modificado para: ");
      printDateTime(t);
      Serial << endl;
      while (Serial.available() > 0) Serial.read();
    }
  }
 
  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    //Grava dados no cartao a cada 1 minuto
    if (second(t) == 0)
    {
      Serial.println("Gravando dados no cartao SD");
      grava_SD(t);
      LCDshow();
    }
    Serial << endl;
  }
}
 
// Mostrar data e hora na serial

void printDateTime(time_t t)
{
  printI00(day(t), 0);
  Serial << monthShortStr(month(t)) << _DEC(year(t));
  Serial << ' ';
  //printTime(t);
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}
 
// Funcao para gravar o log no cartão SD
void grava_SD(time_t t)
{


      float T = bme.readTemperature(); // Funcao implementada nas bibliotecas do BME280
      
      float P = bme.readPressure / 100.0F(); // Funcao implementada nas bibliotecas do BME280
      
      float U = bme.readHumidity(); // Funcao implementada nas bibliotecas do BME280
      
  abre_arquivo_gravacao("log.txt");
  file.print("Data: ");
  file.print(day(t));
  file.print("/");
  if (month(t) < 10)
  {
    file.print("0");
  }
  file.print(month(t));
  file.print("/");
  file.print(year(t));
  file.print(" Hora: ");
  if (hour(t) < 10)
  {
    file.print("0");
  }
  file.print(hour(t));
  file.print(":");
  if (minute(t) < 10)
  {
    file.print("0");
  }
  file.print(minute(t));
  file.print(":");
  if (second(t) < 10)
  {
    file.print("0");
  }
  file.print(second(t));
  file.print(" Temperatura: ");
  file.println(T);
  
  file.print("/");
  
  file.print(" Pressao: ");
  file.println(P);
  
  file.print("/");
  
  file.print(" Umidade: ");
  file.println(U);
  
  fecha_arquivo();
}
 
 
//Correcao para imprimir "00" ao inves de "0" caso
//o valor seja menor do que 10
void printI00(int val, char delim)
{
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}

void inicia_SD()
{
  pinMode(CS_PIN, OUTPUT);
 
  if (SD.begin())
  {
  } else
  {
    return;
  }
}
 
int abre_arquivo_gravacao(char filename[])
{
  file = SD.open(filename, FILE_WRITE);
 
  if (file)
  {
    return 1;
  } else
  {
    return 0;
  }
}
 
void fecha_arquivo()
{
  if (file)
  {
    file.close();
  }
}

// Funcao para mostrar na tela valor dos sensores
void LCDshow()
{
 
  float T = bme.readTemperature(); // Funcao implementada nas bibliotecas do BME280
   
  float P = bme.readPressure / 100.0F(); // Funcao implementada nas bibliotecas do BME280
     
  float U = bme.readHumidity(); // Funcao implementada nas bibliotecas do BME280
      
 
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  lcd.print(T);
  delay(10000);
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.setCursor(3, 1);
  lcd.print(P);
  delay(10000);
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.setCursor(3, 1);
  lcd.print(U);
  delay(10000);
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}
