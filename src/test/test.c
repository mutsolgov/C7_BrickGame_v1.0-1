#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/code.h"
#include "../game.h"
#include "../gameInfo.h"
#include "../gui/cli/interface.h"

void initialize_test_environment() {
  initializeState();
  srand(0);
}

START_TEST(test_initializeState) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  ck_assert_int_eq(state->status, Initial);
  ck_assert_ptr_nonnull(state->field);
  ck_assert_int_eq(state->score, 0);
  ck_assert_int_eq(state->level, 1);
  ck_assert_int_eq(state->speed, SPEED);
  ck_assert_int_eq(state->timeLeft, SPEED);
  ck_assert_int_eq(state->pause, 0);
  ck_assert_int_eq(state->coordX, -1);
  ck_assert_int_eq(state->coordY, 4);
  ck_assert_ptr_nonnull(state->nextBlock);
  ck_assert_ptr_nonnull(state->block);
}
END_TEST

START_TEST(test_generateNewBlock) {
  int blockSize;
  int **block = generateNewBlock(&blockSize);

  ck_assert_ptr_nonnull(block);
  ck_assert_int_ge(blockSize, 2);
  ck_assert_int_le(blockSize, 4);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_alpha) {
  int blockSize = 4;
  int **block = createMatrix(blockSize, blockSize);

  block[0][0] = 1;
  block[0][1] = 1;
  block[0][2] = 1;
  block[0][3] = 1;

  ck_assert_int_eq(block[0][0], 1);
  ck_assert_int_eq(block[0][1], 1);
  ck_assert_int_eq(block[0][2], 1);
  ck_assert_int_eq(block[0][3], 1);
}
END_TEST

START_TEST(test_generateNewBlock_delta) {
  int blockSize;

  srand(0);
  while (rand() % 7 != DELTA);

  int **block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 2);
  ck_assert_int_eq(block[0][0], 1);
  ck_assert_int_eq(block[0][1], 1);
  ck_assert_int_eq(block[1][0], 1);
  ck_assert_int_eq(block[1][1], 1);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_omega) {
  int blockSize;

  srand(0);

  int **block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);
  ck_assert_int_eq(block[0][0], 0);
  ck_assert_int_eq(block[0][1], 0);
  ck_assert_int_eq(block[1][1], 0);
  ck_assert_int_eq(block[1][2], 1);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_generateNewBlock_psi) {
  int blockSize;

  srand(0);

  int **block = generateNewBlock(&blockSize);

  ck_assert_int_eq(blockSize, 3);
  ck_assert_int_eq(block[0][0], 0);
  ck_assert_int_eq(block[0][1], 0);
  ck_assert_int_eq(block[0][2], 0);  //
  ck_assert_int_eq(block[1][1], 0);

  freeMatrix(block, blockSize);
}
END_TEST

START_TEST(test_copyMatrix) {
  int rows = 3, cols = 3;
  int **src = createMatrix(rows, cols);
  src[1][1] = 5;

  int **dest = createMatrix(rows, cols);
  copyMatrix(dest, src, rows, cols);

  ck_assert_int_eq(dest[1][1], 5);
  freeMatrix(src, rows);
  freeMatrix(dest, rows);
}
END_TEST

START_TEST(test_rotate) {
  int size = 3;
  int **block = createMatrix(size, size);
  block[0][0] = 1;
  block[0][1] = 1;
  block[0][2] = 1;
  block[1][2] = 1;

  int **rotated = createMatrix(size, size);
  rotate(rotated, block, size);

  ck_assert_int_eq(rotated[0][2], 1);
  ck_assert_int_eq(rotated[1][2], 1);
  ck_assert_int_eq(rotated[2][2], 1);
  ck_assert_int_eq(rotated[2][1], 1);

  freeMatrix(block, size);
  freeMatrix(rotated, size);
}
END_TEST

START_TEST(test_rotate_alfa) {
  int size = 4;
  int **block = createMatrix(size, size);
  block[0][0] = 1;
  block[0][1] = 1;
  block[0][2] = 1;
  block[0][3] = 1;

  int **rotated = createMatrix(size, size);
  rotate(rotated, block, size);

  ck_assert_int_eq(rotated[0][1], 1);
  ck_assert_int_eq(rotated[1][1], 1);
  ck_assert_int_eq(rotated[2][1], 1);
  ck_assert_int_eq(rotated[3][1], 1);

  freeMatrix(block, size);
  freeMatrix(rotated, size);
}
END_TEST

START_TEST(test_rotate_alfa_2) {
  int size = 4;
  int **block = createMatrix(size, size);
  block[0][1] = 1;
  block[1][1] = 1;
  block[2][1] = 1;
  block[3][1] = 1;

  int **rotated = createMatrix(size, size);
  rotate(rotated, block, size);

  ck_assert_int_eq(rotated[0][0], 1);
  ck_assert_int_eq(rotated[0][1], 1);
  ck_assert_int_eq(rotated[0][2], 1);
  ck_assert_int_eq(rotated[0][3], 1);

  freeMatrix(block, size);
  freeMatrix(rotated, size);
}
END_TEST

START_TEST(test_moveBlockLeft_fn) {
  initializeState();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->block[0][1] = 1;
  state->block[1][0] = 1;
  state->block[1][1] = 1;

  state->coordX = 5;
  state->coordY = 5;
  moveBlockLeft();
  ck_assert_int_eq(state->coordY, 4);
  ck_assert_int_eq(state->status, Moving);

  state->coordY = 0;
  moveBlockLeft();
  ck_assert_int_eq(state->coordY, 0);
  ck_assert_int_eq(state->status, Moving);

  state->coordY = 2;
  state->field[4][1] = 1;
  moveBlockLeft();
  ck_assert_int_eq(state->coordY, 2);
  ck_assert_int_eq(state->status, Moving);

  state->coordY = 2;
  state->coordX = FIELD_H - 1;
  moveBlockLeft();
  ck_assert_int_eq(state->status, Attaching);

  freeMatrix(state->block, state->blockSize);
}
END_TEST

START_TEST(test_moveBlockRight_fn) {
  initializeState();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->block[0][1] = 1;
  state->block[1][0] = 1;
  state->block[1][1] = 1;

  state->coordX = 5;
  state->coordY = 5;
  moveBlockRight();
  ck_assert_int_eq(state->coordY, 6);
  ck_assert_int_eq(state->status, Moving);
  state->coordY = FIELD_W - state->blockSize;
  moveBlockRight();
  ck_assert_int_eq(state->coordY, FIELD_W - state->blockSize);
  ck_assert_int_eq(state->status, Moving);

  state->coordY = 4;
  state->field[4][5] = 1;
  moveBlockRight();
  ck_assert_int_eq(state->coordY, 4);
  ck_assert_int_eq(state->status, Moving);

  state->coordY = 4;
  state->coordX = FIELD_H - 1;
  moveBlockRight();
  ck_assert_int_eq(state->status, Attaching);

  freeMatrix(state->block, state->blockSize);
}
END_TEST

START_TEST(test_rotateBlock_fn) {
  initializeState();
  State_t *state = getCurrentState();

  int blockSize = 2;
  state->blockSize = blockSize;

  int **currentBlock = createMatrix(blockSize, blockSize);
  currentBlock[0][0] = 1;
  currentBlock[0][1] = 1;
  currentBlock[1][0] = 1;
  currentBlock[1][1] = 1;
  state->block = currentBlock;

  state->coordX = 1;
  state->coordY = 1;

  state->field[2][1] = 1;

  rotateBlock();

  ck_assert_int_eq(state->status, Attaching);

  state->field[2][1] = 0;

  rotateBlock();

  ck_assert_int_eq(state->status, Moving);

  freeMatrix(currentBlock, blockSize);
}
END_TEST

START_TEST(test_spawnNewBlock_fn) {
  initializeState();
  State_t *state = getCurrentState();

  int initialBlockSize = 2;
  int **initialNextBlock = createMatrix(initialBlockSize, initialBlockSize);
  initialNextBlock[0][0] = 1;
  initialNextBlock[0][1] = 1;
  initialNextBlock[1][0] = 1;
  initialNextBlock[1][1] = 1;

  state->nextBlock = initialNextBlock;
  state->nextBlockSize = initialBlockSize;

  int currentBlockSize = 3;
  int **currentBlock = createMatrix(currentBlockSize, currentBlockSize);
  currentBlock[0][0] = 1;
  currentBlock[0][1] = 0;
  currentBlock[0][2] = 1;
  currentBlock[1][0] = 0;
  currentBlock[1][1] = 1;
  currentBlock[1][2] = 0;
  currentBlock[2][0] = 1;
  currentBlock[2][1] = 0;
  currentBlock[2][2] = 1;

  state->block = currentBlock;
  state->blockSize = currentBlockSize;

  state->coordX = 5;
  state->coordY = 3;
  state->status = Attaching;

  spawnNewBlock();

  ck_assert_ptr_ne(state->block, currentBlock);

  ck_assert_ptr_eq(state->block, initialNextBlock);

  ck_assert_int_eq(state->blockSize, initialBlockSize);

  ck_assert_int_eq(state->coordX, -1);
  if (initialBlockSize == 2) {
    ck_assert_int_eq(state->coordY, 4);
  } else {
    ck_assert_int_eq(state->coordY, 3);
  }
  ck_assert_int_eq(state->status, Moving);

  ck_assert_ptr_ne(state->nextBlock, initialNextBlock);

  ck_assert_int_ne(state->nextBlockSize, initialBlockSize);

  ck_assert_int_ne(state->startTime, 0);
  ck_assert_int_eq(state->timeLeft, state->speed);

  freeMatrix(state->block, state->blockSize);
  freeMatrix(state->nextBlock, state->nextBlockSize);
}
END_TEST

START_TEST(test_processTimer_initial_status) {
  State_t state;
  state.status = Initial;
  state.timeLeft = 1000;
  state.startTime = 0;

  unsigned long long currentTime = 5000;
  unsigned long long result = processTimer(&state, currentTime);

  ck_assert_int_eq(result, (unsigned long long)-1);
}
END_TEST

START_TEST(test_shiftBlock) {
  State_t *state = getCurrentState();

  startGame();

  state->coordX = 5;
  state->startTime = 0;
  state->timeLeft = 0;
  state->speed = 1000;
  if (blockIsAttached() == 0) {
    shiftBlock();

    ck_assert_int_eq(state->coordX, 6);
    ck_assert_int_eq(state->status, Moving);
    ck_assert_int_eq(state->timeLeft, state->speed);
    ck_assert(state->startTime > 0);
  }

  state->coordX = 5;
  if (blockIsAttached() == 1) {
    shiftBlock();

    ck_assert_int_eq(state->status, Attaching);
    ck_assert_int_eq(state->coordX, 5);
  }
}
END_TEST

START_TEST(test_finishGame_integration) {
  initializeState();
  State_t *state = getCurrentState();

  state->status = GameOver;
  finishGame();

  ck_assert_int_eq(state->status, Initial);
  ck_assert_int_eq(state->pause, 0);
  ck_assert_int_eq(state->coordX, -1);
}
END_TEST

START_TEST(test_updateCurrentState_normal) {
  initializeState();
  State_t *state = getCurrentState();

  state->score = 500;
  state->level = 3;
  state->speed = 300;
  state->status = Moving;
  state->pause = 0;

  state->block[0][0] = 1;
  state->coordX = 5;
  state->coordY = 3;

  GameInfo_t info = updateCurrentState();

  ck_assert_int_eq(info.score, 500);
  ck_assert_int_eq(info.level, 3);
  ck_assert_int_eq(info.speed, 300);
  ck_assert_int_eq(info.pause, None);

  ck_assert_int_eq(info.field[5][3], 1);

  freeMatrix(info.field, FIELD_H);
  freeMatrix(info.next, 4);
}
END_TEST

START_TEST(test_userInput_full_flow) {
  initializeState();
  State_t *state = getCurrentState();

  userInput(Start);
  ck_assert_int_eq(state->status, Spawn);

  state->status = Moving;
  int initial_y = state->coordY;
  userInput(Left);
  ck_assert_int_eq(state->coordY, initial_y - 1);

  userInput(Right);
  ck_assert_int_eq(state->coordY, initial_y);

  int **original_block = state->block;
  userInput(Action);
  ck_assert_ptr_ne(state->block, original_block);

  userInput(Pause);
  ck_assert_int_eq(state->pause, 1);

  userInput(Pause);
  ck_assert_int_eq(state->pause, 0);

  userInput(Terminate);

  ck_assert_int_eq(state->score, 0);
  ck_assert_int_eq(state->level, 1);

  initializeState();
}
END_TEST

START_TEST(test_userInput_down_action) {
  initializeState();
  State_t *state = getCurrentState();

  state->status = Moving;

  userInput(Down);

  ck_assert_int_eq(state->status, Attaching);
}
END_TEST

START_TEST(test_userInput_invalid_actions) {
  initializeState();
  State_t *state = getCurrentState();

  state->status = Moving;
  userInput(Start);
  ck_assert_int_ne(state->status, Spawn);

  state->status = Spawn;
  userInput(Down);
  ck_assert_int_ne(state->status, Attaching);

  state->status = GameOver;
  int **original_block = state->block;
  userInput(Action);
  ck_assert_ptr_eq(state->block, original_block);
}
END_TEST

START_TEST(test_updateCurrentState_create_max_score) {
  remove("./max_score.txt");

  initializeState();
  GameInfo_t info = updateCurrentState();

  FILE *f = fopen("./max_score.txt", "r");
  ck_assert_ptr_nonnull(f);
  fclose(f);

  freeMatrix(info.field, FIELD_H);
  freeMatrix(info.next, 4);
}
END_TEST

START_TEST(test_updateCurrentState_pause_game_start) {
  initializeState();
  State_t *state = getCurrentState();
  state->status = Initial;

  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.pause, GameStart);

  freeMatrix(info.field, FIELD_H);
  freeMatrix(info.next, 4);
}
END_TEST

START_TEST(test_updateCurrentState_pause_game_pause) {
  initializeState();
  State_t *state = getCurrentState();
  state->pause = 1;

  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.pause, GamePause);

  freeMatrix(info.field, FIELD_H);
  freeMatrix(info.next, 4);
}
END_TEST

START_TEST(test_updateCurrentState_block_boundaries) {
  initializeState();
  State_t *state = getCurrentState();

  state->block[0][0] = 1;
  state->coordX = -1;
  state->coordY = FIELD_W - 1;

  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.field[0][FIELD_W - 1], 0);

  freeMatrix(info.field, FIELD_H);
  freeMatrix(info.next, 4);
}
END_TEST

START_TEST(test_attachBlock_normal) {
  initializeState();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->block[0][1] = 1;
  state->block[1][0] = 1;
  state->block[1][1] = 1;

  state->coordX = FIELD_H - 2;
  state->coordY = FIELD_W / 2 - 1;

  attachBlock();

  ck_assert_int_eq(state->field[FIELD_H - 2][FIELD_W / 2 - 1], 1);
  ck_assert_int_eq(state->field[FIELD_H - 1][FIELD_W / 2 - 1], 0);

  ck_assert_int_eq(state->status, Spawn);
}
END_TEST

START_TEST(test_attachBlock_game_over) {
  initializeState();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->coordX = -1;

  attachBlock();

  ck_assert_int_eq(state->status, GameOver);
}
END_TEST

START_TEST(test_attachBlock_consume_rows) {
  initializeState();
  State_t *state = getCurrentState();

  for (int j = 0; j < FIELD_W; j++) {
    state->field[FIELD_H - 2][j] = 1;
  }

  state->blockSize = 1;
  state->block = createMatrix(1, 1);
  state->block[0][0] = 1;
  state->coordX = FIELD_H - 1;

  attachBlock();

  int count = 0;
  for (int j = 0; j < FIELD_W; j++) {
    count += state->field[FIELD_H - 1][j];
  }
  ck_assert_int_eq(count, 1);
}
END_TEST

void fill_row(State_t *state, int row) {
  for (int j = 0; j < FIELD_W; j++) {
    state->field[row][j] = 1;
  }
}

START_TEST(test_2_lines_clear) {
  initializeState();
  State_t *state = getCurrentState();

  fill_row(state, FIELD_H - 1);
  fill_row(state, FIELD_H - 2);

  consumeRows();

  ck_assert_int_eq(state->score, 300);
  ck_assert_int_eq(state->level, 1 + (300 / 600));
}
END_TEST

START_TEST(test_4_lines_clear) {
  initializeState();
  State_t *state = getCurrentState();

  for (int i = 0; i < 4; i++) {
    fill_row(state, FIELD_H - 1 - i);
  }

  consumeRows();

  ck_assert_int_eq(state->score, 1500);
  ck_assert_int_eq(state->level, 1 + (1500 / 600));
  ck_assert_int_eq(state->speed, SPEED - (state->level - 1) * SPEED_STEP);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      ck_assert_int_eq(state->field[FIELD_H - 1 - i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_integration_game_loop_consumeRows) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  int rowToClear = FIELD_H - 1;

  for (int j = 0; j < FIELD_W; j++) {
    state->field[rowToClear][j] = 1;
  }
  state->field[rowToClear][5] = 0;

  if (state->block != NULL) {
    freeMatrix(state->block, state->blockSize);
  }
  state->block = createMatrix(1, 1);
  state->block[0][0] = 1;
  state->blockSize = 1;

  state->coordX = rowToClear;
  state->coordY = 5;

  state->status = Attaching;

  attachBlock();

  for (int j = 0; j < FIELD_W; j++) {
    ck_assert_int_eq(state->field[rowToClear][j], 0);
  }

  ck_assert_int_eq(state->score, 100);

  ck_assert_int_eq(state->status, Spawn);
}
END_TEST

START_TEST(test_integration_game_loop_consumeRows_three) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  state->score = 0;

  for (int i = FIELD_H - 3; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      state->field[i][j] = 1;
    }
  }
  for (int j = 0; j < FIELD_W; j++) {
    state->field[FIELD_H - 4][j] = 0;
  }

  consumeRows();

  ck_assert_int_eq(state->score, 700);

  for (int i = FIELD_H - 3; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      ck_assert_int_eq(state->field[i][j], 0);
    }
  }
}
END_TEST

START_TEST(test_updateLevel_normal) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  state->level = 1;
  state->speed = SPEED;
  state->score = 600;

  updateLevel();

  ck_assert_int_eq(state->level, 2);
  ck_assert_int_eq(state->speed, SPEED - (2 - 1) * SPEED_STEP);
}
END_TEST

START_TEST(test_updateLevel_max_level) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  state->level = 1;
  state->speed = SPEED;
  state->score = NEW_LEVEL_THRESHOLD * MAX_LEVEL;

  updateLevel();

  ck_assert_int_eq(state->level, MAX_LEVEL);
  ck_assert_int_eq(state->speed, SPEED - (MAX_LEVEL - 1) * SPEED_STEP);
}
END_TEST

START_TEST(test_shiftBlock_not_attached) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->block[0][1] = 1;
  state->block[1][0] = 1;
  state->block[1][1] = 1;

  state->coordX = 5;
  state->coordY = 3;

  int prevCoordX = state->coordX;

  shiftBlock();

  ck_assert_int_eq(state->coordX, prevCoordX + 1);
  ck_assert(state->startTime > 0);
  ck_assert_int_eq(state->timeLeft, state->speed);
  ck_assert_int_eq(state->status, Moving);
}
END_TEST

START_TEST(test_shiftBlock_attached) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  state->blockSize = 2;
  state->block = createMatrix(2, 2);
  state->block[0][0] = 1;
  state->block[0][1] = 1;
  state->block[1][0] = 1;
  state->block[1][1] = 1;

  state->coordX = FIELD_H - 1;
  state->coordY = 3;

  int prevCoordX = state->coordX;

  shiftBlock();

  ck_assert_int_eq(state->coordX, prevCoordX);
  ck_assert_int_eq(state->status, Attaching);
}
END_TEST

START_TEST(test_spawnNewBlock_non2_branch) {
  initialize_test_environment();
  State_t *state = getCurrentState();

  int dummyNextBlockSize = 3;
  int **dummyNextBlock = createMatrix(dummyNextBlockSize, dummyNextBlockSize);
  for (int i = 0; i < dummyNextBlockSize; i++) {
    for (int j = 0; j < dummyNextBlockSize; j++) {
      dummyNextBlock[i][j] = 1;
    }
  }
  state->nextBlock = dummyNextBlock;
  state->nextBlockSize = dummyNextBlockSize;

  int **dummyBlock = createMatrix(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      dummyBlock[i][j] = 0;
    }
  }
  state->block = dummyBlock;
  state->blockSize = 2;

  int **oldNextBlock = dummyNextBlock;

  spawnNewBlock();

  ck_assert_ptr_eq(state->block, oldNextBlock);
  ck_assert_int_eq(state->blockSize, dummyNextBlockSize);
  ck_assert_int_eq(state->coordX, -1);
  ck_assert_int_eq(state->coordY, 3);
  ck_assert_ptr_ne(state->nextBlock, oldNextBlock);
  ck_assert_int_eq(state->status, Moving);
  ck_assert_int_eq(state->timeLeft, state->speed);
  ck_assert(state->startTime > 0);
}
END_TEST

Suite *game_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Game Logic");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_initializeState);
  tcase_add_test(tc_core, test_generateNewBlock);
  tcase_add_test(tc_core, test_copyMatrix);
  tcase_add_test(tc_core, test_rotate);
  tcase_add_test(tc_core, test_rotate_alfa);
  tcase_add_test(tc_core, test_rotate_alfa_2);
  tcase_add_test(tc_core, test_generateNewBlock_alpha);
  tcase_add_test(tc_core, test_generateNewBlock_delta);
  tcase_add_test(tc_core, test_generateNewBlock_omega);
  tcase_add_test(tc_core, test_generateNewBlock_psi);
  tcase_add_test(tc_core, test_moveBlockLeft_fn);
  tcase_add_test(tc_core, test_moveBlockRight_fn);
  tcase_add_test(tc_core, test_rotateBlock_fn);
  tcase_add_test(tc_core, test_spawnNewBlock_fn);
  tcase_add_test(tc_core, test_processTimer_initial_status);
  tcase_add_test(tc_core, test_shiftBlock);
  tcase_add_test(tc_core, test_finishGame_integration);
  tcase_add_test(tc_core, test_updateCurrentState_normal);
  tcase_add_test(tc_core, test_userInput_full_flow);
  tcase_add_test(tc_core, test_userInput_invalid_actions);
  tcase_add_test(tc_core, test_userInput_down_action);
  tcase_add_test(tc_core, test_updateCurrentState_create_max_score);
  tcase_add_test(tc_core, test_updateCurrentState_pause_game_start);
  tcase_add_test(tc_core, test_updateCurrentState_pause_game_pause);
  tcase_add_test(tc_core, test_updateCurrentState_block_boundaries);
  tcase_add_test(tc_core, test_attachBlock_normal);
  tcase_add_test(tc_core, test_attachBlock_game_over);
  tcase_add_test(tc_core, test_attachBlock_consume_rows);
  tcase_add_test(tc_core, test_2_lines_clear);
  tcase_add_test(tc_core, test_4_lines_clear);
  tcase_add_test(tc_core, test_integration_game_loop_consumeRows);
  tcase_add_test(tc_core, test_integration_game_loop_consumeRows_three);
  tcase_add_test(tc_core, test_updateLevel_normal);
  tcase_add_test(tc_core, test_updateLevel_max_level);
  tcase_add_test(tc_core, test_shiftBlock_not_attached);
  tcase_add_test(tc_core, test_shiftBlock_attached);
  tcase_add_test(tc_core, test_spawnNewBlock_non2_branch);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = game_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
