# Trabalho final - Sistemas Embarcados, 2021

Obs: Trabalho ainda em desenvolvimento

Trabalho realizado por:

  Gabriel Lutffalla Estevam - nº USP 10309191

  Vinicius Leite - nº USP 9796360

  Vitor Monarin Tristão - nº USP 10308993

## Introdução

Nosso grupo optou pelo projeto de uma estação meteorológica. Inicialmente, o grupo pensou em definir uma utilização para a estação a ser montada, a partir da qual poderíamos definir objetivos e funções a serem realizadas. A utilização definida foi para uso na agricultura, sendo possível monitorar plantações, obtendo dados de temperatura e umidade relativa do ar, que podem vir a ser utilizados para tomadas de decisões. Obs: o grupo não chegou a montar algoritmos responsáveis por unir os dados quantitativamente e elaborar tomadas de decisões, limitando-se à obtenção dos dados em si.

O fluxograma a seguir mostra uma ideia de como seria o funcioanmento do sistema:

![WhatsApp Image 2021-08-05 at 21 14 44](https://user-images.githubusercontent.com/82786123/128452197-1c6f21d0-bb1a-4ab9-800a-294f3cd74c8a.jpeg)


## Componentes Utilizados

### RTC DS3231

Esse componente possui a função de fornecer a data e hora para armazenar os dadosobtidos no log, possuindo a função de facilitar a análise dos dados, auxiliando a detectarpadrões que possam ser maléficos para a colheita em determinados horários. A escolhapor esse componente se deve ao fato de conseguir detectar falta de energia e acionar umabateria caso seja necessário, possui ajuste automático de meses que possuem menos de 31dias e correção de ano bissexto. Além disso, possui um sensor próprio de temperatura eum cristal oscilador para garantir maior precisão.

### Oak-RH

O sensor escolhido foi o Oak-RH, um único sensor capaz de obter dados de umidade relativa do ar e temperatura ambiente, com amplo suporte para a Toradex. O sensor é capaz de medir umidade relativa do ar entre 0 e 100%, com resolução de 0,05%. Além disso, é capaz de medir temperaturas ambiente de -10°C a 85°C, com uma resolução de 0,01°C e precisão de 2°C. Portanto, é um sensor que atende bastante nossas necessidades.

Os sensores Oak são sensores USB. As informações são transferidas em “pacotes” de estrutura fixa, chamados Reports. Existem os interrupt reports e os feature reports. Os sensores Oak usam os interrupt reports para transferir dados dos sensores e feature reports para transferir parâmetros de configuração do sensor. O sensor possui biblioteca própria, o que facilita a programação.

### Display

Foi escolhido um display LCD cristal padrão com duas linhas e dezesseis colunas, luzde fundo azul e dígitos brancos. Ele se liga ao controlador por quatro pinos de dados edois pinos de controle. O código foi implementado visando que uma variável seja exibidade cada vez, por um período de 10 segundos cada.


## Desenvolvimento

### Configuração da Toolchain, Build e Run

A placa Toradex Colibri VF50 será usada de forma embarcada. Para a configuração inicial da placa, é necessário se comunicar com ela a partir do computador host do laboratório. 

Inicialmente, é necessário baixar o SDK da Toradex do site para o diretório home do computador e instalá-la com os comandos:

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

O protocolo de comunicação escolhido foi o I2C


