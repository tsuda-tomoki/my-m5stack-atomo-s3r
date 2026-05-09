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

int eyeOffsetX = 0;

// まばたき
bool blinking = false;
unsigned long blinkStart = 0;
unsigned long lastBlink = 0;

// 表情
enum Expression {
  NORMAL,
  HAPPY,
  SLEEPY
};

Expression face = NORMAL;

unsigned long lastAction = 0;

// =====================================
// カプセル型の目
// =====================================
void drawEye(int x, int y, int w, int h) {

  M5.Display.fillRoundRect(
    x - w / 2,
    y - h / 2,
    w,
    h,
    w / 2,
    TFT_CYAN
  );
}

// =====================================
// 顔描画
// =====================================
void drawFace() {

  M5.Display.fillScreen(TFT_BLACK);

  // -------------------------
  // 目を少し下へ（口に近づける）
  // -------------------------
  int eyeY = 52;

  // 目の間を広めに
  int leftEyeX  = 32 + eyeOffsetX;
  int rightEyeX = 96 + eyeOffsetX;

  // -------------------------
  // まばたき
  // -------------------------
  if (blinking) {

    M5.Display.fillRoundRect(
      leftEyeX - 10,
      eyeY,
      20,
      4,
      2,
      TFT_CYAN
    );

    M5.Display.fillRoundRect(
      rightEyeX - 10,
      eyeY,
      20,
      4,
      2,
      TFT_CYAN
    );
  }
  else {

    switch (face) {

      // 通常
      case NORMAL:

        drawEye(leftEyeX, eyeY, 20, 36);
        drawEye(rightEyeX, eyeY, 20, 36);

        break;

      // 喜び
      case HAPPY:

        drawEye(leftEyeX, eyeY, 20, 28);
        drawEye(rightEyeX, eyeY, 20, 28);

        break;

      // 眠い
      case SLEEPY:

        drawEye(leftEyeX, eyeY, 24, 10);
        drawEye(rightEyeX, eyeY, 24, 10);

        break;
    }
  }

  // -------------------------
  // 口
  // 長くしてロボ感アップ
  // -------------------------
  switch (face) {

    case NORMAL:

      M5.Display.fillRoundRect(
        48,
        92,
        32,
        5,
        2,
        TFT_CYAN
      );

      break;

    case HAPPY:

      M5.Display.fillRoundRect(
        44,
        92,
        40,
        7,
        3,
        TFT_CYAN
      );

      break;

    case SLEEPY:

      M5.Display.fillRoundRect(
        50,
        94,
        28,
        4,
        2,
        TFT_CYAN
      );

      break;
  }
}

// =====================================
// setup
// =====================================
void setup() {

  auto cfg = M5.config();

  M5.begin(cfg);

  M5.Display.setRotation(0);

  lastAction = millis();
}

// =====================================
// loop
// =====================================
void loop() {

  M5.update();

  unsigned long now = millis();

  // -------------------------
  // まばたき開始
  // -------------------------
  if (!blinking &&
      now - lastBlink > 4000) {

    blinking = true;

    blinkStart = now;

    lastBlink = now;

    // 少し視線移動
    eyeOffsetX = random(-3, 4);
  }

  // -------------------------
  // まばたき終了
  // -------------------------
  if (blinking &&
      now - blinkStart > 120) {

    blinking = false;
  }

  drawFace();

  delay(33);
}
