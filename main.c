#include <DS3232RTC.h> // inclusao da biblioteca para o modulo timer
#include <stdio.h>
#include <time.h>
#include <Streaming.h>
#include "funcoes.h"

void main (){
int x = 0;
File *log;

while ( x < 1){
  void time();
 
  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    
    //Grava dados no cartao a cada 1 minuto
    if (second(t) == 0)
    {
      gravar(t);
      LCDshow();
    }
  }
}
}
