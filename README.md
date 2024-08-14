
# Рекомендации по монтажу
1. Не удлиннять линию связи с матрицей
2. Добавить радиатор на заднюю стенку матрицы
3. Установить перед матрицей рассеиватель - так будет четче видно символы
4. На выходе на электромагнит уже установлен шунтирующий диод
5. Провода подключения матрицы подходят в левый верхний угол сверху (ориентация матрицы)
   https://github.com/glarionenko/doorQuest/blob/main/matrixTOP.jpg

# Таблица A
|   Pin | Description                                                                  |
|------:|:-----------------------------------------------------------------------------|
|     1 | 12v вход плюс питания загадки                                                |
|     2 | Земля вход питания загадки                                                   |
|     3 | 12v вход плюс питания для замка (можно объединить с плюсом питанием загадки) |
|     4 | Земля вход питания загадки (можно объединить с землей питания загадки)       |
|     5 | ничего                                                                       |
|     6 | ничего                                                                       |
|     7 | ничего                                                                       |
|     8 | 12v выход на плюс питания замка                                              |
|     9 | Земля выход на землю питания замка                                           |

# Таблица B
|   Pin | Description                                         |
|------:|:----------------------------------------------------|
|     1 | ничего                                              |
|     2 | ничего                                              |
|     3 | ничего                                              |
|     4 | Белый провод кнопки 'C'                             |
|     5 | Зеленый провод кнопки 'NO' (замыкается при нажатии) |
|     6 | ничего                                              |
|     7 | Плюс питания матрицы 5v - розовый провод            |
|     8 | земля питания матрицы - белый провод                |
|     9 | Выход данных на матрицу - желтый провод             |

Время открытия замка меняется здесь https://github.com/glarionenko/doorQuest/blob/24890ec36bf7b7172c775d007a364ccfb9897975/doorQuestGood2lockOnZero/doorQuestGood2lockOnZero.ino#L199

Цвета текста и фона можно менять тут и в следующих строках https://github.com/glarionenko/doorQuest/blob/ed126eb9c38f0dd78611e38a95c68bdcb17962ed/doorQuestGood2lockOnZero/doorQuestGood2lockOnZero.ino#L154
