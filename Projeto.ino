#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

const int pinoBotao = 23;    
const int ledPin =  2; 

const char* ssid = "nome da rede";
const char* password =  "senha";

char jsonOutput[1100];

void setup() {

  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP( ssid, password);

  pinMode(ledPin, OUTPUT);  
  pinMode(pinoBotao, INPUT_PULLUP);  

}

void loop() {
  int botaoEstado = digitalRead(pinoBotao);

  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {

    Serial.println("WiFi conectado com sucesso!");
    Serial.println(WiFi.localIP());

    HTTPClient client;

    Serial.println("Enviando para: ");
    Serial.println("http://192.168.15.5:5000/sensor_api");
    
    client.begin("http://192.168.15.5:5000/sensor_api");  //HTTP
    client.addHeader("Content-Type","application/json");
    //client.addHeader("chave","porta");

    const size_t CAPACITY = JSON_OBJECT_SIZE(10);
    StaticJsonDocument<CAPACITY> doc;

    JsonObject object = doc.to<JsonObject>();

    if (botaoEstado != HIGH) {  
      object["tipo"] = "Presença";
      object["dados"] = "Ocupado";
      digitalWrite(ledPin, HIGH);
    }else{
      object["tipo"] = "Presença";
      object["dados"] = "Vazio";
      digitalWrite(ledPin, LOW);
    }

    serializeJson(doc, Serial);
    serializeJson(doc, jsonOutput);

    int httpCode = client.POST(String(jsonOutput));

    if (httpCode > 0){
      String payload = client.getString();
      Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println(payload);   

      client.end();      
    }
    else{
      Serial.println("Erro na requisição do HTTP");      
    }
  }
  else{
    Serial.println("Conexão com o WIFI perdida");
  }

  delay(5000);
}