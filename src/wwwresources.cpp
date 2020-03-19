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

#include "wwwresources.h"

WWWResources::WWWResources(MainWindow *mainWindow)
{
  setMinimumSize(10, 10);
  resize(660, 460);

  MW = mainWindow;
  MW->WWWResIsOpen = true;

  textBrowser = new QTextBrowser(this);
  textBrowser->setMinimumSize(30, 10);
  textBrowser->setOpenExternalLinks(true); // За отваряне на линковете.
  textBrowser->setOpenLinks(true);         // За отваряне на линковете.
  textBrowser->setWordWrapMode(QTextOption::NoWrap);
  textBrowser->setReadOnly(true);

  AddGroupBox = new QGroupBox(MW->MO->TS->AddLink_v1, this);
  AddGroupBox->setVisible(false);

    QLabel *AddUrlLabel = new QLabel(MW->MO->TS->URL_v1, AddGroupBox);
    AddUrlLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *AddDescriptionLabel = new QLabel(MW->MO->TS->Description_v1, AddGroupBox);
    AddDescriptionLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    AddURLLineEdit = new QLineEdit(AddGroupBox);
    AddURLLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    AddDescriptionLineEdit = new QLineEdit(AddGroupBox);
    AddDescriptionLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    InsertBtn = new QPushButton(MW->MO->TS->InsertLinkRow_v1, AddGroupBox);
    InsertBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(InsertBtn, SIGNAL(clicked()), this, SLOT(slotInsertBtn()));

    InsertComboBox = new QComboBox(AddGroupBox);
    InsertComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


  EditDelGroupBox = new QGroupBox(MW->MO->TS->EditDelLink_v1, this);
  EditDelGroupBox->setVisible(false);

    QLabel *EditUrlLabel = new QLabel(MW->MO->TS->URL_v1, EditDelGroupBox);
    EditUrlLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *EditDescriptionLabel = new QLabel(MW->MO->TS->Description_v1, EditDelGroupBox);
    EditDescriptionLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    EditURLLineEdit = new QLineEdit(EditDelGroupBox);
    EditURLLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    EditURLLineEdit->setEnabled(false);

    EditDescriptionLineEdit = new QLineEdit(EditDelGroupBox);
    EditDescriptionLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    EditDescriptionLineEdit->setEnabled(false);

    ChoiceComboBox = new QComboBox(EditDelGroupBox);
    ChoiceComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(ChoiceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChoiceComboBox(int)));

    SaveBtn = new QPushButton(MW->MO->TS->Save_v1, EditDelGroupBox); // Записва   Запиши промените
    SaveBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    SaveBtn->setEnabled(false);
    connect(SaveBtn, SIGNAL(clicked()), this, SLOT(slotSaveBtn()));

    DeleteBtn = new QPushButton(MW->MO->TS->DeleteLinkRow_v1, EditDelGroupBox);
    DeleteBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    DeleteBtn->setEnabled(false);
    connect(DeleteBtn, SIGNAL(clicked()), this, SLOT(slotDeleteBtn()));

  AddPanelBtn = new QPushButton(MW->MO->TS->AddLink_v1, this);
  AddPanelBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  AddPanelBtn->setCheckable(true);
  connect(AddPanelBtn, SIGNAL(toggled(bool)), this, SLOT(slotAddPanelBtn_Toggled(bool)));

  EditDelPanelBtn = new QPushButton(MW->MO->TS->EditDelLink_v1, this);
  EditDelPanelBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  EditDelPanelBtn->setCheckable(true);
  connect(EditDelPanelBtn, SIGNAL(toggled(bool)), this, SLOT(slotEditDelPanelBtn_Toggled(bool)));

  CloseBtn = new QPushButton(MW->MO->TS->CloseWindow_v1, this);
  CloseBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(CloseBtn, SIGNAL(clicked()), this, SLOT(close()));


  QGridLayout *AddGLayout = new QGridLayout(AddGroupBox);
  AddGLayout->setSpacing(2);
  AddGLayout->setMargin(4);
  AddGLayout->addWidget(AddUrlLabel, 0, 0, 1, 1);
  AddGLayout->addWidget(AddURLLineEdit, 0, 1, 1, 3);
  AddGLayout->addWidget(AddDescriptionLabel, 1, 0, 1, 1);
  AddGLayout->addWidget(AddDescriptionLineEdit, 1, 1, 1, 3);
  AddGLayout->addWidget(InsertComboBox, 2, 1, 1, 1);
  AddGLayout->addWidget(InsertBtn, 2, 3, 1, 1);

  QGridLayout *EditDelGLayout = new QGridLayout(EditDelGroupBox);
  EditDelGLayout->setSpacing(2);
  EditDelGLayout->setMargin(4);
  EditDelGLayout->addWidget(EditUrlLabel, 0, 0, 1, 1);
  EditDelGLayout->addWidget(EditURLLineEdit, 0, 1, 1, 3);
  EditDelGLayout->addWidget(EditDescriptionLabel, 1, 0, 1, 1);
  EditDelGLayout->addWidget(EditDescriptionLineEdit, 1, 1, 1, 3);
  EditDelGLayout->addWidget(ChoiceComboBox, 2, 1, 1, 1);
  EditDelGLayout->addWidget(SaveBtn, 2, 2, 1, 1);
  EditDelGLayout->addWidget(DeleteBtn, 2, 3, 1, 1);

  QSpacerItem *HSpacer = new QSpacerItem(206, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  QHBoxLayout *HLayout = new QHBoxLayout();
  HLayout->setSpacing(2);
  HLayout->addWidget(AddPanelBtn);
  HLayout->addWidget(EditDelPanelBtn);
  HLayout->addItem(HSpacer);
  HLayout->addWidget(CloseBtn);

  QVBoxLayout *VLayout = new QVBoxLayout();
  VLayout->addWidget(textBrowser);
  VLayout->addWidget(AddGroupBox);
  VLayout->addWidget(EditDelGroupBox);
  VLayout->addLayout(HLayout);

  QVBoxLayout *MainLayout = new QVBoxLayout(this);
  MainLayout->setSpacing(2);
  MainLayout->setMargin(2);
  MainLayout->addLayout(VLayout);

  init();
}

WWWResources::~WWWResources()
{
  MW->WWWResIsOpen = false;
}

void WWWResources::closeEvent(QCloseEvent *e)
{
  if (modified) save();
  deleteLater(); // Това ще предизвика извикването на деконструктура, който по принцип не се извиква при натискане на бутона за затваряне на формата, а само при delete.
  e->accept();
}

void WWWResources::init()
{
  modified = false;
  loadFile();
  showLinks(false);
  refreshCombo();
}

void WWWResources::loadFile()
{
  QString fileName = QString("%1/Resources/WWWResources.txt").arg(MW->MO->applicationHomePath);
  if (!QFile::exists(fileName)) // Ако файлът не съществува.
  {
    writeNewFile(); // Създава файл с няколко линка.
  }
  QFile rfile(fileName);
  rfile.open(QIODevice::ReadOnly);

  char buf[6144];
  qint64 lineLength = rfile.readLine(buf, sizeof(buf)); // Чете адреса на първия линк.
  while (lineLength != -1) // Ако/Докато има прочетен адрес на линк.
  {
    URL_DESC ud;
    ud.url = QString(buf); // Записва адреса на линка.
    lineLength = rfile.readLine(buf, sizeof(buf)); // Чете описанието на линка.
    if (lineLength != -1) // Ако е прочетено описанието на линка.
      ud.description = QString(buf); // Записва описанието на линка.
    else // Ако не е прочетено описанието (значи има грешка във файла).
      ud.description = MW->MO->TS->FileReadError_v1;

    ud.url.remove(QString("\r"));
    ud.url.remove(QString("\n"));
    ud.description.remove(QString("\r"));
    ud.description.remove(QString("\n"));
    UD << ud; // Добавя новопрочетения линк.

    lineLength = rfile.readLine(buf, sizeof(buf)); // Чете адреса на следващия линк.
  }
  rfile.close();
}

void WWWResources::showLinks(bool withNumber)
{
  QString link = "";
  QString number = "";
  for (int i = 0; i < UD.count(); i++)
  {
    if (withNumber) number = QString("<font color=#ff6050>%1.</font> ").arg(i+1);

    if (UD[i].url.isEmpty())
    {
      link += QString("%1<font color=#00aaaa>%2</font><br />").arg(number).arg(UD[i].description);
    }
    else
    {
      if (UD[i].description.isEmpty())
        link += QString("%1<a href=\"%2\">%2</a><br />").arg(number).arg(UD[i].url);
      else
        link += QString("%1<a href=\"%2\">%2</a> - %3<br />").arg(number).arg(UD[i].url).arg(UD[i].description);
    }
  }

  if (withNumber)
  {
    link += QString("<font color=#a0a0a0><hr>%1<br />%2<br />%3<br />%4<br />%5</font>").arg(MW->MO->TS->EditLinksInfo1_v1).arg(MW->MO->TS->EditLinksInfo2_v1).arg(MW->MO->TS->EditLinksInfo3_v1).arg(MW->MO->TS->EditLinksInfo4_v1).arg(MW->MO->TS->EditLinksInfo5_v1);
  }

  textBrowser->setHtml(link);
}

void WWWResources::writeNewFile()
{
  QString text = "\n";
  text += "MatCrossBible\n";
  text += "https://www.matcraft.org/MatCrossBible/\n";
  text += "The official website of MatCrossBible\n";
  text += "\n";
  text += "\n";

  QFile wfile(QString("%1/Resources/WWWResources.txt").arg(MW->MO->applicationHomePath));
  wfile.open(QIODevice::WriteOnly | QIODevice::Text); // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.

  QTextStream out(&wfile);
  out << text;

  wfile.close();
}

void WWWResources::save()
{
  QString text = "";
  for (int i = 0; i < UD.count(); i++)
  {
    text += QString("%1\n").arg(UD[i].url);
    text += QString("%1\n").arg(UD[i].description);
  }

  QFile wfile(QString("%1/Resources/WWWResources.txt").arg(MW->MO->applicationHomePath));
  wfile.open(QIODevice::WriteOnly | QIODevice::Text); // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.

  QTextStream out(&wfile);
  out << text;

  wfile.close();
}

void WWWResources::refreshCombo()
{
  ChoiceComboBox->clear();
  InsertComboBox->clear();
  ChoiceComboBox->addItem(MW->MO->TS->Row_v1);
  for (int i = 0; i < UD.count(); i++)
  {
    ChoiceComboBox->addItem(QString("%1").arg(i+1));
    InsertComboBox->addItem(QString("%1").arg(i+1));
  }
  InsertComboBox->addItem(QString("%1").arg(UD.count()+1)); // Добавя още един номер към списъка, така че да може да се добави след съществуващите.
  InsertComboBox->setCurrentIndex(UD.count()); // Поставя последния номер на фокус.
}

void WWWResources::slotInsertBtn()
{
  URL_DESC ud;
  ud.url = AddURLLineEdit->text();
  if ( ud.url.count() > 0 && !ud.url.contains(QString("http://")) && !ud.url.contains(QString("https://")) ) ud.url = QString("http://%1").arg(ud.url);
  ud.description = AddDescriptionLineEdit->text();
  UD.insert(InsertComboBox->currentIndex(), (URL_DESC)ud);
  modified = true;
  refreshCombo();
  showLinks(true);
}

void WWWResources::slotChoiceComboBox(int index)
{
  if (index <= 0)
  {
    EditURLLineEdit->setText("");
    EditDescriptionLineEdit->setText("");
    EditURLLineEdit->setEnabled(false);
    EditDescriptionLineEdit->setEnabled(false);
    SaveBtn->setEnabled(false);
    DeleteBtn->setEnabled(false);
  }
  else
  {
    EditURLLineEdit->setText(UD[index-1].url);
    EditDescriptionLineEdit->setText(UD[index-1].description);
    EditURLLineEdit->setEnabled(true);
    EditDescriptionLineEdit->setEnabled(true);
    SaveBtn->setEnabled(true);
    DeleteBtn->setEnabled(true);
  }
}

void WWWResources::slotSaveBtn()
{
  int i = ChoiceComboBox->currentIndex()-1;
  if (i == -1) return; // Това е излишно, защото бутонът няма да е активен.
  UD[i].url = EditURLLineEdit->text();
  if ( UD[i].url.count() > 0 && !UD[i].url.contains(QString("http://")) && !UD[i].url.contains(QString("https://")) ) UD[i].url = QString("http://%1").arg(UD[i].url);
  UD[i].description = EditDescriptionLineEdit->text();
  modified = true;
  showLinks(true);
}

void WWWResources::slotDeleteBtn()
{
  int i = ChoiceComboBox->currentIndex()-1;
  if (i == -1) return; // Това е излишно, защото бутонът няма да е активен.
  UD.removeAt(i);
  modified = true;
  refreshCombo();
  showLinks(true);
}

void WWWResources::slotAddPanelBtn_Toggled(bool checked)
{
  AddGroupBox->setVisible(checked);
  showLinks(AddPanelBtn->isChecked() || EditDelPanelBtn->isChecked());
}

void WWWResources::slotEditDelPanelBtn_Toggled(bool checked)
{
  EditDelGroupBox->setVisible(checked);
  showLinks(AddPanelBtn->isChecked() || EditDelPanelBtn->isChecked());
}
