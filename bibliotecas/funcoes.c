#include "grava.h"

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

