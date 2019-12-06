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

#include "mainwindow.h"
#include <QMessageBox> // QMessageBox::information(this, QString(""), QString(""));

MainWindow::MainWindow()
{
  MO = new MainObject();

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle(QCoreApplication::applicationName());


  mainToolBar = 0; // Тази начална инициализация е важна! В slotFocusChanged се прави проверка.
  mDockMain = 0;
  mDockBooks = 0;
  mDockBookmarks = 0;
  mDockSearch = 0;
  mDockProjector = 0;
  audioToolBar = 0;
  projectorWidget = 0;
  trayIcon = 0; // For TrayIcon.
  pad = 0;
  padIsOpen = false; // Стойността на този флаг се променя в самия pad.cpp. Тук само се проверява.
  WWWResIsOpen = false; // Стойността на този флаг се променя в самия WWWResources.cpp. Тук само се проверява.
  showWinDimensions = false;

  ctrlKeyPressed = false;
  altOnlyKeyPressed = false;
  needToRestart = false;
  iconColorForms = QColor();
  iconColorMenus = QColor();
  //lightTheme = false;
  findInTextString = "";
  findInTextOptions = 0; // Изключени опции за търсене.
  normGeometry = geometry();
  windowMaximized = false;
  currentSession = 0;

  exeName = "";
  startSession = 255;


  setAppColors();
  createViews(); // Създава тулбаровете и разделите.
  createTrayIcon(); // For TrayIcon.

  statusBar = new QStatusBar(this);
  statusBar->setObjectName(QStringLiteral("statusBar"));
  setStatusBar(statusBar);
  statusBar->hide(); // Статус-барът се показва само при необходимост.

  connect(QApplication::instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(slotFocusChanged(QWidget*, QWidget*)));

  // Проверка на аргументите от командния ред.
  commandLineAbsIndex = MAX_VERSES;
  QStringList commandLine = QCoreApplication::arguments(); // Списък с аргументите на програмата. Името на програмата е аргумент 0.
  if (commandLine.size() > 1) // Ако има аргументи след името на програмата. Ако в командния ред не е зададено коя книга, глава и стих да се покаже, показва последните отворени такива.
  {
    // Проверява се дали е зададено правилно от командния ред коя книга, глава и стих да се покаже.
    // За пример: "MatCrossBible 0 55" ще покаже Битие 2:25 в Сесия 0 (Стандартна сесия) (55 е абсолютният индекс на стиха, започващ от нула).
    //            "MatCrossBible 2 55" ще покаже Битие 2:25 в Сесия 2.
    //            "MatCrossBible 0"    ще отвори програмата и ще зареди Сесия 0 (Стандартна сесия).
    //            "MatCrossBible 2"    ще отвори програмата и ще зареди Сесия 2.
    // Името на програмата е първият аргумент, затова проверката е за 3 аргумента.
    if (commandLine.size() >= 3) // Ако има два или повече аргумента след името на програмата (ако са повече игнорира излишните).
    {
      currentSession = (quint8)commandLine.at(1).toUShort(); // Първият аргумент е номерът на сесията в която трябва да се отвори текста.
      commandLineAbsIndex = commandLine.at(2).toInt(); // Кода на книгата се записва винаги по западния стандарт, затова тук се конвертира до източния, ако е нужно.
      if (commandLineAbsIndex < 0 || commandLineAbsIndex >= MAX_VERSES)
      {
        commandLineAbsIndex = MAX_VERSES;
        qDebug("Invalid arguments! For example: MatCrossBible 0 55");
      }
      commandLineAbsIndex = MO->toEasternExtIndexIfNeed(commandLineAbsIndex); // Абсолютният индекс се записва винаги по западния стандарт, затова тук се конвертира до източния, ако е нужно.
    }
    else if (commandLine.size() == 2 && !commandLine.at(1).isEmpty()) // Ако има само един аргумент след името на програмата.
    {
      currentSession = (quint8)commandLine.at(1).toUShort(); // Първият аргумент е номерът на сесията в която трябва да се отвори текста.
      commandLineAbsIndex = MAX_VERSES;
    }

    if (commandLineAbsIndex >= MAX_VERSES) // Ако целта е да се зареди конкретна сесия.
    {
      if (currentSession > 8) // При грешно зададен номер на сесия.
      {
        currentSession = 0;
        qDebug("Invalid arguments! For example: MatCrossBible 2");
      }
    }
  }

  loadSessionSettings(currentSession); // Зарежда последнозаписаните настройки и показва текста.

  //QTimer::singleShot(200, this, SLOT(slotOnFormCreated()));
  
  if (MO->isNewVersion) QTimer::singleShot(2000, this, SLOT(slotOther_Settings())); // Отваря формата с настройките, като на преден план е първият таб - за избор на език (за да покаже на потребителя, че може да избере език).
}

MainWindow::~MainWindow()
{
  if (padIsOpen)
  {
    pad->close(); // Ако не се извика close(), pad изчезва като форма, но остава като процес.
    delete pad; // Това пък извиква деконструктура на pad, където се променя padIsOpen на false.
    pad = 0;
  }

  if (WWWResIsOpen)
  {
    WWWRes->close(); // Ако не се извика close(), WWWRes изчезва като форма, но остава като процес.
    delete WWWRes; // Това пък извиква деконструктура на WWWRes, където се променя WWWResIsOpen на false.
    WWWRes = 0;
  }

  delete MO; // Извиква деструктора.
  MO = 0; // Това се проверява в деструктора на TextView.

  for (int index = 0; index < HDocks.length(); index++)
  {
    delete HDocks[index].textView; //HDocks[index].dockWidget->closeDockWidget();
    delete HDocks[index].dockWidget;
  }
  for (int index = 0; index < ODocks.length(); index++)
  {
    if (ODocks[index].dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY) delete ODocks[index].dictionary; //ODocks[index].dockWidget->closeDockWidget();
    delete ODocks[index].dockWidget;
  }

  delete mDockSearch;
  delete mDockProjector;

  //qDebug("~~~~~~~~ MainWindow");
  QApplication::quit(); // Това затваря всички други прозорци (например хелпа и бележника). Особено нужно е ако е активирана TrayIcon. // For TrayIcon.
  delete trayIcon; // For TrayIcon.
  //qDebug("~~~~~~~~");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  //Ако има системен трей И е разрешена трей икона И не е разрешено затваряне на прозореца или приложението.
  if ( trayIcon != 0 && MO->SVars.enableTrayIcon && !MO->enableExitAction ) // Ако е натиснат бутона за затваряне на програмата // For TrayIcon.
  {
    hide();
    event->ignore();
    return;
  }

  //if (isHidden()) show(); // Показва прозореца такъв какъвто е бил преди да се скрие (нормален или максимизиран). // For TrayIcon.

  statusBar->hide(); // Статус-бара се скрива преди да се запише състоянието на сесията (не знам дали това има значение, но за всеки случай).
  saveSessionSettings(currentSession); // Ако програмата не е била затворена от слота slotLoadSession(), в който настройките са били записани.

  if (!exeName.isEmpty() && startSession < 9)
    QProcess::startDetached(exeName, (QStringList() << QString("%1").arg(startSession))); // Пуска нова програма.

  event->accept();
}

void MainWindow::setAppColors()
{
  int h, s, v; h = 0; s = 0; v = 0;
  
  // Определя цвета на иконите в другите форми, които се отварят от главната (затова този цвят се определя само в началото преди промяната на цвета на главната форма):
  if (!iconColorForms.isValid())
  {
    iconColorForms = this->palette().brush(QPalette::Active, QPalette::Window).color(); // Цвят на прозорците.
    iconColorForms.getHsv(&h, &s, &v);
    if (v > 127) // Ако темата на прозорците е светла.
    {
      v = v - 150; if (v < 40) v = 40;
      iconColorForms.setHsv(h, s, v);
    }
    else // Ако темата на прозорците е тъмна.
    {
      v = v + 170; if (v > 240) v = 240;
      iconColorForms.setHsv(h, s, v);
    }
  }

  // Сменя цветовете на формите и тулбаровете:
  QColor enabledTextColor = MO->SVars.appColorB; // Цвят на текста. Той трябва да бъде малко по-тъмен или малко по-светъл, според избрания цвят (който е цвета на иконите).
  enabledTextColor.getHsv(&h, &s, &v);
  if (v > 127) // Ако цветът е светъл.
  {
    v = v + 30; if (v > 255) v = 255; // Прави го още по-светъл.
    enabledTextColor.setHsv(h, s, v);
  }
  else // Ако цветът е тъмен.
  {
    v = v - 20; if (v < 0) v = 0; // Прави го още по-тъмен.
    enabledTextColor.setHsv(h, s, v);
  }
  QColor disabledTextColor = enabledTextColor;   disabledTextColor.setAlpha(110); // Цвят на текста, когато компонентът е disabled.
  
  QPalette winPalette = this->palette();
  winPalette.setBrush(QPalette::Base, MO->SVars.appColorF); // Това трябва да се използва тук, защото някои компоненти (като чекбоксчетата и радиобутоните) стават малко грозни.
  winPalette.setBrush(QPalette::Window, MO->SVars.appColorF);
  winPalette.setBrush(QPalette::Button, MO->SVars.appColorF);
  
  winPalette.setBrush(QPalette::Active,   QPalette::Text, enabledTextColor);
  winPalette.setBrush(QPalette::Inactive, QPalette::Text, enabledTextColor);
  winPalette.setBrush(QPalette::Disabled, QPalette::Text, disabledTextColor);
  
  winPalette.setBrush(QPalette::Active,   QPalette::WindowText, enabledTextColor);
  winPalette.setBrush(QPalette::Inactive, QPalette::WindowText, enabledTextColor);
  winPalette.setBrush(QPalette::Disabled, QPalette::WindowText, disabledTextColor);
  
  winPalette.setBrush(QPalette::Active,   QPalette::ButtonText, enabledTextColor);
  winPalette.setBrush(QPalette::Inactive, QPalette::ButtonText, enabledTextColor);
  winPalette.setBrush(QPalette::Disabled, QPalette::ButtonText, disabledTextColor);
  this->setPalette(winPalette);
  
  //// Определя светла или тъмна е темата (след смяната на цветовете на главната форма):
  //this->palette().brush(QPalette::Active, QPalette::Window).color().getHsv(&h, &s, &v); // Цвят на прозорците.
  //if (v > 127) // Ако темата на прозорците е светла.
  //{
  //  lightTheme = true;
  //}
  //else // Ако темата на прозорците е тъмна.
  //{
  //  lightTheme = false;
  //}

  // Определя цвета на иконите в контекстното меню:
  QMenu menu; // Създава едно меню за да му вземе цвета.
  iconColorMenus = menu.palette().brush(QPalette::Active, QPalette::Window).color(); // Цвят на контекстното меню.
  iconColorMenus.getHsv(&h, &s, &v);
  if (v > 127) // Ако темата на контекстното меню е светла.
  {
    v = v - 150; if (v < 40) v = 40;
    iconColorMenus.setHsv(h, s, v);
  }
  else // Ако темата на контекстното меню е тъмна.
  {
    v = v + 170; if (v > 240) v = 240;
    iconColorMenus.setHsv(h, s, v);
  }
}

void MainWindow::createViews()
{
  // Main ToolBar
  mainToolBar = new MainToolBar(MO->TS, MO->SVars.TMenuIconSize, MO->SVars.appColorF, MO->SVars.appColorB, 0); // Parent-а тук е нула, но ще се сетне в TMenu.
  connect(mainToolBar->btnNavigation_New, SIGNAL(clicked()), this, SLOT(slotNavigation_newHDock()));
  connect(mainToolBar->btnNavigation_Books, SIGNAL(clicked()), this, SLOT(slotNavigation_BooksToolBar()));
  connect(mainToolBar->btnNavigation_Bookmarks, SIGNAL(clicked()), this, SLOT(slotNavigation_BookmarksToolBar()));
  connect(mainToolBar->btnNavigation_PreviousBook, SIGNAL(clicked()), this, SLOT(slotNavigation_PreviousBook()));
  connect(mainToolBar->btnNavigation_NextBook, SIGNAL(clicked()), this, SLOT(slotNavigation_NextBook()));
  connect(mainToolBar->btnNavigation_PreviousChapter, SIGNAL(clicked()), this, SLOT(slotNavigation_PreviousChapter()));
  connect(mainToolBar->btnNavigation_NextChapter, SIGNAL(clicked()), this, SLOT(slotNavigation_NextChapter()));
  connect(mainToolBar->btnNavigation_PreviousVerse, SIGNAL(clicked()), this, SLOT(slotNavigation_PreviousVerse()));
  connect(mainToolBar->btnNavigation_NextVerse, SIGNAL(clicked()), this, SLOT(slotNavigation_NextVerse()));
  connect(mainToolBar->btnNavigation_PreviousChaptersDailyRead, SIGNAL(clicked()), this, SLOT(slotNavigation_PreviousChaptersDailyRead()));
  connect(mainToolBar->btnNavigation_NextChaptersDailyRead, SIGNAL(clicked()), this, SLOT(slotNavigation_NextChaptersDailyRead()));
  connect(mainToolBar->btnNavigation_PreviousChapterDailyRead, SIGNAL(clicked()), this, SLOT(slotNavigation_PreviousChapterDailyRead()));
  connect(mainToolBar->btnNavigation_NextChapterDailyRead, SIGNAL(clicked()), this, SLOT(slotNavigation_NextChapterDailyRead()));
  connect(mainToolBar->btnNavigation_DailyRead, SIGNAL(clicked()), this, SLOT(slotNavigation_DailyReadToolBar()));
  connect(mainToolBar->btnNavigation_GoBack, SIGNAL(clicked()), this, SLOT(slotNavigation_GoBack()));
  connect(mainToolBar->btnNavigation_GoForward, SIGNAL(clicked()), this, SLOT(slotNavigation_GoForward()));

  connect(mainToolBar->btnText_Search, SIGNAL(clicked()), this, SLOT(slotText_SearchCenter()));
  connect(mainToolBar->btnText_BibleTexts, SIGNAL(clicked()), this, SLOT(slotText_BibleTextsToolBar()));
  connect(mainToolBar->btnText_Audio, SIGNAL(clicked()), this, SLOT(slotText_AudioToolBar()));
  connect(mainToolBar->btnText_ZoomIn, SIGNAL(clicked()), this, SLOT(slotText_ZoomIn()));
  connect(mainToolBar->btnText_ZoomOut, SIGNAL(clicked()), this, SLOT(slotText_ZoomOut()));
  connect(mainToolBar->btnText_ZoomNormal, SIGNAL(clicked()), this, SLOT(slotText_ZoomNormal()));
  connect(mainToolBar->btnText_Statistics, SIGNAL(clicked()), this, SLOT(slotText_Statistics()));

  connect(mainToolBar->btnOther_Pad, SIGNAL(clicked()), this, SLOT(slotOther_Pad()));
  connect(mainToolBar->btnOther_Dictionary, SIGNAL(clicked()), this, SLOT(slotOther_Dictionary()));
  connect(mainToolBar->btnOther_ExternalImages, SIGNAL(clicked()), this, SLOT(slotOther_ExternalImages()));
  connect(mainToolBar->btnOther_WWW, SIGNAL(clicked()), this, SLOT(slotOther_Links()));
  connect(mainToolBar->btnOther_Projector, SIGNAL(clicked()), this, SLOT(slotOther_ProjectorToolBar()));
  connect(mainToolBar->btnOther_Settings, SIGNAL(clicked()), this, SLOT(slotOther_Settings()));

  connect(mainToolBar->btnFile_Exit, SIGNAL(clicked()), this, SLOT(slotFile_Exit()));
  connect(mainToolBar->btnFile_Session, SIGNAL(clicked()), this, SLOT(slotFile_SessionToolBar()));

  connect(mainToolBar->btnHelp_Help, SIGNAL(clicked()), this, SLOT(slotHelp_Help()));
  connect(mainToolBar->btnHelp_AboutMatCrossBible, SIGNAL(clicked()), this, SLOT(slotHelp_About()));

  // Ако няма нито един .hbt файл, прави почти всичко неактивно:
  if (MO->bibleTextList.size() == 0)
  {
    mainToolBar->btnNavigation_New->setEnabled(false);
    mainToolBar->btnNavigation_Books->setEnabled(false);
    mainToolBar->btnNavigation_Bookmarks->setEnabled(false);
    mainToolBar->btnNavigation_GoBack->setEnabled(false);
    mainToolBar->btnNavigation_GoForward->setEnabled(false);
    mainToolBar->btnNavigation_PreviousBook->setEnabled(false);
    mainToolBar->btnNavigation_NextBook->setEnabled(false);
    mainToolBar->btnNavigation_PreviousChapter->setEnabled(false);
    mainToolBar->btnNavigation_NextChapter->setEnabled(false);
    mainToolBar->btnNavigation_PreviousVerse->setEnabled(false);
    mainToolBar->btnNavigation_NextVerse->setEnabled(false);
    mainToolBar->btnNavigation_PreviousChaptersDailyRead->setEnabled(false);
    mainToolBar->btnNavigation_NextChaptersDailyRead->setEnabled(false);
    mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(false);
    mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);
    mainToolBar->btnNavigation_DailyRead->setEnabled(false);
    mainToolBar->btnText_Search->setEnabled(false);
    mainToolBar->btnText_Audio->setEnabled(false);
    mainToolBar->btnText_ZoomIn->setEnabled(false);
    mainToolBar->btnText_ZoomOut->setEnabled(false);
    mainToolBar->btnText_ZoomNormal->setEnabled(false);
    mainToolBar->btnText_SearchInTextPrevious->setEnabled(false);
    mainToolBar->btnText_SearchInTextNext->setEnabled(false);
    mainToolBar->btnText_Statistics->setEnabled(false);
    mainToolBar->btnOther_Dictionary->setEnabled(false);
    mainToolBar->btnOther_Projector->setEnabled(false);
    mainToolBar->btnFile_FileMenu->setEnabled(false);
    mainToolBar->btnFile_Session->setEnabled(false);
    // Отваря прозореца с информация за наличните текстове, където ще се покаже съобщение, че няма такива.
    QTimer::singleShot(250, this, SLOT(slotBibleTextsInfo())); // Отваря го с малко закъснение за да се появи над основния прозорец.
  }

  // Audio ToolBar
  audioToolBar = new AudioToolBar(this, 0); // Parent-а тук е нула, но ще се сетне в TMenu.
  
  // BibleTexts ToolBar
  bibleTextsToolBar = new QWidget(0); // Parent-а тук е нула, но ще се сетне в TMenu.
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    bibleTextBtn << new QToolButton();
    bibleTextBtn[i]->setText(MO->bibleTextList.at(i).name);
    bibleTextBtn[i]->setAutoRaise(true);
    bibleTextBtn[i]->setToolButtonStyle(Qt::ToolButtonTextOnly);
    bibleTextBtn[i]->setToolTip(MO->bibleTextList.at(i).short_description);
    bibleTextBtn[i]->setCheckable(true);
    bibleTextBtn[i]->setChecked(false);
    //QFont font = bibleTextBtn[i]->font();
    //font.setFamily(MO->bibleTextList.at(i).fontFamily.isEmpty() ? MO->SVars.fontFamily : MO->bibleTextList.at(i).fontFamily);
    //bibleTextBtn[i]->setFont(font);
    connect(bibleTextBtn[i], SIGNAL(clicked()), this, SLOT(slotBibleTexts()));
  }
  reorderBibleTextsBtn = new QToolButton();
  reorderBibleTextsBtn->setText(QString("<>"));
  reorderBibleTextsBtn->setAutoRaise(true);
  reorderBibleTextsBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
  reorderBibleTextsBtn->setToolTip(MO->TS->RearrangeBibletexts_v1);
  if (MO->bibleTextList.size() <= 1) reorderBibleTextsBtn->setVisible(false);
  connect(reorderBibleTextsBtn, SIGNAL(clicked()), this, SLOT(slotReorderBibleTexts()));
  bibleTextsInfoBtn = new QToolButton();
  bibleTextsInfoBtn->setText(MO->TS->Info_v1);
  bibleTextsInfoBtn->setAutoRaise(true);
  bibleTextsInfoBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
  bibleTextsInfoBtn->setToolTip(MO->TS->BibleTextsInfo_v1);
  connect(bibleTextsInfoBtn, SIGNAL(clicked()), this, SLOT(slotBibleTextsInfo()));
  moreBibleTextsBtn = new QToolButton();
  moreBibleTextsBtn->setText(MO->TS->More_v1);
  moreBibleTextsBtn->setAutoRaise(true);
  moreBibleTextsBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
  moreBibleTextsBtn->setToolTip(MO->TS->DownloadMoreBibleTexts_v1);
  connect(moreBibleTextsBtn, SIGNAL(clicked()), this, SLOT(slotMoreBibleTexts()));
  convertBibleTextsBtn = new QToolButton();
  convertBibleTextsBtn->setText(MO->TS->Convert_v1);
  convertBibleTextsBtn->setAutoRaise(true);
  convertBibleTextsBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
  convertBibleTextsBtn->setToolTip(MO->TS->ConvertBibleTexts_v1);
  connect(convertBibleTextsBtn, SIGNAL(clicked()), this, SLOT(slotConvertBibleTexts()));

  QHBoxLayout *bibleTextsToolBarLayout = new QHBoxLayout(bibleTextsToolBar);
  bibleTextsToolBarLayout->setContentsMargins(1, 1, 1, 1); // LTRB
  bibleTextsToolBarLayout->setSpacing(1); // Разстояние между обектите.
  for (quint8 i = 0; i < MO->bibleTextList.size(); i++)
  {
    bibleTextsToolBarLayout->addWidget(bibleTextBtn[i]);
  }
  if (MO->bibleTextList.size() > 0) bibleTextsToolBarLayout->addWidget(getVSeparator());
  bibleTextsToolBarLayout->addWidget(reorderBibleTextsBtn);
  bibleTextsToolBarLayout->addWidget(bibleTextsInfoBtn);
  bibleTextsToolBarLayout->addWidget(moreBibleTextsBtn);
  bibleTextsToolBarLayout->addWidget(convertBibleTextsBtn);
  //bibleTextsToolBarLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum) );
  QFont font = bibleTextsToolBar->font();
  font.setPointSize(MO->SVars.otherToolBarFontSize);
  bibleTextsToolBar->setFont(font);

  // Session ToolBar
  sessionToolBar = new QWidget(0); // Parent-а тук е нула, но ще се сетне в TMenu.
  QButtonGroup *sessionGroup = new QButtonGroup(this);
  QPalette saveSessionChBoxPalette = sessionToolBar->palette();
  saveSessionChBoxPalette.setBrush(QPalette::Base, MO->SVars.dock1TextColorB);
  saveSessionChBoxPalette.setBrush(QPalette::Text, MO->SVars.dock1TextColorF);
  for (quint8 s = 0; s < 9; s++) // 0 - нормална сесия, 1-8 - специални сесии, 9 - не запомня сесия.
  {
    saveSessionChBox[s] = new QCheckBox("");
    saveSessionChBox[s]->setToolTip(MO->TS->SaveSession_v1);
    saveSessionChBox[s]->setChecked(false);
    saveSessionChBox[s]->setMinimumWidth(16); // Това е защото в някои GUIStyle, като няма текст в CheckBox-а, той се изрязва от дясно.
    saveSessionChBox[s]->setPalette(saveSessionChBoxPalette); // Ако се смени цветът на формата, този CheckBox ще си смени цвета едва след рестарт на програмата, но това не е фатално и не си струва да се прави по-сложно.
    saveSessionChBox[s]->setAutoFillBackground(false); // Това е важно да е false за да изглежда по-добре, въпреки че за квадратния CheckBox няма никакво значение (но ако е заоблен ще има).

    sessionBtn[s] = new QToolButton();
    sessionBtn[s]->setText(QString("%1 %2").arg(MO->TS->Session_v1).arg(s));
    sessionBtn[s]->setAutoRaise(true);
    sessionBtn[s]->setToolButtonStyle(Qt::ToolButtonTextOnly);
    sessionBtn[s]->setCheckable(true);
    sessionBtn[s]->setChecked(false);
    connect(sessionBtn[s], SIGNAL(clicked()), this, SLOT(slotLoadSession()));
    sessionGroup->addButton(sessionBtn[s]);
  }
  sessionBtn[0]->setText(MO->TS->StandardSession_v1);

  QHBoxLayout *sessionToolBarLayout = new QHBoxLayout(sessionToolBar);
  sessionToolBarLayout->setContentsMargins(1, 1, 1, 1); // LTRB
  sessionToolBarLayout->setSpacing(1); // Разстояние между обектите.
  for (quint8 s = 0; s < 9; s++)
  {
    sessionToolBarLayout->addWidget(saveSessionChBox[s]);
    sessionToolBarLayout->addWidget(sessionBtn[s]);
    if (s < 8) sessionToolBarLayout->addWidget(getVSeparator());
  }
  //sessionToolBarLayout->addItem( new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum) );
  font = sessionToolBar->font();
  font.setPointSize(MO->SVars.otherToolBarFontSize);
  sessionToolBar->setFont(font);


  tMenu = new TMenu(mainToolBar, audioToolBar, bibleTextsToolBar, sessionToolBar, MO->SVars.appColorF, MO->SVars.appColorB, MO->SVars.TMenuPosition == POSITION_TOP, this);
  tMenu->setAudioToolBarVisible(false);
  tMenu->setBibleTextsToolBarVisible(false);
  tMenu->setSessionToolBarVisible(false);
  tMenu->set3DTitleBar(MO->SVars.docks3DTitleBar);

  setTMenuFontSize();

  mDockMain = new MDock();
  mDockMain->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  //mDockMain->setDockWidgetTabbedTitleBar(false);
  //mDockMain->setDockMargins(2, 2, 2, 2); // LTRB
  //mDockMain->setDockWidgetMinSizePr(QSize(10, 10));
  //mDockMain->setDockWidgetPadding(2);
  //mDockMain->setProperties(true, true, true, true);
  mDockMain->setDockBgColor(MO->SVars.appColorB);
  //mDockMain->setTrackFrameColor(QColor(0, 170, 170));
  mDockMain->setDockGridState("0^100_1_0^100");

  fastAccessWidget = new FastAccessWidget(this);
  fastAccessWidget->setFrame(false);
  fastAccessWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // Preferred Expanding

  booksWidget = new BooksWidget(this);
  booksWidget->setFrameShape(QFrame::NoFrame);
  booksWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

  bookmarksWidget = new BookmarksWidget(this);
  bookmarksWidget->setFrameShape(QFrame::NoFrame);
  bookmarksWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

  projectorWidget = new ProjectorWidget(this);
  projectorWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

  mDockBooks = new BooksToolBar(this, booksWidget, fastAccessWidget, 0);
  mDockBooks->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mDockBooks->setVisible(false);

  mDockBookmarks = new BookmarksToolBar(this, bookmarksWidget, 0);
  mDockBookmarks->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mDockBookmarks->setVisible(false);

  mDockSearch = new SearchToolBar(this, 0);
  mDockSearch->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mDockSearch->setVisible(false);
  mDockSearch->setMinimumWidth(MO->SVars.searchToolBarWidth);
  mDockSearch->setMaximumWidth(MO->SVars.searchToolBarWidth);

  mDockProjector = new ProjectorToolBar(this, projectorWidget, 0);
  mDockProjector->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mDockProjector->setVisible(false);
  //mDockProjector->resetMinimumWidth(); // Този ред трябва да е след долните if-ове, защото в тях се сетват маржините, които той използва.

  QWidget *mainWidget = new QWidget(this);
  setCentralWidget(mainWidget);
  QVBoxLayout *mainContainerLayout = new QVBoxLayout(mainWidget);
  mainContainerLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  mainContainerLayout->setSpacing(0);

  QHBoxLayout *dockContainerLayout = new QHBoxLayout();
  dockContainerLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  dockContainerLayout->setSpacing(0);
  if (MO->TS->globalLayoutDirection == Qt::RightToLeft) dockContainerLayout->setDirection(QBoxLayout::RightToLeft); // Ако дирекшъна на цялото приложение е RightToLeft, компоментите в този лайаут ще се обърнат автоматично, а тук не трябва да става така. Ето защо тук се прави още едно обръщане (отново се задава RightToLeft), с което става нещо като двойно обръщане. Не намерих друг начин да избегна автоматичното обръщане на компонентите на този лайаут, когато има RightToLeft дирекшън на цялото приложение.
  int docksMargT = (MO->SVars.TMenuPosition == POSITION_TOP) ? 2 : 2; // Тук трябва да е 3, но ако е 2 стои по-добре. С 3 се получава твърде дебела черта между панела и прозорците. Втората двойка може да е и 1, въпрос на вкус.
  int docksMargB = (MO->SVars.TMenuPosition == POSITION_TOP) ? 0 : 2; // Тук трябва да е 3, но ако е 2 стои по-добре. С 3 се получава твърде дебела черта между панела и прозорците. Нулата трябва да е нула.
  if (MO->SVars.projectorToolBarPosition == POSITION_LEFT)
  {
    mDockProjector->setDockMargins(0, docksMargT, 3, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockProjector);
  }
  if (MO->SVars.booksToolBarPosition == POSITION_LEFT)
  {
    mDockBooks->setDockMargins(0, docksMargT, 3, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockBooks);
  }
  if (MO->SVars.booksToolBarPosition == POSITION_LEFT)
  {
    mDockBookmarks->setDockMargins(0, docksMargT, 3, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockBookmarks);
  }
  if (MO->SVars.searchToolBarPosition == POSITION_LEFT)
  {
    mDockSearch->setDockMargins(0, docksMargT, 3, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockSearch);
  }
  // --------------------------------------------------------------
  mDockMain->setDockMargins(0, docksMargT, 0, docksMargB); // LTRB
  dockContainerLayout->addWidget(mDockMain);
  // --------------------------------------------------------------
  if (MO->SVars.searchToolBarPosition != POSITION_LEFT) // == POSITION_RIGHT
  {
    mDockSearch->setDockMargins(3, docksMargT, 0, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockSearch);
  }
  if (MO->SVars.booksToolBarPosition != POSITION_LEFT) // == POSITION_RIGHT
  {
    mDockBookmarks->setDockMargins(3, docksMargT, 0, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockBookmarks);
  }
  if (MO->SVars.booksToolBarPosition != POSITION_LEFT) // == POSITION_RIGHT
  {
    mDockBooks->setDockMargins(3, docksMargT, 0, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockBooks);
  }
  if (MO->SVars.projectorToolBarPosition != POSITION_LEFT) // == POSITION_RIGHT
  {
    mDockProjector->setDockMargins(3, docksMargT, 0, docksMargB); // LTRB
    dockContainerLayout->addWidget(mDockProjector);
  }
  
  if (MO->SVars.TMenuPosition == POSITION_TOP)
  {
    mainContainerLayout->addWidget(tMenu);
    mainContainerLayout->addLayout(dockContainerLayout);
  }
  else // POSITION_BOTTOM
  {
    mainContainerLayout->addLayout(dockContainerLayout);
    mainContainerLayout->addWidget(tMenu);
  }

  mDockProjector->resetMinimumWidth();

  currentHolyTextView = 0;
  currentTextView = 0;

  //QFont font;
  ////font.setFamily(MO->SVars.fontFamily); // Това не трябва да се разкоментира, защото всеки текст използва собствен шрифт.
  //font.setPointSize(MO->SVars.fontSize);

  compareTwoTextsAction = new QAction(MO->TS->CompareTwoTexts_v1, this);
  compareTwoTextsAction->setShortcut(Qt::Key_F6);
  connect(compareTwoTextsAction, SIGNAL(triggered()), this, SLOT(slotText_CompareTwoTexts()));
  uniqueWordsInBibleAct = new QAction(MO->TS->UniqueWordsInBible_v1, this);
  connect(uniqueWordsInBibleAct, SIGNAL(triggered()), this, SLOT(slotText_UniqueWordsInBible()));
  uniqueWordsInOTAct = new QAction(MO->TS->UniqueWordsInOT_v1, this);
  connect(uniqueWordsInOTAct, SIGNAL(triggered()), this, SLOT(slotText_UniqueWordsInOT()));
  uniqueWordsInNTAct = new QAction(MO->TS->UniqueWordsInNT_v1, this);
  connect(uniqueWordsInNTAct, SIGNAL(triggered()), this, SLOT(slotText_UniqueWordsInNT()));
  uniqueWordsInBookAct = new QAction(MO->TS->UniqueWordsInBook_v1, this);
  connect(uniqueWordsInBookAct, SIGNAL(triggered()), this, SLOT(slotText_UniqueWordsInBook()));
  uniqueWordsInChapterAct = new QAction(MO->TS->UniqueWordsInChapter_v1, this);
  connect(uniqueWordsInChapterAct, SIGNAL(triggered()), this, SLOT(slotText_UniqueWordsInChapter()));
}

/// TrayIcon ------------------------------------------------------------------------------------------------------------------------

void MainWindow::createTrayIcon() // For TrayIcon.
{
  closeAct = new QAction(Icons::icon_Exit(32, 32, iconColorMenus, iconColorMenus), MO->TS->Exit_v1, this);
  connect(closeAct, SIGNAL(triggered()), this, SLOT(slotFile_Exit()));

  showWindowsAction = new QAction(MO->TS->Open_v1, this);
  connect(showWindowsAction, SIGNAL(triggered()), this, SLOT(show()));

  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(showWindowsAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(closeAct);

  if (QSystemTrayIcon::isSystemTrayAvailable()) // Ако има system tray.
  {
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon( QIcon(":/resources/images/logo32x32.png") );
    trayIcon->setToolTip(QCoreApplication::applicationName());
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotIconActivated(QSystemTrayIcon::ActivationReason)));
  }
}

/// slots ------------------------------------------------------------------------------------------------------------------------

void MainWindow::slotOnFormCreated()
{
  // За да се използва този слот, трябва да се разкоментира таймерът, който го извиква (в конструктора).
}

void MainWindow::slotShow()
{
  if (currentHolyTextView == 0) return; // Това е ако няма нито един текст на Библията.
  currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
  if (currentHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
    currentHolyTextView->showBibleText(currentHolyTextView->currentAbsIndex);
  else // Ако е в режим на ежедневно четене.
    currentHolyTextView->showBibleText(currentDR_AbsIndex);
}

void MainWindow::slotNewSelectedText(QString text)
{
  emit newSelectedText(text);
}

void MainWindow::slotNewSelectedVerse(quint16 absIndex, QString reference)
{
  emit newSelectedVerse(absIndex, reference);
}

/// NavigationToolBar
void MainWindow::slotNavigation_newHDock(MDock */*dock*/, MDockWidget *dockWidget)
{
  if (dockWidget == 0) // Ако е натиснат бутона за нов раздел от TMenu.
    newHDock(false); // Отваря новия раздел до текущия.
  else // Ако е натиснат бутона за нов раздел от друг раздел.
    newHDock(false, dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Отваря новия раздел в същия раздел, като таб.
}

void MainWindow::newHDock(bool loadSession, int posXInDock, int posYInDock, int textZoom, QBitArray activeBibleTexts, quint16 activeBibleTextsCount, quint16 absIndex)
{
  // При зареждане на сесията е създадена (възстановена) мрежата на разделите. Ако при това е станала някаква грешка,
  // по подразбиране се създава нова мрежа с един ред и един раздел. Този метод ще се опита да вмъкне новия раздел
  // където му е мястото, но ако се окаже, че няма такова място, го вмъква на позиция 0,0 (такава 100% ще има).
  // Така ако има проблем с мрежата, всички раздели ще са на позиция 0,0.
  if (MO->bibleTextList.size() == 0) return;
  
  DOCKS newDock;

  newDock.textView = new TextView(this);
  newDock.textView->setMinimumSize(10, 20);
  newDock.dictionary = 0;

  newDock.dockWidget = new MDockWidget(mDockMain, "", true, true, MO->SVars.docks3DTitleBar, 0, DOCK_TYPE__HOLY_TEXT_VIEW);
  newDock.dockWidget->setWidget(newDock.textView);
  newDock.dockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само согнал.
  newDock.dockWidget->setDockWidgetTitleBarFontSize(MO->SVars.otherToolBarFontSize);
  newDock.dockWidget->setDockWidgetBgColor(MO->SVars.appColorF);
  newDock.dockWidget->setDockWidgetTitleBarColor(MO->SVars.appColorF);
  newDock.dockWidget->setDockWidgetTitleBarTextColor(MO->SVars.appColorB);
  newDock.dockWidget->setDockWidgetTitleBarButtonColor(MO->SVars.appColorB);
  newDock.dockWidget->setNewBtnToolTip(MO->TS->NewDockWindow_v1);
  newDock.dockWidget->setMaximizeBtnToolTip(MO->TS->MaximizeNormalize_v1);
  newDock.dockWidget->setCloseBtnToolTip(MO->TS->CloseDockWindow_v1);
  connect(newDock.dockWidget, SIGNAL(dockWidgetNewButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotNavigation_newHDock(MDock *, MDockWidget *))); // Излъчения от New бутона сигнал.
  connect(newDock.dockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotCloseDock(MDock *, MDockWidget *, int, quint8))); // Излъчения от Close бутона сигнал.
  connect(newDock.dockWidget, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotDockWidgetRaised(MDock *, MDockWidget *)));

  newDock.textView->dockWidget = newDock.dockWidget;
  newDock.textView->isCurrentHolyTextView = false; // Указва, че изгледа не е текущият. Ще стане текущ след показването му по-долу.

  if (loadSession) // Ако е заредена нова сесия.
  {
    if (absIndex >= MAX_VERSES)  absIndex = 0;

    // Ако трябва да се покаже Второканонична книга, а Второканоничните книги са скрити (показва най-близката предходна книга):
    if (!MO->SVars.showDeuterocanonical)
    {
      quint16 absIndexH = absIndex;
      quint8 cBook = MO->toBookCode(absIndex);
      quint8 cChapter = MO->toChapterCode(absIndex);
      if (cBook >= 40 && cBook <= 50)
      {
        absIndex = MO->toAbsIndex(39, 1, 1);
      }
      if (cBook == 19 && cChapter == 151)
      {
        absIndex = MO->toAbsIndex(19, 150, 1);
      }
      if (cBook == 27 && (cChapter == 13 || cChapter == 14))
      {
        absIndex = MO->toAbsIndex(27, 12, 1);
      }
      
	  if (absIndexH != absIndex)
      {
        QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->DisabledDeuterocanonicalInfo_v1);
      }
    }

    // Новият раздел няма да има история:
    newDock.textView->backForwardList.clear();
    newDock.textView->backForwardList << absIndex;
    newDock.textView->backForwardCurrentIndex = 0;

    // Възстановява отворените текстове от тази сесия:
    newDock.textView->activeBibleTexts = activeBibleTexts;
    newDock.textView->activeBibleTextsCount = activeBibleTextsCount;

    // Унаследява шрифра на текущия изглед и възстановява зуум-а от тази сесия:
    QFont font;
    //font.setFamily(MO->SVars.fontFamily); // Това не трябва да се разкоментира, защото всеки текст използва собствен шрифт.
    font.setPointSize(MO->SVars.fontSize);
    newDock.textView->setFont(font);
    newDock.textView->textZoom = textZoom;
    newDock.textView->zoomIn(textZoom);

    // Показва текста:
    newDock.textView->tempSearchWordsList.clear();
    newDock.textView->tempCaseSensitivitySearch = Qt::CaseInsensitive;

    // Определя къде ще се покаже разделът (по-точно проверява дали може да се покаже на желаното място):
    if (posYInDock >= mDockMain->getRowCount() || posXInDock >= mDockMain->getDockWidgetCount(posYInDock)) // Ако поради някаква грешка в прочитането от INI файла са зададени несъществуващи координати.
    {
      posXInDock = 0; // Ще го покаже на позиция 0, 0, която съществува със сигурност.
      posYInDock = 0;
    }

    newDock.textView->showBibleText(absIndex); // Работи с новия код.

    // Добавя и показва новия раздел.
    HDocks.append(newDock); // Този ред трябва да е преди показването и даването на фокус на новия изглед.
    mDockMain->addDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    currentTextViewChanged(newDock.textView); // Прави новия изглед на текущ. Това е задължително за правилната работа на логиката на програмата, а и е някак логично, че трябва да стане текущ.
  }
  else if (absIndex == MAX_VERSES) // Ако е натиснат "Нов раздел".
  {
    // Унаследява историята на текущия изглед:
    newDock.textView->backForwardList = currentHolyTextView->backForwardList;
    newDock.textView->backForwardCurrentIndex = currentHolyTextView->backForwardCurrentIndex;

    // Унаследява отворените текстове на текущия изглед:
    newDock.textView->activeBibleTexts = currentHolyTextView->activeBibleTexts;
    newDock.textView->activeBibleTextsCount = currentHolyTextView->activeBibleTextsCount;

    // Унаследява шрифра и зуум-а на текущия изглед:
    newDock.textView->setFont(currentHolyTextView->font());
    newDock.textView->textZoom = currentHolyTextView->textZoom;

    // Показва текста:
    newDock.textView->tempSearchWordsList.clear();
    newDock.textView->tempCaseSensitivitySearch = Qt::CaseInsensitive;
	
    // Определя къде ще се покаже разделът:
    bool asTab;
    bool leftToRightDirection = MO->TS->globalLayoutDirection == Qt::LeftToRight;
    if ((posXInDock < 0 && posYInDock < 0) || ctrlKeyPressed) // Ако е натиснат бутона за нов раздел от TMenu или ако е натиснат бутонът за нов раздел от друг раздел, но в комбинация с клавиш Ctrl.
    {
      if (mDockMain->getRowCount() > 1 || (mDockMain->width() > 3*mDockMain->height())) // Ако има повече от един ред или ако прозорецът е много дълъг, показва новия раздел до текущия.
      {
        if (leftToRightDirection)
        {
          posXInDock = currentHolyTextView->dockWidget->getPosXInDock()+1; // Вдясно от текущия.
          posYInDock = currentHolyTextView->dockWidget->getPosYInDock();
        }
        else
        {
          posXInDock = currentHolyTextView->dockWidget->getPosXInDock(); // Вляво от текущия.
          posYInDock = currentHolyTextView->dockWidget->getPosYInDock();
        }
      }
      else // Ако има само един ред, показва новия раздел над текущия.
      {
        posXInDock = -1; // Над текущия.
        posYInDock = -1;
      }
      asTab = false;
    }
    else // Ако е натиснат бутона за нов раздел от друг раздел.
    {
      // posXInDock и posYInDock остават непроменени за да може новият раздел да се отвори като таб в същия раздел.
      asTab = true;
    }

    if (currentHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в нормално четене.
    {
      newDock.textView->showBibleText(currentHolyTextView->currentAbsIndex); // Работи с текущите кодове на изгледа, който е активен.
    }
    else // Ако е в ежедневно четене.
    {
      newDock.textView->showBibleText(currentDR_AbsIndex);
    }

    // Добавя и показва новия раздел.
    HDocks.append(newDock); // Този ред трябва да е преди показването и даването на фокус на новия изглед.
    if (asTab)
      mDockMain->addDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    else
      mDockMain->insertDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    currentTextViewChanged(newDock.textView); // Прави новия изглед на текущ. Това е задължително за правилната работа на логиката на програмата, а и е някак логично, че трябва да стане текущ.
  }
  else // Ако е натиснат Ctrl+клик върху открития стих или Ctrl+клик върху книга или отметка.
  {
    if (absIndex >= MAX_VERSES)  absIndex = 0; // Това за всеки случай.

    // Унаследява историята на текущия изглед:
    newDock.textView->backForwardList = currentHolyTextView->backForwardList;
    newDock.textView->backForwardCurrentIndex = currentHolyTextView->backForwardCurrentIndex;

    // Унаследява историята на текущия изглед плюс текста, в който е търсено (ако не е показан, ще го покаже и него):
    newDock.textView->activeBibleTexts = currentHolyTextView->activeBibleTexts;
    newDock.textView->activeBibleTextsCount = currentHolyTextView->activeBibleTextsCount;
    if (activeBibleTextsCount == 255 && !newDock.textView->activeBibleTexts[mDockSearch->currentSearchWidget->searchTargetTextIndex]) // Ако текстът, в който е търсено не е показан. Тук activeBibleTextsCount се използва като флаг - ако е 255 значи този метод е извикан при кликване върху открития стих; ако е 0 значи е извикан от препратките или отметките.
    {
      newDock.textView->activeBibleTexts[mDockSearch->currentSearchWidget->searchTargetTextIndex] = true; // Показва текста, в който е търсено.
      newDock.textView->activeBibleTextsCount++;
    }

    // Унаследява шрифра и зуум-а на текущия изглед:
    newDock.textView->setFont(currentHolyTextView->font());
    newDock.textView->textZoom = currentHolyTextView->textZoom;

    // Показва текста:
    newDock.textView->tempSearchWordsList = mDockSearch->currentSearchWidget->searchWordsList; // tempSearchWordsList съдържа търсените думи които ще бъдат оцветени веднага след показване на главата, съдържаща търсения стих. Те ще останат оцветени и при прибавяне на нов текст (точно това е идеята), но при показване на друга глава няма да се оцветят повече.
    newDock.textView->tempCaseSensitivitySearch = mDockSearch->currentSearchWidget->caseSensitivitySearch; // tempCaseSensitivitySearch съдържа CaseSensitivity режима на търсените думи, които ще бъдат оцветени веднага след показване на главата съдържаща търсения стих. Те ще останат оцветени и при прибавяне на нов текст (точно това е идеята), но при показване на друга глава няма да се оцветят повече.
	
    // Определя къде ще се покаже разделът:
    posXInDock = currentHolyTextView->dockWidget->getPosXInDock()+1;
    posYInDock = currentHolyTextView->dockWidget->getPosYInDock();

    newDock.textView->showBibleText(absIndex); // Работи със зададения код.

    // Добавя и показва новия раздел.
    HDocks.append(newDock); // Този ред трябва да е преди показването и даването на фокус на новия изглед.
    mDockMain->insertDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    currentTextViewChanged(newDock.textView); // Прави новия изглед на текущ. Това е задължително за правилната работа на логиката на програмата, а и е някак логично, че трябва да стане текущ.
  }

  newDock.textView->setFocus();
}

void MainWindow::slotNavigation_BooksToolBar()
{
  mDockBooks->setVisible(!mDockBooks->isVisible());
}

void MainWindow::slotNavigation_BookmarksToolBar()
{
  mDockBookmarks->setVisible(!mDockBookmarks->isVisible());
}

void MainWindow::slotNavigation_GoBack()
{
  if (currentHolyTextView->backForwardCurrentIndex > 0)
  {
    currentHolyTextView->backForwardList[currentHolyTextView->backForwardCurrentIndex] = currentHolyTextView->currentAbsIndex; // Запомня стария, последно маркиран стих.
    currentHolyTextView->backForwardCurrentIndex--;
    currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    currentHolyTextView->showBibleText(currentHolyTextView->backForwardList[currentHolyTextView->backForwardCurrentIndex]);

    //if (currentHolyTextView->backForwardCurrentIndex == 0) mainToolBar->btnNavigation_GoBack->setEnabled(false);
    //mainToolBar->btnNavigation_GoForward->setEnabled(true);
  }
}

void MainWindow::slotNavigation_GoForward()
{
  if (currentHolyTextView->backForwardCurrentIndex < (currentHolyTextView->backForwardList.count() - 1))
  {
    currentHolyTextView->backForwardList[currentHolyTextView->backForwardCurrentIndex] = currentHolyTextView->currentAbsIndex; // Запомня стария, последно маркиран стих.
    currentHolyTextView->backForwardCurrentIndex++;
    currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    currentHolyTextView->showBibleText(currentHolyTextView->backForwardList[currentHolyTextView->backForwardCurrentIndex]);

    //mainToolBar->btnNavigation_GoBack->setEnabled(true);
    //if (currentHolyTextView->backForwardCurrentIndex == (currentHolyTextView->backForwardList.count() - 1)) mainToolBar->btnNavigation_GoForward->setEnabled(false);
  }
}

void MainWindow::slotNavigation_PreviousBook()
{
  currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
  quint16 newAbsIndex = currentHolyTextView->currentAbsIndex;
  MO->getPrevBook(&newAbsIndex); // Взима новата стойност за текуща книга.
  currentHolyTextView->showBibleText(newAbsIndex);
}

void MainWindow::slotNavigation_NextBook()
{
  currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
  quint16 newAbsIndex = currentHolyTextView->currentAbsIndex;
  MO->getNextBook(&newAbsIndex); // Взима новата стойност за текуща книга.
  currentHolyTextView->showBibleText(newAbsIndex);
}

void MainWindow::slotNavigation_PreviousChapter()
{
  currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
  quint16 newAbsIndex = currentHolyTextView->currentAbsIndex;
  MO->getPrevChapter(&newAbsIndex); // Взима новата стойност за текуща глава.
  currentHolyTextView->showBibleText(newAbsIndex);
}

void MainWindow::slotNavigation_NextChapter()
{
  currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
  quint16 newAbsIndex = currentHolyTextView->currentAbsIndex;
  MO->getNextChapter(&newAbsIndex); // Взима новата стойност за текуща глава.
  currentHolyTextView->showBibleText(newAbsIndex);
}

void MainWindow::slotNavigation_PreviousVerse()
{
  if (currentHolyTextView->textMode == TEXT_MODE__SHOW || currentHolyTextView->textMode == TEXT_MODE__COMPARE)
  {
    currentHolyTextView->textCursorBeginEditBlock();
    currentHolyTextView->selectRow(-1, true, true); // Селектира предходния стих и деселектира останалите.
    currentHolyTextView->textCursorEndEditBlock();
  }
}

void MainWindow::slotNavigation_NextVerse()
{
  if (currentHolyTextView->textMode == TEXT_MODE__SHOW || currentHolyTextView->textMode == TEXT_MODE__COMPARE)
  {
    currentHolyTextView->textCursorBeginEditBlock();
    currentHolyTextView->selectRow(1, true, true); // Селектира следващия стих и деселектира останалите.
    currentHolyTextView->textCursorEndEditBlock();
  }
}

void MainWindow::slotNavigation_PreviousChaptersDailyRead()
{
  currentDR_Day--;
  if (currentDR_Day == 0) currentDR_Day = DAILY_READ_TOTAL_DAYS;

  mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(true);
  mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);

  MO->getDailyReadGroup(currentDR_Day, currentDR_DailyGroup);
  currentDR_ChapterInDailyGroup = currentDR_DailyGroup.size();
  currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
  mainToolBar->dailyReadGrLabel->setText(QString(" %1/%2 ").arg(currentDR_Day).arg(DAILY_READ_TOTAL_DAYS));
  mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()));

  if (!MO->SVars.showDeuterocanonical) dailyReadPanel_HideDeuterocanonical(); // Ако Второканоничните книги са скрити ги скрива и от панела за ежедневно четене.

  currentHolyTextView->showBibleText(currentDR_AbsIndex);
}

void MainWindow::slotNavigation_NextChaptersDailyRead()
{
  currentDR_Day++;
  if (currentDR_Day == (DAILY_READ_TOTAL_DAYS + 1)) currentDR_Day = 1;

  mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(false);
  mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(true);

  MO->getDailyReadGroup(currentDR_Day, currentDR_DailyGroup);
  currentDR_ChapterInDailyGroup = 1;
  currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
  mainToolBar->dailyReadGrLabel->setText(QString(" %1/%2 ").arg(currentDR_Day).arg(DAILY_READ_TOTAL_DAYS));
  mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()));

  if (!MO->SVars.showDeuterocanonical) dailyReadPanel_HideDeuterocanonical(); // Ако Второканоничните книги са скрити ги скрива и от панела за ежедневно четене.

  currentHolyTextView->showBibleText(currentDR_AbsIndex);
}

void MainWindow::slotNavigation_PreviousChapterDailyRead()
{
  currentDR_ChapterInDailyGroup--;

  if (currentDR_ChapterInDailyGroup == 1) mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(false);
  mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(true);

  currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
  mainToolBar->dailyReadGrLabel->setText(QString(" %1/%2 ").arg(currentDR_Day).arg(DAILY_READ_TOTAL_DAYS));
  mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()));

  if (!MO->SVars.showDeuterocanonical) dailyReadPanel_HideDeuterocanonical(); // Ако Второканоничните книги са скрити ги скрива и от панела за ежедневно четене.

  currentHolyTextView->showBibleText(currentDR_AbsIndex);
}

void MainWindow::slotNavigation_NextChapterDailyRead()
{
  currentDR_ChapterInDailyGroup++;

  mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(true);
  if (currentDR_ChapterInDailyGroup == currentDR_DailyGroup.size()) mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);

  currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
  mainToolBar->dailyReadGrLabel->setText(QString(" %1/%2 ").arg(currentDR_Day).arg(DAILY_READ_TOTAL_DAYS));
  mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()));

  if (!MO->SVars.showDeuterocanonical) dailyReadPanel_HideDeuterocanonical(); // Ако Второканоничните книги са скрити ги скрива и от панела за ежедневно четене.

  currentHolyTextView->showBibleText(currentDR_AbsIndex);
}

void MainWindow::slotNavigation_DailyReadToolBar()
{
  if ( mainToolBar->btnNavigation_DailyRead->isChecked() )
  {
    currentHolyTextView->readMode = READ_MODE__DAILY_READ;
    mainToolBar->showDailyReadPanel(true);

    audioToolBar->enableButtonPlayGroup(true);

    MO->getDailyReadGroup(currentDR_Day, currentDR_DailyGroup);
    mainToolBar->btnNavigation_PreviousChapterDailyRead->setEnabled(currentDR_ChapterInDailyGroup > 1);
    mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(currentDR_ChapterInDailyGroup < currentDR_DailyGroup.size());
    mainToolBar->dailyReadGrLabel->setText(QString(" %1/%2 ").arg(currentDR_Day).arg(DAILY_READ_TOTAL_DAYS));
    mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()));

    if (!MO->SVars.showDeuterocanonical) dailyReadPanel_HideDeuterocanonical(); // Ако Второканоничните книги са скрити ги скрива и от панела за ежедневно четене.

    currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    currentHolyTextView->showBibleText(currentDR_AbsIndex);
  }
  else
  {
    currentHolyTextView->readMode = READ_MODE__NORMAL;
    mainToolBar->showDailyReadPanel(false);

    audioToolBar->enableButtonPlayGroup(false);

    currentHolyTextView->showBibleText(currentHolyTextView->currentAbsIndex);
  }
}

void MainWindow::dailyReadPanel_HideDeuterocanonical()
{
  // В разпределението за ежедневно четене, Второканоничните книги и глави са прибавени към следните групи и трябва да се извадят:
  // В група: 135 -- Псалом 151                                                                                                                                (общо  1 глава)
  // В група: 193 -- Даниил 13 и 14                                                                                                                            (общо  2 глави)
  // В група: 208 -- 2 Ездра, Товита, Иудит Премъдрост Соломонова, Исус Сирахов Послание на Еремия, Варуха 1 Макавей, 2 Макавей, 3 Макавей, 3 Ездра, 3 Макавей (общо 188 глави)
  if (currentDR_Day == 135)
  {
    if (currentDR_ChapterInDailyGroup >= 8)
    {
      currentDR_ChapterInDailyGroup = 8;
      currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
      mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);
    }
    mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()-1));
  }
  else if (currentDR_Day == 193)
  {
    if (currentDR_ChapterInDailyGroup >= 4)
    {
      currentDR_ChapterInDailyGroup = 4;
      currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
      mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);
    }
    mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()-2));
  }
  else if (currentDR_Day == 208)
  {
    if (currentDR_ChapterInDailyGroup >= 4)
    {
      currentDR_ChapterInDailyGroup = 4;
      currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1];
      mainToolBar->btnNavigation_NextChapterDailyRead->setEnabled(false);
    }
    mainToolBar->dailyReadChLabel->setText(QString(" %1/%2 ").arg(currentDR_ChapterInDailyGroup).arg(currentDR_DailyGroup.size()-188));
  }
}

/// TextToolBar
void MainWindow::slotText_SearchCenter()
{
  showSearchCenter( !mDockSearch->isVisible() ); // Ако е показан го скрива, ако не е показан го показва.
}

void MainWindow::slotText_BibleTextsToolBar()
{
  tMenu->setBibleTextsToolBarVisible( mainToolBar->btnText_BibleTexts->isChecked() );
}

void MainWindow::slotText_AudioToolBar()
{
  if ( mainToolBar->btnText_Audio->isChecked() ) // Ако бутонът е натиснат (включен).
  {
    if (currentHolyTextView != 0) audioToolBar->enableButtonPlayGroup(currentHolyTextView->readMode == READ_MODE__DAILY_READ);
    tMenu->setAudioToolBarVisible(true);
  }
  else
  {
    tMenu->setAudioToolBarVisible(false);
  }
}

void MainWindow::slotText_PlayCurrentChapter()
{
  if ( !mainToolBar->btnText_Audio->isChecked() ) mainToolBar->btnText_Audio->click(); // Показва (и създава) панела ако не е показан (създаден).
  //audioToolBar->slotPlayCurrentChapterNow(); // Това крашва програмата, затова използвам долния сигнал, който изпълнява същия този слот.
  emit playCurrentChapterNow();
}

void MainWindow::slotText_ZoomIn()
{
  if (currentTextView == mDockSearch->currentSearchWidget->searchView) // Ако изгледа за резултатите от търсенето е на фокус.
  {
    if (mDockSearch->currentSearchWidget->searchView->hasFocus()) mDockSearch->slotZoomIn_AllSearchView(); // За този изглед се изисква да бъде буквално на фокус, за да се променя размера на шрифта му.
  }
  else if (currentTextView != 0) // Текущият изглед.
  {
    currentTextView->textZoom++;
    currentTextView->zoomIn(1);
  }
}

void MainWindow::slotText_ZoomOut()
{
  if (currentTextView == mDockSearch->currentSearchWidget->searchView) // Ако изгледа за резултатите от търсенето е на фокус.
  {
    if (mDockSearch->currentSearchWidget->searchView->hasFocus()) mDockSearch->slotZoomOut_AllSearchView(); // За този изглед се изисква да бъде буквално на фокус, за да се променя размера на шрифта му.
  }
  else if (currentTextView != 0) // Текущият изглед.
  {
    currentTextView->textZoom--;
    currentTextView->zoomOut(1);
  }
}

void MainWindow::slotText_ZoomNormal()
{
  if (currentTextView == mDockSearch->currentSearchWidget->searchView) // Ако изгледа за резултатите от търсенето е на фокус.
  {
    if (mDockSearch->currentSearchWidget->searchView->hasFocus()) mDockSearch->slotZoomNormal_AllSearchView(); // За този изглед се изисква да бъде буквално на фокус, за да се променя размера на шрифта му.
  }
  else if (currentTextView != 0) // Текущият изглед.
  {
    //if (currentTextView->textZoom > 0)
    //  currentTextView->zoomOut(currentTextView->textZoom);
    //else if (currentTextView->textZoom < 0)
    //  currentTextView->zoomIn(-currentTextView->textZoom);
    currentTextView->zoomOut(currentTextView->textZoom); // Този ред е еквивалентен на закоментираните.
    currentTextView->textZoom = 0;
  }
}

void MainWindow::slotText_Statistics()
{
  QMenu *statisticsMenu = new QMenu(MO->TS->StatisticsMenu_v1);
  statisticsMenu->addAction(compareTwoTextsAction);
  statisticsMenu->addSeparator();
  statisticsMenu->addAction(uniqueWordsInBibleAct);
  statisticsMenu->addAction(uniqueWordsInOTAct);
  statisticsMenu->addAction(uniqueWordsInNTAct);
  statisticsMenu->addAction(uniqueWordsInBookAct);
  statisticsMenu->addAction(uniqueWordsInChapterAct);
  if (MO->SVars.TMenuPosition == POSITION_TOP)
    statisticsMenu->exec(QPoint(QCursor::pos().x() - mainToolBar->btnsHeightSize, geometry().y() + mainToolBar->btnsHeightSize));
  else
    statisticsMenu->exec(QPoint(QCursor::pos().x() - mainToolBar->btnsHeightSize, geometry().y() + geometry().height())); //statisticsMenu->exec(QCursor::pos());
  delete statisticsMenu;
}

void MainWindow::slotText_CompareTwoTexts()
{
  if (currentHolyTextView->textMode == TEXT_MODE__COMPARE) // Ако е в режим на сравняване.
    slotShow(); // Връща в нормален режим.
  else // Ако е в нормален режим.
    currentHolyTextView->compareText(); // Минава в режим на сравняване.
}

void MainWindow::slotText_UniqueWordsInBible()
{
  // Кодът в този слот е идентичен с останалите UniqueWordsIn... слотове. Всяка промяна да се отрази и на другите места.
  if (currentHolyTextView->activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  QMessageBox messageBox(this);
  QPushButton *occurrenceButton = messageBox.addButton(MO->TS->SortByOccurrenceOrder_v1, QMessageBox::AcceptRole);     // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
  QPushButton *alphabeticalButton = messageBox.addButton(MO->TS->SortByAlphabeticalOrder_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
  messageBox.setDefaultButton(occurrenceButton);
  messageBox.exec();
  bool alphabeticallyOrder = (messageBox.clickedButton() == alphabeticalButton);

  QString text = MO->getUniqueWords(&currentHolyTextView->activeBibleTexts, currentHolyTextView->currentAbsIndex, true, true, false, false, alphabeticallyOrder); // Само в този ред е разликата с останалите слотове.
    
  ExTextWindow *pad = new ExTextWindow(this, 400, 512, false); // Ако резултатът се показва като текст, широчината на прозореца може да е 400, а ако е като таблица - 600.
  pad->setWindowTitle(MO->TS->UniqueWordsInBible_v1 + " - " + QCoreApplication::applicationName());
  //pad->setEditorFont(font);
  pad->setHtmlText(text);
  pad->show();
}

void MainWindow::slotText_UniqueWordsInOT()
{
  // Кодът в този слот е идентичен с останалите UniqueWordsIn... слотове. Всяка промяна да се отрази и на другите места.
  if (currentHolyTextView->activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  QMessageBox messageBox(this);
  QPushButton *occurrenceButton = messageBox.addButton(MO->TS->SortByOccurrenceOrder_v1, QMessageBox::AcceptRole);     // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
  QPushButton *alphabeticalButton = messageBox.addButton(MO->TS->SortByAlphabeticalOrder_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
  messageBox.setDefaultButton(occurrenceButton);
  messageBox.exec();
  bool alphabeticallyOrder = (messageBox.clickedButton() == alphabeticalButton);

  QString text = MO->getUniqueWords(&currentHolyTextView->activeBibleTexts, currentHolyTextView->currentAbsIndex, true, false, false, false, alphabeticallyOrder); // Само в този ред е разликата с останалите слотове.
    
  ExTextWindow *pad = new ExTextWindow(this, 400, 512, false); // Ако резултатът се показва като текст, широчината на прозореца може да е 400, а ако е като таблица - 600.
  pad->setWindowTitle(MO->TS->UniqueWordsInBible_v1 + " - " + QCoreApplication::applicationName());
  //pad->setEditorFont(font);
  pad->setHtmlText(text);
  pad->show();
}

void MainWindow::slotText_UniqueWordsInNT()
{
  // Кодът в този слот е идентичен с останалите UniqueWordsIn... слотове. Всяка промяна да се отрази и на другите места.
  if (currentHolyTextView->activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  QMessageBox messageBox(this);
  QPushButton *occurrenceButton = messageBox.addButton(MO->TS->SortByOccurrenceOrder_v1, QMessageBox::AcceptRole);     // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
  QPushButton *alphabeticalButton = messageBox.addButton(MO->TS->SortByAlphabeticalOrder_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
  messageBox.setDefaultButton(occurrenceButton);
  messageBox.exec();
  bool alphabeticallyOrder = (messageBox.clickedButton() == alphabeticalButton);

  QString text = MO->getUniqueWords(&currentHolyTextView->activeBibleTexts, currentHolyTextView->currentAbsIndex, false, true, false, false, alphabeticallyOrder); // Само в този ред е разликата с останалите слотове.
    
  ExTextWindow *pad = new ExTextWindow(this, 400, 512, false); // Ако резултатът се показва като текст, широчината на прозореца може да е 400, а ако е като таблица - 600.
  pad->setWindowTitle(MO->TS->UniqueWordsInBible_v1 + " - " + QCoreApplication::applicationName());
  //pad->setEditorFont(font);
  pad->setHtmlText(text);
  pad->show();
}

void MainWindow::slotText_UniqueWordsInBook()
{
  // Кодът в този слот е идентичен с останалите UniqueWordsIn... слотове. Всяка промяна да се отрази и на другите места.
  if (currentHolyTextView->activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  QMessageBox messageBox(this);
  QPushButton *occurrenceButton = messageBox.addButton(MO->TS->SortByOccurrenceOrder_v1, QMessageBox::AcceptRole);     // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
  QPushButton *alphabeticalButton = messageBox.addButton(MO->TS->SortByAlphabeticalOrder_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
  messageBox.setDefaultButton(occurrenceButton);
  messageBox.exec();
  bool alphabeticallyOrder = (messageBox.clickedButton() == alphabeticalButton);

  QString text = MO->getUniqueWords(&currentHolyTextView->activeBibleTexts, currentHolyTextView->currentAbsIndex, false, false, true, false, alphabeticallyOrder); // Само в този ред е разликата с останалите слотове.
    
  ExTextWindow *pad = new ExTextWindow(this, 400, 512, false); // Ако резултатът се показва като текст, широчината на прозореца може да е 400, а ако е като таблица - 600.
  pad->setWindowTitle(MO->TS->UniqueWordsInBible_v1 + " - " + QCoreApplication::applicationName());
  //pad->setEditorFont(font);
  pad->setHtmlText(text);
  pad->show();
}

void MainWindow::slotText_UniqueWordsInChapter()
{
  // Кодът в този слот е идентичен с останалите UniqueWordsIn... слотове. Всяка промяна да се отрази и на другите места.
  if (currentHolyTextView->activeBibleTextsCount != 1)
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->OneActiveBibleTextNeeded_v1);
    return;
  }

  QMessageBox messageBox(this);
  QPushButton *occurrenceButton = messageBox.addButton(MO->TS->SortByOccurrenceOrder_v1, QMessageBox::AcceptRole);     // И двете трябва да са AcceptRole. Така бутон X на диалога става неактивен
  QPushButton *alphabeticalButton = messageBox.addButton(MO->TS->SortByAlphabeticalOrder_v1, QMessageBox::AcceptRole); // и потребителят е принуден да натисне един от бутоните.
  messageBox.setDefaultButton(occurrenceButton);
  messageBox.exec();
  bool alphabeticallyOrder = (messageBox.clickedButton() == alphabeticalButton);

  QString text = MO->getUniqueWords(&currentHolyTextView->activeBibleTexts, currentHolyTextView->currentAbsIndex, false, false, false, true, alphabeticallyOrder); // Само в този ред е разликата с останалите слотове.
    
  ExTextWindow *pad = new ExTextWindow(this, 400, 512, false); // Ако резултатът се показва като текст, широчината на прозореца може да е 400, а ако е като таблица - 600.
  pad->setWindowTitle(MO->TS->UniqueWordsInBible_v1 + " - " + QCoreApplication::applicationName());
  //pad->setEditorFont(font);
  pad->setHtmlText(text);
  pad->show();
}

/// OtherToolBar
void MainWindow::slotOther_Pad()
{
  if (!padIsOpen) // Ако бележника не е отворен.
  {
    //if (pad != 0) delete pad;

    // По-добре е шрифтът и големината му да е като този на цялото приложение. Както на хелпа. Затова долните редове са коментирани.
    //QFont font;
    //font.setFamily(MO->SVars.fontFamily);
    //font.setPointSize(MO->SVars.fontSize);
    //font.setFixedPitch(false);

    pad = new ExTextWindow(this, 640, 512, true);
    pad->setWindowTitle(MO->TS->Pad_v1 + " - " + QCoreApplication::applicationName());
    //pad->setEditorFont(font);
    pad->openFile(QString("%1/Pad/Pad.txt").arg(MO->applicationHomePath), false);
    pad->show();
  }
  else // Ако е вече отворен.
  {
    if (pad->isMinimized()) pad->showNormal(); // Ако е минимизиран го показва.
    pad->raise(); // Прави го на преден план.
    pad->setFocus();
  }
}

void MainWindow::slotOther_Dictionary(MDock */*dock*/, MDockWidget *dockWidget)
{
  if (dockWidget == 0) // Ако е натиснат бутонът за нов раздел от TMenu.
    newDictionary(false, -1, -1); // Отваря новия раздел до текущия.
  else // Ако е натиснат бутонът за нов раздел от друг раздел.
    newDictionary(false, dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Отваря новия раздел в същия раздел, като таб.
}

void MainWindow::newDictionary(bool loadSession, int posXInDock, int posYInDock, int textZoom, int dictIndex, int currIndex, bool btnCState, bool btnAState)
{
  // При зареждане на сесията е създадена (възстановена) мрежата на разделите. Ако при това е станала някаква грешка,
  // по подразбиране се създава нова мрежа с един ред и един раздел. Този метод ще се опита да вмъкне новия раздел
  // където му е мястото, но ако се окаже, че няма такова място, го вмъква на позиция 0,0 (такава 100% ще има).
  // Така, ако има проблем с мрежата, всички раздели ще са на позиция 0,0.
  DOCKS newDock;

  newDock.dictionary = new Dictionary(this, this);
  newDock.textView = newDock.dictionary->mainTextView;

  newDock.dockWidget = new MDockWidget(mDockMain, QString("<b>%1</b>").arg(MO->TS->DictionaryCommentary_v1), true, true, MO->SVars.docks3DTitleBar, 0, DOCK_TYPE__DICTIONARY);
  newDock.dockWidget->setMinimumSize(1, 1);
  newDock.dockWidget->setWidget(newDock.dictionary);
  newDock.dockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само сигнал.
  newDock.dockWidget->setDockWidgetTitleBarFontSize(MO->SVars.otherToolBarFontSize);
  newDock.dockWidget->setDockWidgetBgColor(MO->SVars.appColorF);
  newDock.dockWidget->setDockWidgetTitleBarColor(MO->SVars.appColorF);
  newDock.dockWidget->setDockWidgetTitleBarTextColor(MO->SVars.appColorB);
  newDock.dockWidget->setDockWidgetTitleBarButtonColor(MO->SVars.appColorB);
  newDock.dockWidget->setNewBtnToolTip(MO->TS->NewDockWindow_v1);
  newDock.dockWidget->setMaximizeBtnToolTip(MO->TS->MaximizeNormalize_v1);
  newDock.dockWidget->setCloseBtnToolTip(MO->TS->CloseDockWindow_v1);
  connect(newDock.dockWidget, SIGNAL(dockWidgetNewButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotOther_Dictionary(MDock *, MDockWidget *))); // Излъчения от New бутона сигнал.
  connect(newDock.dockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotCloseDock(MDock *, MDockWidget *, int, quint8))); // Излъчения от Close бутона сигнал.
  connect(newDock.dockWidget, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotDockWidgetRaised(MDock *, MDockWidget *)));

  newDock.textView->dockWidget = newDock.dockWidget;
  newDock.textView->textMode = TEXT_MODE__OTHER;
  newDock.textView->setColorScheme();

  QFont font;
  //font.setFamily(MO->SVars.fontFamily); // Това не трябва да се разкоментира, защото всеки речник/коментар използва собствен шрифт.
  font.setPointSize(MO->SVars.fontSize);
  newDock.textView->setFont(font); // Унаследява шрифра на текущия изглед.
  if (loadSession) // Ако е заредена нова сесия.
  {
    // Възстановява зуум-а от тази сесия:
    newDock.textView->textZoom = textZoom;
    newDock.textView->zoomIn(textZoom);
    newDock.dictionary->dictCmbBox->setCurrentIndex(dictIndex);
    newDock.dictionary->catchCopyEventBtn->setChecked(btnCState);
    newDock.dictionary->catchSelectEventBtn->setChecked(btnAState);
    newDock.dictionary->showWord(currIndex);

    // Определя къде ще се покаже разделът (по-точно проверява дали може да се покаже на желаното място):
    if (posYInDock >= mDockMain->getRowCount() || posXInDock >= mDockMain->getDockWidgetCount(posYInDock)) // Ако поради някаква грешка в прочитането от INI файла са зададени несъществуващи координати.
    {
      posXInDock = 0; // Ще го покаже на позиция 0, 0, която съществува със сигурност.
      posYInDock = 0;
    }

    // Добавя и показва новия раздел.
    ODocks.append(newDock); // Този ред трябва да е преди показването и даването на фокус на новия изглед.
    mDockMain->addDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    newDock.dictionary->entryCmbBox->setFocus();
  }
  else // Ако е натиснат бутонът за нов речник/коментар.
  {
    // Нормализира зуум-а:
    newDock.textView->textZoom = 0;
    newDock.textView->zoomIn(0);

    // Определя къде ще се покаже разделът:
    bool asTab;
    bool leftToRightDirection = MO->TS->globalLayoutDirection == Qt::LeftToRight;
    if ((posXInDock < 0 && posYInDock < 0) || ctrlKeyPressed) // Ако е натиснат бутонът за нов раздел от TMenu или ако е натиснат бутонът за нов раздел от друг раздел, но в комбинация с клавиш Ctrl.
    {
      if (mDockMain->getRowCount() > 1 || (mDockMain->width() > 3*mDockMain->height())) // Ако има повече от един ред или ако прозорецът е много дълъг, показва новия раздел до текущия.
      {
        if (leftToRightDirection)
        {
          posXInDock = currentHolyTextView->dockWidget->getPosXInDock()+1; // Вдясно от текущия.
          posYInDock = currentHolyTextView->dockWidget->getPosYInDock();
        }
        else
        {
          posXInDock = currentHolyTextView->dockWidget->getPosXInDock(); // Вляво от текущия.
          posYInDock = currentHolyTextView->dockWidget->getPosYInDock();
        }
      }
      else // Ако има само един ред, показва новия раздел под текущия.
      {
        posXInDock = -1; // Под текущия.
        posYInDock = currentHolyTextView->dockWidget->getPosYInDock()+1;
      }
      asTab = false;
    }
    else // Ако е натиснат бутонът за нов раздел от друг раздел.
    {
      // posXInDock и posYInDock остават непроменени, за да може новият раздел да се отвори като таб в същия раздел.
      asTab = true;
    }

    // Добавя и показва новия раздел.
    ODocks.append(newDock); // Този ред трябва да е преди показването и даването на фокус на новия изглед.
    if (asTab)
      mDockMain->addDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    else
      mDockMain->insertDockWidget(newDock.dockWidget, posXInDock, posYInDock); // Добавя и показва новия раздел.
    newDock.dictionary->entryCmbBox->setFocus();
  }
}

void MainWindow::slotOther_ExternalImages()
{
  ExImageWindow *exImageWindow = new ExImageWindow(MO->iniFile, 0);
  exImageWindow->setWindowTitle(MO->TS->ExternalImages_v1 + " - " + QCoreApplication::applicationName());
  exImageWindow->show();
}

void MainWindow::slotOther_ProjectorToolBar()
{
  if ( !mDockProjector->isVisible() )
  {
    projectorWidget->initProjectorToolBar(); // Този метод се извиква при всяко показване на тулбара на проектора, но реално ще се изпълни само веднъж - първия път.
    mDockProjector->setVisible(true);
  }
  else
  {
    mDockProjector->setVisible(false);
  }
}

void MainWindow::slotOther_Links()
{
  if (!WWWResIsOpen) // Ако WWWRes не е отворен.
  {
    //if (WWWRes != 0) delete WWWRes;

    WWWRes = new WWWResources(this);
    WWWRes->setWindowTitle(MO->TS->Links_v1 + " - " + QCoreApplication::applicationName());
    WWWRes->show();
  }
  else // Ако е вече отворен.
  {
    if (WWWRes->isMinimized()) WWWRes->showNormal(); // Ако е минимизиран го показва.
    WWWRes->raise(); // Прави го на преден план.
    WWWRes->setFocus();
  }
}

void MainWindow::slotOther_Settings()
{
  SettingsDialog settingsDialog(this);
  settingsDialog.exec();
  MO->saveSVarsSettings();

  if (needToRestart)
  {
    slotRestart(true);
    //needToRestart = false; // Това да не се разкоментира, за да напомня всеки път след затваряне на формата, че има нужда от рестарт.
  }
}

/// FileToolBar
void MainWindow::slotFile_Exit()
{
  MO->enableExitAction = true; // For TrayIcon.
  //qApp->closeAllWindows(); // Това не може да затвори минимизираните в трей-а прозорци.
  //QApplication::setQuitOnLastWindowClosed(true); // If this property is true, the applications quits when the last visible primary window (i.e. window with no parent) with the Qt::WA_QuitOnClose attribute set is closed // For TrayIcon.
  close(); // Само това извиква closeEvent-а и съответно saveSessionSettings() при което се запомнят текущите настройки.
  //QApplication::quit(); // Същото като qApp->quit(); // Това не трябва да се използва, защото не извиква closeEvent-а!
}

void MainWindow::slotFile_SessionToolBar()
{
  tMenu->setSessionToolBarVisible( mainToolBar->btnFile_Session->isChecked() );
}

void MainWindow::slotLoadSession()
{
  quint8 newCurrentSession = 0;
  for (quint8 s = 0; s < 9; s++)
  {
    if (sessionBtn[s]->isChecked()) // Определя се коя е новата избрана сесия.
    {
      newCurrentSession = s;
      break;
    }
  }
  if (newCurrentSession == currentSession) // Ако е натиснат същият бутон. Вместо този if мога да го направя с setEnable, но когато бутонът на текущата сесия е неактивен стои много грозно и не се разбира, че това е текущата сесия.
  {
    sessionBtn[currentSession]->setChecked(true);
    return;
  }

  // Затваря панела със сесиите:
  mainToolBar->btnFile_Session->click();
    
  // Спира аудиото, ако е пуснато. Това е важно, за да се отблокира раздела, за да може да се затвори:
  audioToolBar->slotForceStop(); // Спира аудиото (без значение дали е пуснато или не) и освобождава раздела, за да може да се затвори.

  // Изключва ежедневното четене:
  if (mainToolBar->btnNavigation_DailyRead->isChecked()) mainToolBar->btnNavigation_DailyRead->click();  // Ако ежедневното четене е отворено трябва да се затвори.

  saveSessionSettings(currentSession); // Запомня текущата сесия (вътре в този метод се прави проверка дали трябва да се запомни тази сесия).

  // Превключва сесиите (по един от двата начина):  
  //exeName = QCoreApplication::applicationFilePath();
  //if (QFile::exists(exeName))
  //{
  //  // Този начин на превключване на сесиите е много дървен, но работи добре.
  //
  //  // Затваря бележника. Идеята е ако текста в него не е записан да се запише преди да е пусната програмата отново.
  //  if (padIsOpen) 
  //  {
  //    pad->close();
  //    delete pad;
  //    pad = 0;
  //  }
  //  
  //  // Затваря WWWRes.
  //  if (WWWResIsOpen) 
  //  {
  //    WWWRes->close();
  //    delete WWWRes;
  //    WWWRes = 0;
  //  }
  //
  //  startSession = newCurrentSession; // Това е сесията, която ще се отвори при повторното пускане на програмата в closeEvent метода.
  //  slotFile_Exit(); // Затваря програмата като преди това записва настройките на сесията и стартира програма отново.
  //}
  //else // Ако поради някаква причина не може да върне изпълнимия файл, използва стандартния начин за превключване на сесии:
  //{
    // Този начин на превключване на сесиите е по-добър като идея, защото не затваря програмата и после пак да я отваря, а направо затваря
    // всички раздели и отваря новите според както са записани в новоизбраната сесия. Също така не затваря бележника и ресурсите.

    // Първо затваря всички ODocks раздели:
    int len = ODocks.length();
    for (int index = (len-1); index >= 0; index--)
    {
      ODocks[index].dockWidget->setDockWidgetDisallowCloseLevel1(false); // Премахва евентуалната забрана за затваряне на този раздел.
      ODocks[index].dockWidget->setDockWidgetDisallowCloseLevel2(false); //
      slotCloseDock(mDockMain, ODocks[index].dockWidget, ODocks[index].dockWidget->getDockWidgetID(), ODocks[index].dockWidget->getDockWidgetType());
    }
    // После затваря всички HDocks раздели, но без първия:
    len = HDocks.length();
    for (int index = (len-1); index > 0; index--) // Първият раздел (на индекс 0) не трябва да се затваря, защото не се знае къде ще изгърми програмата (така се спестяват един куп проверки). Ще се затвори по-долу.
    {
      HDocks[index].dockWidget->setDockWidgetDisallowCloseLevel1(false); // Премахва евентуалната забрана за затваряне на този раздел.
      HDocks[index].dockWidget->setDockWidgetDisallowCloseLevel2(false); //
      slotCloseDock(mDockMain, HDocks[index].dockWidget, HDocks[index].dockWidget->getDockWidgetID(), HDocks[index].dockWidget->getDockWidgetType());
    }

    // Зарежда новоизбраната сесия:
    currentSession = newCurrentSession;
    loadSessionSettings(newCurrentSession);

    // Сега трябва да затвори незатворения раздел от предната сесия. Той е на индекс 0:
    // Затварянето ще е безопасно, защото със сигурност има поне един нов раздел от новозаредената сесия:
    HDocks[0].dockWidget->setDockWidgetDisallowCloseLevel1(false); // Премахва евентуалната забрана за затваряне на този раздел.
    HDocks[0].dockWidget->setDockWidgetDisallowCloseLevel2(false); //
    slotCloseDock(mDockMain, HDocks[0].dockWidget, HDocks[0].dockWidget->getDockWidgetID(), HDocks[0].dockWidget->getDockWidgetType());

    if (mainToolBar->btnNavigation_New->hasFocus()) mainToolBar->btnNavigation_New->clearFocus(); // Това е защото първият бутон става на фокус.
  //}
}

void MainWindow::slotRestart(bool question)
{
  // Този слод е подобен на горния (има общи неща).

  if (question)
  {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, QCoreApplication::applicationName(),
                               MO->TS->RestartNowQuestion_v1,
                               QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::No) return;
  }

  // Затваря панела със сесиите:
  mainToolBar->btnFile_Session->click();
    
  // Спира аудиото, ако е пуснато. Това е важно, за да се отблокира раздела, за да може да се затвори:
  audioToolBar->slotForceStop(); // Спира аудиото (без значение дали е пуснато или не) и освобождава раздела, за да може да се затвори.

  // Изключва ежедневното четене:
  if (mainToolBar->btnNavigation_DailyRead->isChecked()) mainToolBar->btnNavigation_DailyRead->click();  // Ако ежедневното четене е отворено трябва да се затвори.

  // Затваря бележника. Идеята е ако текстът в него не е записан да се запише преди да е пусната програмата отново.
  if (padIsOpen) 
  {
    pad->close();
    delete pad;
    pad = 0;
  }

  // Затваря WWWRes.
  if (WWWResIsOpen) 
  {
    WWWRes->close();
    delete WWWRes;
    WWWRes = 0;
  }

  exeName = QCoreApplication::applicationFilePath();
  if (QFile::exists(exeName))
  {
    startSession = currentSession; // Това е сесията, която ще се отвори при повторното пускане на програмата в closeEvent metoda.
  }

  slotFile_Exit(); // Затваря програмата като преди това записва настройките на сесията и стартира програма отново.
}

/// HelpToolBar
void MainWindow::slotHelp_Help()
{
  // Практиката показва, че никой не обича да чете хелп-ове, особено големи.
  // Ето защо, старият хелп е премахнат (редовете по-долу са коментирани, но оставени да се виждат, ако се наложи да се прави нещо подобно).
  // Вместо него е направен един доста опростен хепл, който има едно важно предимство - текстът, който използва е от многоезичните стрингове
  // т.е. хелпът ще се чете на избрания език. Картинките обаче ще са на английски, като общоприет език.
  //
  // Отваряне на стария хелп:
  //ExTextWindow *helpView = new ExTextWindow(this, 650, 650);
  //helpView->setWindowTitle(MO->TS->Help + " - " + QCoreApplication::applicationName());
  //
  //helpView->setSearchPaths(QStringList( QString("%1/Help/%2").arg(QCoreApplication::applicationDirPath()).arg(MO->TS->currentAppTranslation) ));
  //helpView->openFile(QString("%1/Help/%2/Help.html").arg(QCoreApplication::applicationDirPath()).arg(MO->TS->currentAppTranslation), true);
  //helpView->show();

  // Много е важно всеки стринг да бъде поставен в собствен div таг. По този начин се изписват правилно стрингове,
  // които са с различен Layout. Например, ако имаме RightToLeft Layout на цялото приложение и някъде измежду стринговете
  // има един непреведен, т.е. с LeftToRight Layout, то той ще се изпише както трябва. В противен случай ще се получи
  // разместване на някои знаци в него и освен това ще се изпише в дясно.
  // Таг <p> върши същата работа, но той вкарва допълнителен празен ред след себе си, докато <div> вкарва само един, затова след <div> не се слага <br>.
  QString text = QString("<head>");
  text += QString("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />");
  text += QString("<title>Help - MatCrossBible</title>");
  text += QString("<style type=text/css>");
  text += QString("  body{color:#101010;}");
  //text += QString("  table{direction:%1;}").arg((MO->TS->globalLayoutDirection == Qt::LeftToRight) ? "ltr" : "rtl"); // Това не сработва изобщо в този браузър. Би трябвало да обръща местата на колоните в таблиците, но здраве да е. И без това ще вкара странични ефекти, най-вероятно.
  text += QString("  .color_o{background-color:#00aaaa;}");
  text += QString("  .color_b{background-color:#ffffff;}");
  text += QString("</style>");
  text += QString("</head><body>");
  text += QString("<center><img src=\":/resources/images/logo64x64.png\" width=\"64\" height=\"64\"/>");
  text += QString("<font color=#00aaaa><big><b><div>%1</div></b></big></font><font color=#00aaaa><div>Ver %2</div></font><br />").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()); // b00000 - червен.
  text += QString("<div>%1</div><div>%2</div>%3</div><br /><div>%4</div><br /></center>").arg(MO->TS->AboutMatCrossBible1_v1).arg(MO->TS->AboutMatCrossBible2_v1).arg(MO->TS->AboutMatCrossBible3_v1).arg(MO->TS->AboutMatCrossBible4_v1);

  text += QString("<table border=0 cellspacing=0 cellpadding=5 bgcolor=#00aaaa width=100%><tr><td><span style=\"color:#ffffff;\"><big><b>%1</b></big></span></td></tr></table>").arg(MO->TS->MainWindow_v1);
  text += QString("<table border=0 cellspacing=1 cellpadding=5 width=100% class=\"color_o\">");
  text += QString("<tr><td align=\"center\" class=\"color_b\"><img src=\":/resources/help/mainwindow.png\"/></td></tr>");
  text += QString("</table><br /><br />");

  text += QString("<table border=0 cellspacing=0 cellpadding=5 bgcolor=#00aaaa width=100%><tr><td><span style=\"color:#ffffff;\"><big><b>%1</b></big></span></td></tr></table>").arg(MO->TS->TVTMenu_v1);
  text += QString("<table border=0 cellspacing=1 cellpadding=5 width=100% class=\"color_o\">");
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/new.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->NewDockWindow_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/books.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Books_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/bookmarks.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Bookmarks_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/arrowback.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->GoBack_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/arrowforward.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->GoForward_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/navigation.png\"/></td><td class=\"color_b\"><div>%1</div><div>%2</div><div>%3</div></td></tr>").arg(MO->TS->NextPreviousBook_v1).arg(MO->TS->NextPreviousChapter_v1).arg(MO->TS->NextPreviousVerse_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/dailyread.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->DailyRead_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/navigationdr.png\"/></td><td class=\"color_b\"><div>%1</div><div>%2</div></td></tr>").arg(MO->TS->DailyReadGroup_v1).arg(MO->TS->DailyReadChapterInGroup_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/search.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->SearchInBible_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/bibletexts.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->BibleTexts_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/audio.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Audio_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/zoomin.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->ZoomInText_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/zoomout.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->ZoomOutText_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/zoomnormal.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->RestoreDefaultZoom_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/searchinthetext.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->SearchInTheTextPanel_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/casesensitive.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->CaseSensitive_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/wholewords.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->WholeWords_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/selectall.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->SelectAll_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/copy.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Copy_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/save.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Save_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/statistics.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->StatisticsMenu_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/pad.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Pad_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/dictionary.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->DictionaryCommentary_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/image.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->ExternalImages_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/www.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Links_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/projector.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Projector_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/settings.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Settings_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/help.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Help_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/info.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->About_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/filemenu.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->FileMenu_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/session.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Session_v1);
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/exit.png\"/></td><td class=\"color_b\"><div>%1</div></td></tr>").arg(MO->TS->Exit_v1);
  text += QString("</table><br /><br />");

  text += QString("<table border=0 cellspacing=0 cellpadding=5 bgcolor=#00aaaa width=100%><tr><td><span style=\"color:#ffffff;\"><big><b><div>%1</div></b></big></span></td></tr></table>").arg(MO->TS->TitleBarButtons_v1);
  text += QString("<table border=0 cellspacing=1 cellpadding=5 width=100% class=\"color_o\">");
  text += QString("<tr><td width=5% class=\"color_b\"><img src=\":/resources/help/titlebarbuttons.png\"/></td><td class=\"color_b\"><div>%1</div><div>%2</div><div>%3</div></td></tr>").arg(MO->TS->NewDockWindow_v1).arg(MO->TS->MaximizeNormalize_v1).arg(MO->TS->CloseWindow_v1);
  text += QString("</table><br /><br />");

  text += QString("<table border=0 cellspacing=0 cellpadding=5 bgcolor=#00aaaa width=100%><tr><td><span style=\"color:#ffffff;\"><big><b><div>%1</div></b></big></span></td></tr></table>").arg(MO->TS->ToolbarPanels_v1);
  text += QString("<table border=0 cellspacing=1 cellpadding=5 width=100% class=\"color_o\">");
  text += QString("<tr><td class=\"color_b\">");
  text += QString("  <table border=0 cellspacing=0 cellpadding=5 width=100%>");
  text += QString("  <tr><td width=5%><img src=\":/resources/help/bookspanel.png\"/></td><td><b><div>%1</div></b><b><div>%2</div></b></td></tr>").arg(MO->TS->Books_v1).arg(MO->TS->FastAccess_v1);
  text += QString("  </table>");
  text += QString("</td></tr>");
  text += QString("<tr><td class=\"color_b\">");
  text += QString("  <table border=0 cellspacing=0 cellpadding=5 width=100%>");
  text += QString("  <tr><td width=5%><img src=\":/resources/help/bookmarkspanel.png\"/></td><td><b><div>%1</div></b><br><div>%2</div><div>%3</div><div>%4</div></td></tr>").arg(MO->TS->Bookmarks_v1).arg(MO->TS->AddBookmark_v1).arg(MO->TS->ShowBookmark_v1).arg(MO->TS->DeleteBookmark_v1);
  text += QString("  </table>");
  text += QString("</td></tr>");
  text += QString("<tr><td class=\"color_b\">");
  text += QString("  <table border=0 cellspacing=0 cellpadding=5 width=100%>");
  text += QString("  <tr><td width=5%><img src=\":/resources/help/searchpanelresults.png\"/><br><br><img src=\":/resources/help/searchpanelfilter.png\"/><br><br><img src=\":/resources/help/searchpanelmap.png\"/></td>");
  text += QString("  <td><b><div>%1</div></b><br>").arg(MO->TS->SearchInBible_v1);
  text += QString("  <div>%1</div><br>").arg(MO->TS->SearchMethodInfo2_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><div>%3</div><div>%4</div><br>").arg(MO->TS->OptSearchRandom_v1).arg(MO->TS->SearchMethodInfo31_v1).arg(MO->TS->SearchMethodInfo32_v1).arg(MO->TS->SearchMethodInfo33_v1); // •
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><div>%3</div><br>").arg(MO->TS->OptSearchRoot_v1).arg(MO->TS->SearchMethodInfo41_v1).arg(MO->TS->SearchMethodInfo42_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><div>%3</div><br>").arg(MO->TS->OptSearchWord_v1).arg(MO->TS->SearchMethodInfo51_v1).arg(MO->TS->SearchMethodInfo52_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div><div>%2</b></i></font><br>%3</div><div>%4</div><br>").arg(MO->TS->OptSearchAll_v1).arg(MO->TS->OptSearchAny_v1).arg(MO->TS->SearchMethodInfo61_v1).arg(MO->TS->SearchMethodInfo62_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><div>%3</div><br>").arg(MO->TS->OptSearchPhrase_v1).arg(MO->TS->SearchMethodInfo71_v1).arg(MO->TS->SearchMethodInfo72_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><div>%3</div><br>").arg(MO->TS->OptSearchWildCard_v1).arg(MO->TS->SearchMethodInfo81_v1).arg(MO->TS->SearchMethodInfo82_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><br>").arg(MO->TS->OptSearchCaseSensitive_v1).arg(MO->TS->SearchMethodInfo9_v1);
  text += QString("  <font color=#00aaaa><i><b><div>%1</div></b></i></font><div>%2</div><br></td></tr>").arg(MO->TS->OptSearchInChapter_v1).arg(MO->TS->SearchMethodInfo10_v1);
  text += QString("  </table>");
  text += QString("</td></tr>");
  text += QString("<tr><td class=\"color_b\">");
  text += QString("  <table border=0 cellspacing=0 cellpadding=5 width=100%>");
  text += QString("  <tr><td width=5%><img src=\":/resources/help/dictionarypanel.png\"/></td><td><b><div>%1</div></b></td></tr>").arg(MO->TS->DictionaryCommentary_v1);
  text += QString("  </table>");
  text += QString("</td></tr>");
  text += QString("<tr><td class=\"color_b\">");
  text += QString("  <table border=0 cellspacing=0 cellpadding=5 width=100%>");
  text += QString("  <tr><td width=5%><img src=\":/resources/help/projectorpanel.png\"/></td><td><b><div>%1</div></b></td></tr>").arg(MO->TS->Projector_v1);
  text += QString("  </table>");
  text += QString("</td></tr>");
  text += QString("</table><br /><br />");

  text += QString(
    "<center><a href=\"http://www.matcraft.org/\"><font color=#0080ff>www.matcraft.org</font></a><br />"
    "<a href=\"mailto:matcraft.org@gmail.com\"><font color=#0080ff>matcraft.org@gmail.com</font></a><br />"
    "<br />"
    "<font color=#00aaaa><b>MatCraft</b></font></center></body>"); // b00000 - червен.

  QTextBrowser *editor = new QTextBrowser;
  editor->setOpenExternalLinks(true); // За отваряне на линковете.
  editor->setOpenLinks(true);         // За отваряне на линковете.
  editor->setReadOnly(true);
  editor->setWordWrapMode(QTextOption::WordWrap);
  editor->setWindowTitle(MO->TS->Help_v1 + " - " + QCoreApplication::applicationName());
  editor->setHtml(text);
  editor->setMinimumSize(1, 1);
  editor->resize(700, 720);
  editor->show();
}

void MainWindow::slotHelp_About()
{
  QString text = QString("<center><img src=\":/resources/images/logo64x64.png\" width=\"64\" height=\"64\"/>");
  text += QString("<font color=#00aaaa><big><b><div>%1</div></b></big></font><font color=#00aaaa><div>Ver %2</div></font><br />").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()); // b00000 - червен.
  text += QString("<div>%1</div><div>%2</div><div>%3</div><br /><div>%4</div><br /><br />").arg(MO->TS->AboutMatCrossBible1_v1).arg(MO->TS->AboutMatCrossBible2_v1).arg(MO->TS->AboutMatCrossBible3_v1).arg(MO->TS->AboutMatCrossBible4_v1);
  text += QString(
    "<a href=\"http://www.matcraft.org/\"><font color=#0080ff>www.matcraft.org</font></a><br>"
    "<a href=\"mailto:matcraft.org@gmail.com\"><font color=#0080ff>matcraft.org@gmail.com</font></a><br>"
    "<br>"
    "<font color=#00aaaa><b>MatCraft</b></font></center>");

  QTextBrowser *editor = new QTextBrowser;
  editor->setFrameShape(QFrame::StyledPanel);
  editor->setOpenExternalLinks(true); // За отваряне на линковете.
  editor->setOpenLinks(true);         // За отваряне на линковете.
  editor->setReadOnly(true);
  editor->setWordWrapMode(QTextOption::WordWrap);
  editor->setHtml(text);
  editor->setMinimumSize(1, 1);

  QPushButton *newAppVerBtn = new QPushButton(MO->TS->CheckNewAppVersion_v1);
  newAppVerBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Preferred Expanding
  newAppVerBtn->setIcon(Icons::icon_NewAppVersion(16, 16, iconColorForms, iconColorForms));
  newAppVerBtn->setMinimumSize(1, 20);
  newAppVerBtn->setFlat(false);

  QPushButton *aboutQtBtn = new QPushButton(QString("About Qt"));
  aboutQtBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // Preferred Expanding
  aboutQtBtn->setMinimumSize(20, 20);
  aboutQtBtn->setFlat(false);

  QPushButton *closeBtn = new QPushButton(MO->TS->CloseWindow_v1);
  closeBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // Preferred Expanding
  closeBtn->setMinimumSize(40, 20);
  closeBtn->setFlat(false);

  QHBoxLayout *hLayout = new QHBoxLayout;
  hLayout->setMargin(0);
  hLayout->setSpacing(1); // Разстояние между обектите.
  hLayout->addWidget(newAppVerBtn);
  hLayout->addWidget(aboutQtBtn);
  hLayout->addWidget(closeBtn);

  QVBoxLayout *vLayout = new QVBoxLayout;
  vLayout->setMargin(1);
  vLayout->setSpacing(1); // Разстояние между обектите.
  vLayout->addWidget(editor);
  vLayout->addLayout(hLayout);

  QWidget *dialog = new QWidget();
  //QDialog *dialog = new QDialog(this, Qt::Dialog); // Ако се използва QDialog вместо QWidget прозорецът няма да е модален - стои отгоре и НЕ може да се работи с главния прозорец отзад, докато не се затвори. Това е добре, но става ненормална ситуация когато се отвори прозорецът за проверка на нова версия.
  //dialog->setModal(true);
  dialog->setLayout(vLayout);

  connect(newAppVerBtn, SIGNAL(clicked()), this, SLOT(slotHelp_NewAppVersion()));
  connect(aboutQtBtn, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
  connect(closeBtn, SIGNAL(clicked()), dialog, SLOT(close()));

  //dialog->setGeometry(this->pos().x() + 20, this->pos().y() + 40, 440, 320); // - Чрез този метод позиционирането е по-различно отколкото с move(). Тук не се взимат в предвид рамките на прозореца.
  //dialog->move(this->pos().x() + 30, this->pos().y() + 30); // Този ред върви с долния, но го коментирах, за да се показва прозореца в средата на екрана.
  dialog->resize(380, 340);
  dialog->setMinimumSize(50, 50);
  dialog->show();
  closeBtn->setFocus();
}

void MainWindow::slotHelp_NewAppVersion()
{
  NewAppVerWindow *navw = new NewAppVerWindow(this);
  navw->show();
  navw->raise();
}

void MainWindow::slotBibleTexts()
{
  currentHolyTextView->activeBibleTextsCount = 0;
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    if (bibleTextBtn[i]->isChecked())
    {
      currentHolyTextView->activeBibleTexts[i] = true;
      currentHolyTextView->activeBibleTextsCount++;
    }
    else
    {
      currentHolyTextView->activeBibleTexts[i] = false;
    }
  }

  if (currentHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
  {
    currentHolyTextView->showBibleText(currentHolyTextView->currentAbsIndex);
  }
  else // Ако е в режим на ежедневноно четене.
  {
    currentHolyTextView->showBibleText(currentDR_AbsIndex);
  }
}

void MainWindow::slotFastAccessWidgetInFocus()
{
  if (currentHolyTextView == 0 || currentHolyTextView->readMode == READ_MODE__DAILY_READ) return;

  mDockBooks->setVisible(true); // Показва панела с книгите, ако е скрит.
  fastAccessWidget->setFocus(); // Поставя полето за бърз достъп на фокус.
  fastAccessWidget->selectAll(); // Селектира текста, за да е по-лесно да се напише нов.
}

void MainWindow::slotReorderBibleTexts()
{
  ReorderBibleTextsWindow reorderBibleTextsWindow(MO, &needToRestart, this);
  reorderBibleTextsWindow.exec();
  if (needToRestart)
  {
    slotRestart(true);
    //needToRestart = false; // Това да не се разкоментира, за да напомня всеки път след затваряне на формата, че има нужда от рестарт.
  }
}

void MainWindow::slotBibleTextsInfo()
{
  QString text = "";
  if ( MO->bibleTextList.size() == 0 ) // Ако няма файлове с текстове.
  {
    text += QString("<font color=#ff0000><b><div>%1</div></b></font><br>").arg(MO->TS->BibleTextsFileProblem1_v1);
    text += QString("<font color=%1><div>%2</div><div>%3</div><div>%4</div></font>").arg(MO->SVars.textInBracketsColorF.name()).arg(MO->TS->BibleTextsFileProblem2_v1).arg(QDir::toNativeSeparators(QString("%1/BibleTexts").arg(MO->applicationDirPath))).arg(MO->TS->BibleTextsFileProblem3_v1);
  }
  else // Ако има файлове с текстове.
  {
    for (int i = 0; i < MO->bibleTextList.size(); i++)
    {
      text += QString("<font color=#00aaaa>●</font> <span style=\"font-family:%1;\"><font color=#00aaaa><b>%2</b></font><br><font color=#a0a0a0><b>File:</b> %3<br><b>Font-family:</b> %4<br><b>Last modify date:</b> %5<br><b>Language:</b> %6</font><div>%7</div></span><br><br>").arg(MO->bibleTextList[i].fontFamily).arg(MO->bibleTextList[i].name).arg(MO->bibleTextList[i].fileName).arg(MO->bibleTextList[i].nativeFontFamily).arg(MO->bibleTextList[i].lastModifyDate).arg(MO->bibleTextList[i].language).arg(MO->bibleTextList[i].description);
    }
  }

  ExTextWindow *bibleTextsInfoView = new ExTextWindow(this, 600, 400);
  bibleTextsInfoView->setWindowTitle(MO->TS->BibleTextsInfo_v1 + " - " + QCoreApplication::applicationName());
  bibleTextsInfoView->setWordWrapMode(true);
  bibleTextsInfoView->setHtmlText(text);
  bibleTextsInfoView->show();
}

void MainWindow::slotMoreBibleTexts()
{
  MoreBibleTextsWindow *mbtw = new MoreBibleTextsWindow(this);
  mbtw->show();
}

void MainWindow::slotConvertBibleTexts()
{
  BibleTextConvertor *btc = new BibleTextConvertor(MO);
  btc->show();
}

void MainWindow::slotShowWinDimensions()
{
  showWinDimensions = !showWinDimensions;
  if (showWinDimensions)
  {
    //setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height())); // Заглавната лента изписва дименсиите на прозореца (без рамката).
    setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(frameGeometry().x()).arg(frameGeometry().y()).arg(frameGeometry().width()).arg(frameGeometry().height())); // Заглавната лента изписва дименсиите на прозореца (с рамката).
    setWindowIcon(QIcon(":/resources/images/logo128x128e.png"));
  }
  else
  {
    setWindowTitle(QCoreApplication::applicationName());
    setWindowIcon(QIcon(":/resources/images/logo128x128.png"));
  }
}

void MainWindow::slotFocusChanged(QWidget *old, QWidget *now)
{
  if (old == fastAccessWidget) // Ако fastAccessWidget вече не е на фокус.
  {
    fastAccessWidget->showGreyText(true);
  }
  if (now == fastAccessWidget) // Ако fastAccessWidget е на фокус.
  {
    fastAccessWidget->showGreyText(false);
  }

  if (mainToolBar != 0)
  {
    if (old == mainToolBar->lineEdit_SearchInText) // Ако mainToolBar->lineEdit_SearchInText вече не е на фокус.
    {
      mainToolBar->showAlphaPalette_LineEdit_SearchInText(true);
    }
    if (now == mainToolBar->lineEdit_SearchInText) // Ако mainToolBar->lineEdit_SearchInText е на фокус.
    {
      mainToolBar->showAlphaPalette_LineEdit_SearchInText(false);
    }
  }
}

void MainWindow::slotDockWidgetRaised(MDock */*dock*/, MDockWidget *dockWidget)
{
  if (dockWidget->getDockWidgetType() == DOCK_TYPE__HOLY_TEXT_VIEW)
  {
    for (int i = 0; i < HDocks.length(); i++)
    {
      if (HDocks[i].dockWidget == dockWidget)
      {
        if (HDocks[i].textView != 0) currentTextViewChanged(HDocks[i].textView); // Ако съдържа текстово поле.
        break;
      }
    }
  }
  else if (dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY)
  {
    for (int i = 0; i < ODocks.length(); i++)
    {
      if (ODocks[i].dockWidget == dockWidget)
      {
        if (ODocks[i].textView != 0) currentTextViewChanged(ODocks[i].textView); // Ако съдържа текстово поле.
        break;
      }
    }
  }
}

void MainWindow::slotCloseDock(MDock */*dock*/, MDockWidget *dockWidget, int /*dockWidgetID*/, quint8 dockWidgetType)
{
  if (dockWidgetType == DOCK_TYPE__HOLY_TEXT_VIEW) // Търси раздела в списъка HDocks.
  {
    if (HDocks.length() <= 1 || dockWidget->getDockWidgetDisallowCloseLevel1() || dockWidget->getDockWidgetDisallowCloseLevel2()) return; // Ако раздела не може да бъде затворен.

    for (int i = 0; i < HDocks.length(); i++)
    {
      if (HDocks[i].dockWidget == dockWidget)
      {
        if (currentHolyTextView == HDocks[i].textView) currentHolyTextView = 0; // Нулира указателя, защото обектът (разделът) ще бъде изтрит. По-долу указателя ще бъде насочен към друг раздел.
        // Тук не трябва да се извиква "delete dockWidget", защото този слот е извикан от натискането на бутон X на раздела,
        // който трябва да се изтрие и ако разделът се изтрие с delete, управлението след изпълнение на този слот се връща
        // към вече изтрития раздел, следствие на което в повечето случай програмата крашва (но не винаги - зависи дали
        // изтритият раздел е още в паметта). Ето защо трябва да се извиква closeDockWidget, който ще извика слота close
        // и разделът ще бъде изтрит след нормалното завръщане от изпълнението на този слот, тъй като разделът е с атрибут
        // deleteOnClose (сетнат е методът setAttribute(Qt::WA_DeleteOnClose, true);).
        dockWidget->closeDockWidget();
        HDocks.removeAt(i);
        currentTextViewChanged(HDocks[0].textView); // Прави първият раздел текущ (такъв винаги има, защото няма как да бъде изтрит).
        HDocks[0].dockWidget->raise(); // Това ще го покаже на преден план, в случай, че е в таб.

        if (mainToolBar->btnNavigation_New->hasFocus()) mainToolBar->btnNavigation_New->clearFocus(); // Това е, защото първият бутон става на фокус.
        break;
      }
    }
  }
  else // Търси раздела в списъка ODocks.
  {
    if (dockWidget->getDockWidgetDisallowCloseLevel1() || dockWidget->getDockWidgetDisallowCloseLevel2()) return; // Ако раздела не може да бъде затворен.

    for (int i = 0; i < ODocks.length(); i++)
    {
      if (ODocks[i].dockWidget == dockWidget)
      {
        if (dockWidgetType == DOCK_TYPE__DICTIONARY) dockWidget->deleteWidget();
        // Тук не трябва да се извиква "delete dockWidget", защото този слот е извикан от натискането на бутон X на раздела,
        // който трябва да се изтрие и ако разделът се изтрие с delete, управлението след изпълнение на този слот се връща
        // към вече изтрития раздел, следствие на което в повечето случай програмата крашва (но не винаги - зависи дали
        // изтритият раздел е още в паметта). Ето защо трябва да се извиква closeDockWidget, който ще извика слота close
        // и разделът ще бъде изтрит след нормалното завръщане от изпълнението на този слот, тъй като разделът е с атрибут
        // deleteOnClose (сетнат е методът setAttribute(Qt::WA_DeleteOnClose, true);).
        dockWidget->closeDockWidget();
        ODocks.removeAt(i);
        currentTextViewChanged(HDocks[0].textView); // Прави първият раздел текущ (такъв винаги има, защото няма как да бъде изтрит).
        HDocks[0].dockWidget->raise(); // Това ще го покаже на преден план, в случай, че е в таб.

        if (mainToolBar->btnNavigation_New->hasFocus()) mainToolBar->btnNavigation_New->clearFocus(); // Това е, защото първият бутон става на фокус.
        break;
      }
    }
  }
}

void MainWindow::slotIconActivated(QSystemTrayIcon::ActivationReason reason) // For TrayIcon.
{
  switch (reason)
  {
  //case QSystemTrayIcon::Trigger:
  //  break;
  case QSystemTrayIcon::DoubleClick:
    if (QWidget::isHidden()) show(); // Показва прозореца такъв, какъвто е бил преди да се скрие (нормален или максимизиран).
    break;
  //case QSystemTrayIcon::MiddleClick:
  //  break;
  default:
    ;
  }
}

/// Other ------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadSessionSettings(quint8 currentSession)
{
  QSettings settings(MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  
  // Ежедневно четене:
  QStringList srList = settings.value(QString("dailyRead"), "1^1^0").toString().split("^");
  if (srList.size() == 3) // Ако прочетеният стринг е валиден.
  {
    currentDR_Day = (quint16)srList[0].toUShort();             
    currentDR_ChapterInDailyGroup = (quint8)srList[1].toUShort();
    currentDR_AbsIndex = MO->toEasternExtIndexIfNeed((quint16)srList[2].toUShort()); // Абсолютният индекс се записва винаги по западния стандарт, затова тук се конвертира до източния, ако е нужно.

    if (currentDR_Day < 1 || currentDR_Day > DAILY_READ_TOTAL_DAYS) currentDR_Day = 1;
    MO->getDailyReadGroup(currentDR_Day, currentDR_DailyGroup); // Това е тук, за да се провери (в долния ред) дали числото записано като номер на глава от група е действително.
    if (currentDR_ChapterInDailyGroup < 1 || currentDR_ChapterInDailyGroup > currentDR_DailyGroup.size()) currentDR_ChapterInDailyGroup = 1;
    if (MO->getChaptersFirstVerseAbsIndex(currentDR_AbsIndex) != currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1]) currentDR_AbsIndex = currentDR_DailyGroup[currentDR_ChapterInDailyGroup-1]; // Тази проверка е много важна, защото тя ще оправи и проблем, свързан с промяна на подредбата на книгите в момент, в който ежедневното четене е в Новия Завет.
  }
  else // Ако прочетеният стринг е невалиден се прави инициализация по подразбиране.
  {
    currentDR_Day = 1;
    currentDR_ChapterInDailyGroup = 1;
    currentDR_AbsIndex = 0;
  }

  // Настройките на проектора:
  //projectorWidget->loadSettings(); // Това не трябва да се прави тук, защото в този момент проекторът още не е създаден (той се създава при първо отваряне на панела му, за да не натоварва програмата излишно).

  // ------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  QSettings sessionSettings(MO->sessionsFile, QSettings::IniFormat, this);
  sessionSettings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Кои сесии трябва да се помнят по принцип:
  QBitArray saveSessionArr = sessionSettings.value(QString("saveSession"), QBitArray(9, true)).toBitArray();
  if (saveSessionArr.size() != 9)
  {
    saveSessionArr = QBitArray(9, true);
    sessionSettings.setValue(QString("saveSession"), saveSessionArr);
  }
  for (int i = 0; i < 9; i++)
  {
    saveSessionChBox[i]->setChecked(saveSessionArr[i]);
    sessionBtn[i]->setToolTip(MO->TS->LoadSession_v1);
  }
  sessionBtn[currentSession]->setToolTip(MO->TS->CurrentSession_v1);
  sessionBtn[currentSession]->setChecked(true);

  // Версия 1 на стринговете ===========================================================================================================

  // Общи настройки:
  // Версия на стринговете с настройки ^ x ^ y ^ width ^ height ^ WindowMaximized ^ Дали е отворен центърът за търсене ^ Дали е отворен панелът с книгите/отметките ^ Дали е отворен аудио панелът ^ Дали е отворен панелът с текстовете ^ Дали е отворен панелът с проектора ^ Резервирано за бъдещи нужди ^ Резервирано за бъдещи нужди ^ Резервирано за бъдещи нужди
  sessionSettings.beginGroup(QString("Session%1").arg(currentSession));
  QString general = sessionSettings.value(QString("session%1General").arg(currentSession), "").toString(); // Инициализиращият (подразбиращ се) стринг, не трябва да е тук (затова кавичките са празни), защото по-долу се правият проверки за валидност и ако не мине през тях, тогава се инициализира с подразбиращия стринг.
  QString docks = sessionSettings.value(QString("session%1DocksState").arg(currentSession), "").toString(); // Инициализиращият (подразбиращ се) стринг, не трябва да е тук (затова кавичките са празни), защото по-долу се правият проверки за валидност и ако не мине през тях, тогава се инициализира с подразбиращия стринг.
  QString dockGridState = sessionSettings.value(QString("session%1DockGridState").arg(currentSession), "0^100_1_0^100").toString(); // Подразбиращият стринг е един ред с един прозорец.
  sessionSettings.endGroup();

  // Стрингът започва с номера на версията на стринговете, който се проверява.
  QStringList generalList = general.split("^", QString::SkipEmptyParts);
  if (generalList.size() != 14 || generalList[0] != QString("1")) // Ако стрингът е празен или броя на записаните настройки са различни от очакваното или версията не е 1.
  {
    general = "1^30^30^700^512^0^0^1^0^1^0^0^0^0"; // Инициализиращ (подразбиращ се) стринг.
    generalList = general.split("^", QString::SkipEmptyParts);
  }

  normGeometry = QRect(generalList[1].toUInt(), generalList[2].toUInt(), generalList[3].toUInt(), generalList[4].toUInt());
  setGeometry(normGeometry);
  if (generalList[5] == QString("1")) // Ако прозорецът трябва да се максимизира.
  {
    setWindowState(Qt::WindowMaximized);
    windowMaximized = true;
  }
  //#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
  //    widget.showMaximized();
  //#else
  //    widget.resize(640, 480);
  //    widget.show();
  //#endif

  if (generalList[6] == QString("0") && mainToolBar->btnText_Search->isChecked()) mainToolBar->btnText_Search->click();  // Ако центърът за търсене трябва да се затвори.
  if (generalList[6] == QString("1") && !mainToolBar->btnText_Search->isChecked()) mainToolBar->btnText_Search->click(); // Ако центърът за търсене трябва да се отвори.

  if (generalList[7] == QString("0") && mainToolBar->btnNavigation_Books->isChecked()) mainToolBar->btnNavigation_Books->click();          // Ако тулбарът с книгите трябва да се затвори.
  if (generalList[7] == QString("0") && mainToolBar->btnNavigation_Bookmarks->isChecked()) mainToolBar->btnNavigation_Bookmarks->click();  // Ако тулбарът с отметките трябва да се затвори.
  if (generalList[7] == QString("1") && !mainToolBar->btnNavigation_Books->isChecked()) mainToolBar->btnNavigation_Books->click();         // Ако тулбарът с книгите трябва да се отвори.
  if (generalList[7] == QString("2") && !mainToolBar->btnNavigation_Bookmarks->isChecked()) mainToolBar->btnNavigation_Bookmarks->click(); // Ако тулбарът с отметките трябва да се отвори.
  if (generalList[7] == QString("3") && !mainToolBar->btnNavigation_Books->isChecked()) mainToolBar->btnNavigation_Books->click();         // Ако тулбарът с книгите трябва да се отвори.
  if (generalList[7] == QString("3") && !mainToolBar->btnNavigation_Bookmarks->isChecked()) mainToolBar->btnNavigation_Bookmarks->click(); // Ако тулбарът с отметките трябва да се отвори.

  if (generalList[8] == QString("0") && mainToolBar->btnText_Audio->isChecked()) mainToolBar->btnText_Audio->click();  // Ако аудио панелът трябва да се затвори.
  if (generalList[8] == QString("1") && !mainToolBar->btnText_Audio->isChecked()) mainToolBar->btnText_Audio->click(); // Ако аудио панелът трябва да се отвори.

  if (generalList[9] == QString("0") && mainToolBar->btnText_BibleTexts->isChecked()) mainToolBar->btnText_BibleTexts->click();  // Ако панелът с текстовете трябва да се затвори.
  if (generalList[9] == QString("1") && !mainToolBar->btnText_BibleTexts->isChecked()) mainToolBar->btnText_BibleTexts->click(); // Ако панелът с текстовете трябва да се отвори.
  if (MO->bibleTextList.size() == 0  && !mainToolBar->btnText_BibleTexts->isChecked()) mainToolBar->btnText_BibleTexts->click(); // Ако няма нито един текст, панелът с текстовете трябва да е отворен, за да се вижда бутон "Други".

  if (generalList[10] == QString("0") && mainToolBar->btnOther_Projector->isChecked()) mainToolBar->btnOther_Projector->click();  // Ако панелът с проектора трябва да се затвори.
  if (generalList[10] == QString("1") && !mainToolBar->btnOther_Projector->isChecked()) mainToolBar->btnOther_Projector->click(); // Ако панелът с проектора трябва да се отвори.

  // 11, 12 и 13 - 3 полета резервирани за бъдещи нужди.

  if (!mDockMain->setDockGridState(dockGridState)) mDockMain->setDockGridState("0^100_1_0^100"); // Ако има проблем инициализира с подразбиращия стринг - един ред с един прозорец.

  // Настройки на всеки раздел (различните раздели се отделят със знака "|"):
  // Тип на раздела ^ PosXInDock на раздела ^ PosYInDock на раздела ^ textZoom ^ Абсолютен индекс ^ activeBibleTexts   // За раздел от тип DOCK_TYPE__HOLY_TEXT_VIEW
  // Тип на раздела ^ PosXInDock на раздела ^ PosYInDock на раздела ^ textZoom ^ Речник ^ Дума ^ Бутон S ^ Бутон A+    // За раздел от тип DOCK_TYPE__DICTIONARY
  // Тип на раздела ^ textZoom                                                                                         // За раздел от тип DOCK_TYPE__SEARCH_VIEW
  QStringList docksList = docks.split("|", QString::SkipEmptyParts);
  if (docksList.size() == 0) // Ако стрингът е празен.
  {
    docks = "|1^0^0^1^1^1^1^1.1|"; // Инициализиращ (подразбиращ се) стринг. Винаги има поне един отворен раздел (не се допуска последният раздел да се затвори).
    docksList = docks.split("|", QString::SkipEmptyParts);
  }
  for (int di = 0; di < docksList.size(); di++)
  {
    QStringList dockList = docksList[di].split("^", QString::SkipEmptyParts);
    if (dockList.size() == 0) continue; // Ако стрингът е празен.
    quint8 dockType = (quint8)dockList[0].toUShort();
    
    if (dockType == DOCK_TYPE__HOLY_TEXT_VIEW)
    {
      if (dockList.size() != 6) continue; // Ако стрингът е празен или броят на записаните настройки са различни от очакваното.
      int posXInDock = dockList[1].toInt(); // Позиция по X в дока.
      int posYInDock = dockList[2].toInt(); // Позиция по Y в дока.
      int textZoom = dockList[3].toInt();
      quint16 currentAbsIndex = MO->toEasternExtIndexIfNeed((quint16)dockList[4].toUShort()); // Абсолютният индекс се записва винаги по западния стандарт, затова тук се конвертира до източния, ако е нужно.
      QStringList aBibleTextsList = dockList[5].split(".", QString::SkipEmptyParts);
      if (aBibleTextsList.size() <= 1) // Ако стрингът е празен или повреден. Не се прави проверка дали броят на активните текстове (записан в първия елемент) е равен на size-1.
      {
        dockList[5] = "1.1"; // Инициализиращ (подразбиращ се) стринг. Първата единица е броят на активните текстове (в случая 1).
        aBibleTextsList = dockList[5].split(".", QString::SkipEmptyParts);
      }
      QBitArray activeBibleTexts(512, false);
      quint16 activeBibleTextsCount = 0;
      for (quint8 i = 1; i < aBibleTextsList.size(); i++) // Елемент 0 се игнорира защото е броят на активните текстове.
      {
        if (aBibleTextsList[i] == "1")
        {
          activeBibleTexts[i-1] = true;
        }
      }
      // Проверява дали запомнените последно показани книги са реални (може преди пускането на програмата да са изтрити файлове с текстове, които са били последно показани).
      for (int i = 0; i < activeBibleTexts.size(); i++)
      {
        if (i < MO->bibleTextList.size()) // Ако е в рамките на списъка.
        {
          if (activeBibleTexts[i]) activeBibleTextsCount++;
        }
        else // Ако е извън списъка.
        {
          activeBibleTexts[i] = false; // Премахва всички последно показани текстове, които сега са извън списъка на реално съществуващи текстове (файлове).
        }
      }

      if (commandLineAbsIndex < MAX_VERSES) // Ако трябва да се покаже текстът, зададен от командния ред (това е само при първоначално пускане на програмата).
      {
        currentAbsIndex = (quint16)commandLineAbsIndex; // Абсолютният индекс, който идва от командния ред е по западния стандарт и ако е нужно се конвертира до източния, което е направено при четене на командния ред в началото.
        commandLineAbsIndex = MAX_VERSES; // За да не се показва в останалите раздели.
      }

      newHDock(true, posXInDock, posYInDock, textZoom, activeBibleTexts, activeBibleTextsCount, currentAbsIndex);
    }
    else if (dockType == DOCK_TYPE__DICTIONARY)
    {
      if (dockList.size() != 8) continue; // Ако стрингът е празен или броят на записаните настройки са различни от очакваното.
      int posXInDock = dockList[1].toInt(); // Позиция по X в дока.
      int posYInDock = dockList[2].toInt(); // Позиция по Y в дока.
      int textZoom = dockList[3].toInt();
      int dictIndex = dockList[4].toInt(); // Индекс на комбобокса.
      int currIndex = dockList[5].toInt(); // Индекс на текущо показаната дума/обяснение (за речник това няма смисъл да се използва, но за коментар има логика да се използва за да покаже последния прочетен коментар, в случай че някой чете коментарите наред).
      bool btnCState = (dockList[6].toInt() == 0) ? false : true; // Състояние на бутон S.
      bool btnAState = (dockList[7].toInt() == 0) ? false : true; // Състояние на бутон A+.
      
      newDictionary(true, posXInDock, posYInDock, textZoom, dictIndex, currIndex, btnCState, btnAState);
    }
    //else if (dockType == ...)
    //{
    //}
    else if (dockType == DOCK_TYPE__SEARCH_VIEW)
    {
      if (dockList.size() != 2) continue; // Ако стрингът е празен или броят на записаните настройки са различни от очакваното.
      int textZoom = dockList[1].toInt();

      QFont font;
      //font.setFamily(MO->SVars.fontFamily); // Това не трябва да се разкоментира, защото всеки речник/коментар използва собствен шрифт.
      font.setPointSize(MO->SVars.fontSize);
      mDockSearch->slotSetFontSize_AllSearchView(MO->SVars.fontSize, textZoom);
    }
  }

  if (HDocks.length() == 0) // Ако има някаква грешка в INI файла и не е показан нито един раздел.
  {
    mDockMain->setDockGridState("0^100_1_0^100"); // Инициализира с подразбиращия стринг - един ред с един прозорец.
    QBitArray activeBibleTexts(512, false);
    activeBibleTexts[0] = true;

    newHDock(true, 0, 0, 0, activeBibleTexts, 1, 0);
  }
  
  for (int i = 0; i < MO->bibleTextList.size(); i++) // Установява бутоните за отворените текстове на текущия изглед.
  {
    bibleTextBtn[i]->setChecked(currentHolyTextView->activeBibleTexts[i]);
  }

  tMenu->setSessionToolBarVisible( mainToolBar->btnFile_Session->isChecked() ); // Това за всеки случай.
}

void MainWindow::saveSessionSettings(quint8 currentSession)
{
  QSettings settings(MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Ежедневно четене:
  settings.setValue(QString("dailyRead"), QString("%1^%2^%3").arg(currentDR_Day).arg(currentDR_ChapterInDailyGroup).arg(currentDR_AbsIndex));

  // Настройките на проектора:
  projectorWidget->saveSettings(); // Ако проекторът не е бил отварян, този метод няма да се изпълни (проверката е вътре в него).
  
  // SVars:
  //MO->saveSVarsSettings(); // Тези настройки се записват непосредствено след затваряне на прозореца за настройките.
  settings.beginGroup(QString("Search"));
  if (MO->SVars.searchTargetTextIndex < MO->bibleTextList.size()) // Ако има текстове.
    settings.setValue(QString("searchTargetText"), MO->bibleTextList[MO->SVars.searchTargetTextIndex].fileBaseName);
  settings.endGroup();

  // ------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  QSettings sessionSettings(MO->sessionsFile, QSettings::IniFormat, this);
  sessionSettings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  // Кои сесии трябва да се помнят по принцип:
  QBitArray saveSessionArr(9, false);
  for (int i = 0; i < 9; i++)
  {
    saveSessionArr[i] = saveSessionChBox[i]->isChecked();
  }
  sessionSettings.setValue(QString("saveSession"), saveSessionArr);

  // ==================================================================================================================================================================
  if (!saveSessionChBox[currentSession]->isChecked()) return; // Ако текущата сесия не трябва да се запомни.
  // ==================================================================================================================================================================

  // Версия 1 на стринговете ===========================================================================================================

  // Общи настройки:
  // Версия на стринговете с настройки ^ x ^ y ^ width ^ height ^ WindowMaximized ^ Дали е отворен центърът за търсене ^ Дали е отворен панелът с книгите/отметките ^ Дали е отворен аудио панелът ^ Дали е отворен панелът с текстете ^ Дали е отворен панелът с проектора ^ Резервирано за бъдещи нужди ^ Резервирано за бъдещи нужди ^ Резервирано за бъдещи нужди
  QString general = QString("1"); // 1 е номерът на версията на начина на записване (кодиране) на настройките. Предполага се, че след време ще се промени нещо и тогава този номер ще е 2, 3... и т.н.
  if (!windowMaximized) normGeometry = geometry();
  general += QString("^%1").arg(normGeometry.x());
  general += QString("^%1").arg(normGeometry.y());
  general += QString("^%1").arg(normGeometry.width());
  general += QString("^%1").arg(normGeometry.height());
  general += QString("^%1").arg( (windowMaximized)? QString("1") : QString("0") ); // 1 ако е максимизиран, 0 ако не е.
  general += QString("^%1").arg( (mDockSearch->isVisible())? QString("1") : QString("0") ); // 1 ако е отворен центърът за търсене, 0 ако не е.
  QString open = "0";   if (mDockBooks->isVisible()) open = "1";   if (mDockBookmarks->isVisible()) open = "2";   if (mDockBooks->isVisible() && mDockBookmarks->isVisible()) open = "3";
  general += QString("^%1").arg(open); // 1 ако е отворено дървото с книгите, 2 ако е отворен панелът с отметките, 0 ако нито едното нито другото е отворено.
  general += QString("^%1").arg( (mainToolBar->btnText_Audio->isChecked())? QString("1") : QString("0") ); // 1 ако е отворен аудио панелът, 0 ако не е.
  general += QString("^%1").arg( (mainToolBar->btnText_BibleTexts->isChecked())? QString("1") : QString("0") ); // 1 ако е отворен панелът с текстовете, 0 ако не е.
  general += QString("^%1").arg( (mDockProjector->isVisible())? QString("1") : QString("0") ); // 1 ако е отворен панелът с проектора, 0 ако не е.
  general += QString("^0^0^0"); // 3 полета резервирани за бъдещи нужди.

  // Настройки на всеки раздел (различните раздели се отделят със знака "|"):
  // Тип на раздела ^ PosXInDock на раздела ^ PosYInDock на раздела ^ textZoom ^ Абсолютен индекс ^ activeBibleTexts   // За раздел от тип DOCK_TYPE__HOLY_TEXT_VIEW
  // Тип на раздела ^ PosXInDock на раздела ^ PosYInDock на раздела ^ textZoom ^ Речник ^ Дума ^ Бутон S ^ Бутон A+    // За раздел от тип DOCK_TYPE__DICTIONARY
  // Тип на раздела ^ textZoom                                                                                         // За раздел от тип DOCK_TYPE__SEARCH_VIEW
  QString docks = "";
  for (int index = 0; index < HDocks.length(); index++) // За раздели от тип DOCK_TYPE__HOLY_TEXT_VIEW.
  {
    docks += QString("|%1").arg(HDocks[index].dockWidget->getDockWidgetType());
    docks += QString("^%1").arg(HDocks[index].dockWidget->getPosXInDock());
    docks += QString("^%1").arg(HDocks[index].dockWidget->getPosYInDock());
    docks += QString("^%1").arg(HDocks[index].textView->textZoom);
    docks += QString("^%1").arg(MO->toWesternExtIndexIfNeed(HDocks[index].textView->currentAbsIndex)); // Абсолютният индекс се записва винаги по западния стандарт.
    QString aBibleTexts = QString("%1").arg(HDocks[index].textView->activeBibleTextsCount);
    for (int i = 0; i < MO->bibleTextList.size(); i++)
    {
      if (HDocks[index].textView->activeBibleTexts[i])
        aBibleTexts += ".1";
      else
        aBibleTexts += ".0";
    }
    docks += QString("^%1").arg(aBibleTexts);
  }
  for (int index = 0; index < ODocks.length(); index++) // За раздели от друг тип.
  {
    if (ODocks[index].dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY)
    {
      docks += QString("|%1").arg(ODocks[index].dockWidget->getDockWidgetType());
      docks += QString("^%1").arg(ODocks[index].dockWidget->getPosXInDock());
      docks += QString("^%1").arg(ODocks[index].dockWidget->getPosYInDock());
      docks += QString("^%1").arg(ODocks[index].textView->textZoom);
      docks += QString("^%1").arg(ODocks[index].dictionary->dictCmbBox->currentIndex()); // Индекс на комбобокса.
      docks += QString("^%1").arg(ODocks[index].dictionary->currentIndex); // Индекс на текущо показаната дума/обяснение (за речник това няма смисъл да се използва, но за коментар има логика да се използва за да покаже последния прочетен коментар, в случай, че някой чете коментарите наред).
      docks += QString("^%1").arg(ODocks[index].dictionary->catchCopyEventBtn->isChecked() ? 1 : 0); // Състояние на бутон S.
      docks += QString("^%1").arg(ODocks[index].dictionary->catchSelectEventBtn->isChecked() ? 1 : 0); // Състояние на бутон A+.
    }
    //else if (ODocks[index].dockWidget->getDockWidgetType() == ...)
    //{
    //}
  }
  // За изгледа с резултатите от търсенето:
  docks += QString("|%1").arg(DOCK_TYPE__SEARCH_VIEW);
  docks += QString("^%1").arg(mDockSearch->currentSearchWidget->searchView->textZoom);

  // Записва настройките:
  sessionSettings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  sessionSettings.beginGroup(QString("Session%1").arg(currentSession));
    sessionSettings.setValue(QString("session%1General").arg(currentSession), general); // Общи настройки.
    sessionSettings.setValue(QString("session%1DocksState").arg(currentSession), docks); // Настройки на всеки раздел.
    sessionSettings.setValue(QString("session%1DockGridState").arg(currentSession), mDockMain->getDockGridState()); // Запомня състоянието на мрежата на дока.
  sessionSettings.endGroup();

  switchToNormalMode();
}

// Този метод се пренаписва с цел забрана показването на popup менюто на QToolBar.
QMenu *MainWindow::createPopupMenu()
{
  return 0;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
  QMainWindow::keyPressEvent(event);

  if (event->modifiers() == Qt::ControlModifier) // Ако е натиснат Ctrl.
  {
    ctrlKeyPressed = true;

    if (event->key() == Qt::Key_Equal)
    {
      slotText_ZoomIn(); // Клавишната комбинация за увеличаване на текста "Ctrl++", под Уиндоус изисква на практика освен Ctrl, да се задържи и Shift, защото "+" е в горен регистър. Този проблем се решава с този ред (Ctrl+=).
    }
    else if (event->key() == Qt::Key_D)
    {
      slotShowWinDimensions();
    }
  }
  else if (event->modifiers() == Qt::ShiftModifier) // Ако е натиснат Shift.
  {
  }
  else if (event->modifiers() == Qt::AltModifier) // Ако е натиснат Alt.
  {
    //if (event->key() == Qt::Key_0) QMessageBox::information(this, QString(""), QString("0"));
    //if (event->key() == Qt::Key_1) QMessageBox::information(this, QString(""), QString("1"));
    //if (event->key() == Qt::Key_2) QMessageBox::information(this, QString(""), QString("2"));
    //if (event->key() == Qt::Key_3) QMessageBox::information(this, QString(""), QString("3"));
    //if (event->key() == Qt::Key_4) QMessageBox::information(this, QString(""), QString("4"));
    //if (event->key() == Qt::Key_5) QMessageBox::information(this, QString(""), QString("5"));
    //if (event->key() == Qt::Key_6) QMessageBox::information(this, QString(""), QString("6"));
    //if (event->key() == Qt::Key_7) QMessageBox::information(this, QString(""), QString("7"));
    //if (event->key() == Qt::Key_8) QMessageBox::information(this, QString(""), QString("8"));
    //if (event->key() == Qt::Key_9) QMessageBox::information(this, QString(""), QString("9"));

    if (event->key() == Qt::Key_Alt) // Ако е натиснат само Alt без друг клавиш.
      altOnlyKeyPressed = true;
    else // Ако е натисната комбинация Alt плюс друг клавиш.
      altOnlyKeyPressed = false;
  }
  else // Ако НЕ е натиснат Ctrl или Shift или Alt.
  {
    if (event->key() == Qt::Key_F5) slotShow();
    else if (event->key() == Qt::Key_F6) slotText_CompareTwoTexts();
    else if (event->key() == Qt::Key_Escape)
    {
      if (currentHolyTextView != 0)
      {
        currentTextViewChanged(currentHolyTextView);
        fastAccessWidget->clearFocus();
        mainToolBar->lineEdit_SearchInText->clearFocus();
        currentHolyTextView->setFocus();
      }
    }
    else if (event->key() == Qt::Key_F11) slotFastAccessWidgetInFocus();

    altOnlyKeyPressed = false;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  QMainWindow::keyReleaseEvent(event);

  //if (event->key() == Qt::Key_Alt && altOnlyKeyPressed) // Ако е бил натиснат само Alt (без друг клавиш).
  //{
  //  //mainToolBar->slotChangeToolBarPosition(); // Това мести бутоните в MainToolBar в крайно ляво/дясно, но не е добре, защото може да има отворени речници, които използват Alt клавиша за селектиране на дума/стих при което бутоните постоянно се местят.
  //}

  ctrlKeyPressed = false;
  altOnlyKeyPressed = false;
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
  QMainWindow::resizeEvent(event);

  if (showWinDimensions)
  {
    //setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height())); // Заглавната лента изписва дименсиите на прозореца (без рамката).
    setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(frameGeometry().x()).arg(frameGeometry().y()).arg(frameGeometry().width()).arg(frameGeometry().height())); // Заглавната лента изписва дименсиите на прозореца (с рамката).
  }

  //windowMaximized = (windowState() & Qt::WindowMaximized); // !!! Този ред не може да е тук, защото реално състоянието на прозореца още не се е сменило. Ето защо съм принуден да го направя с таймер (долния ред).
  QTimer::singleShot(100, this, SLOT(slotResizeEvent())); // Когато таймерът извика слота, състоянието вече ще се е сменило (става въпрос дали прозорецът е максимизиран или не).
}
void MainWindow::slotResizeEvent()
{
  // Тук вече прозорецът се е установил и може да му се вземе състоянието.
  windowMaximized = (windowState() & Qt::WindowMaximized); // Прозорецът може да е максимизиран, дори когато е минимизиран.
  if (!windowMaximized) normGeometry = geometry();
}

void MainWindow::moveEvent(QMoveEvent *event)
{
  QMainWindow::moveEvent(event);

  // Този ивент (moveEvent) се извиква преди resizeEvent и затова закоментираният ред долу не може да се използва,
  // защото при максимизиране първо ще вземе максимизираните размери и после ще вдигне флага, че е максимизиран.
  // Този проблем се решава частично, като в метода за записване на настройките се взима текущата позиция и размер,
  // но само ако прозорецът не е максимизиран в този момент. Ако е максимизиран, няма да запомни променената преди
  // това позиция, което не е голям проблем. Като допълнително решаване на проблема се използва по-долният метод.
  //if (!windowMaximized) normGeometry = geometry(); // Това ще върне размера и позицията на максимизирания прозорец преди да е установено, че е максимизиран. Затова не може да се използва. Вместо този ред се използва долният.
  if (frameGeometry().y() >= 0) normGeometry = geometry(); // Би трябвало, при НЕмаксимизиран прозорец, y() да е >=0 (тук се проверява размера на рамката).

  if (showWinDimensions)
  {
    //setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height())); // Заглавната лента изписва дименсиите на прозореца (без рамката).
    setWindowTitle(QString("X:%1 Y:%2 (%3x%4)").arg(frameGeometry().x()).arg(frameGeometry().y()).arg(frameGeometry().width()).arg(frameGeometry().height())); // Заглавната лента изписва дименсиите на прозореца (с рамката).
  }
}

void MainWindow::setVisible(bool visible) // For TrayIcon.
{
  QMainWindow::setVisible(visible);

  if (trayIcon != 0)
  {
    if (visible) // Ако прозорецът е отворен.
    {
      trayIcon->hide();
    }
    else if (!MO->enableExitAction) // Ако прозорецът е затворен но от бутона в заглавната лента.
    {
      if (MO->SVars.enableTrayIcon) trayIcon->show();
    }
  }
}

QFrame *MainWindow::getVSeparator()
{
  QFrame *vFrame = new QFrame();
  vFrame->setFrameShape(QFrame::VLine);
  vFrame->setFrameShadow(QFrame::Plain); // Plain  Raised  Sunken

  QColor colorA = MO->SVars.appColorB;   colorA.setAlpha(80);
  QPalette palette;
  palette.setBrush(QPalette::WindowText, colorA);
  vFrame->setPalette(palette);
  
  return vFrame;
}

/// ------------------------------------------------------------------------------------------------------------------------

void MainWindow::showFoundVerse(quint16 absIndex, bool highlightSearchWords)
{
  switchToNormalMode();

  // При кликване върху стих в резултата от търсенето, ако текстът, в който е търсено не е показан, ще го покаже и него:
  //currentTextView->activeBibleTexts.clear(); // Това не работи като хората!!! Да се използва долния ред!
  //currentTextView->activeBibleTexts.fill(false); // Нулира всички битове. Така ще покаже само текста, в който е търсено (ако се махне коментара от този ред).
  currentHolyTextView->activeBibleTextsCount = 0;
  currentHolyTextView->activeBibleTexts[mDockSearch->currentSearchWidget->searchTargetTextIndex] = true; // Това е текстът в който е търсено (в случай, че не е показан, го показва и него).
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    bibleTextBtn[i]->setChecked(currentHolyTextView->activeBibleTexts[i]);
    if (currentHolyTextView->activeBibleTexts[i]) currentHolyTextView->activeBibleTextsCount++;
  }

  if (highlightSearchWords)
  {
    currentHolyTextView->tempSearchWordsList = mDockSearch->currentSearchWidget->searchWordsList; // tempSearchWordsList съдържа търсените думи, които ще бъдат оцветени веднага след показване на главата, съдържаща търсения стих. Те ще останат оцветени и при прибавяне на нов текст (точно това е идеята), но при показване на друга глава няма да се оцветят повече.
    currentHolyTextView->tempCaseSensitivitySearch = mDockSearch->currentSearchWidget->caseSensitivitySearch; // tempCaseSensitivitySearch съдържа CaseSensitivity режима на търсените думи, които ще бъдат оцветени веднага след показване на главата, съдържаща търсения стих. Те ще останат оцветени и при прибавяне на нов текст (точно това е идеята), но при показване на друга глава няма да се оцветят повече.
  }
  else
  {
    currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече (ако има такива).
    currentHolyTextView->tempCaseSensitivitySearch = Qt::CaseInsensitive;
  }
  currentHolyTextView->showBibleText(absIndex);
}

void MainWindow::showBookmark(quint16 absIndex)
{
  quint8 b, c, v;
  MO->absIndexToReference(absIndex, b, c, v); // Превръща абсолютния индекс на стиха в препратки (код на книгата, главата и стиха).
  if (!MO->SVars.showDeuterocanonical) // Ако са скрити Второканоничните книги.
  {
    if ( (b >= 40 && b <= 50) || (b == 19 && c == 151) || (b == 27 && (c == 13 || c == 14)) )
    {
      QMessageBox::information(this, QCoreApplication::applicationName(), MO->TS->DisabledDeuterocanonicalInfo_v1);
      return;
    }
  }

  if (ctrlKeyPressed) // Ако трябва да се покаже в нов раздел (ако е натиснат клавиш Ctrl по време на кликването).
  {
    newHDock(false, -1, -1, 0, QBitArray(), 0, absIndex); // Отваря нов прозорец и показва главата в него. Четвъртия параметър трябва да е 0.
    ctrlKeyPressed = false; // Сваля флага, защото този прозорец вече не е на фокус и не може да прихване keyReleaseEvent-а, който отговаря за свалянето на флага.
  }
  else // Ако не е натиснат клавиш Ctrl по време на кликването.
  {
    switchToNormalMode();
    currentHolyTextView->tempSearchWordsList.clear(); // Изтрива списъка с търсените думи, за да не се оцветяват повече.
    currentHolyTextView->showBibleText(absIndex);
  }
}

void MainWindow::showSearchCenter(bool show)
{
  if (show) // Ако трябва да се покаже панелът за търсене.
  {
    mDockSearch->setVisible(true);
    mDockSearch->currentSearchWidget->setSearchLineInFocus(true);
  }
  else // Ако трябва да се скрие панелът за търсене.
  {
    mDockSearch->setVisible(false);
  }
}

void MainWindow::switchToNormalMode()
{
  // Първо проверява дали текущият изглед не е в режим на ежедневно четене и ако да - превключва в нормално четене.
  if (currentHolyTextView != 0 && currentHolyTextView->readMode == READ_MODE__DAILY_READ) // Ако е в ежедневно четене.
  {
    mainToolBar->btnNavigation_DailyRead->click(); // Превключва в нормално четене.
  }
}

void MainWindow::set3DTitleBars()
{
  tMenu->set3DTitleBar(MO->SVars.docks3DTitleBar);

  mDockBooks->slotSet3DTitleBar();
  mDockBookmarks->slotSet3DTitleBar();
  mDockSearch->slotSet3DTitleBar();
  mDockProjector->slotSet3DTitleBar();

  for (int index = 0; index < HDocks.length(); index++)
  {
    HDocks[index].dockWidget->setDockWidget3DTitleBar(MO->SVars.docks3DTitleBar);
  }
  for (int index = 0; index < ODocks.length(); index++)
  {
    ODocks[index].dockWidget->setDockWidget3DTitleBar(MO->SVars.docks3DTitleBar);
  }
}

void MainWindow::colorChanged()
{
  setAppColors();  

  tMenu->setColors(MO->SVars.appColorF, MO->SVars.appColorB);
  mainToolBar->setIconsColor(MO->SVars.appColorF, MO->SVars.appColorB);

  if (MO->bibleTextList.size() == 0) return; // Ако няма нито един текст на Библията, всичко ще е неактивно и няма нужда да се променят цветовете. Така спестявам и много проверки против крашване на програмата.

  mDockMain->setDockBgColor(MO->SVars.appColorB);
  mDockBooks->slotSetColors();
  mDockBookmarks->slotSetColors();
  mDockSearch->slotSetColors();
  mDockProjector->slotSetColors();

  for (int index = 0; index < HDocks.length(); index++)
  {
    HDocks[index].dockWidget->setDockWidgetBgColor(MO->SVars.appColorF);
    HDocks[index].dockWidget->setDockWidgetTitleBarColor(MO->SVars.appColorF);
    HDocks[index].dockWidget->setDockWidgetTitleBarTextColor(MO->SVars.appColorB);
    HDocks[index].dockWidget->setDockWidgetTitleBarButtonColor(MO->SVars.appColorB);
    HDocks[index].textView->setColorScheme();
    if (HDocks[index].textView->textMode == TEXT_MODE__SHOW || HDocks[index].textView->textMode == TEXT_MODE__COMPARE)
    {
      if (HDocks[index].textView->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
        HDocks[index].textView->showBibleText(HDocks[index].textView->currentAbsIndex);
      else // Ако е в режим на ежедневно четене.
        HDocks[index].textView->showBibleText(currentDR_AbsIndex);
    }
  }
  for (int index = 0; index < ODocks.length(); index++)
  {
    ODocks[index].dockWidget->setDockWidgetBgColor(MO->SVars.appColorF);
    ODocks[index].dockWidget->setDockWidgetTitleBarColor(MO->SVars.appColorF);
    ODocks[index].dockWidget->setDockWidgetTitleBarTextColor(MO->SVars.appColorB);
    ODocks[index].dockWidget->setDockWidgetTitleBarButtonColor(MO->SVars.appColorB);
    if (ODocks[index].dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY)
    {
      ODocks[index].dictionary->setDicColorScheme();
    }
  }
  mDockSearch->slotSetColorScheme_AllSearchView();

  booksWidget->slotRefreshPalette();
  bookmarksWidget->slotRefreshPalette();
  mDockSearch->slotRefreshPalette();
}

void MainWindow::fontChanged()
{
  // Този метод променя шрифта по различен, специфичен начин за различните видове изгледи.
  // Ето затова, повечето от долните редове са закоментирани - защото е грешно шрифтът им да се променя по стандартния начин.
  // Въпреки това съм ги оставил за да видя след време (когато забравя какво съм правил), че това не е случайно.

  //QFont font;
  for (int i = 0; i < MO->bibleTextList.size(); i++)
  {
    MO->bibleTextList[i].fontFamily = MO->mergeFontFamilies(MO->bibleTextList[i].nativeFontFamily, MO->SVars.fontFamily);
  }
  //for (int index = 0; index < HDocks.length(); index++) -- Да не се разкоментират!
  //{
  //  font = HDocks[index].textView->font();
  //  font.setFamily(MO->SVars.fontFamily);
  //  HDocks[index].textView->setFont(font);
  //}
  //for (int index = 0; index < ODocks.length(); index++)
  //{
  //  //if (ODocks[index].dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY)
  //  //{
  //  //  // Да се използва един от долните два реда. Подобен ред има и в dictionary.cpp файла в метода LoadDict (ред 161), където също трябва да се избере кой от двата инициализиращи метода да се извиква.
  //  //  ODocks[index].dictionary->setDicFontFamily(MO->SVars.fontFamily); // Това, в случай, че искам шрифта на речника да е като този на Библейските текстове.
  //  //  //ODocks[index].dictionary->setDicFontFamily(); // Това, в случай, че искам шрифта на речника да е като този на системата (== qApp->font().family()).
  //  //}
  //  //else
  //  //{
  //  //  //font = ODocks[index].textView->font();
  //  //  //font.setFamily(MO->SVars.fontFamily);
  //  //  //ODocks[index].textView->setFont(font);
  //  //}
  //}
  //mDockSearch->slotSetFontFamily_AllSearchView(MO->SVars.fontFamily); -- Да не се разкоментират!
}

void MainWindow::fontSizeChanged()
{
  QFont font;
  for (int index = 0; index < HDocks.length(); index++)
  {
    font = HDocks[index].textView->font();
    font.setPointSize(MO->SVars.fontSize);
    HDocks[index].textView->setFont(font);
    HDocks[index].textView->textZoom = 0;
  }
  for (int index = 0; index < ODocks.length(); index++)
  {
    font = ODocks[index].textView->font();
    font.setPointSize(MO->SVars.fontSize);
    ODocks[index].textView->setFont(font);
    ODocks[index].textView->textZoom = 0;
  }
  mDockSearch->slotSetFontSize_AllSearchView(MO->SVars.fontSize, 0);
}

void MainWindow::setTMenuFontSize()
{
  QFont font = bibleTextsToolBar->font();
  font.setPointSize(MO->SVars.otherToolBarFontSize);
  bibleTextsToolBar->setFont(font);
  sessionToolBar->setFont(font);
  audioToolBar->setFont(font);
  QFontMetrics fm(font);
  int tbBtnMargins = MO->SVars.otherToolBarFontSize + 2*(5 + MO->SVars.otherToolBarFontSize/3); // Опитът показва, че горният и долният маргин (разстоянието между надписа на бутона и стените му) се изчисляват най-добре по тази формула за да се показват бутоните добре.
  int lrBtnMargins = 2 * (5 + fm.width(" ")); // Опитът показва, че левият и десният маргин (разстоянието между надписа на бутона и стените му) са равни на 5 точни + широчината на един интервал. Ето защо това разстояние се добавя към дължината на надписа на бутона.
  
  tMenu->setToolBarsHeight(tbBtnMargins); // Това ще бъде височината на всички панели.

  // Audio ToolBar
  audioToolBar->slotSetToolBarFontSize(); // В този метод се правят същите неща като по-долу, но са в отделен метод, защото компонентите са private и не могат да се достъпят от тук.

  // BibleTexts ToolBar
  int panelWidth = 0; // Дължина на панела. Ще се изчисли така, че всички компоненти да се съберат в него.
  for (quint8 i = 0; i < MO->bibleTextList.size(); i++)
  {
    panelWidth += fm.width(bibleTextBtn[i]->text()) + lrBtnMargins;
  }
  panelWidth += fm.width(reorderBibleTextsBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(bibleTextsInfoBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(moreBibleTextsBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(convertBibleTextsBtn->text()) + lrBtnMargins;

  bibleTextsToolBar->resize(panelWidth, tbBtnMargins); // Това ще бъде новият размер на панела. Всички компоненти трябва да се съберат в него.

  // Session ToolBar
  panelWidth = 0; // Дължина на панела. Ще се изчисли така, че всички компоненти да се съберат в него.
  for (quint8 i = 0; i < 9; i++)
  {
    panelWidth += 17; //saveSessionChBox[i]->width();
    panelWidth += fm.width(sessionBtn[i]->text()) + lrBtnMargins;
    panelWidth += 4; // За VSeparator
  }

  sessionToolBar->resize(panelWidth, tbBtnMargins); // Това ще бъде новият размер на панела. Всички компоненти трябва да се съберат в него.
}

void MainWindow::currentHolyTextViewChanged(TextView *newCurrentTextView)
{
  // Тук се определя кой от изгледите е текущ т.е. към кой изглед ще бъдат пренасочени бутоните и панелите.
  // Този изглед може да не е на фокус, но е текущ и всички действия ще се насочват към него (например показване
  // на стих при щракване върху откритите стихове, показване на стих при щракване в панела с книгите и т.н.).
  //
  // newCurrentTextView е обект (който и да е обект), който е станал на фокус в момента.
  // Текущия изглед може да се промени само при смяна на фокуса (било то чрез щракване с мишката или натискане на Esc)
  // или при затваряне на раздел. При затваряне на раздел, задължително на фокус става първият изглед, който не може да се
  // затвори, ако е единствен и гарантирано е там. Ето защо, при затворен раздел, следващият if ще открие, че новият обект,
  // който е на фокус (в случая първият изглед) е различен от обекта (изгледа) към който е сочел currentTextView и ще
  // направи нужните промени.

  if (newCurrentTextView == currentHolyTextView) // Ако на фокус е дошъл изгледът, който е бил текущ и преди (т.е. няма нужда от промени).
  {
    if (currentHolyTextView != 0) currentHolyTextView->setCurrentHolyTextView(true); // Това е старият текущ изглед и няма нужда този метод да се извиква тук, но това се прави за да може да скрие маркера, ако това е единственият останал изглед (проверката за това се прави в този метод).
    return;
  }

  for (int index = 0; index < HDocks.length(); index++) // Търси новия обект в списъка с HolyTextView-тата.
  {
    if (newCurrentTextView == HDocks[index].textView) // Ако това е изгледът, който е на фокус.
    {
      if (currentHolyTextView != 0) currentHolyTextView->setCurrentHolyTextView(false); // Това е старият текущ изглед. Установява го като неактивен (скрива маркера).
      currentHolyTextView = newCurrentTextView; // Насочва към новия.
      currentHolyTextView->setCurrentHolyTextView(true); // Това е новият текущ изглед. Установява го като активен (показва маркера).

      // Сега трябва да се пренасочи всичко към този изглед:
      for (int i = 0; i < MO->bibleTextList.size(); i++)
      {
        bibleTextBtn[i]->setChecked(currentHolyTextView->activeBibleTexts[i]);
      }
      //mainToolBar->btnNavigation_GoBack->setEnabled( currentHolyTextView->backForwardCurrentIndex > 0 );
      //mainToolBar->btnNavigation_GoForward->setEnabled( currentHolyTextView->backForwardCurrentIndex < (currentHolyTextView->backForwardList.count() - 1) );

      bool hasActiveDailyReadMode = false;
      for (int index = 0; index < HDocks.length(); index++) // Проверява дали някой от изгледите е в режим на ежедневно четене.
      {
        if (HDocks[index].textView->readMode == READ_MODE__DAILY_READ) // Ако е в режим на ежедневно четене.
        {
          hasActiveDailyReadMode = true;
          break;
        }
      }
      if (currentHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене (не ежедневно).
      {
        booksWidget->setCurrentCodes(MO->toBookCode(currentHolyTextView->currentAbsIndex), MO->toChapterCode(currentHolyTextView->currentAbsIndex));
      
        mainToolBar->btnNavigation_DailyRead->setEnabled(!hasActiveDailyReadMode);
        mainToolBar->showDailyReadPanel(false);
        audioToolBar->enableButtonPlayGroup(false);
      }
      else //if (currentHolyTextView->readMode == READ_MODE__DAILY_READ) // Ако е в режим на ежедневно четене.
      {
        booksWidget->setCurrentCodes(MO->toBookCode(currentDR_AbsIndex), MO->toChapterCode(currentDR_AbsIndex));
      
        mainToolBar->btnNavigation_DailyRead->setEnabled(true);
        mainToolBar->showDailyReadPanel(true);
        audioToolBar->enableButtonPlayGroup(true);
      }
      break;
    }
  }
}

void MainWindow::currentTextViewChanged(TextView *newCurrentTextView)
{
  currentTextView = newCurrentTextView;
  if (currentTextView == 0) return;

  currentHolyTextViewChanged(currentTextView); // Тук ще бъде сменен (ако е необходимо) текущия изглед, показващ текст от Библията.

  // Показва действията в главното меню само на текстовото поле, което е на фокус и съответно скрива другите.
  if (currentTextView == currentHolyTextView) // Ако някой от HolyTextView-тата е станал на фокус.
  {
    disconnect(mainToolBar->btnText_SearchInTextPrevious, 0, 0, 0); connect(mainToolBar->btnText_SearchInTextPrevious, SIGNAL(clicked()), currentHolyTextView, SLOT(slotFindPrevious()));
    disconnect(mainToolBar->btnText_SearchInTextNext, 0, 0, 0);     connect(mainToolBar->btnText_SearchInTextNext, SIGNAL(clicked()), currentHolyTextView, SLOT(slotFindNext()));
    disconnect(mainToolBar->btnFile_FileMenu, 0, 0, 0);             connect(mainToolBar->btnFile_FileMenu, SIGNAL(clicked()), currentHolyTextView, SLOT(slotShowFileMenu()));
  }
  else if (currentTextView == mDockSearch->currentSearchWidget->searchView) // Ако някой от searchView-тата е на фокус.
  {
    disconnect(mainToolBar->btnText_SearchInTextPrevious, 0, 0, 0); connect(mainToolBar->btnText_SearchInTextPrevious, SIGNAL(clicked()), mDockSearch->currentSearchWidget->searchView, SLOT(slotFindPrevious()));
    disconnect(mainToolBar->btnText_SearchInTextNext, 0, 0, 0);     connect(mainToolBar->btnText_SearchInTextNext, SIGNAL(clicked()), mDockSearch->currentSearchWidget->searchView, SLOT(slotFindNext()));
    disconnect(mainToolBar->btnFile_FileMenu, 0, 0, 0);             connect(mainToolBar->btnFile_FileMenu, SIGNAL(clicked()), mDockSearch->currentSearchWidget->searchView, SLOT(slotShowFileMenu()));
  }
  else if (currentTextView != 0) // Ако друг обект е на фокус.
  {
    int index = -1;
    for (int i = 0; i < ODocks.length(); i++)
    {
      if (currentTextView == ODocks[i].textView)
      {
        index = i;
        break;
      }
    }
    if (index >= 0)
    {
      disconnect(mainToolBar->btnText_SearchInTextPrevious, 0, 0, 0); connect(mainToolBar->btnText_SearchInTextPrevious, SIGNAL(clicked()), ODocks[index].textView, SLOT(slotFindPrevious()));
      disconnect(mainToolBar->btnText_SearchInTextNext, 0, 0, 0);     connect(mainToolBar->btnText_SearchInTextNext, SIGNAL(clicked()), ODocks[index].textView, SLOT(slotFindNext()));
      disconnect(mainToolBar->btnFile_FileMenu, 0, 0, 0);             connect(mainToolBar->btnFile_FileMenu, SIGNAL(clicked()), ODocks[index].textView, SLOT(slotShowFileMenu()));
    }
    else
    {
      if (mDockSearch != 0 && mDockSearch->isVisible())
      {
        disconnect(mainToolBar->btnFile_FileMenu, 0, 0, 0);
      }
    }
  }
}

void MainWindow::setProjectorText(QString bibleText, QString chapter, QString verse, quint16 absIndex, QBitArray *activeBibleTexts, quint16 position)
{
  if (!mDockProjector->isVisible()) return;
  if (position >= activeBibleTexts->size()) return;
  
  int index = -1;
  for (int i = 0; i < activeBibleTexts->size(); i++)
  {
    if (activeBibleTexts->at(i)) index++;
    if (index == position)
    {
      projectorWidget->setScreenText(bibleText, chapter, verse, absIndex, MO->bibleTextList[i].fontFamily);
      return;
    }
  }
}

void MainWindow::showStatusBarMessage(QString message, int timeout)
{
  statusBar->show();
  statusBar->showMessage(message, timeout);
}
