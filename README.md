# Estação Meterológica - Sistemas Embarcados

Obs: Trabalho ainda em desenvolvimento - continuaremos desenvolvendo no final de semana

Trabalho realizado por:

  Gabriel Lutffalla Estevam- nº USP 10309191
  
  Vinicius Leite - nº USP 9796360
  
  Vitor Monarin Tristão - nº USP 10308993

## Introdução

Nosso grupo optou pelo projeto de uma Estação Meteorológica, capaz de medir a tempratura e umidade relativa do ar do ambiente em que está inserida. Foi definida uma utilização específica para a estação a ser montada, a partir da qual poderíamos definir claros objetivos e funções a serem realizadas, focalizando a definição dos parâmetros do projeto. A utilização definida foi para uso na agricultura, sendo possível monitorar plantações, obtendo dados de temperatura e umidade relativa do ar, que podem vir a ser utilizados para tomadas de decisões pelo agricultor. A elaboração de algoritmos responsáveis por unir os dados quantitativamente e elaborar tomadas de decisões está fora do escopo do projeto, que limita-se à obtenção dos dados em si e seu fornecimento bruto ao usuário.

O fluxograma a seguir descreve qualitativamente os componentes e funcionamento do sistema:

![Fluxograma](https://user-images.githubusercontent.com/70172639/128652794-9d6ec1bf-f1fa-4d71-994a-60a202df6239.png)


## Componentes Utilizados

### Módulo e Carrier Board

Foi utilizada a Toradex Colibri VF50 com Carrier Board Viola Plus V1.2. A Colibri VF50 é um módulo SODIMM System on Chip, que possui processador ARM Cortex-A5, permite rodar um sistema operacional Linux, e oferece possibilidades de interface GPIO, I2C, SPI, RMII, UART, CAN, USB, ethernet, etc.

### RTC DS3231

Esse componente possui a função de fornecer a data e hora para armazenar os dados obtidos no log, possuindo a função de facilitar a análise dos dados, auxiliando a detectar padrões que possam ser maléficos para a colheita em determinados horários. A escolha por esse componente se deve ao fato de conseguir detectar falta de energia e acionar uma bateria caso seja necessário, além de possuir ajuste automático de meses que possuem menos de 31 dias e correção de ano bissexto. Conta também com um sensor próprio de temperatura e um cristal oscilador, que garante maior precisão.

### Oak-RH

O sensor escolhido foi o Oak-RH, um único sensor capaz de obter dados de umidade relativa do ar e temperatura ambiente, com amplo suporte para a Toradex. O sensor é capaz de medir umidade relativa do ar entre 0 e 100%, com resolução de 0,05%. Além disso, é capaz de medir temperaturas ambiente de -10°C a 85°C, com uma resolução de 0,01°C e precisão de 2°C. Portanto, é um sensor que atende bastante nossas necessidades.

Os sensores Oak são sensores USB. As informações são transferidas em “pacotes” de estrutura fixa, chamados Reports. Existem os interrupt reports e os feature reports. Os sensores Oak usam os interrupt reports para transferir dados dos sensores e feature reports para transferir parâmetros de configuração do sensor. O sensor possui biblioteca própria, o que facilita a programação.

### Display

Foi escolhido um display LCD cristal padrão com duas linhas e dezesseis colunas, luzde fundo azul e dígitos brancos. Ele se liga ao controlador por quatro pinos de dados edois pinos de controle. O código foi implementado visando que uma variável seja exibidade cada vez, por um período de 10 segundos cada.


## Desenvolvimento

### Configuração da Toolchain, Build e Run

A placa Toradex Colibri VF50 será usada de forma embarcada. Para a configuração inicial da placa, é necessário se comunicar com ela a partir do computador host do laboratório. 

Inicialmente, é necessário baixar o SDK da Toradex do site para o diretório home do computador e instalá-la com os comandos no terminal do Linux:

    chmod +x angstrom-glibc-x86_64-armv7at2hf-neon-v2017.12-toolchain.sh
    
    ./angstrom-glic-x86_64-armv7at2hf-neon-v2017.12-toolchain.sh
    
Em seguida, exporta-se as variáveis para cross-compiling e executa-se o script:

    . /usr/local/oecore-x86_64/environment-setup-armv7at2hf-neon-angstrom-linux-gnueabi
    
    . environment-setup-armv7at2hf-neon-angstrom-linux-gnueabi
    
Para compilar o código na placa, faz-se o cross-compiling, envia-se ao IP do target e o executa:

    ${CC} -Wall main.c -o codigoARM
    
    scp codigoARM root@172.17.2.121:/home/root
    
    ./codigoARM


### Comunicação

O protocolo de comunicação escolhido foi o I2C.

Para I2C, é necessário conectar 2 pinos (SDA e SCL). Com a Colibri VF50 original, esses pinos são o 194 (SDA) e 196 (SCL), porém, com a adição da Viola com o conector de extensão X9, esses pinos passam a ser os pinos 5 (SCL) e 6 (SDA) da Viola.


