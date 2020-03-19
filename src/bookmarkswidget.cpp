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

#include "bookmarkswidget.h"

BookmarksWidget::BookmarksWidget(MainWindow *MW) : QTextBrowser()
{
  setReadOnly(true);
  setMinimumSize(1, 1); // Не трябва да е 0 защото няма ефект.
  setContextMenuPolicy(Qt::NoContextMenu);
  document()->setDocumentMargin(-1); // 2

  this->MW = MW;

  blockFormatCol0LtR.setNonBreakableLines(false); // Това позволява на текста да се изписва на два реда (иначе се показва скролбар и се скрива колоната с X-овете). Този ред може да се коментира, защото false е по подразбиране.
  blockFormatCol0RtL.setNonBreakableLines(false); // Това позволява на текста да се изписва на два реда (иначе се показва скролбар и се скрива колоната с X-овете). Този ред може да се коментира, защото false е по подразбиране.
  blockFormatCol0LtR.setAlignment(Qt::AlignLeft);
  blockFormatCol0RtL.setAlignment(Qt::AlignRight);
  blockFormatCol1.setNonBreakableLines(true); // Това не позволява на текста да се изписва на два реда.
  blockFormatCol1.setAlignment(Qt::AlignHCenter);

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

  initTable();
}

void BookmarksWidget::initTable()
{
  clear();
  textCursor().beginEditBlock();

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
  table = textCursor().insertTable(MAX_BOOKMARKS, 2, tableFormat);

  fo_AllBg.setBackground(MW->MO->SVars.dock2TextColorB);

  QString num;
  for (int i = 0; i < MAX_BOOKMARKS; i++)
  {
    num = (i < 10) ? QString("0%1").arg(i) : QString("%1").arg(i);
    num = QString("<sup><font color=%1><b>%2</b></font></sup>").arg(MW->MO->SVars.dock2TextColorF.name()).arg(num); // &nbsp;

    table->cellAt(i, C0).setFormat(fo_AllBg);
    if (MW->MO->bookmarks[i].absIndex < MAX_VERSES) // Ако има отметка.
    {
      if (MW->MO->TS->globalLayoutDirection == Qt::RightToLeft && !MW->MO->bookmarks[i].label.isRightToLeft()) // Ако интерфейсът е дясно-към-ляво и ако текстът не съдържа дясно-към-ляво подравнен текст, прилага дясно-към-ляво подравняване принудително. Ако има дясно-към-ляво подравнен текст, тук трябва да се зададе ляво-към-дясно защото Qt го обръща автоматични.
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0RtL); // Формат на текста.
      else
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0LtR); // Формат на текста.

      if (MW->MO->bookmarks[i].absIndex >= NT_START_INDEX)
      {
        table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font color=%2><b>%3</b></font>").arg(num).arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->bookmarks[i].label));
      }
      else
      {
        if (MW->MO->bookmarks[i].absIndex >= DC_START_INDEX)
          table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font style=\"color:rgba(%2,%3,%4,%5);\"><i><b>%6</b></i></font>").arg(num).arg(MW->MO->SVars.oldTestamentColorFA.red()).arg(MW->MO->SVars.oldTestamentColorFA.green()).arg(MW->MO->SVars.oldTestamentColorFA.blue()).arg(MW->MO->SVars.oldTestamentColorFA.alpha()).arg(MW->MO->bookmarks[i].label));
        else
          table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font color=%2><b>%3</b></font>").arg(num).arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->bookmarks[i].label));
      }
    }
    else // Ако няма отметка (празен ред, съдържа само номер на реда).
    {
      if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0LtR); // Формат на текста.
      else //  Ако интерфейсът е дясно-към-ляво, тук трябва изрично да се сетне дясно-към-ляво подравняване, защото тук няма дясно-към-ляво подравнен текст и номерът стои в ляво.
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0RtL); // Формат на текста.
      table->cellAt(i, C0).firstCursorPosition().insertHtml(num);
    }

    table->cellAt(i, C1).setFormat(fo_AllBg);
    table->cellAt(i, C1).firstCursorPosition().setBlockFormat(blockFormatCol1); // Формат на текста.
    if (MW->MO->bookmarks[i].label.isEmpty())
      table->cellAt(i, C1).firstCursorPosition().insertHtml(QString("<font color=%1>&nbsp;X&nbsp;</font>").arg(MW->MO->SVars.dock2TextColorB.name()));
    else
      table->cellAt(i, C1).firstCursorPosition().insertHtml(QString("<font color=%1>&nbsp;X&nbsp;</font>").arg(MW->MO->SVars.dock2TextColorF.name()));
  }

  textCursor().endEditBlock();

  moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor); // Това позиционира в началото на таблицата.
}

void BookmarksWidget::addRemoveBookmark(quint8 bookmarkIndex, quint16 absIndex, QString verseCode)
{
  if (absIndex >= MAX_VERSES) // Ако отметката трябва да се премахне.
  {
    MW->MO->bookmarks[bookmarkIndex].absIndex = MAX_VERSES;
    MW->MO->bookmarks[bookmarkIndex].label = "";
  }
  else // Ако отметката трябва да се добави.
  {
    quint8 b = 1, c = 1, v = 1;
    if (!MW->MO->absIndexToReference(absIndex, b, c, v)) return; // Превръща абсолютния индекс на стиха в препратки (код на книгата, главата и стиха).
    MW->MO->bookmarks[bookmarkIndex].absIndex = absIndex;
    MW->MO->bookmarks[bookmarkIndex].verseCode = verseCode;
    MW->MO->bookmarks[bookmarkIndex].label = QString("%1 %2:%3").arg(MW->MO->bookMinNameArr[b-1]).arg(c).arg(verseCode);
  }

  QString bm = ""; // bookmarkIndex.verseAbsCode.verseCode^bookmarkIndex.verseAbsCode.verseCode...
  for (int i = 0; i < MAX_BOOKMARKS; i++)
  {
    if (MW->MO->bookmarks[i].absIndex < MAX_VERSES) // Ако има отметка.
      bm += QString("%1.%2.%3^").arg(i).arg(MW->MO->toWesternExtIndexIfNeed(MW->MO->bookmarks[i].absIndex)+1).arg(MW->MO->bookmarks[i].verseCode); // Номерата на стиховете започват от 1, затова тук се прави +1. // Ако е по източния стандарт на подредба на книгите го прави по западния защото отметките се помнят само по западния в INI файла.
  }
  QSettings settings(MW->MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  settings.setValue(QString("bookmarks"), bm);
}

void BookmarksWidget::refreshBookmarks()
{
  textCursor().beginEditBlock();
  
  QTextTableFormat tableFormat = table->format();

  table->removeColumns(1, 1); // Изтрива втората колона.
  table->appendColumns(1);    // Създава я отново празна. Това е защото не можах да разбера как се трие съдържанието на клетките в таблицата.
  table->removeColumns(0, 1); // Изтрива първата колона.
  table->insertColumns(0, 1); // Създава я отново празна. Това е защото не можах да разбера как се трие съдържанието на клетките в таблицата.

  tableFormat.setAlignment(Qt::AlignLeft);
  QVector<QTextLength> constraints;
  constraints << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 90 : 10)
              << QTextLength(QTextLength::PercentageLength, (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? 10 : 90);
  tableFormat.setColumnWidthConstraints(constraints);
  table->setFormat(tableFormat);

  QString num;
  for (int i = 0; i < MAX_BOOKMARKS; i++)
  {
    num = (i < 10) ? QString("0%1").arg(i) : QString("%1").arg(i);
    num = QString("<sup><font color=%1><b>%2</b></font></sup>").arg(MW->MO->SVars.dock2TextColorF.name()).arg(num); // &nbsp;

    table->cellAt(i, C0).setFormat(fo_AllBg);
    if (MW->MO->bookmarks[i].absIndex < MAX_VERSES) // Ако има отметка.
    {
      if (MW->MO->TS->globalLayoutDirection == Qt::RightToLeft && !MW->MO->bookmarks[i].label.isRightToLeft()) // Ако интерфейсът е дясно-към-ляво и ако текста не съдържа дясно-към-ляво подравнен текст, прилага дясно-към-ляво подравняване принудително. Ако има дясно-към-ляво подравнен текст, тук трябва да се зададе ляво-към-дясно защото Qt го обръща автоматични.
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0RtL); // Формат на текста.
      else
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0LtR); // Формат на текста.

      if (MW->MO->bookmarks[i].absIndex >= NT_START_INDEX)
      {
        table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font color=%2><b>%3</b></font>").arg(num).arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->bookmarks[i].label));
      }
      else
      {
        if (MW->MO->bookmarks[i].absIndex >= DC_START_INDEX)
          table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font style=\"color:rgba(%2,%3,%4,%5);\"><i><b>%6</b></i></font>").arg(num).arg(MW->MO->SVars.oldTestamentColorFA.red()).arg(MW->MO->SVars.oldTestamentColorFA.green()).arg(MW->MO->SVars.oldTestamentColorFA.blue()).arg(MW->MO->SVars.oldTestamentColorFA.alpha()).arg(MW->MO->bookmarks[i].label));
        else
          table->cellAt(i, C0).firstCursorPosition().insertHtml(QString("%1 <font color=%2><b>%3</b></font>").arg(num).arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->bookmarks[i].label));
      }
    }
    else // Ако няма отметка (празен ред, съдържа само номер на реда).
    {
      if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0LtR); // Формат на текста.
      else //  Ако интерфейсът е дясно-към-ляво, тук трябва изрично да се сетне дясно-към-ляво подравняване, защото тук няма дясно-към-ляво подравнен текст и номерът стои в ляво.
        table->cellAt(i, C0).firstCursorPosition().setBlockFormat(blockFormatCol0RtL); // Формат на текста.
      table->cellAt(i, C0).firstCursorPosition().insertHtml(num);
    }

    table->cellAt(i, C1).setFormat(fo_AllBg);
    table->cellAt(i, C1).firstCursorPosition().setBlockFormat(blockFormatCol1); // Формат на текста.
    if (MW->MO->bookmarks[i].label.isEmpty())
      table->cellAt(i, C1).firstCursorPosition().insertHtml(QString("<font color=%1>&nbsp;X&nbsp;</font>").arg(MW->MO->SVars.dock2TextColorB.name()));
    else
      table->cellAt(i, C1).firstCursorPosition().insertHtml(QString("<font color=%1>&nbsp;X&nbsp;</font>").arg(MW->MO->SVars.dock2TextColorF.name()));
  }

  textCursor().endEditBlock();
}

void BookmarksWidget::mousePressEvent(QMouseEvent *event)
{
  QTextBrowser::mousePressEvent(event);
  // Ляв бутон - показва отметката --- Left-click to show bookmarks.
  // Добави отметка --- Toggle bookmarks

  int blockNumber = textCursor().blockNumber();
  if (blockNumber < 1 || blockNumber > (MAX_BOOKMARKS * 2)) return; // MAX_BOOKMARKS x 2 реда.

  quint8 row = ((blockNumber - 1) / 2);
  quint8 col = ((blockNumber - 1) % 2);

  if (col == C1) // Ако е натиснат X за да се изтрие отметката.
  {
    if (MW->MO->bookmarks[row].absIndex < MAX_VERSES) // Ако отметката не е празна.
    {
      if ( QMessageBox::question(this, QCoreApplication::applicationName(), MW->MO->TS->DeleteBookmarkQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
      {
        addRemoveBookmark(row, MAX_VERSES, "");
        refreshBookmarks();
      }
    }
  }
  else // Ако трябва да се добави или покаже отметка.
  {
    if (MW->MO->bookmarks[row].absIndex >= MAX_VERSES) // Ако отметката е празна.
    {
      if (MW->currentHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
        addRemoveBookmark(row, MW->currentHolyTextView->currentAbsIndex, MW->currentHolyTextView->currentVerseCode);
      else // Ако е в режим на ежедневно четене.
        addRemoveBookmark(row, MW->currentDR_AbsIndex, MW->currentHolyTextView->currentVerseCode);
      refreshBookmarks();
    }
    else // Ако има записана отметка.
    {
      MW->showBookmark(MW->MO->bookmarks[row].absIndex);
    }
  }
}

void BookmarksWidget::mouseReleaseEvent(QMouseEvent *event)
{
  QTextBrowser::mouseReleaseEvent(event);

  if (textCursor().hasSelection())
  {
    moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor); // Това премахва селекцията.
  }
}

void BookmarksWidget::slotRefreshPalette()
{
  initTable();
}

// ==========================================================================================================================================================

BookmarksToolBar::BookmarksToolBar(MainWindow *mainWindow, BookmarksWidget *bookmarksWidget, QWidget *parent) : MDock(parent)
{
  this->MW = mainWindow;

  setDockWidgetTabbedTitleBar(true);
  setProperties(false, false, true, false);
  setDockGridState("0^100_1_0^100"); // Един ред с един раздел.
  setMinimumSize(1, 1); // Не трябва да е 0, защото няма ефект.

  mDockWidget = new MDockWidget(this, QString("<b>%1</b>").arg(MW->MO->TS->Bookmarks_v1), false, false, MW->MO->SVars.docks3DTitleBar, 1, 0);
  mDockWidget->setWidget(bookmarksWidget);
  mDockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само сигнал.
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  mDockWidget->setCloseBtnToolTip(MW->MO->TS->HideToolBar_v1);
  connect(mDockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotCloseDock(MDock *, MDockWidget *, int, quint8))); // Излъченият от Close бутона сигнал.

  addDockWidget(mDockWidget, 0, 0);

  QFont currfont = bookmarksWidget->font();
  currfont.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  bookmarksWidget->setFont(currfont);
  // F    6    7    8    9   10   11   12   14   16   18   20 - възможни размери на шрифта.
  // W  130  145  160  175  190  205  220  250  280  310  340 - широчина на тулбара за отметките.
  //
  // W = F * 15 + 40
  //
  int W = MW->MO->SVars.booksToolBarFontSize * 15 + 40;
  this->setMinimumWidth(W);
  this->setMaximumWidth(W);
  
  slotSetColors();
}

BookmarksToolBar::~BookmarksToolBar()
{
  delete mDockWidget;
}

void BookmarksToolBar::slotCloseDock(MDock */*dock*/, MDockWidget */*dockWidget*/, int /*dockWidgetID*/, quint8 /*dockWidgetType*/)
{
  //setVisible(false); // Това ще скрие (затвори) панела, но бутонът в TMenu няма да се отпусне.
  MW->mainToolBar->btnNavigation_Bookmarks->click(); // Това косвено ще извика setVisible(false).
}

void BookmarksToolBar::slotSetTitleBarFontSize()
{
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
}

void BookmarksToolBar::slotSetColors()
{
  setDockBgColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
}

void BookmarksToolBar::slotSet3DTitleBar()
{
  mDockWidget->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
}
