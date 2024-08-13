#include <Adafruit_NeoPixel.h>

#define PIN 6            // Пин, к которому подключена матрица NeoPixel
#define NUMPIXELS 64     // Общее количество пикселей в матрице
#define BUTTON_PIN 5     // Пин, к которому подключена кнопка
#define MOSFET_PIN 3     // Пин, управляющий мосфетом
#define DEBUG 1          // Установите 1 для включения отладочных сообщений, 0 для отключения

#if DEBUG
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Массив с цифрами и символами (0-10 и дополнительный символ)
uint8_t digits[12][8][8] = {
  // Цифра 0
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 1
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 2
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 3
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 4
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 5
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 6
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 7
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 8
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 9
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  // Цифра 10
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  },
};

uint32_t orange = pixels.Color(255, 165, 0);  // Оранжевый цвет
uint32_t red = pixels.Color(0, 0, 0);       // Красный цвет
uint32_t green = pixels.Color(0, 255, 0);     // Зеленый цвет
uint32_t black = pixels.Color(0, 0, 0);       // Черный цвет

int currentDigit = 10;  // Начинаем с цифры 10
bool buttonLocked = false;  // Флаг блокировки кнопки
unsigned long lockStartTime; // Время начала блокировки

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, HIGH); // Включаем мосфет
  pixels.begin();
  pixels.clear();

  if (DEBUG) {
    Serial.begin(115200);
    DEBUG_PRINTLN("Запуск программы...");
    DEBUG_PRINT("Отображаем начальный символ: ");
    DEBUG_PRINTLN(currentDigit);
  }

  displayDigit(currentDigit, orange, red); // Отображаем цифру 10
}

void loop() {
  // Если достигнута цифра 0, кнопка больше не должна реагировать
  if (currentDigit == 0) {
    return;
  }

  if (digitalRead(BUTTON_PIN) == LOW && !buttonLocked) {
    // Если кнопка нажата и не заблокирована
    buttonLocked = true;
    lockStartTime = millis();
    
    DEBUG_PRINTLN("Кнопка нажата, блокируем и выключаем мосфет.");
    
    digitalWrite(MOSFET_PIN, LOW); // Выключаем мосфет
    displayDigit(11, green, black); // Отображаем дополнительный символ

    DEBUG_PRINTLN("Отображен дополнительный символ (11).");

    // Блокируем кнопку на 2 минуты
    delay(60000);  // Замените на 120000 для 2 минут

    buttonLocked = false;
    DEBUG_PRINTLN("Блокировка кнопки снята.");

    if (currentDigit > 0) {
      currentDigit--; // Переходим к следующей цифре
      
      DEBUG_PRINT("Отображаем следующую цифру: ");
      DEBUG_PRINTLN(currentDigit);
      
      digitalWrite(MOSFET_PIN, HIGH); // Включаем мосфет
      displayDigit(currentDigit, orange, red);
    } else {
      DEBUG_PRINTLN("Достигнута цифра 0, больше не реагируем на кнопку.");
    }
  }
}

void displayDigit(int digit, uint32_t color1, uint32_t color0) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      int pixelNum = y * 8 + x;
      uint32_t color = (digits[digit][y][x] == 1) ? color1 : color0;
      pixels.setPixelColor(pixelNum, color);
    }
  }
  pixels.show();

  DEBUG_PRINT("Цифра ");
  DEBUG_PRINT(digit);
  DEBUG_PRINTLN(" отображена.");
}
