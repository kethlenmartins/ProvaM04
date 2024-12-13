#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 41 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int botao = 18;  // pino para controle do botão
int statusBotao;  // variável que lê o estado do botão
int ultimoStatusBotao = LOW; // Variável Backup que salvará o último status do botão
int contador = 0; // Variável que armazena quantas vezes o botão foi pressionado

unsigned long tempoUltimoDebounce = 0; // Variável que armazenará o tempo do último Debounce
unsigned long tempoDebounce = 50;      // Tempo (em milissegundos)que é necessário manter o botão pressionado para ter a certeza de que ele foi pressionado de fato.

const int ldr = 4;  // Pino utilizado para controle do ldr
int limite=600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_verde,OUTPUT);
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(botao, INPUT); // Inicia o botão como input

  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600
}

void loop() {
  debounceBotao();
  contagem();  

  int ldrstatus=analogRead(ldr);

  if(ldrstatus<=limite){
    Serial.println("Está escuro, ativando o modo noturno.");
    Serial.println("Status do LDR: ");
    Serial.print(ldrstatus);
    modo_noturno();
  }else{
    Serial.println("Está claro, ativando o modo diurno.");
    Serial.println("Status do LDR: ");
    Serial.print(ldrstatus);
    modo_diurno();
  }

  if(ldrstatus>39 && led_vermelho==HIGH && statusBotao==HIGH) { // se estiver de dia, o semáforo estiver fechado e o botão for apertado uma vez, abrir o sinal depois de 1s
    delay(1000);
    Serial.println("O botão foi apertado três vezes. Abrindo o semáforo.");
    modo_diurno();
  }
}

void modo_noturno () {
  digitalWrite(led_amarelo, HIGH);
  delay(1000);
  digitalWrite(led_amarelo, LOW);
  delay(1000);
  digitalWrite(led_amarelo, HIGH);
}

void modo_diurno () {
  digitalWrite(led_verde, HIGH);
  delay(2000);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, HIGH);
  delay(2000);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, HIGH);
  delay(5000);
  digitalWrite(led_vermelho, LOW);
}

void debounceBotao() {

  int leitura = digitalRead(botao);   

  if (leitura != ultimoStatusBotao) {   
    tempoUltimoDebounce = millis();  

  if ((millis() - tempoUltimoDebounce) > tempoDebounce) { 
    if (leitura != statusBotao) {          
      statusBotao = leitura;                     
      if (statusBotao == HIGH) {            
        contador++;                              
      }
    }
  }
  ultimoStatusBotao = leitura; 

}}


void contagem() {
  if (contador == 3) { 
    if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String link = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(link.c_str());

    int codigo_resposta_http = http.GET(); // Código do Resultado da Requisição HTTP

    if (codigo_resposta_http>0) {
      Serial.print("Código de resposta HTTP: ");
      Serial.println(codigo_resposta_http);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Código de erro: ");
      Serial.println(codigo_resposta_http);
      }
      http.end();
    }

  else {
    Serial.println("O Wifi foi desconectado");
  }
}
}
