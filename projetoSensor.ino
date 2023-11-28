#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "https://sensoriot-8162d-default-rtdb.europe-west1.firebasedatabase.app/"
#define FIREBASE_AUTH "MyN71EyEYqJ8bfzk5tW8411EqMbE9W5UJdleHqY9"

const char* ssid = "Visitantes";      // Insira o nome da sua rede Wi-Fi
const char* password = "Guest20.2";  // Insira a senha da sua rede Wi-Fi

#define sensor 14
#define ledVermelho 4
#define ledVerde 5

#define PINO_RTS 15 // Certifique-se de verificar o número correto do pino RTS

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Configuração do pino RTS como saída
  pinMode(PINO_RTS, OUTPUT);

   // Conectar à rede Wi-Fi
  WiFi.begin(ssid, password);
  delay(1000);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 30) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
    tentativas++;
  }
  Serial.println("Conectado ao WiFi!");

  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(sensor, INPUT);
  digitalWrite(sensor, LOW);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  if (digitalRead(sensor)) {
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    Serial.println("Movimento detectado");

    // Atualize diretamente o nó "sensor" no Firebase
    Firebase.setBool("/sensor", true);
    Serial.println("Atualização no Firebase bem-sucedida");
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    Serial.println("Nenhum movimento detectado");

    // Atualize diretamente o nó "sensor" no Firebase
    Firebase.setBool("/sensor", false);
    Serial.println("Atualização no Firebase bem-sucedida");
  }

  delay(1000);
}
