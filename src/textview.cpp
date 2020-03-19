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

#include "textview.h"
//#include <QTextOption>

TextView::TextView(MainWindow *MW, QWidget *parent) : QTextBrowser(parent)
{
  this->MW = MW;
  dockWidget = 0;
  isCurrentHolyTextView = false;

  activeBibleTexts.resize(512);
  activeBibleTextsCount = 0;
  currentVerseCode = "";
  currentAbsIndex = MAX_VERSES;
  tempSearchWordsList.clear();
  tempCaseSensitivitySearch = Qt::CaseInsensitive;
  currentBibleTextsNames = "";
  backForwardCurrentIndex = 0;

  textMode = 0;
  readMode = READ_MODE__NORMAL;
  textZoom = 0;
  highlighter = 0;
  disallowSelectRow = false;
  currentRow = 0;
  currentCol = -1;
  selectedRows.fill(false, 192);
  selectedVerse = "";
  selectedVerseRef = "";
  findInTextString = "";
  findInTextOptions = 0; // Изключени опции за търсене.
  versesTable = 0;

  document()->setDocumentMargin(2);
  //setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere); // По подразбиране е това (не важи за текста в рамки).
  setReadOnly(true);
  setUndoRedoEnabled(false);
  setAcceptRichText(false);
  setFrameShape(QFrame::NoFrame);
  //setAutoFillBackground(true);
  setOpenExternalLinks(false);
  setOpenLinks(false);
  connect(this, SIGNAL(anchorClicked (const QUrl &)), this, SLOT(slotAnchorClicked(const QUrl &)));

  searchTextAct = new QAction(Icons::icon_Search(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->SearchTextInTheBible_v1, this);
  //searchTextAct->setEnabled(false);
  connect(searchTextAct, SIGNAL(triggered()), this, SLOT(slotSearchInBible()));

  customHighlightAddAct = new QAction(MW->MO->TS->CustomHighlightAdd_v1, this);
  customHighlightAddAct->setShortcut(Qt::CTRL + Qt::Key_M);
  customHighlightAddAct->setEnabled(true);
  connect(customHighlightAddAct, SIGNAL(triggered()), this, SLOT(slotCustomHighlightAdd()));

  customHighlightDelAct = new QAction(MW->MO->TS->CustomHighlightDel_v1, this); //"Премахва оцветяването само на селектирания или на всеки оцветен текст, ако няма селектиран (Ctrl+E)"
  customHighlightDelAct->setShortcut(Qt::CTRL + Qt::Key_E);
  customHighlightDelAct->setEnabled(true);
  connect(customHighlightDelAct, SIGNAL(triggered()), this, SLOT(slotCustomHighlightDel()));

  exportTextAct = new QAction(Icons::icon_ExportTxt(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->ExportToText_v1, this);
  connect(exportTextAct, SIGNAL(triggered()), this, SLOT(slotExportText()));

  exportHTMLAct = new QAction(Icons::icon_ExportHtm(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->ExportToHTML_v1, this);
  connect(exportHTMLAct, SIGNAL(triggered()), this, SLOT(slotExportHTML()));

  exportPDFAct = new QAction(Icons::icon_ExportPdf(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->ExportToPDF_v1, this);
  connect(exportPDFAct, SIGNAL(triggered()), this, SLOT(slotExportPDF()));

  createHTMLMatCrossBibleV1Act = new QAction(MW->MO->TS->CreateHTMLMatCrossBibleV1_v1, this);
  connect(createHTMLMatCrossBibleV1Act, SIGNAL(triggered()), this, SLOT(slotCreateHTMLMatCrossBibleV1()));

  createHTMLMatCrossBibleV2Act = new QAction(MW->MO->TS->CreateHTMLMatCrossBibleV2_v1, this);
  connect(createHTMLMatCrossBibleV2Act, SIGNAL(triggered()), this, SLOT(slotCreateHTMLMatCrossBibleV2()));

  printPreviewAct = new QAction(Icons::icon_PrintPreview(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->PrintPreview_v1, this);
  connect(printPreviewAct, SIGNAL(triggered()), this, SLOT(slotPrintPreview()));

  printAct = new QAction(Icons::icon_Print(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->Print_v1, this);
  printAct->setShortcut(Qt::CTRL + Qt::Key_P);
  connect(printAct, SIGNAL(triggered()), this, SLOT(slotPrint()));

  selectAllAct = new QAction(Icons::icon_SelectAll(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->SelectAll_v1, this);
  selectAllAct->setShortcut(Qt::CTRL + Qt::Key_A);
  connect(selectAllAct, SIGNAL(triggered()), this, SLOT(slotSelectAll()));

  copyAct = new QAction(Icons::icon_Copy(32, 32, MW->iconColorMenus, MW->iconColorMenus), MW->MO->TS->Copy_v1, this);
  copyAct->setShortcut(Qt::CTRL + Qt::Key_C);
  copyAct->setEnabled(false);
  connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));
  connect(this, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));

  markWidget = new QWidget(this);
  markWidget->setGeometry(QRect(1, 1, 3, 3));
  markWidget->setToolTip(MW->MO->TS->CurrentView_v1);
  QPalette pal;
  pal.setBrush(QPalette::Window, MW->MO->SVars.appColorB);
  markWidget->setPalette(pal);
  markWidget->setAutoFillBackground(true);
  markWidget->hide();
}

TextView::~TextView()
{
  //qDebug("~TextView");
  if (MW->MO != 0 && readMode == READ_MODE__DAILY_READ) // Ако е затворен само този изглед (не цялата програма) и е в режим на систематично четене.
  {
    MW->mainToolBar->btnNavigation_DailyRead->setEnabled(true); // Прави бутона активен, защото е бил неактивен при другите изгледи.
    MW->mainToolBar->btnNavigation_DailyRead->click(); // Превключва в нормално четене (реално нищо не се променя, само бутонът изпъква).
  }

  delete markWidget;
  markWidget = 0;
}

void TextView::textCursorBeginEditBlock()
{
  textCursor().beginEditBlock(); // Това решава проблема със скоростта на показване и промяна на текста (http://bugreports.qt.nokia.com/browse/QTBUG-3554).
}

void TextView::textCursorEndEditBlock()
{
  textCursor().endEditBlock(); // Това решава проблема със скоростта на показване и промяна на текста (http://bugreports.qt.nokia.com/browse/QTBUG-3554).
}

void TextView::initializeTextView(quint8 initialTextMode)
{
  this->textMode = initialTextMode;
  reInitializeTextView();
}

void TextView::reInitializeTextView()
{
  clear();
  versesTable = 0;
  currentRow = 0;
  currentCol = -1;
  selectedRows.fill(false);

  if (highlighter == 0) highlighter = new Highlighter(document());
  highlighter->initializeHighlighter(MW, this);

  standardFormat.setFontWeight(QFont::Normal);
  textCursor().setCharFormat(standardFormat);
}

void TextView::insertTable(int row, int col)
{
  QTextTableFormat tableFormat;
  //tableFormat.setBackground(MW->MO->colorModify(MW->MO->SVars.dock2TextColorF, 50)); // Показва рамките на таблицата.
  tableFormat.setCellPadding(1);
  tableFormat.setCellSpacing(1);
  tableFormat.setBorder(0);

  QVector<QTextLength> constraints;
  for (int i = 0; i < col; i++)
  {
    constraints << QTextLength(QTextLength::PercentageLength, 100/col); // Ако е показан само един текст, колоната му да заема цялото място.
  }
  tableFormat.setColumnWidthConstraints(constraints);
  //tableFormat.clearColumnWidthConstraints(); // Доколкото разбирам този ред оправя нещата и няма нужда от горните редове. Но нещо не се получава, когато е само една колона (не стига до край таблицата).

  versesTable = textCursor().insertTable(row, col, tableFormat);
}

void TextView::appendRowsToTable(int count)
{
  if (versesTable != 0) versesTable->appendRows(count); // Добавя count нови редове към таблицата.
}

void TextView::removeLastRowsFromTable(int count)
{
  if (versesTable != 0 && versesTable->rows() >= count) versesTable->removeRows(versesTable->rows() - count, count); // Изтрива последните count реда от таблицата.
}

void TextView::tvInsertTextAt(int row, int col, QString text)
{
  versesTable->cellAt(row, col).firstCursorPosition().insertText(text, standardFormat);
}

void TextView::tvInsertTextAt(int row, int col, QString text, QTextCharFormat format)
{
  versesTable->cellAt(row, col).firstCursorPosition().insertText(text, format);
}

void TextView::tvInsertHtmlAt(int row, int col, QString text)
{
  versesTable->cellAt(row, col).firstCursorPosition().insertHtml(text);
}

void TextView::tvInsertHtmlAt(int row, int col, QString text, QTextCharFormat format)
{
  versesTable->cellAt(row, col).setFormat(format);
  versesTable->cellAt(row, col).firstCursorPosition().insertHtml(text);
}

void TextView::tvInsertText(QString text)
{
  textCursor().insertText(text, standardFormat);
}

void TextView::tvInsertText(QString text, QTextCharFormat format)
{
  textCursor().insertText(text, format);
}

void TextView::tvInsertHtml(QString text)
{
  textCursor().insertHtml(text);
}

void TextView::tvSetPlainText(QString text)
{
  setPlainText(text);
  versesTable = 0;
}

void TextView::tvSetHtml(QString text)
{
  setHtml(text);
  versesTable = 0;
}

void TextView::slotSelectAll()
{
  selectAll();
}

void TextView::slotShowFileMenu()
{
  QMenu *fileMenu = createFileMenu();
  if (MW->MO->SVars.TMenuPosition == POSITION_TOP)
    fileMenu->exec(QPoint(QCursor::pos().x() - MW->mainToolBar->btnsHeightSize, MW->geometry().y() + MW->mainToolBar->btnsHeightSize));
  else
    fileMenu->exec(QPoint(QCursor::pos().x() - MW->mainToolBar->btnsHeightSize, MW->geometry().y() + MW->geometry().height())); //fileMenu->exec(QCursor::pos());
  delete fileMenu;
}

void TextView::slotExportText()
{
  QString fileName = QFileDialog::getSaveFileName(this, QString("Save As"), QString("%1 %2.txt").arg(MW->MO->toBookShortName(currentAbsIndex)).arg(MW->MO->toChapterCode(currentAbsIndex)), QString("*.*"));
  if (!fileName.isEmpty())
  {
    if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(".txt");
    saveFile(fileName, false);
  }
}

void TextView::slotExportHTML()
{
  QString fileName = QFileDialog::getSaveFileName(this, QString("Export HTML"), QString("%1 %2.html").arg(MW->MO->toBookShortName(currentAbsIndex)).arg(MW->MO->toChapterCode(currentAbsIndex)), QString("*.html"));
  if (!fileName.isEmpty())
  {
    if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
    {
      textCursorBeginEditBlock();
      deselectAllRow();
      textCursorEndEditBlock();
    }
    if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(".html");
    saveFile(fileName, true);
  }
}

void TextView::slotExportPDF()
{
#ifndef QT_NO_PRINTER
  QString fileName = QFileDialog::getSaveFileName(this, QString("Export PDF"), QString("%1 %2.pdf").arg(MW->MO->toBookShortName(currentAbsIndex)).arg(MW->MO->toChapterCode(currentAbsIndex)), QString("*.pdf"));
  if (!fileName.isEmpty())
  {
    if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
    {
      textCursorBeginEditBlock();
      deselectAllRow();
      textCursorEndEditBlock();
    }
    if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(".pdf");

    MW->MO->printer->setOutputFormat(QPrinter::PdfFormat);
    MW->MO->printer->setOutputFileName(fileName); // Указва че ще се "принтира" във файла fileName.

    print(MW->MO->printer);

    MW->MO->printer->setOutputFormat(QPrinter::NativeFormat);
    MW->MO->printer->setOutputFileName(""); // Указва че ще се принтира на принтера, а не във файл.
  }
#endif
}

void TextView::slotCreateHTMLMatCrossBibleV1()
{
  slotCreateHTMLMatCrossBibleV(1);
}

void TextView::slotCreateHTMLMatCrossBibleV2()
{
  slotCreateHTMLMatCrossBibleV(2);
}

void TextView::slotCreateHTMLMatCrossBibleV(quint8 ver)
{
  if (activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  // Определя активния превод:
  int currentBibleText = 0;
  for (currentBibleText = 0; currentBibleText < activeBibleTexts.size(); currentBibleText++)
  {
    if (activeBibleTexts.at(currentBibleText)) break;
  }
  QString name = MW->MO->bibleTextList[currentBibleText].name.trimmed();

  QProgressBar *progressBar = new QProgressBar(this);
  progressBar->setMinimum(1);
  if (MW->MO->SVars.showDeuterocanonical)
    progressBar->setMaximum(77);
  else
    progressBar->setMaximum(66);
  progressBar->resize(this->size().width(), MW->MO->SVars.globalFontSize + 10); //progressBar->size().height()
  progressBar->setAlignment(Qt::AlignHCenter);
  progressBar->show();

  QDir dir; // Създава (ако не съществуват) директориите, в които ще се поместват файловете.
  dir.mkpath(QString("%1/MatCrossBible.HTML/%2").arg(QCoreApplication::applicationDirPath()).arg(name));
  for (int i = 0; i < 77; i++)
  {
    if ((i >= 39 && i <= 49) && !MW->MO->SVars.showDeuterocanonical) continue; // Ако трябва да се скрият второканоничните книги.
    dir.mkpath(QString("%1/MatCrossBible.HTML/%2/%3_%4").arg(QCoreApplication::applicationDirPath()).arg(name).arg(i+1, 2, 10, QLatin1Char('0')).arg(MW->MO->bookFileNameArr[i]));
  }

  for (int b = 1; b <= 77; b++)
  {
    if ((b >= 40 && b <= 50) && !MW->MO->SVars.showDeuterocanonical) continue; // Ако трябва да се скрият второканоничните книги.

    for (int c = 1; c <= MW->MO->chaptersCountArr[b-1]; c++)
    {
      if (ver == 1)
        MW->MO->createHTML_MatCrossBible_File_V1(&MW->MO->bibleTextList[currentBibleText], b, c);
      else if (ver == 2)
        MW->MO->createHTML_MatCrossBible_File_V2(&MW->MO->bibleTextList[currentBibleText], b, c);
    }
    progressBar->setValue(b);
  }
  MW->MO->createHTML_MatCrossBible_Main_File(&MW->MO->bibleTextList[currentBibleText], ver);

  delete progressBar;
  QMessageBox::information(this, QCoreApplication::applicationName(), QString("%1\n%2/MatCrossBible.HTML/%3").arg(MW->MO->TS->HTMLMatCrossBibleCreatedIn_v1).arg(QCoreApplication::applicationDirPath()).arg(name));
}

void TextView::slotPrintPreview()
{
#ifndef QT_NO_PRINTER
    if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
    {
      textCursorBeginEditBlock();
      deselectAllRow();
      textCursorEndEditBlock();
    }
  QPrintPreviewDialog preview(MW->MO->printer, this);
  connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(slotPrintPreviewPaintRequested(QPrinter*)));
  preview.exec();
#endif
}

void TextView::slotPrintPreviewPaintRequested(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
  Q_UNUSED(printer);
#else
  print(printer);
#endif
}

void TextView::slotPrint()
{
#ifndef QT_NO_PRINTER
    if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
    {
      textCursorBeginEditBlock();
      deselectAllRow();
      textCursorEndEditBlock();
    }
  QPrintDialog *dlg = new QPrintDialog(MW->MO->printer, this);
  if (textCursor().hasSelection()) dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
  dlg->setWindowTitle(QString("Print Document"));
  if (dlg->exec() == QDialog::Accepted) print(MW->MO->printer);
  delete dlg;
#endif
}

void TextView::slotFindNext()
{
  QString text = MW->mainToolBar->lineEdit_SearchInText->text();
  if (text.isEmpty() || MW->mainToolBar->lineEdit_SearchInText_IsInactive) return;
  QTextDocument::FindFlags options;
  if (MW->mainToolBar->btnText_SearchInTextCaseSensitive->isChecked()) options = options | QTextDocument::FindCaseSensitively;
  if (MW->mainToolBar->btnText_SearchInTextWholeWords->isChecked())    options = options | QTextDocument::FindWholeWords;

  QTextDocument *doc = document();
  QTextCursor c = textCursor();

  if (c.hasSelection())
  {
    c.setPosition(c.position(), QTextCursor::MoveAnchor);
  }

  QTextCursor newCursor = c;

  if (!text.isEmpty())
  {
    newCursor = doc->find(text, c, options & ~QTextDocument::FindBackward); // FindBackward е задължително изключена.

    if (newCursor.isNull()) // Ако няма резултат, то това означава, че или е достигнат краят (началото) на документа или няма такава дума. Затова се прави ново търсене - ако и то не даде резултат, значи няма такава дума.
    {
      QTextCursor ac(doc);
      ac.movePosition(QTextCursor::Start);
      newCursor = doc->find(text, ac, options & ~QTextDocument::FindBackward); // FindBackward е задължително изключена.
      if (newCursor.isNull()) // Търсената дума не съществува.
      {
        newCursor = c;
        QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->TextNotFound_v1);
      }
      else // Търсената дума съществува, но е достигнат краят (началото) на документа и търсенето е започнало от началото (края) на документа.
      {
        //qDebug("-->Reached end of page, continued from top");
      }
    }
  }
  setTextCursor(newCursor);
  setFocus();
}

void TextView::slotFindPrevious()
{
  QString text = MW->mainToolBar->lineEdit_SearchInText->text();
  if (text.isEmpty() || MW->mainToolBar->lineEdit_SearchInText_IsInactive) return;
  QTextDocument::FindFlags options;
  if (MW->mainToolBar->btnText_SearchInTextCaseSensitive->isChecked()) options = options | QTextDocument::FindCaseSensitively;
  if (MW->mainToolBar->btnText_SearchInTextWholeWords->isChecked())    options = options | QTextDocument::FindWholeWords;

  QTextDocument *doc = document();
  QTextCursor c = textCursor();

  if (c.hasSelection())
  {
    c.setPosition(c.anchor(), QTextCursor::MoveAnchor);
  }

  QTextCursor newCursor = c;

  if (!text.isEmpty())
  {
    newCursor = doc->find(text, c, options | QTextDocument::FindBackward); // FindBackward е задължително включена.

    if (newCursor.isNull()) // Ако няма резултат, то това означава, че или е достигнат краят (началото) на документа или няма такава дума. Затова се прави ново търсене - ако и то не даде резултат, значи няма такава дума.
    {
      QTextCursor ac(doc);
      ac.movePosition(QTextCursor::End);
      newCursor = doc->find(text, ac, options | QTextDocument::FindBackward); // FindBackward е задължително включена.
      if (newCursor.isNull()) // Търсената дума не съществува.
      {
        newCursor = c;
        QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->TextNotFound_v1);
      }
      else // Търсената дума съществува, но е достигнат краят (началото) на документа и търсенето е започнало от началото (края) на документа.
      {
        //qDebug("<--Reached end of page, continued from top");
      }
    }
  }
  setTextCursor(newCursor);
  setFocus();
}

void TextView::slotSearchInBible()
{
  if (!MW->mainToolBar->btnText_Search->isChecked()) MW->mainToolBar->btnText_Search->click();  // Ако центърът за търсене трябва да се отвори.
  MW->mDockSearch->currentSearchWidget->setSearchLineText( textCursor().selectedText() );
  MW->mDockSearch->currentSearchWidget->setSearchLineInFocus(true);
  MW->mDockSearch->currentSearchWidget->slotSearchGo();
}

void TextView::slotCustomHighlightAdd()
{
  if ( !textCursor().selectedText().isEmpty() ) // Ако има селектиран текст.
    slotExtraSelections(textCursor().selectedText(), false);
    //highlighter->addCustomPattern(textCursor().selectedText());
}

void TextView::slotCustomHighlightDel()
{
  if ( !textCursor().selectedText().isEmpty() ) // Ако има селектиран текст.
    slotExtraSelections("", false);
    //highlighter->delCustomPattern(textCursor().selectedText()); // Премахва оцветяването само на селектирания текст.
  else // Ако няма селектиран текст.
    slotExtraSelections("", false);
    //highlighter->delCustomPatterns(); // Премахва оцветяването на всички оцветени думи.
}

void TextView::slotExtraSelections(QString text, bool firstExtraSelections)
{
  // Този слот прави мултиселекция на селектиран текст (параметър text). Това ще рече, че ако се селектира част от текста,
  // ще се селектират (оцветят) автоматично всички срещания на този текст.
  //
  // Селектираният текст е разделен на две групи - първа и втора мултиселекция, като текущата се определя от firstExtraSelections параметъра.
  // Първа мултиселекция се оцветява в extraSelectColor1B и се прави от щракване с мишката, а втора мултиселекция
  // е в extraSelectColor2B и се прави от контекстното меню.
  //
  // Методът е така направен, че позволява да се селектира нов текст, без да е премахната мултиселекцията от предния.
  // Това позволява да се селектира различен текст с една селекция (цвят).
  // Ако параметърът text е празен, съответната селекция се изчиства.

  QList<QTextEdit::ExtraSelection> extraSelections;
  quint64 count = 0;
  QTextDocument *doc = document();
  QTextCursor cursor = textCursor();
  cursor.beginEditBlock();
  cursor.movePosition(QTextCursor::Start);
  QTextCursor newCursor = cursor;
    
  if (text.isEmpty()) // Ако при щракване върху текста, няма селектиран текст.
  {
    if (firstExtraSelections)
    {
      if (extraSelections1.count() > 0) extraSelections1.clear();
    }
    else
    {
      if (extraSelections2.count() > 0) extraSelections2.clear();
    }
  }
  else // Ако има селектиран текст.
  {
    QTextEdit::ExtraSelection selection;
    if (firstExtraSelections)
    {
      selection.format.setBackground(MW->MO->SVars.extraSelectColor1B); // Първа мултиселекция.
      selection.format.setForeground(MW->MO->SVars.dock1TextColorB); // Ако този ред е коментиран, цветът на буквите няма да се промени.
    }
    else
    {
      selection.format.setBackground(MW->MO->SVars.extraSelectColor2B); // Втора мултиселекция.
      selection.format.setForeground(MW->MO->SVars.dock1TextColorB); // Ако този ред е коментиран, цветът на буквите няма да се промени.
    }
    
    while (true)
    {
      newCursor = doc->find(text, newCursor);
    
      if (!newCursor.isNull()) // Ако текстът е открит.
      {
        selection.cursor = newCursor;
        if (firstExtraSelections)
          extraSelections1.append(selection);
        else
          extraSelections2.append(selection);

        if (newCursor.hasSelection()) count++; // Ако има селектиран текст.
      }
      else // Ако текстът не е открит или е достигнат край на документа.
      {
        break;
      }
    }
  }

  if (extraSelections1.count() > 0)
  {
    for (int i = 0; i < extraSelections1.count(); i++)
      extraSelections.append(extraSelections1[i]);
  }
  if (extraSelections2.count() > 0)
  {
    for (int i = 0; i < extraSelections2.count(); i++)
      extraSelections.append(extraSelections2[i]);
  }
  setExtraSelections(extraSelections); // Селектира открития текст (екстра селекция). Ако няма такъв - деселектира всичко.

  if (count > 0)
  {
    if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
      QToolTip::showText(QCursor::pos(), QString("%1 %2").arg(MW->MO->TS->MatchesToOccurrences_v1).arg(count), this);
    else // Ако текстът е с дясно подравняване.
      QToolTip::showText(QCursor::pos(), QString("%1 %2").arg(count).arg(MW->MO->TS->MatchesToOccurrences_v1), this);
  }

  cursor.endEditBlock();
}

bool TextView::saveFile(const QString &fileName, const bool toHtml)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
      QMessageBox::warning(this, QCoreApplication::applicationName(),
                           QString("Cannot write file %1:\n%2.")
                           .arg(fileName)
                           .arg(file.errorString()));
      return false;
  }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  if (toHtml)
  {
    QString s = this->toHtml();
    s.replace(QString("<meta name=\"qrichtext\" content=\"1\" />"), QString("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />"));
    s.replace("<td width=\"", "<td widthh=\""); // Това ще премахне генерираната широчина. Свойството "widthh" не съществува и ще бъде игнорирана от браузърите.
    out << s;
    //out << this->toHtml();
  }
  else
  {
    out << this->toPlainText();
  }
  QApplication::restoreOverrideCursor();

  return true;
}

void TextView::contextMenuEvent(QContextMenuEvent *event)
{
  if (textCursor().selectedText().isEmpty()) // Ако няма селектиран текст.
  {
    searchTextAct->setEnabled(false);
    customHighlightAddAct->setEnabled(false);
  }
  else // Ако има селектиран текст.
  {
    searchTextAct->setEnabled(true);
    customHighlightAddAct->setEnabled(true);
  }

  //QMenu *menu = createStandardContextMenu(); // Така се прави разширение на стандартното меню.
  QMenu menu; // Ново меню.
  menu.addAction(searchTextAct);
  menu.addSeparator();
  menu.addAction(customHighlightAddAct);
  menu.addAction(customHighlightDelAct);
  menu.addSeparator();
  menu.addAction(copyAct);
  menu.addAction(selectAllAct);
  menu.addSeparator();

  QMenu *fileMenu = createFileMenu();
  menu.addMenu(fileMenu);

  menu.exec(event->globalPos());

  delete fileMenu;
}

QMenu *TextView::createFileMenu()
{
  QMenu *fileMenu = new QMenu(MW->MO->TS->File_v1);
  fileMenu->addAction(exportTextAct);
  fileMenu->addAction(exportHTMLAct);
  fileMenu->addAction(exportPDFAct);
  if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
  {
    fileMenu->addSeparator();
    fileMenu->addAction(createHTMLMatCrossBibleV1Act);
    fileMenu->addAction(createHTMLMatCrossBibleV2Act);
  }
  fileMenu->addSeparator();
  fileMenu->addAction(printPreviewAct);
  fileMenu->addAction(printAct);

  return fileMenu;
}

void TextView::keyPressEvent(QKeyEvent *event)
{
  QTextEdit::keyPressEvent(event);

  if (event->modifiers() == Qt::ControlModifier) // Ако е натиснат Ctrl.
  {
    if (event->key() == Qt::Key_M)
      slotCustomHighlightAdd();
    else if (event->key() == Qt::Key_E)
      slotCustomHighlightDel();
    else if (event->key() == Qt::Key_F && !textCursor().selectedText().isEmpty())
    {
      MW->mainToolBar->lineEdit_SearchInText->setFocus(); // Този ред трябва да е преди долния.
      MW->mainToolBar->lineEdit_SearchInText->setText( textCursor().selectedText() );
    }
  }
  //else if (event->modifiers() == Qt::ShiftModifier) // Ако е натиснат Shift.
  //{
  //}
  else // Ако НЕ е натиснат Ctrl или Shift.
  {
    if (event->key() == Qt::Key_Right) MW->mainToolBar->btnNavigation_NextVerse->click();
    else if (event->key() == Qt::Key_Left) MW->mainToolBar->btnNavigation_PreviousVerse->click();
  }
}

void TextView::mousePressEvent(QMouseEvent *event)
{
  bool isSelTxtBef = !textCursor().selectedText().isEmpty();
  QTextEdit::mousePressEvent(event);
  bool isSelTxtAft = !textCursor().selectedText().isEmpty();
  disallowSelectRow = isSelTxtAft || (isSelTxtBef && (!isSelTxtAft)); // Ако има селектиран текст, който ще се деселектира при излизане от тази функция ИЛИ ако току що е деселектиран селектираният текст.
}

void TextView::mouseReleaseEvent(QMouseEvent *event)
{
  QTextEdit::mouseReleaseEvent(event);

  if (MW->currentTextView != this) MW->currentTextViewChanged(this);
  
  if (event->button() == Qt::RightButton) return;

  slotExtraSelections(textCursor().selectedText(), true);

  if (!textCursor().selectedText().isEmpty()) // Ако има селектиран текст.
  {
    // Подава селектирания текст към речниците:
    if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE || textMode == TEXT_MODE__SEARCH) // Ако е в режим на показване, сравняване на текста или търсене (но не други режими като речник).
    {
      QString text = textCursor().selectedText().trimmed();

      // Проверява дали текстът съдържа няколко реда за да вземе само първия:
      int eol = text.indexOf("\r\n");
      if (eol < 0) eol = text.indexOf("\n");
      if (eol >= 0) text = text.left(eol); // Взима само първия ред.
      text = text.trimmed(); // Премахва разните интервали и други неща от началото и края на текста.
    
      if (!text.isEmpty()) MW->slotNewSelectedText(text);
    }
    return;
  }

  if (disallowSelectRow) // Ако е имало селектиран текст.
  {
    disallowSelectRow = false;
    return;
  }

  if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
  {
    textCursorBeginEditBlock();
    selectRow(0, !MW->ctrlKeyPressed, true);
    textCursorEndEditBlock();
    if ((currentRow-2) >= 0 && (currentRow-2) < absIndexesList.count())
    {
      MW->slotNewSelectedVerse(absIndexesList[currentRow-2], selectedVerseRef);
    }
  }
}

void TextView::wheelEvent(QWheelEvent *event)
{
  QTextEdit::wheelEvent(event);

  // При движение на колелцето на мишката.
  if (MW->currentTextView != this) MW->currentTextViewChanged(this);
}

void TextView::paintEvent(QPaintEvent * event)
{
  QPainter painter(viewport()); // viewport() is the paintable area and could be whats causing the issue
  QColor rectangleFill;
  QColor circleFill;
  QRect rectangle;
  
  // Чертае фона:
  rectangle.setRect(viewport()->geometry().x() - 1, viewport()->geometry().y() - 1, viewport()->geometry().width() + 4, viewport()->geometry().height() + 4); // Размерът е зададен умишлено по-голям, въпреки, че е излишно.
  if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE)
  {
    painter.fillRect(rectangle, MW->MO->SVars.dock1TextColorB);
  }
  else
  {
    painter.fillRect(rectangle, MW->MO->SVars.dock2TextColorB);
  }
  
  // Чертае картинка (ако е зададена):
  // Ако картинката е полу-прозрачна ще се вижда и фонът под нея и така ще има разлика ако се използва една картинка и за HDocks и за ODocks обекти, но потребителят да се сети да си направи фоновете еднакви.
  if (!BGImage.isNull())
  {
    int imageCountX = viewport()->width() / BGImage.width() + 1;
    int imageCountY = viewport()->height() / BGImage.height() + 1;
    for (int x = 0; x < imageCountX; x++)
    {
      for (int y = 0; y < imageCountY; y++)
      {
        painter.drawImage(QPoint(x*BGImage.width(), y*BGImage.height()), BGImage);
      }
    }
  }
  
  // Чертае правоъгълника на селекцията:
  if ((textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE) && versesTable != 0 && versesTable->columns() >= 1)
  {
    int currentRowYTop; // Горна Y координата на реда, който ще се селектира.
    int currentRowYBottom; // Долна Y координата на реда, който ще се селектира.

    quint16 currAbsIndex;
    if (readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
      currAbsIndex = currentAbsIndex;
    else // Ако е в режим на ежедневно четене.
      currAbsIndex = MW->currentDR_AbsIndex;

    if (currAbsIndex >= NT_START_INDEX)
    {
      painter.setPen(MW->MO->SVars.newTestamentColorF);
      rectangleFill = MW->MO->SVars.newTestamentColorF;
      rectangleFill.setAlpha(MW->MO->SVars.newTestamentAlphaF);
    }
    else
    {
      painter.setPen(MW->MO->SVars.oldTestamentColorF);
      rectangleFill = MW->MO->SVars.oldTestamentColorF;
      rectangleFill.setAlpha(MW->MO->SVars.oldTestamentAlphaF);
    }

    for (int r = 2; r < versesTable->rows(); r++)
    {
      if ( selectedRows[r] ) // Ако редът е селектиран.
      {
        currentRowYTop = 2147483647;
        currentRowYBottom = -2147483647;
        for (int c = 0; c < versesTable->columns(); c++) // Търси най-високата и най-ниската точка във всяка колона от таблицата.
        {
          currentRowYTop = qMin(cursorRect(versesTable->cellAt(r,c).firstCursorPosition()).y() - 1, currentRowYTop); // Текущ ред, най-горна точка.
          if (r < (versesTable->rows()-1)) // Ако не е последен ред.
            currentRowYBottom = qMax(cursorRect(versesTable->cellAt(r+1,c).firstCursorPosition()).y() - 3, currentRowYBottom); // Следващ ред, най-горна точка минус две точки.
          else // Ако е последен ред.
            currentRowYBottom = qMax(cursorRect(versesTable->cellAt(r,c).lastCursorPosition()).y() + cursorRect(versesTable->cellAt(r,c).lastCursorPosition()).height(), currentRowYBottom); // Текущ ред, най-долна точка плюс една точка.
        }

        rectangle.setRect(viewport()->x() + 1,   currentRowYTop,   viewport()->width() - 3,   currentRowYBottom - currentRowYTop);
        painter.fillRect(rectangle, rectangleFill);
        painter.drawRect(rectangle);
      }
    }
  }

  QTextEdit::paintEvent(event);
}

void TextView::slotAnchorClicked(const QUrl &link)
{
  bool ok;
  quint16 absIndex;

  if (textMode == TEXT_MODE__SEARCH) // От панела за търсене.
  {
    // Показва открития стих в текущия изглед (след щракване върху главата на стиха).
    ok = false;
    absIndex = link.toString().toUShort(&ok); // Съдържа абсолютния индекс на стиха.

    if (ok && absIndex < MAX_VERSES)
    {
      if (MW->ctrlKeyPressed) // Ако е натиснат клавиш Ctrl по време на кликването.
      {
        MW->newHDock(false, -1, -1, 0, QBitArray(), 255, absIndex); // Отваря нов прозорец и в него показва главата с открития стих.
        MW->ctrlKeyPressed = false; // Сваля флага, защото този прозорец вече не е на фокус и не може да прихване keyReleaseEvent-а, който отговаря за свалянето на флага.
      }
      else // Ако не е натиснат клавиш Ctrl по време на кликването.
      {
        MW->showFoundVerse(absIndex, true); // Показва главата с открития стих.
      }
    }
  }
  else //if (textMode == TEXT_MODE__OTHER) // Засега този линк може да дойде само от коментар!
  {
    // Показва открития стих в текущия изглед (след щракване върху главата на стиха).
    ok = false;
    absIndex = link.toString().toUShort(&ok); // Съдържа абсолютния индекс на стиха, но започващ от 1, защото първият стих е на ред 1 в .hbt файла.
    if (!ok || absIndex < 1 || absIndex > MAX_VERSES) return;
    absIndex--; // За да започва от 0, както се очаква.
    absIndex = MW->MO->toEasternExtIndexIfNeed(absIndex); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.

    if (MW->ctrlKeyPressed) // Ако е натиснат клавиш Ctrl по време на кликването.
    {
      MW->newHDock(false, -1, -1, 0, QBitArray(), 255, absIndex); // Отваря нов прозорец и в него показва главата с открития стих.
      MW->ctrlKeyPressed = false; // Сваля флага, защото този прозорец вече не е на фокус и не може да прихване keyReleaseEvent-а, който отговаря за свалянето на флага.
    }
    else // Ако не е натиснат клавиш Ctrl по време на кликването.
    {
      MW->showFoundVerse(absIndex, false); // Показва главата с открития стих.
    }
  }
}

void TextView::selectVerse(const quint16 absIndex, const bool deselectAllOther)
{
  // Този метод се извиква след показване на нова глава.

  if (activeBibleTextsCount == 0) return;
  if (versesTable == 0) return;
  if (versesTable->rows() <= 2) return;

  if (absIndexesList.count() > 0) // Ако има поне един ред със стих(ове).
  {
    for (int i = 0; i < absIndexesList.count(); i++)
    {
      if (absIndex == absIndexesList[i])
      {
        // Ред 0: Име на текст
        // Ред 1: Номер на глава
        // Ред 2: Стих 1
        // ...
        currentRow = i+2-1; // Стих 1 е на ред 2 (редовете започват от нула). Тук се задава предходния ред, защото в долния ред ще се селектира следващия ред, т.е. този, който ни трябва.
        selectRow(1, deselectAllOther, false); // Селектира следващия ред, който отговаря на желания стих. Този метод имитира натискане на бутон "Следващ стих", но се извиква само при показване на нова глава и в този случай текстът не трябва да се изпраща към проектора.
        return;
      }
    }
    // Щом минава от тук значи няма стих с такъв индекс, затова ще селектира първия, който и да е той:
    currentRow = 1; // Това ще доведе до селектиране на първия стих.
    selectRow(1, deselectAllOther, false);
  }
}

void TextView::selectRow(const qint8 rowOperation, const bool deselectAllOther, bool setProjector)
{
  // Този метод се извиква или след показване на нова глава или след селектиране на стих на вече показана глава.

  if (activeBibleTextsCount == 0) return;
  if (versesTable == 0) return; // Ако няма таблица.

  if (deselectAllOther) deselectAllRow();

  // Определя текущия ред в таблицата:
  int newCurrentRow = 0; // Името newCurrentRow е неправилно, защото се има в предвид не текущия ред, а текущата клетка от таблицата (защото таблицата може да е с повече от една колони) и би трябвало да се нарича currentCell (и съответно oldCurrentCell).
  QString t = ""; // Текста, който съдържа текущия ред (клетка) от таблицата.
  selectedVerse = ""; // Съхранява стиха, който ще се копира от контекстното меню.
  if (rowOperation == 0) // Ако новият ред е избран с мишката.
  {
    int fbn = textCursor().blockNumber()-1;
    newCurrentRow = (int)(fbn / activeBibleTextsCount + 0.5);
    if ( newCurrentRow >= 2 && newCurrentRow < versesTable->rows() )
    {
      t = textCursor().block().text();
      currentCol = (int)(fbn % activeBibleTextsCount + 0.5);
      if ( currentCol < 0 || currentCol >= versesTable->columns() ) currentCol = 0;
    }
    else
    {
      newCurrentRow = 0;
      t = "";
      if (currentCol == -1) currentCol = 0; // Ако все още не е щракнато с мишката върху текста се приема, че първият текст (колона) е текущ. 
    }
  }
  else // Ако новият ред е избран със стрелките на клавиатурата.
  {
    newCurrentRow = currentRow + rowOperation; // rowOperation е 1 или -1.
    if ( newCurrentRow < 2 ) newCurrentRow = 2;
    if ( newCurrentRow >= versesTable->rows() ) newCurrentRow = versesTable->rows() - 1;
    if (currentCol == -1) currentCol = 0; // Ако все още не е щракнато с мишката върху текста се приема, че първият текст (колона) е текущ. 
    t = versesTable->cellAt(newCurrentRow, currentCol).begin().currentBlock().text();
  }

  // Определя номера на новия, текущ стих.
  if (MW->MO->SVars.showAbsVerseNumber) // Ако е показан абсолютният номер на стих (задължително има интервал).
  {
    int colon = t.indexOf(' '); // 25048 1. Xxxx xxx
    if (colon >= 0) t.remove(0, colon+1); // 1. Xxxx xxx
  }
  if (MW->MO->SVars.verseStruct != VERSE_STRUCT__NUMBER_ONLY) // Ако е показана книгата пред номера на стиха (задължително има две точки).
  {
    int colon = t.indexOf(':'); // Бит. 1:1. Xxxx xxx
    if (colon >= 0) t.remove(0, colon+1); // 1. Xxxx xxx
  }

  if (newCurrentRow >= 2) // Ако е ред, съдържащ стих.
  {
    currentRow = newCurrentRow;

    quint16 absIndex = MAX_VERSES;
    if ((currentRow-2) < absIndexesList.count())
    {
      if (readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
      {
        currentAbsIndex = absIndexesList[currentRow-2];
        absIndex = currentAbsIndex;
      }
      else // Ако е в режим на ежедневно четене.
      {
        MW->currentDR_AbsIndex = absIndexesList[currentRow-2];
        absIndex = MW->currentDR_AbsIndex;
      }
    }

    // Разпознаване на номера на стиха (нужен е за отметките и проектора):
    int currentVerseCodeI = 0;
    QStringList tlist = t.split(".");
    if (tlist.size() > 0) currentVerseCodeI = tlist[0].toInt(); // Ако не може да се определи номерът на стиха, currentVerseCodeI приема стойност 0.

    if (currentVerseCodeI == 0) // Ако номерът на стиха не е определен.
    {
      QString t2; // Съседен стих, от който ще се извлече номерът (няма да се използва за друго).
      for (int c = 0; c < versesTable->columns(); c++)
      {
        t2 = versesTable->cellAt(currentRow, c).begin().currentBlock().text();
        if (MW->MO->SVars.showAbsVerseNumber) // Ако е показан абсолютният номер на стих (задължително има интервал).
        {
          int colon = t2.indexOf(' '); // 25048 1. Xxxx xxx
          if (colon >= 0) t2.remove(0, colon+1); // 1. Xxxx xxx
        }
        if (MW->MO->SVars.verseStruct != VERSE_STRUCT__NUMBER_ONLY) // Ако е показана книгата пред номера на стиха (задължително има две точки).
        {
          int colon = t2.indexOf(':'); // Бит. 1:1. Xxxx xxx
          if (colon >= 0) t2.remove(0, colon+1); // 1. Xxxx xxx
        }
        tlist = t2.split(".");
        if (tlist.size() > 0) currentVerseCodeI = tlist[0].toInt(); // Ако не може да се определи номерът на стиха, currentVerseCodeI приема стойност 0.
        if (currentVerseCodeI > 0) break; // Ако номерът на стиха е определен.
      }
    }

    currentVerseCode = (currentVerseCodeI > 0 && currentVerseCodeI <= 176) ? QString("%1").arg(currentVerseCodeI) : "?"; // Максималния брой стихове е в Псалом 119 - 176 стиха.

    selectedVerseRef = QString("%1:%2").arg(versesTable->cellAt(1, currentCol).begin().currentBlock().text()).arg(currentVerseCode);
    if (setProjector) MW->setProjectorText(versesTable->cellAt(0, currentCol).begin().currentBlock().text(), selectedVerseRef, t, absIndex, &activeBibleTexts, currentCol);
    selectedVerse = QString("%1 %2:%3").arg(MW->MO->toBookShortName(absIndexesList[currentRow-2])).arg(MW->MO->toChapterCode(absIndexesList[currentRow-2])).arg(t);

    // Селектира реда:
    if (selectedRows[currentRow]) // Ако този ред е селектиран.
    {
      selectedRows[currentRow] = false;
    }
    else // Ако НЕ е селектиран.
    {
      selectedRows[currentRow] = true;
    }
  }
  else // Ако е ред НЕсъдържащ стих.
  {
    if (setProjector) MW->setProjectorText("", "", "", MAX_VERSES, &activeBibleTexts, 0); // Това ще предизвика скриване на текста на проектора.
  }

  update();
}

void TextView::deselectAllRow()
{
  if (activeBibleTextsCount == 0) return;
  if (versesTable == 0) return;

  // Премахва оцветяването на фона на текущия стих:
  selectedRows.fill(false);
  update();
}

void TextView::setCurrentHolyTextView(bool current)
{
  isCurrentHolyTextView = current;

  if (current)
  {
    if (dockWidget != 0)
    {
      // Тук се прави нещо, което да отличава текущия раздел.
      if (markWidget != 0)
      {
        if (MW->HDocks.length() > 1) // Ако има повече от един изгледи.
        {
          markWidget->show();
        }
        else // Ако е само активният изглед (няма нужда точката да се вижда).
        {
          markWidget->hide();
        }
      }
    }
  }
  else
  {
    if (dockWidget != 0)
    {
      // Тук се премахва нещото, което отличава текущия раздел.
      if (markWidget != 0) markWidget->hide();
    }
  }
}

// Установява различни цветови схеми.
void TextView::setColorScheme()
{
  QPalette pal = palette();

  pal.setBrush(QPalette::Highlight, pal.brush(QPalette::Active, QPalette::Highlight)); // Прави селектирания текст да е винаги видим, дори когато прозорецът не е на фокус.

  if (textMode == TEXT_MODE__SHOW || textMode == TEXT_MODE__COMPARE) // В режим на показване или сравняване на глави от Библията.
  {
    BGImage = MW->MO->SVars.dock1BGImage.isEmpty() ? QImage() : QImage(MW->MO->SVars.dock1BGImage);
    pal.setBrush(QPalette::Text, MW->MO->SVars.dock1TextColorF);   // Цвят на текста.
    pal.setBrush(QPalette::Base, QColor(255, 255, 255, 0));        // Цвят на фона. Тук трябва да е прозрачност, а не MW->MO->SVars.dock1TextColorB, защото иначе не сработва селектирането на стих (рамката)!
    pal.setBrush(QPalette::Window, MW->MO->SVars.dock1TextColorB); //
    //pal.setBrush(QPalette::Button, MW->MO->SVars.appColorF);     // Това оцветява само скрол-бара. Реално указва влияние само на скролбара и затова е избран да е appColorF - за да бъдат всички скролбарове еднакви на цвят, но по-добре е редът да е закоментиран, за да си взима цветовете автоматично.
    setPalette(pal);
  }
  else if (textMode == TEXT_MODE__SEARCH || textMode == TEXT_MODE__OTHER) // В режим на показване на търсени стихове или други режими.
  {
    BGImage = MW->MO->SVars.dock2BGImage.isEmpty() ? QImage() : QImage(MW->MO->SVars.dock2BGImage);
    pal.setBrush(QPalette::Text, MW->MO->SVars.dock2TextColorF);   // Цвят на текста.
    pal.setBrush(QPalette::Base, MW->MO->SVars.dock2TextColorB);   // Цвят на фона. Не указва влияние, защото цветът на фона се определя на друго място.
    pal.setBrush(QPalette::Window, MW->MO->SVars.dock2TextColorB); // Цвят на фона. Не указва влияние, защото цветът на фона се определя на друго място.
    //pal.setBrush(QPalette::Button, MW->MO->SVars.appColorF);     // Това оцветява само скрол-бара. Реално указва влияние само на скролбара и затова е избран да е appColorF - за да бъдат всички скролбарове еднакви на цвят, но по-добре е редът да е закоментиран, за да си взима цветовете автоматично.
    setPalette(pal);
  }

  if (markWidget != 0)
  {
    pal = markWidget->palette();
    pal.setBrush(QPalette::Window, MW->MO->SVars.appColorB);
    markWidget->setPalette(pal);
  }
}

void TextView::showBibleText(quint16 absIndex)
{
  if (absIndex >= MAX_VERSES) return;
//QTime timer; int te1=0, te2=0; timer.start(); //---------------------------------------------------------------------------------------------------------

  if (readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене (не ежедневно).
  {
    if ( (MW->MO->toBookCode(backForwardList[backForwardCurrentIndex]) != MW->MO->toBookCode(absIndex)) || (MW->MO->toChapterCode(backForwardList[backForwardCurrentIndex]) != MW->MO->toChapterCode(absIndex)) ) // Ако новата глава е различна от старата.
    {
      // Изтрива всички локации след текущата
      while( backForwardCurrentIndex < (backForwardList.count() - 1) ) // Ако текущия индекс не е последен в списъка.
      {
        backForwardList.removeLast(); // Изтрива последната локация докато текущия стане последен.
      }
      backForwardList[backForwardCurrentIndex] = currentAbsIndex; // Запомня стария, последно маркиран стих.
      backForwardList << absIndex; // Добавя новата локация.
      backForwardCurrentIndex = backForwardList.count() - 1;

      //MW->mainToolBar->btnNavigation_GoBack->setEnabled(true);
      //MW->mainToolBar->btnNavigation_GoForward->setEnabled(false);
    }

    currentAbsIndex = absIndex;
  }
  //else if (readMode == READ_MODE__DAILY_READ) // Ако е в режим на ежедневно четене.
  //{
  //}

  if (MW->statusBar->currentMessage().isEmpty()) MW->statusBar->hide(); // Статус-бара се показва само при необходимост, затова ако няма съобщение в него се скрива.
  //if (isCurrentHolyTextView) MW->mainToolBar->btnText_Compare->setEnabled((activeBibleTextsCount == 2) && (readMode == READ_MODE__NORMAL));
  MW->booksWidget->setCurrentCodes(MW->MO->toBookCode(absIndex), MW->MO->toChapterCode(absIndex));

  textCursorBeginEditBlock();
  textMode = TEXT_MODE__SHOW;
  setToolTip("");
  reInitializeTextView();
//te1 = timer.elapsed(); timer.restart(); //---------------------------------------------------------------------------------------------------------------
  if (!tempSearchWordsList.isEmpty()) highlighter->addPatterns(tempSearchWordsList, tempCaseSensitivitySearch);

  QString bookName;
  if ( MW->MO->read(&activeBibleTexts, absIndex, &bookName, &currentBibleTextsNames, &absIndexesList, this) )
  {
    selectVerse(absIndex, true);
    setColorScheme();
    //if (bookName.isEmpty()) // Ако не е избран нито един от наличните текстове или ако няма файлове с текстове.
    //{
    //  textMode = TEXT_MODE__OTHER;
    //  setColorScheme();
    //  highlighter->setEnableHighlighter(false);
    //}
    //tvSetHtml(text);
    //if (bookName.isEmpty()) highlighter->setEnableHighlighter(true);
  }
  else
  {
    //textMode = TEXT_MODE__OTHER;
    //setColorScheme();
    //bookName = QString("<b>Error</b>");
    //setHtml(QString("<span style=\"color: rgb(255, 0, 0);\"><b>%1<b></span>").arg(MW->MO->TS->ShowTextError));
  }
  textCursorEndEditBlock();

  // Показва текущата книга, глава и име на текст в заглавната лента на раздела.
  if (dockWidget != 0) dockWidget->setDockWidgetTitle(QString("<b>%1</b> %2").arg(bookName).arg(currentBibleTextsNames));

  // Следващата функция прави така, че текущият стих да се покаже на екрана, в случай че е някъде надолу и не се вижда.
  // Това става посредством преход към котвата, която е поставена в началото на всеки стих.
  // scrollToAnchor работи само ако преди това е извикана textCursorEndEditBlock().
  if (absIndexesList.size() > 0 && absIndex != absIndexesList[0])
    scrollToAnchor(QString("i%1").arg(absIndex));
  else
    moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor); // Това позиционира в началото на таблицата.
//te2 = timer.elapsed(); //--------------------------------------------------------------------------------------------------------------------------------
//dockWidget->setDockWidgetTitle(QString("<<< %1 ms изтриване >>>   <<< %2 ms показване >>>").arg(te1).arg(te2)); //-------------------------------------------
}

void TextView::compareText()
{
  if (textMode == TEXT_MODE__OTHER || readMode == READ_MODE__DAILY_READ || (activeBibleTextsCount != 2))
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->TwoActiveBibleTextsNeeded_v1);
    return;
  }

  tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.

//QTime timer; int te1=0, te2=0; timer.start(); //---------------------------------------------------------------------------------------------------------
  textCursorBeginEditBlock();

  textMode = TEXT_MODE__COMPARE;
  setColorScheme();
  reInitializeTextView();

//te1 = timer.elapsed(); timer.restart(); //---------------------------------------------------------------------------------------------------------------
  if ( MW->MO->compare(&activeBibleTexts, currentAbsIndex, &currentBibleTextsNames, &absIndexesList, this) )
  {
    selectVerse(currentAbsIndex, true);
  }

  textCursorEndEditBlock();

  // Следващата функция прави така, че текущият стих да се покаже на екрана, в случай че е някъде надолу и не се вижда.
  // Това става посредством преход към котвата, която е поставена в началото на всеки стих.
  // currentTextView->scrollToAnchor работи само ако преди това е извикана currentTextView->textCursorEndEditBlock().
  if (absIndexesList.size() > 0 && currentAbsIndex != absIndexesList[0])
    scrollToAnchor(QString("i%1").arg(currentAbsIndex));
  else
    moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor); // Това позиционира в началото на таблицата.

//te2 = timer.elapsed(); //--------------------------------------------------------------------------------------------------------------------------------
//dockWidget->setDockWidgetTitle(QString("<<< %1 ms изтриване >>>   <<< %2 ms показване >>>").arg(te1).arg(te2)); //-------------------------------------------
}
