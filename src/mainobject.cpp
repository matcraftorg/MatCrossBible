/***************************************************************************
 *   MatCrossBible  (old name: CrossBgBible)                               *
 *   Copyright (C) 2007-2020 by MatCraft, Bulgaria                         *
 *   matcraft.org@gmail.com                                                *
 *   https://www.matcraft.org/  (old site: https://www.crossbgbible.com/)  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainobject.h"

#define BUF_LEN 16384

// Този клас се явява просто допълнение на MainWindow и съдържа преди всичко начални инициализации и методи за достъп до файловете.

QStringList MainObject::getChapStructure(bool extStruct)
{
  QStringList sList;

  // Старият Завет
  sList << "1   31 25 24 26 32 22 24 22 29 32 32 20 18 24 21 16 27 33 38 18 34 24 20 67 34 35 46 22 35 43 55 32 20 31 29 43 36 30 23 23 57 38 34 34 28 34 31 22 33 26";
  sList << "2   22 25 22 31 23 30 25 32 35 29 10 51 22 31 27 36 16 27 25 26 36 31 33 18 40 37 21 43 46 38 18 35 23 35 35 38 29 31 43 38";
  sList << "3   17 16 17 35 19 30 38 36 24 20 47 8 59 57 33 34 16 30 37 27 24 33 44 23 55 46 34";
  sList << "4   54 34 51 49 31 27 89 26 23 36 35 16 34 45 41 50 13 32 22 29 35 41 30 25 18 65 23 31 40 17 54 42 56 29 34 13"; // <-----------------
  sList << "5   46 37 29 49 33 25 26 20 29 22 32 32 18 29 23 22 20 22 21 20 23 30 25 22 19 19 26 68 29 20 30 52 29 12";
  sList << "6   18 24 17 24 16 27 26 35 27 43 23 24 33 15 63 10 18 28 51 9 45 34 16 36"; // <-----------------
  sList << "7   36 23 31 24 31 40 25 35 57 18 40 15 25 20 20 31 13 31 30 48 25";
  sList << "8   22 23 18 22";
  sList << "9   28 36 21 22 12 21 17 22 27 27 15 25 23 52 35 23 58 30 24 43 15 23 29 23 44 25 12 25 11 31 13"; // <-----------------
  sList << "10   27 32 39 12 25 23 29 18 13 19 27 31 39 33 37 23 29 33 43 26 22 51 39 25";
  sList << "11   53 46 28 34 18 38 51 66 28 29 43 33 34 31 34 34 24 46 21 43 29 53";
  sList << "12   18 25 27 44 27 33 20 29 37 36 21 21 25 29 38 20 41 37 37 21 26 20 37 20 30";
  sList << "13   54 55 24 43 26 81 40 40 44 14 47 40 14 17 29 43 27 17 19 8 30 19 32 31 31 32 34 21 30";
  sList << "14   17 18 17 22 14 42 22 18 31 19 23 16 22 15 19 14 19 34 11 37 20 12 21 27 28 23 9 27 36 27 21 33 25 33 27 38"; // (Молитвата на Манасия)
  sList << "15   11 70 13 24 17 22 28 36 15 44";
  sList << "16   11 20 32 23 19 19 73 18 38 39 36 47 31";
  sList << "17   39 23 22 66 14 14 10 41 32 14"; // (Допълнение на Естир) <-----------------
  sList << "18   22 13 26 21 27 30 21 22 35 22 20 25 28 22 35 22 16 21 29 29 34 30 17 25 6 14 23 28 25 31 40 22 33 37 16 33 24 41 35 32 34 17"; // <-----------------
  if (extStruct) // За православните текстове
    sList << "19   6 12 8 8 12 10 17 9 38 7 8 6 7 5 11 15 50 14 9 13 31 6 10 22 12 14 9 11 12 24 11 22 22 28 12 40 22 13 17 13 11 5 26 17 11 9 14 20 23 19 9 6 7 23 13 11 11 17 12 8 12 11 10 13 20 7 35 36 5 24 20 28 23 10 12 20 72 13 19 16 8 18 12 13 17 7 18 52 17 16 15 5 23 11 13 12 9 9 5 8 28 22 35 45 48 43 13 31 7 10 10 9 26 9 10 2 29 176 7 8 9 4 8 5 6 5 6 8 8 3 18 3 3 21 26 9 8 24 13 10 7 12 15 21 10 11 9 14 9 6 16"; // (Additions to Psalms) <-----------------
  else // За протестантските текстове
    sList << "19   6 12 8 8 12 10 17 9 20 18 7 8 6 7 5 11 15 50 14 9 13 31 6 10 22 12 14 9 11 12 24 11 22 22 28 12 40 22 13 17 13 11 5 26 17 11 9 14 20 23 19 9 6 7 23 13 11 11 17 12 8 12 11 10 13 20 7 35 36 5 24 20 28 23 10 12 20 72 13 19 16 8 18 12 13 17 7 18 52 17 16 15 5 23 11 13 12 9 9 5 8 28 22 35 45 48 43 13 31 7 10 10 9 8 18 19 2 29 176 7 8 9 4 8 5 6 5 6 8 8 3 18 3 3 21 26 9 8 24 13 10 7 12 15 21 10 20 14 9 6 16"; // (Additions to Psalms) <-----------------
  sList << "20   33 22 35 29 23 35 27 36 18 32 31 28 26 35 33 33 28 25 29 30 31 29 35 34 28 28 27 28 27 33 31"; // <-----------------
  sList << "21   18 26 22 17 20 12 29 17 18 20 10 14"; // <-----------------
  sList << "22   17 17 11 16 16 13 14 14"; // <-----------------
  sList << "23   31 22 26 6 30 13 25 22 21 34 16 6 22 32 9 14 14 7 25 6 17 25 18 23 12 21 13 29 24 33 9 20 24 17 10 22 38 22 8 31 29 25 28 28 25 13 15 22 26 11 23 15 12 17 13 12 21 14 21 22 11 12 19 12 25 24";
  sList << "24   19 37 25 31 31 30 34 22 26 25 23 17 27 22 21 21 27 23 15 18 14 30 40 10 38 24 22 17 32 24 40 44 26 22 19 32 21 28 18 16 18 22 13 30 5 28 7 47 39 46 64 34";
  sList << "25   22 22 66 22 22";
  sList << "26   28 10 27 17 17 14 27 18 11 22 25 28 23 23 8 63 24 32 14 49 32 31 49 27 17 21 36 26 21 26 18 32 33 31 15 38 28 23 29 49 26 20 27 31 25 24 23 35";
  sList << "27   21 49 101 37 31 28 28 27 27 21 45 13 64 43"; // (Даниил 3, 13, 14) <-----------------
  sList << "28   11 23 5 19 15 11 16 14 17 15 12 14 16 10"; // <-----------------
  sList << "29   20 32 21";
  sList << "30   15 16 15 13 27 14 17 14 15";
  sList << "31   21";
  sList << "32   17 11 10 11"; // <-----------------
  sList << "33   16 13 12 13 15 16 20";
  sList << "34   15 13 19";
  sList << "35   17 20 19";
  sList << "36   18 15 20";
  sList << "37   15 23";
  sList << "38   21 13 10 14 11 15 14 23 17 12 17 14 9 21";
  sList << "39   14 17 18 6";

  // Второканонични книги:
  sList << "40   58 31 24 63 73 34 15 97 56"; // (2 Ездра)
  sList << "41   25 23 25 23 28 22 20 24 12 13 21 22 23 17"; // (Товита)
  sList << "42   16 28 15 17 29 21 32 36 19 23 23 20 31 19 15 31"; // (Иудит)
  sList << "43   16 25 19 20 24 27 30 21 19 21 27 28 19 31 19 29 21 25 22"; // (Премъдрост Соломонова)
  sList << "44   44 23 34 36 18 37 40 22 25 34 36 19 32 27 22 31 32 33 30 33 31 33 38 47 36 29 33 30 35 27 42 28 33 31 26 31 34 39 42 32 29 26 37 27 31 23 31 28 19 31 38 13"; // (Премъдрост на Исус, син Сирахов)
  sList << "45   73"; // (Послание на Еремия)
  sList << "46   22 35 38 37 9"; // (Варуха)
  sList << "47   67 70 60 61 68 63 50 32 73 89 74 54 54 49 41 24"; // (1 Макавей)
  sList << "48   36 33 40 50 27 31 42 36 29 38 38 46 26 46 40"; // (2 Макавей)
  sList << "49   29 33 30 21 51 41 23    35 24 21 26 38 35 23 29 32 21 27 19 27 20 32 25 24 24"; // (3,4 Макавей)
  sList << "50   40 48 36 52 56 59 140 63 47 60 46 51 58 48 63 78"; // (3 Ездра)

  // Новият Завет
  sList << "51   25 23 17 25 48 34 29 34 38 42 30 50 58 36 39 28 27 35 30 34 46 46 39 51 46 75 66 20";
  sList << "52   45 28 35 41 43 56 37 38 50 52 33 44 37 72 47 20";
  sList << "53   80 52 38 44 39 49 50 56 62 42 54 59 35 35 32 31 37 43 48 47 38 71 56 53";
  sList << "54   51 25 36 54 47 71 53 59 41 42 57 50 38 31 27 33 26 40 42 31 25";
  sList << "55   26 47 26 37 42 15 60 40 43 48 30 25 52 28 41 40 34 28 41 38 40 30 35 27 27 32 44 31";

  sList << "56   32 29 31 25 21 23 25 39 33 21 36 21 14 26 33 27"; // <-----------------
  sList << "57   31 16 23 21 13 20 40 13 27 33 34 31 13 40 58 24";
  sList << "58   24 17 18 18 21 18 16 24 15 18 33 21 14";
  sList << "59   24 21 29 31 26 18";
  sList << "60   23 22 21 32 33 24";
  sList << "61   30 30 21 23";
  sList << "62   29 23 25 18";
  sList << "63   10 20 13 18 28";
  sList << "64   12 17 18";
  sList << "65   20 15 16 16 25 21";
  sList << "66   18 26 17 22";
  sList << "67   16 15 15";
  sList << "68   25";
  sList << "69   14 18 19 16 14 20 28 13 28 39 40 29 25";

  sList << "70   27 26 18 17 20";
  sList << "71   25 25 22 19 14";
  sList << "72   21 22 18";
  sList << "73   10 29 24 21 21";
  sList << "74   13";
  sList << "75   15"; // <-----------------
  sList << "76   25";

  sList << "77   20 29 22 11 14 17 17 13 21 11 19 17 18 20 8 21 18 24 21 15 27 21";
  return sList;
}

void MainObject::setBibStructure()
{
  chaptersCountArr[0]  = 50;
  chaptersCountArr[1]  = 40;
  chaptersCountArr[2]  = 27;
  chaptersCountArr[3]  = 36;  
  chaptersCountArr[4]  = 34;
  chaptersCountArr[5]  = 24;
  chaptersCountArr[6]  = 21;
  chaptersCountArr[7]  = 4;   
  chaptersCountArr[8]  = 31;
  chaptersCountArr[9]  = 24;
  chaptersCountArr[10] = 22;
  chaptersCountArr[11] = 25;  
  chaptersCountArr[12] = 29;
  chaptersCountArr[13] = 36;
  chaptersCountArr[14] = 10;
  chaptersCountArr[15] = 13;  
  chaptersCountArr[16] = 10;  
  chaptersCountArr[17] = 42;
  chaptersCountArr[18] = 151;
  chaptersCountArr[19] = 31;
  chaptersCountArr[20] = 12;  
  chaptersCountArr[21] = 8;
  chaptersCountArr[22] = 66;  
  chaptersCountArr[23] = 52;
  chaptersCountArr[24] = 5;
  chaptersCountArr[25] = 48;
  chaptersCountArr[26] = 14;
  chaptersCountArr[27] = 14;
  chaptersCountArr[28] = 3;   
  chaptersCountArr[29] = 9;
  chaptersCountArr[30] = 1;
  chaptersCountArr[31] = 4;
  chaptersCountArr[32] = 7;   
  chaptersCountArr[33] = 3;
  chaptersCountArr[34] = 3;
  chaptersCountArr[35] = 3;
  chaptersCountArr[36] = 2;   
  chaptersCountArr[37] = 14;
  chaptersCountArr[38] = 4;

  chaptersCountArr[39] = 9;  // (2 Ездра)
  chaptersCountArr[40] = 14; // (Товита)
  chaptersCountArr[41] = 16; // (Иудит)
  chaptersCountArr[42] = 19; // (Премъдрост Соломонова)
  chaptersCountArr[43] = 52; // (Премъдрост на Исус, син Сирахов)
  chaptersCountArr[44] = 1;  // (Послание на Еремия)
  chaptersCountArr[45] = 5;  // (Варуха)
  chaptersCountArr[46] = 16; // (1 Макавей)
  chaptersCountArr[47] = 15; // (2 Макавей)
  chaptersCountArr[48] = 25; // (3,4 Макавей)
  chaptersCountArr[49] = 16; // (3 Ездра)

  chaptersCountArr[50] = 28; // Матей
  chaptersCountArr[51] = 16;
  chaptersCountArr[52] = 24;
  chaptersCountArr[53] = 21;
  chaptersCountArr[54] = 28; // ДА
  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) // Западен стандарт на подредба на книгите.
  {
    chaptersCountArr[55] = 16; // Рим
    chaptersCountArr[56] = 16;
    chaptersCountArr[57] = 13;
    chaptersCountArr[58] = 6;
    chaptersCountArr[59] = 6;
    chaptersCountArr[60] = 4;
    chaptersCountArr[61] = 4;
    chaptersCountArr[62] = 5;
    chaptersCountArr[63] = 3;
    chaptersCountArr[64] = 6;
    chaptersCountArr[65] = 4;
    chaptersCountArr[66] = 3;
    chaptersCountArr[67] = 1;
    chaptersCountArr[68] = 13; // Евр
    chaptersCountArr[69] = 5;  // Яков
    chaptersCountArr[70] = 5;
    chaptersCountArr[71] = 3;
    chaptersCountArr[72] = 5;
    chaptersCountArr[73] = 1;
    chaptersCountArr[74] = 1;
    chaptersCountArr[75] = 1;  // Юда
  }
  else // Източен стандарт на подредба на книгите.
  {
    chaptersCountArr[55] = 5;  // Яков
    chaptersCountArr[56] = 5;
    chaptersCountArr[57] = 3;
    chaptersCountArr[58] = 5;
    chaptersCountArr[59] = 1;
    chaptersCountArr[60] = 1;
    chaptersCountArr[61] = 1;  // Юда
    chaptersCountArr[62] = 16; // Рим
    chaptersCountArr[63] = 16;
    chaptersCountArr[64] = 13;
    chaptersCountArr[65] = 6;
    chaptersCountArr[66] = 6;
    chaptersCountArr[67] = 4;
    chaptersCountArr[68] = 4;
    chaptersCountArr[69] = 5;
    chaptersCountArr[70] = 3;
    chaptersCountArr[71] = 6;
    chaptersCountArr[72] = 4;
    chaptersCountArr[73] = 3;
    chaptersCountArr[74] = 1;
    chaptersCountArr[75] = 13; // Евр
  }
  chaptersCountArr[76] = 22; // Откр

  bookNameArr = TS->bookNameArr;
  bookShortNameArr = TS->bookShortNameArr;
  bookMinNameArr = TS->bookMinNameArr;
  bookFileNameArr = TS->bookFileNameArr;

  if (SVars.currentBooksOrder == BOOKS_ORDER__EASTERN) // Пренарежда масивите според източния стандарт (ако е избран).
  {
    // Структурите на файловете с преводите са направени по западния стандарт на подредба на главите (ДА-Рим-1Кор...Евр-Яков-1Петр...Юда-Откр).
    // За да се показват по източния стандарт (ДА-Яков-1Петр...Юда-Рим-1Кор...Евр-Откр) се налага да се разместят данните във всички масиви.
    //
    //                   Западен                    Източен
    //      --------------------       --------------------
    // 55                ДА                         ДА          55 -> 55
    // 56   1237 (34818) Рим --        1237 (34818) Яков --     56 -> 70
    // 57                1 Кор                      1 Пет       57 -> 71
    // 58                2 Кор                      2 Пет       58 -> 72
    // 59                Гал                        1 Йоан      59 -> 73
    // 60                Еф                         2 Йоан      60 -> 74
    // 61                Фил                        3 Йоан      61 -> 75
    // 62                Кол                        Юда         62 -> 76
    // 63                1 Сол         1258 (35250) Рим --      63 -> 56   <-- Това се изчислява така: 1237+(1358-1337)=1258  и  34818+(37589-37157)=35250.
    // 64                2 Сол                      1 Кор       64 -> 57
    // 65                1 Тим                      2 Кор       65 -> 58
    // 66                2 Тим                      Гал         66 -> 59
    // 67                Тит                        Еф          67 -> 60
    // 68                Филим                      Фил         68 -> 61
    // 69                Евр                        Кол         69 -> 62
    // 70   1337 (37157) Яков --                    1 Сол       70 -> 63
    // 71                1 Пет                      2 Сол       71 -> 64
    // 72                2 Пет                      1 Тим       72 -> 65
    // 73                1 Йоан                     2 Тим       73 -> 66
    // 74                2 Йоан                     Тит         74 -> 67
    // 75                3 Йоан                     Филим       75 -> 68
    // 76                Юда                        Евр         76 -> 69
    // 77   1358 (37589) Откр --       1358 (37589) Откр --     77 -> 77
    //
    QString sArr77[77]; // Помощен масив.
    for (quint8 i = 55; i < 76; i++)
      sArr77[toEasternBookCodeIfNeed(i+1)-1] = bookNameArr[i]; // Записва ги разместени.
    for (quint8 i = 55; i < 76; i++)
      bookNameArr[i] = sArr77[i]; // Връща стойностите обратно.
    
    for (quint8 i = 55; i < 76; i++)
      sArr77[toEasternBookCodeIfNeed(i+1)-1] = bookShortNameArr[i]; // Записва ги разместени.
    for (quint8 i = 55; i < 76; i++)
      bookShortNameArr[i] = sArr77[i]; // Връща стойностите обратно.
    
    for (quint8 i = 55; i < 76; i++)
      sArr77[toEasternBookCodeIfNeed(i+1)-1] = bookMinNameArr[i]; // Записва ги разместени.
    for (quint8 i = 55; i < 76; i++)
      bookMinNameArr[i] = sArr77[i]; // Връща стойностите обратно.
    
    for (quint8 i = 55; i < 76; i++)
      sArr77[toEasternBookCodeIfNeed(i+1)-1] = bookFileNameArr[i]; // Записва ги разместени.
    for (quint8 i = 55; i < 76; i++)
      bookFileNameArr[i] = sArr77[i]; // Връща стойностите обратно.
  }

  // Следващите два цикъла са идентични с разлика само в един ред, но ми е по-лесно да ги направя два отделни с копи-пейст.

  // За протестантските текстове (66 книги).
  int verseAbsIndex = 0;
  int chapterAbsIndex = 0;
  quint8 bookCode = 0;
  QStringList sList = getChapStructure(false);
  foreach (QString sBook, sList) // Този цикъл обхожда всички книги.
  {
    int chapterCode = -1;
    QStringList sChapters = sBook.split(" ", QString::SkipEmptyParts);
    foreach (QString sChapter, sChapters) // Този цикъл обхожда всички глави.
    {
      int versesCount = sChapter.toInt();
      if (chapterCode != -1)
      {
        chapterCode++;
        booksShortArr[toEasternShortIndexIfNeed(chapterAbsIndex)] = toEasternBookCodeIfNeed(bookCode);
        chaptersShortArr[toEasternShortIndexIfNeed(chapterAbsIndex)] = chapterCode;
        chapterAbsIndex++;
        for (quint8 v = 0; v < versesCount; v++)
        {
          booksExtArr[toEasternExtIndexIfNeed(verseAbsIndex)] = toEasternBookCodeIfNeed(bookCode);
          chapters66ExtArr[toEasternExtIndexIfNeed(verseAbsIndex)] = chapterCode; // <--- Само това е различно и заради него са двата цикъла.
          verseAbsIndex++;
        }
      }
      else // Пропуска първото число, защото е номер на книга, а не брой на стиховете в конкретната глава.
      {
        chapterCode = 0;
        bookCode = versesCount; // Тук versesCount съдържа поредния номер на книгата.
      }
    }
  }

  // За православните текстове (77 книги). 
  verseAbsIndex = 0;
  chapterAbsIndex = 0;
  bookCode = 0;
  sList = getChapStructure(true);
  foreach (QString sBook, sList) // Този цикъл обхожда всички книги.
  {
    int chapterCode = -1;
    QStringList sChapters = sBook.split(" ", QString::SkipEmptyParts);
    foreach (QString sChapter, sChapters) // Този цикъл обхожда всички глави.
    {
      int versesCount = sChapter.toInt();
      if (chapterCode != -1)
      {
        chapterCode++;
        //booksShortArr[toEasternShortIndexIfNeed(chapterAbsIndex)] = toEasternBookCodeIfNeed(bookCode); // Това се инициализира в горния цикъл и тук няма смисъл, защото ще получи същата стойност.
        //chaptersShortArr[toEasternShortIndexIfNeed(chapterAbsIndex)] = chapterCode;                    // Това се инициализира в горния цикъл и тук няма смисъл, защото ще получи същата стойност.
        chapterAbsIndex++;
        for (quint8 v = 0; v < versesCount; v++)
        {
          //booksExtArr[toEasternExtIndexIfNeed(verseAbsIndex)] = toEasternBookCodeIfNeed(bookCode); // Това се инициализира в горния цикъл и тук няма смисъл, защото ще получи същата стойност.
          chapters77ExtArr[toEasternExtIndexIfNeed(verseAbsIndex)] = chapterCode; // <--- Само това е различно и заради него са двата цикъла.
          verseAbsIndex++;
        }
      }
      else // Пропуска първото число, защото е номер на книга, а не брой на стиховете в конкретната глава.
      {
        chapterCode = 0;
        bookCode = versesCount; // Тук versesCount съдържа поредния номер на книгата.
      }
    }
  }
}

MainObject::MainObject()
{
  //splash = new QSplashScreen(QPixmap(":/resources/images/logo100.png"));
  //splash->show(); // Показва началния прозорец (логото).

  TS = new TrStrings(); // Тук се инициализират всички стрингове.

  QApplication::setLayoutDirection(TS->globalLayoutDirection);

  enableExitAction = false;
  isFirstStart = false;
  isNewVersion = false;

  applicationDirPath = QCoreApplication::applicationDirPath();

  // Установяване на директорията applicationHomePath в, която ще се записват настройките на MatCrossBible, бележника и други.
  // Отначало се проверява дали потребителят е задал път във файла /Settings/PathToSettings.ini.
  // Ако вместо път е написал думата "local", пътят ще се насочи към директория /Settings, намираща се в директорията на изпълнимия файл.
  // Ако е задал валиден път, то той става applicationHomePath.
  // Ако не е задал или е задал, но е невалиден (несъществуващ), то applicationHomePath се избира автоматично според QDir::homePath().
  // ------------------------------------------------------------------------------------------------------------------------------------
  createPathToSettingsIniFile(); // Създава PathToSettings.ini файла, ако не съществува.
  QSettings iniSettings(QString("%1/Settings/PathToSettings.ini").arg(applicationDirPath), QSettings::IniFormat, this);
  iniSettings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  QString pathToSettings = iniSettings.value(QString("fullPath"), "").toString(); // Потребителски зададен път за настройките.
  pathToSettings = QDir::fromNativeSeparators(pathToSettings); // Установява разделителите на пътя в нормални наклонени черти /.

  if (pathToSettings == QString("local")) // Ако вместо път е написана думата "local"
  {
    applicationHomePath = QString("%1/Settings").arg(applicationDirPath);
  }
  else if ( !pathToSettings.isEmpty() && QDir( pathToSettings ).exists() ) // Ако е зададен специален път, където да се записват настройките.
  {
    applicationHomePath = pathToSettings;
  }
  else // Ако не е зададен специален път, където да се записват настройките.
  {
    if (QDir::homePath() != QDir::rootPath()) // Ако home-директорията е различна от root-директорията. QDir::rootPath() -- For Unix operating systems this returns "/". For Windows file systems this normally returns "c:/".
    {
      applicationHomePath = QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath());
    }
    else // Ако има проблем с разпознаването на хом-директорията.
    {
      applicationHomePath = QString("%1/Settings").arg(applicationDirPath);
    }
  }
  // ------------------------------------------------------------------------------------------------------------------------------------

  iniFile = QString("%1/Config/MatCrossBible.ini").arg(applicationHomePath);
  sessionsFile = QString("%1/Config/MatCrossBible.Sessions.ini").arg(applicationHomePath);

  // |--applicationHomePath
  //    |--.MatCraft
  //       |--MatCrossBible
  //          |--Config
  //          |--Pad
  //          |--Resources
  QDir dir; // Създава (ако не съществуват) директориите, в които ще се поместват различни файлове като например INI-файла, бележника (Pad.txt) и др.
  dir.mkpath(applicationHomePath);
  dir.mkpath(QString("%1/Config").arg(applicationHomePath));
  dir.mkpath(QString("%1/Pad").arg(applicationHomePath));
  dir.mkpath(QString("%1/Resources").arg(applicationHomePath));

  dir.mkpath(QString("%1/Audio").arg(applicationDirPath));
  dir.mkpath(QString("%1/BibleTexts").arg(applicationDirPath));
  dir.mkpath(QString("%1/DictAndComm").arg(applicationDirPath));
  dir.mkpath(QString("%1/Images").arg(applicationDirPath));
  dir.mkpath(QString("%1/Tr").arg(applicationDirPath));

  loadSVarsSettings();
  TS->initEmbedBooksNames(SVars.currentBooksTranslation);

  setBibStructure();

  QSettings settings(iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Чете реда на текстовете от настройките:
  QStringList bibleTextsOrder = settings.value(QString("bibleTextsOrder"), "").toString().split("^", QString::SkipEmptyParts);

  QStringList allFileNamesUnordered = QDir( QString("%1/BibleTexts").arg(applicationDirPath) ).entryList(QDir::Files, QDir::Name); // QDir::Name QDir::Time QDir::Unsorted
  QStringList allFileNames; // Подреден списък.

  // Пренарежда списъка с имената на текстовете според горния ред:
  for (quint16 ord = 0; ord < bibleTextsOrder.count(); ord++)
  {
    QString fName = bibleTextsOrder[ord];
    quint16 index = 65535;
    for (quint16 i = 0; i < allFileNamesUnordered.count(); i++)
    {
      index = 65535;
      if (allFileNamesUnordered[i].toLower().contains(fName.toLower() + ".hbt"))
      {
        index = i;
      }
      if (index != 65535)
      {
        allFileNames << allFileNamesUnordered[i]; // Добавя тези от списъка в реда, в който са.
        allFileNamesUnordered.removeAt(i);
        break;
      }
    }
  }
  for (quint16 i = 0; i < allFileNamesUnordered.count(); i++)
  {
    allFileNames << allFileNamesUnordered[i]; // Добавя останалите, ако има такива (ще има такива, ако е добавен нов файл).
  }

  // Версия 3 на текстовете на Библията.
  // Файлът започва с текста на Библията, а служебните редове са в края му, разделени с един празен ред от текста:
  //
  // ...
  // 21. Благодатта на Господ Исус Христос да бъде със светиите. Амин.
  //
  // STRUCTURE_VERSION=3
  // NAME=ББД (2005)
  // SHORT_DESCRIPTION=Българско библейско дружество (ББД), 2005. Всички права запазени ©
  // NUMERATION_CODE=1
  // NATIVE_VERSE_NUMERATION=Yes
  // FONT_FAMILY=
  // LAYOUT_DIRECTION=LeftToRight
  // LANGUAGE=Bulgarian
  // LAST_MODIFY_DATE=2013.12.09
  // DESCRIPTION:
  // Българско библейско дружество (ББД), 2005. Всички права запазени ©.<br>
  // Преводът е написан на съвременен български език.<br>
  // <br>
  // Текстът съдържа следните форматиращи скоби:<br>
  // &nbsp; <b>( )</b> - стандартна граматическа функция ("в скоби");<br>
  // &nbsp; <b>{ }</b> - обяснение на предишната дума или фраза (т.нар. бележка под линия).<br>
  // В <i>наклонен шрифт (курсив)</i> са думите, които липсват в оригиналния текст, а са добавени поради логична необходимост.<br>
  // В <b>удебелен шрифт</b> са думите или фразите, които автора е преценил, че са важни и си струва да се откроят от останалия текст.

  bibleTextList.clear();
  QString fileName;
  char buf[BUF_LEN];
  for (quint16 f = 0; f < allFileNames.count(); f++)
  {
    fileName = QString("%1/BibleTexts/%2").arg(applicationDirPath).arg(allFileNames[f]);
    if (QFile::exists(fileName))
    {
      QFileInfo fileInfo(fileName);
      if (fileInfo.suffix().toLower() != QString("hbt")) continue; // Ако разширението на файла не е .hbt го игнорира.

      BIBLE_TEXT bt;
      bt.fileName = fileName;
      bt.fileBaseName = fileInfo.completeBaseName(); // Тук се използва completeBaseName, а по-горе се използва suffix, а не completeSuffix. Това означава, че всяка точка в името на файла, без последната, ще се счита като част от името, а не като част от разширението.
      bt.file = new QFile(fileName);
      bt.file->open(QIODevice::ReadOnly);

      QString line; // Ред от файла;
      qint64 lineLength;

      // Пълнене на масива с отместванията.
      quint8 currBook = 0;
      for(quint16 i = 0; i < MAX_VERSES; i++) // Тук i е абсолютният индекс на стиха по западния стандарт на подредба на книгите (защото файловете са винаги по западния).
      {
        if (booksExtArr[toEasternExtIndexIfNeed(i)] != toEasternBookCodeIfNeed(currBook)) // Ако следващият стих (ред), който ще се прочете е първият стих на нова глава. Структурата може да е по източния стандарт, затова тук се прави евентуално конвертиране.
        {
          currBook++; // currBook е по западния стандарт и приема стойността на следващата глава. 
          bt.seekBookArr[toEasternBookCodeIfNeed(currBook)-1] = bt.file->pos(); // Това е началната позиция на новата глава. Тук се прави и конвертиране към източния стандарт (ако се налага), защото файловете са винаги по западния.
        }
        //bt.seekVerseArr[i] = bt.file->pos(); // Това е началната позиция на всеки стих.
        lineLength = bt.file->readLine(buf, sizeof(buf)); // Чете един стих (ред). След прочитането pos() ще върне края на прочетения ред (т.е. началото на следващия).
        if (lineLength <= 0) continue; // Ако файлът е с по-малко редове.
      }

      // Чете празния ред след текста.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      if (line.length() > 2) // Ако не е празен ред.
      {
        bt.file->close();
        continue;
      }

      // Чете първия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("STRUCTURE_VERSION=")); // Изтрива се ненужната информация.
      if (line.toUShort() != STRUCTURE_VERSION)   // Ако файлът има структура различна от очакваната.
      {
        bt.file->close();
        continue;
      }

      // Чете втория служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("NAME=")); // Изтрива се ненужната информация.
      bt.name = line.trimmed();      // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.

      // Чете третия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("SHORT_DESCRIPTION=")); // Изтрива се ненужната информация.
      bt.short_description = line.trimmed();      // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.

      // Чете четвъртия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("NUMERATION_CODE=")); // Изтрива се ненужната информация.
      bt.booksExtArr = booksExtArr;
      if (line.toUShort() == NUMERATION__2) // Ако е с номерация 2 на стиховете.
      {
        bt.chaptersExtArr = chapters77ExtArr;
      }
      else //if (line.toUShort() == NUMERATION__1) // Ако е с номерация 1 на стиховете.
      {
        bt.chaptersExtArr = chapters66ExtArr;
      }
      //else // Ако числото на номерацията е друго (грешно записано).
      //{
      //  bt.file->close();
      //  continue;
      //}

      // Чете петия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("NATIVE_VERSE_NUMERATION=")); // Изтрива се ненужната информация.
      line = line.trimmed().toUpper();                  // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
      if (line == "YES" || line == "TRUE")
      {
        bt.nativeVerseNum = true;
      }
      else //if (line == "NO" || line == "FALSE")
      {
        bt.nativeVerseNum = false;
      }

      // Чете шестия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("FONT_FAMILY=")); // Изтрива се ненужната информация.
      bt.nativeFontFamily = line.trimmed(); // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
      bt.fontFamily = mergeFontFamilies(bt.nativeFontFamily, SVars.fontFamily);

      // Чете седмия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("LAYOUT_DIRECTION=")); // Изтрива се ненужната информация.
      line = line.trimmed().toUpper();           // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
      if (line == "RIGHTTOLEFT" || line == "RIGHT_TO_LEFT")
      {
        bt.layoutDirection = Qt::RightToLeft;
      }
      else //if (line == "LEFTTORIGHT" || line == "LEFT_TO_RIGHT")
      {
        bt.layoutDirection = Qt::LeftToRight;
      }
      //else // Ако е грешно записано.
      //{
      //  bt.file->close();
      //  continue;
      //}

      // Чете осмия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("LANGUAGE=")); // Изтрива се ненужната информация.
      bt.language = line.trimmed();      // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.

      // Чете деветия служебен ред.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("LAST_MODIFY_DATE=")); // Изтрива се ненужната информация.
      bt.lastModifyDate = line.trimmed();        // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.

      // Чете последните редове с описанието на текста.
      bt.file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);
      line.remove(QString("DESCRIPTION:")); // Изтрива се ненужната информация.
      //line = line.trimmed(); // Тук не трябва да се използва trimmed() за да не се изтрие евентуален последен интервал на реда и това да доведе до слепване на последната дума от този ред с първата от следващия.
      bt.description = "";
      if (line.length() > 0) bt.description = line; // Ако след двете точки има текст.
      while (!bt.file->atEnd())
      {
        bt.file->readLine(buf, sizeof(buf)); // Чете следващ ред.
        line = QString("%1").arg(buf);
        bt.description += line;//.trimmed(); // Тук не трябва да се използва trimmed() за да не се изтрие евентуален последен интервал на реда и това да доведе до слепване на последната дума от този ред с първата от следващия.
      }

      bibleTextList.append(bt);
    }
  }

  // Записва реда на текстовете в настройките:
  QString bTextsOrder = "";
  for (int i = 0; i < bibleTextList.size(); i++)
  {
    bTextsOrder += bibleTextList[i].fileBaseName + "^";
  }
  settings.setValue(QString("bibleTextsOrder"), bTextsOrder);

  // Инициализира индекса на текста, в който ще се търси.
  SVars.searchTargetTextIndex = 0;
  for (int i = 0; i < bibleTextList.size(); i++)
  {
    if (bibleTextList[i].fileBaseName == SVars.searchTargetText)
    {
      SVars.searchTargetTextIndex = i;
      break;
    }
  }

  /// Отметки -------------------------------------------------------------------------------------------------------------------------------------------------
  QString bmStr = settings.value(QString("bookmarks"), "").toString();
  QStringList bmList = bmStr.split("^", QString::SkipEmptyParts);

  // bookmarkIndex.verseAbsCode.verseCode^bookmarkIndex.verseAbsCode.verseCode...

  for (int i = 0; i < MAX_BOOKMARKS; i++)
  {
    bookmarks[i].absIndex = MAX_VERSES;
    bookmarks[i].label = "";
  }

  quint8  bookmarkIndex = 0; // 0 - MAX_BOOKMARKS-1
  quint16 verseAbsCode = 0;  // 1 - MAX_VERSES
  QString verseCode = "";    // Стринг, съдържащ извлечения от стиха номер или въпросителен знак, ако номерът не е бил определен.
  bool    ok0 = false;
  bool    ok1 = false;
  quint8  bCode = 1, cCode = 1, vCode = 1;
  for (quint8 i = 0; i < bmList.size(); i++)
  {
    QStringList bm = bmList[i].split(".", QString::SkipEmptyParts);
    if (bm.size() == 3) // Ако формата на отметката е валиден.
    {
      bookmarkIndex = bm[0].toUInt(&ok0);
      verseAbsCode = bm[1].toUInt(&ok1);
      verseCode = bm[2];

      if (ok0 && ok1 && bookmarkIndex < MAX_BOOKMARKS && verseAbsCode > 0 && verseAbsCode <= MAX_VERSES) // Ако има отметка и е валиден стих. Тук индексът започва от 1.
      {
        bookmarks[bookmarkIndex].absIndex = toEasternExtIndexIfNeed(verseAbsCode - 1); // Номерата на стиховете започват от 1, затова тук се прави да започва от 0. // Тук конвертира кода към източния стандарт, ако е нужно.
        absIndexToReference(bookmarks[bookmarkIndex].absIndex, bCode, cCode, vCode); // Този ред трябва да е след горния. Превръща абсолютния индекс на стиха в препратки (код на книгата, главата и стиха).
        bookmarks[bookmarkIndex].verseCode = verseCode;
        bookmarks[bookmarkIndex].label = QString("%1 %2:%3").arg(bookMinNameArr[bCode-1]).arg(cCode).arg(verseCode);
      }
      else // Ако няма отметка или е невалиден стих.
      {
        bookmarks[bookmarkIndex].absIndex = MAX_VERSES;
        bookmarks[bookmarkIndex].verseCode = "";
        bookmarks[bookmarkIndex].label = "";
      }
    }
    else // Ако формата на отметката е повреден (това става, ако е писано на ръка в INI файла).
    {
      bookmarks[bookmarkIndex].absIndex = MAX_VERSES;
      bookmarks[bookmarkIndex].verseCode = "";
      bookmarks[bookmarkIndex].label = "";
    }
  }
  /// Отметки -------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef QT_NO_PRINTER
  printer = new QPrinter(QPrinter::HighResolution);
  printer->setPaperSize(QPrinter::A4);
  printer->setOrientation(QPrinter::Portrait);
  printer->setPageMargins(15, 5, 5, 10, QPrinter::Millimeter);
#endif

  for (int i = MAX_VERSES-1; i >= 0 ; i--) // Цикълът се движи в обратен ред и по този начин в bookStartIndexInBooksExtArr...
  {
    bookStartIndexInBooksExtArr[booksExtArr[i]-1] = i; // ...ще се запомни началният индекс в booksExtArr на всяка книга.
  }
  
  // Ако програмата се пуска за първи път или ако не е за първи път, но е по-нова версия от последно пуснатата:
  if (isFirstStart || isNewVersion)
  {
    //QString fileName = QString("%1/Images/Genealogy-Line, Ver 1.0, Bulgarian.png").arg(applicationDirPath);
    //if (!QFile::exists(fileName)) // Ако файлът не съществува на хардиска.
    //{
    //  QFile file(":/resources/genealogy/Genealogy-Line, Ver 1.0, Bulgarian.png"); // Зарежда файла от ресурсите (вграденият в exe-то файл).
    //  file.copy(fileName); // Записва го на хардиска.
    //}
    //
    //fileName = QString("%1/Images/Genealogy-Tree, Ver 1.0, Bulgarian.png").arg(applicationDirPath);
    //if (!QFile::exists(fileName)) // Ако файлът не съществува на хардиска.
    //{
    //  QFile file(":/resources/genealogy/Genealogy-Tree, Ver 1.0, Bulgarian.png"); // Зарежда файла от ресурсите (вграденият в exe-то файл).
    //  file.copy(fileName); // Записва го на хардиска.
    //}
  }
}

MainObject::~MainObject()
{
  for (int i = 0; i < bibleTextList.size(); i++)
  {
    bibleTextList[i].file->close();
  }
  //qDebug("~~~~~~~~");
}

void MainObject::loadSVarsSettings()
{
  QSettings settings(iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Global
  QString applicationVersion = settings.value(QString("applicationVersion"), "").toString();
  if (applicationVersion.isEmpty()) isFirstStart = true; // Ако програмата се пуска за първи път. Този флаг се чете където е нужно и се прави каквото е нужно.
  if (applicationVersion != QCoreApplication::applicationVersion()) // Ако програмата се пуска за първи път или не се пуска за първи път, но има разминаване във версиите с тази от последното пускане.
  {
    // Тук се прави по-точна проверка на версията и се правят необходимите действия, а после новата версия се записва и следващия път не се минава през това място.
    if ( appVersionToInt(QCoreApplication::applicationVersion()) > appVersionToInt(applicationVersion.trimmed()) ) // Ако текущата версия на програмата е по-нова от последно пуснатата програма.
    {
      isNewVersion = true; // Този флаг се чете където е нужно и се прави каквото е нужно.
    }

    applicationVersion = QCoreApplication::applicationVersion();
    settings.setValue(QString("applicationVersion"), applicationVersion);
  }
  
  // Language
  settings.beginGroup(QString("Language"));
  SVars.currentBooksTranslation = settings.value(QString("currentBooksTranslation"), "").toString();
  if (!TS->allBooksTranslation.contains(SVars.currentBooksTranslation)) SVars.currentBooksTranslation = ""; // Ако името на превода записано в INI файла, не от вградените езици.
  settings.endGroup();

  // Colors
  settings.beginGroup(QString("Colors"));
  SVars.dock1TextColorF.setNamedColor( settings.value(QString("dock1TextColorF"), "").toString() );
  if (!SVars.dock1TextColorF.isValid())
  {
    SVars.dock1TextColorF = QColor(16, 16, 16); // (#101010) Тъмно сив.
    settings.setValue(QString("dock1TextColorF"), SVars.dock1TextColorF.name());
  }

  SVars.dock1TextColorB.setNamedColor( settings.value(QString("dock1TextColorB"), "").toString() );
  if (!SVars.dock1TextColorB.isValid())
  {
    SVars.dock1TextColorB = QColor(255, 255, 255); // (#ffffff) Бял.
    settings.setValue(QString("dock1TextColorB"), SVars.dock1TextColorB.name());
  }

  SVars.dock1BGImage = settings.value(QString("dock1BGImage"), "aaa").toString();
  if (!SVars.dock1BGImage.isEmpty() && !QFile::exists(SVars.dock1BGImage))
  {
    SVars.dock1BGImage = "";
    settings.setValue(QString("dock1BGImage"), SVars.dock1BGImage);
  }

  SVars.dock2TextColorF.setNamedColor( settings.value(QString("dock2TextColorF"), "").toString() );
  if (!SVars.dock2TextColorF.isValid())
  {
    SVars.dock2TextColorF = QColor(16, 16, 16); // (#101010) Тъмно сив.
    settings.setValue(QString("dock2TextColorF"), SVars.dock2TextColorF.name());
  }

  SVars.dock2TextColorB.setNamedColor( settings.value(QString("dock2TextColorB"), "").toString() );
  if (!SVars.dock2TextColorB.isValid())
  {
    SVars.dock2TextColorB = QColor(255, 255, 255); // (#ffffff) Бял.
    //SVars.dock2TextColorB = QColor(255, 255, 235); // (#ffffeb) Бледо жълт.
    settings.setValue(QString("dock2TextColorB"), SVars.dock2TextColorB.name());
  }

  SVars.dock2BGImage = settings.value(QString("dock2BGImage"), "aaa").toString();
  if (!SVars.dock2BGImage.isEmpty() && !QFile::exists(SVars.dock2BGImage))
  {
    SVars.dock2BGImage = "";
    settings.setValue(QString("dock2BGImage"), SVars.dock2BGImage);
  }

  SVars.oldTestamentColorF.setNamedColor( settings.value(QString("oldTestamentColorF"), "").toString() );
  if (!SVars.oldTestamentColorF.isValid())
  {
    SVars.oldTestamentColorF = QColor(0, 170, 170); // (#00aaaa) Тъмно зелен/син.
    settings.setValue(QString("oldTestamentColorF"), SVars.oldTestamentColorF.name());
  }

  SVars.oldTestamentColorFA = SVars.oldTestamentColorF;
  SVars.oldTestamentColorFA.setAlphaF(0.6); //setAlpha(150);

  SVars.newTestamentColorF.setNamedColor( settings.value(QString("newTestamentColorF"), "").toString() );
  if (!SVars.newTestamentColorF.isValid())
  {
    SVars.newTestamentColorF = QColor(255, 96, 80); // (#ff6050) Светло червен (Tomato).
    settings.setValue(QString("newTestamentColorF"), SVars.newTestamentColorF.name());
  }

  SVars.oldTestamentAlphaF = settings.value(QString("oldTestamentAlphaF"), -1).toInt();
  if (SVars.oldTestamentAlphaF < 0 || SVars.oldTestamentAlphaF > 255)
  {
    SVars.oldTestamentAlphaF = 40;
    settings.setValue(QString("oldTestamentAlphaF"), SVars.oldTestamentAlphaF);
  }

  SVars.newTestamentAlphaF = settings.value(QString("newTestamentAlphaF"), -1).toInt();
  if (SVars.newTestamentAlphaF < 0 || SVars.newTestamentAlphaF > 255)
  {
    SVars.newTestamentAlphaF = 32;
    settings.setValue(QString("newTestamentAlphaF"), SVars.newTestamentAlphaF);
  }

  SVars.textInBracketsColorF.setNamedColor( settings.value(QString("textInBracketsColorF"), "").toString() );
  if (!SVars.textInBracketsColorF.isValid())
  {
    SVars.textInBracketsColorF = QColor(160, 160, 160); // (#a0a0a0) Сив.
    settings.setValue(QString("textInBracketsColorF"), SVars.textInBracketsColorF.name());
  }

  SVars.JesusWordsColorF.setNamedColor( settings.value(QString("JesusWordsColorF"), "").toString() );
  if (!SVars.JesusWordsColorF.isValid())
  {
    SVars.JesusWordsColorF = QColor(176, 0, 0); // (#b00000) Винено червен.
    settings.setValue(QString("JesusWordsColorF"), SVars.JesusWordsColorF.name());
  }

  SVars.JesusWordsColorFEnable = settings.value(QString("JesusWordsColorFEnable"), true).toBool();

  SVars.compareEqColorF.setNamedColor( settings.value(QString("compareEqColorF"), "").toString() );
  if (!SVars.compareEqColorF.isValid())
  {
    SVars.compareEqColorF = QColor(16, 16, 16); // (#101010) Тъмно сив.
    settings.setValue(QString("compareEqColorF"), SVars.compareEqColorF.name());
  }

  SVars.compareNoEqColorF.setNamedColor( settings.value(QString("compareNoEqColorF"), "").toString() );
  if (!SVars.compareNoEqColorF.isValid())
  {
    SVars.compareNoEqColorF = QColor(160, 160, 160); // (#a0a0a0) Сив.
    settings.setValue(QString("compareNoEqColorF"), SVars.compareNoEqColorF.name());
  }

  SVars.appColorF.setNamedColor( settings.value(QString("appColorF"), "").toString() );
  if (!SVars.appColorF.isValid())
  {
    SVars.appColorF = QColor(255, 255, 255); // (#ffffff) Бяло (Windows 10).
    //SVars.appColorF = QColor(235, 235, 235); // (#ebebeb) Почти бяло (с видими 3D заглавни ленти).
    settings.setValue(QString("appColorF"), SVars.appColorF.name());
  }

  SVars.appColorB.setNamedColor( settings.value(QString("appColorB"), "").toString() );
  if (!SVars.appColorB.isValid())
  {
    SVars.appColorB = QColor(100, 100, 100);  // Тъмно сив.
    settings.setValue(QString("appColorB"), SVars.appColorB);
  }

  SVars.docks3DTitleBar = settings.value(QString("docks3DTitleBar"), false).toBool();
  settings.endGroup();

  // View
  settings.beginGroup(QString("View"));
  SVars.TMenuPosition = (quint8)settings.value(QString("TMenuPosition"), 0).toUInt();
  if (SVars.TMenuPosition != POSITION_TOP && SVars.TMenuPosition != POSITION_BOTTOM)
  {
    SVars.TMenuPosition = POSITION_TOP;
    settings.setValue(QString("TMenuPosition"), SVars.TMenuPosition);
  }

  SVars.TMenuIconSize = settings.value(QString("TMenuIconSize"), 0).toUInt(); // 16 24 32 40 48 56 64 72 80 88 96
  if (SVars.TMenuIconSize < 16 || SVars.TMenuIconSize > 96 || (SVars.TMenuIconSize % 8) != 0)
  {
    SVars.TMenuIconSize = 24;
    settings.setValue(QString("TMenuIconSize"), SVars.TMenuIconSize);
  }

  SVars.booksToolBarPosition = (quint8)settings.value(QString("booksToolBarPosition"), 0).toUInt();
  if (SVars.booksToolBarPosition != POSITION_LEFT && SVars.booksToolBarPosition != POSITION_RIGHT)
  {
    SVars.booksToolBarPosition = POSITION_LEFT;
    settings.setValue(QString("booksToolBarPosition"), SVars.booksToolBarPosition);
  }

  SVars.otherToolBarFontSize = settings.value(QString("otherToolBarFontSize"), 0).toInt();
  QFontDatabase fdb;
  bool standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (fSize >= 6 && fSize <= 48 && SVars.otherToolBarFontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.otherToolBarFontSize = 8;
    settings.setValue(QString("otherToolBarFontSize"), SVars.otherToolBarFontSize);
  }

  SVars.booksToolBarFontSize = settings.value(QString("booksToolBarFontSize"), 0).toInt();
  standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (fSize >= 6 && fSize <= 20 && SVars.booksToolBarFontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.booksToolBarFontSize = 8;
    settings.setValue(QString("booksToolBarFontSize"), SVars.booksToolBarFontSize);
  }

  SVars.searchToolBarPosition = (quint8)settings.value(QString("searchToolBarPosition"), 0).toUInt();
  if (SVars.searchToolBarPosition != POSITION_LEFT && SVars.searchToolBarPosition != POSITION_RIGHT)
  {
    SVars.searchToolBarPosition = POSITION_RIGHT;
    settings.setValue(QString("searchToolBarPosition"), SVars.searchToolBarPosition);
  }

  SVars.searchToolBarWidth = settings.value(QString("searchToolBarWidth"), 0).toInt();
  if (SVars.searchToolBarWidth < 100)
  {
    SVars.searchToolBarWidth = 300;
    settings.setValue(QString("searchToolBarWidth"), SVars.searchToolBarWidth);
  }

  SVars.searchToolBarFontSize = settings.value(QString("searchToolBarFontSize"), 0).toInt();
  standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (fSize >= 6 && fSize <= 20 && SVars.searchToolBarFontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.searchToolBarFontSize = 8;
    settings.setValue(QString("searchToolBarFontSize"), SVars.searchToolBarFontSize);
  }

  SVars.projectorToolBarPosition = (quint8)settings.value(QString("projectorToolBarPosition"), 0).toUInt();
  if (SVars.projectorToolBarPosition != POSITION_LEFT && SVars.projectorToolBarPosition != POSITION_RIGHT)
  {
    SVars.projectorToolBarPosition = POSITION_LEFT;
    settings.setValue(QString("projectorToolBarPosition"), SVars.projectorToolBarPosition);
  }

  SVars.projectorToolBarPrevSize = settings.value(QString("projectorToolBarPrevSize"), 0).toInt();
  if (SVars.projectorToolBarPrevSize < 160 || SVars.projectorToolBarPrevSize > 512 || SVars.projectorToolBarPrevSize%16 != 0)
  {
    SVars.projectorToolBarPrevSize = 256;
    settings.setValue(QString("projectorToolBarPrevSize"), SVars.projectorToolBarPrevSize);
  }

  SVars.projectorToolBarFontSize = settings.value(QString("projectorToolBarFontSize"), 0).toInt();
  standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (fSize >= 6 && fSize <= 20 && SVars.projectorToolBarFontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.projectorToolBarFontSize = 8;
    settings.setValue(QString("projectorToolBarFontSize"), SVars.projectorToolBarFontSize);
  }

  SVars.GUIStyle = QString("Fusion"); // Програмата ще използва само този стил (защото другите не се държат добре при смяната на цветовете) и потребителят няма да има възможност да го сменя. Но кодът за избор на стиловете не е изтрит, а само закоментиран, където трябва (тук и в сетингите - за да не се вижда комбобокса).
  //SVars.GUIStyle = settings.value(QString("GUIStyle"), "").toString();
  //if (!QStyleFactory::keys().contains(SVars.GUIStyle)) // QStyleFactory::keys е списък с имената на всички поддържани от системата стилове.
  //{
  //  SVars.GUIStyle = "";
  //  settings.setValue(QString("GUIStyle"), SVars.GUIStyle);
  //}
  qApp->setStyle(SVars.GUIStyle); // Ако е непознат стил или SVars.GUIStyle = "", приложението ще остане непроменено, т.е. със системния стил.
  settings.endGroup();

  // Text
  settings.beginGroup(QString("Text"));
  SVars.globalFontSize = settings.value(QString("globalFontSize"), 0).toInt();
  standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (fSize >= 6 && fSize <= 20 && SVars.globalFontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.globalFontSize = 8;
    settings.setValue(QString("globalFontSize"), SVars.globalFontSize);
  }

  SVars.globalFontAntialias = settings.value(QString("globalFontAntialias"), true).toBool();

  QFont font = qApp->font();
  font.setPointSize(SVars.globalFontSize); // Големина на шрифта по подразбиране за всички обекти.
  if (SVars.globalFontAntialias) // Antialias на шрифта за всички обекти.
    font.setStyleStrategy(QFont::PreferAntialias);
  else
    font.setStyleStrategy(QFont::NoAntialias);
  qApp->setFont(font);

  SVars.fontFamily = settings.value(QString("fontFamily"), "").toString();
  if (SVars.fontFamily == "")
  {
    SVars.fontFamily = QString("Sans");
    settings.setValue(QString("fontFamily"), SVars.fontFamily);
  }

  SVars.fontSize = settings.value(QString("fontSize"), 0).toInt();
  standardSize = false;
  foreach(int fSize, fdb.standardSizes())
    if (SVars.fontSize == fSize)
      standardSize = true;
  if (!standardSize)
  {
    SVars.fontSize = 8;
    settings.setValue(QString("fontSize"), SVars.fontSize);
  }

  SVars.verseNumberBold = settings.value(QString("verseNumberBold"), true).toBool();

  SVars.verseNumberSup = settings.value(QString("verseNumberSup"), false).toBool();

  SVars.verseStruct = (quint8)settings.value(QString("verseStruct"), VERSE_STRUCT__NUMBER_ONLY).toUInt();
  if (SVars.verseStruct != VERSE_STRUCT__NUMBER_ONLY && SVars.verseStruct != VERSE_STRUCT__MIN_BOOK_NAME && SVars.verseStruct != VERSE_STRUCT__SHORT_BOOK_NAME)
  {
    SVars.verseStruct = VERSE_STRUCT__NUMBER_ONLY;
  }

  SVars.currentNumeration = (quint8)settings.value(QString("numeration"), 0).toUInt();
  if (SVars.currentNumeration != NUMERATION__1 && SVars.currentNumeration != NUMERATION__2)
  {
    SVars.currentNumeration = NUMERATION__1;
    settings.setValue(QString("numeration"), SVars.currentNumeration);
  }
  SVars.newNumeration = SVars.currentNumeration; // Този параметър ще се променя от настройките, а currentNumeration няма да се променя, освен тук - при първоначално пускане на програмата.

  SVars.currentBooksOrder = (quint8)settings.value(QString("booksOrder"), 0).toUInt();
  if (SVars.currentBooksOrder != BOOKS_ORDER__EASTERN && SVars.currentBooksOrder != BOOKS_ORDER__WESTERN)
  {
    SVars.currentBooksOrder = TS->isBulgarianAppTranslation ? BOOKS_ORDER__EASTERN : BOOKS_ORDER__WESTERN;
    settings.setValue(QString("booksOrder"), SVars.currentBooksOrder);
  }
  SVars.newBooksOrder = SVars.currentBooksOrder; // Този параметър ще се променя от настройките, а currentBooksOrder няма да се променя, освен тук - при първоначално пускане на програмата.

  SVars.showDeuterocanonical = settings.value(QString("showDeutrocanonical"), false).toBool(); // По подразбиране Второканоничните книги ще са скрити.
  SVars.newShowDeuterocanonical = SVars.showDeuterocanonical; // Този параметър ще се променя от настройките, а showDeuterocanonical няма да се променя, освен тук - при първоначално пускане на програмата.
  SVars.showAbsVerseNumber = settings.value(QString("showAbsVerseNumber"), false).toBool();
  settings.endGroup();

  // Search
  settings.beginGroup(QString("Search"));
  SVars.foundWordsBold = settings.value(QString("foundWordsBold"), false).toBool();
  SVars.foundWordsUnderline = settings.value(QString("foundWordsUnderline"), false).toBool();
  SVars.foundWordsColorF = settings.value(QString("foundWordsColorF"), false).toBool();
  SVars.foundWordsColorB = settings.value(QString("foundWordsColorB"), true).toBool();

  SVars.foundWordsColor1F.setNamedColor( settings.value(QString("foundWordsColor1F"), "").toString() );
  if (!SVars.foundWordsColor1F.isValid())
  {
    SVars.foundWordsColor1F = QColor(255,128,0); // (#ff8000)
    settings.setValue(QString("foundWordsColor1F"), SVars.foundWordsColor1F.name());
  }

  SVars.foundWordsColor2F.setNamedColor( settings.value(QString("foundWordsColor2F"), "").toString() );
  if (!SVars.foundWordsColor2F.isValid())
  {
    SVars.foundWordsColor2F = QColor(255, 85,255); // (#ff55ff)
    settings.setValue(QString("foundWordsColor2F"), SVars.foundWordsColor2F.name());
  }

  SVars.foundWordsColor3F.setNamedColor( settings.value(QString("foundWordsColor3F"), "").toString() );
  if (!SVars.foundWordsColor3F.isValid())
  {
    SVars.foundWordsColor3F = QColor(170,0,127); // (#aa007f)
    settings.setValue(QString("foundWordsColor3F"), SVars.foundWordsColor3F.name());
  }

  SVars.foundWordsColor4F.setNamedColor( settings.value(QString("foundWordsColor4F"), "").toString() );
  if (!SVars.foundWordsColor4F.isValid())
  {
    SVars.foundWordsColor4F = QColor(0,150,0); // (#009600)
    settings.setValue(QString("foundWordsColor4F"), SVars.foundWordsColor4F.name());
  }

  SVars.foundWordsColor5F.setNamedColor( settings.value(QString("foundWordsColor5F"), "").toString() );
  if (!SVars.foundWordsColor5F.isValid())
  {
    SVars.foundWordsColor5F = QColor(130,130,100); // (#828264)
    settings.setValue(QString("foundWordsColor5F"), SVars.foundWordsColor5F.name());
  }

  SVars.foundWordsColor1B.setNamedColor( settings.value(QString("foundWordsColor1B"), "").toString() );
  if (!SVars.foundWordsColor1B.isValid())
  {
    SVars.foundWordsColor1B = QColor(255,210,185); // (#ffd2b9)
    settings.setValue(QString("foundWordsColor1B"), SVars.foundWordsColor1B.name());
  }

  SVars.foundWordsColor2B.setNamedColor( settings.value(QString("foundWordsColor2B"), "").toString() );
  if (!SVars.foundWordsColor2B.isValid())
  {
    SVars.foundWordsColor2B = QColor(255,210,255); // (#ffd2ff)
    settings.setValue(QString("foundWordsColor2B"), SVars.foundWordsColor2B.name());
  }

  SVars.foundWordsColor3B.setNamedColor( settings.value(QString("foundWordsColor3B"), "").toString() );
  if (!SVars.foundWordsColor3B.isValid())
  {
    SVars.foundWordsColor3B = QColor(225,200,200); // (#e1c8c8)
    settings.setValue(QString("foundWordsColor3B"), SVars.foundWordsColor3B.name());
  }

  SVars.foundWordsColor4B.setNamedColor( settings.value(QString("foundWordsColor4B"), "").toString() );
  if (!SVars.foundWordsColor4B.isValid())
  {
    SVars.foundWordsColor4B = QColor(185,255,185); // (#b9ffb9)
    settings.setValue(QString("foundWordsColor4B"), SVars.foundWordsColor4B.name());
  }

  SVars.foundWordsColor5B.setNamedColor( settings.value(QString("foundWordsColor5B"), "").toString() );
  if (!SVars.foundWordsColor5B.isValid())
  {
    SVars.foundWordsColor5B = QColor(210,210,156); // (#d2d29c)
    settings.setValue(QString("foundWordsColor5B"), SVars.foundWordsColor5B.name());
  }

  SVars.extraSelectColor1B.setNamedColor( settings.value(QString("extraSelectColor1B"), "").toString() );
  if (!SVars.extraSelectColor1B.isValid())
  {
    SVars.extraSelectColor1B = QColor(0,170,170); // (#00aaaa)
    settings.setValue(QString("extraSelectColor1B"), SVars.extraSelectColor1B.name());
  }

  SVars.extraSelectColor2B.setNamedColor( settings.value(QString("extraSelectColor2B"), "").toString() );
  if (!SVars.extraSelectColor2B.isValid())
  {
    SVars.extraSelectColor2B = QColor(255,96,80); // (#ff6050)
    settings.setValue(QString("extraSelectColor2B"), SVars.extraSelectColor2B.name());
  }

  SVars.searchTargetText = settings.value(QString("searchTargetText"), "").toString();
  settings.endGroup();

  // Audio
  settings.beginGroup(QString("Audio"));
  SVars.currentAudioLocation = settings.value(QString("currentAudioLocation"), "").toString();
  settings.endGroup();

  // Other
  settings.beginGroup(QString("Other"));
  SVars.pathToSettings = applicationHomePath; // Тази помощна променлива се инициализира тук, но не се записва в INI файла, а се използва само във формата за настройки, за установяване на промяна.

  SVars.proxyType = (quint8)settings.value(QString("proxyType"), 0).toUInt();
  if (SVars.proxyType != PROXY__NO_PROXY && SVars.proxyType != PROXY__HTTP_PROXY && SVars.proxyType != PROXY__SOCKS_5_PROXY)
  {
    SVars.proxyType = PROXY__NO_PROXY;
    settings.setValue(QString("proxyType"), SVars.proxyType);
  }

  SVars.proxyHostName = settings.value(QString("proxyHostName"), "").toString();
  if (SVars.proxyHostName == "")
  {
    SVars.proxyHostName = QString("");
    settings.setValue(QString("proxyHostName"), SVars.proxyHostName);
  }

  SVars.proxyPort = (quint16)settings.value(QString("proxyPort"), 0).toUInt();

    // Настройка на прокси за цялото приложение:
    QNetworkProxy proxy;
    if (SVars.proxyType == PROXY__NO_PROXY)
      proxy.setType(QNetworkProxy::NoProxy);
    else if (SVars.proxyType == PROXY__HTTP_PROXY)
      proxy.setType(QNetworkProxy::HttpProxy);
    else if (SVars.proxyType == PROXY__SOCKS_5_PROXY)
      proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(SVars.proxyHostName);
    proxy.setPort(SVars.proxyPort);
    proxy.setUser("");
    proxy.setPassword("");
    //QNetworkProxy::setApplicationProxy(proxy); // Ако разкоментирам този ред, проксито не работи.

  SVars.enableTrayIcon = settings.value(QString("enableTrayIcon"), false).toBool(); // For TrayIcon.
  if (QSystemTrayIcon::isSystemTrayAvailable()) // Ако има system tray. // For TrayIcon.
  {
    QApplication::setQuitOnLastWindowClosed(false); // If this property is true, the applications quits when the last visible primary window (i.e. window with no parent) with the Qt::WA_QuitOnClose attribute set is closed
  }
  else // Ако няма system tray.
  {
    SVars.enableTrayIcon = false;
    settings.setValue(QString("enableTrayIcon"), SVars.enableTrayIcon);
  }

  //SVars.MatCrossBibleURL = settings.value(QString("MatCrossBibleURL"), "").toString();
  //if (SVars.MatCrossBibleURL == "")
  //{
    SVars.MatCrossBibleURL = QString("https://www.matcraft.org/MatCrossBible/"); // Да не се изтрива https:// и последната наклонена черта!
  //  settings.setValue(QString("MatCrossBibleURL"), SVars.MatCrossBibleURL);
  //}
  //if (!SVars.MatCrossBibleURL.contains(QString("https://"))) SVars.MatCrossBibleURL = QString("https://%1").arg(SVars.MatCrossBibleURL); // Ако не съдържа https:// го добавя.
  //QUrl mbURL(SVars.MatCrossBibleURL); // Това изчиства линка от https и наклонените черти.
  //SVars.MatCrossBibleURL = QString("https://%1/").arg(mbURL.host()); // Това ги добавя наново. Добавя и последната наклонена черта, което е цялата идея.
  settings.endGroup();
}

void MainObject::saveSVarsSettings()
{
  QSettings settings(iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Global

  // Language
  settings.beginGroup(QString("Language"));
    settings.setValue(QString("currentBooksTranslation"), SVars.currentBooksTranslation);
  settings.endGroup();

  // Colors
  settings.beginGroup(QString("Colors"));
    settings.setValue(QString("dock1TextColorF"), SVars.dock1TextColorF.name());
    settings.setValue(QString("dock1TextColorB"), SVars.dock1TextColorB.name());
    settings.setValue(QString("dock1BGImage"), SVars.dock1BGImage);
    settings.setValue(QString("dock2TextColorF"), SVars.dock2TextColorF.name());
    settings.setValue(QString("dock2TextColorB"), SVars.dock2TextColorB.name());
    settings.setValue(QString("dock2BGImage"), SVars.dock2BGImage);
    settings.setValue(QString("oldTestamentColorF"), SVars.oldTestamentColorF.name());
    settings.setValue(QString("newTestamentColorF"), SVars.newTestamentColorF.name());
    settings.setValue(QString("oldTestamentAlphaF"), SVars.oldTestamentAlphaF);
    settings.setValue(QString("newTestamentAlphaF"), SVars.newTestamentAlphaF);
    settings.setValue(QString("textInBracketsColorF"), SVars.textInBracketsColorF.name());
    settings.setValue(QString("JesusWordsColorF"), SVars.JesusWordsColorF.name());
    settings.setValue(QString("JesusWordsColorFEnable"), SVars.JesusWordsColorFEnable);
    settings.setValue(QString("compareEqColorF"), SVars.compareEqColorF.name());
    settings.setValue(QString("compareNoEqColorF"), SVars.compareNoEqColorF.name());
    settings.setValue(QString("appColorF"), SVars.appColorF.name());
    settings.setValue(QString("appColorB"), SVars.appColorB.isValid() ? SVars.appColorB.name() : "");
    settings.setValue(QString("docks3DTitleBar"), SVars.docks3DTitleBar);
  settings.endGroup();

  // View
  settings.beginGroup(QString("View"));
    settings.setValue(QString("TMenuPosition"), SVars.TMenuPosition);
    settings.setValue(QString("TMenuIconSize"), SVars.TMenuIconSize);
    settings.setValue(QString("otherToolBarFontSize"), SVars.otherToolBarFontSize);
    settings.setValue(QString("booksToolBarPosition"), SVars.booksToolBarPosition);
    settings.setValue(QString("booksToolBarFontSize"), SVars.booksToolBarFontSize);
    settings.setValue(QString("searchToolBarPosition"), SVars.searchToolBarPosition);
    settings.setValue(QString("searchToolBarWidth"), SVars.searchToolBarWidth);
    settings.setValue(QString("searchToolBarFontSize"), SVars.searchToolBarFontSize);
    settings.setValue(QString("projectorToolBarPosition"), SVars.projectorToolBarPosition);
    settings.setValue(QString("projectorToolBarPrevSize"), SVars.projectorToolBarPrevSize);
    settings.setValue(QString("projectorToolBarFontSize"), SVars.projectorToolBarFontSize);
    //settings.setValue(QString("GUIStyle"), SVars.GUIStyle);
  settings.endGroup();
  
  // Text
  settings.beginGroup(QString("Text"));
    settings.setValue(QString("globalFontSize"), SVars.globalFontSize);
    settings.setValue(QString("globalFontAntialias"), SVars.globalFontAntialias);
    settings.setValue(QString("fontFamily"), SVars.fontFamily);
    settings.setValue(QString("fontSize"), SVars.fontSize);
    settings.setValue(QString("verseNumberBold"), SVars.verseNumberBold);
    settings.setValue(QString("verseNumberSup"), SVars.verseNumberSup);
    settings.setValue(QString("verseStruct"), SVars.verseStruct);
    settings.setValue(QString("numeration"), SVars.newNumeration); // Тук не трябва да се записва currentNumeration, защото той не се променя, а newNumeration, който евентуално е бил променен в настройките.
    settings.setValue(QString("booksOrder"), SVars.newBooksOrder); // Тук не трябва да се записва currentBooksOrder, защото той не се променя, а newBooksOrder, който евентуално е бил променен в настройките.
    settings.setValue(QString("showDeutrocanonical"), SVars.newShowDeuterocanonical); // Тук не трябва да се записва showDeuterocanonical, защото той не се променя, а newShowDeuterocanonical, който евентуално е бил променен в настройките.
    settings.setValue(QString("showAbsVerseNumber"), SVars.showAbsVerseNumber);
  settings.endGroup();
  
  // Search
  settings.beginGroup(QString("Search"));
    settings.setValue(QString("foundWordsBold"), SVars.foundWordsBold);
    settings.setValue(QString("foundWordsUnderline"), SVars.foundWordsUnderline);
    settings.setValue(QString("foundWordsColorF"), SVars.foundWordsColorF);
    settings.setValue(QString("foundWordsColorB"), SVars.foundWordsColorB);
    settings.setValue(QString("foundWordsColor1F"), SVars.foundWordsColor1F.name());
    settings.setValue(QString("foundWordsColor2F"), SVars.foundWordsColor2F.name());
    settings.setValue(QString("foundWordsColor3F"), SVars.foundWordsColor3F.name());
    settings.setValue(QString("foundWordsColor4F"), SVars.foundWordsColor4F.name());
    settings.setValue(QString("foundWordsColor5F"), SVars.foundWordsColor5F.name());
    settings.setValue(QString("foundWordsColor1B"), SVars.foundWordsColor1B.name());
    settings.setValue(QString("foundWordsColor2B"), SVars.foundWordsColor2B.name());
    settings.setValue(QString("foundWordsColor3B"), SVars.foundWordsColor3B.name());
    settings.setValue(QString("foundWordsColor4B"), SVars.foundWordsColor4B.name());
    settings.setValue(QString("foundWordsColor5B"), SVars.foundWordsColor5B.name());
    settings.setValue(QString("extraSelectColor1B"), SVars.extraSelectColor1B.name());
    settings.setValue(QString("extraSelectColor2B"), SVars.extraSelectColor2B.name());
  settings.endGroup();

  // Audio
  //settings.beginGroup(QString("Audio"));
  //settings.endGroup();

  // Other
  settings.beginGroup(QString("Other"));
    settings.setValue(QString("proxyType"), SVars.proxyType);
    settings.setValue(QString("proxyHostName"), SVars.proxyHostName);
    settings.setValue(QString("proxyPort"), SVars.proxyPort);
    settings.setValue(QString("enableTrayIcon"), SVars.enableTrayIcon); // For TrayIcon.
  settings.endGroup();
}

bool MainObject::read(QBitArray *activeBibleTexts, quint16 absIndex, QString *bookName, QString *bibleTextsNames, QUInt16List *absIndexesList, TextView *textView)
{
  absIndexesList->clear();
  *bookName = QString("%1 %2").arg(toBookShortName(absIndex)).arg(toChapterCode(absIndex));
  *bibleTextsNames = "";

  if (bibleTextList.size() == 0)
  {
    QString text = "";
    text  = QString("<font color=#ff6050><b>%1</b></font><br><br>").arg(TS->BibleTextsFileProblem1_v1);
    text += QString("<font color=%1>%2<br>%3<br>%4<br></font>").arg(SVars.textInBracketsColorF.name()).arg(TS->BibleTextsFileProblem2_v1).arg(QDir::toNativeSeparators(QString("%1/BibleTexts").arg(applicationDirPath))).arg(TS->BibleTextsFileProblem3_v1);
    textView->tvSetHtml(text);
    return false;
  }

  QList<BIBLE_TEXT*> btList;
  if (TS->globalLayoutDirection == Qt::LeftToRight)
  {
    for (int i = 0; i < bibleTextList.size(); i++)
    {
      if (activeBibleTexts->at(i)) btList << &bibleTextList[i];
    }
  }
  else
  {
    for (int i = (bibleTextList.size()-1); i >= 0; i--)
    {
      if (activeBibleTexts->at(i)) btList << &bibleTextList[i];
    }
  }

  if (btList.size() == 0)
  {
    *bibleTextsNames = QString("• %1").arg(TS->NoOpenText1_v1);
    QString text = "";
    text  = QString("<font color=%1><b>%2</b></font><br><br>").arg(SVars.oldTestamentColorF.name()).arg(TS->NoOpenText2_v1);
    text += QString("<font color=%1>%2</font><br><br><br>").arg(SVars.textInBracketsColorF.name()).arg(TS->NoOpenText3_v1);
    text += QString("<u>%1</u><br><br>").arg(TS->NoOpenText4_v1);
    foreach (BIBLE_TEXT bl, bibleTextList)
    {
      text += QString("● <b>%1</b> -- %2<br>").arg(bl.name).arg(bl.short_description);
    }
    text += QString("</font>");
    textView->tvSetHtml(text);
    return false;
  }

  // Избор на работна номерация.
  // Кодът по-долу е закоментиран, защото дава странични ефекти. Те са причинени от това, че всички методи работят с номерацията
  // избрана от потребителя. Ако тя е например 1 и е показан само един превод, който е по номерация 2, тук ще се избере автоматично
  // да се покаже по номерация 2, но всички помощни методи ще продължат да работят по номерация 1 и става разминаване между желания
  // номер на глава и реално показания. Този ефект се получи след преминаване от кодове към абсолютен индекс.
  quint8 *chaptersExtArr;
  //if (btList.size() == 1) // Ако е само един текст...
  //{
  //  chaptersExtArr = btList[0]->chaptersExtArr; // ...се рабори с неговата номерация.
  //}
  //else // Ако са няколко текста...
  //{
  //  bool equal = true;
  //  for (quint8 i = 1; i < btList.size(); i++) // ...се проверява дали използват еднаква номерация.
  //  {
  //    if (btList[i-1]->chaptersExtArr != btList[i]->chaptersExtArr) equal = false; // Тук се сравняват указателите към масивите.
  //  }
  //
  //  if (equal) // Ако използват еднаква номерация...
  //  {
  //    chaptersExtArr = btList[0]->chaptersExtArr; // ...се работи с нея.
  //  }
  //  else // Ако използват различна номерация...
  //  {
      if (SVars.currentNumeration == NUMERATION__1) // ... се работи с номерацията избрана от потребителя (от настройките).
        chaptersExtArr = chapters66ExtArr;
      else // if (SVars.currentNumeration == NUMERATION__2)
        chaptersExtArr = chapters77ExtArr;
  //  }
  //}

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  foreach (BIBLE_TEXT *bl, btList)
  {
    bl->file->seek(bl->seekBookArr[toBookCode(absIndex)-1]); // Позициониране в началото на книгата.
  }
  qint32 bSeek = -1; // bSeek е номерът на първия стих (ред) от първа глава в избраната книгата.
  qint32 cSeek = -1; // cSeek е номерът на първия стих (ред) от избраната главата в избраната книгата.
  for(qint32 i = bookStartIndexInBooksExtArr[toBookCode(absIndex)-1]; i < MAX_VERSES; i++)
  {
    if (bSeek < 0 && booksExtArr[i] == toBookCode(absIndex)) bSeek = i; // Определяне на bSeek.
    if (bSeek >= 0 && chaptersExtArr[i] == toChapterCode(absIndex))     // Определяне на cSeek.
    {
      cSeek = i;
      break;
    }
  }

  textView->insertTable(2, btList.size());

  QTextCharFormat foCellBG; // Фонов цвят.
  //foCellBG.setBackground(SVars.dock1TextColorB);
  foCellBG.setVerticalAlignment(QTextCharFormat::AlignTop);

  for(quint16 i = 0; i < btList.size(); i++)
  {
    // Първи ред.
    textView->tvInsertHtmlAt(0, i, QString("<span style=\"font-family:%1;\"><b>%2</b></span>").arg(btList[i]->fontFamily).arg(btList[i]->name), foCellBG);

    *bibleTextsNames += QString("• %1 ").arg(btList[i]->name);

    // Втори ред.
    if (absIndex >= NT_START_INDEX)
      textView->tvInsertHtmlAt(1, i, QString("<font color=%1><b>%2 %3</b></font>").arg(SVars.newTestamentColorF.name()).arg(toBookShortName(absIndex)).arg(btList[i]->chaptersExtArr[cSeek]), foCellBG); // Тук се използва chaptersExtArr[cSeek], а не toChapterCode(absIndex), защото при показване на няколко превода в Псалми, може chaptersExtArr[cSeek] да е различно от toChapterCode(absIndex).
    else
      textView->tvInsertHtmlAt(1, i, QString("<font color=%1><b>%2 %3</b></font>").arg(SVars.oldTestamentColorF.name()).arg(toBookShortName(absIndex)).arg(btList[i]->chaptersExtArr[cSeek]), foCellBG); // Тук се използва chaptersExtArr[cSeek], а не toChapterCode(absIndex), защото при показване на няколко превода в Псалми, може chaptersExtArr[cSeek] да е различно от toChapterCode(absIndex).
  }

  QString beforeVNumber = ""; // Тагове преди номера на стиха.
  QString afterVNumber = ""; // Тагове след номера на стиха.
  afterVNumber = "</font>";
  if (absIndex >= NT_START_INDEX)
    beforeVNumber = QString("<font color=%1>").arg(SVars.newTestamentColorF.name());
  else
    beforeVNumber = QString("<font color=%1>").arg(SVars.oldTestamentColorF.name());

  if (SVars.verseNumberBold) // Ако потребителят е избрал удебелен шрифт на номерата на стиховете.
  {
    beforeVNumber = beforeVNumber + "<b>";
    afterVNumber = "</b>" + afterVNumber;
  }
  if (SVars.verseNumberSup) // Ако потребителят е избрал умален (sup) шрифт на номерата на стиховете.
  {
    beforeVNumber = beforeVNumber + "<sup>";
    afterVNumber = "</sup>" + afterVNumber;
  }

  if (SVars.verseStruct == VERSE_STRUCT__MIN_BOOK_NAME) // Ако потребителят е избрал да се показва името на книгата (съкратено) пред всеки стих.
  {
    beforeVNumber = beforeVNumber + QString("%1 %2:").arg(toBookMinName(absIndex)).arg(toChapterCode(absIndex)); // Тук би трябвало да се използва chaptersExtArr[cSeek] вместо toChapterCode(absIndex), но това значи да се правят два различни beforeVNumber и не знам дали си струва...
  }
  else if (SVars.verseStruct == VERSE_STRUCT__SHORT_BOOK_NAME) // Ако потребителят е избрал да се показва името на книгата пред всеки стих.
  {
    beforeVNumber = beforeVNumber + QString("%1 %2:").arg(toBookShortName(absIndex)).arg(toChapterCode(absIndex)); // Тук би трябвало да се използва chaptersExtArr[cSeek] вместо toChapterCode(absIndex), но това значи да се правят два различни beforeVNumber и не знам дали си струва...
  }

  quint8 *autoVerseNumber = new quint8[btList.size()]; // Автоматично изчислен номер на стих (използва се при текстове без собствена номерация). Работи на принципа: всеки открит стих приема пореден номер от текущата глава.
  for(quint16 i = 0; i < btList.size(); i++)
  {
    autoVerseNumber[i] = 0;
  }

  bool hasVerse = false; // Флаг указващ, че на дадения ред има поне един стих.
  QString absVerseNumber = "";

  for(quint16 i = bSeek; i < MAX_VERSES; i++)
  {
    if (booksExtArr[i] > toBookCode(absIndex)) break;
    if (booksExtArr[i] == toBookCode(absIndex) && chaptersExtArr[i] > toChapterCode(absIndex)) break;
    if (chaptersExtArr[i] == toChapterCode(absIndex))
    {
      textView->appendRowsToTable(1); // Добавя един нов ред.
      hasVerse = false;

      absVerseNumber = (SVars.showAbsVerseNumber) ? QString("<font color=%1><sup><b>%2</b></sup></font> ").arg(SVars.textInBracketsColorF.name()).arg(i+1) : ""; // Добавя абсолютния номер на стиха (ако е разрешено от потребителя).

      for(quint16 bl = 0; bl < btList.size(); bl++)
      {
        lineLength = btList[bl]->file->readLine(buf, sizeof(buf));
        if (lineLength != -1)
        {

          // Форматира номера на стиха (цвят, дебелина, размер):
          QString sBuf(buf);
          sBuf = sBuf.trimmed();
          if (sBuf.size() > 0)
          {
            autoVerseNumber[bl]++;
            hasVerse = true; // Ако има стих.
            if (!btList[bl]->nativeVerseNum) sBuf = QString("%1. %2").arg(autoVerseNumber[bl]).arg(sBuf); // Прибавя автоматично изчислен номер.
          }
          int firstDot = sBuf.lastIndexOf(". ", 3);//176.
          if (firstDot > 0)
          {
            sBuf.replace(firstDot, 1, "." + afterVNumber); //sBuf.insert(firstDot++, afterVNumber);
            sBuf = absVerseNumber + beforeVNumber + sBuf;
          }

          // Форматира текста в {} скоби (цвят).
          sBuf.replace(QString("{"), QString("<font color=%1>{").arg(SVars.textInBracketsColorF.name()));
          sBuf.replace(QString("}"), QString("}</font>"));

          // Замества JW (от Jesus Words) таговете (ако има такива) за оцветяване на думите на Исус с валидни Html тагове и цвят, избран от потребителя.
          if (SVars.JesusWordsColorFEnable) // Ако е разрешено от потребителя.
          {
            sBuf.replace(QString("<JW>"), QString("<font color=%1>").arg(SVars.JesusWordsColorF.name()));
            sBuf.replace(QString("</JW>"), QString("</font>"));
          }

          if (chaptersExtArr[i] == btList[bl]->chaptersExtArr[i]) // Ако избраната номерация съвпада с тази на текста.
          {
            sBuf = QString("<a id=\"i%1\"></a><span style=\"font-family:%2;\">%3</span>").arg(i).arg(btList[bl]->fontFamily).arg(sBuf); // В началото на стиха се поставя котва с id = на абсолютния номер на стиха, която се използва за позициониране на текущия стих в рамките на екрана, когато той е извън него..
          }
          else
          {
            sBuf = QString("<a id=\"i%1\"></a><span style=\"font-family:%2;\"><font color=%3>%4</font></span>").arg(i).arg(btList[bl]->fontFamily).arg(SVars.textInBracketsColorF.name()).arg(sBuf);
          }

          textView->tvInsertHtmlAt(textView->versesTable->rows()-1, bl, sBuf, foCellBG);
        }
      }

      if (!hasVerse) // Ако няма нито един стих на този ред.
        textView->removeLastRowsFromTable(1); // Изтрива реда.
      else
        *absIndexesList << i;
    }
    else
    {
      foreach (BIBLE_TEXT *bl, btList)
      {
        bl->file->readLine(buf, sizeof(buf)); // Прочита реда без да го използва.
      }
    }
  }

  return true;
}

bool MainObject::compare(QBitArray *activeBibleTexts, quint16 absIndex, QString *bibleTextsNames, QUInt16List *absIndexesList, TextView *textView)
{
  if (bibleTextList.size() == 0) return false;

  QList<BIBLE_TEXT*> btList;
  if (TS->globalLayoutDirection == Qt::LeftToRight)
  {
    for (int i = 0; i < bibleTextList.size(); i++)
    {
      if (activeBibleTexts->at(i)) btList << &bibleTextList[i];
    }
  }
  else
  {
    for (int i = (bibleTextList.size()-1); i >= 0; i--)
    {
      if (activeBibleTexts->at(i)) btList << &bibleTextList[i];
    }
  }

  if (btList.size() != 2) return false;

  *bibleTextsNames = "";
  absIndexesList->clear();

  // Избор на работна номерация.
  // Кодът по-долу е закоментиран, защото дава странични ефекти. Те са причинени от това, че всички методи работят с номерацията
  // избрана от потребителя. Ако тя е например 1 и е показан само един превод, който е по номерация 2, тук ще се избере автоматично
  // да се покаже по номерация 2, но всички помощни методи ще продължат да работят по номерация 1 и става разминаване между желания
  // номер на глава и реално показания. Този ефект се получи след преминаване от кодове към абсолютен индекс.
  quint8 *chaptersExtArr;
  //bool equal = true;
  //for (quint8 i = 1; i < btList.size(); i++) // Проверява се дали използват еднаква номерация.
  //{
  //  if (btList[i-1]->chaptersExtArr != btList[i]->chaptersExtArr) equal = false; // Тук се сравняват указателите към масивите.
  //}
  //  
  //if (equal) // Ако използват еднаква номерация...
  //{
  //  chaptersExtArr = btList[0]->chaptersExtArr; // ...се работи с нея.
  //}
  //else // Ако използват различна номерация...
  //{
    if (SVars.currentNumeration == NUMERATION__1) // ... се работи с номерацията избрана от потребителя (от настройките).
      chaptersExtArr = chapters66ExtArr;
    else // if (SVars.currentNumeration == NUMERATION__2)
      chaptersExtArr = chapters77ExtArr;
  //}

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  foreach (BIBLE_TEXT *bl, btList)
  {
    bl->file->seek(bl->seekBookArr[toBookCode(absIndex)-1]); // Позициониране в началото на книгата.
  }
  qint32 bSeek = -1; // bSeek е номерът на първия стих (ред) от първа глава в избраната книгата.
  qint32 cSeek = -1; // cSeek е номерът на първия стих (ред) от избраната главата в избраната книгата.
  for(qint32 i = bookStartIndexInBooksExtArr[toBookCode(absIndex)-1]; i < MAX_VERSES; i++)
  {
    if (bSeek < 0 && booksExtArr[i] == toBookCode(absIndex)) bSeek = i; // Определяне на bSeek.
    if (bSeek >= 0 && chaptersExtArr[i] == toChapterCode(absIndex))     // Определяне на cSeek.
    {
      cSeek = i;
      break;
    }
  }

  int stat1Eq = 0;  // Броят на думите в главата на първия текст, които присъстват и във втория.
  int stat1All = 0; // Броят на всички думи в главата на първия текст.
  int stat2Eq = 0;  // Броят на думите в главата на втория текст, които присъстват и в първия.
  int stat2All = 0; // Броят на всички думи в главата на втория текст.

  textView->insertTable(2, btList.size());

  QTextCharFormat foCellBG; // Фонов цвят.
  //foCellBG.setBackground(SVars.dock1TextColorB);
  foCellBG.setVerticalAlignment(QTextCharFormat::AlignTop);

  for(quint16 i = 0; i < btList.size(); i++)
  {
    // Първи ред.
    textView->tvInsertHtmlAt(0, i, QString("<span style=\"font-family:%1;\"><b>%2</b></span>").arg(btList[i]->fontFamily).arg(btList[i]->name), foCellBG);

    *bibleTextsNames += QString("• %1 ").arg(btList[i]->name);

    // Втори ред.
    if (absIndex >= NT_START_INDEX)
      textView->tvInsertHtmlAt(1, i, QString("<font color=%1><b>%2 %3</b></font>").arg(SVars.newTestamentColorF.name()).arg(toBookShortName(absIndex)).arg(btList[i]->chaptersExtArr[cSeek]), foCellBG); // Тук се използва chaptersExtArr[cSeek], а не toChapterCode(absIndex), защото при показване на няколко превода в Псалми, може chaptersExtArr[cSeek] да е различно от toChapterCode(absIndex).
    else
      textView->tvInsertHtmlAt(1, i, QString("<font color=%1><b>%2 %3</b></font>").arg(SVars.oldTestamentColorF.name()).arg(toBookShortName(absIndex)).arg(btList[i]->chaptersExtArr[cSeek]), foCellBG); // Тук се използва chaptersExtArr[cSeek], а не toChapterCode(absIndex), защото при показване на няколко превода в Псалми, може chaptersExtArr[cSeek] да е различно от toChapterCode(absIndex).
  }

  QString beforeVNumber = ""; // Тагове преди номера на стиха.
  QString afterVNumber = ""; // Тагове след номера на стиха.
  afterVNumber = "</font>";
  if (absIndex >= NT_START_INDEX)
    beforeVNumber = QString("<font color=%1>").arg(SVars.newTestamentColorF.name());
  else
    beforeVNumber = QString("<font color=%1>").arg(SVars.oldTestamentColorF.name());

  if (SVars.verseNumberBold) // Ако потребителят е избрал удебелен шрифт на номерата на стиховете.
  {
    beforeVNumber = beforeVNumber + "<b>";
    afterVNumber = "</b>" + afterVNumber;
  }
  if (SVars.verseNumberSup) // Ако потребителят е избрал умален (sup) шрифт на номерата на стиховете.
  {
    beforeVNumber = beforeVNumber + "<sup>";
    afterVNumber = "</sup>" + afterVNumber;
  }

  if (SVars.verseStruct == VERSE_STRUCT__MIN_BOOK_NAME) // Ако потребителят е избрал да се показва името на книгата (съкратено) пред всеки стих.
  {
    beforeVNumber = beforeVNumber + QString("%1 %2:").arg(toBookMinName(absIndex)).arg(toChapterCode(absIndex)); // Тук би трябвало да се използва chaptersExtArr[cSeek] вместо toChapterCode(absIndex), но това значи да се правят два различни beforeVNumber и не знам дали си струва...
  }
  else if (SVars.verseStruct == VERSE_STRUCT__SHORT_BOOK_NAME) // Ако потребителят е избрал да се показва името на книгата пред всеки стих.
  {
    beforeVNumber = beforeVNumber + QString("%1 %2:").arg(toBookShortName(absIndex)).arg(toChapterCode(absIndex)); // Тук би трябвало да се използва chaptersExtArr[cSeek] вместо toChapterCode(absIndex), но това значи да се правят два различни beforeVNumber и не знам дали си струва...
  }

  quint8 *autoVerseNumber = new quint8[btList.size()]; // Автоматично изчислен номер на стих (използва се при текстове без собствена номерация). Работи на принципа: всеки открит стих приема пореден номер от текущата глава.
  for(quint16 i = 0; i < btList.size(); i++)
  {
    autoVerseNumber[i] = 0;
  }

  bool hasVerse = false; // Флаг указващ, че на дадения ред има поне един стих.

  for(quint16 i = bSeek; i < MAX_VERSES; i++)
  {
    if (booksExtArr[i] > toBookCode(absIndex)) break;
    if (booksExtArr[i] == toBookCode(absIndex) && chaptersExtArr[i] > toChapterCode(absIndex)) break;
    if (chaptersExtArr[i] == toChapterCode(absIndex))
    {
      QString v1 = ""; // Съдържат текущия стих от първия текст.
      QString v2 = ""; // Съдържат текущия стих от втория текст.
      QString nv1 = ""; // Съдържат v1 след обработката.
      QString nv2 = ""; // Съдържат v2 след обработката.

      textView->appendRowsToTable(1); // Добавя един нов ред.
      hasVerse = false;

      // Чете стих от първия текст.
      lineLength = btList[0]->file->readLine(buf, sizeof(buf));
      if (lineLength != -1)
      {
        v1 = QString(buf);
      }
      // Чете стих от втория текст.
      lineLength = btList[1]->file->readLine(buf, sizeof(buf));
      if (lineLength != -1)
      {
        v2 = QString(buf);
      }

      removeTags(&v1); // Премахва таговете
      removeTags(&v2); // Премахва таговете

      QStringList words1 = v1.split(QRegExp("\\b")); // Съдържат всички думи и знаци от текущия стих на първия текст.
      QStringList words2 = v2.split(QRegExp("\\b")); // Съдържат всички думи и знаци от текущия стих на втория текст.

      for (int j = 0; j < words1.size(); j++)
      {
        if ( words1[j].split(QRegExp("\\W+"), QString::SkipEmptyParts).size() == 0 ) // Ако е някакъв знак.
        {
          nv1 += words1[j];
        }
        else if ( words1[j].split(QRegExp("\\d+"), QString::SkipEmptyParts).size() == 0 ) // Ако е цифра.
        {
          nv1 += words1[j];
        }
        else // Ако е дума
        {
          stat1All++;
          bool res = false;
          foreach (QString word, words2) // Проверява дали думата от първия стих се съдържа във втория.
          {
            if ( words1[j].toLower() == word.toLower() ) // Ако има съвпадение на думите.
            {
              stat1Eq++;
              res = true;
              break;
            }
          }
          if (res) // Ако думата от първия стих се съдържа във втория.
            nv1 += QString("<font color=%1>%2</font>").arg(SVars.compareEqColorF.name()).arg(words1[j]);
          else // Ако не се съдържа.
            nv1 += QString("<font color=%1>%2</font>").arg(SVars.compareNoEqColorF.name()).arg(words1[j]);
        }
      }

      for (int j = 0; j < words2.size(); j++)
      {
        if ( words2[j].split(QRegExp("\\W+"), QString::SkipEmptyParts).size() == 0 ) // Ако е някакъв знак.
        {
          nv2 += words2[j];
        }
        else if ( words2[j].split(QRegExp("\\d+"), QString::SkipEmptyParts).size() == 0 ) // Ако е цифра.
        {
          nv2 += words2[j];
        }
        else // Ако е дума.
        {
          stat2All++;
          bool res = false;
          foreach (QString word, words1) // Проверява дали думата от втория стих се съдържа в първия.
          {
            if ( words2[j].toLower() == word.toLower() ) // Ако има съвпадение на думите.
            {
              stat2Eq++;
              res = true;
              break;
            }
          }
          if (res) // Ако думата от втория стих се съдържа в първия.
            nv2 += QString("<font color=%1>%2</font>").arg(SVars.compareEqColorF.name()).arg(words2[j]);
          else // Ако не се съдържа.
            nv2 += QString("<font color=%1>%2</font>").arg(SVars.compareNoEqColorF.name()).arg(words2[j]);
        }
      }

      // Форматира номера на стиха (цвят, дебелина, размер).
      nv1 = nv1.trimmed();
      if (nv1.size() > 0)
      {
        autoVerseNumber[0]++;
        hasVerse = true; // Ако има стих.
        if (!btList[0]->nativeVerseNum) nv1 = QString("%1. %2").arg(autoVerseNumber[0]).arg(nv1); // Прибавя автоматично изчислен номер.
      }
      int firstDot = nv1.lastIndexOf(". ", 3);//176.
      if (firstDot >= 0)
      {
        nv1.replace(firstDot, 1, "." + afterVNumber); //nv1.insert(firstDot++, afterVNumber);
        nv1 = beforeVNumber + nv1;
      }
      nv1 = QString("<a id=\"i%1\"></a><span style=\"font-family:%2;\">%3</span>").arg(i).arg(btList[0]->fontFamily).arg(nv1); // В началото на стиха се поставя котва с id = на абсолютния номер на стиха, която се използва за позициониране на текущия стих в рамките на екрана, когато той е извън него..

      // Форматира номера на стиха (цвят, дебелина, размер).
      nv2 = nv2.trimmed();
      if (nv2.size() > 0)
      {
        autoVerseNumber[1]++;
        hasVerse = true; // Ако има стих.
        if (!btList[1]->nativeVerseNum) nv2 = QString("%1. %2").arg(autoVerseNumber[1]).arg(nv2); // Прибавя автоматично изчислен номер.
      }
      firstDot = nv2.lastIndexOf(". ", 3);//176.
      if (firstDot >= 0)
      {
        nv2.replace(firstDot, 1, "." + afterVNumber); //nv2.insert(firstDot++, afterVNumber);
        nv2 = beforeVNumber + nv2;
      }
      nv2 = QString("<a id=\"i%1\"></a><span style=\"font-family:%2;\">%3</span>").arg(i).arg(btList[1]->fontFamily).arg(nv2); // В началото на стиха се поставя котва с id = на абсолютния номер на стиха, която се използва за позициониране на текущия стих в рамките на екрана, когато той е извън него..

      textView->tvInsertHtmlAt(textView->versesTable->rows()-1, 0, nv1, foCellBG);
      textView->tvInsertHtmlAt(textView->versesTable->rows()-1, 1, nv2, foCellBG);
      if (!hasVerse) // Ако няма нито един стих на този ред.
        textView->removeLastRowsFromTable(1); // Изтрива реда.
      else
        *absIndexesList << i;
    }
    else
    {
      foreach (BIBLE_TEXT *bl, btList)
      {
        bl->file->readLine(buf, sizeof(buf));
      }
    }
  }

  // Статистика:
  textView->appendRowsToTable(1); // Добавя един нов ред.
  QString text = "";

  text = QString("<hr><b>%1</b><br>").arg(TS->Statistics_v1);
  text += QString("%1 %2<br>%3 %4<br>").arg(TS->MatchedWords_v1).arg(stat1Eq).arg(TS->AllWords_v1).arg(stat1All);
  if (stat1All == 0) stat1All = 1; // Защита от делене на нула.
  text += QString("%1 <b>%2%</b><hr>").arg(TS->PercentageMatch_v1).arg(100 * stat1Eq / stat1All);
  textView->tvInsertHtmlAt(textView->versesTable->rows()-1, 0, text, foCellBG);
  
  text = QString("<hr><b>%1</b><br>").arg(TS->Statistics_v1);
  text += QString("%1 %2<br>%3 %4<br>").arg(TS->MatchedWords_v1).arg(stat2Eq).arg(TS->AllWords_v1).arg(stat2All);
  if (stat2All == 0) stat2All = 1; // Защита от делене на нула.
  text += QString("%1 <b>%2%</b><hr>").arg(TS->PercentageMatch_v1).arg(100 * stat2Eq / stat2All);
  textView->tvInsertHtmlAt(textView->versesTable->rows()-1, 1, text, foCellBG);

  return true;
}

bool MainObject::searchInVerse(BIBLE_TEXT *targetBibleText, quint8 targetBook, QStringList searchWordsList, SEARCH_OPTIONS sOpt, int *foundVersesCount, quint16 *allVersesInTargetBook, quint32 *foundWordCount, QBitArray *searchImageArray, QString *foundVerses)
{
  // Метод за стандартно търсене в текста на Библията. Търсенето се осъществява във всеки стих от указаната книга.
  quint16  findWordCount = searchWordsList.count();
  quint8   currentChapterCode = 0;
  QString  currentVerse = "";
  *foundVersesCount = 0; // Брой на откритите стихове, съдържащи търсените думи.
  *allVersesInTargetBook = 0; // Общ брой на стиховете, в които се търси (за статистиката).
  QString  uniteSymbol  = ":"; // Това е знакът, който се поставя между препратката и стиха. Ако има номер на стих, този знак е двуеточие. Ако е RightToLeft текст или стиховете нямат собствени номера, знакът е </div><div> - за да изпише препратката и текста на два реда.
  if (targetBibleText->layoutDirection == Qt::RightToLeft || targetBibleText->layoutDirection != TS->globalLayoutDirection || !targetBibleText->nativeVerseNum) // Ако е RightToLeft текст или ако глобалният Layout е различен от този на текста или ако стиховете нямат собствени номера.
    uniteSymbol = "</div><div>";

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  targetBibleText->file->seek(targetBibleText->seekBookArr[targetBook-1]); // Позициониране в началото на тази книга.

  quint16 begin = bookStartIndexInBooksExtArr[targetBook-1]; // Това е позицията в booksExtArr на първия стих от книгата, в която се търси.
  quint16 end = (targetBook < 77) ? bookStartIndexInBooksExtArr[targetBook] : MAX_VERSES; // Това е позицията в booksExtArr на първия стих от следващата книга (в която НЕ се търси).
  if (!SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити, не трябва да се търси в Псалом 151 и Данаил 13 и 14. /////////////////////////////////////////////////////////////////////
  {
    if (targetBook == 19) end = end - 16; // Без Псалом 151 (16 стиха).
    else if (targetBook == 27) end = end - 64 - 43; // Без Данаил 13 и 14 (64 + 43 стиха).
  }
  for(quint16 i = begin; i < end; i++)
  {
    currentChapterCode = targetBibleText->chaptersExtArr[i];
    lineLength = targetBibleText->file->readLine(buf, sizeof(buf));
    if (lineLength != -1)
      currentVerse = QString(buf).trimmed();
    else
      break;

    if (currentVerse.length() > 0) // Ако не е празен ред.
    {
      removeTags(&currentVerse); // Премахва таговете преди да търси в стринга.
      *allVersesInTargetBook = *allVersesInTargetBook + 1; // Общ брой на стиховете, в които се търси (за статистиката).
      int c = 0;
      if (sOpt.searchWordsLogic == SEARCH_WORDS_LOGIC__ALL)
      {
        foreach (QString word, searchWordsList)
        {
          if ( currentVerse.contains(QRegExp(word, sOpt.caseSensitivitySearch)) )
            c++;
          else
            break;
        }
      }
      else //if (sOpt.searchWordsLogic == SEARCH_WORDS_LOGIC__ANY)
      {
        foreach (QString word, searchWordsList)
        {
          if ( currentVerse.contains(QRegExp(word, sOpt.caseSensitivitySearch)) ) // Ако е открита поне една от думите.
          {
            c++;
            break; // Излиза от цикъла, защото няма нужда да проверява другите думи.
          }
        }
        if (c > 0) c = findWordCount; // Това е за да мине през следващата проверка.
      }

      if (c == findWordCount) // Ако стихът съдържа всички търсени думи.
      {
        *foundVersesCount = *foundVersesCount + 1; // Брой на откритите стихове, съдържащи търсените думи.
        c = 0;
        foreach (QString word, searchWordsList)
        {
          foundWordCount[c] += currentVerse.count(QRegExp(word, sOpt.caseSensitivitySearch)); // Брой срещания на отделните търсени думи, само в откритите стихове.
          c++;
        }

        *foundVerses += QString("<p style=\"font-family:%1;\"><div><a style=\"color:%2;\" href=\"%3\"><b>%4 %5</b></a>%6%7</div></p>").arg(targetBibleText->fontFamily).arg(SVars.dock2TextColorF.name()).arg(i).arg(bookShortNameArr[targetBook-1]).arg(currentChapterCode).arg(uniteSymbol).arg(QString(buf));
        searchImageArray->setBit(i, true);
      }
    }
  }

  if (*foundVersesCount > 0) *foundVerses += "<hr>";

  return true;
}

bool MainObject::searchInChapter(BIBLE_TEXT *targetBibleText, quint8 targetBook, QStringList searchWordsList, SEARCH_OPTIONS sOpt, int *foundChaptersCount, quint16 *allChaptersInTargetBook, quint32 *foundWordCount, QBitArray *searchImageArray, QString *foundChapters)
{
  // Метод за нестандартно търсене в текста на Библията. Търсенето се осъществява в отделна глава.
  // Този метод е почти същият като горния (търсене в стих), но с някои различия, поради които е по-удачно
  // да се напише отделен метод, отколкото да се преправи горният, чрез въвеждане на един куп допълнителни проверки,
  // с което да се забави самото търсене.
  quint16  findWordCount = searchWordsList.count();
  quint8   currentChapterCode = 0;
  QString  currentVerse = "";
  QString  currentBigVerse = ""; // Този стринг ще съдържа всички стихове от една глава, като търсенето ще бъде направено в него.
  quint8   versesCount = 0; // Брой на стиховете в текущата глава.
  *foundChaptersCount = 0; // Брой на откритите глави, съдържащи търсените думи.
  *allChaptersInTargetBook = 0; // Общ брой на главите, в които се търси (за статистиката).

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  targetBibleText->file->seek(targetBibleText->seekBookArr[targetBook-1]); // Позициониране в началото на тази книга.

  // Този вид търсене (търсене в глава) е същият като търсене в стих, само че тук една цяла глава се разглежда като един
  // голям стих. Затова първо всички стихове от една глава се обединяват в един "голям" стих (currentBigVerse) и после
  // се търси по познатия начин в този голям стих.
  quint16 begin = bookStartIndexInBooksExtArr[targetBook-1]; // Това е позицията в booksExtArr на първия стих от книгата, в която се търси.
  quint16 end = (targetBook < 77) ? bookStartIndexInBooksExtArr[targetBook] : MAX_VERSES; // Това е позицията в booksExtArr на първия стих от следващата книга (в която НЕ се търси).
  if (!SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити, не трябва да се търси в Псалом 151 и Данаил 13 и 14. /////////////////////////////////////////////////////////////////////
  {
    if (targetBook == 19) end = end - 16; // Без Псалом 151 (16 стиха).
    else if (targetBook == 27) end = end - 64 - 43; // Без Данаил 13 и 14 (64 + 43 стиха).
  }
  for(quint16 i = begin; i < end; i += versesCount) // Увеличава брояча с versesCount за да може при следващото завъртане на цикъла, да се започне не от следващия стих, а от следващата глава.
  {
    currentChapterCode = targetBibleText->chaptersExtArr[i];

    // Преброява колко стиха има в текущата глава:
    versesCount = 0;
    for(quint16 j = i; j < MAX_VERSES; j++)
    {
      if (targetBook == (booksExtArr[j]) && currentChapterCode == targetBibleText->chaptersExtArr[j]) // Ако стиха е от същата глава.
        versesCount++;
    }

    // Обединява всички стихове от текущата глава в един "голям" стих, в който ще се търси:
    currentBigVerse = ""; // Нулира големия стих.
    for(quint8 j = 0; j < versesCount; j++)
    {
      lineLength = targetBibleText->file->readLine(buf, sizeof(buf));
      if (lineLength != -1)
      {
        currentVerse = QString(buf);
        removeTags(&currentVerse); // Премахва таговете.
      }
      else
      {
        break; // Ако е достигнат край на файла.
      }

      currentBigVerse += QString(" %1").arg(currentVerse); // Добавя текущия стих към "големия".
    }
    currentBigVerse = currentBigVerse.trimmed().toUpper(); // Премахва '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.

    // Осъщесвяване на самото търсене в големия стих:
    if (!currentBigVerse.isEmpty()) // Ако не е празна глава.
    {
      *allChaptersInTargetBook = *allChaptersInTargetBook + 1; // Общ брой на главите, в които се търси (за статистиката).
      int c = 0;
      if (sOpt.searchWordsLogic == SEARCH_WORDS_LOGIC__ALL)
      {
        foreach (QString word, searchWordsList)
        {
          if ( currentBigVerse.contains(QRegExp(word, sOpt.caseSensitivitySearch)) )
            c++;
          else
            break;
        }
      }
      else //if (sOpt.searchWordsLogic == SEARCH_WORDS_LOGIC__ANY)
      {
        foreach (QString word, searchWordsList)
        {
          if ( currentBigVerse.contains(QRegExp(word, sOpt.caseSensitivitySearch)) ) // Ако е открита поне една от думите.
          {
            c++;
            break; // Излиза от цикъла, защото няма нужда да проверява другите думи.
          }
        }
        if (c > 0) c = findWordCount; // Това е за да мине през следващата проверка.
      }

      if (c == findWordCount) // Ако стихът съдържа всички търсени думи.
      {
        *foundChaptersCount = *foundChaptersCount + 1; // Брой на откритите глави, съдържащи търсените думи.
        c = 0;
        foreach (QString word, searchWordsList)
        {
          foundWordCount[c] += currentBigVerse.count(QRegExp(word, sOpt.caseSensitivitySearch)); // Брой срещания на отделните търсени думи, само в откритите глави.
          c++;
        }

        *foundChapters += QString("<p><a style=\"color:%1;\" href=\"%2\"><b>%3 %4</b></a></p>").arg(SVars.dock2TextColorF.name()).arg(i).arg(bookShortNameArr[targetBook-1]).arg(currentChapterCode);
        for(quint8 j = 0; j < versesCount; j++)
        {
          searchImageArray->setBit(i+j, true);
        }
      }
    }
  }

  if (*foundChaptersCount > 0) *foundChapters += "<hr>";

  return true;
}

QString MainObject::getUniqueWords(QBitArray *activeBibleTexts, quint16 absIndex, bool currentOT, bool currentNT, bool currentBook, bool currentChapter, bool alphabeticallyOrder)
{
  if (bibleTextList.size() == 0) return "";

  BIBLE_TEXT *bibleText = 0;
  for (int i = 0; i < bibleTextList.size(); i++)
  {
    if (activeBibleTexts->at(i))
    {
      bibleText = &bibleTextList[i];
      break;
    }
  }
  if (bibleText == 0) return "";
  
  QString bookName = "";
  quint16 begin = 0;
  quint16 end = 0;

  if (currentOT && currentNT)
  {
    bookName = TS->AllBooks_v1;
    //absIndex = OT_START_INDEX;
    begin = OT_START_INDEX;
    end = MAX_VERSES;
  }
  else if (currentOT)
  {
    bookName = TS->TheOldTestament_v1;
    //absIndex = OT_START_INDEX;
    begin = OT_START_INDEX;
    end = NT_START_INDEX;
  }
  else if (currentNT)
  {
    bookName = TS->TheNewTestament_v1;
    //absIndex = NT_START_INDEX;
    begin = NT_START_INDEX;
    end = MAX_VERSES;
  }
  else if (currentBook)
  {
    bookName = toBookShortName(absIndex);
    begin = bookStartIndexInBooksExtArr[toBookCode(absIndex)-1]; // Това е позицията в booksExtArr на първия стих, от желаната книга.
    end = (toBookCode(absIndex) < 77) ? bookStartIndexInBooksExtArr[toBookCode(absIndex)] : MAX_VERSES; // Това е позицията в booksExtArr на първия стих, от следващата книга (която не ни интересува).
  }
  else if (currentChapter)
  {
    bookName = QString("%1 %2").arg(toBookShortName(absIndex)).arg(toChapterCode(absIndex));
    begin = bookStartIndexInBooksExtArr[toBookCode(absIndex)-1]; // Това е позицията в booksExtArr на първия стих, от желаната книга.
    end = MAX_VERSES; // Сочи към края на Библията. Това е нужно, в случай, че не мине през долния цикъл.
    // Сега се търси конкретна глава от книгата.
    for(quint16 i = begin; i < MAX_VERSES; i++)
    {
      if (booksExtArr[i] == toBookCode(absIndex) && bibleText->chaptersExtArr[i] == toChapterCode(absIndex)) // Ако е желаната книга, и е началото на желаната глава.
      {
        begin = i;
        break;
      }
    }
    for(quint16 i = begin; i < MAX_VERSES; i++)
    {
      if ( (booksExtArr[i] > toBookCode(absIndex)) || (booksExtArr[i] == toBookCode(absIndex) && bibleText->chaptersExtArr[i] > toChapterCode(absIndex)) ) // Ако преминато в следващата книга или ако е желаната книга, но е преминато към главата след желаната.
      {
        end = i; // Ако не мине от тук (защото е достигнат край на текста) ще си остане инициализирано с MAX_VERSES.
        break;
      }
    }
  }
  
  int allWords = 0;
  int uniqueWords = 0;
  int hapaxLegomenon = 0;
  char buf[BUF_LEN];
  qint64 lineLength = 0;
  QStringList words;
  QString word;
  int count = 0;
  QMap<QString, int> map;

  bibleText->file->seek(0); // Позиционира в началото на файла. Това е важно!
  for(quint16 i = 0; i < MAX_VERSES; i++)
  {
    if (i >= end) break;
    lineLength = bibleText->file->readLine(buf, sizeof(buf));
    if (lineLength != -1 && i >= begin)
    {
      QString sBuf(buf);
      sBuf = sBuf.trimmed();
      removeTags(&sBuf); // Премахва таговете преди да вземе думите.
      words = sBuf.split(QRegExp("[\\W+\\d+]"), QString::SkipEmptyParts); // За разделител се приемат всички символи различни от букви (\W+) и цифри (\d+).
      for (int n = 0; n < words.size(); n++)
      {
        word = words[n].toLower();
        count = map.value(word, 0) + 1; // Ако няма такава дума в речника ще върне стойност по подразбиране 0;
        map.insert(word, count);
        allWords++;
      }
    }
  }
  
  uniqueWords = map.count();
  
  QStringList wordList; // Съдържа всички думи.
  QList<int> countList; // Съдържа броя на всяка дума.
  if (alphabeticallyOrder) // Ако трябва да са подредени в азбучен ред.
  {
    // Те по принцип са си подредени в азбучен ред в map-а, затова тук не прави нищо - само копира данните от map-а в двата масива.
    // Знам, че е тъпо и яде памет, но логиката се опростява, а това действие не отнема абсолютно никакво време.
    int i = 0;
    QMapIterator<QString, int> iterator(map);
    while (iterator.hasNext())
    {
      iterator.next();

      wordList << iterator.key();
      countList << iterator.value();
      i++;	  
    }
  }
  else // Ако трябва да са подредени по брой на срещанията и в същото време по азбучен ред.
  {
    // Тук работата е по-сложна и правя разни врътки за да сортирам масивите. Но и тук това действие не отнема никакво време.
    QMap<QString, QString> mapH; // Тук key ще бъде един сложен стринг, а value ще е това, което е key в map.
    QString key;
    
    QMapIterator<QString, int> iterator(map);
    while (iterator.hasNext())
    {
      iterator.next();

      key = QString("%1_%2").arg(90000 - iterator.value()).arg(iterator.key()); // Колкото по-голямо е числото value, толкова по-малка ще е получената разлика, и така mapH ще е сортиран по азбучен ред, като в него участва и броят на думите.
      mapH.insert(key, iterator.key());
    }

    int i = 0;
    QMapIterator<QString, QString> iteratorH(mapH);
    while (iteratorH.hasNext())
    {
      iteratorH.next();

      wordList << iteratorH.value();
      countList << map.value(iteratorH.value(), 0);
      i++;	  
    }
  }

  // Това показва думите без таблица и не изглежда много добре, но е много по-бързо.
  QString wordAll = "";
  QString wordOne = "";
  for (int i = 0; i < uniqueWords; i++)
  {
    wordAll += QString("%1  <font color=%2>(%3)</font><br>").arg(wordList[i]).arg(SVars.textInBracketsColorF.name()).arg(countList[i]);
  
    if (countList[i] == 1)
    {
      hapaxLegomenon++;
      wordOne += QString("%1<br>").arg(wordList[i]);
    }
  }

  QString text = QString("<font color=%1><b>%2<br>%3</b></font><br><br>%4<br><br>").arg(SVars.oldTestamentColorF.name()).arg(bibleText->name).arg(bookName).arg(alphabeticallyOrder ? TS->SortByAlphabeticalOrder_v1 : TS->SortByOccurrenceOrder_v1);
  text += QString("<b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->AllWords_v1).arg(SVars.newTestamentColorF.name()).arg(allWords);
  text += QString("<b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->UniqueWordsOnly_v1).arg(SVars.newTestamentColorF.name()).arg(uniqueWords);
  text += wordAll;
  text += QString("<br><b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->HapaxLegomenon_v1).arg(SVars.newTestamentColorF.name()).arg(hapaxLegomenon);
  text += QString("<font color=%1>%2</font>").arg(SVars.JesusWordsColorF.name()).arg(wordOne); // Показва ги в друг цвят, за да се открояват при скролване, иначе потребителят може да не забележи, че ги има отделно от другите думи.
  return text;

  // Това показва думите в таблица и изглежда по-добре, но е много по-бавно.
  //QString wordAll = "";
  //QString wordOne = "";
  //for (int i = 0; i < uniqueWords; i++)
  //{
  //  wordAll += QString("%1  <font color=%2>(%3)</font><br>").arg(wordList[i]).arg(SVars.textInBracketsColorF.name()).arg(countList[i]);
  //  if (countList[i] == 1)
  //  {
  //    hapaxLegomenon++;
  //    wordOne += QString("%1<br>").arg(wordList[i]);
  //  }
  //}
  //
  //QString colUniqueWords = QString("<b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->UniqueWordsOnly_v1).arg(SVars.newTestamentColorF.name()).arg(uniqueWords);
  //QString colHapaxLegomenon = QString("<b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->HapaxLegomenon_v1).arg(SVars.newTestamentColorF.name()).arg(hapaxLegomenon);
  //
  //QString text = QString("<font color=%1><b>%2<br>%3</b></font><br><br>%4<br><br>").arg(SVars.oldTestamentColorF.name()).arg(bibleText->name).arg(bookName).arg(alphabeticallyOrder ? TS->SortByAlphabeticalOrder_v1 : TS->SortByOccurrenceOrder_v1);
  //text += QString("<b>%1</b><br><font color=%2><b>%3</b></font><br><br>").arg(TS->AllWords_v1).arg(SVars.newTestamentColorF.name()).arg(allWords);
  //text += QString("<table %1 border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n").arg((bibleText->layoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  //text += QString("<tr><td width=\"30%\">%1</td><td>%2</td></tr>\n").arg(colUniqueWords).arg(colHapaxLegomenon);
  //text += QString("<tr><td>%1</td><td>%2</td></tr>\n").arg(wordAll).arg(wordOne);
  //text += QString("</table>\n");
  //return text;
}

void MainObject::createHTML_MatCrossBible_File_V1(BIBLE_TEXT *targetBibleText, quint8 bookCode, quint8 chapterCode)
{
  QString text = "";
  QString bookName = QString("%1 %2").arg(bookNameArr[(bookCode-1)]).arg(chapterCode);

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  targetBibleText->file->seek(targetBibleText->seekBookArr[(bookCode-1)]); // Позициониране в началото на книгата.
  qint32 bSeek = -1; // bSeek е номерът на първия стих (ред) от първа глава в избраната книгата.
  for(qint32 i = 0; i < MAX_VERSES; i++)
  {
    if (bSeek < 0 && booksExtArr[i] == bookCode)
    {
      bSeek = i; // Определяне на bSeek.
      break;
    }
  }

  QString beforeVNumber = ""; // Тагове преди номера на стиха.
  QString afterVNumber = ""; // Тагове след номера на стиха.
  if (bookCode > 50)
    beforeVNumber = QString("<span class=\"colorred\"><b>");
  else
    beforeVNumber = QString("<span class=\"colorblue\"><b>");
  afterVNumber = "</b></span>";

  bool hasVerse = false; // Флаг, указващ, че на дадения ред има поне един стих.

//  allText += QString("<p %1>\n").arg((targetBibleText->layoutDirection == Qt::LeftToRight) ? "dir=\"LTR\" align=\"left\"" : "dir=\"RTL\"");
  text += QString("<table %1 border=\"0\" width=\"100%\" cellspacing=\"0\" cellpadding=\"0\">\n").arg((targetBibleText->layoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  text += QString("  <tr><td onclick=\"select_row(0)\" class=\"row\"><b>%1</b></td></tr>\n").arg(targetBibleText->name.trimmed());
  if (bookCode > 50)
    text += QString("  <tr><td onclick=\"select_row(0)\" class=\"row\"><span class=\"colorred\"><b>%1</b></span></td></tr>\n").arg(bookName.trimmed());
  else
    text += QString("  <tr><td onclick=\"select_row(0)\" class=\"row\"><span class=\"colorblue\"><b>%1</b></span></td></tr>\n").arg(bookName.trimmed());

  int row = 0;
  for(quint16 i = bSeek; i < MAX_VERSES; i++)
  {
    if (booksExtArr[i] != bookCode) break;
    if (targetBibleText->chaptersExtArr[i] == chapterCode)
    {
      hasVerse = false;
      lineLength = targetBibleText->file->readLine(buf, sizeof(buf));
      if (lineLength != -1)
      {
        // Форматира номера на стиха.
        QString sBuf(buf);
        sBuf = sBuf.trimmed();
        int firstDot = sBuf.lastIndexOf(". ", 3);//176.
        if (firstDot >= 0)
        {
          sBuf.replace(firstDot, 1, "." + afterVNumber); //sBuf.insert(firstDot++, afterVNumber);
          sBuf = beforeVNumber + sBuf;
        }
        if (sBuf.size() > 3) hasVerse = true; // Ако има стих.

        // Форматира текста в {} скоби (цвят).
        sBuf.replace(QString("{"), QString("<font color=%1>{").arg(SVars.textInBracketsColorF.name()));
        sBuf.replace(QString("}"), QString("}</font>"));

        // Замества JW (от Jesus Words) таговете (ако има такива) за оцветяване на думите на Исус с валидни Html тагове и цвят избран от потребителя.
        sBuf.replace(QString("<JW>"), QString("<font color=%1>").arg(SVars.JesusWordsColorF.name()));
        sBuf.replace(QString("</JW>"), QString("</font>"));

        if (hasVerse) text += QString("  <tr><td id=\"r%1\" onclick=\"select_row(%1)\" class=\"row\">%2</td></tr>\n").arg(++row).arg(sBuf);
      }
    }
    else
    {
      targetBibleText->file->readLine(buf, sizeof(buf)); // Прочита реда без да го използва.
    }
  }
  text += QString("</table>\n");
  text += QString("<script language=\"JavaScript\" type='text/javascript'>\n");
  text += QString("  select_row(1);\n"); // Селектира първия ред.
  text += QString("</script>\n");

  QColor oldTestamentColorB = mergeColors(SVars.dock1TextColorB, getTransparentColor(SVars.oldTestamentColorF, SVars.oldTestamentAlphaF));
  QColor newTestamentColorB = mergeColors(SVars.dock1TextColorB, getTransparentColor(SVars.newTestamentColorF, SVars.newTestamentAlphaF));

  QString allText = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">\n");
  allText += QString("<html>\n");
  allText += QString("<head>\n");
  allText += QString("  <meta name=\"qrichtext\" content=\"1\" />\n");
  allText += QString("  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n");
  allText += QString("  <title>%1 - MatCrossBible.HTML</title>\n").arg(bookName);
  allText += QString("\n");
  allText += QString("  <script language=\"JavaScript\" type=\"text/javascript\">\n");
  allText += QString("  var currentRow = 1;\n"); // Щом е щракнато върху ред, значи със сигурност има поне един ред, затова тази инициализация е 1.
  allText += QString("  function select_row(row) {\n");
  allText += QString("    document.getElementById(\"r\" + currentRow).style.backgroundColor = 'rgba(0,0,0,0)';\n"); // Изтрива фона и очертанията на стария, селектиран ред (с прозрачно).
  allText += QString("    document.getElementById(\"r\" + currentRow).style.borderColor = 'rgba(0,0,0,0)';\n");     //
  allText += QString("    if (row != 0) {\n");
  allText += QString("      currentRow = row;\n");
  allText += QString("      document.getElementById(\"r\" + row).style.backgroundColor = '%1';\n").arg((bookCode > 50) ? newTestamentColorB.name() : oldTestamentColorB.name());         // Задава фона и очертанията на новия селектиран ред.
  allText += QString("      document.getElementById(\"r\" + row).style.borderColor = '%1';\n").arg((bookCode > 50) ? SVars.newTestamentColorF.name() : SVars.oldTestamentColorF.name()); //
  allText += QString("    }\n");
  allText += QString("    document.activeElement.blur();\n"); // Премахва фокуса от клетката, върху която е щракнато. Някои браузъри осветяват елемента, който е на фокус и в този случай става грозно.
  allText += QString("  }\n");
  allText += QString("  </script>\n");
  allText += QString("\n");
  allText += QString("  <style type=text/css>\n");
  allText += QString("    body{color:%1; background-color:%2; font-family:%3,Arial,Verdana,DejaVu Sans,Liberation Sans; margin:1px;}\n").arg(SVars.dock1TextColorF.name()).arg(SVars.dock1TextColorB.name()).arg(targetBibleText->fontFamily);
  allText += QString("\n");
  allText += QString("    a.arrow:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.JesusWordsColorF.name());
  allText += QString("    a.arrow:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.JesusWordsColorF.name());
  allText += QString("    a.newt:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.newt:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldt:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldt:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldd:link {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldd:visited {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(SVars.dock1TextColorB.name());
  allText += QString("\n");
  allText += QString("    .row{ border-style: solid; border-width:1px; border-color: rgba(0,0,0,0); padding-left: 2px; padding-top: 0px;  padding-right: 2px;  padding-bottom: 0px; }\n");
  allText += QString("\n");
  allText += QString("    .colorred{color:%1;}\n").arg(SVars.newTestamentColorF.name());
  allText += QString("    .colorblue{color:%1;}\n").arg(SVars.oldTestamentColorF.name());
  allText += QString("\n");
  allText += QString("    .colorbgred{color:%1; background-color:%2;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.newTestamentColorF.name());
  allText += QString("    .colorbgblue{color:%1; background-color:%2;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.oldTestamentColorF.name());
  allText += QString("  </style>\n");
  allText += QString("</head>\n");
  allText += QString("\n");
  allText += QString("<body>\n");

  QString nav = QString("<p %1 align=\"center\"><big>").arg((TS->globalLayoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");

  if (bookCode == 1)
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a>&nbsp; &nbsp;").arg("77").arg(bookFileNameArr[77-1]).arg(bookFileNameArr[77-1]).arg("01");
  else if (bookCode == 51 && !SVars.showDeuterocanonical) // Ако трябва да се скрият второканоничните книги.
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a>&nbsp; &nbsp;").arg("39").arg(bookFileNameArr[39-1]).arg(bookFileNameArr[39-1]).arg("01");
  else
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a>&nbsp; &nbsp;").arg(bookCode-1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)-1]).arg(bookFileNameArr[(bookCode-1)-1]).arg("01");

  if (chapterCode == 1)
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&lt;&nbsp;&nbsp;</b></a>&nbsp; &nbsp;").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  else
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&lt;&nbsp;&nbsp;</b></a>&nbsp; &nbsp;").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode-1, 2, 10, QLatin1Char('0'));

  if (chapterCode == chaptersCountArr[(bookCode-1)])
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&gt;&nbsp;&nbsp;</b></a>&nbsp; &nbsp;").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  else
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&gt;&nbsp;&nbsp;</b></a>&nbsp; &nbsp;").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode+1, 2, 10, QLatin1Char('0'));

  if (bookCode == 77)
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a>").arg("01").arg(bookFileNameArr[1-1]).arg(bookFileNameArr[1-1]).arg("01");
  else if (bookCode == 39 && !SVars.showDeuterocanonical) // Ако трябва да се скрият второканоничните книги.
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a>").arg("51").arg(bookFileNameArr[51-1]).arg(bookFileNameArr[51-1]).arg("01");
  else
    nav += QString("<a class=\"arrow\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a>").arg(bookCode+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)+1]).arg(bookFileNameArr[(bookCode-1)+1]).arg("01");

  nav += QString("</big></p>\n");

  allText += nav;
  allText += text;
  allText += nav;

  allText += QString("<p %1 align=\"center\"><big>").arg((TS->globalLayoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  for (int i = 0; i < chaptersCountArr[(bookCode-1)]; i ++)
  {
    if (i == (chapterCode-1))
    {
      if (bookCode > 50)
      {
        allText += QString("<span class=\"colorbgred\"><b>&nbsp;%1&nbsp;</b></span> ").arg(i+1, 2, 10, QLatin1Char('0'));
      }
      else
      {
        allText += QString("<span class=\"colorbgblue\"><b>&nbsp;%1&nbsp;</b></span> ").arg(i+1, 2, 10, QLatin1Char('0'));
      }
    }
    else
    {
      if (bookCode > 50)
      {
        allText += QString("<a class=\"newt\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a> ").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(i+1, 2, 10, QLatin1Char('0')).arg(i+1, 2, 10, QLatin1Char('0'));
      }
      else
      {
        allText += QString("<a class=\"oldt\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a> ").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(i+1, 2, 10, QLatin1Char('0')).arg(i+1, 2, 10, QLatin1Char('0'));
      }
    }
  }
  allText += QString("</big></p>\n");

  allText += QString("<p align=\"center\">\n<big>\n");
  for (int i = 0; i < 77; i ++)
  {
    if (i == (bookCode-1))
    {
      if (i < 50)
      {
        allText += QString("<span class=\"colorbgblue\"><b>&nbsp;%1&nbsp;</b></span><br />\n").arg(bookShortNameArr[i]);
      }
      else
      {
        allText += QString("<span class=\"colorbgred\"><b>&nbsp;%1&nbsp;</b></span><br />\n").arg(bookShortNameArr[i]);
      }
    }
    else
    {
      if (i < 50)
      {
        if (i > 38)
        {
          if (SVars.showDeuterocanonical) allText += QString("<a class=\"oldd\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
        }
        else
        {
          allText += QString("<a class=\"oldt\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
        }
      }
      else
      {
        allText += QString("<a class=\"newt\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
      }
    }

    if (i == 4 || i == 17 || i == 21 || i == 38 || i == 49 || i == 54 || i == ((SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) ? 68 : 61) || i == 75)
    {
      allText += QString("<br />\n");
    }
  }
  allText += QString("</big>\n</p>\n");

  allText += QString("<p align=\"center\" style=\"color:%1;\"><small>").arg(SVars.oldTestamentColorF.name());
  allText += QString("  <b>• MatCrossBible.HTML •</b><br />\n");
  allText += QString("  <a class=\"colorblue\" href=\"https://www.matcraft.org/\">https://www.matcraft.org/</a>\n");
  allText += QString("</small></p>\n\n");s

  allText += QString("</body>\n</html>\n");

  QString fileName = QString("%1/MatCrossBible.HTML/%2/%3_%4/%5_%6.htm").arg(QCoreApplication::applicationDirPath()).arg(targetBibleText->name.trimmed()).arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  QFile *htmlFile = new QFile(fileName);
  if (htmlFile->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text, записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(htmlFile);
    out << allText;
  }
  htmlFile->close();
  delete htmlFile;
}

void MainObject::createHTML_MatCrossBible_File_V2(BIBLE_TEXT *targetBibleText, quint8 bookCode, quint8 chapterCode)
{
  QString text = "";
  QString bookName = QString("%1 %2").arg(bookNameArr[(bookCode-1)]).arg(chapterCode);

  char buf[BUF_LEN];
  qint64 lineLength = 0;
  targetBibleText->file->seek(targetBibleText->seekBookArr[(bookCode-1)]); // Позициониране в началото на книгата.
  qint32 bSeek = -1; // bSeek е номерът на първия стих (ред) от първа глава в избраната книгата.
  for(qint32 i = 0; i < MAX_VERSES; i++)
  {
    if (bSeek < 0 && booksExtArr[i] == bookCode)
    {
      bSeek = i; // Определяне на bSeek.
      break;
    }
  }

  QString beforeVNumber = ""; // Тагове преди номера на стиха.
  QString afterVNumber = ""; // Тагове след номера на стиха.
  if (bookCode > 50)
    beforeVNumber = QString("<span class=\"color_r1\"><b>");
  else
    beforeVNumber = QString("<span class=\"color_b1\"><b>");
  afterVNumber = "</b></span>";

  bool hasVerse = false; // Флаг указващ, че на дадения ред има поне един стих.

  text += QString("      <table %1 border=\"0\" width=\"100%\" cellspacing=\"0\" cellpadding=\"0\">\n").arg((targetBibleText->layoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  text += QString("        <tr><td onclick=\"select_row(0)\" class=\"row\"><b>%1</b></td></tr>\n").arg(targetBibleText->name.trimmed());
  if (bookCode > 50)
    text += QString("        <tr><td onclick=\"select_row(0)\" class=\"row\"><span class=\"color_r1\"><b>%1</b></span></td></tr>\n").arg(bookName.trimmed());
  else
    text += QString("        <tr><td onclick=\"select_row(0)\" class=\"row\"><span class=\"color_b1\"><b>%1</b></span></td></tr>\n").arg(bookName.trimmed());

  int row = 0;
  for(quint16 i = bSeek; i < MAX_VERSES; i++)
  {
    if (booksExtArr[i] != bookCode) break;
    if (targetBibleText->chaptersExtArr[i] == chapterCode)
    {
      hasVerse = false;
      lineLength = targetBibleText->file->readLine(buf, sizeof(buf));
      if (lineLength != -1)
      {
        // Форматира номера на стиха.
        QString sBuf(buf);
        sBuf = sBuf.trimmed();
        int firstDot = sBuf.lastIndexOf(". ", 3);//176.
        if (firstDot >= 0)
        {
          sBuf.replace(firstDot, 1, "." + afterVNumber); //sBuf.insert(firstDot++, afterVNumber);
          sBuf = beforeVNumber + sBuf;
        }
        if (sBuf.size() > 3) hasVerse = true; // Ако има стих.

        // Форматира текста в {} скоби (цвят).
        sBuf.replace(QString("{"), QString("<font color=%1>{").arg(SVars.textInBracketsColorF.name()));
        sBuf.replace(QString("}"), QString("}</font>"));

        // Замества JW (от Jesus Words) таговете (ако има такива) за оцветяване на думите на Исус с валидни Html тагове и цвят избран от потребителя.
        sBuf.replace(QString("<JW>"), QString("<font color=%1>").arg(SVars.JesusWordsColorF.name()));
        sBuf.replace(QString("</JW>"), QString("</font>"));

        if (hasVerse) text += QString("        <tr><td id=\"r%1\" onclick=\"select_row(%1)\" class=\"row\">%2</td></tr>\n").arg(++row).arg(sBuf);
      }
    }
    else
    {
      targetBibleText->file->readLine(buf, sizeof(buf)); // Прочита реда без да го използва.
    }
  }
  text += QString("      </table>\n");
  text += QString("      <script language=\"JavaScript\" type='text/javascript'>\n");
  text += QString("        select_row(1);\n"); // Селектира първия ред.
  text += QString("      </script>\n");

  QColor oldTestamentColorB1 = mergeColors(SVars.dock1TextColorB, getTransparentColor(SVars.oldTestamentColorF, SVars.oldTestamentAlphaF));
  QColor newTestamentColorB1 = mergeColors(SVars.dock1TextColorB, getTransparentColor(SVars.newTestamentColorF, SVars.newTestamentAlphaF));
  QColor oldTestamentColorB2 = mergeColors(SVars.dock2TextColorB, getTransparentColor(SVars.oldTestamentColorF, SVars.oldTestamentAlphaF));
  QColor newTestamentColorB2 = mergeColors(SVars.dock2TextColorB, getTransparentColor(SVars.newTestamentColorF, SVars.newTestamentAlphaF));

  QString allText = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">\n");
  allText += QString("<html>\n");
  allText += QString("<head>\n");
  allText += QString("  <meta name=\"qrichtext\" content=\"1\" />\n");
  allText += QString("  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n");
  allText += QString("  <title>%1 - MatCrossBible.HTML</title>\n").arg(bookName);
  allText += QString("\n");
  allText += QString("  <script language=\"JavaScript\" type=\"text/javascript\">\n");
  allText += QString("  var currentRow = 1;\n"); // Щом е щракнато върху ред, значи със сигурност има поне един ред, затова тази инициализация е 1.
  allText += QString("  function select_row(row) {\n");
  allText += QString("    document.getElementById(\"r\" + currentRow).style.backgroundColor = 'rgba(0,0,0,0)';\n"); // Изтрива фона и очертанията на стария, селектиран ред (с прозрачно).
  allText += QString("    document.getElementById(\"r\" + currentRow).style.borderColor = 'rgba(0,0,0,0)';\n");     //
  allText += QString("    if (row != 0) {\n");
  allText += QString("      currentRow = row;\n");
  allText += QString("      document.getElementById(\"r\" + row).style.backgroundColor = '%1';\n").arg((bookCode > 50) ? newTestamentColorB1.name() : oldTestamentColorB1.name());       // Задава фона и очертанията на новия селектиран ред.
  allText += QString("      document.getElementById(\"r\" + row).style.borderColor = '%1';\n").arg((bookCode > 50) ? SVars.newTestamentColorF.name() : SVars.oldTestamentColorF.name()); //
  allText += QString("    }\n");
  allText += QString("    document.activeElement.blur();\n"); // Премахва фокуса от клетката, върху която е щракнато. Някои браузъри осветяват елемента, който е на фокус и в този случай става грозно.
  allText += QString("  }\n");
  allText += QString("  </script>\n");
  allText += QString("\n");
  allText += QString("  <style type=text/css>\n");
  allText += QString("    body{color:%1; background-color:%2; font-family:%3,Arial,Verdana,DejaVu Sans,Liberation Sans; margin:1px;}\n").arg(SVars.dock1TextColorF.name()).arg(SVars.dock1TextColorB.name()).arg(targetBibleText->fontFamily);
  allText += QString("\n");
  allText += QString("    a.color_w_r1:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.newTestamentColorF.name()); // ffffff ff6050
  allText += QString("    a.color_w_r1:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.newTestamentColorF.name()); // ffffff ff6050
  allText += QString("    a.color_w_b1:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.oldTestamentColorF.name()); // ffffff 00aaaa
  allText += QString("    a.color_w_b1:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.oldTestamentColorF.name()); // ffffff 00aaaa
  allText += QString("\n");
  allText += QString("    a.color_r1_y:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // ff6050 ffffcc
  allText += QString("    a.color_r1_y:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // ff6050 ffffcc
  allText += QString("    a.color_bk_r2:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock2TextColorF.name()).arg(newTestamentColorB2.name()); // 000000 faccbc
  allText += QString("    a.color_bk_r2:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock2TextColorF.name()).arg(newTestamentColorB2.name()); // 000000 faccbc
  allText += QString("\n");
  allText += QString("    a.color_b1_y:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // 00aaaa ffffcc
  allText += QString("    a.color_b1_y:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // 00aaaa ffffcc
  allText += QString("    a.color_bk_b2:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock2TextColorF.name()).arg(oldTestamentColorB2.name()); // 000000 c4e1ff
  allText += QString("    a.color_bk_b2:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.dock2TextColorF.name()).arg(oldTestamentColorB2.name()); // 000000 c4e1ff
  allText += QString("\n");
  allText += QString("    a.color_b3_y:link {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(SVars.dock2TextColorB.name()); // 64b1ff ffffcc
  allText += QString("    a.color_b3_y:visited {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(SVars.dock2TextColorB.name()); // 64b1ff ffffcc
  allText += QString("    a.color_b3_b2:link {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(oldTestamentColorB2.name()); // 64b1ff c4e1ff
  allText += QString("    a.color_b3_b2:visited {color:rgba(%1,%2,%3,%4); background-color:%5; text-decoration:none;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(oldTestamentColorB2.name()); // 64b1ff c4e1ff
  allText += QString("\n");
  allText += QString("    .row{ border-style: solid; border-width:1px; border-color: rgba(0,0,0,0); padding-left: 2px; padding-top: 0px;  padding-right: 2px;  padding-bottom: 0px; }\n");
  allText += QString("\n");
  allText += QString("    .color_r1{color:%1;}\n").arg(SVars.newTestamentColorF.name()); // ff6050
  allText += QString("    .color_b1{color:%1;}\n").arg(SVars.oldTestamentColorF.name()); // 00aaaa
  allText += QString("    .color_y{background-color:%1;}\n").arg(SVars.dock2TextColorB.name()); // ffffcc
  allText += QString("\n");
  allText += QString("    .color_r1_y{color:%1; background-color:%2;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // ff6050 ffffcc
  allText += QString("    .color_b1_y{color:%1; background-color:%2;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock2TextColorB.name()); // 00aaaa ffffcc
  allText += QString("    .color_b3_y{color:rgba(%1,%2,%3,%4); background-color:%5;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(SVars.dock2TextColorB.name()); // 64b1ff ffffcc
  allText += QString("    .color_r1_r2{color:%1; background-color:%2;}\n").arg(SVars.newTestamentColorF.name()).arg(newTestamentColorB2.name()); // ff6050 faccbc
  allText += QString("    .color_b1_b2{color:%1; background-color:%2;}\n").arg(SVars.oldTestamentColorF.name()).arg(oldTestamentColorB2.name()); // 00aaaa c4e1ff
  allText += QString("    .color_b3_b2{color:rgba(%1,%2,%3,%4); background-color:%5;}\n").arg(SVars.oldTestamentColorFA.red()).arg(SVars.oldTestamentColorFA.green()).arg(SVars.oldTestamentColorFA.blue()).arg(SVars.oldTestamentColorFA.alphaF()).arg(oldTestamentColorB2.name()); // 64b1ff c4e1ff
  allText += QString("\n");
  allText += QString("    .color_bk_r1{color:%1; background-color:%2;}\n").arg(SVars.dock2TextColorF.name()).arg(SVars.newTestamentColorF.name()); // 000000 ff6050
  allText += QString("    .color_bk_b1{color:%1; background-color:%2;}\n").arg(SVars.dock2TextColorF.name()).arg(SVars.oldTestamentColorF.name()); // 000000 00aaaa
  allText += QString("    .color_bk_r2{color:%1; background-color:%2;}\n").arg(SVars.dock2TextColorF.name()).arg(newTestamentColorB2.name()); // 000000 faccbc
  allText += QString("    .color_bk_b2{color:%1; background-color:%2;}\n").arg(SVars.dock2TextColorF.name()).arg(oldTestamentColorB2.name()); // 000000 c4e1ff
  allText += QString("\n");
  allText += QString("    .color_w_r1{color:%1; background-color:%2;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.newTestamentColorF.name()); // ffffff ff6050
  allText += QString("    .color_w_b1{color:%1; background-color:%2;}\n").arg(SVars.dock1TextColorB.name()).arg(SVars.oldTestamentColorF.name()); // ffffff 00aaaa
  allText += QString("  </style>\n");
  allText += QString("</head>\n");
  allText += QString("\n");
  allText += QString("<body>\n\n");

  allText += QString("<big><big><big>\n\n");

  QString nav = QString("<table %1 border=\"0\" width=\"100%\" cellspacing=\"4\" cellpadding=\"0\">\n").arg((TS->globalLayoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  nav += QString("  <tr align=\"center\">\n");

  if (bookCode == 1)
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a></td>\n").arg("77").arg(bookFileNameArr[77-1]).arg(bookFileNameArr[77-1]).arg("01");
  else if (bookCode == 51 && !SVars.showDeuterocanonical) // Ако трябва да се скрият второканоничните книги.
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a></td>\n").arg("39").arg(bookFileNameArr[39-1]).arg(bookFileNameArr[39-1]).arg("01");
  else
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&lt;&lt;&nbsp;</b></a></td>\n").arg(bookCode-1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)-1]).arg(bookFileNameArr[(bookCode-1)-1]).arg("01");

  if (chapterCode == 1)
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&lt;&nbsp;&nbsp;</b></a></td>\n").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  else
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&lt;&nbsp;&nbsp;</b></a></td>\n").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode-1, 2, 10, QLatin1Char('0'));

  if (chapterCode == chaptersCountArr[(bookCode-1)])
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&gt;&nbsp;&nbsp;</b></a></td>\n").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  else
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&nbsp;&gt;&nbsp;&nbsp;</b></a></td>\n").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode+1, 2, 10, QLatin1Char('0'));

  if (bookCode == 77)
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a></td>\n").arg("01").arg(bookFileNameArr[1-1]).arg(bookFileNameArr[1-1]).arg("01");
  else if (bookCode == 39 && !SVars.showDeuterocanonical) // Ако трябва да се скрият второканоничните книги.
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a></td>\n").arg("51").arg(bookFileNameArr[51-1]).arg(bookFileNameArr[51-1]).arg("01");
  else
    nav += QString("    <td class=\"color_w_b1\"><a class=\"color_w_b1\" href=\"../%1_%2/%3_%4.htm\"><b>&nbsp;&gt;&gt;&nbsp;</b></a></td>\n").arg(bookCode+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)+1]).arg(bookFileNameArr[(bookCode-1)+1]).arg("01");

  if (bookCode > 50) nav = nav.replace(QString("color_w_b1"), QString("color_w_r1"));

  nav += QString("  </tr>\n");
  nav += QString("</table>\n\n");

  allText += nav;

  allText += QString("<table %1 border=\"0\" width=\"100%\" cellspacing=\"4\" cellpadding=\"0\">\n").arg((targetBibleText->layoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"");
  allText += QString("  <tr valign=\"top\">\n\n");

  allText += QString("    <td class=\"color_y\" width=\"10%\">\n");
  allText += QString("      <table %1 border=\"0\" width=\"100%\" cellspacing=\"1\" cellpadding=\"2\" style=\"background-color:%2;\">\n").arg((TS->globalLayoutDirection == Qt::LeftToRight) ? "dir=\"LTR\"" : "dir=\"RTL\"").arg(SVars.dock2TextColorF.name());

  QStringList tdBooks;
  QStringList tdChapters;
  int chapter = 0;

  quint16 chaptersCount = chaptersCountArr[(bookCode-1)]; // Брой на главите в книгата.
  quint16 tableRowsCount = bookCode + chaptersCount - 1; // Брой на редовете, които трябва да съдържа таблицата.
  if (SVars.showDeuterocanonical)
  {
    if (tableRowsCount < 77) tableRowsCount = 77; // Редовете не могат да бъдат по-малко от броя на всички книги в Библията.
  }
  else
  {
    if (bookCode > 50) tableRowsCount -= 11; // Това е защото второканоничните са скрити и всички книги от НЗ се вдигат с 11 нагоре.
    if (tableRowsCount < 66) tableRowsCount = 66; // Редовете не могат да бъдат по-малко от броя на всички книги в Библията (в случая без второканоничните).
  }

  quint16 corr = 0; // Корекция - указва колко книги да се извадят, ако трябва да се скрият второканоничните книги.
  for (int i = 0; i < tableRowsCount; i ++)
  {
    corr = (bookCode > 50 && !SVars.showDeuterocanonical) ? 11 : 0; // Ако трябва да се скрият второканоничните книги.
	
    // Лява колона с книгите:
    if (i == (bookCode-corr-1)) // Ако е текущата книга.
    {
      if (i < 39) // За Стария Завет.
      {
        tdBooks << QString("<td class=\"color_b1_b2\"><span class=\"color_b1_b2\"><b>%1</b></span></td>").arg(bookMinNameArr[i].replace(QString(" "), QString("&nbsp;")));
      }
      else if (SVars.showDeuterocanonical && i < 50) // За второканоничните книги.
      {
        tdBooks << QString("<td class=\"color_b3_b2\"><span class=\"color_b3_b2\"><b>%1</b></span></td>").arg(bookMinNameArr[i].replace(QString(" "), QString("&nbsp;")));
      }
      else // За Новия Завет.
      {
        tdBooks << QString("<td class=\"color_r1_r2\"><span class=\"color_r1_r2\"><b>%1</b></span></td>").arg(bookMinNameArr[i+corr].replace(QString(" "), QString("&nbsp;")));
      }
    }
    else
    {
      if ((SVars.showDeuterocanonical && i >= 77) || (!SVars.showDeuterocanonical && i >= 66)) // За празните редове след Новия Завет.
      {
        tdBooks << QString("<td class=\"color_y\"></td>"); // Празен ред.
      }
      else if (i < 39) // За Стария Завет.
      {
        tdBooks << QString("<td class=\"color_b1_y\"><a class=\"color_b1_y\" href=\"../%1_%2/%3_%4.htm\"><b>%5</b></a></td>").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookMinNameArr[i].replace(QString(" "), QString("&nbsp;")));
      }
      else if (SVars.showDeuterocanonical && i < 50) // За второканоничните книги.
      {
        tdBooks << QString("<td class=\"color_b3_y\"><a class=\"color_b3_y\" href=\"../%1_%2/%3_%4.htm\"><b>%5</b></a></td>").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookMinNameArr[i].replace(QString(" "), QString("&nbsp;")));
      }
      else if (SVars.showDeuterocanonical) // За Новия Завет, когато са показани второканоничните книги.
      {
        tdBooks << QString("<td class=\"color_r1_y\"><a class=\"color_r1_y\" href=\"../%1_%2/%3_%4.htm\"><b>%5</b></a></td>").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookMinNameArr[i].replace(QString(" "), QString("&nbsp;")));
      }
      else // За Новия Завет, когато не са показани второканоничните книги.
      {
        tdBooks << QString("<td class=\"color_r1_y\"><a class=\"color_r1_y\" href=\"../%1_%2/%3_%4.htm\"><b>%5</b></a></td>").arg(i+11+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i+11]).arg(bookFileNameArr[i+11]).arg("01").arg(bookMinNameArr[i+11].replace(QString(" "), QString("&nbsp;")));
      }
    }

    // Дясна колона с главите:
    if (i >= (bookCode-corr-1) && chapter < chaptersCount)
    {
      chapter++;
      if (chapter == chapterCode) // Ако е текущата глава.
      {
        if (bookCode > 50) // За Новия Завет.
        {
          tdChapters << QString("<td class=\"color_bk_r1\" width=\"10%\" align=\"center\"><span>%1</span></td>").arg(chapter, 2, 10, QLatin1Char('0'));
        }
        else // За Стария Завет и второканоничните книги.
        {
          tdChapters << QString("<td class=\"color_bk_b1\" width=\"10%\" align=\"center\"><span>%1</span></td>").arg(chapter, 2, 10, QLatin1Char('0'));
        }
      }
      else
      {
        if (bookCode > 50) // За Новия Завет.
        {
          tdChapters << QString("<td class=\"color_bk_r2\" width=\"10%\" align=\"center\"><a class=\"color_bk_r2\" href=\"../%1_%2/%3_%4.htm\">%5</a></td>").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapter, 2, 10, QLatin1Char('0')).arg(chapter, 2, 10, QLatin1Char('0'));
        }
        else // За Стария Завет и второканоничните книги.
        {
          tdChapters << QString("<td class=\"color_bk_b2\" width=\"10%\" align=\"center\"><a class=\"color_bk_b2\" href=\"../%1_%2/%3_%4.htm\">%5</a></td>").arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapter, 2, 10, QLatin1Char('0')).arg(chapter, 2, 10, QLatin1Char('0'));
        }
      }
    }
    else
    {
      tdChapters << QString("<td class=\"color_y\" width=\"10%\" align=\"center\"></td>"); // Празен ред.
    }
  }

  for (int i = 0; i < tableRowsCount; i ++)
  {
    allText += QString("        <tr valign=\"center\"> %1 %2 </tr>\n").arg(tdBooks[i]).arg(tdChapters[i]);
  }

  allText += QString("      </table>\n");
  allText += QString("    </td>\n\n");

  allText += QString("    <td>\n");
  allText += text;
  allText += QString("    </td>\n\n");

  allText += QString("  </tr>\n");
  allText += QString("</table>\n\n");

  allText += nav;

  allText += QString("</big></big></big>\n\n");

  allText += QString("<p align=\"center\" style=\"color:%1;\">\n").arg(SVars.oldTestamentColorF.name());;
  allText += QString("  <b>• MatCrossBible.HTML •</b><br />\n");
  allText += QString("  <a class=\"color_b1\" href=\"https://www.matcraft.org/\">https://www.matcraft.org/</a>\n");
  allText += QString("</p>\n\n");

  allText += QString("</body>\n</html>\n");

  QString fileName = QString("%1/MatCrossBible.HTML/%2/%3_%4/%5_%6.htm").arg(QCoreApplication::applicationDirPath()).arg(targetBibleText->name.trimmed()).arg(bookCode, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[(bookCode-1)]).arg(bookFileNameArr[(bookCode-1)]).arg(chapterCode, 2, 10, QLatin1Char('0'));
  QFile *htmlFile = new QFile(fileName);
  if (htmlFile->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text, записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(htmlFile);
    out << allText;
  }
  htmlFile->close();
  delete htmlFile;
}

void MainObject::createHTML_MatCrossBible_Main_File(BIBLE_TEXT *targetBibleText, quint8 ver)
{
  QString allText = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">\n");
  allText += QString("<html>\n");
  allText += QString("<head>\n");
  allText += QString("  <meta name=\"qrichtext\" content=\"1\" />\n");
  allText += QString("  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n");
  allText += QString("  <title>%1 - MatCrossBible.HTML</title>\n").arg(targetBibleText->name.trimmed());
  allText += QString("\n");
  allText += QString("  <style type=text/css>\n");
  allText += QString("    body{color:%1; background-color:%2; font-family:%3,Arial,Verdana,DejaVu Sans,Liberation Sans;}\n").arg(SVars.dock1TextColorF.name()).arg(SVars.dock1TextColorB.name()).arg(targetBibleText->fontFamily);
  allText += QString("\n");
  allText += QString("    a.newt:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.newt:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.newTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldt:link {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldt:visited {color:%1; background-color:%2; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.name()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldd:link {color:rgba(%1,%2,%3,0.6); background-color:%4; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.red()).arg(SVars.oldTestamentColorF.green()).arg(SVars.oldTestamentColorF.blue()).arg(SVars.dock1TextColorB.name());
  allText += QString("    a.oldd:visited {color:rgba(%1,%2,%3,0.6); background-color:%4; text-decoration:none;}\n").arg(SVars.oldTestamentColorF.red()).arg(SVars.oldTestamentColorF.green()).arg(SVars.oldTestamentColorF.blue()).arg(SVars.dock1TextColorB.name());
  allText += QString("\n");
  allText += QString("    .colorred{color:%1;}\n").arg(SVars.newTestamentColorF.name());
  allText += QString("    .colorblue{color:%1;}\n").arg(SVars.oldTestamentColorF.name());
  allText += QString("  </style>\n");
  allText += QString("</head>\n");
  allText += QString("\n");
  allText += QString("<body>\n");

  allText += QString("<p align=\"center\">\n");
  if (ver == 2) allText += QString("<big><big><big>\n");
  allText += targetBibleText->description;
  if (ver == 2) allText += QString("</big></big></big>\n");
  allText += QString("</p>\n");

  if (ver == 2)
    allText += QString("<p align=\"center\">\n<big><big><big>\n");
  else
    allText += QString("<p align=\"center\">\n<big>\n");
  for (int i = 0; i < 77; i ++)
  {
    if (i < 50)
    {
      if (i > 38)
      {
        if (SVars.showDeuterocanonical) allText += QString("<a class=\"oldd\" href=\"%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
      }
      else
      {
        allText += QString("<a class=\"oldt\" href=\"%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
      }
    }
    else
    {
      allText += QString("<a class=\"newt\" href=\"%1_%2/%3_%4.htm\"><b>&nbsp;%5&nbsp;</b></a><br />\n").arg(i+1, 2, 10, QLatin1Char('0')).arg(bookFileNameArr[i]).arg(bookFileNameArr[i]).arg("01").arg(bookShortNameArr[i]);
    }

    if (i == 4 || i == 17 || i == 21 || i == 38 || i == 49 || i == 54 || i == ((SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) ? 68 : 61) || i == 75)
    {
      allText += QString("<br />\n");
    }
  }
  if (ver == 2)
    allText += QString("</big></big></big>\n</p>\n");
  else
    allText += QString("</big>\n</p>\n");

  allText += QString("<p align=\"center\" style=\"color:%1;\"><small>").arg(SVars.oldTestamentColorF.name());
  allText += QString("  <b>• MatCrossBible.HTML •</b><br />\n");
  allText += QString("  <a class=\"colorblue\" href=\"https://www.matcraft.org/\">https://www.matcraft.org/</a>\n");
  allText += QString("</small></p>\n\n");

  allText += QString("</body>\n</html>\n");

  QString fileName = QString("%1/MatCrossBible.HTML/%2/%2.htm").arg(QCoreApplication::applicationDirPath()).arg(targetBibleText->name.trimmed());
  QFile *htmlFile = new QFile(fileName);
  if (htmlFile->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text, записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(htmlFile);
    out << allText;
  }
  htmlFile->close();
  delete htmlFile;
}

void MainObject::createPathToSettingsIniFile(QString path)
{
  // Ако path не е празен стринг, създава файла наново, дори да съществува.
  bool replaceFile = !path.isEmpty();

  if (!path.isEmpty() && path != QString("local")) // Ако не е празен стринг и ако не е думата "local".
  {
    // Предполага се, че е валидна директория и се проверява дали съществува:
    if (QDir(path) == QDir(QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath()))) // Ако е хом-директорията.
      path = "";
    else if (QDir(path) == QDir(QString("%1/Settings").arg(applicationDirPath))) // Ако е в диркторията на exe-то.
      path = "local";
    else if (!QDir(path).exists()) // Ако е друга директория и не съществува на диска.
      path = "";
    // Ако мине през горните проверки, значи е друга, съществуваща директория, която ще се запише.
  }

  // Създава PathToSettings.ini файла, ако не съществува.
  QString fileName = QString("%1/Settings/PathToSettings.ini").arg(applicationDirPath);
  if (QFile::exists(fileName) && !replaceFile) return; // Ако файлът съществува и не е зададен нов път, тоест няма нужда да се риплейсва. Тази ситуация става само при създаване на MainObject, тоест при инициализация на програмата.

  if (!QFile::exists(fileName) && !replaceFile) // Ако файлът не съществува и не е зададен нов път. Тази ситуация става при първо пускане на програмата. Този ред определя къде да се запишат настройките при първо пускане на програмата.
  {
    QString message = QString("<b>%1</b>").arg(TS->TOFirstIniPath_v1);
    message += "<br/><br/>";
    message += "<ul>";
    message += QString("<li><span style=\"color:#008080;\"><b>%1</b></span>").arg(TS->TOFirstIniPathH1_v1);
    message += QString("<br/><span style=\"color:#008080;\">%1</span>").arg(TS->TOFirstIniPathH2_v1);
    message += QString("<br/><span style=\"color:#008080;\">%1</span>").arg(TS->TOFirstIniPathH3_v1);
    message += "<br/>";
    message += QString("<span style=\"color:#808080;\">(%1/.MatCraft/MatCrossBible)</span>").arg(QDir::homePath());
    message += "<br/><br/>";
    message += QString("<li><span style=\"color:#008080;\"><b>%1</b></span>").arg(TS->TOFirstIniPathL1_v1);
    message += QString("<br/><span style=\"color:#008080;\">%1</span>").arg(TS->TOFirstIniPathL2_v1);
    message += QString("<br/><span style=\"color:#008080;\">%1</span>").arg(TS->TOFirstIniPathL3_v1);
    message += "<br/>";
    message += QString("<span style=\"color:#808080;\">(%1/Settings)</span>").arg(applicationDirPath);
    message += "</ul>";
    message += "<br/><br/>";

    QMessageBox messageBox(0);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setText(message);
    QPushButton *homeButton = messageBox.addButton(TS->TOFirstIniPathH4_v1, QMessageBox::AcceptRole);   // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
    QPushButton *lockalButton = messageBox.addButton(TS->TOFirstIniPathL4_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
    messageBox.setDefaultButton(homeButton);
    messageBox.exec();

    if (messageBox.clickedButton() == lockalButton) path = "local";
  }

  QString text = "[General]\n";
  text += QString("fullPath=%1\n").arg(path);
  text += "\n";
  text += "\n";
  text += "; Path to the folder where the settings, notes and MatCrossBible resource will be stored.\n";
  text += "; \n";
  text += "; Examples:\n";
  text += "; \n";
  text += "; Indicates, that the settings will be saved in your computer's Home folder:\n";
  text += "; fullPath=\n";
  text += "; \n";
  text += "; Indicates, that the settings will be saved in the Settings folder, found in the same\n";
  text += "; folder as the MatCrossBible executable file (for portable version):\n";
  text += "; fullPath=local\n";
  text += "; \n";
  text += "; Indicates, that the settings will be saved in a random, EXISTING folder (the folder\n";
  text += "; separators must be forward slashes):\n";
  text += "; fullPath=D:/Programs/MatCrossBible/Settings\n";
  text += "\n";
  text += "\n";
  text += "; BULGARIAN:\n";
  text += "; Път до директорията, в която ще се записват настройките, бележника и ресурсите на MatCrossBible.\n";
  text += ";\n";
  text += "; Ако не зададете път, т.е. ако след fullPath= няма нищо, то настройките ще се запишат в домашната\n";
  text += "; директория на Вашия компютър, както правят повечето компютърни програми.\n";
  text += "; Ако вместо път е написана думата local (fullPath=local), то настройките ще се запишат в директория\n";
  text += "; Settings, която се намира в директорията на изпълнимия файл на MatCrossBible (в която е файлът,\n";
  text += "; който четете в момента). Това е подходящо за портабъл версия - ако програмата се пуска от флашка.\n";
  text += ";\n";
  text += "; Трябва да спазите две важни особености, ако решите да напишете пътя:\n";
  text += ";\n";
  text += "; 1. Разделителните черти между директориите, трябва да са нормални наклонени черти - \"/\".\n";
  text += "; Например fullPath=D:/Programs/MatCrossBible/Settings\n";
  text += "; 2. Пътят трябва да съществува на диска. Ако не съществува, първо го създайте.\n";
  text += ";\n";
  text += "; Ако поради някаква причина пътят е невалиден, MatCrossBible ще използва подразбиращия се път до\n";
  text += "; домашната директория.\n";
  text += ";\n";
  text += "; По гореописания начин, можете да зададете произволно място, където ще се пазят настройките на MatCrossBible.\n";
  text += "; Ако зададете пътя до директорията, в която е изпълнимия файл на MatCrossBible (с думата local), всички\n";
  text += "; настройки ще се пазят на едно място - в директорията на MatCrossBible, а не някъде в домашната директория.\n";
  text += "; Но това крие и някои опасности. Ако инсталирате нова версия, без инсталатор, може да забравите, че настройките\n";
  text += "; са в директорията на MatCrossBible и да я изтриете (с идеята да сложите по-новата версия) и по този начин\n";
  text += "; да изгубите всички настройки, съдържанието на бележника и други.\n";
  
  QDir dir; // Създава (ако не съществува) директория Settings.
  dir.mkpath(QString("%1/Settings").arg(applicationDirPath));

  QFile *iniFile = new QFile(fileName);
  if (iniFile->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text, записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(iniFile); // Note: On Windows, all '\n' characters are written as '\r\n' if QTextStream's device or string is opened using the QIODevice::Text flag.
    out << text;
  }
  iniFile->close();
  delete iniFile;
}

void MainObject::getNextBook(quint16 *absIndex, quint8 *bookCode)
{
  if (absIndex != 0)
  {
    quint8 bCode = toBookCode(*absIndex);
    getNextBook(0, &bCode); // Рекурсивно извикване на тази функция, но с другия параметър.
    *absIndex = toAbsIndex(bCode, 1, 1);
  }

  if (bookCode != 0)
  {
    *bookCode = *bookCode + 1;
    if (*bookCode > 77) *bookCode = 1;

    if (!SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
    {
      if (*bookCode >= 40 && *bookCode <= 50) *bookCode = 51;
    }
  }
}

void MainObject::getPrevBook(quint16 *absIndex, quint8 *bookCode)
{
  if (absIndex != 0)
  {
    quint8 bCode = toBookCode(*absIndex);
    getPrevBook(0, &bCode); // Рекурсивно извикване на тази функция, но с другия параметър.
    *absIndex = toAbsIndex(bCode, 1, 1);
  }

  if (bookCode != 0)
  {
    *bookCode = *bookCode - 1;
    if (*bookCode < 1) *bookCode = 77;

    if (!SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
    {
      if (*bookCode >= 40 && *bookCode <= 50) *bookCode = 39;
    }
  }
}

void MainObject::getNextChapter(quint16 *absIndex, quint8 *bookCode, quint8 *chapterCode)
{
  if (absIndex != 0)
  {
    quint8 bCode = toBookCode(*absIndex);
    quint8 cCode = toChapterCode(*absIndex);
    getNextChapter(0, &bCode, &cCode); // Рекурсивно извикване на тази функция, но с другите параметри.
    *absIndex = toAbsIndex(bCode, cCode, 1);
  }

  if (bookCode != 0 && chapterCode != 0)
  {
    int i;
    for(i = 0; i < MAX_CHAPTERS; i++)
    {
      if (booksShortArr[i] == *bookCode && chaptersShortArr[i] == *chapterCode) break;
    }

    i++;
    if (i == MAX_CHAPTERS) i = 0;
    *bookCode = booksShortArr[i];
    *chapterCode = chaptersShortArr[i];

    if (!SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
    {
      if (*bookCode >= 40 && *bookCode <= 50) {*bookCode = 51; *chapterCode = 1;}

      if (*bookCode == 19 && *chapterCode == 151) {*bookCode = 20; *chapterCode = 1;}
      else if (*bookCode == 27 && (*chapterCode == 13 || *chapterCode == 14)) {*bookCode = 28; *chapterCode = 1;}
    }
  }
}

void MainObject::getPrevChapter(quint16 *absIndex, quint8 *bookCode, quint8 *chapterCode)
{
  if (absIndex != 0)
  {
    quint8 bCode = toBookCode(*absIndex);
    quint8 cCode = toChapterCode(*absIndex);
    getPrevChapter(0, &bCode, &cCode); // Рекурсивно извикване на тази функция, но с другите параметри.
    *absIndex = toAbsIndex(bCode, cCode, 1);
  }

  if (bookCode != 0 && chapterCode != 0)
  {
    int i;
    for(i = (MAX_CHAPTERS-1); i >= 0; i--)
    {
      if (booksShortArr[i] == *bookCode && chaptersShortArr[i] == *chapterCode) break;
    }

    i--;
    if (i < 0) i = MAX_CHAPTERS - 1;
    *bookCode = booksShortArr[i];
    *chapterCode = chaptersShortArr[i];

    if (!SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
    {
      if (*bookCode >= 40 && *bookCode <= 50) {*bookCode = 39; *chapterCode = 4;}

      if (*bookCode == 19 && *chapterCode == 151) *chapterCode = 150;
      else if (*bookCode == 27 && (*chapterCode == 13 || *chapterCode == 14)) *chapterCode = 12;
    }
  }
}

void MainObject::getDailyReadGroup(quint16 day, QUInt16List &dailyGroup)
{
  // Кодът в if-else е еднакъв, разликата е само в разместените групи.
  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) // По западния стандарт.
  {
    // Разпределение на главите в режим ежедневно четене по западния стандарт:
    quint8 arr[DAILY_READ_TOTAL_DAYS] = {                                                                      // Разпределението е за DAILY_READ_TOTAL_DAYS дни:
      4,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,     //   1 -  50
      4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,4,5,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,5,     //  51 - 100
      5,4,4,5,5,5,4,4,4,4,4,4,4,4,5,5,8,8,8,8,8,8,8,8,8,8,8,8,8,8,6,8,8,8,8+1,4,4,4,4,4,4,4,3,4,4,4,4,4,5,4,   // 101 - 150
      4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4+2,5,4,5,3,5,4,5,   // 151 - 200
      7,3,3,5,5,5,4,4+188,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4,4,                           // 201 - 237
      4,4,4,4,4,4,4,4,4,4,5,6,6,4,4,5,3,6,4,4,5,4,4,    5,5,3,5,3,                                             // 238 - 265 // Подредба по западния стандарт: Римляни..Евреи, Яков..Юда.
      5,5,4,4,4};                                                                                              // 266 - 270

    quint16 count = 0;
    for (quint16 i = 0; i < (day-1); i++)
    {
      count += arr[i];
    }
    
    dailyGroup.clear();
    for (quint8 i = 0; i < arr[day-1]; i++)
    {
      dailyGroup << toAbsIndex(booksShortArr[count+i], chaptersShortArr[count+i], 1);
    }
  }
  else // По източния стандарт.
  {
    // Разпределение на главите в режим ежедневно четене по източния стандарт:
    quint8 arr[DAILY_READ_TOTAL_DAYS] = {                                                                      // Разпределението е за DAILY_READ_TOTAL_DAYS дни:
      4,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,     //   1 -  50
      4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,5,5,4,4,4,4,4,5,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,5,     //  51 - 100
      5,4,4,5,5,5,4,4,4,4,4,4,4,4,5,5,8,8,8,8,8,8,8,8,8,8,8,8,8,8,6,8,8,8,8+1,4,4,4,4,4,4,4,3,4,4,4,4,4,5,4,   // 101 - 150
      4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4+2,5,4,5,3,5,4,5,   // 151 - 200
      7,3,3,5,5,5,4,4+188,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,4,4,4,4,4,4,4,4,4,4,                           // 201 - 237
      5,5,3,5,3,    4,4,4,4,4,4,4,4,4,4,5,6,6,4,4,5,3,6,4,4,5,4,4,                                             // 238 - 265 // Подредба по източния стандарт: Яков..Юда, Римляни..Евреи.
      5,5,4,4,4};                                                                                              // 266 - 270

    quint16 count = 0;
    for (quint16 i = 0; i < (day-1); i++)
    {
      count += arr[i];
    }
    
    dailyGroup.clear();
    for (quint8 i = 0; i < arr[day-1]; i++)
    {
      dailyGroup << toAbsIndex(booksShortArr[count+i], chaptersShortArr[count+i], 1);
    }
  }

  // В това разпределение Второканоничните книги и глави са прибавени към следните групи:
  // В група: 135 -- Псалом 151                                                                                                                                (общо  1 глава)
  // В група: 193 -- Даниил 13 и 14                                                                                                                            (общо  2 глави)
  // В група: 208 -- 2 Ездра, Товита, Иудит Премъдрост Соломонова, Исус Сирахов Послание на Еремия, Варуха 1 Макавей, 2 Макавей, 3 Макавей, 3 Ездра, 3 Макавей (общо 188 глави)
}

void MainObject::removeTags(QString *str)
{
  // В някои езици, като френския, триъгълните скоби се използват като кавички - например « succès ».
  // Понякога вместо тези знаци се използват две съседни кавички например така << succès >>.
  // Дори тук да се направи проверка за такива слепени скоби, и те да се игнорират, това няма да реши
  // проблема при показването на текста в QTextBrowser, който ще интерпретира тези скоби като тагове
  // и ще ги премахне, заедно с текста между тях (т.е. текста между такива скоби няма да се покаже).
  // Ето защо просто не трябва да се допуска в текстовете с Библията да има такива слепени кавички.
  // Ако има, те трябва предварително да се заменят с « » в самия .hbt файл.
  // Поради тази причина, в този метод не се следи за такива неща, а всичко разположено между
  // триъгълни скоби се изтрива.

  // Това е моят начин за отстраняване на тагове, преди да разбера, че има по-интелигентен (като долния с QRegExp):
  //int index1 = str->indexOf("<"); // Търси отваряща скоба на таг (връща -1 ако няма).
  //if (index1 == -1) return;         // Ако няма отваряща скоба на таг, връща стринга непроменен.
  //int index2 = str->indexOf(">"); // Търси затваряща скоба на таг (връща -1 ако няма).
  //if (index2 == -1) return;         // Ако няма затваряща скоба на таг (невалиден таг), връща стринга непроменен.
  //if (index2 < index1) return;      // Ако затварящата скоба е преди отваряща (невалиден таг), връща стринга непроменен.
  //removeTags(&str->remove(index1, (index2-index1+1))); // Рекурсивно извикване на функцията за търсене на следващ таг в стринга.
  
  // http://stackoverflow.com/questions/2799379/is-there-an-easy-way-to-strip-html-from-a-qstring-in-qt
  str->remove(QRegExp("<[^>]*>"));
  
  //QTextDocument doc;
  //doc.setHtml(*str);
  //*str = doc.toPlainText();
}

// Проверява дали кодовете са валидни. Използва се (засега) само от системата за бърз достъп и щракване върху картата с резултатите от търсенето.
bool MainObject::verification(quint8 bookCode, quint8 chapterCode, quint8 verseCode)
{
  if (!SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
  {
    if ( bookCode >= 40 && bookCode <= 50 ) return false;
    if ( (bookCode == 19 && chapterCode == 151) || (bookCode == 27 && (chapterCode == 13 || chapterCode == 14)) ) return false;
  }
  if (bookCode < 1 || bookCode > 77) return false;
  if (chapterCode < 1 || chapterCode > chaptersCountArr[bookCode-1]) return false;
  if (verseCode < 1) return false; // Проверката за валидност на стиха е трудна и затова не се прави, но това не е фатално. 
  return true;
}

QString MainObject::toBookName(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return "";

  return bookNameArr[booksExtArr[absIndex]-1];
}

QString MainObject::toBookShortName(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return "";

  return bookShortNameArr[booksExtArr[absIndex]-1];
}

QString MainObject::toBookMinName(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return "";

  return bookMinNameArr[booksExtArr[absIndex]-1];
}

QString MainObject::toBookFileName(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return "";

  return bookFileNameArr[booksExtArr[absIndex]-1];
}

quint8 MainObject::toBookCode(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return 1; // Ако абсолютният индекс е извън границите, връща 1, което не е редно, но е по-добре, отколкото програмата да гръмне.

  return booksExtArr[absIndex];
}

quint8 MainObject::toChapterCode(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return 1; // Ако абсолютният индекс е извън границите, връща 1, което не е редно, но е по-добре, отколкото програмата да гръмне.

  if (SVars.currentNumeration == NUMERATION__1)
    return chapters66ExtArr[absIndex];
  else
    return chapters77ExtArr[absIndex];
}

quint8 MainObject::toWesternBookCodeIfNeed(quint8 code)
{
  // Структурите на файловете с преводите са направени по западния стандарт на подредба на главите (ДА-Рим-1Кор...Евр-Яков-1Петр...Юда-Откр).
  // За да се показват по източния стандарт (ДА-Яков-1Петр...Юда-Рим-1Кор...Евр-Откр) се налага да се разместят данните във всички масиви.
  //
  //      Западен     Източен       Западен -> Източен       Източен -> Западен
  //      -------     -------       ------------------       ------------------
  // 55   ДА          ДА                 55 -> 55                 55 -> 55
  // 56   Рим --      Яков --            56 -> 70                 56 -> 70
  // 57   1 Кор       1 Пет              57 -> 71                 57 -> 71
  // 58   2 Кор       2 Пет              58 -> 72                 58 -> 72
  // 59   Гал         1 Йоан             59 -> 73                 59 -> 73
  // 60   Еф          2 Йоан             60 -> 74                 60 -> 74
  // 61   Фил         3 Йоан             61 -> 75                 61 -> 75
  // 62   Кол         Юда                62 -> 76                 62 -> 76
  // 63   1 Сол       Рим --             63 -> 56                 63 -> 56
  // 64   2 Сол       1 Кор              64 -> 57                 64 -> 57
  // 65   1 Тим       2 Кор              65 -> 58                 65 -> 58
  // 66   2 Тим       Гал                66 -> 59                 66 -> 59
  // 67   Тит         Еф                 67 -> 60                 67 -> 60
  // 68   Филим       Фил                68 -> 61                 68 -> 61
  // 69   Евр         Кол                69 -> 62                 69 -> 62
  // 70   Яков --     1 Сол              70 -> 63                 70 -> 63
  // 71   1 Пет       2 Сол              71 -> 64                 71 -> 64
  // 72   2 Пет       1 Тим              72 -> 65                 72 -> 65
  // 73   1 Йоан      2 Тим              73 -> 66                 73 -> 66
  // 74   2 Йоан      Тит                74 -> 67                 74 -> 67
  // 75   3 Йоан      Филим              75 -> 68                 75 -> 68
  // 76   Юда         Евр                76 -> 69                 76 -> 69
  // 77   Откр --     Откр --            77 -> 77                 77 -> 77
  // 
  // Западен:  ДА-Рим-1Кор...Евр-Яков-1Петр...Юда-Откр
  // Източен:  ДА-Яков-1Петр...Юда-Рим-1Кор...Евр-Откр

  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return code; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (code <= 55 || code == 77) return code;

  if (code <= 62)
    return code + 14;
  else 
    return code - 7;
}

quint8 MainObject::toEasternBookCodeIfNeed(quint8 code)
{
  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return code; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (code <= 55 || code == 77) return code;

  if (code >= 70)
    return code - 14;
  else 
    return code + 7;
}

quint16 MainObject::toWesternShortIndexIfNeed(quint16 index)
{
  // Структурите на файловете с преводите са направени по западния стандарт на подредба на главите (ДА-Рим-1Кор...Евр-Яков-1Петр...Юда-Откр).
  // За да се показват по източния стандарт (ДА-Яков-1Петр...Юда-Рим-1Кор...Евр-Откр) се налага да се разместят данните във всички масиви.
  //
  //           Западен             Източен
  //      ------------       -------------
  // 55        ДА                  ДА          
  // 56   1237 Рим --        1237  Яков --     
  // 57        1 Кор               1 Пет       
  // 58        2 Кор               2 Пет       
  // 59        Гал                 1 Йоан      
  // 60        Еф                  2 Йоан      
  // 61        Фил                 3 Йоан      
  // 62        Кол                 Юда         
  // 63        1 Сол         1258  Рим --      <-- Това се изчислява така: 1237+(1358-1337)=1258.
  // 64        2 Сол               1 Кор       
  // 65        1 Тим               2 Кор       
  // 66        2 Тим               Гал         
  // 67        Тит                 Еф          
  // 68        Филим               Фил         
  // 69        Евр                 Кол         
  // 70   1337 Яков --             1 Сол       
  // 71        1 Пет               2 Сол       
  // 72        2 Пет               1 Тим       
  // 73        1 Йоан              2 Тим       
  // 74        2 Йоан              Тит         
  // 75        3 Йоан              Филим       
  // 76        Юда                 Евр         
  // 77   1358 Откр --       1358  Откр --     
  //
  // За booksShortArr и chaptersShortArr по западния стандарт:
  // Рим  започва от индекс 1237 и за да стане по източния стандарт, трябва да се премести на индекс 1258.
  // Яков започва от индекс 1337 и за да стане по източния стандарт, трябва да се премести на индекс 1237.
  // Откр започва от индекс 1358.

  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return index; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (index < 1237 || index >= 1358) return index;

  if (index < 1258)
    return index + 100; // 1337 - 1237
  else 
    return index - 21; // 1258 - 1237
}

quint16 MainObject::toEasternShortIndexIfNeed(quint16 index)
{
  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return index; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (index < 1237 || index >= 1358) return index;

  if (index >= 1337)
    return index - 100; // 1337 - 1237
  else 
    return index + 21; // 1258 - 1237
}

quint16 MainObject::toWesternExtIndexIfNeed(quint16 index)
{
  // Структурите на файловете с преводите са направени по западния стандарт на подредба на главите (ДА-Рим-1Кор...Евр-Яков-1Петр...Юда-Откр).
  // За да се показват по източния стандарт (ДА-Яков-1Петр...Юда-Рим-1Кор...Евр-Откр) се налага да се разместят данните във всички масиви.
  //
  //            Западен             Източен
  //      -------------       -------------
  // 55         ДА                  ДА          
  // 56   34818 Рим --        34818 Яков --     
  // 57         1 Кор               1 Пет       
  // 58         2 Кор               2 Пет       
  // 59         Гал                 1 Йоан      
  // 60         Еф                  2 Йоан      
  // 61         Фил                 3 Йоан      
  // 62         Кол                 Юда         
  // 63         1 Сол         35250 Рим --      <-- Това се изчислява така: 34818+(37589-37157)=35250.
  // 64         2 Сол               1 Кор       
  // 65         1 Тим               2 Кор       
  // 66         2 Тим               Гал         
  // 67         Тит                 Еф          
  // 68         Филим               Фил         
  // 69         Евр                 Кол         
  // 70   37157 Яков --             1 Сол       
  // 71         1 Пет               2 Сол       
  // 72         2 Пет               1 Тим       
  // 73         1 Йоан              2 Тим       
  // 74         2 Йоан              Тит         
  // 75         3 Йоан              Филим       
  // 76         Юда                 Евр         
  // 77   37589 Откр --       37589 Откр --     
  //
  // За booksExtArr, chapters66ExtArr и chapters77ExtArr по западния стандарт:
  // Рим  започва от индекс 34818 и за да стане по източния стандарт, трябва да се премести на индекс 35250.
  // Яков започва от индекс 37157 и за да стане по източния стандарт, трябва да се премести на индекс 34818.
  // Откр започва от индекс 37589.

  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return index; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (index < 34818 || index >= 37589) return index;

  if (index < 35250)
    return index + 2339; // 37157 - 34818
  else 
    return index - 432; // 35250 - 34818
}

quint16 MainObject::toEasternExtIndexIfNeed(quint16 index)
{
  if (SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) return index; // Ако програмата работи по западния стандарт и няма нужда от конвертиране.
  if (index < 34818 || index >= 37589) return index;

  if (index >= 37157)
    return index - 2339; // 37157 - 34818
  else 
    return index + 432; // 35250 - 34818
}

QString MainObject::absIndexToReference(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return QString("%1").arg(absIndex); // Ако абсолютният индекс е извън границите, го връща като стринг и това би трябвало да подскаже, че нещо не е наред.

  quint8 *chaptersExtArr = chapters66ExtArr;
  if (SVars.currentNumeration == NUMERATION__2) chaptersExtArr = chapters77ExtArr;
  quint8 bookCode = booksExtArr[absIndex];
  quint8 chapterCode = chaptersExtArr[absIndex];
  quint8 verseCode = 0;

  for(int i = absIndex; i >= 0; i--) // Тук по най-дървения начин се определя кой е номера на стиха, като се брои на какво разстояние е от първия стих в тази глава.
  {
    if (booksExtArr[i] != bookCode || chaptersExtArr[i] != chapterCode) break;
    verseCode++;
  }

  return QString("%1 %2:%3").arg(bookShortNameArr[bookCode-1]).arg(chapterCode).arg(verseCode);
}

bool MainObject::absIndexToReference(quint16 absIndex, quint8 &bookCode, quint8 &chapterCode, quint8 &verseCode)
{
  if (absIndex >= MAX_VERSES) return false; // Ако абсолютният индекс е извън границите.

  quint8 *chaptersExtArr = chapters66ExtArr;
  if (SVars.currentNumeration == NUMERATION__2) chaptersExtArr = chapters77ExtArr;
  bookCode = booksExtArr[absIndex];
  chapterCode = chaptersExtArr[absIndex];
  verseCode = 0;

  for(int i = absIndex; i >= 0; i--) // Тук по най-дървения начин се определя кой е номера на стиха, като се брои на какво разстояние е от първия стих в тази глава.
  {
    if (booksExtArr[i] != bookCode || chaptersExtArr[i] != chapterCode) break;
    verseCode++;
  }

  return true;
}

quint16 MainObject::toAbsIndex(quint8 bookCode, quint8 chapterCode, quint8 verseCode)
{
  // В този метод се правят много проверки и се върти цикъл и всичко изглежда много тромаво, но не е - проверките са мигновени, а цикълът е само колкото броя на стиховете в избраната глава.

  if (bookCode < 1 || bookCode > 77) return 0; // Тук не е редно да връща 0, но няма какво друго да върне (може да върне MAX_VERSES, но това налага проверка в извикващия метод).
  if (chapterCode < 1 || chapterCode > chaptersCountArr[bookCode-1]) return 0; //
  if (verseCode < 1) verseCode = 1; // Проверката за валидност на стиха е трудна и затова не се прави, но това не е фатално. 

  quint8 *chaptersExtArr = chapters66ExtArr;
  if (SVars.currentNumeration == NUMERATION__2) chaptersExtArr = chapters77ExtArr;

  qint32 beginAbsIndex = -1; // Това ще сочи към първия стих на избраната глава.
  qint32 endAbsIndex = -1; // Това ще сочи към последния стих на избраната глава.

  for(qint32 i = bookStartIndexInBooksExtArr[bookCode-1]; i < MAX_VERSES; i++) // Това започва от позицията в booksExtArr на книгата bookCode, глава 1, стих 1.
  {
    if (booksExtArr[i] == bookCode && chaptersExtArr[i] == chapterCode)
    {
      if (beginAbsIndex < 0) beginAbsIndex = i; // Тук beginAbsIndex е номера на първия стих (ред) от избраната главата в избраната книгата.
      endAbsIndex = i; // Последната стойност, която ще запомни endAbsIndex, е индексът на последния стих от тази глава.
    }
    else if (beginAbsIndex >= 0) // Ако beginAbsIndex е установен и е преминато към следващата книга или глава.
    {
      break; // Тук в endAbsIndex е запомнен индексът на последния стих от тази глава.
    }
  }

  if (beginAbsIndex < 0 || endAbsIndex < beginAbsIndex) return 0; // Това не може да се случи, но да има.

  beginAbsIndex += (verseCode - 1); // Добавя се кодът на стиха, но като индекс (затова е -1).
  if (beginAbsIndex > endAbsIndex) beginAbsIndex = endAbsIndex; // Ако кодът на стиха е по-голям от броя на стиховете в тази глава. Само заради тази проверка се търси последният стих кой е.
  if (beginAbsIndex >= MAX_VERSES) beginAbsIndex = MAX_VERSES - 1; // Все пак да има и такава крайна проверка. Аз обичам проверките :)

  return (quint16)beginAbsIndex;
}

quint16 MainObject::getChaptersFirstVerseAbsIndex(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return absIndex;

  quint8 *chaptersExtArr = chapters66ExtArr;
  if (SVars.currentNumeration == NUMERATION__2) chaptersExtArr = chapters77ExtArr;
  quint8 bookCode = booksExtArr[absIndex];
  quint8 chapterCode = chaptersExtArr[absIndex];

  return toAbsIndex(bookCode, chapterCode, 1);
}

// Затваря началния прозорец (логото). 
//void MainObject::closeSplashScreen()
//{
//  if (splash != 0)
//  {
//    delete splash;
//    splash = 0;
//  }
//}

int MainObject::appVersionToInt(QString appVersion)
{
  // Конвертира версията на програмата до число, подходящо за сравняване на версиите.
  // 0.9.34  = 00000+900+34  =   934
  // 0.12.34 = 00000+1200+34 =  1234
  // 3.1.38  = 30000+100+38  = 30138

  QStringList appVersionNums = QString("%1.0.0").arg(appVersion.trimmed()).split(QString(".")); // Добавянето на ".0.0", е за да улесни следващата операция. Така ако версията е 1 ще стане 1.0.0, а ако е 1.0.0 ще стане 1.0.0.0.0

  return (int)((QString(appVersionNums[0]).toUInt(0, 10)*10000) + (QString(appVersionNums[1]).toUInt(0, 10)*100) + QString(appVersionNums[2]).toUInt(0, 10));
}

QColor MainObject::colorModify(QColor color, int modify)
{
  // Ако modify е положително число, цветът ще стане по-светъл, ако е отрицателно - по-тъмен.
  // Методът прави редица изчисления и при необходимост обръща знака на модификацията.
  // Крайната цел е да се получи цвят, максимално открояващ се от оригиналния, дори ако е в другата посока.
  // За пример: Ако оригиналният цвят е много тъмен, дори черен, и се зададе модификация -40, така че новият
  // цвят да е по-тъмен, то новият ще стане незначително по-тъмен и дори еднакъв с оригиналния (ако е черен).
  // В този случай, методът ще обърне знака на модификация, така че да се получи по-светъл цвят.
  // Ако оригиналният цвят и модификацита са такива, че и в двете посоки се излиза от границите, методът ще
  // избере такава модификация, при която ще се получи по-голямо открояване на новия цвят от оригиналния.

  if (modify == 0) return color;

  int h, s, v, a;
  color.getHsv(&h, &s, &v, &a);

  int vm = v + modify;
  if ((vm >= 0) && (vm <= 255)) // Ако след модификация ще се получи реален цвят.
  {
    v = vm;
  }
  else if ((vm < 0) && ((v - modify) <= 255)) // Ако след модификация ще се излезе от долната граница, но няма да се излезе от горната, в случай, че се обърне знакът на модификацията.
  {
    v = v - modify;
  }
  else if ((vm > 255) && ((v - modify) > 0)) // Ако след модификация ще се излезе от горната граница, но няма да се излезе от долната, в случай, че се обърне знакът на модификацията.
  {
    v = v - modify;
  }
  else // Ако след модификация ще се излезе и от двете граници.
  {
    if (v > 127)
    {
      v = 0;
    }
    else
    {
      v = 255;
    }
  }

  if (v > 255) v = 255; // Тези проверки са излишни но за всеки случаи, защото стана много сложна горната логика.
  if (v < 0) v = 0;     //

  color.setHsv(h, s, v, a);
  return color;
}

QColor MainObject::getTransparentColor(QColor opaqueColor, int alpha)
{
  opaqueColor.setAlpha(alpha);
  return opaqueColor;
}

QColor MainObject::mergeColors(QColor opaqueColor, QColor transparentColor)
{
  QImage image(1, 1, QImage::Format_ARGB32);
  image.fill(QColor(255, 255, 255)); // Бял фон.

  QPainter painter(&image);
  
  painter.setPen(opaqueColor);
  painter.drawPoint(0, 0);
  
  painter.setPen(transparentColor);
  painter.drawPoint(0, 0);
  
  return QColor(image.pixel(0, 0));
}

QString MainObject::mergeFontFamilies(QString fontFamily1, QString fontFamily)
{
  QStringList fontFamilyList = QString("%1,%2").arg(fontFamily1.trimmed()).arg(fontFamily.trimmed()).split(",", QString::SkipEmptyParts); // Съединява двата стринга и веднага след това ги разделя на отделни части, а за разделител се взима запетаята. Целта е да не се допусне да има две съседни запетаи или общия стринг да започва със запетая.
  QString fontFamilies = "";
  foreach (QString fontFamily, fontFamilyList) // Отново сглабя стринга, без интервали и само с по една запетая между отделните имена на шрифтове.
  {
    fontFamilies += QString(",%1").arg(fontFamily); // По този начин, новияt стринг ще започва със запетая, която трябва да се изтрие, защото ако fontFamily започва със запетая взима системния шрифт и игнорира тези след запетаята.
  }
  if (!fontFamilies.isEmpty()) fontFamilies.remove(0, 1); // Изтрива първия знак, защото е запетая.
  return fontFamilies;
}
