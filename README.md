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


### BME280

O sensor escolhido foi o sensor BME280, fabricado pela Bosch Sensortech. Este é um sensor digital combinado, capaz de obter dados de temperatura, pressão atmosférica e umidade do ar, ou seja, vai ao encontro dos nossos objetivos por ser um sensor de baixo custo por permitir efetuar a leitura de 3 grandezas diferentes com um único sensor. O sensor é bastante compacto, sendo muito fácil de ser embarcado. O sensor em si possui dimensões de 2,5 x 2,5 x 0,93 mm³ e vem em uma placa como mostrado a seguir:


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


### Referências

    https://developer.toradex.com/getting-started?som=colibri-vf61&board=colibri-evaluation-board&os=linux&desktop=linux

    https://developer.toradex.com/knowledge-base/i2c-linux

    https://developer.toradex.com/products/colibri-vf50#tab-carrier-boards

    https://github.com/BoschSensortec/BME280_driver
