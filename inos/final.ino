#include <DHT.h>
#include <ArduinoJson.h>

const int potPin = A0;
#define MOTOR_PIN 9 
#define DHTPIN 4     // Define a porta digital 4 como a porta de dados do sensor
#define DHTTYPE DHT11 // Define o tipo de sensor como DHT11
const int ldrPin = A1; // Pino A1 como entrada analógica para o sensor LDR
DynamicJsonDocument doc(1024);


DHT dht(DHTPIN, DHTTYPE); // Inicializa o objeto DHT

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  int ldrValue = analogRead(ldrPin); // Lê o valor analógico do sensor LDR
  Serial.begin(9600); // Inicializa a comunicação serial com a taxa de baud 9600
  dht.begin();        // Inicializa o sensor DHT
}

void loop() {
  delay(2000); // Aguarda 2 segundos para evitar leituras frequentes
  String data_JSON;

  float valph =  analogRead(potPin);
  float ph = (valph / 73.00) - 7;


  // le a quantidade de luz do ambiente
  int ldrValue = analogRead(ldrPin); // Lê o valor analógico do sensor LDR

  // Lê a umidade relativa
  float humidity = dht.readHumidity();

  // Lê a temperatura em graus Celsius
  float temperature = dht.readTemperature();

  // Verifica se a leitura do sensor foi bem-sucedida
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro ao ler o sensor DHT!");
  } else {
    // Exibe os dados no monitor serial
    doc["humi"] = humidity;
    doc["temp"] = temperature;
    doc["light"] = ldrValue * 15;
    doc["ph"] = ph;
    doc["plant_id"] = 1;
    if (temperature > 26) {
      // Liga o motor DC
      digitalWrite(MOTOR_PIN, HIGH);
    } else {
      // Desliga o motor DC
      digitalWrite(MOTOR_PIN, LOW);
    }
  serializeJson(doc, data_JSON);
  Serial.println(data_JSON);
  }
  delay(1000);
}