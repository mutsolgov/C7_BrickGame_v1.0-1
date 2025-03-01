#ifndef GAME_INFO_H
#define GAME_INFO_H

#define FIELD_H 20
#define FIELD_W 10

typedef enum { None, GameStart, GamePause } Banner;

typedef struct {
  int **field;
  int **next;
  int score;
  int highScore;
  int level;
  int speed;
  Banner pause;
} GameInfo_t;

#endif