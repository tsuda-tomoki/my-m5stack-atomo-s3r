/**
 * @file display.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5AtomS3 Display Test
 * @version 0.1
 * @date 2023-12-13
 *
 *
 * @Hardwares: M5AtomS3
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5AtomS3: https://github.com/m5stack/M5AtomS3
 */

#include <M5Unified.h>
// 電源が入ったあとに {} 内が１回実行される

int eyeOffsetX = 0;

bool blinking = false;
unsigned long blinkStart = 0;
unsigned long lastBlink = 0;

String expression = "normal";

// 必須
// 電源ONときに一回だけ必ず実行される
void setup() {
  auto cfg = M5.config(); // M5Stack初期設定用の構造体を代入
  M5.begin(cfg); // M5デバイスの初期化

  M5.Display.setTextColor(WHITE); // テキストカラーを白に設定
}

// 電源がONになっているときに繰り返し実行される
// 必須
void loop() {
  M5.update(); // ボタン操作を読み込む ※ ボタン処理のときは必須

  unsigned long now = millis(); // プログラムがスタートしてからの時間 (ミリ秒)

  // まばたき開始
  if (!blinking && now - lastBlink > 4000) { // blinking = true かつ 最後にまばたきした時間が4sより上
    blinking = true;
    blinkStart = now;
    lastBlink = now;
  }

  // まばたき終了
  if (blinking && now - blinkStart > 150) {
    blinking = false;
  }

  drawFace();

  delay(33); // 33 ミリ秒停止
}

// 顔の描画処理
void drawFace() {
  M5.Display.fillScreen(BLACK); // スクリーンカラーを黒に設定

  int eyeY = 50;
  int leftEyeX = 40 + eyeOffsetX;
  int rightEyeX = 88 + eyeOffsetX;

  // まばたき中
  if (blinking) {
    M5.Display.fillRect(leftEyeX - 10, eyeY, 20, 3, WHITE); // 四角の描写
    M5.Display.fillRect(rightEyeX - 10, eyeY, 20, 3, WHITE);
  }
  else {
    // 通常目
    M5.Display.fillCircle(leftEyeX, eyeY, 10, WHITE); // 塗りつぶされた円を描写する, x軸, y軸, 半径, 色
    M5.Display.fillCircle(rightEyeX, eyeY, 10, WHITE);
  }
}
