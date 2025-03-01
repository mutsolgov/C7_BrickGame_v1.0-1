CFLAGS = -Wall -Wextra -Werror -std=c11
INSTALL_FILES = brick_game/tetris/code.c gui/cli/interface.c game.c
TEST_FILES = test/test.c brick_game/tetris/code.c gui/cli/interface.c
GCOV_FILES = test/test.c brick_game/tetris/code.c gui/cli/interface.c
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage
LDFLAGS = -lcheck -lsubunit -lrt -lpthread -lm -lncurses
DIST_DIR = s21_Tetris

.PHONY: test dvi

UNAME_S = $(shell uname)

ifeq ($(UNAME_S), Darwin)
OPEN_CMD = open
endif

ifeq ($(UNAME_S),Linux)
OPEN_CMD = xdg-open
ADD_LDFLAGS = -lm -lsubunit
endif

all: install

install:
	mkdir -p build
	gcc $(CFLAGS) $(INSTALL_FILES) $(LDFLAGS) $(ADD_LDFLAGS) -o build/Tetris

uninstall:
	rm -rf build

test:
	gcc $(CFLAGS) $(TEST_FILES) $(LDFLAGS) $(ADD_LDFLAGS) -o test/test
	cd test && ./test


gcov_report: clean
	mkdir -p gcov
	gcc $(CFLAGS) $(GCOV_FLAGS) $(GCOV_FILES) -o gcov/gcov_test $(LDFLAGS)
	./gcov/gcov_test
	lcov -t "s21_tetris" -o gcov/s21_test.info -c -d . --exclude *gui/* 
	genhtml -o gcov/report gcov/s21_test.info
	$(OPEN_CMD) gcov/report/index.html

dvi:
	cd dvi && latex doc.tex
	cd dvi && xdvi doc.dvi

dist:
	mkdir -p $(DIST_DIR)
	cp -a brick_game $(DIST_DIR)
	cp -a gui $(DIST_DIR)
	cp -a test $(DIST_DIR)
	cp -a *.c $(DIST_DIR)
	cp -a *.h $(DIST_DIR)
	tar -czf s21_Tetris.tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)

clang_format:
	# cp ../../../materials/linters/.clang-format 
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.[c,h] */*.[c,h] */*/*.[c,h]
	clang-format -i *.[c,h] */*.[c,h] */*/*.[c,h]
	rm -rf .clang-format

clean:
	rm -rf gcov
	rm -rf Tetris
	rm -rf *.txt
	rm -rf *.gz
	cd test && rm -rf *.txt test
	cd build && rm -rf max_score.txt Tetris
	cd dvi && rm -rf *.aux *.dvi *.log