# 🎮 S21 Tetris  

S21 Tetris — это консольная игра, реализованная на языке C с использованием библиотеки ncurses.  

## 🚀 Установка и запуск  

### 🔧 Установка зависимостей  

Перед запуском убедитесь, что у вас установлены необходимые библиотеки:  
```sh
sudo apt update
sudo apt install libncurses-dev check libsubunit-dev lcov
```
### 🔨 Сборка и запуск
```sh
cd src && make  
cd ./build && ./Tetris  
```

## 📝 Описание игры
Игрок управляет падающими блоками, которые можно перемещать и поворачивать, заполняя горизонтальные линии. Заполненные линии исчезают, увеличивая счёт.


## 📌 Реализованные механики
✅ Вращение фигур <br> 
✅ Перемещение фигуры по горизонтали <br> 
✅ Ускоренное падение фигуры <br> 
✅ Показ следующей фигуры <br> 
✅ Уничтожение заполненных линий <br> 
✅ Завершение игры при достижении верхней границы <br> 
✅ Подсчёт очков и сохранение рекорда <br> 
✅ Механика уровней (до 10 уровней, увеличение скорости) <br>


## 📌 Управление <br>
- ⬅ / ➡ — перемещение блока <br>
- ⬇ — ускорение падения <br>
- Пробел — поворот блока <br>
- P — пауза <br>
- Q — выход <br>


## 📈 Подсчёт очков
Очки начисляются в зависимости от количества уничтоженных линий:

- 1 линия — 100 очков
- 2 линии — 300 очков
- 3 линии — 700 очков
- 4 линии — 1500 очков

Каждые 600 очков повышают уровень, увеличивая скорость игры. Максимальный уровень — 10.


## 💾 Сохранение рекордов
Максимальный счёт сохраняется между запусками в файле max_score.txt. Если игрок побил рекорд, он автоматически обновляется.

## 📁 Структура проекта
```bash
src/  
 ├── brick_game/tetris/   # Логика тетриса  
 ├── gui/cli/             # Графический интерфейс (ncurses)  
 ├── test/                # Unit-тесты  
 ├── dvi/doc.tex          # Документация (LaTeX)  
 ├── Makefile             # Сборка проекта  
 ├── game.c               # Основной файл игры  
 ├── game.h               # Заголовочный файл  
```


## 🛠 Команды Makefile
Команда	| Описание
------------ | -------------
make | Сборка проекта
make install | Установка игры
make test |	Запуск тестов
make gcov_report | Генерация отчёта покрытия кода
make dvi | Компиляция документации (LaTeX)
make dist | Архивация проекта
make clean | Очистка временных файлов


## 🖥 Пример игрового поля
``` sh
+----------------------+  +-------------------+
|                      |  |                   |
|     [ ][ ][ ]        |  |  Score: 100       |
|        [ ]           |  |                   |
|                      |  |  Max score: 1000  |
|                      |  |                   |
|                      |  |  Level: 1         | 
|                      |  |                   |
|[ ][ ]     [ ]        |  |                   |
|[ ][ ]  [ ][ ][ ]     |  |                   |
+----------------------+  +-------------------+ 
```

## 📜 Лицензия
Проект разработан в рамках учебного процесса в Школе 21.

