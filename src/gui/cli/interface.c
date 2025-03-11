#include "interface.h"

void terminateGame() {
  endwin();
  exit(0);
}

void render(GameInfo_t info) {
  WINDOW *gameWindow = newwin(FIELD_H + 2, 3 * FIELD_W + 2, 0, 0);
  refresh();
  box(gameWindow, 0, 0);

  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      if (info.field[i][j] == 1)
        mvwprintw(gameWindow, i + 1, 3 * j + 1, "[ ]");
      else
        mvwprintw(gameWindow, i + 1, 3 * j + 1, "   ");
    }
  }

  wrefresh(gameWindow);

  if (info.pause != None) {
    WINDOW *textWindow = newwin(3, 7, 9, 13);
    refresh();
    box(gameWindow, 0, 0);
    if (info.pause == GameStart)
      mvwprintw(textWindow, 1, 1, "START");
    else
      mvwprintw(textWindow, 1, 1, "PAUSE");
    wrefresh(textWindow);
    delwin(textWindow);
  }
  WINDOW *paramsWindow =
      newwin(FIELD_H + 2, 3 * FIELD_W + 2, 0, 3 * FIELD_W + 4);
  refresh();
  box(paramsWindow, 0, 0);

  char score[10];
  sprintf(score, "%d", info.score);
  mvwprintw(paramsWindow, 2, 5, "SCORE: ");
  mvwprintw(paramsWindow, 2, 12, "%s", score);

  char highScore[10];
  sprintf(highScore, "%d", info.highScore);
  mvwprintw(paramsWindow, 4, 5, "MAX SCORE: ");
  mvwprintw(paramsWindow, 4, 16, "%s", highScore);

  char level[10];
  sprintf(level, "%d", info.level);
  mvwprintw(paramsWindow, 6, 5, "LEVEL: ");
  mvwprintw(paramsWindow, 6, 12, "%s", level);

  char speed[10];
  sprintf(speed, "%d", info.speed);
  mvwprintw(paramsWindow, 8, 5, "SPEED: ");
  mvwprintw(paramsWindow, 8, 12, "%s", speed);

  mvwprintw(paramsWindow, 12, 5, "NEXT:");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (info.next[i][j] == 1)
        mvwprintw(paramsWindow, 12 + 4 - i, 5 + 3 * j, "[ ]");
    }
  }
  wrefresh(paramsWindow);
  for (int i = 0; i < FIELD_H; i++) {
    free(info.field[i]);
  }
  free(info.field);

  for (int i = 0; i < 4; i++) {
    free(info.next[i]);
  }
  free(info.next);

  delwin(gameWindow);
  delwin(paramsWindow);
}
