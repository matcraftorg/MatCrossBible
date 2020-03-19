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

#ifndef BOOKMARKSWIDGET_H
#define BOOKMARKSWIDGET_H

#include <QToolBar>
#include <QLabel>
#include <QPalette>
#include "mdock.h"
#include "mainwindow.h"

class MDock;
class MainWindow;

class BookmarksWidget : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  QTextTable *table;
  QTextCharFormat  fo_AllBg; // Фонов цвят на всички клетки от таблицата.
  QTextBlockFormat blockFormatCol0LtR; // Формат на лява колона (ляв текст с пренасяне).
  QTextBlockFormat blockFormatCol0RtL; // Формат на лява колона (десен текст с пренасяне).
  QTextBlockFormat blockFormatCol1; // Формат на дясна колона (центриран текст, без пренасяне).
  quint8 C0; // При LeftToRight C0 е лявата колона, а при RightToLeft - дясната.
  quint8 C1; // При LeftToRight C1 е дясната колона, а при RightToLeft - лявата.
  bool ctrlKeyPressed; // Този флаг е вдигнат докато е натиснат клавиш Crtl.

  void initTable(); // Този метод е обособен отделно за да може да се извиква както в началото, така и при смяна на цветовете от настройките.
  void addRemoveBookmark(quint8 bookmarkIndex, quint16 absIndex, QString verseCode); // Поставя или премахва отметка (в зависимост от това дали кодовете са нула).
  void refreshBookmarks();
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

public:
  BookmarksWidget(MainWindow *MW);
  
public slots:
  void slotRefreshPalette();
};

// ==========================================================================================================================================================

class BookmarksToolBar : public MDock
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
  BookmarksToolBar(MainWindow *mainWindow, BookmarksWidget *bookmarksWidget, QWidget *parent = 0);
  virtual ~BookmarksToolBar();
};

#endif
