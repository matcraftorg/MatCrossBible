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

#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QtGui>
#include <QBitArray>
#include <QMenu>
#include <QList>
#include <QLabel>
#include <QTextBrowser>
#include <QPalette>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QToolTip>
#include <QStatusBar>
#include <QMessageBox>
#include "datatypes.h"
#include "utility.h"
#include "highlighter.h"
#include "mainobject.h"
#include "mainwindow.h"

class MDockWidget;
class QAction;
class Highlighter;
class MainObject;
class MainWindow;

class TextView : public QTextBrowser  
{
  Q_OBJECT

private:
  bool            disallowSelectRow; // Не разрешава селектиране на ред. Това е само когато има селектиран текст и се щракне с мишката на някой ред.
  int             currentRow;        // Помни текущия ред (не стих!).
  int             currentCol;        // Помни текущата колона (заради името на текста, който се използва в проектора, също и заради коментарите).
  QUInt16List     absIndexesList;    // Списък с големина броя на показаните стихове, съдържащ абсолютния индекс в глобалната структура на всеки от показаните стихове.
  QBitArray       selectedRows;      // Помни кои редове са селектирани.
  QTextCharFormat standardFormat;    // Формат по подразбиране, който се използва при изписване на текстове без зададен формат.
  QString         selectedVerse;     // Съхранява стиха, върху който е щракнато с левия бутон на мишката.
  QString         selectedVerseRef;  // Съхранява препратката на стиха, върху който е щракнато с левия бутон на мишката.
  QString         findInTextString;
  QTextDocument::FindFlags findInTextOptions;
  QList<QTextEdit::ExtraSelection> extraSelections1; // Мултиселекция, направена чрез селектиране с мишката (първа мултиселекция).
  QList<QTextEdit::ExtraSelection> extraSelections2; // Мултиселекция, направена чрез контекстното меню (втора мултиселекция).
  QImage          BGImage; // Картинка за фон (ако има).
  QWidget        *markWidget; // Малък правоъгълник, указващ, че това е текущият изглед.

  bool saveFile(const QString &fileName, const bool toHtml);
  void contextMenuEvent(QContextMenuEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event); // При движение на колелцето на мишката.
  void paintEvent(QPaintEvent * event);

public:
  MainWindow  *MW;
  MDockWidget *dockWidget; // Указател към раздела, който съдържа този изглед (ако е в раздел). Чрез него ще записва текущата книга и глава в заглавната лента на раздела.
  bool         isCurrentHolyTextView; // Указва дали този изглед е текущ (активен) в този момент.
  QTextTable  *versesTable;
  Highlighter *highlighter;
  quint8       textMode; // Указва режима на показване на текст.
  quint8       readMode;
  int          textZoom; // Указва големината на текста.
  QBitArray    activeBibleTexts;
  quint16      activeBibleTextsCount; // Активни текстове (брой колони в режим показване).
  QString      currentVerseCode; // Номер на текущия стих. Взима се от самия стих и се използва на места, като отметките и проектора. Няма значение в какъв режим на показване на текста е изгледът.
  quint16      currentAbsIndex; // Абсолютния индекс на текущия стих.
  QUInt16List  backForwardList;
  int          backForwardCurrentIndex; // Текущия индекс в backForwardList.
  QStringList  tempSearchWordsList; // Съдържа търсените думи, които ще бъдат оцветени веднага след отваряне на новия прозорец при щракване върху намерен стих.
  Qt::CaseSensitivity tempCaseSensitivitySearch; // Съдържа CaseSensitivity режима на търсените думи, които ще бъдат оцветени веднага след отваряне на новия прозорец при щракване върху намерен стих.
  QString      currentBibleTextsNames; // Помощен стринг. Съхранява имената на текущо отворените текстове, за да ги покаже в заглавната лента.

  QAction *searchTextAct;
  QAction *customHighlightAddAct;
  QAction *customHighlightDelAct;
  QAction *selectAllAct;
  QAction *copyAct;
  QAction *exportTextAct;
  QAction *exportHTMLAct;
  QAction *exportPDFAct;
  QAction *createHTMLMatCrossBibleV1Act;
  QAction *createHTMLMatCrossBibleV2Act;
  QAction *printPreviewAct;
  QAction *printAct;

  TextView(MainWindow *MW, QWidget *parent = 0);
  virtual ~TextView();
  void textCursorBeginEditBlock();
  void textCursorEndEditBlock();
  void initializeTextView(quint8 initialTextMode);
  void reInitializeTextView();
  void insertTable(int row, int col);
  void appendRowsToTable(int count);
  void removeLastRowsFromTable(int count);
  void tvInsertTextAt(int row, int col, QString text);
  void tvInsertTextAt(int row, int col, QString text, QTextCharFormat format);
  void tvInsertHtmlAt(int row, int col, QString text);
  void tvInsertHtmlAt(int row, int col, QString text, QTextCharFormat format);
  void tvInsertText(QString text);
  void tvInsertText(QString text, QTextCharFormat format);
  void tvInsertHtml(QString text);
  void tvSetPlainText(QString text);
  void tvSetHtml(QString text);
  void selectVerse(const quint16 absIndex, const bool deselectAllOther); // Селектира (оцветява) дадения стих. Също така указва дали да деселектира останалите стихове.
  void selectRow(const qint8 rowOperation, const bool deselectAllOther, bool setProjector); // Селектира (оцветява) предходния (rowOperation=-1), следващия (rowOperation=1) или реда от таблицата върху когото е щракнато с мишката (rowOperation=0). Също така указва дали да деселектира останалите редове. Също така указва дали селектираният стих да се изпрати към проектора.
  void deselectAllRow(); // Деселектира всички селектирани редове.
  void setCurrentHolyTextView(bool current); // Установява този изглед, като текущ (активен) в този момент или не (показва или скрива маркера).
  void setColorScheme(); // Установява различни цветови схеми.
  void showBibleText(quint16 absIndex);
  void compareText();
  QMenu *createFileMenu(); // Създава меню Файл.

public slots:
  void slotShowFileMenu();
  void slotExportText();
  void slotExportHTML();
  void slotExportPDF();
  void slotCreateHTMLMatCrossBibleV1();
  void slotCreateHTMLMatCrossBibleV2();
  void slotCreateHTMLMatCrossBibleV(quint8 ver); // Този слот се извиква от един от горните два.
  void slotPrintPreview();
  void slotPrintPreviewPaintRequested(QPrinter *printer);
  void slotPrint();
  void slotSelectAll();
  void slotFindNext();
  void slotFindPrevious();
  void slotSearchInBible();
private slots:
  void slotCustomHighlightAdd();
  void slotCustomHighlightDel();
  void slotExtraSelections(QString text, bool firstExtraSelections); // Задава текста, който ще се селектира и от кой вид е (първа или втора мултиселекция).
  void slotAnchorClicked(const QUrl &link);

signals:
  void bookChanged(QString newBookShortName, int newChapterCode);
};
#endif
