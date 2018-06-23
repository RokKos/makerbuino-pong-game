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

// BALL DATA
const int kBallSize = 6;
int ball_x_ = player_02_x_ - kBallSize - 1;
int ball_y_ = player_01_y_;
int ball_velocity_x_ = 3;
int ball_velocity_y_ = 3;

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

void MoveBall() {
  ball_x_ += ball_velocity_x_;
  ball_y_ += ball_velocity_y_;

  bool is_ball_under_screen = ball_y_ + kBallSize > LCDHEIGHT;
  if (is_ball_under_screen) {
    ball_velocity_y_ *= -1;
    ball_y_ = LCDHEIGHT - kBallSize;
    game_buino_.sound.playTick();
  }

  bool is_ball_over_screen = ball_y_ + kBallSize < 0;
  if (is_ball_over_screen) {
    ball_velocity_y_ *= -1;
    ball_y_ = 0;
    game_buino_.sound.playTick();
  }

  bool is_ball_touching_player_01_paddle =
      ball_x_ + kBallSize < player_01_x_ &&
      ball_y_ < player_01_y_ + kPlayerHeight / 2 &&
      ball_y_ > player_01_y_ - kPlayerHeight / 2;
  if (is_ball_touching_player_01_paddle) {
    ball_velocity_x_ *= -1;
    ball_x_ = player_01_x_ + kBallSize + 1;
    game_buino_.sound.playTick();
  }

  bool is_ball_touching_player_02_paddle =
      ball_x_ + kBallSize > player_02_x_ &&
      ball_y_ < player_02_y_ + kPlayerHeight / 2 &&
      ball_y_ > player_02_y_ - kPlayerHeight / 2;
  if (is_ball_touching_player_02_paddle) {
    ball_velocity_x_ *= -1;
    ball_x_ = player_02_x_ - kBallSize - 1;
    game_buino_.sound.playTick();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // update returns true every 50 milisecons, this means we have 20 FPS
  if (game_buino_.update()) {
    ProcesInputFromPlayers();
    MoveBall();
    // Draw players
    game_buino_.display.fillRect(player_01_x_, player_01_y_, kPlayerWidth,
                                 kPlayerHeight);
    game_buino_.display.fillRect(player_02_x_, player_02_y_, kPlayerWidth,
                                 kPlayerHeight);

    // Draw Ball
    game_buino_.display.fillCircle(ball_x_, ball_y_, kBallSize);
  }
}
