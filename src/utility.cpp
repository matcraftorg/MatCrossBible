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

#include "utility.h"

ReorderBibleTextsWindow::ReorderBibleTextsWindow(MainObject *mainObject, bool *needToRestart, QWidget *parent) : QDialog(parent)
{
  this->MO = mainObject;
  this->needToRestart = needToRestart;

  setModal(true);
  resize(200, 200);
  setMinimumSize(10, 10);

  listWidget = new QListWidget(this);
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    allFileBaseNames << MO->bibleTextList[i].fileBaseName;
    allNames << MO->bibleTextList[i].name;
    listWidget->addItem(MO->bibleTextList[i].name);
  }
  listWidget->setCurrentRow(0);
  currentRow = 0;

  btnUp = new QPushButton(this);
  btnUp->setText(QString("<"));
  btnUp->setAutoRepeat(true);
  btnUp->setAutoRepeatDelay(200);
  btnUp->setAutoRepeatInterval(100);
  connect(btnUp, SIGNAL(clicked()), this, SLOT(slotUp()));

  btnDown = new QPushButton(this);
  btnDown->setText(QString(">"));
  btnDown->setAutoRepeat(true);
  btnDown->setAutoRepeatDelay(200);
  btnDown->setAutoRepeatInterval(100);
  connect(btnDown, SIGNAL(clicked()), this, SLOT(slotDown()));

  btnOK = new QPushButton(this);
  btnOK->setText(MO->TS->OK_v1);
  connect(btnOK, SIGNAL(clicked()), this, SLOT(slotOK()));

  btnCancel = new QPushButton(this);
  btnCancel->setText(MO->TS->Cancel_v1);
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(close()));

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->setSpacing(2); // Разстояние между обектите.
  mainLayout->setContentsMargins(3, 3, 3, 3);
  mainLayout->addWidget(listWidget, 0, 0, 1, 4);
  mainLayout->addWidget(btnUp, 1, 0);
  mainLayout->addWidget(btnDown, 1, 1);
  mainLayout->addWidget(btnOK, 1, 2);
  mainLayout->addWidget(btnCancel, 1, 3);
  setLayout(mainLayout);
  listWidget->setFocus();
}

ReorderBibleTextsWindow::~ReorderBibleTextsWindow()
{
  delete listWidget;
  delete btnUp;
  delete btnDown;
  delete btnOK;
  delete btnCancel;
}

void ReorderBibleTextsWindow::slotUp()
{
  currentRow = listWidget->currentRow();
  if (currentRow > 0)
  {
    QString s;

    s = allFileBaseNames[currentRow-1];
    allFileBaseNames[currentRow-1] = allFileBaseNames[currentRow];
    allFileBaseNames[currentRow] = s;

    s = allNames[currentRow-1];
    allNames[currentRow-1] = allNames[currentRow];
    allNames[currentRow] = s;

    listWidget->clear();
    for (quint8 i = 0; i < allNames.size(); i++)
    {
      listWidget->addItem(allNames[i]);
    }
    listWidget->setCurrentRow(currentRow-1);
  }
  //listWidget->setFocus(); // Това обърква AutoRepeat на бутоните.
}

void ReorderBibleTextsWindow::slotDown()
{
  currentRow = listWidget->currentRow();
  if (currentRow < (allFileBaseNames.count()-1))
  {
    QString s;

    s = allFileBaseNames[currentRow+1];
    allFileBaseNames[currentRow+1] = allFileBaseNames[currentRow];
    allFileBaseNames[currentRow] = s;

    s = allNames[currentRow+1];
    allNames[currentRow+1] = allNames[currentRow];
    allNames[currentRow] = s;

    listWidget->clear();
    for (quint8 i = 0; i < allNames.size(); i++)
    {
      listWidget->addItem(allNames[i]);
    }
    listWidget->setCurrentRow(currentRow+1);
  }
  //listWidget->setFocus(); // Това обърква AutoRepeat на бутоните.
}

void ReorderBibleTextsWindow::slotOK()
{
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    if (MO->bibleTextList[i].fileBaseName != allFileBaseNames[i]) // Ако има промяна.
    {
      QSettings settings(MO->iniFile, QSettings::IniFormat, this);
      settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
      
      QString bTextsOrder = "";
      for (quint8 i = 0; i < allFileBaseNames.count(); i++)
      {
        bTextsOrder += allFileBaseNames[i] + "^";
      }
      settings.setValue(QString("bibleTextsOrder"), bTextsOrder);

      *needToRestart = true;
      break;
    }
  }

  close();
}

// =========================================================================================================================================================

ProgressDialog::ProgressDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
  resize(320, 90);
  setModal(true);

  isAutoShow = true;
  isAutoHide = true;

  label = new QLabel("", this);

  progressBar = new QProgressBar(this);
  progressBar->setAlignment(Qt::AlignCenter);
  progressBar->setRange(0, 0);
  progressBar->setValue(0);

  btnCancel = new QPushButton(QString("Cancel"), this);
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(btnCancelClicked()));

  QHBoxLayout *horizontalLayout = new QHBoxLayout();
  horizontalLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
  horizontalLayout->addWidget(btnCancel);

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);
  verticalLayout->setContentsMargins(5, 5, 5, 5);
  verticalLayout->addWidget(label);
  verticalLayout->addWidget(progressBar);
  verticalLayout->addLayout(horizontalLayout);
}

ProgressDialog::ProgressDialog(const QString &labelText, const QString &cancelButtonText, int minimum, int maximum, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
  resize(320, 90);
  setModal(true);

  isAutoShow = true;
  isAutoHide = true;

  label = new QLabel(labelText, this);

  progressBar = new QProgressBar(this);
  progressBar->setAlignment(Qt::AlignCenter);
  progressBar->setRange(minimum, maximum);
  progressBar->setValue(0);

  btnCancel = new QPushButton(cancelButtonText, this);
  connect(btnCancel, SIGNAL(clicked()), this, SLOT(btnCancelClicked()));

  QHBoxLayout *horizontalLayout = new QHBoxLayout();
  horizontalLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
  horizontalLayout->addWidget(btnCancel);

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);
  verticalLayout->setContentsMargins(5, 5, 5, 5);
  verticalLayout->addWidget(label);
  verticalLayout->addWidget(progressBar);
  verticalLayout->addLayout(horizontalLayout);
}

ProgressDialog::~ProgressDialog()
{
}

QString ProgressDialog::labelText()
{
  return label->text();
}

void ProgressDialog::setLabelText(const QString &text)
{
  label->setText(text);
}

QString ProgressDialog::cancelButtonText()
{
  return btnCancel->text();
}

void ProgressDialog::setCancelButtonText(const QString &cancelButtonText)
{
  btnCancel->setText(cancelButtonText);
}

int ProgressDialog::minimum()
{
  return progressBar->minimum();
}

int ProgressDialog::maximum()
{
  return progressBar->maximum();
}

int ProgressDialog::value()
{
  return progressBar->value();
}

bool ProgressDialog::autoShow()
{
  return isAutoShow;
}

void ProgressDialog::setAutoShow(bool autoShow)
{
  isAutoShow = autoShow;
}

bool ProgressDialog::autoHide()
{
  return isAutoHide;
}

void ProgressDialog::setAutoHide(bool autoHide)
{
  isAutoHide = autoHide;
}

void ProgressDialog::btnCancelClicked()
{
  emit canceled();
  hide();
}

void ProgressDialog::reset()
{
  progressBar->setValue(0);
  progressBar->setRange(0, 0);
}

void ProgressDialog::setMinimum(int minimum)
{
  progressBar->setMinimum(minimum);
}

void ProgressDialog::setMaximum(int maximum)
{
  progressBar->setMaximum(maximum);
}

void ProgressDialog::setRange(int minimum, int maximum)
{
  progressBar->setRange(minimum, maximum);
}

void ProgressDialog::setValue(int progress)
{
  if (isAutoShow && maximum() > minimum() && progress < maximum()) show();
  if (isAutoHide && progress >= maximum()) hide();

  progressBar->setValue(progress);
}

// =========================================================================================================================================================

BibleTextConvertor::BibleTextConvertor(MainObject *mainObject, QWidget *parent) : QWidget(parent)
{
  this->MO = mainObject;

  setWindowTitle(QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()));
  resize(620, 160);

  // CrossBgBible:
  QGroupBox *groupBoxCrossBgBible = new QGroupBox(MO->TS->ConvertCrossBgBibleFile_v1, this);
  groupBoxCrossBgBible->setMinimumWidth(200);

  lineEditCrossBgBibleFile = new QLineEdit(groupBoxCrossBgBible);
  lineEditCrossBgBibleFile->setReadOnly(true);
  lineEditCrossBgBibleFile->setMinimumWidth(50);

  btnChoiceCrossBgBibleFile = new QPushButton("...", groupBoxCrossBgBible);
  btnChoiceCrossBgBibleFile->setToolTip(MO->TS->ChooseFile_v1);
  btnChoiceCrossBgBibleFile->setMinimumWidth(30);
  btnChoiceCrossBgBibleFile->setMaximumWidth(30);
  connect(btnChoiceCrossBgBibleFile, SIGNAL(clicked()), this, SLOT(btnChoiceCrossBgBibleFileClicked()));

  btnConvertCrossBgBibleFile = new QPushButton(MO->TS->Convert_v1, groupBoxCrossBgBible);
  connect(btnConvertCrossBgBibleFile, SIGNAL(clicked()), this, SLOT(btnConvertCrossBgBibleFileClicked()));

  QHBoxLayout *hLayoutCrossBgBible = new QHBoxLayout(groupBoxCrossBgBible);
  hLayoutCrossBgBible->addWidget(lineEditCrossBgBibleFile);
  hLayoutCrossBgBible->addWidget(btnChoiceCrossBgBibleFile);
  hLayoutCrossBgBible->addWidget(btnConvertCrossBgBibleFile);

  // TheWord:
  QGroupBox *groupBoxTheWord = new QGroupBox(MO->TS->ConvertTheWordFile_v1, this);
  groupBoxTheWord->setMinimumWidth(200);

  lineEditTheWordFile = new QLineEdit(groupBoxTheWord);
  lineEditTheWordFile->setReadOnly(true);
  lineEditTheWordFile->setMinimumWidth(50);

  btnChoiceTheWordFile = new QPushButton("...", groupBoxTheWord);
  btnChoiceTheWordFile->setToolTip(MO->TS->ChooseFile_v1);
  btnChoiceTheWordFile->setMinimumWidth(30);
  btnChoiceTheWordFile->setMaximumWidth(30);
  connect(btnChoiceTheWordFile, SIGNAL(clicked()), this, SLOT(btnChoiceTheWordFileClicked()));

  btnConvertTheWordFile = new QPushButton(MO->TS->Convert_v1, groupBoxTheWord);
  connect(btnConvertTheWordFile, SIGNAL(clicked()), this, SLOT(btnConvertTheWordFileClicked()));
  
  chBoxAddNumbersToVerses = new QCheckBox(MO->TS->AddNumbersToVerses_v1);
  chBoxAddNumbersToVerses->setChecked(true);
  chBoxAddNumbersToVerses->setMinimumWidth(50);

  QGridLayout *gLayoutTheWord = new QGridLayout(groupBoxTheWord);
  gLayoutTheWord->addWidget(new QLabel(MO->TS->ConvertFileToUTF8First_v1), 0, 0, 1, 3);
  gLayoutTheWord->addWidget(lineEditTheWordFile, 1, 0);
  gLayoutTheWord->addWidget(btnChoiceTheWordFile, 1, 1);
  gLayoutTheWord->addWidget(btnConvertTheWordFile, 1, 2);
  gLayoutTheWord->addWidget(chBoxAddNumbersToVerses, 2, 0, 1, 3);

  
  QVBoxLayout *verticalLayout = new QVBoxLayout(this);
  verticalLayout->setSpacing(20);
  verticalLayout->addWidget(groupBoxCrossBgBible);
  verticalLayout->addWidget(groupBoxTheWord);
  verticalLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

BibleTextConvertor::~BibleTextConvertor()
{
}

void BibleTextConvertor::btnChoiceCrossBgBibleFileClicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, QString("CrossBgBible File"), "", QString("CrossBgBible Files (translation.*);;All Files (*.*)")); // <-- Не знам дали е добра идея да се слага такъв филтър (translation.*).
  if (!fileName.isEmpty()) lineEditCrossBgBibleFile->setText(fileName);
}

void BibleTextConvertor::btnConvertCrossBgBibleFileClicked()
{
  // Файлът, който ще се конвертира:
  QString targetFileName = lineEditCrossBgBibleFile->text();
  if (targetFileName.isEmpty() || !QFile::exists(targetFileName)) return;

  // Определя името на новия файл:
  QString fileType = "";
  QString newFileName = targetFileName;

  if (!QFile::exists(newFileName + ".hbt"))
  {
    newFileName += ".hbt";
  }
  else
  {
    for (int i = 1; i < 1000000; i++) // Дали някой ще направи 1 милион опита? :)
    {
      if (!QFile::exists(newFileName + QString(" (%1).hbt").arg(i)))
      {
        newFileName += QString(" (%1).hbt").arg(i);
        break;
      }
    }
  }

  char buf[65536]; // Буферът трябва да е голям, защото може да има много дълги редове.
  QString line = "";
  QString sbuf = "";
  QStringList allVerses;
  QStringList allVerses2;
  
  QString numerationCode = "";
  QString name = "";
  QString shortDescription = "";
  QString description = "";

  // Прочита файла, който ще се конвертира:
  QFile rfile(targetFileName);
  if (rfile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    // Структура на файла:
    //
    // STRUCTURE_VERSION=1
    // NUMERATION_CODE=1
    // TRANSLATION_NAME=Протестантски (1940)
    // TRANSLATION_SHORT_DESCRIPTION=Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>
    // TRANSLATION_DESCRIPTION=Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>.<br>Преводът е написан на съвременен български език.<br>Съдържа 66 книги, 1189 глави, 31101 стиха, 679466 думи и 3027900 символа.<br>Текстът съдържа следните форматиращи скоби:<br>&nbsp; <b>( )</b> - стандартна граматическа функция ("в скоби");<br>&nbsp; <b>[ ]</b> - текстът не съществува във всички познати ръкописи;<br>&nbsp; <b>{ }</b> - обяснение на предишната дума или фраза (т.нар. бележка под линия).<br>В <i>курсив</i> са думите, които липсват в оригиналния текст, а са добавени поради логична необходимост.
    // 
    // 1. В начало Бог създаде небето и земята.
    // ...

    // Чете първи служебен ред:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    if (!line.contains(QString("STRUCTURE_VERSION=1"), Qt::CaseInsensitive)) // Ако файлът има структура различна от очакваната.
    {
      QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
      rfile.close();
      return;
    }

    // Чете втори служебен ред:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    line.remove(QString("NUMERATION_CODE="));
    numerationCode = line.trimmed();

    // Чете трети служебен ред:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    line.remove(QString("TRANSLATION_NAME="));
    name = line.trimmed();

    // Чете четвърти служебен ред:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    line.remove(QString("TRANSLATION_SHORT_DESCRIPTION="));
    shortDescription = line.trimmed();

    // Чете пети служебен ред:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    line.remove(QString("TRANSLATION_DESCRIPTION="));
    description = line.trimmed();

    // Чете празния ред преди текста:
    rfile.readLine(buf, sizeof(buf));
    line = QString("%1").arg(buf).trimmed();
    if (!line.isEmpty()) // Ако не е празен ред.
    {
      QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
      rfile.close();
      return;
    }

    // Чете текста:
    while (rfile.readLine(buf, sizeof(buf)) != -1)
    {
      line = QString("%1").arg(buf).trimmed();
      allVerses << line;
      if (allVerses.count() == 37056) break; // Това е за да не прочита евентуални празни редове след текста.
    }
    rfile.close();
  }

  // Повторна проверка за правилно прочитане на файла:
  if (allVerses.count() != 37056)
  {
    QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
    return;
  }

  // Следващите книги трябва да се преместят в края на СЗ (2 Ездра, Товита, Иудит, Пр.Сол., Ис.Сир., Пос.Ер., Вар., 1Мак., 2Мак., 3Мак., 3Езд.)
  // CBB
  // 12712   2 Ездра
  //         Товита
  //         Иудит
  // 13738   ----Естир
  // 
  // 
  // //17450   Псалми 151
  // //17457   ----Притчи
  // 
  // 
  // 18717   Пр.Сол.
  //         Ис.Сир.
  // 20680   ----Исая
  // 
  // 		
  // 23490   Пос.Ер.
  //         Вар.
  // 23703   ----Езекиил
  // 
  // 
  // //25069   Даниил 3:24-90
  // //25136   ----
  // //
  // //
  // //25403   Даниил 13
  // //        Даниил 14
  // //25509   ----Осия
  // 
  // 		
  // 26561   1Мак.
  //         2Мак.
  //         3Мак.
  //         3Езд.
  // 29096   ----Матей

  // Изнася вророканоничните книги след СЗ:
  for (int i = 1; i < 29096; i++) // Всичко до края на СЗ. Записва само каноничните книги.
  {
    if (i >= 12712 && i < 13738) continue;
    if (i >= 18717 && i < 20680) continue;
    if (i >= 23490 && i < 23703) continue;
    if (i >= 26561 && i < 29096) continue;
    allVerses2 << allVerses[i-1];
  }
  for (int i = 1; i < 29096; i++) // Всичко до края на СЗ. Записва само апокрифните книги (добавя ги след каноничните).
  {
    if ((i >= 12712 && i < 13738) ||
        (i >= 18717 && i < 20680) ||
        (i >= 23490 && i < 23703) ||
        (i >= 26561 && i < 29096)) allVerses2 << allVerses[i-1];
  }

  // Размества посланията от източния в западния стандарт:
  for (int i = 29096; i < 33882; i++) // Всичко от началото на НЗ до края на ДА.
  {
    allVerses2 << allVerses[i-1];
  }
  for (int i = 34314; i < 36653; i++) // Всичко от Римляни до края на Евреи.
  {
    allVerses2 << allVerses[i-1];
  }
  for (int i = 33882; i < 34314; i++) // Всичко от Яков до края на Юда.
  {
    allVerses2 << allVerses[i-1];
  }
  for (int i = 36653; i < (allVerses.count() + 1); i++) // Откровение.
  {
    allVerses2 << allVerses[i-1];
  }

  // След всички горни действия, би трябвало тук да имаме allVerses2 с count = 37056.
  if (allVerses2.count() != 37056) return; // Тази проверка е излишна, но да има...

  // Сега трябва да се добавят следните празни редове за да се премине към HBT формат:
  // СЗ
  for (int i = 0; i < 15; i++)
    allVerses2.insert(12026-1, "");
  for (int i = 0; i < 17; i++)
    allVerses2.insert(12727-1, "");
  for (int i = 0; i < 7; i++)
    allVerses2.insert(12802-1, "");
  for (int i = 0; i < 49; i++)
    allVerses2.insert(12828-1, "");
  for (int i = 0; i < 24; i++)
    allVerses2.insert(12927-1, "");
  for (int i = 0; i < 10; i++)
    allVerses2.insert(12992-1, "");
  for (int i = 0; i < 9; i++)
    allVerses2.insert(16553-1, "");
  allVerses2.insert(22065-1, "");
  allVerses2.insert(22439-1, "");
  // Втор.
  for (int i = 0; i < 3; i++)
    allVerses2.insert(23738-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(23882-1, "");
  allVerses2.insert(23942-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(23965-1, "");
  for (int i = 0; i < 9; i++)
    allVerses2.insert(23982-1, "");
  for (int i = 0; i < 8; i++)
    allVerses2.insert(24008-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(24037-1, "");
  for (int i = 0; i < 6; i++)
    allVerses2.insert(24061-1, "");
  for (int i = 0; i < 4; i++)
    allVerses2.insert(24085-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(24106-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(24130-1, "");
  for (int i = 0; i < 6; i++)
    allVerses2.insert(24139-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(24176-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(24219-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(24239-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(24295-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(24315-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(24341-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(24449-1, "");
  for (int i = 0; i < 11; i++)
    allVerses2.insert(24540-1, "");
  allVerses2.insert(24584-1, "");
  for (int i = 0; i < 6; i++)
    allVerses2.insert(24610-1, "");
  allVerses2.insert(24656-1, "");
  allVerses2.insert(25011-1, "");
  allVerses2.insert(25058-1, "");
  for (int i = 0; i < 14; i++)
    allVerses2.insert(25089-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(25121-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(25157-1, "");
  allVerses2.insert(25195-1, "");
  allVerses2.insert(25290-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25336-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25406-1, "");
  allVerses2.insert(25426-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25506-1, "");
  allVerses2.insert(25570-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25632-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25665-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25729-1, "");
  allVerses2.insert(25768-1, "");
  for (int i = 0; i < 10; i++)
    allVerses2.insert(25806-1, "");
  for (int i = 0; i < 7; i++)
    allVerses2.insert(25845-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(25879-1, "");
  for (int i = 0; i < 4; i++)
    allVerses2.insert(25975-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(26043-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(26073-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(26135-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(26163-1, "");
  for (int i = 0; i < 2; i++)
    allVerses2.insert(26195-1, "");
  allVerses2.insert(26435-1, "");
  allVerses2.insert(26594-1, "");
  for (int i = 0; i < 13; i++)
    allVerses2.insert(26664-1, "");
  allVerses2.insert(26749-1, "");
  for (int i = 0; i < 3; i++)
    allVerses2.insert(26955-1, "");
  allVerses2.insert(27651-1, "");
  allVerses2.insert(27705-1, "");
  allVerses2.insert(28265-1, "");
  allVerses2.insert(28377-1, "");
  for (int i = 0; i < 4; i++)
    allVerses2.insert(28403-1, "");
  for (int i = 0; i < 9; i++)
    allVerses2.insert(28431-1, "");
  for (int i = 0; i < 8; i++)
    allVerses2.insert(28462-1, "");
  for (int i = 0; i < 5; i++)
    allVerses2.insert(28486-1, "");
  for (int i = 0; i < 15; i++)
    allVerses2.insert(28527-1, "");
  for (int i = 0; i < 4; i++)
    allVerses2.insert(28579-1, "");
  for (int i = 0; i < 485; i++)
    allVerses2.insert(28603-1, "");
  for (int i = 0; i < 70; i++)
    allVerses2.insert(29449-1, "");

  // След всички горни действия, би трябвало тук да имаме allVerses2 с count = 37993 (MAX_VERSES), т.е HBT формат.
  if (allVerses2.count() != MAX_VERSES) return; // Тази проверка е излишна, но да има...

  // Добавяне на служебната информация:
  //
  // STRUCTURE_VERSION=3
  // NAME=Протестантски (1940)
  // SHORT_DESCRIPTION=Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>
  // NUMERATION_CODE=1
  // NATIVE_VERSE_NUMERATION=Yes
  // FONT_FAMILY=
  // LAYOUT_DIRECTION=LeftToRight
  // LANGUAGE=
  // LAST_MODIFY_DATE=
  // DESCRIPTION:
  // Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>.<br>
  //
  allVerses2 << QString(""); // Празен ред.
  allVerses2 << QString("STRUCTURE_VERSION=3");
  allVerses2 << QString("NAME=%1").arg( name.isEmpty() ? QFileInfo(newFileName).baseName() : name );
  allVerses2 << QString("SHORT_DESCRIPTION=%1").arg(shortDescription);
  allVerses2 << QString("NUMERATION_CODE=%1").arg(numerationCode);
  allVerses2 << QString("NATIVE_VERSE_NUMERATION=Yes");
  allVerses2 << QString("FONT_FAMILY=");
  allVerses2 << QString("LAYOUT_DIRECTION=LeftToRight");
  allVerses2 << QString("LANGUAGE=");
  allVerses2 << QString("LAST_MODIFY_DATE=");
  allVerses2 << QString("DESCRIPTION:");
  allVerses2 << description;

  // Запис на файла:
  QFile wfile(newFileName);
  if (wfile.open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    for (int v = 0; v < allVerses2.count(); v++)
    {
      wfile.write(QString("%1\n").arg(allVerses2[v]).toUtf8());
    }
    wfile.close();
  }

  QMessageBox::information(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString("%1\n%2").arg(MO->TS->ConversionSuccessful_v1).arg(newFileName));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Сравняване на главите:
  //QString fileName1 = QString("C:/Bulgarian_Sinod1992.hbt");
  //if (!QFile::exists(fileName1)) return;
  //QFile rfile1(fileName1);
  //rfile1.open(QIODevice::ReadOnly | QIODevice::Text);
  //
  //if (!QFile::exists(newFileName)) return;
  //QFile rfile2(newFileName);
  //rfile2.open(QIODevice::ReadOnly | QIODevice::Text);
  //
  //QFile wfile2(newFileName + "_");
  //if (!wfile2.open(QIODevice::WriteOnly | QIODevice::Text)) return; // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  //
  //char buf1[6144];
  //char buf2[6144];
  //QString sbuf1 = "";
  //QString sbuf2 = "";
  //qint32 diff = 0;
  //qint32 row = 0;
  //while (rfile1.readLine(buf1, sizeof(buf1)) != -1 && rfile2.readLine(buf2, sizeof(buf2)) != -1)
  //{
  //  row++;
  //  sbuf1 = QString("%1").arg(buf1).trimmed();      //sbuf1.remove(QString("</JW>"));  sbuf1.remove(QString("<JW>"));
  //  sbuf2 = QString("%1").arg(buf2).trimmed();      //sbuf2.remove(QString("</JW>"));  sbuf2.remove(QString("<JW>"));
  //  if (sbuf1.left(20) != sbuf2.left(20))
  //  {
  //    diff++;
  //    wfile2.write(QString("%1\t\t%2\n"  ).arg(row).arg(sbuf1).toUtf8());
  //    wfile2.write(QString("%1\t\t%2\n\n").arg(row).arg(sbuf2).toUtf8());
  //  }
  //}
  //rfile2.close();
  //rfile1.close();
  //wfile2.close();
  //QMessageBox::information(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString("Diff: %1").arg(diff));
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void BibleTextConvertor::btnChoiceTheWordFileClicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, QString("TheWord File"), "", QString("TheWord Files (*.ont *.ot *.nt);;All Files (*.*)"));
  if (!fileName.isEmpty()) lineEditTheWordFile->setText(fileName);
}

void BibleTextConvertor::btnConvertTheWordFileClicked()
{
  // Файлът, който ще се конвертира:
  QString targetFileName = lineEditTheWordFile->text();
  if (targetFileName.isEmpty() || !QFile::exists(targetFileName)) return;

  // Определя името на новия файл:
  QString fileType = "";
  QString newFileName = targetFileName;
  if (newFileName.endsWith(".ont", Qt::CaseInsensitive))
  {
    fileType = "ont";
    newFileName = newFileName.left(newFileName.length()-4);
  }
  else if (newFileName.endsWith(".ot", Qt::CaseInsensitive))
  {
    fileType = "ot";
    newFileName = newFileName.left(newFileName.length()-3);
  }
  else if (newFileName.endsWith(".nt", Qt::CaseInsensitive))
  {
    fileType = "nt";
    newFileName = newFileName.left(newFileName.length()-3);
  }

  if (!QFile::exists(newFileName + ".hbt"))
  {
    newFileName += ".hbt";
  }
  else
  {
    for (int i = 1; i < 1000000; i++) // Дали някой ще направи 1 милион опита? :)
    {
      if (!QFile::exists(newFileName + QString(" (%1).hbt").arg(i)))
      {
        newFileName += QString(" (%1).hbt").arg(i);
        break;
      }
    }
  }

  char buf[65536]; // Буферът трябва да е голям, защото може да има много дълги редове.
  QString line = "";
  QString info = "";
  QString sbuf = "";
  QStringList allVerses;
  
  QString language = "";
  QString lastModifyDate = "";
  QString fontFamily = "";
  QString name = "";
  QString shortDescription = "";
  QStringList description;
  QStringList additionalDescription;
  bool readInfo = false; // Флаг, указващ, че е започнало четенето на информацията след текста.
  bool readDescription = false; // Флаг, указващ, че е започнало четенето на Description-а (т.е. последните редове от файла).

  // Прочита файла, който ще се конвертира:
  QFile rfile(targetFileName);
  if (rfile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    while (rfile.readLine(buf, sizeof(buf)) != -1)
    {
      line = QString("%1").arg(buf).trimmed();
      info = line; // info ще запомни необработения ред, защото инфото не е добре да минава през долните обработки.
      info.replace(QString("<br>"), QString("<br />"));
      info.replace(QString("<br/>"), QString("<br />"));

      // Заграждащи тагове:
      // <TS1><Ts1>   // Заглавие на абзац/раздел. Да се заменят с интервал{<b></b>}интервал.
      line.replace(QString("<TS1>"), QString(" {<b>"));
      line.replace(QString("<Ts1>"), QString("</b>} "));
      // <TS2><Ts2>   // Същото като горното, но да не е болднато - интервал{}интервал.
      // <TS2><Ts>    // Като горното.
      // <TS3><Ts>    // Като горното.
      // <TS><Ts>     // Като горното.
      line.replace(QString("<TS2>"), QString(" {"));
      line.replace(QString("<TS3>"), QString(" {"));
      line.replace(QString("<TS>"), QString(" {"));
      line.replace(QString("<Ts2>"), QString("} "));
      line.replace(QString("<Ts>"),  QString("} "));
      // <z1><z2>     // Заграждат текста, за който се отнася обяснителната записка след него. Да се изтрият или да се заменят с <u></u>.
      line.replace(QString("<z1>"), QString("<u>"));
      line.replace(QString("<z2>"), QString("</u>"));
      // <FR><Fr>     // Думите на Исус Христос Да се заменят с <JW></JW>
      line.replace(QString("<FR>"), QString("<JW>"));
      line.replace(QString("<Fr>"), QString("</JW>"));
      // <FI><Fi>     // Италик. Да се заменят с {<i></i>}.
      line.replace(QString("<FI>"), QString("<i>"));
      line.replace(QString("<Fi>"), QString("</i>"));
      // <FO><Fo>     // Обяснителна записка - заглавия на Псалмите и на други места. Да се заменят с интервал{}интервал.
      line.replace(QString("<FO>"), QString(" {"));
      line.replace(QString("<Fo>"), QString("} "));
      // <RF><Rf>     // Обяснителна записка. Да се заменят с интервал{}интервал.
      line.replace(QString("<RF>"), QString(" {"));
      line.replace(QString("<Rf>"), QString("} "));
      // <RF q=*><Rf> // Служебна информация. Например, че този стих го няма в този превод. Да се заменят с интервал{}интервал.
      // <RF q=a><Rf> // Обяснителна записка. Вместо 'a' може да е друга буква. Да се заменят с интервал{}интервал.
      line.replace(QRegExp("<RF q=.>"), QString(" {")); // . - Matches any single character.
      line.replace(QString("<Rf>"), QString("} "));
      // <HEB><Heb>   // Заграждат дума на еврейски. Да се заменят с {}.
      line.replace(QString("<HEB>"), QString("{"));
      line.replace(QString("<Heb>"), QString("}"));
      // <HE><He>     // Заграждат дума на еврейски. Да се заменят с {}.
      line.replace(QString("<HE>"), QString("{"));
      line.replace(QString("<He>"), QString("}"));
      // <font color="00000a"></font> // Да се оставят както са и потребителят да си ги оправя.
      // <font size=+1></font> // Да се оставят както са и потребителят да си ги оправя.
      // <br>         // Да се заменят всички <br />, <br/> и <br> с интервал.
      line.replace(QString("<br>"), QString(" "));
      line.replace(QString("<br/>"), QString(" "));
      line.replace(QString("<br />"), QString(" "));
      // 
      // Единични тагове:
      // <CM>  // Предполагаем разделител между абзаци. (еквивалентно на <br /><br />). Да се замени с интервал.
      // <CI>  // Предполагаем нов ред (еквивалентно на <br />). Да се замени с интервал.
      // <CL>  // Предполагаем нов ред (еквивалентно на <br />). Да се замени с интервал.
      // <CLX> //  Предполагаем нов ред (еквивалентно на <br />). Да се замени с интервал. 
      line.replace(QString("<CM>"), QString(" "));
      line.replace(QString("<CI>"), QString(" "));
      line.replace(QString("<CL>"), QString(" "));
      line.replace(QString("<CLX>"), QString(" "));
      // 
      // <PF0> // Най-вероятно изписват текста навътре или е някакъв вид параграф. Тези PF тагове са винаги предшествани от <CM> или <CI>, т.е. винаги започват на нов ред. Да се изтриват.
      // <PF1> //
      // <PF2> //
      // <PF3> //
      line.replace(QString("<PF0>"), QString(""));
      line.replace(QString("<PF1>"), QString(""));
      line.replace(QString("<PF2>"), QString(""));
      line.replace(QString("<PF3>"), QString(""));
      // 
      // <PI1> // Свързани са с цитати. Винаги са предшествани от PF таг и съответно от <CM> или <CI> таг. Да се изтриват.
      // <PI2> //
      // <PI3> //
      line.replace(QString("<PI1>"), QString(""));
      line.replace(QString("<PI2>"), QString(""));
      line.replace(QString("<PI3>"), QString(""));
      // 
      // <RX 23.7.14>     // Препратки. Да се оставят.
      // <RX 19.91.11-12> //
      // <AX Viis.2:23>   //
      // <AX Siir.39:16>  //
      // 
      // Да се изтриват всички съседни интервали, получени от премахването на горните тагове.
      // Да се замени интервал+точка с точка.
      // Да се замени интервал+запетая с запетая.
      // Да се замени интервал+точка и запетая с точка и запетая.
      // Да се замени интервал+двоеточие с двоеточие.
      // Да се замени интервал+въпросителен знак с въпросителен знак.
      // Да се замени интервал+удивителен знак с удивителен знак.
      line.replace(QString("    "), QString(" ")); // С тези три реда се изтриват дължини до 10 последователни интервала.
      line.replace(QString("   "), QString(" "));  //
      line.replace(QString("  "), QString(" "));   //
      //line.replace(QString(" ."), QString(".")); //  Тези по-добре да не се правят, защото на някои места тези знаци не се използват по предназначение и се изтриват интервали, които трябва да ги има.
      //line.replace(QString(" ,"), QString(",")); //
      //line.replace(QString(" ;"), QString(";")); //
      //line.replace(QString(" :"), QString(":")); //
      //line.replace(QString(" ?"), QString("?")); //
      //line.replace(QString(" !"), QString("!")); //
      line = line.trimmed();
    
      if (fileType == "ot")
      {
        if (allVerses.count() < 23145)
        {
          allVerses << line;
        }
        else
        {
          readInfo = true;
        }
      }
      else if (fileType == "nt")
      {
        if (allVerses.count() < 7957)
        {
          allVerses << line;
        }
        else
        {
          readInfo = true;
        }
      }
      else //if (fileType == "ont") // Ако е ont или какъв да е файл.
      {
        if (allVerses.count() < 31102)
        {
          allVerses << line;
        }
        else
        {
          readInfo = true;
        }
      }

      if (readInfo)
      {
        if (!readDescription)
        {
          if (info.startsWith("lang=", Qt::CaseInsensitive)) language = info.remove(0, 5).trimmed();
          else if (info.startsWith("version.date=", Qt::CaseInsensitive)) lastModifyDate = info.remove(0, 13).trimmed();
          else if (info.startsWith("font=", Qt::CaseInsensitive)) fontFamily = info.remove(0, 5).trimmed();
          else if (info.startsWith("short.title=", Qt::CaseInsensitive)) name = info.remove(0, 12).trimmed();
          else if (info.startsWith("description=", Qt::CaseInsensitive)) shortDescription = info.remove(0, 12).trimmed();
          else if (info.startsWith("author=", Qt::CaseInsensitive)) additionalDescription << ("Author: " + info.remove(0, 7).trimmed() + "<br />");
          else if (info.startsWith("creator=", Qt::CaseInsensitive)) additionalDescription << ("Creator: " + info.remove(0, 8).trimmed() + "<br />");
          else if (info.startsWith("source=", Qt::CaseInsensitive)) additionalDescription << ("Source: " + info.remove(0, 7).trimmed() + "<br />");
          else if (info.startsWith("about=", Qt::CaseInsensitive))
          {
            info = info.remove(0, 6).trimmed();
            if (info.endsWith("\\")) info = info.left(info.length()-1).trimmed(); // Ако редът завършва с обратна наклонена черта я изтрива. А пък trimmed() ще изтрие евентуалния интервал в края на реда и трябва да се постави нов.
            if (!info.isEmpty()) description << info + " "; // Добавя интервал, защото след изтриване на наклонената черта + trimmed(), последният интервал (ако е имало такъв) е бил изтрит и ако не се постави нов, първата дума от новия ред ще се залепи за последната от този.
            readDescription = true; // Указва, че е започнало четенето на описанието и всички следващи редове до края на файла се отнасят за него.
          }
        }
        else
        {
          if (info.endsWith("\\")) info = info.left(info.length()-1).trimmed(); // Ако редът завършва с обратна наклонена черта я изтрива. А пък trimmed() ще изтрие евентуалния интервал в края на реда и трябва да се постави нов.
          if (!info.isEmpty()) description << info + " "; // Добавя интервал защото след изтриване на наклонената черта + trimmed(), последният интервал (ако е имало такъв) е бил изтрит и ако не се постави нов, първата дума от новия ред ще се залепи за последната от този.
        }
      }
    }
    rfile.close();
  }

  // Повторна проверка за правилно прочитане на файла и правилен формат:
  if (fileType == "ot")
  {
    if (allVerses.count() != 23145)
    {
      QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
      return;
    }
  }
  else if (fileType == "nt")
  {
    if (allVerses.count() != 7957)
    {
      QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
      return;
    }
  }
  else //if (fileType == "ont") // Ако е ont или какъв да е файл.
  {
    if (allVerses.count() != 31102) // Ако е ont или какъв да е файл.
    {
      QMessageBox::critical(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString(MO->TS->UnknownFileFormat_v1));
      return;
    }
  }

  // Добавяне на празни редове, ако файлът е от тип ot или nt:
  if (fileType == "ot") // Ако файлът съдържа само СЗ.
  {
    // Добавя празни редове за НЗ:
    for (int i = 0; i < 7957; i++)
    {
      allVerses << "";
    }
  }
  if (fileType == "nt") // Ако файлът съдържа само НЗ.
  {
    // Инсъртва празни редове за СЗ:
    for (int i = 0; i < 23145; i++)
    {
      allVerses.insert(0, "");
    }
  }

  // След всички горни действия, би трябвало тук да имаме allVerses с count = 31102, т.е ONT формат.
  if (allVerses.count() != 31102) return; // Тази проверка е излишна, но да има...

  // ONT     HBT
  // 1       1     -- СЗ                    (В тази част трябва да се вмъкнат 346 празни реда: 4077, 4651, 5953, 3:6514-6516, 7780, 7849, 15:12026-12040, 17:12727-12743, 7:12802-12808, 49:12828-12876, 24:12927-12950, 11:12991-13001, 5:13997-14001, 8:14026-14033, 16:16546-16561, 2:16679-16680, 16924, 17073, 17563, 17794, 68:21998-22065, 3:22073-22075, 107:22333-22439, 22628, 22895)
  //
  // -----   23492 -- Втор.                 (В тази част трябва да се вмъкнат 6541 празни реда: 23492-30032)
  //
  // 23146   30033 -- НЗ
  // 27932   34819 -- Римляни 1 - Евреи 13  (В тази част трябва да се вмъкнат 3 празни реда: 35192, 35193 и 35194)
  // 30268   37158 -- Яков 1 - Юда 1        (В тази част трябва да се вмъкне 1 празен ред: 37564)
  // 30699   37590 -- Откровение 1
  // 31103   37994 -- Description

  // Сега трябва да се добавят гореописаните празни редове за да се премине към HBT формат:
  allVerses.insert(4077-1, ""); // 4077
  allVerses.insert(4651-1, ""); // 4651
  allVerses.insert(5953-1, ""); // 5953
  allVerses.insert(6514-1, ""); // 6514
  allVerses.insert(6515-1, ""); // 6515
  allVerses.insert(6516-1, ""); // 6516
  allVerses.insert(7780-1, ""); // 7780
  allVerses.insert(7849-1, ""); // 7849
  for (int i = 0; i < 15; i++)
    allVerses.insert(12026-1, ""); // 15:12026-12040
  for (int i = 0; i < 17; i++)
    allVerses.insert(12727-1, ""); // 17:12727-12743
  for (int i = 0; i < 7; i++)
    allVerses.insert(12802-1, ""); // 7:12802-12808
  for (int i = 0; i < 49; i++)
    allVerses.insert(12828-1, ""); // 49:12828-12876
  for (int i = 0; i < 24; i++)
    allVerses.insert(12927-1, ""); // 24:12927-12950
  for (int i = 0; i < 11; i++)
    allVerses.insert(12991-1, ""); // 11:12991-13001
  for (int i = 0; i < 5; i++)
    allVerses.insert(13997-1, ""); // 5:13997-14001
  for (int i = 0; i < 8; i++)
    allVerses.insert(14026-1, ""); // 8:14026-14033
  for (int i = 0; i < 16; i++)
    allVerses.insert(16546-1, ""); // 16:16546-16561
  allVerses.insert(16679-1, ""); // 16679
  allVerses.insert(16680-1, ""); // 16680
  allVerses.insert(16924-1, ""); // 16924
  allVerses.insert(17073-1, ""); // 17073
  allVerses.insert(17563-1, ""); // 17563
  allVerses.insert(17794-1, ""); // 17794
  for (int i = 0; i < 68; i++)
    allVerses.insert(21998-1, ""); // 68:21998-22065
  allVerses.insert(22073-1, ""); // 22073
  allVerses.insert(22074-1, ""); // 22074
  allVerses.insert(22075-1, ""); // 22075
  for (int i = 0; i < 107; i++)
    allVerses.insert(22333-1, ""); // 107:22333-22439
  allVerses.insert(22628-1, ""); // 22628
  allVerses.insert(22895-1, ""); // 22895)

  for (int i = 0; i < 6541; i++)
    allVerses.insert(23492-1, ""); // 6541:23492-30032

  allVerses.insert(35192-1, ""); // 35192)
  allVerses.insert(35193-1, ""); // 35193)
  allVerses.insert(35194-1, ""); // 35194)
  allVerses.insert(37564-1, ""); // 37564)

  // След всички горни действия, би трябвало тук да имаме allVerses с count = 37993 (MAX_VERSES), т.е HBT формат.
  if (allVerses.count() != MAX_VERSES) return; // Тази проверка е излишна, но да има...

  // Поставяне на номерата на редовете:
  if (chBoxAddNumbersToVerses->isChecked())
  {
    quint8 autoVerseNumber = 0;
    quint8 bookCode = 0;
    quint8 chapterCode = 0;
    for(quint16 i = 0; i < MAX_VERSES; i++)
    {
      if (bookCode != MO->toBookCode(i) || chapterCode != MO->toChapterCode(i)) // Започва нова глава.
      {
        autoVerseNumber = 0;
      }

      bookCode = MO->toBookCode(i);
      chapterCode = MO->toChapterCode(i); // Този метод връща или chapters66ExtArr или chapters77ExtArr според избраната номерация. Това дава възможност да се конвертират текстовете до желаната номерация по избор на потребителя.

      if (!allVerses[i].isEmpty()) // Ако има стих (не е празен ред).
      {
        autoVerseNumber++;
        allVerses[i] = QString("%1. %2").arg(autoVerseNumber).arg(allVerses[i]); // Прибавя автоматично изчислен номер.
      }
    }
  }

  // Добавяне на служебната информация:
  //
  // STRUCTURE_VERSION=3
  // NAME=Протестантски (1940)
  // SHORT_DESCRIPTION=Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>
  // NUMERATION_CODE=1
  // NATIVE_VERSE_NUMERATION=Yes
  // FONT_FAMILY=
  // LAYOUT_DIRECTION=LeftToRight
  // LANGUAGE=
  // LAST_MODIFY_DATE=
  // DESCRIPTION:
  // Ревизирано издание от 1940 г. Всички права запазени © 1995-2005 <u>www.bibliata.com</u>.<br>
  //
  allVerses << QString(""); // Празен ред.
  allVerses << QString("STRUCTURE_VERSION=3");
  allVerses << QString("NAME=%1").arg( name.isEmpty() ? QFileInfo(newFileName).baseName() : name );
  allVerses << QString("SHORT_DESCRIPTION=%1").arg(shortDescription);
  allVerses << QString("NUMERATION_CODE=%1").arg( (MO->SVars.currentNumeration == NUMERATION__1) ? "1" : "2");
  allVerses << QString("NATIVE_VERSE_NUMERATION=%1").arg( (chBoxAddNumbersToVerses->isChecked()) ? "Yes" : "No" );
  allVerses << QString("FONT_FAMILY=%1").arg(fontFamily);
  allVerses << QString("LAYOUT_DIRECTION=%1").arg("LeftToRight");
  allVerses << QString("LANGUAGE=%1").arg(language);
  allVerses << QString("LAST_MODIFY_DATE=%1").arg(lastModifyDate);
  allVerses << QString("DESCRIPTION:");
  allVerses << description;
  if (additionalDescription.count() > 0)
  {
    allVerses << QString("<br />");
    allVerses << QString("_______<br />");
    allVerses << additionalDescription;
  }

  // Запис на файла:
  QFile wfile(newFileName);
  if (wfile.open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    for (int v = 0; v < allVerses.count(); v++)
    {
      wfile.write(QString("%1\n").arg(allVerses[v]).toUtf8());
    }
    wfile.close();
  }

  QMessageBox::information(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString("%1\n%2").arg(MO->TS->ConversionSuccessful_v1).arg(newFileName));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// Сравняване на главите:
  //QString fileName1 = QString("C:/Bulgarian_Prot1940.hbt");
  //if (!QFile::exists(fileName1)) return;
  //QFile rfile1(fileName1);
  //rfile1.open(QIODevice::ReadOnly | QIODevice::Text);
  //
  //if (!QFile::exists(newFileName)) return;
  //QFile rfile2(newFileName);
  //rfile2.open(QIODevice::ReadOnly | QIODevice::Text);
  //
  //QFile wfile2(newFileName + "_");
  //if (!wfile2.open(QIODevice::WriteOnly | QIODevice::Text)) return; // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  //
  //char buf1[6144];
  //char buf2[6144];
  //QString sbuf1 = "";
  //QString sbuf2 = "";
  //qint32 diff = 0;
  //qint32 row = 0;
  //while (rfile1.readLine(buf1, sizeof(buf1)) != -1 && rfile2.readLine(buf2, sizeof(buf2)) != -1)
  //{
  //  row++;
  //  sbuf1 = QString("%1").arg(buf1).trimmed();      sbuf1.remove(QString("</JW>"));  sbuf1.remove(QString("<JW>"));
  //  sbuf2 = QString("%1").arg(buf2).trimmed();
  //  if (sbuf1.left(20) != sbuf2.left(20))
  //  {
  //    diff++;
  //    wfile2.write(QString("%1\t\t%2\n"  ).arg(row).arg(sbuf1).toUtf8());
  //    wfile2.write(QString("%1\t\t%2\n\n").arg(row).arg(sbuf2).toUtf8());
  //  }
  //}
  //rfile2.close();
  //rfile1.close();
  //wfile2.close();
  //QMessageBox::information(this, QString("Bible Text Convertor - %1").arg(QCoreApplication::applicationName()), QString("Diff: %1").arg(diff));
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
