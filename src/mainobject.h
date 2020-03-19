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

#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <QObject>
//#include <QSplashScreen>
#include <QFile>
#include <QList>
#include <QPrinter>
#include <QStringList>

#include "trstrings.h"
#include "datatypes.h"
#include "mainwindow.h"
#include "textview.h"

class QObject;
class TrStrings;
class MainWindow;
class TextView;

// Този клас съдържа всички методи и данни, които са общи за всеки отворен раздел.
class MainObject : public QObject
{
  Q_OBJECT

private:
  //QSplashScreen *splash; // Начален прозорец (лого).
  quint8  booksExtArr[MAX_VERSES];
  quint8  chapters66ExtArr[MAX_VERSES];
  quint8  chapters77ExtArr[MAX_VERSES];
  quint8  booksShortArr[MAX_CHAPTERS];
  quint8  chaptersShortArr[MAX_CHAPTERS];

  QStringList getChapStructure(bool extStruct);
  void setBibStructure();
  void reorderBooks(); // Пренарежда масивите с данни според източния стандарт (ако е избран).
  void removeTags(QString *str);

public:
  TrStrings *TS;
  QList<BIBLE_TEXT> bibleTextList;
  QString *bookNameArr;          // Указател към масива bookNameArr[77] в TS.
  QString *bookShortNameArr;     // Указател към масива bookShortNameArr[77] в TS.
  QString *bookMinNameArr;       // Указател към масива bookMinNameArr[77] в TS.
  QString *bookFileNameArr;      // Указател към масива bookFileNameArr[77] в TS.
  quint8   chaptersCountArr[77]; // Съхранява броя на главите във всяка книга.
  quint16  bookStartIndexInBooksExtArr[77]; // Масив, съдържащ началния индекс в booksExtArr на всяка книга (т.е. помни от кой индекс започва всяка книга). Използва се за търсене в Библията.
  QString  applicationDirPath;
  QString  applicationHomePath;
  QString  iniFile;
  QString  sessionsFile;
  bool     enableExitAction; // Флаг, разрешаващ затварянето на всички прозорци, включително и минимизираните в системния трей. // For TrayIcon.
  BOOKMARKS bookmarks[MAX_BOOKMARKS]; // Списък с отметките.
  SETTINGS_VARIABLES SVars;
  QPrinter *printer;
  bool     isFirstStart; // Флаг, указващ, дали програмата е пусната за първи път.
  bool     isNewVersion; // Флаг, указващ, дали програмата е по-нова версия.

  MainObject();
  virtual ~MainObject();
  void loadSVarsSettings();
  void saveSVarsSettings();
  bool read(QBitArray *activeBibleTexts, quint16 absIndex, QString *bookName, QString *bibleTextsNames, QUInt16List *absIndexesList, TextView *textView);
  bool compare(QBitArray *activeBibleTexts, quint16 absIndex, QString *bibleTextsNames, QUInt16List *absIndexesList, TextView *textView);
  bool searchInVerse(BIBLE_TEXT *targetBibleText, quint8 targetBook, QStringList searchWordsList, SEARCH_OPTIONS sOpt, int *foundVersesCount, quint16 *allVersesInTargetBook, quint32 *foundWordCount, QBitArray *searchImageArray, QString *foundVerses);
  bool searchInChapter(BIBLE_TEXT *targetBibleText, quint8 targetBook, QStringList searchWordsList, SEARCH_OPTIONS sOpt, int *foundChaptersCount, quint16 *allChaptersInTargetBook, quint32 *foundWordCount, QBitArray *searchImageArray, QString *foundChapters);
  QString getUniqueWords(QBitArray *activeBibleTexts, quint16 absIndex, bool currentOT, bool currentNT, bool currentBook, bool currentChapter, bool alphabeticallyOrder);
  void createHTML_MatCrossBible_File_V1(BIBLE_TEXT *targetBibleText, quint8 bookCode, quint8 chapterCode);
  void createHTML_MatCrossBible_File_V2(BIBLE_TEXT *targetBibleText, quint8 bookCode, quint8 chapterCode);
  void createHTML_MatCrossBible_Main_File(BIBLE_TEXT *targetBibleText, quint8 ver);
  void createPathToSettingsIniFile(QString path = ""); // Създава PathToSettings.ini файла, ако не съществува. Ако path не е празен стринг, създава файла наново, дори да съществува.
  void getNextBook(quint16 *absIndex, quint8 *bookCode = 0); // Връща следващата книга (или по зададен абсолютен индекс или по зададен код на книга).
  void getPrevBook(quint16 *absIndex, quint8 *bookCode = 0); // Връща предходната книга (или по зададен абсолютен индекс или по зададен код на книга).
  void getNextChapter(quint16 *absIndex, quint8 *bookCode = 0, quint8 *chapterCode = 0); // Връща следващата глава (или по зададен абсолютен индекс или по зададен код на книга и глава).
  void getPrevChapter(quint16 *absIndex, quint8 *bookCode = 0, quint8 *chapterCode = 0); // Връща предходната глава (или по зададен абсолютен индекс или по зададен код на книга и глава).
  void getDailyReadGroup(quint16 day, QUInt16List &dailyGroup);
  bool verification(quint8 bookCode, quint8 chapterCode, quint8 verseCode);
  QString toBookName(quint16 absIndex);     // Връща стринг от масива bookNameArr по зададен абсолютен индекс.
  QString toBookShortName(quint16 absIndex);  // Връща стринг от масива bookShortNameArr по зададен абсолютен индекс.
  QString toBookMinName(quint16 absIndex);  // Връща стринг от масива bookMinNameArr по зададен абсолютен индекс.
  QString toBookFileName(quint16 absIndex); // Връща стринг от масива bookFileNameArr по зададен абсолютен индекс.
  quint8 toBookCode(quint16 absIndex); // Връща кода на книгата по зададен абсолютен индекс.
  quint8 toChapterCode(quint16 absIndex); // Връща кода на главата по зададен абсолютен индекс.
  quint8 toWesternBookCodeIfNeed(quint8 code); // Превръща кода на книгата от източния в западния стандарт на подредба на книгите (ако е нужно).
  quint8 toEasternBookCodeIfNeed(quint8 code); // Превръща кода на книгата от западния в източния стандарт на подредба на книгите (ако е нужно).
  quint16 toWesternShortIndexIfNeed(quint16 index); // Превръща индекса в Short масивите от източния в западния стандарт на подредба на книгите (ако е нужно).
  quint16 toEasternShortIndexIfNeed(quint16 index); // Превръща индекса в Short масивите от западния в източния стандарт на подредба на книгите (ако е нужно).
  quint16 toWesternExtIndexIfNeed(quint16 index); // Превръща индекса в Ext масивите от източния в западния стандарт на подредба на книгите (ако е нужно).
  quint16 toEasternExtIndexIfNeed(quint16 index); // Превръща индекса в Ext масивите от западния в източния стандарт на подредба на книгите (ако е нужно).
  QString absIndexToReference(quint16 absIndex); // Превръща абсолютния индекс на стиха в препратка (като стринг).
  bool absIndexToReference(quint16 absIndex, quint8 &bookCode, quint8 &chapterCode, quint8 &verseCode); // Превръща абсолютния индекс на стиха в препратки (код на книгата, главата и стиха).
  quint16 toAbsIndex(quint8 bookCode, quint8 chapterCode, quint8 verseCode = 1); // Превръща абсолютния индекс на стиха по зададени кодове на книга, глава и стих.
  quint16 getChaptersFirstVerseAbsIndex(quint16 absIndex); // Връща абсолютния индекс на първия стих от главата определена чрез аргумента. Използва се за верификация - дали два абсолютни индекса са от една и съща глава.
  //void closeSplashScreen();
  int appVersionToInt(QString appVersion); // Конвертира версията на програмата до число, подходящо за сравняване на версиите.
  QColor colorModify(QColor color, int modify); // Променя R, G и B съставките на color със стойност modify (може да е положителна или отрицателна).
  QColor getTransparentColor(QColor opaqueColor, int alpha); // Добавя полу-прозрачна съставка на зададения цвят.
  QColor mergeColors(QColor opaqueColor, QColor transparentColor); // Наслагва полу-прозрачен цвят върху непрозрачен и връща новия цвят.
  QString mergeFontFamilies(QString fontFamily1, QString fontFamily2); // Съединява два fontFamily стринга (добавя запетая между тях, само ако и двата не са празни.)
};
#endif
