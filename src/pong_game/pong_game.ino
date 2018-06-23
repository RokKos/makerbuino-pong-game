#include <Gamebuino.h>
#include <SPI.h>

Gamebuino game_buino_;

// PLAYERS DATA
int player_score_01_ = 0;
int player_score_02_ = 0;
const int kPlayerHeight = 16;  // this is 1/3 MAKERbuino screen
const int kPlayerWidth = 3;
const int kPlayerVelocityY = 2;
const int kTopScreenOffset = LCDHEIGHT - kPlayerHeight;
int player_01_x_ = 0;
int player_01_y_ = kTopScreenOffset / 2;
int player_02_x_ = LCDWIDTH - kPlayerWidth;
int player_02_y_ = player_01_y_;

void setup() {
  // put your setup code here, to run once:
  game_buino_.begin();
  game_buino_.titleScreen(F("Pong Tutorial"));
  game_buino_.pickRandomSeed();
  game_buino_.battery.show = false;
  game_buino_.display.fontSize = 2;
}

void ProcesInputFromPlayers() {
  if (game_buino_.buttons.repeat(BTN_UP, 1)) {
    player_01_y_ = max(0, player_01_y_ - kPlayerVelocityY);
  }
  if (game_buino_.buttons.repeat(BTN_DOWN, 1)) {
    player_01_y_ = min(kTopScreenOffset, player_01_y_ + kPlayerVelocityY);
  }

  if (game_buino_.buttons.repeat(BTN_A, 1)) {
    player_02_y_ = max(0, player_02_y_ - kPlayerVelocityY);
  }
  if (game_buino_.buttons.repeat(BTN_B, 1)) {
    player_02_y_ = min(kTopScreenOffset, player_02_y_ + kPlayerVelocityY);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // update returns true every 50 milisecons, this means we have 20 FPS
  if (game_buino_.update()) {
    ProcesInputFromPlayers();

    // Draw players
    game_buino_.display.fillRect(player_01_x_, player_01_y_, kPlayerWidth,
                                 kPlayerHeight);
    game_buino_.display.fillRect(player_02_x_, player_02_y_, kPlayerWidth,
                                 kPlayerHeight);
  }
}
