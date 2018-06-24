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
const int kBallSize = 4;
const int kBallVelocity = 3;
int ball_x_ = player_02_x_ - kBallSize - 1;
int ball_y_ = player_01_y_;
int ball_velocity_x_ = kBallVelocity;
int ball_velocity_y_ = kBallVelocity;

// LINES DATA
const int kNumberOfLines = 12;
const int kLineWidth = 2;
const int kLineHeight = LCDHEIGHT / kNumberOfLines;
const int kLineX = (LCDWIDTH - kLineWidth) / 2;

// BORDERS DATA
const int kBorderThickness = 1;

// HELPER VARIABLES
const int kOffsetFromPlayer01 = player_01_x_ + kPlayerWidth + kBallSize + 1;
const int kOffsetFromPlayer02 = player_02_x_ - kBallSize - 1;

void setup() {
  // put your setup code here, to run once:
  game_buino_.begin();
  game_buino_.titleScreen(F("Pong for 2 players\n BY: Rok Kos"));
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

  bool is_ball_over_screen = ball_y_ - kBallSize < 0;
  if (is_ball_over_screen) {
    ball_velocity_y_ *= -1;
    ball_y_ = kBallSize;
    game_buino_.sound.playTick();
  }

  bool is_ball_touching_player_01_paddle =
      ball_x_ - kBallSize < player_01_x_ + kPlayerWidth &&
      ball_y_ <= player_01_y_ + kPlayerHeight && ball_y_ > player_01_y_;
  if (is_ball_touching_player_01_paddle) {
    ball_velocity_x_ *= -1;
    ball_x_ = kOffsetFromPlayer01;
    game_buino_.sound.playTick();
  }

  bool is_ball_touching_player_02_paddle =
      ball_x_ + kBallSize > player_02_x_ &&
      ball_y_ <= player_02_y_ + kPlayerHeight && ball_y_ > player_02_y_;
  if (is_ball_touching_player_02_paddle) {
    ball_velocity_x_ *= -1;
    ball_x_ = kOffsetFromPlayer02;
    game_buino_.sound.playTick();
  }
}

void PlayersScoring() {
  bool reset_round = false;

  bool is_ball_behind_player_01 = ball_x_ + kBallSize < player_01_x_;
  if (is_ball_behind_player_01) {
    reset_round = true;
    ball_x_ = kOffsetFromPlayer01;
    ball_velocity_x_ = kBallVelocity;
    player_score_02_++;
  }

  bool is_ball_behind_player_02 =
      ball_x_ - kBallSize > player_02_x_ + kPlayerWidth;
  if (is_ball_behind_player_02) {
    reset_round = true;
    ball_x_ = kOffsetFromPlayer02;
    ball_velocity_x_ = -kBallVelocity;
    player_score_01_++;
  }

  if (reset_round) {
    ball_y_ = random(0, LCDHEIGHT - kBallSize);
    game_buino_.sound.playCancel();
  }
}

void PrintScore() {
  game_buino_.display.cursorX = 21;
  game_buino_.display.cursorY = 8;
  game_buino_.display.print(player_score_01_);

  game_buino_.display.cursorX = 57;
  game_buino_.display.cursorY = 8;
  game_buino_.display.print(player_score_02_);
}

void DrawGameElements() {
  // Draw players
  game_buino_.display.fillRect(player_01_x_, player_01_y_, kPlayerWidth,
                               kPlayerHeight);
  game_buino_.display.fillRect(player_02_x_, player_02_y_, kPlayerWidth,
                               kPlayerHeight);

  // Draw Ball
  game_buino_.display.fillCircle(ball_x_, ball_y_, kBallSize);

  // Draw middle lines
  for (int i = 0; i < kNumberOfLines; i += 2) {
    game_buino_.display.fillRect(kLineX, i * kLineHeight, kLineWidth,
                                 kLineHeight);
  }

  // Draw borders lines
  game_buino_.display.fillRect(0, 0, LCDWIDTH, kBorderThickness);
  game_buino_.display.fillRect(0, LCDHEIGHT - 1, LCDWIDTH, kBorderThickness);
}

void CheckForExitGame() {
  if (game_buino_.buttons.pressed(BTN_C)) {
    game_buino_.titleScreen(F("Pong Tutorial"));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // update returns true every 50 milisecons, this means we have 20 FPS
  if (game_buino_.update()) {
    ProcesInputFromPlayers();
    MoveBall();
    DrawGameElements();
    PlayersScoring();
    PrintScore();
    CheckForExitGame();
  }
}
