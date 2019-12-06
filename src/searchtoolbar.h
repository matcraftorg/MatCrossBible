/***************************************************************************
 *   MatCrossBible  (old name: CrossBgBible)                               *
 *   Copyright (C) 2007-2020 by MatCraft, Bulgaria                         *
 *   matcraft.org@gmail.com                                                *
 *   http://www.matcraft.org/  (old site: http://www.crossbgbible.com/)    *
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

#ifndef SEARCHTOOLBAR_H
#define SEARCHTOOLBAR_H

#include <QWidget>
#include "mdock.h"
#include "datatypes.h"
#include "mainobject.h"
#include "mainwindow.h"
#include "textview.h"

class QLineEdit;
class QComboBox;
class QToolButton;
class QFrame;
class QRadioButton;
class QCheckBox;
class QTableWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QScrollArea;
class QLabel;
class QPixmap;
class QPainter;
class MDock;
class MainObject;
class MainWindow;
class TextView;
class Label;

class SearchWidget : public QWidget
{
Q_OBJECT

private:
  MainWindow   *MW;
  quint8        searchIn[77];
  quint8        percentIconHeight;
  quint8        percentIconWidth;
  QColor        iconColor; // Цвят на иконите на двата бутона ("Търсене" и "Опции за търсене").
  BIBLE_TEXT   *tBibleText; // Помощна.
  BIBLE_TEXT   *targetBibleText;
  QString       targetBooks;
  QString       searchWords;
  QLineEdit    *searchLineEdit;
  QToolButton  *searchBtn;
  QToolButton  *showOptionsBtn;
  QComboBox    *targetTextComBox;
  QFrame       *frameOptions1;
  QFrame       *frameOptions2;
  QFrame       *frameOptions3;
  QRadioButton *searchRandomRBtn;           // Търсене по произволна част от дума.
  QRadioButton *searchRootRBtn;             // Търсене по корен на дума.
  QRadioButton *searchWordRBtn;             // Търсене по точна дума.
  QRadioButton *searchAllWordsRBtn;         // Всички търсени думи.
  QRadioButton *searchAnyWordsRBtn;         // Поне една от думите.
  QRadioButton *searchPhraseRBtn;           // Търсене по точна фраза.
  QCheckBox    *searchWildCardChBox;        // Разширено търсене (чрез * и ?).
  QCheckBox    *searchCaseSensitivityChBox; // Различава главни/малки букви.
  QCheckBox    *searchInChapter;            // Търси в глава.
  int           currentRow;                 // Текущ ред селектиран в списъка.
  MDock        *mDock;
  MDockWidget  *mDockWidget1;
  MDockWidget  *mDockWidget2;
  MDockWidget  *mDockWidget3;
  QTreeWidget  *booksTreeWidget;
  QTreeWidgetItem *treeWidgetItemAll;
  QTreeWidgetItem *treeWidgetItemOld;
  QTreeWidgetItem *treeWidgetItemNew;
  QTreeWidgetItem *treeWidgetItem[77];
  QScrollArea  *imageScrollArea;
  QBitArray     searchImageArray; // За всеки стих, в който е търсено - съдържа 1, ако стихът съдържа търсения текст и 0 ако не го съдържа.
  Label        *imageLabel;
  int           imageWidth; // Широчина на картата по задание.
  int           imageW; // Реална широчина на картата след изчисляване на заданието.
  int           imageH; // Реална височина на картата след изчисляване.
  QToolButton  *imageSaveBtn;
  QToolButton  *imageWidthDecreaseBtn;
  QToolButton  *imageWidthIncreaseBtn;

  void searchGo(bool newSearch);
  void keyPressEvent(QKeyEvent *event);
  QIcon percentIcon(QColor color, QColor colorBG, double percent);
  void raiseSearchView(); // Показва на преден план изгледа "Резултати от търсенето".
  QString getSearchMethodInfo();

private slots:
  void slotShowOptions();
  void slotTargetText(int index);
  void slotSearchRandom(bool checked);
  void slotSearchRoot(bool checked);
  void slotSearchWord(bool checked);
  void slotSearchAllWords(bool checked);
  void slotSearchAnyWords(bool checked);
  void slotSearchPhrase(bool checked);
  void slotSearchWildCard(bool checked);
  void slotSearchCaseSensitivity(bool checked);
  void slotSearchInChapter(bool checked);
  //void slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); // С този слот (сигнал) не става добре, затова се използва комбинация от долните два.
  void slotItemActivated(QTreeWidgetItem *item, int column); // При еднократно или двукратно кликване с мишката (зависи от системата) или натискане на Enter.
  void slotItemClicked(QTreeWidgetItem *item, int column); // При еднократно кликване с мишката.
  void slotCurrentItemChanged(QTreeWidgetItem *item, int column); // Този слот се извиква от един от горните два.
  void slotDockWidgetRaised(MDock *dock, MDockWidget *dockWidget); // Изчертава картата.
  void slotImageSave();
  void slotImageWidthIncrease();
  void slotImageWidthDecrease();
  void slotImageMouseMoveOrPressEvent(int X, int Y, bool press);

public slots:
  void slotSearchGo();
  void slotRefreshPalette();
  void slotSetTitleBarFontSize();
  void slotSetFontSize();
  void slotSetColors();
  void slotSet3DTitleBar();

public:
  TextView *searchView;
  quint8 searchTargetTextIndex; // Запомня текста, в който действително се търси в момента (защото може от комбобокса да се избере друг текст, но да не е натиснат бутонът за търсене).
  QStringList searchWordsList;
  quint8 searchMethod;
  quint8 searchWordsLogic;
  Qt::CaseSensitivity caseSensitivitySearch;

  SearchWidget(MainWindow *mainWindow);
  virtual ~SearchWidget();
  void setSearchLineText(QString searchText); // Поставя нов текст в полето за търсене в Библията.
  void setSearchLineInFocus(bool select); // Поставя полето за търсене в Библията на фокус и селектира текста му ако select=true.
};

// ==========================================================================================================================================================

class Label : public QLabel
{
  Q_OBJECT

private:
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

public:
  Label(QWidget *parent = 0, Qt::WindowFlags f = 0);
  Label(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);

signals:
  void mouseMoveOrPressEvent(int X, int Y, bool press);
};

// ==========================================================================================================================================================

class SearchToolBar : public MDock
{
  Q_OBJECT

private:
  MainWindow *MW;
  QList<SearchWidget*> searchWidget;
  QList<MDockWidget*> mDockWidget;

private slots:
  void slotNewSearchToolBar();
  void slotHideSearchToolBar(MDock *dock, MDockWidget *dockWidget, int dockWidgetID, quint8 dockWidgetType); // Скрива панела.
  void slotSearchToolBarRaised(MDock *dock, MDockWidget *dockWidget); // Установява активния панел за търсене и насочва указателя към него.

public slots:
  void slotRefreshPalette(); // Ще извика същия слот във всички SearchWidget.
  void slotSetTitleBarFontSize(); // Ще сетне размера на текста на заглавните ленти на всички табове.
  void slotSetFontSize(); // Ще извика същия слот във всички SearchWidget.
  void slotSetColors(); // Ще сетне цветовете на фона и на прозорците.
  void slotSet3DTitleBar();
  void slotSetColorScheme_AllSearchView(); // Ще сетне цветовете на всички searchView-та.
  void slotSetFontSize_AllSearchView(int fontSize, int textZoom); // Ще сетне размера на текста на всички searchView-та.
  void slotZoomIn_AllSearchView();     // Ще увеличи размера на текста на всички searchView-та.
  void slotZoomOut_AllSearchView();    // Ще намали размера на текста на всички searchView-та.
  void slotZoomNormal_AllSearchView(); // Ще нулира размера на текста на всички searchView-та.

public:
  SearchWidget *currentSearchWidget; // Указател към активния SearchWidget.

  SearchToolBar(MainWindow *mainWindow, QWidget *parent = 0);
  virtual ~SearchToolBar();
};

#endif // SEARCHTOOLBAR_H
