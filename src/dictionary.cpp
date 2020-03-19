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

#include <QGridLayout>
#include <QTextStream>
#include <QDir>
#include "dictionary.h"
#include <QMessageBox> // QMessageBox::information(this, QString(""), QString(""));
//#include <QDebug>

#define BUF_LEN 16384

Dictionary::Dictionary(MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->MW = MW;
  setMinimumSize(1, 1);

  isDictionary = true;
  wordsInListBox = 100;
  fromListBox = false;
  file = 0;
  SEEKS_COMM = 0;
  clearDP();

  QDir dir; dir.mkpath(QString("%1/DictAndComm").arg(MW->MO->applicationDirPath));
  allFileNames << QDir( QString("%1/DictAndComm").arg(MW->MO->applicationDirPath) ).entryList(QStringList() << "*.dct", QDir::Files, QDir::Name); // QDir::Name QDir::Time QDir::Unsorted
  allFileNames << QDir( QString("%1/DictAndComm").arg(MW->MO->applicationDirPath) ).entryList(QStringList() << "*.cmt", QDir::Files, QDir::Name); // QDir::Name QDir::Time QDir::Unsorted
  
  currentIndex = -1;
  currentIndexInList = -1;
  BFList.clear();
  currentIndexInBFList = -1;

  splitter = new QSplitter(this);
  splitter->setMinimumSize(1, 1);
  splitter->setOrientation(Qt::Horizontal);
  splitter->setChildrenCollapsible(true); // false - забранява затварянето на сплитера.
  //splitter->setHandleWidth(1);

  QWidget *widget1 = new QWidget(splitter);
  widget1->setMinimumSize(1, 1);

  entryCmbBox = new QComboBox(widget1);
  //entryCmbBox->setMinimumSize(1, 1); // Това е важно (да е коментирано) за преоразмеряването на панела, при смяна на големината на шрифта.
  entryCmbBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed); // Това е важно (Ignored и Fixed) за преоразмеряването на панела, при смяна на големината на шрифта.
  entryCmbBox->setIconSize(QSize(8, 8));
  entryCmbBox->setEditable(true);
  //entryCmbBox->setMaxCount(100); // Това ограничава съдържанието на падащото меню, но е зле направено, защото не може да се добави нова стойност след максималната (щеше да е добре, ако изтриваше първата и добавяше нова).
  entryCmbBox->setInsertPolicy(QComboBox::NoInsert); // Забранява инсъртването на текста в падащото меню при натискането на ENTER. Тази функция се прави ръчно в keyPressEvent за да може да става и когато комбобоксът не е на фокус и е натиснат ENTER.
  connect(entryCmbBox, SIGNAL(editTextChanged(QString)), this, SLOT(slotEntryCmbBox_textChanged(QString)));
  QPalette entryCmbBoxPalette = entryCmbBox->palette();
  entryCmbBoxPalette.setBrush(QPalette::Base, MW->MO->SVars.dock1TextColorB);
  entryCmbBoxPalette.setBrush(QPalette::Text, MW->MO->SVars.dock1TextColorF);
  entryCmbBox->setPalette(entryCmbBoxPalette);

  hitMarkerPaletteNormal = palette();   hitMarkerPaletteNormal.setBrush(QPalette::Window, QColor(0,0,0,0)); // Прозрачност.
  hitMarkerPaletteYellow = palette();   hitMarkerPaletteYellow.setBrush(QPalette::Window, QColor(255, 200, 0, 255));
  hitMarkerPaletteGreen  = palette();   hitMarkerPaletteGreen.setBrush(QPalette::Window, QColor(0, 170, 0, 255));
  hitMarker = new QWidget(widget1);
  hitMarker->setGeometry(2, 2, 4, 4);
  hitMarker->setAutoFillBackground(true);
  hitMarker->setPalette(hitMarkerPaletteNormal);

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
    backBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(8.0, 0.0) << QPointF(8.0, 8.0) << QPointF(0.0, 4.0), MW->MO->SVars.appColorB), QString(""), widget1); // <
  else
    backBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(0.0, 0.0) << QPointF(0.0, 8.0) << QPointF(8.0, 4.0), MW->MO->SVars.appColorB), QString(""), widget1); // <
  backBtn->setToolTip(MW->MO->TS->Back_v1);
  backBtn->setMinimumHeight(1);
  backBtn->setMinimumWidth(20);
  backBtn->setMaximumWidth(30);
  backBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  backBtn->setIconSize(QSize(8, 8));
  backBtn->setEnabled(false);
  connect(backBtn, SIGNAL(clicked()), this, SLOT(slotBack()));

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight)
    forwardBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(0.0, 0.0) << QPointF(0.0, 8.0) << QPointF(8.0, 4.0), MW->MO->SVars.appColorB), QString(""), widget1); // >
  else
    forwardBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(8.0, 0.0) << QPointF(8.0, 8.0) << QPointF(0.0, 4.0), MW->MO->SVars.appColorB), QString(""), widget1); // >
  forwardBtn->setToolTip(MW->MO->TS->Forward_v1);
  forwardBtn->setMinimumHeight(1);
  forwardBtn->setMinimumWidth(20);
  forwardBtn->setMaximumWidth(30);
  forwardBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  forwardBtn->setIconSize(QSize(8, 8));
  forwardBtn->setEnabled(false);
  connect(forwardBtn, SIGNAL(clicked()), this, SLOT(slotForward()));

  catchCopyEventBtn = new QPushButton(QString("C"), widget1); // C
  catchCopyEventBtn->setToolTip(MW->MO->TS->CatchCopyEvent_v1);
  catchCopyEventBtn->setMinimumHeight(1);
  catchCopyEventBtn->setMinimumWidth(20);
  catchCopyEventBtn->setMaximumWidth(30);
  catchCopyEventBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  catchCopyEventBtn->setIconSize(QSize(8, 8));
  catchCopyEventBtn->setCheckable(true);
  catchCopyEventBtn->setChecked(false);
  connect(catchCopyEventBtn, SIGNAL(clicked()), this, SLOT(slotCatchCopyEvent()));

  catchSelectEventBtn = new QPushButton(QString("A+"), widget1); // A+ = Alt+Mouse
  catchSelectEventBtn->setToolTip(MW->MO->TS->CatchSelectEvent_v1);
  catchSelectEventBtn->setMinimumHeight(1);
  catchSelectEventBtn->setMinimumWidth(20);
  catchSelectEventBtn->setMaximumWidth(30);
  catchSelectEventBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  catchSelectEventBtn->setIconSize(QSize(8, 8));
  catchSelectEventBtn->setCheckable(true);
  catchSelectEventBtn->setChecked(false);
  connect(catchSelectEventBtn, SIGNAL(clicked()), this, SLOT(slotCatchSelectEvent()));

  mainTextView = new TextView(MW, widget1);
  mainTextView->setMinimumSize(1, 1);
  mainTextView->setFrameShape(QFrame::StyledPanel); // NoFrame  StyledPanel // Без рамка не стои добре, когато има показан скрол-бар. Затова в речниците се прави изключение и се използват рамки.
  mainTextView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mainTextView->setReadOnly(true);
  mainTextView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mainTextView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mainTextView->setText(QString("<font color=#00aaaa><b>%1</b></font>").arg(MW->MO->TS->ChooseDictionaryOrCommentary_v1));
  highlighter = new Highlighter(mainTextView->document());

  QWidget *widget2 = new QWidget(splitter);
  widget2->setMinimumSize(1, 1);

  prevGroupBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(0.0, 8.0) << QPointF(8.0, 8.0) << QPointF(4.0, 0.0), MW->MO->SVars.appColorB), QString(""), widget2); // ∧
  prevGroupBtn->setToolTip(MW->MO->TS->PreviousGroup_v1);
  prevGroupBtn->setMinimumHeight(1);
  prevGroupBtn->setMinimumWidth(20);
  prevGroupBtn->setMaximumWidth(30);
  prevGroupBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  prevGroupBtn->setIconSize(QSize(8, 8));
  connect(prevGroupBtn, SIGNAL(clicked()), this, SLOT(slotPrevGroup()));

  nextGroupBtn = new QPushButton(generatePixmap(QPolygonF() << QPointF(0.0, 0.0) << QPointF(8.0, 0.0) << QPointF(4.0, 8.0), MW->MO->SVars.appColorB), QString(""), widget2); // ∨
  nextGroupBtn->setToolTip(MW->MO->TS->NextGroup_v1);
  nextGroupBtn->setMinimumHeight(1);
  nextGroupBtn->setMinimumWidth(20);
  nextGroupBtn->setMaximumWidth(30);
  nextGroupBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  nextGroupBtn->setIconSize(QSize(8, 8));
  connect(nextGroupBtn, SIGNAL(clicked()), this, SLOT(slotNextGroup()));

  dictCmbBox = new QComboBox(widget2);
  dictCmbBox->setToolTip(MW->MO->TS->DictionariesAndCommentaries_v1);
  //dictCmbBox->setMinimumSize(1, 1); // Това е важно (да е коментирано) за преоразмеряването на панела, при смяна на големината на шрифта.
  dictCmbBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed); // Това е важно (Ignored и Fixed) за преоразмеряването на панела, при смяна на големината на шрифта.
  dictCmbBox->setIconSize(QSize(8, 8));
  dictCmbBox->setEditable(false);
  for (int i = 0; i < allFileNames.size(); i++)
  {
    dictCmbBox->addItem(readDictName(allFileNames[i]));
  }
  dictCmbBox->setCurrentIndex(-1); // За да не избира речник, при отваряне на нов речник.
  //dictCmbBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
  connect(dictCmbBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDictCmbBox_currentIndexChanged(int)));
  if (dictCmbBox->count() == 0)
  {
    mainTextView->setText(QString("<div><font color=#ff6050><b>%1</b></font></div><div><font color=#00aaaa><b>%2</b></font></div>").arg(MW->MO->TS->NoFoundDictsOrComms_v1).arg(QString("%1/DictAndComm").arg(MW->MO->applicationDirPath)));
  }

  otherWordsListWidget = new QListWidget(widget2);
  otherWordsListWidget->setMinimumSize(1, 1);
  otherWordsListWidget->setFrameShape(QFrame::StyledPanel); // NoFrame  StyledPanel // Без рамка не стои добре, когато има показан скрол-бар. Затова в речниците се прави изключение и се използват рамки.
  otherWordsListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  //otherWordsListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  //connect(otherWordsListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(slotListWidget_currentRowChanged(int)));
  connect(otherWordsListWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(slotListWidget_currentItemChanged(QListWidgetItem*)));
  connect(otherWordsListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotListWidget_currentItemChanged(QListWidgetItem*)));

  QGridLayout *gridLayout1 = new QGridLayout(widget1);
  gridLayout1->setContentsMargins(0, 0, 0, 0);
  gridLayout1->setSpacing(1);
  gridLayout1->addWidget(entryCmbBox, 0, 0, 1, 1);
  gridLayout1->addWidget(backBtn, 0, 1, 1, 1);
  gridLayout1->addWidget(forwardBtn, 0, 2, 1, 1);
  gridLayout1->addWidget(catchCopyEventBtn, 0, 3, 1, 1);
  gridLayout1->addWidget(catchSelectEventBtn, 0, 4, 1, 1);
  gridLayout1->addWidget(mainTextView, 1, 0, 1, 5);

  QGridLayout *gridLayout2 = new QGridLayout(widget2);
  gridLayout2->setContentsMargins(0, 0, 0, 0);
  gridLayout2->setSpacing(1);
  gridLayout2->addWidget(prevGroupBtn, 0, 0, 1, 1);
  gridLayout2->addWidget(nextGroupBtn, 0, 1, 1, 1);
  gridLayout2->addWidget(dictCmbBox, 0, 2, 1, 1);
  gridLayout2->addWidget(otherWordsListWidget, 1, 0, 1, 3);

  splitter->addWidget(widget1);
  splitter->addWidget(widget2);
  splitter->setStretchFactor(0, 70); // Това прави лявата част да е 70%,
  splitter->setStretchFactor(1, 30); // а дясната 30%.
  //splitter->restoreState(settings.value(QString("splitterSizes")).toByteArray());

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->setContentsMargins(1, 1, 1, 1);
  gridLayout->setSpacing(1);
  gridLayout->addWidget(splitter, 0, 0, 1, 1);

  setDicFontFamily();
  setDicFontSize();
  setDicColorScheme();

  connect(MW, SIGNAL(newSelectedText(QString)), this, SLOT(slotNewSelectedText(QString)));
  connect(MW, SIGNAL(newSelectedVerse(quint16, QString)), this, SLOT(slotNewSelectedVerse(quint16, QString)));
  clipboard = QApplication::clipboard();//QClipboard::changed ( QClipboard::Mode mode )
  QString txt = clipboard->text(); // Ако не извикам метода text(), слотът slotClipboard_changed, незнайно защо, не се извиква когато се копира текст във външна програма. Извикването на text() някак активира следенето на клипборда. Може би аз нещо не разбирам...
  connect(clipboard, SIGNAL(changed(QClipboard::Mode)), this, SLOT(slotClipboard_changed(QClipboard::Mode))); // Този ред да е след горния!

  setAttribute(Qt::WA_DeleteOnClose, true);
}

Dictionary::~Dictionary()
{
  if (file != 0)
  {
    file->close();
    delete file;
  }

  delete highlighter;
  delete mainTextView;
  delete entryCmbBox;
  delete backBtn;
  delete forwardBtn;
  delete catchCopyEventBtn;
  delete catchSelectEventBtn;
  delete prevGroupBtn;
  delete nextGroupBtn;
  delete dictCmbBox;
  delete otherWordsListWidget;
  delete splitter;
}

void Dictionary::setDicFontFamily(QString fontFamily)
{
  QFont font;
  if (fontFamily.isEmpty())
    fontFamily = MW->MO->mergeFontFamilies(DP.fontFamily, qApp->font().family());
  else
    fontFamily = MW->MO->mergeFontFamilies(DP.fontFamily, fontFamily);

  font = mainTextView->font();
  font.setFamily(fontFamily);
  mainTextView->setFont(font);

  font = entryCmbBox->font();
  font.setFamily(fontFamily);
  entryCmbBox->setFont(font); // Ако големината на този шрифт е по-голяма от големината на нормалния, entryCmbBox и бутоните до него ще станат по-големи от dictCmbBox и бутоните до него. И става малко грозно, но не се сещам как да го направя.

  font = otherWordsListWidget->font();
  font.setFamily(fontFamily);
  otherWordsListWidget->setFont(font);

  dictCmbBox->resize(entryCmbBox->width(), entryCmbBox->height());
}

void Dictionary::setDicFontSize()
{
  QFont font;
  int searchToolBarFontSize = MW->MO->SVars.searchToolBarFontSize; // Засега няма отделна опция за големина на шрифта на речника, а е обвързана с тази на панела за търсене.

  font = entryCmbBox->font();
  font.setPointSize(searchToolBarFontSize);
  entryCmbBox->setFont(font);

  font = backBtn->font();
  font.setPointSize(searchToolBarFontSize);
  backBtn->setFont(font);

  font = forwardBtn->font();
  font.setPointSize(searchToolBarFontSize);
  forwardBtn->setFont(font);

  font = catchCopyEventBtn->font();
  font.setPointSize(searchToolBarFontSize);
  catchCopyEventBtn->setFont(font);

  font = catchSelectEventBtn->font();
  font.setPointSize(searchToolBarFontSize);
  catchSelectEventBtn->setFont(font);

  font = prevGroupBtn->font();
  font.setPointSize(searchToolBarFontSize);
  prevGroupBtn->setFont(font);

  font = nextGroupBtn->font();
  font.setPointSize(searchToolBarFontSize);
  nextGroupBtn->setFont(font);

  font = dictCmbBox->font();
  font.setPointSize(searchToolBarFontSize);
  dictCmbBox->setFont(font);

  font = otherWordsListWidget->font();
  font.setPointSize(searchToolBarFontSize);
  otherWordsListWidget->setFont(font);
}

void Dictionary::setDicColorScheme()
{
  mainTextView->setColorScheme();

  QPalette pal = otherWordsListWidget->palette();
  pal.setBrush(QPalette::Base, MW->MO->SVars.dock2TextColorB); // Цвят на фона.
  pal.setBrush(QPalette::Text, MW->MO->SVars.dock2TextColorF); // Цвят на текста.
  otherWordsListWidget->setPalette(pal);

  pal = entryCmbBox->palette();
  pal.setBrush(QPalette::Base, MW->MO->SVars.dock1TextColorB); // Цвят на фона.
  pal.setBrush(QPalette::Text, MW->MO->SVars.dock1TextColorF); // Цвят на текста.
  entryCmbBox->setPalette(pal);
}

void Dictionary::clearDP()
{
  DP.structureVersion = 0;
  DP.lastModifyDate = "";
  DP.fontFamily = "";
  DP.layoutDirection = Qt::LeftToRight;
  DP.dictName = "";
  DP.dictVersion = "";
  DP.dictAuthor = "";
  DP.dictShortDescription = "";
  DP.dictDescription = "";
  DP.charSet1_Enable = false;
  DP.charSet1_Chars = "";
  DP.charSet1_Color = "";
  DP.charSet1_Bold = QFont::Normal;
  DP.charSet1_Italic = false;
  DP.charSet1_Underline = false;
  DP.charSet2_Enable = false;
  DP.charSet2_Chars = "";
  DP.charSet2_Color = "";
  DP.charSet2_Bold = QFont::Normal;
  DP.charSet2_Italic = false;
  DP.charSet2_Underline = false;
  DP.charSet3_Enable = false;
  DP.charSet3_Chars = "";
  DP.charSet3_Color = "";
  DP.charSet3_Bold = QFont::Normal;
  DP.charSet3_Italic = false;
  DP.charSet3_Underline = false;
  DP.textInBracket_Enable = false;
  DP.textInBracket_Color = "";
  DP.textInBracket_Bold = QFont::Normal;
  DP.textInBracket_Italic = false;
  DP.textInBracket_Underline = false;
  DP.textInSquareBracket_Enable = false;
  DP.textInSquareBracket_Color = "";
  DP.textInSquareBracket_Bold = QFont::Normal;
  DP.textInSquareBracket_Italic = false;
  DP.textInSquareBracket_Underline = false;
  DP.textInBrace_Enable = false;
  DP.textInBrace_Color = "";
  DP.textInBrace_Bold = QFont::Normal;
  DP.textInBrace_Italic = false;
  DP.textInBrace_Underline = false;
  DP.latinNumeration_Enable = false;
  DP.latinNumeration_Color = "";
  DP.latinNumeration_Bold = QFont::Normal;
  DP.latinNumeration_Italic = false;
  DP.latinNumeration_Underline = false;
  DP.arabicNumeration_Enable = false;
  DP.arabicNumeration_Color = "";
  DP.arabicNumeration_Bold = QFont::Normal;
  DP.arabicNumeration_Italic = false;
  DP.arabicNumeration_Underline = false;
  DP.equalSymbols_Enable = false;
  DP.equalSymbols1.clear();
  DP.equalSymbols2.clear();
}

void Dictionary::keyPressEvent(QKeyEvent * event)
{
  QWidget::keyPressEvent(event);

  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) // Key_Return - клавиш ENTER; Key_Enter - ENTER на малката клавиатура.
  {
    if (!entryCmbBox->lineEdit()->text().isEmpty())
    {
      QString text = entryCmbBox->lineEdit()->text().trimmed();
      if (entryCmbBox->findText(text) < 0) entryCmbBox->addItem(text); // Добавя текста (ако няма такъв) в падащия списък при натискане на ENTER.

      if ( (currentIndexInBFList < 0) || (BFList[currentIndexInBFList] != text) ) // Ако списъкът е празен или новият стринг е различен от стария.
      {
        // Изтрива всички стрингове след текущата:
        while( currentIndexInBFList < (BFList.count() - 1) ) // Ако текущият индекс не е последен в списъка.
        {
          BFList.removeLast(); // Изтрива последния стринг, докато текущият стане последен.
        }

        BFList << text;
        currentIndexInBFList = BFList.count() - 1;
      
        backBtn->setEnabled(true);
        forwardBtn->setEnabled(false);
      }

      entryCmbBox->lineEdit()->selectAll();
      entryCmbBox->setFocus();
    }
  }
}

QPixmap Dictionary::generatePixmap(QPolygonF polygon, QColor iconColor)
{
  QPainterPath path;
  path.addPolygon(polygon);

  QPixmap pix(8, 8);
  pix.fill(QColor(0, 0, 0, 0));

  QPainter painter(&pix);
  painter.setRenderHints(QPainter::Antialiasing, true);
  painter.fillPath(path, iconColor);

  return pix;
}

void Dictionary::loadDict(QString fileName)
{
  QString line; // Ред от файла.
  char buf[BUF_LEN];
  bool headerError = false;
  fileName = QString("%1/DictAndComm/%2").arg(MW->MO->applicationDirPath).arg(fileName);
  QString fileNameInd = QString("%1.ind").arg(fileName); // Индексният файл.
  currentIndex = -1;
  currentIndexInList = -1;
  SEEKS.clear();
  if (SEEKS_COMM != 0)
  {
    delete [] SEEKS_COMM;
    SEEKS_COMM = 0;
  }
  if (!isDictionary) SEEKS_COMM = new QInt64List[MAX_VERSES];
  qint64 SEEKS_COMM_Size = 0;
  QString sameWords = "";
  entryCmbBox->setEnabled(isDictionary);
  backBtn->setEnabled(isDictionary);
  forwardBtn->setEnabled(isDictionary);
  catchCopyEventBtn->setEnabled(isDictionary);
  prevGroupBtn->setEnabled(isDictionary);
  nextGroupBtn->setEnabled(isDictionary);
  otherWordsListWidget->setToolTip(isDictionary ? "" : MW->MO->TS->PossibleDifferentVerseNumber_v1);
  entryCmbBox->setEditText(""); // Това ще вдигне ивента за промяна на текста, но слотът няма да направи нищо.
  hitMarker->setPalette(hitMarkerPaletteNormal);

  if (QFile::exists(fileName) && QFile::exists(fileNameInd))
  {
    QFileInfo fileInfo(fileName);
    QFileInfo fileInfoInd(fileNameInd);
    if (fileInfo.lastModified() >= fileInfoInd.lastModified()) // Ако файлът с речника е модифициран (т.е. индексният е стар).
    {
      QFile::remove(fileNameInd);
    }
    else // Ако индексният файл е по-нов.
    {
      QFile lFile(fileNameInd);
      lFile.open(QIODevice::ReadOnly);
      bool OK = true;

      // Чете данните:
      if (isDictionary) // Ако е речник.
      {
        while (!lFile.atEnd())
        {
          lFile.readLine(buf, sizeof(buf)); // Чете следващ ред.
          line = QString("%1").arg(buf);
          line = line.trimmed(); // Изтрива се ненужната информация - премахва  '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
          if (line.isEmpty()) continue;
        
          SEEKS << line.toLongLong(&OK);
          if (!OK) break; // Ако индексният файл е повреден.
        }
      }
      else // Ако е коментар.
      {
        int index = 0;
        QStringList allSeeks;

        lFile.readLine(buf, sizeof(buf)); // Чете първия ред (броя на коментарите).
        line = QString("%1").arg(buf);
        SEEKS_COMM_Size = line.trimmed().toLongLong(&OK); // Брой на коментарите. Служи само за да покаже броя при първоначално зареждане на коментара и затова не следя дали стойността му е прочетена правилно (ако има проблем ще е нула).

        while (!lFile.atEnd())
        {
          lFile.readLine(buf, sizeof(buf)); // Чете следващ ред.
          line = QString("%1").arg(buf);
          line = line.trimmed(); // Изтрива се ненужната информация - премахва  '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
          if (line.isEmpty()) continue;
        
          allSeeks = line.split(" ", QString::SkipEmptyParts);
          if (allSeeks.count() < 1)
          {
            OK = false;
            break; // Ако индексният файл е повреден.
          }
          index = allSeeks[0].trimmed().toLongLong(&OK);
          if (index < OT_START_INDEX || index > ONT_END_INDEX) OK = false;
          if (!OK) break; // Ако индексният файл е повреден.
          index = MW->MO->toEasternExtIndexIfNeed(index); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
          for (int i = 1; i < allSeeks.count(); i++)
          {
            SEEKS_COMM[index - OT_START_INDEX] << allSeeks[i].trimmed().toLongLong(&OK);
            if (!OK) break; // Ако индексният файл е повреден.
          }
        }
      }

      lFile.close();

      if (OK)
      {
        delete file;
        file = new QFile(fileName); // Този файл е работният - при търсене в речника.
        file->open(QIODevice::ReadOnly);
        headerError = loadHeader(); // Чете хедъра на файла (използва file).
      }
      else // Ако индексният файл е повреден.
      {
        QFile::remove(fileNameInd);
        SEEKS_COMM_Size = 0; // Това нулиране тук е важно.
      }
    }
  }
  else
  {
    QFile::remove(fileNameInd); // Ако нещо не е наред, изтрива индексния файл (ако изобщо има такъв) и по-долу го създава отново.
  }

  if (QFile::exists(fileName) && !QFile::exists(fileNameInd)) // Ако има файл с речник, но няма индексен файл.
  {
    QProgressBar *progressBar = new QProgressBar(mainTextView->isVisible() ? mainTextView : 0); // Ако програмата все още не се е показала, показва прогресбара като самостоятелен елемент.
    progressBar->setMinimum(0);
    progressBar->setMaximum(40); // Това е умишлено 40, а прогресбарът цъка веднъж на 5000 думи за да не бави процеса на зареждане (т.е. прогресбарът е настроен на 200000 думи максимум).
    progressBar->resize(mainTextView->isVisible() ? mainTextView->size().width() : 300, MW->MO->SVars.globalFontSize + 10);
    progressBar->setAlignment(Qt::AlignHCenter);
    progressBar->setFormat(QString("Indexing...")); // Indexing %p%
    progressBar->show();

    QFile lFile(fileName); // Този файл е само за този метод - при зареждане на речника.
    lFile.open(QIODevice::ReadOnly);
    delete file;
    file = new QFile(fileName); // Този файл е работният - при търсене в речника.
    file->open(QIODevice::ReadOnly);
    headerError = loadHeader(); // Чете хедъра на файла (използва file).

    // Чете данните:
    QString word = "";   // Текуща дума.
    qint64 seek = 0;     // Положение във файла на текущия ред.
    qint64 wordSeek = 0; // Положение във файла на текущата дума.
    QInt64List indexes;
    while (!lFile.atEnd())
    {
      seek = lFile.pos(); // Тук seek сочи към началото на реда, който ще бъде прочетен в следващия ред.
      lFile.readLine(buf, sizeof(buf)); // Чете следващ ред.
      line = QString("%1").arg(buf);
      line.remove(QString("\r\n"));
      line.remove(QString("\n"));
      line = line.trimmed(); // Изтрива се ненужната информация - премахва  '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
      if (line.isEmpty()) continue;
    
      if (line.indexOf("##") == 0) // Така започва всяка дума в речник и всяка препратка в коментар.
      {
        if (!word.isEmpty()) // Записва seek към предната дума.
        {
          if (isDictionary) // Ако е речник.
          {
            SEEKS.insert(getIndexInSortSEEKSList(replaceSymbols(word)), wordSeek);
            progressBar->setValue(SEEKS.size()/5000); // Така прогресбарът ще се опреснява веднъж на всеки 5000 думи. Ако го прави на по-често (например на всяка дума), самият прогресбар забавя зареждането драстично.
          }
          else // Ако е коментар.
          {
            indexes = convertToIndexes(word);
            foreach (qint64 index, indexes)
            {
              index = MW->MO->toEasternExtIndexIfNeed(index); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
              SEEKS_COMM[index - OT_START_INDEX] << wordSeek;
            }
            SEEKS_COMM_Size++; // Тук ще покаже колко е реалният брой на коментарите. Този брой може да се изчисли само тук, затова трябва да се запомни в индексния файл (на първия ред).
            progressBar->setValue(SEEKS_COMM_Size/500); // Така прогресбарът ще се опреснява веднъж на всеки 500 коментара. Ако го прави на по-често (например на всеки коментар), самият прогресбар забавя зареждането драстично.
         }
        }
        word = line.remove(0, 2); // Изтрива ##.
        wordSeek = seek;
      }
    }
    if (!word.isEmpty()) // Записва последната дума.
    {
      if (isDictionary) // Ако е речник.
      {
        SEEKS.insert(getIndexInSortSEEKSList(replaceSymbols(word)), wordSeek);
      }
      else // Ако е коментар.
      {
        indexes = convertToIndexes(word);
        foreach (qint64 index, indexes)
        {
          index = MW->MO->toEasternExtIndexIfNeed(index); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
          SEEKS_COMM[index - OT_START_INDEX] << wordSeek;
        }
        SEEKS_COMM_Size++; // Тук ще покаже колко е реалният брой на коментарите. Този брой може да се изчисли само тук, затова трябва да се запомни в индексния файл (на първия ред).
      }
    }

    lFile.close();

    // Създава индексния файл:
    QFile wfile(fileNameInd);
    wfile.open(QIODevice::WriteOnly);
    if (isDictionary) // Ако е речник.
    {
      for (int i = 0; i < SEEKS.size(); i++)
      {
        wfile.write(QString("%1\r\n").arg(SEEKS[i]).toUtf8());
      }
    }
    else // Ако е коментар.
    {
      wfile.write(QString("%1\r\n").arg(SEEKS_COMM_Size).toUtf8()); // На първия ред записва броя на коментарите. Това е нужно, защото при четене от индексния файл, е невъзможно да се изчисли какъв точно е броят на коментарите.
      for (int i = 0; i < MAX_VERSES; i++)
      {
        word = ""; // Тук word се използва като помощна променлива.
        for (int j = 0; j < SEEKS_COMM[i].count(); j++)
        {
          word += QString(" %1").arg(SEEKS_COMM[i][j]);
        }
        if (!word.isEmpty())
        {
          wfile.write(QString("%1%2\r\n").arg(MW->MO->toWesternExtIndexIfNeed(i)).arg(word).toUtf8()); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
        }
      }
    }
    wfile.close();

    // Проверка за коректност на файла (проверява дали има повтарящи се думи, което не е нормално за речник):
    if (isDictionary) // Ако е речник.
    {
      progressBar->setValue(0);
      progressBar->setFormat(QString("Checking...")); // Checking %p%
      QString prevWordMod = ""; // Предходна дума (модифицирана).
      QString currWordMod = ""; // Текуща дума (модифицирана).
      QString prevWordOrg = ""; // Предходна дума (оригинална).
      QString currWordOrg = ""; // Текуща дума (оригинална).
      for (int i = 0; i < SEEKS.size(); i++)
      {
        currWordOrg = getWord(SEEKS[i]);
        currWordMod = replaceSymbols(currWordOrg);
        progressBar->setValue(i/5000); // Така прогресбарът ще се опреснява веднъж на всеки 5000 думи. Ако го прави на по-често (например на всяка дума), самият прогресбар забавя зареждането драстично.
        if (QString::compare(prevWordOrg, currWordOrg, Qt::CaseInsensitive) == 0) // Ако има точно съвпадение.
        {
          sameWords += QString("<div><b>%1</b></div>").arg(currWordOrg);
        }
        prevWordMod = currWordMod;
        prevWordOrg = currWordOrg;
      }
    }

    delete progressBar;
  }

  // English-Bulgarian-English Dictionary
  // Версия: 1.0
  // Автор: 
  // ------------------------------------
  // English-Bulgarian-English Dictionary
  // More than 250000 words and phrases.
  // 
  // Contributor: Wise Guy
  // Source: Unknown
  // ------------------------------------
  // Име на файла: eb.dct
  // Всички думи/фрази: 88363
  // ------------------------------------

  mainTextView->clear();
  mainTextView->dockWidget->setDockWidgetTitle(QString("<b>%1</b>").arg(DP.dictShortDescription));
  //setDicFontFamily(MW->MO->SVars.fontFamily); // Който и метод от тези два да се избере, трябва да се избере и подобния на него във файла mainwindow.cpp, в метода FontChanged().
  setDicFontFamily();
  highlighter->setDictPatterns(&DP);
  // Всеки TS стринг по-долу е в собствен <div> таг, за да се покаже правилно, според собственото си ляво или дясно подравняване.
  if (headerError)
  {
    mainTextView->dockWidget->setDockWidgetTitle(QString("<b>%1</b>").arg(MW->MO->TS->DictionaryCommentary_v1));
    mainTextView->append(QString("<div><font color=#ff0000>%1</font></div><div><font color=#ff0000><b>%2</b></font></div><div></div>").arg(MW->MO->TS->IncorrectHeaderSection_v1).arg(fileName));
  }
  if (SEEKS.size() > 0 || SEEKS_COMM != 0)
  {
    mainTextView->append(QString("<div><b>%1</b></div><div><b>%2 %3</b></div><div><b>%4 %5</b></div><hr><div>%6</div><div></div>").arg(DP.dictShortDescription).arg(MW->MO->TS->Version_v1).arg(DP.dictVersion).arg(MW->MO->TS->Author_v1).arg(DP.dictAuthor).arg(DP.dictDescription));
  
    if (isDictionary) // Ако е речник.
    {
      mainTextView->append(QString("<div>%1 %2</div><div>%3 <b>%4</b></div><div></div>").arg(MW->MO->TS->FileName_v1).arg(allFileNames[dictCmbBox->currentIndex()]).arg(MW->MO->TS->AllWordsPhrases_v1).arg(SEEKS.size()));
    }
    else // Ако е коментар.
    {
      mainTextView->append(QString("<div>%1 %2</div><div>%3 <b>%4</b></div><div></div>").arg(MW->MO->TS->FileName_v1).arg(allFileNames[dictCmbBox->currentIndex()]).arg(MW->MO->TS->AllCommentary_v1).arg(SEEKS_COMM_Size));
    }
  }
  else
  {
    mainTextView->dockWidget->setDockWidgetTitle(QString("<b>%1</b>").arg(MW->MO->TS->DictionaryCommentary_v1));
    mainTextView->append(QString("<div><font color=#ff0000>%1</font></div><div><font color=#ff0000><b>%2</b></font></div>").arg(MW->MO->TS->IncorrectDataSection_v1).arg(fileName));
  }
  if (!sameWords.isEmpty())
  {
    mainTextView->append(QString("<div><font color=#ff0000><br />%1</font></div>%2<div></div>").arg(MW->MO->TS->EqualWordsExpressions_v1).arg(sameWords));
  }
  mainTextView->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor); // Това позиционира в началото.

  if (isDictionary)
    slotPrevGroup();
  else
    otherWordsListWidget->clear();
  //QTime timer; timer.start(); //---------------------------------------------------------------------------------------------------------
  //mainTextView->dockWidget->setDockWidgetTitle(QString("%1").arg(timer.elapsed())); //-------------------------------------------------------
}

QString Dictionary::readDictName(QString fileName)
{
  QString line = ""; // Ред от файла.
  char buf[BUF_LEN];
  QString fullFileName = QString("%1/DictAndComm/%2").arg(MW->MO->applicationDirPath).arg(fileName);

  if (QFile::exists(fullFileName))
  {
    QFile *file = new QFile(fullFileName);
    file->open(QIODevice::ReadOnly);

    file->readLine(buf, sizeof(buf)); // Чете първи ред.
    file->readLine(buf, sizeof(buf)); // Чете втори ред.
    file->readLine(buf, sizeof(buf)); // Чете трети ред.
    file->readLine(buf, sizeof(buf)); // Чете четвърти ред.
    file->readLine(buf, sizeof(buf)); // Чете пети ред, който съдържа DICT_NAME.
    line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
    if (line.contains(QString("DICT_NAME=")))
    {
      line = line.remove(QString("DICT_NAME=")); // Изтрива се ненужната информация.
    }
    else // Ако не съдържа очаквания ред.
    {
      line = "";
    }

    file->close();
    delete file;
  }

  if (line.isEmpty())
    return fileName;
  else
    return line;
}

bool Dictionary::loadHeader()
{
  QString line; // Ред от файла.
  char buf[BUF_LEN];
  bool headerError = false;
  QString value = "";

  clearDP();

  if ( readNextHeaderString(QString("STRUCTURE_VERSION"), &value) )
    DP.structureVersion = value.toInt();
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if (DP.structureVersion != 1) return true; // Ако файлът има структура различна от очакваната (прекратява незабавно четенето на хедъра, защото ще стане голяма каша надолу).

  if ( readNextHeaderString(QString("LAST_MODIFY_DATE"), &value) )
    DP.lastModifyDate = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("FONT_FAMILY"), &value) )
    DP.fontFamily = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("LAYOUT_DIRECTION"), &value) )
    { if (value.toUpper() == "RIGHTTOLEFT" || value.toUpper() == "RIGHT_TO_LEFT") DP.layoutDirection = Qt::RightToLeft; }
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("DICT_NAME"), &value) )
    DP.dictName = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("DICT_VERSION"), &value) )
    DP.dictVersion = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("DICT_AUTHOR"), &value) )
    DP.dictAuthor = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("DICT_SHORT_DESCRIPTION"), &value) )
    DP.dictShortDescription = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // Чете редовете на Description. Тук не използвам метода readNextHeaderString, защото има малки но важни разлики.
  file->readLine(buf, sizeof(buf));
  line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
  if (line.isEmpty()) // Ако е прочетен празен ред.
  {
    file->readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
  }
  if (line.contains(QString("DICT_DESCRIPTION__BEGIN")))
  {
    bool success = false;
    for (int r = 0; r < 300; r++) // Може да прочете максимум 300 реда Description.
    {
      file->readLine(buf, sizeof(buf));
      line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   //line = line.trimmed();
      if (line.contains(QString("DICT_DESCRIPTION__END")))
      {
        success = true;
        break;
      }
      DP.dictDescription += line;
    }
    if (!success) // Ако при четенето на редовете не е достигнато до DICT_DESCRIPTION__END.
    {
      return true; // Прекратява незабавно четенето на хедъра, защото ще стане голяма каша надолу.
    }
  }
  else // Ако не съдържа очаквания ред.
  {
    return true; // Прекратява незабавно четенето на хедъра, защото ще стане голяма каша надолу.
  }

  // CHARSET_1 ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("CHARSET_1__ENABLE"), &value) )
    DP.charSet1_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_1__CHARS"), &value) )
    DP.charSet1_Chars = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_1__COLOR"), &value) )
    DP.charSet1_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_1__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.charSet1_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_1__ITALIC"), &value) )
    DP.charSet1_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_1__UNDERLINE"), &value) )
    DP.charSet1_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // CHARSET_2 ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("CHARSET_2__ENABLE"), &value) )
    DP.charSet2_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_2__CHARS"), &value) )
    DP.charSet2_Chars = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_2__COLOR"), &value) )
    DP.charSet2_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_2__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.charSet2_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_2__ITALIC"), &value) )
    DP.charSet2_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_2__UNDERLINE"), &value) )
    DP.charSet2_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // CHARSET_3 ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("CHARSET_3__ENABLE"), &value) )
    DP.charSet3_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_3__CHARS"), &value) )
    DP.charSet3_Chars = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_3__COLOR"), &value) )
    DP.charSet3_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_3__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.charSet3_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_3__ITALIC"), &value) )
    DP.charSet3_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("CHARSET_3__UNDERLINE"), &value) )
    DP.charSet3_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // TEXT_IN_BRACKET ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("TEXT_IN_BRACKET__ENABLE"), &value) )
    DP.textInBracket_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACKET__COLOR"), &value) )
    DP.textInBracket_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACKET__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.textInBracket_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACKET__ITALIC"), &value) )
    DP.textInBracket_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACKET__UNDERLINE"), &value) )
    DP.textInBracket_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // TEXT_IN_SQUARE_BRACKET ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("TEXT_IN_SQUARE_BRACKET__ENABLE"), &value) )
    DP.textInSquareBracket_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_SQUARE_BRACKET__COLOR"), &value) )
    DP.textInSquareBracket_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_SQUARE_BRACKET__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.textInSquareBracket_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_SQUARE_BRACKET__ITALIC"), &value) )
    DP.textInSquareBracket_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_SQUARE_BRACKET__UNDERLINE"), &value) )
    DP.textInSquareBracket_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // TEXT_IN_BRACE ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("TEXT_IN_BRACE__ENABLE"), &value) )
    DP.textInBrace_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACE__COLOR"), &value) )
    DP.textInBrace_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACE__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.textInBrace_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACE__ITALIC"), &value) )
    DP.textInBrace_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("TEXT_IN_BRACE__UNDERLINE"), &value) )
    DP.textInBrace_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // LATIN_NUMERATION ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("LATIN_NUMERATION__ENABLE"), &value) )
    DP.latinNumeration_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("LATIN_NUMERATION__COLOR"), &value) )
    DP.latinNumeration_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("LATIN_NUMERATION__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.latinNumeration_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("LATIN_NUMERATION__ITALIC"), &value) )
    DP.latinNumeration_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("LATIN_NUMERATION__UNDERLINE"), &value) )
    DP.latinNumeration_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // ARABIC_NUMERATION ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("ARABIC_NUMERATION__ENABLE"), &value) )
    DP.arabicNumeration_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("ARABIC_NUMERATION__COLOR"), &value) )
    DP.arabicNumeration_Color = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("ARABIC_NUMERATION__BOLD"), &value) )
    { if (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE")) DP.arabicNumeration_Bold = QFont::Bold; } // QFont::Normal QFont::Bold
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("ARABIC_NUMERATION__ITALIC"), &value) )
    DP.arabicNumeration_Italic = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if ( readNextHeaderString(QString("ARABIC_NUMERATION__UNDERLINE"), &value) )
    DP.arabicNumeration_Underline = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  // EQUAL_SYMBOLS ---------------------------------------------------------------------------------------------------------
  if ( readNextHeaderString(QString("EQUAL_SYMBOLS__ENABLE"), &value) )
    DP.equalSymbols_Enable = (value.toUpper() == QString("YES") || value.toUpper() == QString("TRUE"));
  else // Ако не съдържа очаквания ред.
    headerError = true;

  QString equalSymbols = "";
  if ( readNextHeaderString(QString("EQUAL_SYMBOLS__EXPRESSIONS"), &value) ) // EQUAL_SYMBOLS__EXPRESSIONS=à=a,á=a,â=a,ã=a,ä=a,å=a,ç=c,è=e,é=e,ê=e,ë=e,ì=i,í=i,î=i,ï=i,ñ=n,ò=o,ó=o,ô=o,õ=o,ö=o,ù=u,ú=u,û=u,ü=u,ý=y,ÿ=y
    equalSymbols = value;
  else // Ако не съдържа очаквания ред.
    headerError = true;

  if (DP.equalSymbols_Enable && !equalSymbols.isEmpty())
  {
    QStringList allExpressions = equalSymbols.split(",", QString::SkipEmptyParts);
    QStringList expression;
    for (int i = 0; i < allExpressions.count(); i++)
    {
      expression = allExpressions[i].split("=", QString::SkipEmptyParts);
      if (expression.count() == 2)
      {
        DP.equalSymbols1 << expression[0].trimmed();
        DP.equalSymbols2 << expression[1].trimmed();
      }
    }
  }
  if (DP.equalSymbols1.count() == 0) DP.equalSymbols_Enable = false;

  return headerError;
}

bool Dictionary::readNextHeaderString(QString expectLine, QString *value)
{
  QString line; // Ред от файла.
  char buf[BUF_LEN];
  *value = "";

  file->readLine(buf, sizeof(buf));
  line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
  if (line.isEmpty()) // Ако е прочетен празен ред.
  {
    file->readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
  }
  if (line.isEmpty()) // Ако е прочетен втори празен ред (допуска се до два празни реда).
  {
    file->readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf);   line.remove(QString("\r\n"));   line.remove(QString("\n"));   line = line.trimmed();
  }

  if (line.contains(QString("%1=").arg(expectLine)))
  {
    *value = line.remove(QString("%1=").arg(expectLine)); // Изтрива се ненужната информация.
    return true;
  }
  else if (line.contains(QString("%1 =").arg(expectLine)))
  {
    *value = line.remove(QString("%1 =").arg(expectLine)); // Изтрива се ненужната информация.
    return true;
  }
  else // Ако не съдържа очаквания ред.
  {
    return false;
  }
}

int Dictionary::getIndexInSortSEEKSList(QString word)
{
  // Двоично търсене в списъка. Резултатът е винаги или индексът на търсената дума или индексът на следващата най-близка.

  int iRes = -1;
  int a = 0; // Сега a е първият елемент.
  int b = SEEKS.size()-1; // Сега b е последният елемент.
  int m = -1;

  // Първо сравнява с последния елемент и ако новата дума е след текущата по азбучен ред, се избягва двуичното търсене по-долу:
  if (b >= 0)
  {
    iRes = QString::compare(word, replaceSymbols(getWord(SEEKS[b])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
    if (iRes >= 0) return b+1;
  }

  // Двоично търсене в списъка:
  while (a <= b)
  {
    m = (a+b)/2; // m е средният елемент между a и b.
    iRes = QString::compare(word, replaceSymbols(getWord(SEEKS[m])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
    if (iRes == 0) // Ако има съвпадение.
    {
      return m;
    }
    else
    {
      if (iRes < 0) // Ако търсената дума е преди текущата по азбучен ред.
        b = m-1;
      else // Ако търсената дума е след текущата по азбучен ред.
        a = m+1;
    }
  }
  return b+1; // b+1 или a.
}

QInt64List Dictionary::convertToIndexes(QString links)
{
  // Този метод преобразува препратките в стихове и връща индекса в масива за всеки стих.
  // Самите препратки се явяват реалния номер на реда на съответния стих в .hbt файловете.
  // Това налага версията на структурата на коментара да е същата като тази на .hbt файла.
  // Например - ако препратката е само един стих - ще върне индекса само на този стих.
  // Ако препратката е от няколко стиха, ще върне индексите на всички стихове от тази глава(и).
  //
  // ##12000                   - Точно определен стих (това е номерът на реда в .hbt файла, на който се намира този стих).
  // ##12000-12030             - Няколко стиха от - до (включително). По този начин могат да се направят коментари за няколко стиха от една глава, за няколко стиха от края на една глава и началото на друга, за цяла глава, цяла книга, цял завет и цялата Библия.
  // ##12000-12030;12080-12095 - Като горното, но се повтаря неграничен брой пъти за различни части, разделени с точка и запетая.

  QInt64List indexes;
  bool OK = true;
  qint64 index1, index2;
  QStringList fromTo;
  QStringList expressions = links.split(";", QString::SkipEmptyParts);
  foreach (QString expression, expressions)
  {
    fromTo = expression.trimmed().split("-", QString::SkipEmptyParts);
    if (fromTo.count() == 1)
    {
      index1 = fromTo[0].trimmed().toLongLong(&OK);
      if (!OK) break;
      index1 = index1 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index1 < OT_START_INDEX || index1 > ONT_END_INDEX) break;

      indexes << index1;
    }
    else if (fromTo.count() == 2)
    {
      index1 = fromTo[0].trimmed().toLongLong(&OK);
      if (!OK) break;
      index1 = index1 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index1 < OT_START_INDEX || index1 > ONT_END_INDEX) break;

      index2 = fromTo[1].trimmed().toLongLong(&OK);
      if (!OK) break;
      index2 = index2 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index2 < OT_START_INDEX || index2 > ONT_END_INDEX) break;

      if (index1 > index2) break;

      for (int i = index1; i <= index2; i++)
      {
        indexes << i;
      }
    }
    else
    {
      break;
    }
  }

  return indexes;
}

QString Dictionary::convertToReference(QString links)
{
  // Този метод преобразува числовите препратки (12000-12030;12080-12095) в смислени препратки (Битие 1:1 - Битие 1:30; Битие 2:1 - Битие 2:15).

  QString ref = "";
  bool OK = true;
  qint64 index1, index2;
  QStringList fromTo;
  QStringList expressions = links.split(";", QString::SkipEmptyParts);
  foreach (QString expression, expressions)
  {
    fromTo = expression.trimmed().split("-", QString::SkipEmptyParts);
    if (fromTo.count() == 1)
    {
      index1 = fromTo[0].trimmed().toLongLong(&OK);
      if (!OK) break;
      index1 = index1 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index1 < OT_START_INDEX || index1 > ONT_END_INDEX) break;

      index1 = MW->MO->toEasternExtIndexIfNeed(index1); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
      if (!ref.isEmpty()) ref += QString("; ");
      ref += QString("%1").arg(MW->MO->absIndexToReference(index1));
    }
    else if (fromTo.count() == 2)
    {
      index1 = fromTo[0].trimmed().toLongLong(&OK);
      if (!OK) break;
      index1 = index1 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index1 < OT_START_INDEX || index1 > ONT_END_INDEX) break;

      index2 = fromTo[1].trimmed().toLongLong(&OK);
      if (!OK) break;
      index2 = index2 - 1; // Първият стих е на ред 1 в .hbt файла, но тук трябва да стане индекс т.е. да започва от нула.
      if (index2 < OT_START_INDEX || index2 > ONT_END_INDEX) break;

      if (index1 > index2) break;
      index1 = MW->MO->toEasternExtIndexIfNeed(index1); // Ако подредбата на книгите е по източния стандарт, тук се прави конвертиране, защото абсолютният индекс, който идва от коментара е винаги по западния.
      index2 = MW->MO->toEasternExtIndexIfNeed(index2); //
      if (!ref.isEmpty()) ref += QString("; ");

      if (index1 == OT_START_INDEX && index2 == ONT_END_INDEX) // Ако е за цялата Библия.
        ref += MW->MO->TS->AllBooks_v1;
      else if (index1 == OT_START_INDEX && index2 == (NT_START_INDEX-1)) // Ако е за целия Стар Завет.
        ref += MW->MO->TS->TheOldTestament_v1;
      else if (index1 == NT_START_INDEX && index2 == ONT_END_INDEX) // Ако е за целия Нов Завет.
        ref += MW->MO->TS->TheNewTestament_v1;
      else // При всички останали случаи.
        ref += QString("%1 - %2").arg(MW->MO->absIndexToReference(index1)).arg(MW->MO->absIndexToReference(index2));
    }
    else
    {
      break;
    }
  }

  return ref;
}

void Dictionary::showWord(int index)
{
  if (isDictionary)
  {
    if (index >= 0 && index < SEEKS.size())
    {
      mainTextView->clear();
      currentIndex = index;
      QString word = getWord(SEEKS[index]);
      mainTextView->setHtml(QString("<b>%1</b><hr>%2").arg(word).arg(getDescription(SEEKS[index])));
    
      if (otherWordsListWidget->count() == 0 || word.toLower() != otherWordsListWidget->currentItem()->text().toLower()) // Ако НЕ е натиснато върху списъка с други думи.
      {
        otherWordsListWidget->clear();
        currentIndexInList = index;
        for (int i = 0; i < wordsInListBox; i++)
        {
          if ((currentIndexInList+i) >= SEEKS.size()) break;
          otherWordsListWidget->addItem(getWord(SEEKS[currentIndexInList+i]));
        }
        if (otherWordsListWidget->count() > 0) otherWordsListWidget->setCurrentRow(0);
      }
    }
  }
  else
  {
    if (index < OT_START_INDEX || index >= ONT_END_INDEX) return;
    mainTextView->clear();
    QString description = "";
    if (currentIndex != index) // Ако трябва да се покаже коментарът за нов стих.
    {
      currentIndex = index;
      otherWordsListWidget->clear();
      currentIndexInList = -1;
      if (SEEKS_COMM[index - OT_START_INDEX].count() > 0)
      {
        description = getDescription(SEEKS_COMM[index - OT_START_INDEX][0]);

        for (int i = 0; i < SEEKS_COMM[index - OT_START_INDEX].count(); i++)
        {
          otherWordsListWidget->addItem(convertToReference(getWord(SEEKS_COMM[index - OT_START_INDEX][i]))); // ##10-12;14-18;40-50
        }
        otherWordsListWidget->setCurrentRow(0);
        currentIndexInList = 0;
      }
    }
    else // Ако трябва да се покаже друг коментар, за същия стих (т.е. ако е натиснато върху списъка с други коментари).
    {
      currentIndexInList = otherWordsListWidget->currentRow();
      if (SEEKS_COMM[index - OT_START_INDEX].count() > currentIndexInList)
      {
        description = getDescription(SEEKS_COMM[index - OT_START_INDEX][currentIndexInList]);
      }
    }

    if (!description.isEmpty())
    {
      if (!entryCmbBox->lineEdit()->text().isEmpty()) hitMarker->setPalette(hitMarkerPaletteGreen); // Това поле ще е празно само при първоначално зареждане на сесията и показване на последно показания коментар. 
      mainTextView->setHtml(description);
    }
    else
    {
      hitMarker->setPalette(hitMarkerPaletteNormal);
    }
  }
}

QString Dictionary::getWord(qint64 seek)
{
  char buf[BUF_LEN];
  QString line = "";
  file->seek(seek); // Позициониране в реда, съдържащ търсената дума.
  file->readLine(buf, sizeof(buf)); // Чете реда.
  line = QString("%1").arg(buf);
  line.remove(QString("\r\n"));
  line.remove(QString("\n"));
  line = line.trimmed(); // Изтрива се ненужната информация - премахва  '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
  line = line.remove(0, 2); // Изтива ##.
  return line;
}

QString Dictionary::getDescription(qint64 seek)
{
  char buf[BUF_LEN];
  QString desc = "";
  QString line = "";
  file->seek(seek); // Позициониране в реда, съдържащ търсената дума.
  file->readLine(buf, sizeof(buf)); // Чете реда, за да го прескочи.
  while (!file->atEnd())
  {
    file->readLine(buf, sizeof(buf)); // Чете следващ ред.
    line = QString("%1").arg(buf);
    line.remove(QString("\r\n"));
    line.remove(QString("\n"));
    line = line.trimmed(); // Изтрива се ненужната информация - премахва  '\t', '\n', '\v', '\f', '\r', и ' ' от началото и края на стринга.
    if (line.indexOf("##") == 0) break; // Ако започва нова дума.
    if (desc.isEmpty())
    {
      desc = QString("%1").arg(line);
    }
    else
    {
      desc += QString("<p>%1</p>").arg(line);
    }
  }
  return desc;
}

QString Dictionary::replaceSymbols(QString word)
{
  if (!DP.equalSymbols_Enable) return word;

  for (int i = 0; i < DP.equalSymbols1.count(); i++)
  {
    word.replace(DP.equalSymbols1[i], DP.equalSymbols2[i], Qt::CaseInsensitive);
  }
  return word;
}

void Dictionary::slotBack()
{
  if (currentIndexInBFList > 0)
  {
    currentIndexInBFList--;
    entryCmbBox->setEditText(BFList[currentIndexInBFList]); // Това ще вдигне ивента за промяна на текста.

    if (currentIndexInBFList == 0) backBtn->setEnabled(false);
    forwardBtn->setEnabled(true);
  }
  entryCmbBox->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotForward()
{
  if (currentIndexInBFList < (BFList.count() - 1))
  {
    currentIndexInBFList++;
    entryCmbBox->setEditText(BFList[currentIndexInBFList]); // Това ще вдигне ивента за промяна на текста.

    backBtn->setEnabled(true);
    if (currentIndexInBFList == (BFList.count() - 1)) forwardBtn->setEnabled(false);
  }
  entryCmbBox->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotCatchCopyEvent()
{
  entryCmbBox->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotCatchSelectEvent()
{
  entryCmbBox->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotPrevGroup()
{
  otherWordsListWidget->clear();
  currentIndexInList -= wordsInListBox;
  if (currentIndexInList < 0) currentIndexInList = 0;
  for (int i = 0; i < wordsInListBox; i++)
  {
    if ((currentIndexInList+i) >= SEEKS.size()) break;
    otherWordsListWidget->addItem(getWord(SEEKS[currentIndexInList+i]));
  }
  if (otherWordsListWidget->count() > 0) otherWordsListWidget->setCurrentRow(0, QItemSelectionModel::Deselect);
  otherWordsListWidget->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotNextGroup()
{
  if ((currentIndexInList + wordsInListBox) < SEEKS.size())
  {
    otherWordsListWidget->clear();
    currentIndexInList += wordsInListBox;
    for (int i = 0; i < wordsInListBox; i++)
    {
      if ((currentIndexInList+i) >= SEEKS.size()) break;
      otherWordsListWidget->addItem(getWord(SEEKS[currentIndexInList+i]));
    }
    if (otherWordsListWidget->count() > 0) otherWordsListWidget->setCurrentRow(0, QItemSelectionModel::Deselect);
  }
  otherWordsListWidget->setFocus(); // Това е важно, за да не стои бутонът на фокус, защото няма да може да се затвори разделът на речника от бутона X в TMenu.
}

void Dictionary::slotDictCmbBox_currentIndexChanged(int /*index*/)
{
  isDictionary = allFileNames[dictCmbBox->currentIndex()].contains(".dct", Qt::CaseInsensitive);
  loadDict(allFileNames[dictCmbBox->currentIndex()]);
}

void Dictionary::slotEntryCmbBox_textChanged(QString text)
{
  if (dictCmbBox->currentIndex() < 0) return; // Ако няма избран речник/коментар.
  if (!isDictionary) return;
  if (fromListBox) return; // Когато думата в текстбокса е дошла не от писане, а от списъка с други думи.
  text = text.trimmed();
  if (text.isEmpty())
  {
    hitMarker->setPalette(hitMarkerPaletteNormal);
    return;
  }
  text = replaceSymbols(text);

  int index = getIndexInSortSEEKSList(text);
  if (index == SEEKS.size()) index--; // Ако търсената дума не е намерена и по азбучен ред е след последната дума в речника.

  int iRes = QString::compare(text, replaceSymbols(getWord(SEEKS[index])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
  if (iRes == 0) // Ако има точно съвпадение.
  {
    hitMarker->setPalette(hitMarkerPaletteGreen);
  }
  else // Ако няма съвпадение.
  {
    if (text.size() > 2)
    {
      text = text.remove(text.size()-1, 1); // Изтрива последната буква.
      int index2 = getIndexInSortSEEKSList(text); // Прави ново търсене.
      if (index2 == SEEKS.size()) index2--; // Ако търсената дума не е намерена и по азбучен ред е след последната дума в речника.
      iRes = QString::compare(text, replaceSymbols(getWord(SEEKS[index2])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
      if (iRes == 0) // Ако има точно съвпадение.
      {
        hitMarker->setPalette(hitMarkerPaletteYellow);
        index = index2;
      }
      else // Ако отново няма съвпадение.
      {
        if (text.size() > 2)
        {
          text = text.remove(text.size()-1, 1); // Изтрива последната буква.
          index2 = getIndexInSortSEEKSList(text); // Прави ново търсене.
          if (index2 == SEEKS.size()) index2--; // Ако търсената дума не е намерена и по азбучен ред е след последната дума в речника.
          iRes = QString::compare(text, replaceSymbols(getWord(SEEKS[index2])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
          if (iRes == 0) // Ако има точно съвпадение.
          {
            hitMarker->setPalette(hitMarkerPaletteYellow);
            index = index2;
          }
          else // Ако отново няма съвпадение.
          {
            hitMarker->setPalette(hitMarkerPaletteNormal);
          }
        }
        else
        {
          hitMarker->setPalette(hitMarkerPaletteNormal);
        }
      }
    }
    else
    {
      hitMarker->setPalette(hitMarkerPaletteNormal);
    }
  }

  // Проверява дали предходната дума(и) не е същата и ако да, показва нея (това е възможно поради несъвършенство в алгоритъма за двоично търсене и наличие на еднакви думи):
  for (int i = 0; i < 100; i++) // Прави максимум 100 проверки назад, за да не забавя търсенето (не е нормално в един речник да има толкова еднакви думи. То не е нормално да има дори две еднакви думи...).
  {
    if (index <= 0) break;
    iRes = QString::compare(replaceSymbols(getWord(SEEKS[index])), replaceSymbols(getWord(SEEKS[index-1])), Qt::CaseInsensitive); // -1 ако търсената дума е преди текущата по азбучен ред; 0 - ако съвпадат; +1 ако търсената е след текущата.
    if (iRes == 0) // Ако има точно съвпадение.
    {
      index = index - 1;
    }
    else
    {
      break;
    }
  }

  showWord(index);
}

void Dictionary::slotListWidget_currentItemChanged(QListWidgetItem *item)
{
  if (isDictionary)
  {
    // Този метод може да се направи елементарно - просто, като се запише в полето за търсене текстът, върху който е щракнато в списъка.
    // Така ще се задейства стандартната процедура за показване на търсената дума. Но, ще има проблем, когато в списъка с другите думи
    // има еднакви думи. При наличие на еднакви думи в списъка (речника), това ще доведе до объркване - ще покаже друга дума (първата).
    // Затова не го правя по този прост и естествен начин, а използвам флаг, който да забрани вдигането на ивента при промяна на текста.
    if (item == 0) return;
    fromListBox = true; // Това ще забрани вдигането на ивента за промяна на текста и няма да се изпълни горният слот.
    entryCmbBox->setEditText(otherWordsListWidget->currentItem()->text().toLower()); // Това ще вдигне ивента за промяна на текста, но слотът няма да направи нищо.
    hitMarker->setPalette(hitMarkerPaletteGreen);
    showWord(currentIndexInList + otherWordsListWidget->currentRow());
    fromListBox = false;
    //entryCmbBox->lineEdit()->selectAll();
    //entryCmbBox->setFocus();
  }
  else
  {
    showWord(currentIndex);
    //entryCmbBox->lineEdit()->selectAll();
    //entryCmbBox->setFocus();
  }
}

void Dictionary::slotNewSelectedText(QString text)
{
  // Този метод използва Alt клавиша за селектиране на текст. В Linux, KDE обаче натискането на Alt клавиш + мишката води до преместване на целия прозорец, при което този метод не може да прихване този ивент. 
  // За Linux, KDE - за да се изключи глобалната настройка Alt+Mouse да мести прозореца: В System Settings -- "Window Behavior" -- "Window Actions" таб -- "Inner window, titlebar & frame" -- "Left button" = "Nothing".
  if (dictCmbBox->currentIndex() < 0) return; // Ако няма избран речник/коментар.
  if (!isDictionary) return;
  if (catchSelectEventBtn->isChecked() && !MW->altOnlyKeyPressed) return;
  if (text.isEmpty()) return;

  entryCmbBox->setEditText(text);
  //entryCmbBox->lineEdit()->selectAll();
  //entryCmbBox->setFocus();
}

void Dictionary::slotNewSelectedVerse(quint16 absIndex, QString reference)
{
  // Този метод използва Alt клавиша за селектиране на стих. В Linux, KDE обаче натискането на Alt клавиш + мишката води до преместване на целия прозорец, при което този метод не може да прихване този ивент. 
  // За Linux, KDE - за да се изключи глобалната настройка Alt+Mouse да мести прозореца: В System Settings -- "Window Behavior" -- "Window Actions" таб -- "Inner window, titlebar & frame" -- "Left button" = "Nothing".
  if (dictCmbBox->currentIndex() < 0) return; // Ако няма избран речник/коментар.
  if (isDictionary) return;
  if (catchSelectEventBtn->isChecked() && !MW->altOnlyKeyPressed) return;
  if (/*absIndex < OT_START_INDEX ||*/ absIndex > ONT_END_INDEX) return;

  entryCmbBox->setEditText(reference);
  showWord(absIndex);
  //entryCmbBox->lineEdit()->selectAll();
  //entryCmbBox->setFocus();
}

void Dictionary::slotClipboard_changed(QClipboard::Mode mode)
{
  if (!isDictionary) return;
  if (!catchCopyEventBtn->isChecked()) return;
  if (mode != QClipboard::Clipboard) return;
  if (dictCmbBox->currentIndex() < 0) return; // Ако няма избран речник/коментар.
  QString text = clipboard->text().trimmed();

  // Проверява дали текстът съдържа няколко реда, за да вземе само първия:
  int eol = text.indexOf("\r\n");
  if (eol < 0) eol = text.indexOf("\n");
  if (eol >= 0) text = text.left(eol); // Взима само първия ред.
  text = text.trimmed(); // Премахва разните интервали и други неща от началото и края на текста.
  if (text.isEmpty()) return;

  entryCmbBox->setEditText(text);
  //entryCmbBox->lineEdit()->selectAll();
  //entryCmbBox->setFocus();
}
