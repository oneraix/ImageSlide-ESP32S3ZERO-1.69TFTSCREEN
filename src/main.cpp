#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "image.h" 

// --- CẤU HÌNH CHÂN ---
#define PIN_SCK  1
#define PIN_MOSI 2
#define PIN_RST  3
#define PIN_DC   4
#define PIN_CS   5
#define PIN_BLK  6 

// Cấu hình màn hình
Arduino_DataBus *bus = new Arduino_ESP32SPI(PIN_DC, PIN_CS, PIN_SCK, PIN_MOSI, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_ST7789(bus, PIN_RST, 0, true,240,280,0,20);

void setup() {
    Serial.begin(115200);

    // Bật đèn nền sáng tối đa 
    pinMode(PIN_BLK, OUTPUT);
    digitalWrite(PIN_BLK, HIGH); 

    gfx->begin();
    gfx->fillScreen(BLACK);
}

// Hàm vẽ ảnh theo kiểu rèm cửa (Wipe Down)
void drawWipeEffect(const uint16_t *bitmap) {
    int w = 240; // Chiều rộng ảnh
    int h = 280; // Chiều cao ảnh
    int chunk_height = 3; // Mỗi lần vẽ x dòng 

    for (int y = 0; y < h; y += chunk_height) {
        // Tính toán độ cao khoảng vẽ
        int current_chunk = (y + chunk_height > h) ? (h - y) : chunk_height;
        
        // Tìm vị trí bắt đầu trong mảng ảnh
        const uint16_t *offset_bitmap = bitmap + (y * w);
        gfx->draw16bitRGBBitmap(0, y, (uint16_t*)offset_bitmap, w, current_chunk);
        

        delay(10); 
    }
}

void loop() {
    // --- HIỂN THỊ ẢNH 1 ---
    drawWipeEffect(anh_so_1);
    delay(2000); 

    // --- HIỂN THỊ ẢNH 2 ---
    drawWipeEffect(anh_so_2);
    delay(2000);

    // --- HIỂN THỊ ẢNH 3 ---
    drawWipeEffect(anh_so_3); 
    delay(2000);

    // --- HIỂN THỊ ẢNH 4 ---
    drawWipeEffect(anh_so_4);
    delay(2000);

    // --- HIỂN THỊ ẢNH 5 ---
    drawWipeEffect(anh_so_5);
    delay(2000);
}