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

#ifndef BOOKSWIDGET_H
#define BOOKSWIDGET_H

#include <QTreeWidget>
#include <QTextBrowser>
#include "mdock.h"
#include "mainwindow.h"
#include "fastaccesswidget.h"

class MDock;
class MainWindow;
class FastAccessWidget;

class BooksWidget : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  QTextTable *table;
  quint8 bookCode;      // Текуща книга.
  quint8 chapterCode;   // Текуща глава в книгата.
  quint8 booksCount;    // Брой на главите/редовете в таблицата - 66 или 77 (според това дали са показани Второканоничните книги).
  QTextCharFormat *fo_ActiveBook;        // Сочи към fo_ActiveBookNew или fo_ActiveBookOld;
  QTextCharFormat  fo_ActiveBookNew;     // Фонов цвят на активната книга (и номерата на всички глави от нея, без текущата), ако е от Новия Завет.
  QTextCharFormat  fo_ActiveBookOld;     // Фонов цвят на активната книга (и номерата на всички глави от нея, без текущата), ако е от Стария Завет.
  QTextCharFormat  fo_InactiveBooks;     // Фонов цвят на неактивните книги.
  QTextCharFormat  fo_CurrentChapterNew; // Фонов цвят на текущата глава, ако е от Новия Завет.
  QTextCharFormat  fo_CurrentChapterOld; // Фонов цвят на текущата глава, ако е от Стария Завет.
  QTextBlockFormat blockFormatCol2; // Формат на колона 2 (центриран текст, без пренасяне).
  quint8  bookCodeToRowNumber[77]; // Ако са показани Второканоничните книги, кодът на книгата е равен на номера на реда в таблицата. Ако са скрити Второканоничните, номерът на реда не е равен на кода на книгата. Този масив помни действителния номер на ред в таблицата.
  quint8  rowNumberToBookCode[77]; // Ако са показани Второканоничните книги, кодът на книгата е равен на номера на реда в таблицата. Ако са скрити Второканоничните, номерът на реда не е равен на кода на книгата. Този масив помни действителния код на книгата.
  quint8  C0; // При LeftToRight C0 е лявата колона. а при RightToLeft - дясната.
  quint8  C1; // При LeftToRight C1 е дясната колона. а при RightToLeft - лявата.
  bool    ctrlKeyPressed;    // Този флаг е вдигнат докато е натиснат клавиша Crtl.

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void initTable(); // Този метод е обособен отделно, за да може да се извиква както в началото, така и при смяна на цветовете от настройките.
  void setRowBackground(quint8 newBookCode, quint8 newChapterCode, quint8 oldBookCode, quint8 oldChapterCode, bool refresh); // Този също се извиква и при смяна на цветовете (тогава refresh=true).
  void moveTable(); // Показва текущия номер на глава на екрана, в случай че не се вижда.

public:
  BooksWidget(MainWindow *MW);
  void setCurrentCodes(quint8 newBookCode, quint8 newChapterCode);
  
public slots:
  void slotRefreshPalette();
};

// =========================================================================================================================================================
/*
class BooksTreeWidget : public QTreeWidget
{
Q_OBJECT

private:
  MainWindow *MW;
  QTreeWidgetItem *OldTestamentItem;
  QTreeWidgetItem *NewTestamentItem;
  QTreeWidgetItem *item; // Помощна.
  quint8 testamentCode;  // Текущ завет.
  quint8 bookCode;       // Текуща книга.
  quint8 chapterCode;    // Текуща глава в книгата.
  
  void setChapters(QTreeWidgetItem *parentItem, QList<QTreeWidgetItem *> items, quint8 chaptersCount, bool isOldTestament);
  void mousePressEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void showBibleText(QTreeWidgetItem *cItem);

public:
  BooksTreeWidget(MainWindow *MW);
  void setCurrentCodes(quint8 newTestamentCode, quint8 newBookCode, quint8 newChapterCode);
};
*/
// =========================================================================================================================================================
/*
class BooksLinkWidget : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  quint8 testamentCode;  // Текущ завет.
  quint8 bookCode;       // Текуща книга.
  quint8 chapterCode;    // Текуща глава в книгата.
  int    stringPosition; // Позиция на номера на текущата глава която трябва да се селектира.

  void init1(); // Цветен фон, едноцветни линкове.
  void init2(); // Цветни линкове, едноцветен фон.
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private slots:
  void slotAnchorClicked(const QUrl &link);

public:
  BooksLinkWidget(MainWindow *MW);
  void setBooksLinkPalette(QColor textColor, QColor baseColor);
  void setCurrentCodes(quint8 newTestamentCode, quint8 newBookCode, quint8 newChapterCode);
};
*/

// ==========================================================================================================================================================

class BooksToolBar : public MDock
{
  Q_OBJECT

private:
  MainWindow *MW;
  MDockWidget *mDockWidget;

private slots:
  void slotCloseDock(MDock *dock, MDockWidget *dockWidget, int dockWidgetID, quint8 dockWidgetType); // Скрива панела.

public slots:
  void slotSetTitleBarFontSize(); // Ще сетне размера на текста на заглавната лента.
  void slotSetColors(); // Ще сетне цветовете на фона и на прозорците.
  void slotSet3DTitleBar();

public:
  BooksToolBar(MainWindow *mainWindow, BooksWidget *booksWidget, FastAccessWidget *fastAccessWidget, QWidget *parent = 0);
  virtual ~BooksToolBar();
};

#endif
