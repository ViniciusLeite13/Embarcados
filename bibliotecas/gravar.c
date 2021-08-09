#include "gravar.h"

// Funcao para gravar o log no cartão SD
void gravar(time_t t, T, P, U)
{
            
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

