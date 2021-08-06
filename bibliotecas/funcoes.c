#include "funcoes.h"

// Funcao para gravar o log no cartão SD
void gravar(time_t t)
{
    // Recebendo o valor da temperatura utilizando o i2c
      float T = ;
      
    // Recebendo o valor da umidade utilizando o i2c
      float U = ;
      
      
  log = fopen("log.txt", "a");
  fputs("Data: ");
  fputs(day(t));
  fputs("/");
  if (month(t) < 10)
  {
    fputs("0");
  }
  fputs(month(t));
  fputs("/");
  fputs(year(t));
  fputs(" Hora: ");
  if (hour(t) < 10)
  {
    fputs("0");
  }
  fputs(hour(t));
  fputs(":");
  if (minute(t) < 10)
  {
    fputs("0");
  }
  fputs(minute(t));
  fputs(":");
  if (second(t) < 10)
  {
    fputs("0");
  }
  fputs(second(t));
  fputs(" Temperatura: ");
  fscanf(log,%f,T);
  
  fputs("/");
  
  fputs(" Umidade: ");
  fscanf(log, %f, U);
  
  fputs("/");
  
  fclose (log);
    }
}

void LCDshow()
{
 // Recebendo o valor da temperatura via i2c
  float T = ;
  
 // Recebendo o valor da umidade via i2c
  float U =
 
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
  lcd.print(U);
  delay(10000);
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

//funcao para configurar o tempo
void time()
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;
 
  //Verifica se foi setado um novo horario
  //Formato: ano, mês, dia, hora, minuto, segundo
  
      int y = Serial.parseInt();
      tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      RTC.set(t);
      setTime(t);
      printDateTime(t);
    
  }
