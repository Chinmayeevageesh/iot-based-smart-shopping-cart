// IoT-Based Smart Shopping Cart
// Controller: ESP32-CAM
// Description: RFID-based automated billing system
// Note: This code was implemented as part of an academic mini project
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===== WiFi =====
const char* ssid = "Alfiya";
const char* password = "12102006";

// ===== Server for barcode =====
String serverPost = "http://10.87.244.101/iot_project/frontend/esp_post.php";

// ===== LCD =====
#define I2C_SDA 18
#define I2C_SCL 17
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== Buzzer =====
#define BUZZER 13

// ===== Buttons =====
#define SCAN_BUTTON 12

float totalAmount = 0.0;

// ===== Beeps =====
void beepSuccess() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 2000, 150);
    delay(200);
  }
}

void beepFail() {
  tone(BUZZER, 500, 700);
  delay(800);
}

void beepWiFi() {
  tone(BUZZER, 1500, 300);
  delay(350);
}

// ===================================================================
//                         SETUP
// ===================================================================
void setup() {
  Serial.begin(115200);
  delay(10);

  // LCD SETUP
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Smart Cart Init");
  delay(800);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Button
  pinMode(SCAN_BUTTON, INPUT_PULLUP);

  // ===== YOUR EXACT WIFI BLOCK =====
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  lcd.clear();
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.print("WiFi Connected");

  beepWiFi();   // one beep to confirm WiFi success
  delay(1200);

  lcd.clear();
  lcd.print("Ready to Scan!");
}

// ===================================================================
//                         LOOP
// ===================================================================
void loop() {
  if (digitalRead(SCAN_BUTTON) == LOW) {
    scanBarcode();
    delay(1500);
  }
}

// ===================================================================
//                        BARCODE SCAN FUNCTION
// ===================================================================
void scanBarcode() {
  lcd.clear();
  lcd.print("Scanning...");
  Serial.println("Requesting scan...");

  if (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.print("WiFi Lost!");
    beepFail();
    return;
  }

  HTTPClient http;
  http.begin(serverPost);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int response = http.POST("request=scan");

  if (response != 200) {
    lcd.clear();
    lcd.print("Scan Failed!");
    beepFail();
    http.end();
    return;
  }

  String payload = http.getString();
  http.end();

  Serial.println(payload);

  String name = extractValue(payload, "name");
  float price = extractValue(payload, "price").toFloat();

  if (name == "" || price == 0) {
    lcd.clear();
    lcd.print("Invalid Code!");
    beepFail();
    return;
  }

  totalAmount += price;

  // LCD OUTPUT
  lcd.clear();
  lcd.print(name.substring(0, 16));
  lcd.setCursor(0, 1);
  lcd.print("Rs:");
  lcd.print(price, 2);

  beepSuccess();  // 3 beeps for success

  delay(2000);

  lcd.clear();
  lcd.print("Total: Rs ");
  lcd.print(totalAmount, 2);
  delay(1200);

  lcd.clear();
  lcd.print("Ready to Scan!");
}

// ===================================================================
//                     JSON PARSE HELPER
// ===================================================================
String extractValue(String json, String key) {
  int start = json.indexOf("\"" + key + "\":");
  if (start == -1) return "";
  start += key.length() + 3;
  int end = json.indexOf(",", start);
  if (end == -1) end = json.indexOf("}", start);
  String value = json.substring(start, end);
  value.replace("\"", "");
  return value;
}
