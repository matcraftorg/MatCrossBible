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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>
#include <QSplitter>
#include <QSettings>
#include <QTextCodec>
#include <QCloseEvent>
#include <QClipboard>

#include "trstrings.h"
#include "datatypes.h"
#include "utility.h"
#include "highlighter.h"
#include "mainwindow.h"
#include "textview.h"

class DockWidget;
class Highlighter;
class MainWindow;
class TextView;
struct DICT_PROPERTIES;

class Dictionary : public QWidget
{
  Q_OBJECT

private:
  MainWindow *MW;
  bool isDictionary;  // Флаг указващ, че: true - показва речник; false - показва коментар.
  int wordsInListBox; // Брой на думите в списъка с други думи.
  bool fromListBox;   // Флаг указващ, че думата в текстбокса е дошла не от писане, а от списъка с други думи (това ще забрани търсенето ѝ в речника).
  QStringList allFileNames; // Запомня имената на файловете на всички налични речници.
  QFile *file;
  QInt64List SEEKS; // За речник.
  QInt64List *SEEKS_COMM; // За коментар.
  DICT_PROPERTIES DP;
  Highlighter *highlighter;
  QClipboard *clipboard;
  QSplitter *splitter;
  QStringList BFList; // BF = BackForward
  int currentIndexInBFList;
  QWidget *hitMarker; // Малка квадратна точка, чиито цвят показва дали има точно попадение на думата.
  QPalette hitMarkerPaletteNormal;
  QPalette hitMarkerPaletteYellow;
  QPalette hitMarkerPaletteGreen;

  void clearDP();
  void keyPressEvent(QKeyEvent *event);
  QPixmap generatePixmap(QPolygonF polygon, QColor iconColor);
  QString readDictName(QString fileName);
  void loadDict(QString fileName);
  bool loadHeader();
  bool readNextHeaderString(QString expectLine, QString *value);
  int getIndexInSortSEEKSList(QString word); // Връща индекса на търсената дума в сортирания списък (списъкът се сортира още при зареждането му).
  QInt64List convertToIndexes(QString links); // Връща списък от индекси отговарящи на реални стихове, кодирани в препратката на коментара.
  QString convertToReference(QString links); // Превръща препратката от число (абсолютен индекс) в разбираем стринг (Бит. 1:2).
  QString getWord(qint64 seek); // Връща думата (чете от файла).
  QString getDescription(qint64 seek); // Връща описанието на думата (чете от файла).
  QString replaceSymbols(QString word); // Подменя символите в думата според EQUAL_SYMBOLS списъка.

public:
  TextView *mainTextView;
  QComboBox *entryCmbBox;
  QPushButton *backBtn;
  QPushButton *forwardBtn;
  QPushButton *catchCopyEventBtn;
  QPushButton *catchSelectEventBtn;
  QPushButton *prevGroupBtn;
  QPushButton *nextGroupBtn;
  QComboBox *dictCmbBox;
  QListWidget *otherWordsListWidget;
  int currentIndex; // Това е индексът на текущо показаната дума.
  int currentIndexInList; // Това е индексът на първата дума в списъка с други думи. В повечето случаи currentIndexInList = currentIndex.

  Dictionary(MainWindow *MW, QWidget *parent = 0);
  ~Dictionary();
  void setDicFontFamily(QString fontFamily = "");
  void setDicFontSize();
  void setDicColorScheme();
  void showWord(int index);

private slots:
  void slotBack();
  void slotForward();
  void slotCatchCopyEvent();
  void slotCatchSelectEvent();
  void slotPrevGroup();
  void slotNextGroup();
  void slotDictCmbBox_currentIndexChanged(int index);
  void slotEntryCmbBox_textChanged(QString text);
  //void slotListWidget_currentRowChanged(int currentRow); // С този слот (сигнал) не става добре, затова се използва комбинация от долните два.
  void slotListWidget_currentItemChanged(QListWidgetItem *item); // При еднократно или двукратно кликване с мишката (зависи от системата) или натискане на Enter.
  void slotNewSelectedText(QString text); // Приема изчистения селектиран текст в HDocks и searchView разделите. Използва се от речниците.
  void slotNewSelectedVerse(quint16 absIndex, QString reference); // Приема абсолютния индекс на текущия селектиран стих. Използва се от коментарите.
  void slotClipboard_changed(QClipboard::Mode mode);
};

#endif // DICTIONARY_H
