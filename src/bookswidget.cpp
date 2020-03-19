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

#include "bookswidget.h"
#include "datatypes.h"
#include <QKeyEvent>

BooksWidget::BooksWidget(MainWindow *MW) : QTextBrowser()
{
  setReadOnly(true);
  setMinimumSize(1, 1); // Не трябва да е 0 защото няма ефект.
  setContextMenuPolicy(Qt::NoContextMenu);
  document()->setDocumentMargin(-1); // 2

  this->MW = MW;
  bookCode = 1;
  chapterCode = 1;

  blockFormatCol2.setNonBreakableLines(true); // Това е много важно. Не позволява номерата на редовете да се изписват на два реда.
  blockFormatCol2.setAlignment(Qt::AlignHCenter);

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
  {
    C0 = 0;
    C1 = 1;
  }
  else
  {
    C0 = 1;
    C1 = 0;
  }

  // Този if да се премести в initTable(), ако се направи показването/скриването на Второканоничните книги да става веднага (без рестарт).
  if (MW->MO->SVars.showDeuterocanonical)
  {
    booksCount = 77;

    for (int i = 0; i < 77; i++)
    {
      bookCodeToRowNumber[i] = i + 1;
      rowNumberToBookCode[i] = i + 1;
    }
  }
  else
  {
    booksCount = 66;

    // Номер на ред в таблицата      Код на книгата
    bookCodeToRowNumber[0]  = 1;     rowNumberToBookCode[0]  = 1;
    bookCodeToRowNumber[1]  = 2;     rowNumberToBookCode[1]  = 2;
    bookCodeToRowNumber[2]  = 3;     rowNumberToBookCode[2]  = 3;
    bookCodeToRowNumber[3]  = 4;     rowNumberToBookCode[3]  = 4;
    bookCodeToRowNumber[4]  = 5;     rowNumberToBookCode[4]  = 5;
    bookCodeToRowNumber[5]  = 6;     rowNumberToBookCode[5]  = 6;
    bookCodeToRowNumber[6]  = 7;     rowNumberToBookCode[6]  = 7;
    bookCodeToRowNumber[7]  = 8;     rowNumberToBookCode[7]  = 8;
    bookCodeToRowNumber[8]  = 9;     rowNumberToBookCode[8]  = 9;
    bookCodeToRowNumber[9]  = 10;    rowNumberToBookCode[9]  = 10;
    bookCodeToRowNumber[10] = 11;    rowNumberToBookCode[10] = 11;
    bookCodeToRowNumber[11] = 12;    rowNumberToBookCode[11] = 12;
    bookCodeToRowNumber[12] = 13;    rowNumberToBookCode[12] = 13;
    bookCodeToRowNumber[13] = 14;    rowNumberToBookCode[13] = 14;
    bookCodeToRowNumber[14] = 15;    rowNumberToBookCode[14] = 15;
    bookCodeToRowNumber[15] = 16;    rowNumberToBookCode[15] = 16;
    bookCodeToRowNumber[16] = 17;    rowNumberToBookCode[16] = 17;
    bookCodeToRowNumber[17] = 18;    rowNumberToBookCode[17] = 18;
    bookCodeToRowNumber[18] = 19;    rowNumberToBookCode[18] = 19;
    bookCodeToRowNumber[19] = 20;    rowNumberToBookCode[19] = 20;
    bookCodeToRowNumber[20] = 21;    rowNumberToBookCode[20] = 21;
    bookCodeToRowNumber[21] = 22;    rowNumberToBookCode[21] = 22;
    bookCodeToRowNumber[22] = 23;    rowNumberToBookCode[22] = 23;
    bookCodeToRowNumber[23] = 24;    rowNumberToBookCode[23] = 24;
    bookCodeToRowNumber[24] = 25;    rowNumberToBookCode[24] = 25;
    bookCodeToRowNumber[25] = 26;    rowNumberToBookCode[25] = 26;
    bookCodeToRowNumber[26] = 27;    rowNumberToBookCode[26] = 27;
    bookCodeToRowNumber[27] = 28;    rowNumberToBookCode[27] = 28;
    bookCodeToRowNumber[28] = 29;    rowNumberToBookCode[28] = 29;
    bookCodeToRowNumber[29] = 30;    rowNumberToBookCode[29] = 30;
    bookCodeToRowNumber[30] = 31;    rowNumberToBookCode[30] = 31;
    bookCodeToRowNumber[31] = 32;    rowNumberToBookCode[31] = 32;
    bookCodeToRowNumber[32] = 33;    rowNumberToBookCode[32] = 33;
    bookCodeToRowNumber[33] = 34;    rowNumberToBookCode[33] = 34;
    bookCodeToRowNumber[34] = 35;    rowNumberToBookCode[34] = 35;
    bookCodeToRowNumber[35] = 36;    rowNumberToBookCode[35] = 36;
    bookCodeToRowNumber[36] = 37;    rowNumberToBookCode[36] = 37;
    bookCodeToRowNumber[37] = 38;    rowNumberToBookCode[37] = 38;
    bookCodeToRowNumber[38] = 39;    rowNumberToBookCode[38] = 39;
    bookCodeToRowNumber[39] = 0;     rowNumberToBookCode[39] = 51; // 2 Ездра
    bookCodeToRowNumber[40] = 0;     rowNumberToBookCode[40] = 52; // Товита
    bookCodeToRowNumber[41] = 0;     rowNumberToBookCode[41] = 53; // Иудит
    bookCodeToRowNumber[42] = 0;     rowNumberToBookCode[42] = 54; // Премъдрост Соломонова
    bookCodeToRowNumber[43] = 0;     rowNumberToBookCode[43] = 55; // Премъдрост на Исус, син Сирахов
    bookCodeToRowNumber[44] = 0;     rowNumberToBookCode[44] = 56; // Послание на Еремия
    bookCodeToRowNumber[45] = 0;     rowNumberToBookCode[45] = 57; // Варуха
    bookCodeToRowNumber[46] = 0;     rowNumberToBookCode[46] = 58; // 1 Макавей
    bookCodeToRowNumber[47] = 0;     rowNumberToBookCode[47] = 59; // 2 Макавей
    bookCodeToRowNumber[48] = 0;     rowNumberToBookCode[48] = 60; // 3,4 Макавей
    bookCodeToRowNumber[49] = 0;     rowNumberToBookCode[49] = 61; // 3 Ездра
    bookCodeToRowNumber[50] = 40;    rowNumberToBookCode[50] = 62;
    bookCodeToRowNumber[51] = 41;    rowNumberToBookCode[51] = 63;
    bookCodeToRowNumber[52] = 42;    rowNumberToBookCode[52] = 64;
    bookCodeToRowNumber[53] = 43;    rowNumberToBookCode[53] = 65;
    bookCodeToRowNumber[54] = 44;    rowNumberToBookCode[54] = 66;
    bookCodeToRowNumber[55] = 45;    rowNumberToBookCode[55] = 67;
    bookCodeToRowNumber[56] = 46;    rowNumberToBookCode[56] = 68;
    bookCodeToRowNumber[57] = 47;    rowNumberToBookCode[57] = 69;
    bookCodeToRowNumber[58] = 48;    rowNumberToBookCode[58] = 70;
    bookCodeToRowNumber[59] = 49;    rowNumberToBookCode[59] = 71;
    bookCodeToRowNumber[60] = 50;    rowNumberToBookCode[60] = 72;
    bookCodeToRowNumber[61] = 51;    rowNumberToBookCode[61] = 73;
    bookCodeToRowNumber[62] = 52;    rowNumberToBookCode[62] = 74;
    bookCodeToRowNumber[63] = 53;    rowNumberToBookCode[63] = 75;
    bookCodeToRowNumber[64] = 54;    rowNumberToBookCode[64] = 76;
    bookCodeToRowNumber[65] = 55;    rowNumberToBookCode[65] = 77;
    bookCodeToRowNumber[66] = 56;    rowNumberToBookCode[66] = 0;
    bookCodeToRowNumber[67] = 57;    rowNumberToBookCode[67] = 0;
    bookCodeToRowNumber[68] = 58;    rowNumberToBookCode[68] = 0;
    bookCodeToRowNumber[69] = 59;    rowNumberToBookCode[69] = 0;
    bookCodeToRowNumber[70] = 60;    rowNumberToBookCode[70] = 0;
    bookCodeToRowNumber[71] = 61;    rowNumberToBookCode[71] = 0;
    bookCodeToRowNumber[72] = 62;    rowNumberToBookCode[72] = 0;
    bookCodeToRowNumber[73] = 63;    rowNumberToBookCode[73] = 0;
    bookCodeToRowNumber[74] = 64;    rowNumberToBookCode[74] = 0;
    bookCodeToRowNumber[75] = 65;    rowNumberToBookCode[75] = 0;
    bookCodeToRowNumber[76] = 66;    rowNumberToBookCode[76] = 0;
  }

  initTable();
}

void BooksWidget::initTable()
{
//QTime timer; timer.start(); //---------------------------------------------------------------------------------------------------------
  textCursor().beginEditBlock();
  clear();

  QPalette pal = this->palette();
  pal.setBrush(QPalette::Base, MW->MO->SVars.dock2TextColorB);   // Цвят на фона. Не указва влияние, защото цветът на фона се определя на друго място.
  pal.setBrush(QPalette::Window, MW->MO->SVars.dock2TextColorB); // Цвят на фона. Не указва влияние, защото цветът на фона се определя на друго място.
  //pal.setBrush(QPalette::Button, MW->MO->SVars.appColorF);     // Това оцветява само скрол-бара. Реално указва влияние само на скролбара и затова е избран да е appColorF - за да бъдат всички скролбарове еднакви на цвят, но по-добре е редът да е закоментиран за да си взима цветовете автоматично.
  setPalette(pal);

  QTextTableFormat tableFormat;
  //tableFormat.setAlignment(Qt::AlignHCenter);
  tableFormat.setBackground(MW->MO->SVars.appColorB); //tableFormat.setBackground(MW->MO->colorModify(MW->MO->SVars.dock2TextColorF, 50));
  tableFormat.setCellPadding(2);
  tableFormat.setCellSpacing(1);
  tableFormat.setBorder(0);
  QVector<QTextLength> constraints;
  constraints << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 90 : 10)
              << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 10 : 90);
  tableFormat.setColumnWidthConstraints(constraints);
  table = textCursor().insertTable(booksCount, 2, tableFormat);

  fo_ActiveBookNew.setBackground(MW->MO->mergeColors(MW->MO->SVars.dock2TextColorB, MW->MO->getTransparentColor(MW->MO->SVars.newTestamentColorF, MW->MO->SVars.oldTestamentAlphaF)));
  fo_ActiveBookOld.setBackground(MW->MO->mergeColors(MW->MO->SVars.dock2TextColorB, MW->MO->getTransparentColor(MW->MO->SVars.oldTestamentColorF, MW->MO->SVars.oldTestamentAlphaF)));
  fo_InactiveBooks.setBackground(MW->MO->SVars.dock2TextColorB);
  fo_CurrentChapterNew.setBackground(MW->MO->SVars.newTestamentColorF);
  fo_CurrentChapterOld.setBackground(MW->MO->SVars.oldTestamentColorF);

  quint8 row = 0;
  for (int i = 0; i < 77; i++) // Тук трябва да е твърдо 77, а не booksCount.
  {
    table->cellAt(row, C0).setFormat(fo_InactiveBooks);
    if (i >= 50)
    {
      table->cellAt(row, C0).firstCursorPosition().insertHtml(QString("<font color=%1><b>%2</b></font>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->bookMinNameArr[i])); // bookShortNameArr bookMinNameArr
      row++;
    }
    else
    {
      if (i >= 39)
      {
        if (MW->MO->SVars.showDeuterocanonical)
        {
          table->cellAt(row, C0).firstCursorPosition().insertHtml(QString("<font style=\"color:rgba(%1,%2,%3,%4);\"><i><b>%5</b></i></font>").arg(MW->MO->SVars.oldTestamentColorFA.red()).arg(MW->MO->SVars.oldTestamentColorFA.green()).arg(MW->MO->SVars.oldTestamentColorFA.blue()).arg(MW->MO->SVars.oldTestamentColorFA.alpha()).arg(MW->MO->bookMinNameArr[i])); // &nbsp; // Тук за алфа за прозрачност се използва цялото число alpha() = 150 (между 0 и 255), докато във HTML файловете за WEB браузърите трябва да се използва реалното число alphaF() = 0.6 (между 0 и 1)!
          row++;
        }
      }
      else
      {
        table->cellAt(row, C0).firstCursorPosition().insertHtml(QString("<font color=%1><b>%2</b></font>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->bookMinNameArr[i]));
        row++;
      }
    }
  }

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
  {
    table->cellAt(bookCodeToRowNumber[18]-1, C0).lastCursorPosition().insertHtml(QString("&nbsp;&nbsp;&nbsp;<font color=%1>•</font>").arg(MW->MO->SVars.dock2TextColorF.name())); // •● oldTestamentColorF dock2TextColorF
    table->cellAt(bookCodeToRowNumber[22]-1, C0).lastCursorPosition().insertHtml(QString("&nbsp;&nbsp;&nbsp;<font color=%1>•</font>").arg(MW->MO->SVars.dock2TextColorF.name())); // •●
    table->cellAt(bookCodeToRowNumber[55]-1, C0).lastCursorPosition().insertHtml(QString("&nbsp;&nbsp;&nbsp;<font color=%1>•</font>").arg(MW->MO->SVars.dock2TextColorF.name())); // •●
    table->cellAt(bookCodeToRowNumber[(MW->MO->SVars.currentBooksOrder == BOOKS_ORDER__WESTERN) ? 69 : 62]-1, C0).lastCursorPosition().insertHtml(QString("&nbsp;&nbsp;&nbsp;<font color=%1>•</font>").arg(MW->MO->SVars.dock2TextColorF.name())); // •●
  }

  textCursor().endEditBlock();

  setRowBackground(bookCode, chapterCode, bookCode, chapterCode, true);
  moveTable();
//QMessageBox::information(this, QString(""), QString("\n<<%1>>").arg(timer.elapsed())); // -------------------------------------------------------
}

void BooksWidget::setRowBackground(quint8 newBookCode, quint8 newChapterCode, quint8 oldBookCode, quint8 oldChapterCode, bool refresh)
{
  textCursor().beginEditBlock();

  if (newBookCode > 50)
    fo_ActiveBook = &fo_ActiveBookNew;
  else
    fo_ActiveBook = &fo_ActiveBookOld;

  if (oldBookCode != newBookCode || refresh) // Ако е сменена книгата или трябва да се рефрешне поради смяна на цветовете.
  {
    quint16 chaptersCount = MW->MO->chaptersCountArr[newBookCode-1]; // Брой на главите в новоизбраната книга.
    if (!MW->MO->SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити.
    {
      if (newBookCode==19) chaptersCount = chaptersCount - 1; // За да не се показва 151-ва глава от Псалми.
      if (newBookCode==27) chaptersCount = chaptersCount - 2; // За да не се показва 13-та и 14-та глава от Данаил.
    }
    quint16 tableRowsCount = bookCodeToRowNumber[newBookCode-1] + chaptersCount - 1; // Брой на редовете които трябва да съдържа таблицата.
    if (tableRowsCount < booksCount) tableRowsCount = booksCount; // Редовете не могат да бъдат по-малко от броя на всички книги в Библията.

    if (tableRowsCount > table->rows()) // Ако трябва да се добавят още редове.
      table->appendRows(tableRowsCount - table->rows()); // Добавя нови редове.
    else if (table->rows() > tableRowsCount) // Ако трябва да се изтрият редове.
      table->removeRows(table->rows() - (table->rows() - tableRowsCount), table->rows() - tableRowsCount); // Изтрива ненужните редове.


    if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
    {
      table->removeColumns(1, 1); // Изтрива цялата колона.
      table->appendColumns(1); // Създава я отново празна. Това е защото не можах да разбера как се трие съдържанието на клетките в таблицата, но то пък така стана по-добре.
    }
    else
    {
      table->removeColumns(0, 1); // Изтрива цялата колона.
      table->insertColumns(0, 1); // Създава я отново празна. Това е защото не можах да разбера как се трие съдържанието на клетките в таблицата, но то пък така стана по-добре.
    }

    QTextTableFormat tableFormat = table->format();
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 90 : 10)
                << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 10 : 90);
    tableFormat.setColumnWidthConstraints(constraints);
    table->setFormat(tableFormat);

    int chapter = 0;
    for (int row = 0; row < table->rows(); row++)
    {
      table->cellAt(row, C0).setFormat(fo_InactiveBooks);
      table->cellAt(row, C1).firstCursorPosition().setBlockFormat(blockFormatCol2); // Формат на текста.

      if (row >= (bookCodeToRowNumber[newBookCode-1] - 1) && chapter < chaptersCount)
      {
        chapter++;
        table->cellAt(row, C1).setFormat(*fo_ActiveBook); // Формат на фона.
        if ( (newBookCode==19 && chapter==151) || (newBookCode==27 && (chapter==13 || chapter==14)) )
        {
          table->cellAt(row, C1).firstCursorPosition().insertHtml(QString("<font color=%1><i>%2</i></font>").arg(MW->MO->SVars.dock2TextColorF.name()).arg(chapter));
        }
        else
        {
          table->cellAt(row, C1).firstCursorPosition().insertHtml(QString("<font color=%1>%2</font>").arg(MW->MO->SVars.dock2TextColorF.name()).arg(chapter));
        }
      }
      else
      {
        table->cellAt(row, C1).setFormat(fo_InactiveBooks);
        table->cellAt(row, C1).firstCursorPosition().insertHtml(QString("<font color=%1>0 0</font>").arg(MW->MO->SVars.dock2TextColorB.name())); // Тези нули се поставят, защото когато числото е едноцифрено ширината на клетките става по-малка и така е винаги еднаква.
      }
    }

    table->cellAt(bookCodeToRowNumber[newBookCode-1] - 1, C0).setFormat(*fo_ActiveBook);
  }
  else // Ако само главата е сменена.
  {
    table->cellAt(bookCodeToRowNumber[newBookCode-1] + oldChapterCode - 2, C1).setFormat(*fo_ActiveBook);
  }

  if (newBookCode > 50)
  {
    table->cellAt(bookCodeToRowNumber[newBookCode-1] + newChapterCode - 2, C1).setFormat(fo_CurrentChapterNew);
  }
  else
  {
    table->cellAt(bookCodeToRowNumber[newBookCode-1] + newChapterCode - 2, C1).setFormat(fo_CurrentChapterOld);
  }

  textCursor().endEditBlock();
}

void BooksWidget::moveTable()
{
  // Следващите редове правят така, че текущия номер на глава да се покаже на екрана, в случай че не се вижда.
  int absolutePosition = table->cellAt(bookCodeToRowNumber[bookCode-1] + chapterCode - 2, C1).firstCursorPosition().position();
  QTextCursor c = textCursor();
  c.setPosition(absolutePosition, QTextCursor::MoveAnchor); // Премества курсора в началото (но без да мести текста).
  setTextCursor(c); // Премества курсора, върху номера на главата, като мести и текста ако не се вижда (което е целта).
}

void BooksWidget::mousePressEvent(QMouseEvent *event)
{
  QTextBrowser::mousePressEvent(event);

  quint8  newBookCode = bookCode;
  quint8  newChapterCode = chapterCode;
  QString str = textCursor().block().text();
  quint32 num = str.toUInt(); // Това ще върне 0, ако е щракнато върху текст т.е. име на глава.

  if (str == "0 0" || str == "") // Ако е щракнато върху празна клетка.
  {
    return;
  }
  else if (str.length() > 1 && num == 0) // Ако е щракнато върху име на книга.
  {
    newBookCode = textCursor().blockNumber() / 2 + ((MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 1 : 0);
    newBookCode = rowNumberToBookCode[newBookCode - 1]; // Това в случай, че са скрити Второканоничните книги.
    newChapterCode = 1;
  }
  else if (num > 0) // Ако е щракнато върху номер на глава.
  {
    newBookCode = bookCode;
    newChapterCode = num;
  }

  if (MW->ctrlKeyPressed) // Ако е натиснат клавиш Ctrl по време на кликването.
  {
    MW->newHDock(false, -1, -1, 0, QBitArray(), 0, MW->MO->toAbsIndex(newBookCode, newChapterCode, 1)); // Отваря нов прозорец и показва главата в него. Четвъртия параметър трябва да е 0.
    MW->ctrlKeyPressed = false; // Сваля флага, защото този прозорец вече не е на фокус и не може да прихване keyReleaseEvent-а който отговаря за свалянето на флага.
  }
  else // Ако не е натиснат клавиш Ctrl по време на кликването.
  {
    MW->switchToNormalMode(); // След този ред bookCode и chapterCode може да са се променили.
    if (newBookCode != bookCode || newChapterCode != chapterCode)
    {
      MW->currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
      MW->currentHolyTextView->showBibleText(MW->MO->toAbsIndex(newBookCode, newChapterCode, 1));
    }
  }
}

void BooksWidget::mouseReleaseEvent(QMouseEvent *event)
{
  QTextBrowser::mouseReleaseEvent(event);

  if (textCursor().hasSelection())
  {
    moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor); // Това премахва селекцията.
    moveTable();
  }
}

void BooksWidget::setCurrentCodes(quint8 newBookCode, quint8 newChapterCode)
{
  if (bookCode == newBookCode && chapterCode == newChapterCode) return;
  setRowBackground(newBookCode, newChapterCode, bookCode, chapterCode, false);

  bookCode = newBookCode;
  chapterCode = newChapterCode;

  moveTable();
}

void BooksWidget::slotRefreshPalette()
{
  initTable();
}

// =========================================================================================================================================================
/*
BooksTreeWidget::BooksTreeWidget(MainWindow *MW) : QTreeWidget()
{
  this->MW = MW;
  testamentCode = 0;
  bookCode = 0;
  chapterCode = 0;

  //setAnimated(true); // Това прави плавно отваряне на дървото, но в конзолата се изписват следните съобщения: QPainter::begin: Cannot paint on a null pixmap    QPainter::translate: Painter not active   QPainter::end: Painter not active, aborted

//QTime StartTime1, StopTime1;
//StartTime1 = QTime::currentTime();
  QTreeWidgetItem *headerItem = new QTreeWidgetItem;
  setHeaderHidden(true); // Това скрива заглавието.
  headerItem->setText(0, tr("Книги:"));
  setHeaderItem(headerItem);

  QFont font; font.setBold(true);

  OldTestamentItem = new QTreeWidgetItem;
  OldTestamentItem->setText(0, tr("Стар Завет"));
  OldTestamentItem->setFont(0, font);
  OldTestamentItem->setForeground(0, QColor(255,124,0));
  OldTestamentItem->setIcon(0, QIcon(":/resources/images/oldbooks16.png"));
  addTopLevelItem(OldTestamentItem);
  OldTestamentItem->setExpanded(true);

  NewTestamentItem = new QTreeWidgetItem;
  NewTestamentItem->setText(0, tr("Нов Завет"));
  NewTestamentItem->setFont(0, font);
  NewTestamentItem->setForeground(0, QColor(255,124,0));
  NewTestamentItem->setIcon(0, QIcon(":/resources/images/newbooks16.png"));
  addTopLevelItem(NewTestamentItem);
  NewTestamentItem->setExpanded(true);


  // Star Zavet
  QList<QTreeWidgetItem *> OldItems;
  for (int i = 0; i < 50; i++)
  {
    item = new QTreeWidgetItem(OldTestamentItem);
    item->setForeground(0, QColor(0, 128, 255));
    item->setIcon(0, QIcon(":/resources/images/oldbooks16.png"));
    OldItems.append(item);
  }
  insertTopLevelItems(0, OldItems);

  // Now Zavet
  QList<QTreeWidgetItem *> NewItems;
  for (int i = 0; i < 27; i++)
  {
    item = new QTreeWidgetItem(NewTestamentItem);
    item->setForeground(0, QColor(255, 0, 0));
    item->setIcon(0, QIcon(":/resources/images/newbooks16.png"));
    NewItems.append(item);
  }
  insertTopLevelItems(0, NewItems);

  // Star Zavet
  OldItems[0]->setText(0, MW->MO->bookShortNameArr[0]);
      QList<QTreeWidgetItem *> OldItems0;
      setChapters(OldItems[0], OldItems0, MW->MO->chaptersCountArr[0], true);
  OldItems[1]->setText(0, MW->MO->bookShortNameArr[1]);
      QList<QTreeWidgetItem *> OldItems1;
      setChapters(OldItems[1], OldItems1, MW->MO->chaptersCountArr[1], true);
  OldItems[2]->setText(0, MW->MO->bookShortNameArr[2]);
      QList<QTreeWidgetItem *> OldItems2;
      setChapters(OldItems[2], OldItems2, MW->MO->chaptersCountArr[2], true);
  OldItems[3]->setText(0, MW->MO->bookShortNameArr[3]);
      QList<QTreeWidgetItem *> OldItems3;
      setChapters(OldItems[3], OldItems3, MW->MO->chaptersCountArr[3], true);
  OldItems[4]->setText(0, MW->MO->bookShortNameArr[4]);
      QList<QTreeWidgetItem *> OldItems4;
      setChapters(OldItems[4], OldItems4, MW->MO->chaptersCountArr[4], true);
  OldItems[5]->setText(0, MW->MO->bookShortNameArr[5]);
      QList<QTreeWidgetItem *> OldItems5;
      setChapters(OldItems[5], OldItems5, MW->MO->chaptersCountArr[5], true);
  OldItems[6]->setText(0, MW->MO->bookShortNameArr[6]);
      QList<QTreeWidgetItem *> OldItems6;
      setChapters(OldItems[6], OldItems6, MW->MO->chaptersCountArr[6], true);
  OldItems[7]->setText(0, MW->MO->bookShortNameArr[7]);
      QList<QTreeWidgetItem *> OldItems7;
      setChapters(OldItems[7], OldItems7, MW->MO->chaptersCountArr[7], true);
  OldItems[8]->setText(0, MW->MO->bookShortNameArr[8]);
      QList<QTreeWidgetItem *> OldItems8;
      setChapters(OldItems[8], OldItems8, MW->MO->chaptersCountArr[8], true);
  OldItems[9]->setText(0, MW->MO->bookShortNameArr[9]);
      QList<QTreeWidgetItem *> OldItems9;
      setChapters(OldItems[9], OldItems9, MW->MO->chaptersCountArr[9], true);
  OldItems[10]->setText(0, MW->MO->bookShortNameArr[10]);
      QList<QTreeWidgetItem *> OldItems10;
      setChapters(OldItems[10], OldItems10, MW->MO->chaptersCountArr[10], true);
  OldItems[11]->setText(0, MW->MO->bookShortNameArr[11]);
      QList<QTreeWidgetItem *> OldItems11;
      setChapters(OldItems[11], OldItems11, MW->MO->chaptersCountArr[11], true);
  OldItems[12]->setText(0, MW->MO->bookShortNameArr[12]);
      QList<QTreeWidgetItem *> OldItems12;
      setChapters(OldItems[12], OldItems12, MW->MO->chaptersCountArr[12], true);
  OldItems[13]->setText(0, MW->MO->bookShortNameArr[13]);
      QList<QTreeWidgetItem *> OldItems13;
      setChapters(OldItems[13], OldItems13, MW->MO->chaptersCountArr[13], true);
  OldItems[14]->setText(0, MW->MO->bookShortNameArr[14]);
      QList<QTreeWidgetItem *> OldItems14;
      setChapters(OldItems[14], OldItems14, MW->MO->chaptersCountArr[14], true);
  OldItems[15]->setText(0, MW->MO->bookShortNameArr[15]);
      QList<QTreeWidgetItem *> OldItems15;
      setChapters(OldItems[15], OldItems15, MW->MO->chaptersCountArr[15], true);
  OldItems[16]->setText(0, "["+MW->MO->bookShortNameArr[16]+"]");
      QList<QTreeWidgetItem *> OldItems16;
      setChapters(OldItems[16], OldItems16, MW->MO->chaptersCountArr[16], true);
  OldItems[17]->setText(0, "["+MW->MO->bookShortNameArr[17]+"]");
      QList<QTreeWidgetItem *> OldItems17;
      setChapters(OldItems[17], OldItems17, MW->MO->chaptersCountArr[17], true);
  OldItems[18]->setText(0, "["+MW->MO->bookShortNameArr[18]+"]");
      QList<QTreeWidgetItem *> OldItems18;
      setChapters(OldItems[18], OldItems18, MW->MO->chaptersCountArr[18], true);
  OldItems[19]->setText(0, MW->MO->bookShortNameArr[19]);
      QList<QTreeWidgetItem *> OldItems19;
      setChapters(OldItems[19], OldItems19, MW->MO->chaptersCountArr[19], true);
  OldItems[20]->setText(0, MW->MO->bookShortNameArr[20]);
      QList<QTreeWidgetItem *> OldItems20;
      setChapters(OldItems[20], OldItems20, MW->MO->chaptersCountArr[20], true);
  OldItems[21]->setText(0, MW->MO->bookShortNameArr[21]);
  OldItems[21]->setFont(0, font);
      QList<QTreeWidgetItem *> OldItems21;
      setChapters(OldItems[21], OldItems21, MW->MO->chaptersCountArr[21], true);
      OldItems[21]->child(150)->setText(0, QString("[151]"));
  OldItems[22]->setText(0, MW->MO->bookShortNameArr[22]);
      QList<QTreeWidgetItem *> OldItems22;
      setChapters(OldItems[22], OldItems22, MW->MO->chaptersCountArr[22], true);
  OldItems[23]->setText(0, MW->MO->bookShortNameArr[23]);
      QList<QTreeWidgetItem *> OldItems23;
      setChapters(OldItems[23], OldItems23, MW->MO->chaptersCountArr[23], true);
  OldItems[24]->setText(0, MW->MO->bookShortNameArr[24]);
      QList<QTreeWidgetItem *> OldItems24;
      setChapters(OldItems[24], OldItems24, MW->MO->chaptersCountArr[24], true);
  OldItems[25]->setText(0, "["+MW->MO->bookShortNameArr[25]+"]");
      QList<QTreeWidgetItem *> OldItems25;
      setChapters(OldItems[25], OldItems25, MW->MO->chaptersCountArr[25], true);
  OldItems[26]->setText(0, "["+MW->MO->bookShortNameArr[26]+"]");
      QList<QTreeWidgetItem *> OldItems26;
      setChapters(OldItems[26], OldItems26, MW->MO->chaptersCountArr[26], true);
  OldItems[27]->setText(0, MW->MO->bookShortNameArr[27]);
      QList<QTreeWidgetItem *> OldItems27;
      setChapters(OldItems[27], OldItems27, MW->MO->chaptersCountArr[27], true);
  OldItems[28]->setText(0, MW->MO->bookShortNameArr[28]);
      QList<QTreeWidgetItem *> OldItems28;
      setChapters(OldItems[28], OldItems28, MW->MO->chaptersCountArr[28], true);
  OldItems[29]->setText(0, MW->MO->bookShortNameArr[29]);
      QList<QTreeWidgetItem *> OldItems29;
      setChapters(OldItems[29], OldItems29, MW->MO->chaptersCountArr[29], true);
  OldItems[30]->setText(0, "["+MW->MO->bookShortNameArr[30]+"]");
      QList<QTreeWidgetItem *> OldItems30;
      setChapters(OldItems[30], OldItems30, MW->MO->chaptersCountArr[30], true);
  OldItems[31]->setText(0, "["+MW->MO->bookShortNameArr[31]+"]");
      QList<QTreeWidgetItem *> OldItems31;
      setChapters(OldItems[31], OldItems31, MW->MO->chaptersCountArr[31], true);
  OldItems[32]->setText(0, MW->MO->bookShortNameArr[32]);
      QList<QTreeWidgetItem *> OldItems32;
      setChapters(OldItems[32], OldItems32, MW->MO->chaptersCountArr[32], true);
  OldItems[33]->setText(0, MW->MO->bookShortNameArr[33]);
      QList<QTreeWidgetItem *> OldItems33;
      setChapters(OldItems[33], OldItems33, MW->MO->chaptersCountArr[33], true);
      OldItems[33]->child(12)->setText(0, QString("[13]"));
      OldItems[33]->child(13)->setText(0, QString("[14]"));
  OldItems[34]->setText(0, MW->MO->bookShortNameArr[34]);
      QList<QTreeWidgetItem *> OldItems34;
      setChapters(OldItems[34], OldItems34, MW->MO->chaptersCountArr[34], true);
  OldItems[35]->setText(0, MW->MO->bookShortNameArr[35]);
      QList<QTreeWidgetItem *> OldItems35;
      setChapters(OldItems[35], OldItems35, MW->MO->chaptersCountArr[35], true);
  OldItems[36]->setText(0, MW->MO->bookShortNameArr[36]);
      QList<QTreeWidgetItem *> OldItems36;
      setChapters(OldItems[36], OldItems36, MW->MO->chaptersCountArr[36], true);
  OldItems[37]->setText(0, MW->MO->bookShortNameArr[37]);
      QList<QTreeWidgetItem *> OldItems37;
      setChapters(OldItems[37], OldItems37, MW->MO->chaptersCountArr[37], true);
  OldItems[38]->setText(0, MW->MO->bookShortNameArr[38]);
      QList<QTreeWidgetItem *> OldItems38;
      setChapters(OldItems[38], OldItems38, MW->MO->chaptersCountArr[38], true);
  OldItems[39]->setText(0, MW->MO->bookShortNameArr[39]);
      QList<QTreeWidgetItem *> OldItems39;
      setChapters(OldItems[39], OldItems39, MW->MO->chaptersCountArr[39], true);
  OldItems[40]->setText(0, MW->MO->bookShortNameArr[40]);
      QList<QTreeWidgetItem *> OldItems40;
      setChapters(OldItems[40], OldItems40, MW->MO->chaptersCountArr[40], true);
  OldItems[41]->setText(0, MW->MO->bookShortNameArr[41]);
      QList<QTreeWidgetItem *> OldItems41;
      setChapters(OldItems[41], OldItems41, MW->MO->chaptersCountArr[41], true);
  OldItems[42]->setText(0, MW->MO->bookShortNameArr[42]);
      QList<QTreeWidgetItem *> OldItems42;
      setChapters(OldItems[42], OldItems42, MW->MO->chaptersCountArr[42], true);
  OldItems[43]->setText(0, MW->MO->bookShortNameArr[43]);
      QList<QTreeWidgetItem *> OldItems43;
      setChapters(OldItems[43], OldItems43, MW->MO->chaptersCountArr[43], true);
  OldItems[44]->setText(0, MW->MO->bookShortNameArr[44]);
      QList<QTreeWidgetItem *> OldItems44;
      setChapters(OldItems[44], OldItems44, MW->MO->chaptersCountArr[44], true);
  OldItems[45]->setText(0, MW->MO->bookShortNameArr[45]);
      QList<QTreeWidgetItem *> OldItems45;
      setChapters(OldItems[45], OldItems45, MW->MO->chaptersCountArr[45], true);
  OldItems[46]->setText(0, "["+MW->MO->bookShortNameArr[46]+"]");
      QList<QTreeWidgetItem *> OldItems46;
      setChapters(OldItems[46], OldItems46, MW->MO->chaptersCountArr[46], true);
  OldItems[47]->setText(0, "["+MW->MO->bookShortNameArr[47]+"]");
      QList<QTreeWidgetItem *> OldItems47;
      setChapters(OldItems[47], OldItems47, MW->MO->chaptersCountArr[47], true);
  OldItems[48]->setText(0, "["+MW->MO->bookShortNameArr[48]+"]");
      QList<QTreeWidgetItem *> OldItems48;
      setChapters(OldItems[48], OldItems48, MW->MO->chaptersCountArr[48], true);
  OldItems[49]->setText(0, "["+MW->MO->bookShortNameArr[49]+"]");
      QList<QTreeWidgetItem *> OldItems49;
      setChapters(OldItems[49], OldItems49, MW->MO->chaptersCountArr[49], true);

  // Now Zavet
  NewItems[0]->setText(0, MW->MO->bookShortNameArr[50]);
      QList<QTreeWidgetItem *> NewItems0;
      setChapters(NewItems[0], NewItems0, MW->MO->chaptersCountArr[50], false);
  NewItems[1]->setText(0, MW->MO->bookShortNameArr[51]);
      QList<QTreeWidgetItem *> NewItems1;
      setChapters(NewItems[1], NewItems1, MW->MO->chaptersCountArr[51], false);
  NewItems[2]->setText(0, MW->MO->bookShortNameArr[52]);
      QList<QTreeWidgetItem *> NewItems2;
      setChapters(NewItems[2], NewItems2, MW->MO->chaptersCountArr[52], false);
  NewItems[3]->setText(0, MW->MO->bookShortNameArr[53]);
      QList<QTreeWidgetItem *> NewItems3;
      setChapters(NewItems[3], NewItems3, MW->MO->chaptersCountArr[53], false);
  NewItems[4]->setText(0, MW->MO->bookShortNameArr[54]);
      QList<QTreeWidgetItem *> NewItems4;
      setChapters(NewItems[4], NewItems4, MW->MO->chaptersCountArr[54], false);
  NewItems[5]->setText(0, MW->MO->bookShortNameArr[55]);
      QList<QTreeWidgetItem *> NewItems5;
      setChapters(NewItems[5], NewItems5, MW->MO->chaptersCountArr[55], false);
  NewItems[6]->setText(0, MW->MO->bookShortNameArr[56]);
      QList<QTreeWidgetItem *> NewItems6;
      setChapters(NewItems[6], NewItems6, MW->MO->chaptersCountArr[56], false);
  NewItems[7]->setText(0, MW->MO->bookShortNameArr[57]);
      QList<QTreeWidgetItem *> NewItems7;
      setChapters(NewItems[7], NewItems7, MW->MO->chaptersCountArr[57], false);
  NewItems[8]->setText(0, MW->MO->bookShortNameArr[58]);
      QList<QTreeWidgetItem *> NewItems8;
      setChapters(NewItems[8], NewItems8, MW->MO->chaptersCountArr[58], false);
  NewItems[9]->setText(0, MW->MO->bookShortNameArr[59]);
      QList<QTreeWidgetItem *> NewItems9;
      setChapters(NewItems[9], NewItems9, MW->MO->chaptersCountArr[59], false);
  NewItems[10]->setText(0, MW->MO->bookShortNameArr[60]);
      QList<QTreeWidgetItem *> NewItems10;
      setChapters(NewItems[10], NewItems10, MW->MO->chaptersCountArr[60], false);
  NewItems[11]->setText(0, MW->MO->bookShortNameArr[61]);
      QList<QTreeWidgetItem *> NewItems11;
      setChapters(NewItems[11], NewItems11, MW->MO->chaptersCountArr[61], false);
  NewItems[12]->setText(0, MW->MO->bookShortNameArr[62]);
      QList<QTreeWidgetItem *> NewItems12;
      setChapters(NewItems[12], NewItems12, MW->MO->chaptersCountArr[62], false);
  NewItems[13]->setText(0, MW->MO->bookShortNameArr[63]);
      QList<QTreeWidgetItem *> NewItems13;
      setChapters(NewItems[13], NewItems13, MW->MO->chaptersCountArr[63], false);
  NewItems[14]->setText(0, MW->MO->bookShortNameArr[64]);
      QList<QTreeWidgetItem *> NewItems14;
      setChapters(NewItems[14], NewItems14, MW->MO->chaptersCountArr[64], false);
  NewItems[15]->setText(0, MW->MO->bookShortNameArr[65]);
      QList<QTreeWidgetItem *> NewItems15;
      setChapters(NewItems[15], NewItems15, MW->MO->chaptersCountArr[65], false);
  NewItems[16]->setText(0, MW->MO->bookShortNameArr[66]);
      QList<QTreeWidgetItem *> NewItems16;
      setChapters(NewItems[16], NewItems16, MW->MO->chaptersCountArr[66], false);
  NewItems[17]->setText(0, MW->MO->bookShortNameArr[67]);
      QList<QTreeWidgetItem *> NewItems17;
      setChapters(NewItems[17], NewItems17, MW->MO->chaptersCountArr[67], false);
  NewItems[18]->setText(0, MW->MO->bookShortNameArr[68]);
      QList<QTreeWidgetItem *> NewItems18;
      setChapters(NewItems[18], NewItems18, MW->MO->chaptersCountArr[68], false);
  NewItems[19]->setText(0, MW->MO->bookShortNameArr[69]);
      QList<QTreeWidgetItem *> NewItems19;
      setChapters(NewItems[19], NewItems19, MW->MO->chaptersCountArr[69], false);
  NewItems[20]->setText(0, MW->MO->bookShortNameArr[70]);
      QList<QTreeWidgetItem *> NewItems20;
      setChapters(NewItems[20], NewItems20, MW->MO->chaptersCountArr[70], false);
  NewItems[21]->setText(0, MW->MO->bookShortNameArr[71]);
      QList<QTreeWidgetItem *> NewItems21;
      setChapters(NewItems[21], NewItems21, MW->MO->chaptersCountArr[71], false);
  NewItems[22]->setText(0, MW->MO->bookShortNameArr[72]);
      QList<QTreeWidgetItem *> NewItems22;
      setChapters(NewItems[22], NewItems22, MW->MO->chaptersCountArr[72], false);
  NewItems[23]->setText(0, MW->MO->bookShortNameArr[73]);
      QList<QTreeWidgetItem *> NewItems23;
      setChapters(NewItems[23], NewItems23, MW->MO->chaptersCountArr[73], false);
  NewItems[24]->setText(0, MW->MO->bookShortNameArr[74]);
      QList<QTreeWidgetItem *> NewItems24;
      setChapters(NewItems[24], NewItems24, MW->MO->chaptersCountArr[74], false);
  NewItems[25]->setText(0, MW->MO->bookShortNameArr[75]);
      QList<QTreeWidgetItem *> NewItems25;
      setChapters(NewItems[25], NewItems25, MW->MO->chaptersCountArr[75], false);
  NewItems[26]->setText(0, MW->MO->bookShortNameArr[76]);
      QList<QTreeWidgetItem *> NewItems26;
      setChapters(NewItems[26], NewItems26, MW->MO->chaptersCountArr[76], false);

  resizeColumnToContents(0);
//StopTime1 = QTime::currentTime();
//QMessageBox::information(this, QString(""), QString("\n<<%1>>").arg((StopTime1.minute()*60000+StopTime1.second()*1000+StopTime1.msec())-(StartTime1.minute()*60000+StartTime1.second()*1000+StartTime1.msec())));
}

void BooksTreeWidget::setChapters(QTreeWidgetItem *parentItem, QList<QTreeWidgetItem *> items, quint8 chaptersCount, bool isOldTestament)
{
  for (int i = 0; i < chaptersCount; i++)
  {
    QFont font;
    //font.setItalic(true);
    //font.setUnderline(true);

    item = new QTreeWidgetItem(parentItem);
    item->setText(0, QString("%1").arg(i+1));
    //item->setForeground(0, QColor(255, 0, 0));
    item->setFont(0, font);
    if (isOldTestament)
      item->setIcon(0, QIcon(":/resources/images/oldbook16.png"));
    else
      item->setIcon(0, QIcon(":/resources/images/newbook16.png"));
    items.append(item);
  }
  insertTopLevelItems(0, items);
}

void BooksTreeWidget::mousePressEvent(QMouseEvent *event)
{
  QTreeWidget::mousePressEvent(event);

  QTreeWidgetItem *cItem = currentItem();
  if (cItem->parent() == 0) return;
  showBibleText(cItem);
}

void BooksTreeWidget::keyPressEvent(QKeyEvent *event)
{
  QTreeWidget::keyPressEvent(event);

  QTreeWidgetItem *cItem = currentItem();
  if (event->key() != Qt::Key_Return  &&  event->key() != Qt::Key_Space  &&  event->key() != Qt::Key_Enter) return;
  if (cItem->parent() == 0) return;
  showBibleText(cItem);
}

void BooksTreeWidget::showBibleText(QTreeWidgetItem *cItem)
{
  quint8 oldTestamentCode = testamentCode;
  quint8 oldBookCode = bookCode;
  quint8 oldChapterCode = chapterCode;

  if (cItem->parent()->parent() != 0)
  {
    testamentCode = indexOfTopLevelItem(cItem->parent()->parent()) + 1;
    bookCode = cItem->parent()->parent()->indexOfChild(cItem->parent()) + 1;
    if (testamentCode == TESTAMENT__NEW) bookCode += 50;
    chapterCode = cItem->parent()->indexOfChild(cItem) + 1;
  }
  else
  {
    testamentCode = indexOfTopLevelItem(cItem->parent()) + 1;
    bookCode = cItem->parent()->indexOfChild(cItem) + 1;
    if (testamentCode == TESTAMENT__NEW) bookCode += 50;
    chapterCode = 1;
  }

  if ( oldTestamentCode != testamentCode || oldBookCode != bookCode || oldChapterCode != chapterCode )
  {
    MW->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    MW->showBibleText(testamentCode, bookCode, chapterCode, 1);
  }
}

void BooksTreeWidget::setCurrentCodes(quint8 newTestamentCode, quint8 newBookCode, quint8 newChapterCode)
{
  if (currentItem() != 0 && currentItem()->isSelected()) currentItem()->setSelected(false);
  testamentCode = newTestamentCode;
  bookCode = newBookCode;
  chapterCode = newChapterCode;
  if (newTestamentCode == TESTAMENT__NEW) newBookCode -= 50;
  QTreeWidgetItem *item = topLevelItem(newTestamentCode-1)->child(newBookCode-1)->child(newChapterCode-1);
  item->setSelected(true);
  setCurrentItem(item);
}
*/
// =========================================================================================================================================================
/*
BooksLinkWidget::BooksLinkWidget(MainWindow *MW) : QTextBrowser()
{
  this->MW = MW;
  testamentCode = 0;
  bookCode = 0;
  chapterCode = 0;
  stringPosition = -1;

  setOpenExternalLinks(false);
  setOpenLinks(false);
  setReadOnly(true);
  setContextMenuPolicy(Qt::NoContextMenu);
  setContentsMargins(0, 0, 0, 0); // left, top, right, bottom
  document()->setDocumentMargin(2);
  connect(this, SIGNAL(anchorClicked (const QUrl &)), this, SLOT(slotAnchorClicked(const QUrl &)));

  setBooksLinkPalette(MW->MO->SVars.dock2TextColorF, MW->MO->SVars.dock2TextColorB);

//QTime timer; timer.start(); //---------------------------------------------------------------------------------------------------------
  if (MW->MO->SVars.treeToolBarView == TREE_TOOL_BAR_VIEW__LINK_1)
  {
    init1(); // Цветен фон, едноцветни линкове.
  }
  else // MW->MO->SVars.treeToolBarView == TREE_TOOL_BAR_VIEW__LINK_2
  {
    init2(); // Цветни линкове, едноцветен фон.
  }
//QMessageBox::information(this, QString(""), QString("\n<<%1>>").arg(timer.elapsed())); // -------------------------------------------------------
}

void BooksLinkWidget::setBooksLinkPalette(QColor textColor, QColor baseColor)
{
  QPalette palette = this->palette();
  palette.setBrush(QPalette::Text, textColor); // Цвят на текста.
  palette.setBrush(QPalette::Base, baseColor); // Цвят на фона.
  palette.setBrush(QPalette::Inactive, QPalette::Highlight, palette.brush(QPalette::Active, QPalette::Highlight)); // Цвят на неактивната селекция (прави се да е като цвета на активната).
  palette.setBrush(QPalette::Active, QPalette::HighlightedText, MW->MO->SVars.dock2TextColorB); // Цвят на активния селектиран текст (прави се да е като цвета на фона).
  palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, MW->MO->SVars.dock2TextColorB); // Цвят на неактивния селектиран текст (прави се да е като цвета на фона).
  setPalette(palette);
}

void BooksLinkWidget::init1()
{
  // Цветен фон, едноцветни линкове.

  QString text = QString("<style type=\"text/css\"> a:link {color: %1; text-decoration: none;} a:hover {color: #ff0000; text-decoration: underline overline;} </style>").arg(MW->MO->SVars.dock2TextColorF.name()); // Това е цветът на линковете. //textInBracketsColorF
  text += QString("<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"2\" cellspacing=\"0\"><tbody>");
  for(quint16 i = 0; i < 77; i++)
  {
    if (i < 5) // Петокнижие.
      text += QString("<tr><td style=\"background-color: %1\">").arg(MW->MO->SVars.foundWordsColor5B.name());
    else if (i > 20 && i < 23) // Псалми и Притчи.
     text += QString("<tr><td style=\"background-color: %1\">").arg(MW->MO->SVars.foundWordsColor4B.name());
    else if (i > 26 && i < 50) // Пророци.
      text += QString("<tr><td style=\"background-color: %1\">").arg(MW->MO->SVars.foundWordsColor3B.name());
    else if (i > 49 && i < 54) // Евангелие.
      text += QString("<tr><td style=\"background-color: %1\">").arg(MW->MO->SVars.foundWordsColor2B.name());
    else if (i > 61 && i < 76) // Павлови книги.
      text += QString("<tr><td style=\"background-color: %1\">").arg(MW->MO->SVars.foundWordsColor1B.name());
    else // Всички останали книги.
      text += QString("<tr><td>"); // tr-red   td-kolona

    if (i >= 50)
    {
      text += QString("<font color=%1><b>%2</b></font><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->bookShortNameArr[i]);
    }
    else
    {
      if (i == 16 || i == 17 || i == 18 || i == 25 || i == 26 || i == 30 || i == 31 || i >= 46)
        text += QString("<font color=%1><b>[%2]</b></font><br>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->bookShortNameArr[i]);
      else
        text += QString("<font color=%1><b>%2</b></font><br>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->bookShortNameArr[i]);
    }

    for(quint16 j = 0; j < MW->MO->chaptersCountArr[i]; j++)
    {
      if ( (i==21 && j==150) || (i==33 && (j==12 || j==13)) )
        text += QString("<a href=\"%1.%2\">[%2] </a>").arg(i+1).arg(j+1);
      else
        text += QString("<a href=\"%1.%2\">%2 </a>").arg(i+1).arg(j+1);
    }
    text += QString("</td></tr>");
  }
  text += QString("</tbody></table>");
  setHtml(text);
}

void BooksLinkWidget::init2()
{
  // Цветни линкове, едноцветен фон.

  QString text = QString("<style type=\"text/css\"> .c5 {color: %1;} .c4 {color: %2;} .c3 {color: %3;} .c2 {color: %4;} .c1 {color: %5;} .c0 {color: %6;} a:link {text-decoration: none;} a:hover {color: #ff0000; text-decoration: underline overline;} </style>").arg(MW->MO->SVars.foundWordsColor5F.name()).arg(MW->MO->SVars.foundWordsColor4F.name()).arg(MW->MO->SVars.foundWordsColor3F.name()).arg(MW->MO->SVars.foundWordsColor2F.name()).arg(MW->MO->SVars.foundWordsColor1F.name()).arg(MW->MO->SVars.dock2TextColorF.name()); // Това е цветът на линковете.
  text += QString("<table style=\"text-align: left; width: 100%;\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tbody>");
  for(quint16 i = 0; i < 77; i++)
  {
    text += QString("<tr><td>"); // tr-red   td-kolona

    QString colorClass;
    if (i < 5) // Петокнижие.
      colorClass = QString("class=c5");
    else if (i > 20 && i < 23) // Псалми и Притчи.
      colorClass = QString("class=c4");
    else if (i > 26 && i < 50) // Пророци.
      colorClass = QString("class=c3");
    else if (i > 49 && i < 54) // Евангелие.
      colorClass = QString("class=c2");
    else if (i > 61 && i < 76) // Павлови книги.
      colorClass = QString("class=c1");
    else // Всички останали книги.
      colorClass = QString("class=c0");

    if (i >= 50)
    {
      text += QString("<font %1><b>%2</b></font><br>").arg(colorClass).arg(MW->MO->bookShortNameArr[i]);
    }
    else
    {
      if (i == 16 || i == 17 || i == 18 || i == 25 || i == 26 || i == 30 || i == 31 || i >= 46)
        text += QString("<font %1><b>[%2]</b></font><br>").arg(colorClass).arg(MW->MO->bookShortNameArr[i]);
      else
        text += QString("<font %1><b>%2</b></font><br>").arg(colorClass).arg(MW->MO->bookShortNameArr[i]);
    }

    for(quint16 j = 0; j < MW->MO->chaptersCountArr[i]; j++)
    {
      if ( (i==21 && j==150) || (i==33 && (j==12 || j==13)) )
        text += QString("<a %1 href=\"%2.%3\">[%3] </a>").arg(colorClass).arg(i+1).arg(j+1);
      else
        text += QString("<a %1 href=\"%2.%3\">%3 </a>").arg(colorClass).arg(i+1).arg(j+1);
    }
    text += QString("</td></tr>");
  }
  text += QString("</tbody></table>");
  setHtml(text);
}

void BooksLinkWidget::slotAnchorClicked(const QUrl &link)
{
//QTime StartTime1, StopTime1;
//StartTime1 = QTime::currentTime();
  quint8 oldTestamentCode = testamentCode;
  quint8 oldBookCode = bookCode;
  quint8 oldChapterCode = chapterCode;

  QStringList bc = link.toString().split(QString("."));
  bookCode = (quint8)bc[0].toShort();
  chapterCode = (quint8)bc[1].toShort();
  QString sChapter = bc[1];
  if (bookCode > 50)
    testamentCode = TESTAMENT__NEW;
  else
    testamentCode = TESTAMENT__OLD;

  //  // Това са някакви неуспешни опити за оцветяване на текущата глава (по този начин се оцветява за 110 ms).
  //
  //  QTextBlock tb = document()->findBlockByNumber(book);
  //  //QFont font = tb.charFormat().font();
  //  //setFont(font);
  //  int p = tb.position();
  //  if (!p) return;
  //  QTextCursor tc = textCursor();
  //  //bool up = p > tc.position();
  //  tc.setPosition(p);
  //  tc.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
  //
  //  //QString h = tc.selection().toHtml();
  //  tc.select(QTextCursor::WordUnderCursor);
  //  h.replace(QString("color:#9999aa;\">%1<").arg(chapter), QString("color:#ff0000;\">%1<").arg(chapter));
  //  //h.replace("color:#9999aa;","color:#9999ff;");
  //  //h.replace("text-decoration: underline","text-decoration: none");
  //
  //  tc.insertHtml(h);
  //  //if (up) setTextCursor(tc);
  //  //tc.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
  //  //setTextCursor(tc);
  //
  //  //QMessageBox::information(this, QString(""), QString("--%1--").arg(h));

  // Селектира главата (използва се принципа на търсене на текст):
  QTextCursor c = textCursor();
  stringPosition = c.position() - 5;
  if (stringPosition < 0) stringPosition = 0;
  //QTextDocument *doc = document();
  //c.setPosition(stringPosition, QTextCursor::MoveAnchor);
  //c = doc->find(sChapter, c);
  //setTextCursor(c);

  if ( oldTestamentCode != testamentCode || oldBookCode != bookCode || oldChapterCode != chapterCode )
  {
    MW->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    MW->showBibleText(testamentCode, bookCode, chapterCode, 1);
  }
//StopTime1 = QTime::currentTime();
//QMessageBox::information(this, QString(""), QString("\n<<%1>>").arg((StopTime1.minute()*60000+StopTime1.second()*1000+StopTime1.msec())-(StartTime1.minute()*60000+StartTime1.second()*1000+StartTime1.msec())));
}

void BooksLinkWidget::mousePressEvent(QMouseEvent *event)
{
  QTextBrowser::mousePressEvent(event);
}

void BooksLinkWidget::mouseReleaseEvent(QMouseEvent *event)
{
  QTextBrowser::mouseReleaseEvent(event);

  if (stringPosition == -1) return;

  QString sChapter = QString("%1").arg(chapterCode);
  QTextDocument *doc = document();
  QTextCursor c = textCursor();
  c.setPosition(stringPosition, QTextCursor::MoveAnchor);
  c = doc->find(sChapter, c);
  setTextCursor(c);
}

void BooksLinkWidget::setCurrentCodes(quint8 newTestamentCode, quint8 newBookCode, quint8 newChapterCode)
{
  if (testamentCode == newTestamentCode && bookCode == newBookCode && chapterCode == newChapterCode) return;

  testamentCode = newTestamentCode;
  bookCode = newBookCode;
  chapterCode = newChapterCode;

  // Селектира главата (използва се принципа на търсене на текст):
  QTextDocument *doc = document();
  QTextCursor c = textCursor();
  c.setPosition(0, QTextCursor::MoveAnchor); // Премества курсора в началото (но без да мести текста).
  c = doc->find(MW->MO->bookShortNameArr[bookCode-1], c); // Търси името на книгата.
  setTextCursor(c); // Премества курсора, върху името на книгата (мести и текста, ако не се вижда).
  stringPosition = c.position(); // Взима текущата позиция на курсора.
  c = doc->find(QString("%1").arg(chapterCode), c); // Търси номера на главата и я селектира.
  setTextCursor(c); // Премества курсора, върху името на книгата (мести и текста, ако не се вижда).
}
*/

// ==========================================================================================================================================================

BooksToolBar::BooksToolBar(MainWindow *mainWindow, BooksWidget *booksWidget, FastAccessWidget *fastAccessWidget, QWidget *parent) : MDock(parent)
{
  this->MW = mainWindow;

  setDockWidgetTabbedTitleBar(true);
  setProperties(false, false, true, false);
  setDockGridState("0^100_1_0^100"); // Един ред с един раздел.
  setMinimumSize(1, 1); // Не трябва да е 0, защото няма ефект.

  QWidget *widget = new QWidget();
  widget->setMinimumSize(1, 1);
  widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  fastAccessWidget->setParent(widget);
  booksWidget->setParent(widget);

  QWidget *divider = new QWidget(); // Това ще служи като разделител, защото трябва цветът му да е като на фона на док-а.
  divider->setMinimumSize(1, 1);
  divider->setMinimumHeight(1);
  divider->setMaximumHeight(1);
  divider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QPalette dividerPalette = divider->palette();
  dividerPalette.setBrush(QPalette::Window, getDockBgColor()); // Ако се промени цветът на фона на док-а, цветът на този разделител няма да се промени веднага, а след рестарт, което не е проблем.
  divider->setPalette(dividerPalette);
  divider->setAutoFillBackground(true);

  QVBoxLayout *vLayout = new QVBoxLayout(widget);
  vLayout->setMargin(0);
  vLayout->setSpacing(0); // Разстояние между обектите. Нула е, защото се използва QWidget като разделител.
  vLayout->addWidget(fastAccessWidget);
  vLayout->addWidget(divider);
  vLayout->addWidget(booksWidget);

  mDockWidget = new MDockWidget(this, QString("<b>%1</b>").arg(MW->MO->TS->Books_v1), false, false, MW->MO->SVars.docks3DTitleBar, 1, 0);
  mDockWidget->setWidget(widget);
  mDockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само сигнал.
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  mDockWidget->setCloseBtnToolTip(MW->MO->TS->HideToolBar_v1);
  connect(mDockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotCloseDock(MDock *, MDockWidget *, int, quint8))); // Излъчения от Close бутона сигнал.

  addDockWidget(mDockWidget, 0, 0);

  QFont currfont = booksWidget->font();
  currfont.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  booksWidget->setFont(currfont);
  currfont = fastAccessWidget->font();
  currfont.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  fastAccessWidget->setFont(currfont);
  // F    6    7    8    9   10   11   12   14   16   18   20 - възможни размери на шрифта.
  // W  100  110  120  130  140  150  160  180  200  220  260 - широчина на тулбара за книгите.
  //
  // W = F * 10 + 40
  //
  int W = MW->MO->SVars.booksToolBarFontSize * 10 + 40;
  this->setMinimumWidth(W);
  this->setMaximumWidth(W);
  
  slotSetColors();
}

BooksToolBar::~BooksToolBar()
{
  delete mDockWidget;
}

void BooksToolBar::slotCloseDock(MDock */*dock*/, MDockWidget */*dockWidget*/, int /*dockWidgetID*/, quint8 /*dockWidgetType*/)
{
  //setVisible(false); // Това ще скрие (затвори) панела, но бутонът в TMenu няма да се отпусне.
  MW->mainToolBar->btnNavigation_Books->click(); // Това косвено ще извика setVisible(false).
}

void BooksToolBar::slotSetTitleBarFontSize()
{
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
}

void BooksToolBar::slotSetColors()
{
  setDockBgColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
}

void BooksToolBar::slotSet3DTitleBar()
{
  mDockWidget->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
}
