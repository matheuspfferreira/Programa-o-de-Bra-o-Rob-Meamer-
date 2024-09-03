// Importação de Bibliotecas
#include <Servo.h>

// Declaração de Constantes
#define decimoSegundo 100
#define anguloPartida 90

// Declaração dos Servo Motores
Servo primeiroMotor;
Servo segundoMotor;
Servo terceiroMotor;
Servo quartoMotor;

// Declaração de Funções
void configuraMotores(Servo array[], int portas[], int quantidade);
void inicializaAngulos(Servo array[], int quantidade, int angulo);
void configuraJoystick(int array[], int quantidade);
void variacaoMotores(Servo motores[], int array[], int quantidade);

// Declaração de Array - Armazenar os Servo Motores Utilizados
Servo motores[] = {primeiroMotor, segundoMotor, terceiroMotor, quartoMotor};

// Declação de Array - Armazenar as Portas dos Servo Motores
int portasMotores[] = {5, 6, 9, 10};

// Declaração de Array - Armazenar as Portas dos Joysticks
int portasJoystick[] = {A0, A1, A2, A3};

// Declaração de Variáveis Numéricas
int quantidadeMotores = sizeof(motores) / sizeof(motores[0]);
int quantidadePortas = sizeof(portasJoystick) / sizeof(portasJoystick[0]);

void setup() {

  // Inicialização do Monitor Serial
  Serial.begin(9600);

  // Configuração dos Servo Motores - Anexo dos Servo Motores às Portas
  configuraMotores(motores, portasMotores, quantidadeMotores);

  // Inicialização dos Servo Motores em 90 Graus
  inicializaAngulos(motores, quantidadeMotores, anguloPartida);

  // Inicialização dos Dois Joysticks
  configuraJoystick(portasJoystick, quantidadePortas);
 
}

void loop() {

  // Movimentação dos Servo Motores
  variacaoMotores(motores, portasJoystick, quantidadeMotores);

  // Esperando por 0.1s
  delay(decimoSegundo);

}

// Inicialização da Função de Anexo dos Servo Motores às Portas
void configuraMotores(Servo array[], int portas[], int quantidade){

  for (int i = 0; i < quantidade; i++){
    array[i].attach(portas[i]);
  }

}

// Inicialização da Função de Definição do Ângulo dos Servo Motores
void inicializaAngulos(Servo array[], int quantidade, int angulo){

  for (int i = 0; i < quantidade; i++){
    array[i].write(angulo);
  }

}

// Inicialização da Função de Configuração dos Joysticks
void configuraJoystick(int array[], int quantidade){

  for (int i = 0; i < quantidade; i++){
    pinMode(array[i], INPUT);
  }

}

// Inicialização da Função de Variação do Ângulo do Primeiro Servo Motor
void variacaoMotores(Servo motores[], int array[], int quantidade){

  // Declaração de Variáveis de Ambiente
  int anguloMinimo = 0, anguloMaximo = 180;

  for (int i = 0; i < quantidade; i++){

    if (!(i == 0)){

      if (i == 1){
        anguloMinimo = 45, anguloMaximo = 135;
      } else if (i == 2){
        anguloMinimo = 50, anguloMaximo = 90;
      } else {
        anguloMinimo = 90, anguloMaximo = 130;
      }

    }

    motores[i].write(map(analogRead(array[i]), 0, 1023, anguloMinimo, anguloMaximo));
    
  }

}