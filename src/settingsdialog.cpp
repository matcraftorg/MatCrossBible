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

#include "settingsdialog.h"

SettingsDialog::SettingsDialog(MainWindow *MW) : QDialog(MW)
{
  this->MW = MW;
  setMinimumSize(10, 10);
  resize(450, 530);
  
  // Настройките които могат да се променят:
  // Language
  SVars.currentAppTranslation    = MW->MO->TS->currentAppTranslation;
  SVars.currentBooksTranslation  = MW->MO->SVars.currentBooksTranslation;
  // Colors
  SVars.dock1TextColorF          = MW->MO->SVars.dock1TextColorF;
  SVars.dock1TextColorB          = MW->MO->SVars.dock1TextColorB;
  SVars.dock1BGImage             = MW->MO->SVars.dock1BGImage;
  SVars.dock2TextColorF          = MW->MO->SVars.dock2TextColorF;
  SVars.dock2TextColorB          = MW->MO->SVars.dock2TextColorB;
  SVars.dock2BGImage             = MW->MO->SVars.dock2BGImage;
  SVars.oldTestamentColorF       = MW->MO->SVars.oldTestamentColorF;
  SVars.newTestamentColorF       = MW->MO->SVars.newTestamentColorF;
  SVars.oldTestamentAlphaF       = MW->MO->SVars.oldTestamentAlphaF;
  SVars.newTestamentAlphaF       = MW->MO->SVars.newTestamentAlphaF;
  SVars.textInBracketsColorF     = MW->MO->SVars.textInBracketsColorF;
  SVars.JesusWordsColorF         = MW->MO->SVars.JesusWordsColorF;
  SVars.JesusWordsColorFEnable   = MW->MO->SVars.JesusWordsColorFEnable;
  SVars.compareEqColorF          = MW->MO->SVars.compareEqColorF;
  SVars.compareNoEqColorF        = MW->MO->SVars.compareNoEqColorF;
  SVars.appColorF                = MW->MO->SVars.appColorF;
  SVars.appColorB                = MW->MO->SVars.appColorB;
  SVars.docks3DTitleBar          = MW->MO->SVars.docks3DTitleBar;
  // View
  SVars.TMenuPosition            = MW->MO->SVars.TMenuPosition;
  SVars.TMenuIconSize            = MW->MO->SVars.TMenuIconSize;
  SVars.otherToolBarFontSize     = MW->MO->SVars.otherToolBarFontSize;
  SVars.booksToolBarPosition     = MW->MO->SVars.booksToolBarPosition;
  SVars.booksToolBarFontSize     = MW->MO->SVars.booksToolBarFontSize;
  SVars.searchToolBarPosition    = MW->MO->SVars.searchToolBarPosition;
  SVars.searchToolBarWidth       = MW->MO->SVars.searchToolBarWidth;
  SVars.searchToolBarFontSize    = MW->MO->SVars.searchToolBarFontSize;
  SVars.projectorToolBarPosition = MW->MO->SVars.projectorToolBarPosition;
  SVars.projectorToolBarPrevSize = MW->MO->SVars.projectorToolBarPrevSize;
  SVars.projectorToolBarFontSize = MW->MO->SVars.projectorToolBarFontSize;
  SVars.GUIStyle                 = MW->MO->SVars.GUIStyle;
  // Text
  SVars.globalFontSize           = MW->MO->SVars.globalFontSize;
  SVars.globalFontAntialias      = MW->MO->SVars.globalFontAntialias;
  SVars.fontFamily               = MW->MO->SVars.fontFamily;
  SVars.fontSize                 = MW->MO->SVars.fontSize;
  SVars.verseNumberBold          = MW->MO->SVars.verseNumberBold;
  SVars.verseNumberSup           = MW->MO->SVars.verseNumberSup;
  SVars.verseStruct              = MW->MO->SVars.verseStruct;
  SVars.newNumeration            = MW->MO->SVars.newNumeration;
  SVars.newBooksOrder            = MW->MO->SVars.newBooksOrder;
  SVars.newShowDeuterocanonical  = MW->MO->SVars.newShowDeuterocanonical;
  SVars.showAbsVerseNumber       = MW->MO->SVars.showAbsVerseNumber;
  // Search
  SVars.foundWordsBold           = MW->MO->SVars.foundWordsBold;
  SVars.foundWordsUnderline      = MW->MO->SVars.foundWordsUnderline;
  SVars.foundWordsColorF         = MW->MO->SVars.foundWordsColorF;
  SVars.foundWordsColorB         = MW->MO->SVars.foundWordsColorB;
  SVars.foundWordsColor1F        = MW->MO->SVars.foundWordsColor1F;
  SVars.foundWordsColor2F        = MW->MO->SVars.foundWordsColor2F;
  SVars.foundWordsColor3F        = MW->MO->SVars.foundWordsColor3F;
  SVars.foundWordsColor4F        = MW->MO->SVars.foundWordsColor4F;
  SVars.foundWordsColor5F        = MW->MO->SVars.foundWordsColor5F;
  SVars.foundWordsColor1B        = MW->MO->SVars.foundWordsColor1B;
  SVars.foundWordsColor2B        = MW->MO->SVars.foundWordsColor2B;
  SVars.foundWordsColor3B        = MW->MO->SVars.foundWordsColor3B;
  SVars.foundWordsColor4B        = MW->MO->SVars.foundWordsColor4B;
  SVars.foundWordsColor5B        = MW->MO->SVars.foundWordsColor5B;
  SVars.extraSelectColor1B       = MW->MO->SVars.extraSelectColor1B;
  SVars.extraSelectColor2B       = MW->MO->SVars.extraSelectColor2B;
  // Audio
  // Other
  SVars.pathToSettings           = MW->MO->SVars.pathToSettings;
  SVars.MatCrossBibleURL         = MW->MO->SVars.MatCrossBibleURL;
  SVars.proxyType                = MW->MO->SVars.proxyType;
  SVars.proxyHostName            = MW->MO->SVars.proxyHostName;
  SVars.proxyPort                = MW->MO->SVars.proxyPort;
  SVars.enableTrayIcon           = MW->MO->SVars.enableTrayIcon;

  effectAfterRestart = false;
  effectAfterChange = false;

  QScrollArea *languageScrollArea = new QScrollArea;
  languageScrollArea->setMinimumSize(10, 10);
  languageScrollArea->setWidgetResizable(true);
  LanguageTab *languageTab = new LanguageTab(&SVars, MW, languageScrollArea);
  languageScrollArea->setWidget(languageTab);

  QScrollArea *colorsScrollArea = new QScrollArea;
  colorsScrollArea->setMinimumSize(10, 10);
  colorsScrollArea->setWidgetResizable(true);
  ColorsTab *colorsTab = new ColorsTab(&SVars, MW, colorsScrollArea);
  colorsScrollArea->setWidget(colorsTab);


  QScrollArea *viewScrollArea = new QScrollArea;
  viewScrollArea->setMinimumSize(10, 10);
  viewScrollArea->setWidgetResizable(true);
  ViewTab *viewTab = new ViewTab(&SVars, MW, viewScrollArea);
  viewScrollArea->setWidget(viewTab);


  QScrollArea *textScrollArea = new QScrollArea;
  textScrollArea->setMinimumSize(10, 10);
  textScrollArea->setWidgetResizable(true);
  TextTab *textTab = new TextTab(&SVars, MW, textScrollArea);
  textScrollArea->setWidget(textTab);


  QScrollArea *searchScrollArea = new QScrollArea;
  searchScrollArea->setMinimumSize(10, 10);
  searchScrollArea->setWidgetResizable(true);
  SearchTab *searchTab = new SearchTab(&SVars, MW, searchScrollArea);
  searchScrollArea->setWidget(searchTab);


  QScrollArea *otherScrollArea = new QScrollArea;
  otherScrollArea->setMinimumSize(10, 10);
  otherScrollArea->setWidgetResizable(true);
  OtherTab *otherTab = new OtherTab(&SVars, MW, otherScrollArea);
  otherScrollArea->setWidget(otherTab);

  tabWidget = new QTabWidget;
  tabWidget->addTab(languageScrollArea, MW->MO->TS->TabLanguage_v1);
  tabWidget->addTab(colorsScrollArea, MW->MO->TS->TabColors_v1);
  tabWidget->addTab(viewScrollArea, MW->MO->TS->TabView_v1);
  tabWidget->addTab(textScrollArea, MW->MO->TS->TabText_v1);
  tabWidget->addTab(searchScrollArea, MW->MO->TS->TabSearch_v1);
  tabWidget->addTab(otherScrollArea, MW->MO->TS->TabMisc_v1);

  buttomBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  connect(buttomBox, SIGNAL(accepted()), this, SLOT(slotAccept())); // accept()
  connect(buttomBox, SIGNAL(rejected()), this, SLOT(slotReject())); // reject()

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttomBox);
  setLayout(mainLayout);

  setWindowTitle(MW->MO->TS->Settings_v1 + " - " + QCoreApplication::applicationName());
}

void SettingsDialog::slotAccept()
{
  // Language
  if (MW->MO->TS->currentAppTranslation != SVars.currentAppTranslation)
  {
    effectAfterRestart = true;
    MW->MO->TS->currentAppTranslation = SVars.currentAppTranslation;
    MW->MO->TS->saveCurrentAppTranslationToSettings();
  }
  if (MW->MO->SVars.currentBooksTranslation != SVars.currentBooksTranslation) effectAfterRestart = true;
  // Colors
  if (MW->MO->SVars.dock1TextColorF != SVars.dock1TextColorF) effectAfterChange = true;
  if (MW->MO->SVars.dock1TextColorB != SVars.dock1TextColorB) effectAfterChange = true;
  if (MW->MO->SVars.dock1BGImage != SVars.dock1BGImage) effectAfterChange = true;
  if (MW->MO->SVars.dock2TextColorF != SVars.dock2TextColorF) effectAfterChange = true;
  if (MW->MO->SVars.dock2TextColorB != SVars.dock2TextColorB) effectAfterChange = true;
  if (MW->MO->SVars.dock2BGImage != SVars.dock2BGImage) effectAfterChange = true;
  if (MW->MO->SVars.oldTestamentColorF != SVars.oldTestamentColorF) effectAfterChange = true;
  if (MW->MO->SVars.newTestamentColorF != SVars.newTestamentColorF) effectAfterChange = true;
  if (MW->MO->SVars.oldTestamentAlphaF != SVars.oldTestamentAlphaF) effectAfterChange = true;
  if (MW->MO->SVars.newTestamentAlphaF != SVars.newTestamentAlphaF) effectAfterChange = true;
  if (MW->MO->SVars.textInBracketsColorF != SVars.textInBracketsColorF) effectAfterChange = true;
  if (MW->MO->SVars.JesusWordsColorF != SVars.JesusWordsColorF) effectAfterChange = true;
  if (MW->MO->SVars.JesusWordsColorFEnable != SVars.JesusWordsColorFEnable) effectAfterChange = true;
  if (MW->MO->SVars.compareEqColorF != SVars.compareEqColorF) effectAfterChange = true;
  if (MW->MO->SVars.compareNoEqColorF != SVars.compareNoEqColorF) effectAfterChange = true;
  if (MW->MO->SVars.appColorF != SVars.appColorF) effectAfterChange = true;
  if (MW->MO->SVars.appColorB != SVars.appColorB) effectAfterChange = true;
  // View
  if (MW->MO->SVars.TMenuPosition != SVars.TMenuPosition) effectAfterRestart = true;
  if (MW->MO->SVars.TMenuIconSize != SVars.TMenuIconSize) effectAfterRestart = true;
  if (MW->MO->SVars.booksToolBarPosition != SVars.booksToolBarPosition) effectAfterRestart = true;
  if (MW->MO->SVars.searchToolBarPosition != SVars.searchToolBarPosition) effectAfterRestart = true;
  if (MW->MO->SVars.projectorToolBarPosition != SVars.projectorToolBarPosition) effectAfterRestart = true;
  if (MW->MO->SVars.GUIStyle != SVars.GUIStyle) effectAfterRestart = true;
  // Text
  if (MW->MO->SVars.fontFamily != SVars.fontFamily) effectAfterChange = true;
  if (MW->MO->SVars.verseNumberBold != SVars.verseNumberBold) effectAfterChange = true;
  if (MW->MO->SVars.verseNumberSup != SVars.verseNumberSup) effectAfterChange = true;
  if (MW->MO->SVars.verseStruct != SVars.verseStruct) effectAfterChange = true;
  if (MW->MO->SVars.newNumeration != SVars.newNumeration) effectAfterRestart = true;
  if (MW->MO->SVars.newBooksOrder != SVars.newBooksOrder) effectAfterRestart = true;
  if (MW->MO->SVars.newShowDeuterocanonical != SVars.newShowDeuterocanonical) effectAfterRestart = true;
  if (MW->MO->SVars.showAbsVerseNumber != SVars.showAbsVerseNumber) effectAfterChange = true;
  // Search
  if (MW->MO->SVars.foundWordsBold != SVars.foundWordsBold) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsUnderline != SVars.foundWordsUnderline) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColorF != SVars.foundWordsColorF) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColorB != SVars.foundWordsColorB) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor1F != SVars.foundWordsColor1F) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor2F != SVars.foundWordsColor2F) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor3F != SVars.foundWordsColor3F) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor4F != SVars.foundWordsColor4F) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor5F != SVars.foundWordsColor5F) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor1B != SVars.foundWordsColor1B) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor2B != SVars.foundWordsColor2B) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor3B != SVars.foundWordsColor3B) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor4B != SVars.foundWordsColor4B) effectAfterChange = true;
  if (MW->MO->SVars.foundWordsColor5B != SVars.foundWordsColor5B) effectAfterChange = true;
  if (MW->MO->SVars.extraSelectColor1B != SVars.extraSelectColor1B) effectAfterChange = true;
  if (MW->MO->SVars.extraSelectColor2B != SVars.extraSelectColor2B) effectAfterChange = true;
  // Audio
  // Other
  if (!SVars.pathToSettings.isEmpty() && MW->MO->SVars.pathToSettings != SVars.pathToSettings) effectAfterRestart = true; // Ако е избрано Other, но не е избрана директория, няма да има ефект.

  
  // Language
  MW->MO->SVars.currentBooksTranslation  = SVars.currentBooksTranslation;
  // Colors
  MW->MO->SVars.dock1TextColorF          = SVars.dock1TextColorF;
  MW->MO->SVars.dock1TextColorB          = SVars.dock1TextColorB;
  MW->MO->SVars.dock1BGImage             = SVars.dock1BGImage;
  MW->MO->SVars.dock2TextColorF          = SVars.dock2TextColorF;
  MW->MO->SVars.dock2TextColorB          = SVars.dock2TextColorB;
  MW->MO->SVars.dock2BGImage             = SVars.dock2BGImage;
  MW->MO->SVars.oldTestamentColorF       = SVars.oldTestamentColorF;
  MW->MO->SVars.oldTestamentColorFA      = SVars.oldTestamentColorF;     MW->MO->SVars.oldTestamentColorFA.setAlphaF(0.6); //setAlpha(150);
  MW->MO->SVars.newTestamentColorF       = SVars.newTestamentColorF;
  MW->MO->SVars.oldTestamentAlphaF       = SVars.oldTestamentAlphaF;
  MW->MO->SVars.newTestamentAlphaF       = SVars.newTestamentAlphaF;
  MW->MO->SVars.textInBracketsColorF     = SVars.textInBracketsColorF;
  MW->MO->SVars.JesusWordsColorF         = SVars.JesusWordsColorF;
  MW->MO->SVars.JesusWordsColorFEnable   = SVars.JesusWordsColorFEnable;
  MW->MO->SVars.compareEqColorF          = SVars.compareEqColorF;
  MW->MO->SVars.compareNoEqColorF        = SVars.compareNoEqColorF;
  MW->MO->SVars.appColorF                = SVars.appColorF;
  MW->MO->SVars.appColorB                = SVars.appColorB;
  MW->MO->SVars.docks3DTitleBar          = SVars.docks3DTitleBar;
  // View
  MW->MO->SVars.TMenuPosition            = SVars.TMenuPosition;
  MW->MO->SVars.TMenuIconSize            = SVars.TMenuIconSize;
  MW->MO->SVars.otherToolBarFontSize     = SVars.otherToolBarFontSize;
  MW->MO->SVars.booksToolBarPosition     = SVars.booksToolBarPosition;
  MW->MO->SVars.booksToolBarFontSize     = SVars.booksToolBarFontSize;
  MW->MO->SVars.searchToolBarPosition    = SVars.searchToolBarPosition;
  MW->MO->SVars.searchToolBarWidth       = SVars.searchToolBarWidth;
  MW->MO->SVars.searchToolBarFontSize    = SVars.searchToolBarFontSize;
  MW->MO->SVars.projectorToolBarPosition = SVars.projectorToolBarPosition;
  MW->MO->SVars.projectorToolBarPrevSize = SVars.projectorToolBarPrevSize;
  MW->MO->SVars.projectorToolBarFontSize = SVars.projectorToolBarFontSize;
  MW->MO->SVars.GUIStyle                 = SVars.GUIStyle;
  // Text
  MW->MO->SVars.globalFontSize           = SVars.globalFontSize;
  MW->MO->SVars.globalFontAntialias      = SVars.globalFontAntialias;
  if (MW->MO->SVars.fontFamily != SVars.fontFamily)
  {
    MW->MO->SVars.fontFamily             = SVars.fontFamily;
    MW->fontChanged(); // По-долу ще бъде извикан методът MW->colorChanged(), който ще предизвика рефреш и ще се смени и шрифта.
  }
  MW->MO->SVars.fontSize                 = SVars.fontSize;
  MW->MO->SVars.verseNumberBold          = SVars.verseNumberBold;
  MW->MO->SVars.verseNumberSup           = SVars.verseNumberSup;
  MW->MO->SVars.verseStruct              = SVars.verseStruct;
  MW->MO->SVars.newNumeration            = SVars.newNumeration;
  MW->MO->SVars.newBooksOrder            = SVars.newBooksOrder;
  MW->MO->SVars.newShowDeuterocanonical  = SVars.newShowDeuterocanonical;
  MW->MO->SVars.showAbsVerseNumber       = SVars.showAbsVerseNumber;
  // Search
  MW->MO->SVars.foundWordsBold           = SVars.foundWordsBold;
  MW->MO->SVars.foundWordsUnderline      = SVars.foundWordsUnderline;
  MW->MO->SVars.foundWordsColorF         = SVars.foundWordsColorF;
  MW->MO->SVars.foundWordsColorB         = SVars.foundWordsColorB;
  MW->MO->SVars.foundWordsColor1F        = SVars.foundWordsColor1F;
  MW->MO->SVars.foundWordsColor2F        = SVars.foundWordsColor2F;
  MW->MO->SVars.foundWordsColor3F        = SVars.foundWordsColor3F;
  MW->MO->SVars.foundWordsColor4F        = SVars.foundWordsColor4F;
  MW->MO->SVars.foundWordsColor5F        = SVars.foundWordsColor5F;
  MW->MO->SVars.foundWordsColor1B        = SVars.foundWordsColor1B;
  MW->MO->SVars.foundWordsColor2B        = SVars.foundWordsColor2B;
  MW->MO->SVars.foundWordsColor3B        = SVars.foundWordsColor3B;
  MW->MO->SVars.foundWordsColor4B        = SVars.foundWordsColor4B;
  MW->MO->SVars.foundWordsColor5B        = SVars.foundWordsColor5B;
  MW->MO->SVars.extraSelectColor1B       = SVars.extraSelectColor1B;
  MW->MO->SVars.extraSelectColor2B       = SVars.extraSelectColor2B;
  // Audio
  // Other
  if (!SVars.pathToSettings.isEmpty() && MW->MO->SVars.pathToSettings != SVars.pathToSettings)
  {
    MW->MO->createPathToSettingsIniFile(SVars.pathToSettings); // Създава (презаписва) PathToSettings.ini файла с новия път.
    // Тук MW->MO->SVars.pathToSettings все още сочи към стария път и тук е мястото да се направи копие на всички файлове в новата директория, ако е празна:
    QDir dir;
    if (!QDir(QString("%1/Config").arg(SVars.pathToSettings)).exists()) // Само ако тази директория не съществува!
    {
      dir.mkpath(QString("%1/Config").arg(SVars.pathToSettings));
      QFile::copy(MW->MO->SVars.pathToSettings + "/Config/MatCrossBible.ini", SVars.pathToSettings + "/Config/MatCrossBible.ini");
      QFile::copy(MW->MO->SVars.pathToSettings + "/Config/MatCrossBible.Sessions.ini", SVars.pathToSettings + "/Config/MatCrossBible.Sessions.ini");
    }
    if (!QDir(QString("%1/Pad").arg(SVars.pathToSettings)).exists()) // Само ако тази директория не съществува!
    {
      dir.mkpath(QString("%1/Pad").arg(SVars.pathToSettings));
      QFile::copy(MW->MO->SVars.pathToSettings + "/Pad/Pad.txt", SVars.pathToSettings + "/Pad/Pad.txt");
    }
    if (!QDir(QString("%1/Resources").arg(SVars.pathToSettings)).exists()) // Само ако тази директория не съществува!
    {
      dir.mkpath(QString("%1/Resources").arg(SVars.pathToSettings));
      QFile::copy(MW->MO->SVars.pathToSettings + "/Resources/WWWResources.txt", SVars.pathToSettings + "/Resources/WWWResources.txt");
    }
    MW->MO->SVars.pathToSettings         = SVars.pathToSettings;
  }
  MW->MO->SVars.proxyType                = SVars.proxyType;
  MW->MO->SVars.proxyHostName            = SVars.proxyHostName;
  MW->MO->SVars.proxyPort                = SVars.proxyPort;
  MW->MO->SVars.enableTrayIcon           = SVars.enableTrayIcon;

  if (effectAfterRestart && effectAfterChange)
    QMessageBox::information(this, MW->MO->TS->Settings_v1, MW->MO->TS->EffectAfterChangeOrRestart_v1);
  else if (effectAfterRestart)
    QMessageBox::information(this, MW->MO->TS->Settings_v1, MW->MO->TS->EffectAfterRestart_v1);
  else if (effectAfterChange)
    QMessageBox::information(this, MW->MO->TS->Settings_v1, MW->MO->TS->EffectAfterChange_v1);

  if (effectAfterChange) MW->colorChanged(); // Това ще извика и ShowBibleText за всеки раздел, така че освен цветовете ще се рефрешне и номерът и начинът на изписване на стиховете. Други неща, като резултатите от търсенето няма да се рефрешнат, но това не е фатално.

  if (effectAfterRestart) MW->needToRestart = true; // Вдига, но не сваля флага.

  accept(); // Вътрешният слот accept.
}

void SettingsDialog::slotReject()
{
  reject(); // Вътрешният слот reject.
}




// Language ---------------------------------------------------------------------------------------------------------------------------------------------------------
LanguageTab::LanguageTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;

  QGroupBox *appLanguageGroup = new QGroupBox("Application Language"); // Това трябва да е винаги на английски.

  appLanguageListWidget = new QListWidget(this);
  appLanguageListWidget->addItems(MW->MO->TS->allAppTranslation);
  appLanguageListWidget->addItem("<<< More >>>");
  appLanguageListWidget->setCurrentRow(MW->MO->TS->allAppTranslation.indexOf(SVars->currentAppTranslation));
  appLanguageListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  appLanguageListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  appLanguageListWidget->setMinimumSize(10, 10);
  appLanguageListWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(appLanguageListWidget, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotAppLanguage(const QString &)));

  QVBoxLayout *appLanguageLayout = new QVBoxLayout;
  appLanguageLayout->addWidget(appLanguageListWidget);
  appLanguageGroup->setLayout(appLanguageLayout);


  QGroupBox *booksLanguageGroup = new QGroupBox("Bible Books Language"); // Това трябва да е винаги на английски.

  booksLanguageListWidget = new QListWidget(this);
  booksLanguageListWidget->addItem("<<< From App. Language >>>"); // <<< Auto >>>
  booksLanguageListWidget->addItems(MW->MO->TS->allBooksTranslation);
  booksLanguageListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  booksLanguageListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  booksLanguageListWidget->setMinimumSize(10, 10);
  booksLanguageListWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(booksLanguageListWidget, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotBooksLanguage(const QString &)));

  if (MW->MO->TS->allBooksTranslation.contains(SVars->currentBooksTranslation)) // Тази проверка е вече направена в MO и тук може да се провери само дали currentBooksTranslation е празен.
  {
    booksLanguageListWidget->setCurrentRow(MW->MO->TS->allBooksTranslation.indexOf(SVars->currentBooksTranslation) + 1);
  }
  else
  {
    booksLanguageListWidget->setCurrentRow(0);
  }

  QVBoxLayout *booksLanguageLayout = new QVBoxLayout;
  booksLanguageLayout->addWidget(booksLanguageListWidget);
  booksLanguageGroup->setLayout(booksLanguageLayout);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addWidget(appLanguageGroup);
  mainLayout->addWidget(booksLanguageGroup);
  setLayout(mainLayout);
}

void LanguageTab::slotAppLanguage(const QString &language)
{
  if (appLanguageListWidget->currentRow() == (appLanguageListWidget->count()-1)) // Ако е избран <<< More >>>.
  {
    MoreTRFilesWindow *mtrfw = new MoreTRFilesWindow(MW);
    mtrfw->setWindowModality(Qt::ApplicationModal); // Qt::WindowModal   Qt::ApplicationModal
    mtrfw->show();
    connect(mtrfw, SIGNAL(downloadTRFileFinished()), this, SLOT(slotDownloadTRFileFinished()));

    QTimer::singleShot(200, this, SLOT(slotSelectOldLanguage())); // Това ще върне селекцията върху текущия език. Само с таймер може да се направи, защото иначе селектира текущия език, а след това този слот приключва и селектира отново последния ред.

    return;
  }

  SVars->currentAppTranslation = language;
}

void LanguageTab::slotSelectOldLanguage()
{
  //appLanguageListWidget->disconnect();
  appLanguageListWidget->setCurrentRow(MW->MO->TS->allAppTranslation.indexOf(SVars->currentAppTranslation)); // Селектира текущия избран език, за да не остане селектиран ред <<< More >>>.
  //connect(appLanguageListWidget, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotAppLanguage(const QString &)));
}

void LanguageTab::slotDownloadTRFileFinished()
{
  MW->MO->TS->setAllAppTranslation(); // Реинициализира allAppTranslation списъка за да се добави евентуално новият изтеглен TR файл.
  appLanguageListWidget->disconnect();
  appLanguageListWidget->clear();
  appLanguageListWidget->addItems(MW->MO->TS->allAppTranslation);
  appLanguageListWidget->addItem("<<< More >>>");
  appLanguageListWidget->setCurrentRow(MW->MO->TS->allAppTranslation.indexOf(SVars->currentAppTranslation)); // Селектира текущия избран език, за да не остане селектиран ред <<< More >>>.
  connect(appLanguageListWidget, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotAppLanguage(const QString &)));

}

void LanguageTab::slotBooksLanguage(const QString &language)
{
  if (booksLanguageListWidget->currentRow() == 0) // Ако е избрано от TS файла.
    SVars->currentBooksTranslation = "";
  else
    SVars->currentBooksTranslation = language;
}




// Colors ---------------------------------------------------------------------------------------------------------------------------------------------------------
ColorsTab::ColorsTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;

  QPixmap pix(16, 16);

  QLabel *dock1TextColorFLabel = new QLabel(MW->MO->TS->TCDock1TextColorF_v1);
  dock1TextColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  dock1TextColorFBtn = new QToolButton(this);
  dock1TextColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->dock1TextColorF);
  dock1TextColorFBtn->setIcon(pix);
  connect(dock1TextColorFBtn, SIGNAL(clicked()), this, SLOT(slotDock1TextColorF()));

  QLabel *dock1TextColorBLabel = new QLabel(MW->MO->TS->TCDock1TextColorB_v1);
  dock1TextColorBLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  dock1TextColorBBtn = new QToolButton(this);
  dock1TextColorBBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->dock1TextColorB);
  dock1TextColorBBtn->setIcon(pix);
  connect(dock1TextColorBBtn, SIGNAL(clicked()), this, SLOT(slotDock1TextColorB()));

  dock1BGImageCheckBox = new QCheckBox(MW->MO->TS->TCDockBGImage_v1, this);
  dock1BGImageCheckBox->setToolTip(MW->MO->TS->TCDockBGImageTT_v1);
  if (!SVars->dock1BGImage.isEmpty()) dock1BGImageCheckBox->setChecked(true);
  connect(dock1BGImageCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotDock1BGImage_Toggled(bool)));

  QLabel *dock2TextColorFLabel = new QLabel(MW->MO->TS->TCDock2TextColorF_v1);
  dock2TextColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  dock2TextColorFBtn = new QToolButton(this);
  dock2TextColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->dock2TextColorF);
  dock2TextColorFBtn->setIcon(pix);
  connect(dock2TextColorFBtn, SIGNAL(clicked()), this, SLOT(slotDock2TextColorF()));

  QLabel *dock2TextColorBLabel = new QLabel(MW->MO->TS->TCDock2TextColorB_v1);
  dock2TextColorBLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  dock2TextColorBBtn = new QToolButton(this);
  dock2TextColorBBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->dock2TextColorB);
  dock2TextColorBBtn->setIcon(pix);
  connect(dock2TextColorBBtn, SIGNAL(clicked()), this, SLOT(slotDock2TextColorB()));

  dock2BGImageCheckBox = new QCheckBox(MW->MO->TS->TCDockBGImage_v1, this);
  dock2BGImageCheckBox->setToolTip(MW->MO->TS->TCDockBGImageTT_v1);
  if (!SVars->dock2BGImage.isEmpty()) dock2BGImageCheckBox->setChecked(true);
  connect(dock2BGImageCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotDock2BGImage_Toggled(bool)));

  QLabel *oldTestamentColorFLabel = new QLabel(MW->MO->TS->TCOldTestamentColorF_v1);
  oldTestamentColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  oldTestamentColorFBtn = new QToolButton(this);
  oldTestamentColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->oldTestamentColorF);
  oldTestamentColorFBtn->setIcon(pix);
  connect(oldTestamentColorFBtn, SIGNAL(clicked()), this, SLOT(slotOldTestamentColorF()));

  oldTestamentAlphaFSpinBox = new QSpinBox(this);
  oldTestamentAlphaFSpinBox->setToolTip(MW->MO->TS->TCOldTestamentAlphaFTT_v1);
  oldTestamentAlphaFSpinBox->setMaximum(255);
  oldTestamentAlphaFSpinBox->setValue(MW->MO->SVars.oldTestamentAlphaF);
  connect(oldTestamentAlphaFSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotOldTestamentAlphaF_valueChanged(int)));

  QLabel *newTestamentColorFLabel = new QLabel(MW->MO->TS->TCNewTestamentColorF_v1);
  newTestamentColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  newTestamentColorFBtn = new QToolButton(this);
  newTestamentColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->newTestamentColorF);
  newTestamentColorFBtn->setIcon(pix);
  connect(newTestamentColorFBtn, SIGNAL(clicked()), this, SLOT(slotNewTestamentColorF()));

  newTestamentAlphaFSpinBox = new QSpinBox(this);
  newTestamentAlphaFSpinBox->setToolTip(MW->MO->TS->TCNewTestamentAlphaFTT_v1);
  newTestamentAlphaFSpinBox->setMaximum(255);
  newTestamentAlphaFSpinBox->setValue(MW->MO->SVars.newTestamentAlphaF);
  connect(newTestamentAlphaFSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotNewTestamentAlphaF_valueChanged(int)));

  QLabel *textInBracketsColorFLabel = new QLabel(MW->MO->TS->TCTextInBracketsColorF_v1);
  textInBracketsColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  textInBracketsColorFBtn = new QToolButton(this);
  textInBracketsColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->textInBracketsColorF);
  textInBracketsColorFBtn->setIcon(pix);
  connect(textInBracketsColorFBtn, SIGNAL(clicked()), this, SLOT(slotTextInBracketsColorF()));

  JesusWordsColorFEnableCheckBox = new QCheckBox(MW->MO->TS->TCJesusWordsColorF_v1);
  JesusWordsColorFEnableCheckBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  if (SVars->JesusWordsColorFEnable) JesusWordsColorFEnableCheckBox->setChecked(true);
  connect(JesusWordsColorFEnableCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotJesusWordsColorFEnable_Toggled(bool)));
  JesusWordsColorFBtn = new QToolButton(this);
  JesusWordsColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->JesusWordsColorF);
  JesusWordsColorFBtn->setIcon(pix);
  connect(JesusWordsColorFBtn, SIGNAL(clicked()), this, SLOT(slotJesusWordsColorF()));
  JesusWordsColorFBtn->setEnabled(SVars->JesusWordsColorFEnable);

  QLabel *compareEqColorFLabel = new QLabel(MW->MO->TS->TCCompareEqColorF_v1);
  compareEqColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  compareEqColorFBtn = new QToolButton(this);
  compareEqColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->compareEqColorF);
  compareEqColorFBtn->setIcon(pix);
  connect(compareEqColorFBtn, SIGNAL(clicked()), this, SLOT(slotCompareEqColorF()));

  QLabel *compareNoEqColorFLabel = new QLabel(MW->MO->TS->TCCompareNoEqColorF_v1);
  compareNoEqColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  compareNoEqColorFBtn = new QToolButton(this);
  compareNoEqColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->compareNoEqColorF);
  compareNoEqColorFBtn->setIcon(pix);
  connect(compareNoEqColorFBtn, SIGNAL(clicked()), this, SLOT(slotCompareNoEqColorF()));

  QLabel *appColorFLabel = new QLabel(MW->MO->TS->TCAppColorF_v1);
  appColorFLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  appColorFBtn = new QToolButton(this);
  appColorFBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->appColorF);
  appColorFBtn->setIcon(pix);
  connect(appColorFBtn, SIGNAL(clicked()), this, SLOT(slotAppColorF()));

  QLabel *appColorBLabel = new QLabel(MW->MO->TS->TCAppColorB_v1);
  appColorBLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  appColorBBtn = new QToolButton(this);
  appColorBBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->appColorB);
  appColorBBtn->setIcon(pix);
  connect(appColorBBtn, SIGNAL(clicked()), this, SLOT(slotAppColorB()));

  docks3DTitleBarCheckBox = new QCheckBox(QString("3D"), this); // 3D си е 3D на всички езици.
  docks3DTitleBarCheckBox->setToolTip(MW->MO->TS->TCShow3DTitleBarTT_v1);
  docks3DTitleBarCheckBox->setChecked(SVars->docks3DTitleBar);
  connect(docks3DTitleBarCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotDocks3DTitleBar_Toggled(bool)));

  QLabel *infoLabel = new QLabel(MW->MO->TS->TCInfo_v1);
  infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  infoLabel->setWordWrap(true);
  infoLabel->setEnabled(false); // Това за да стане по-светъл текстът (да се откроява от другите).

  defaultColorsBtn = new QPushButton(MW->MO->TS->GetDefaultSettings_v1);
  //defaultColorsBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(defaultColorsBtn, SIGNAL(clicked()), this, SLOT(slotDefaultColors()));

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(dock1TextColorFBtn, 0, 0);
  mainLayout->addWidget(dock1TextColorFLabel, 0, 1);
  mainLayout->addWidget(dock1TextColorBBtn, 1, 0);
  mainLayout->addWidget(dock1TextColorBLabel, 1, 1);
  mainLayout->addWidget(dock1BGImageCheckBox, 1, 2);
  mainLayout->addWidget(dock2TextColorFBtn, 2, 0);
  mainLayout->addWidget(dock2TextColorFLabel, 2, 1);
  mainLayout->addWidget(dock2TextColorBBtn, 3, 0);
  mainLayout->addWidget(dock2TextColorBLabel, 3, 1);
  mainLayout->addWidget(dock2BGImageCheckBox, 3, 2);
  mainLayout->addWidget(oldTestamentColorFBtn, 4, 0);
  mainLayout->addWidget(oldTestamentColorFLabel, 4, 1);
  mainLayout->addWidget(oldTestamentAlphaFSpinBox, 4, 2);
  mainLayout->addWidget(newTestamentColorFBtn, 5, 0);
  mainLayout->addWidget(newTestamentColorFLabel, 5, 1);
  mainLayout->addWidget(newTestamentAlphaFSpinBox, 5, 2);
  mainLayout->addWidget(textInBracketsColorFBtn, 6, 0);
  mainLayout->addWidget(textInBracketsColorFLabel, 6, 1);
  mainLayout->addWidget(JesusWordsColorFBtn, 7, 0);
  mainLayout->addWidget(JesusWordsColorFEnableCheckBox, 7, 1);
  mainLayout->addWidget(compareEqColorFBtn, 8, 0);
  mainLayout->addWidget(compareEqColorFLabel, 8, 1);
  mainLayout->addWidget(compareNoEqColorFBtn, 9, 0);
  mainLayout->addWidget(compareNoEqColorFLabel, 9, 1);
  mainLayout->addWidget(appColorFBtn, 10, 0);
  mainLayout->addWidget(appColorFLabel, 10, 1);
  mainLayout->addWidget(docks3DTitleBarCheckBox, 10, 2);
  mainLayout->addWidget(appColorBBtn, 11, 0);
  mainLayout->addWidget(appColorBLabel, 11, 1);
  mainLayout->addWidget(infoLabel, 12, 0, 1, 3);
  mainLayout->addWidget(defaultColorsBtn, 13, 0, 1, 3);
  mainLayout->setRowStretch(14, 1); // Този номер на ред не съществува, но така се добавя нещо като Space под последния ред.
  setLayout(mainLayout);
}

void ColorsTab::slotDock1TextColorF()
{
  QColor col = QColorDialog::getColor(SVars->dock1TextColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  dock1TextColorFBtn->setIcon(pix);
  SVars->dock1TextColorF = col;
}

void ColorsTab::slotDock1TextColorB()
{
  QColor col = QColorDialog::getColor(SVars->dock1TextColorB, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  dock1TextColorBBtn->setIcon(pix);
  SVars->dock1TextColorB = col;
}

void ColorsTab::slotDock1BGImage_Toggled(const bool checked)
{
  if (checked)
  {
    QString fileName = QFileDialog::getOpenFileName(this, QString("Wallpaper"), "", QString("Wallpaper (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm *.tiff *.mng *.svg *.tga);;All Files (*.*)"));
    if (!QImage(fileName).isNull())
    {
      SVars->dock1BGImage = fileName;
    }
    else
    {
      SVars->dock1BGImage = "";
      dock1BGImageCheckBox->setChecked(false);
    }
  }
  else
  {
    SVars->dock1BGImage = "";
  }
}

void ColorsTab::slotDock2TextColorF()
{
  QColor col = QColorDialog::getColor(SVars->dock2TextColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  dock2TextColorFBtn->setIcon(pix);
  SVars->dock2TextColorF = col;
}

void ColorsTab::slotDock2TextColorB()
{
  QColor col = QColorDialog::getColor(SVars->dock2TextColorB, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  dock2TextColorBBtn->setIcon(pix);
  SVars->dock2TextColorB = col;
}

void ColorsTab::slotDock2BGImage_Toggled(const bool checked)
{
  if (checked)
  {
    QString fileName = QFileDialog::getOpenFileName(this, QString("Wallpaper"), "", QString("Wallpaper (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm *.tiff *.mng *.svg *.tga);;All Files (*.*)"));
    if (!QImage(fileName).isNull())
    {
      SVars->dock2BGImage = fileName;
    }
    else
    {
      SVars->dock2BGImage = "";
      dock2BGImageCheckBox->setChecked(false);
    }
  }
  else
  {
    SVars->dock2BGImage = "";
  }
}

void ColorsTab::slotOldTestamentColorF()
{
  QColor col = QColorDialog::getColor(SVars->oldTestamentColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  oldTestamentColorFBtn->setIcon(pix);
  SVars->oldTestamentColorF = col;
}

void ColorsTab::slotOldTestamentAlphaF_valueChanged(int i)
{
  SVars->oldTestamentAlphaF = i;
}

void ColorsTab::slotNewTestamentColorF()
{
  QColor col = QColorDialog::getColor(SVars->newTestamentColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  newTestamentColorFBtn->setIcon(pix);
  SVars->newTestamentColorF = col;
}

void ColorsTab::slotNewTestamentAlphaF_valueChanged(int i)
{
  SVars->newTestamentAlphaF = i;
}

void ColorsTab::slotTextInBracketsColorF()
{
  QColor col = QColorDialog::getColor(SVars->textInBracketsColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  textInBracketsColorFBtn->setIcon(pix);
  SVars->textInBracketsColorF = col;
}

void ColorsTab::slotJesusWordsColorF()
{
  QColor col = QColorDialog::getColor(SVars->JesusWordsColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  JesusWordsColorFBtn->setIcon(pix);
  SVars->JesusWordsColorF = col;
}

void ColorsTab::slotJesusWordsColorFEnable_Toggled(const bool checked)
{
  SVars->JesusWordsColorFEnable = checked;
  JesusWordsColorFBtn->setEnabled(SVars->JesusWordsColorFEnable);
}

void ColorsTab::slotCompareEqColorF()
{
  QColor col = QColorDialog::getColor(SVars->compareEqColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  compareEqColorFBtn->setIcon(pix);
  SVars->compareEqColorF = col;
}

void ColorsTab::slotCompareNoEqColorF()
{
  QColor col = QColorDialog::getColor(SVars->compareNoEqColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  compareNoEqColorFBtn->setIcon(pix);
  SVars->compareNoEqColorF = col;
}

void ColorsTab::slotAppColorF()
{
  QColor col = QColorDialog::getColor(SVars->appColorF, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  appColorFBtn->setIcon(pix);
  SVars->appColorF = col;
}

void ColorsTab::slotAppColorB()
{
  QColor col = QColorDialog::getColor(SVars->appColorB, this);
  if (!col.isValid()) return;
  QPixmap pix(16, 16);
  pix.fill(col);
  appColorBBtn->setIcon(pix);
  SVars->appColorB = col;
}

void ColorsTab::slotDocks3DTitleBar_Toggled(const bool checked)
{
  SVars->docks3DTitleBar = checked;
  MW->MO->SVars.docks3DTitleBar = checked;
  MW->set3DTitleBars();
}

void ColorsTab::slotDefaultColors()
{
  if ( QMessageBox::question(this, MW->MO->TS->Settings_v1, MW->MO->TS->GetDefaultSettingsQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
  {
    QMessageBox messageBox(this);
    QAbstractButton *whiteThemeButton = messageBox.addButton(MW->MO->TS->WhiteTheme_v1, QMessageBox::AcceptRole); // Всички трябва да са AcceptRole. Така бутон X на диалога става
    QAbstractButton *greyThemeButton = messageBox.addButton(MW->MO->TS->GreyTheme_v1, QMessageBox::AcceptRole);   // неактивен и потребителят е принуден да натисне един от бутоните.
    QAbstractButton *darkThemeButton = messageBox.addButton(MW->MO->TS->DarkTheme_v1, QMessageBox::AcceptRole);   //

    messageBox.exec();

    if (messageBox.clickedButton() == whiteThemeButton)
    {
      SVars->dock1TextColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->dock1TextColorB = QColor(255, 255, 255);      // (#ffffff) Бял.
      SVars->dock2TextColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->dock2TextColorB = QColor(255, 255, 255);      // (#ffffff) Бял.
      SVars->oldTestamentColorF = QColor(0, 170, 170);     // (#00aaaa) Тъмно зелен/син.
      SVars->newTestamentColorF = QColor(255, 96, 80);     // (#ff6050) Светло червен (Tomato).
      SVars->oldTestamentAlphaF = 40;
      SVars->newTestamentAlphaF = 32;
      SVars->textInBracketsColorF = QColor(160, 160, 160); // (#а0а0а0) Сив.
      SVars->JesusWordsColorF = QColor(176, 0, 0);         // (#b00000) Винено червен.
      SVars->JesusWordsColorFEnable = true;
      SVars->compareEqColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->compareNoEqColorF = QColor(160, 160, 160);    // (#а0а0а0) Сив.
      SVars->appColorF = QColor(255, 255, 255);            // (#ffffff) Бяло (Windows 10).
      SVars->appColorB = QColor(100, 100, 100);            // (#646464) Тъмно сив.
      SVars->docks3DTitleBar = false;
    }
    else if (messageBox.clickedButton() == greyThemeButton)
    {
      SVars->dock1TextColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->dock1TextColorB = QColor(255, 255, 255);      // (#ffffff) Бял.
      SVars->dock2TextColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->dock2TextColorB = QColor(255, 255, 235);      // (#ffffeb) Бледо жълт.
      SVars->oldTestamentColorF = QColor(0, 170, 170);     // (#00aaaa) Тъмно зелен/син.
      SVars->newTestamentColorF = QColor(255, 96, 80);     // (#ff6050) Светло червен (Tomato).
      SVars->oldTestamentAlphaF = 40;
      SVars->newTestamentAlphaF = 32;
      SVars->textInBracketsColorF = QColor(160, 160, 160); // (#а0а0а0) Сив.
      SVars->JesusWordsColorF = QColor(176, 0, 0);         // (#b00000) Винено червен.
      SVars->JesusWordsColorFEnable = true;
      SVars->compareEqColorF = QColor(16, 16, 16);         // (#101010) Тъмно сив.
      SVars->compareNoEqColorF = QColor(160, 160, 160);    // (#а0а0а0) Сив.
      SVars->appColorF = QColor(235, 235, 235);            // (#ebebeb) Почти бяло (с видими 3D заглавни ленти).
      SVars->appColorB = QColor(100, 100, 100);            // (#646464) Тъмно сив.
      SVars->docks3DTitleBar = true;
    }
    else if (messageBox.clickedButton() == darkThemeButton)
    {
      SVars->dock1TextColorF = QColor(210, 210, 210);      // (#d2d2d2) Светло сив.
      SVars->dock1TextColorB = QColor(48, 48, 48);         // (#303030) Тъмно сив.
      SVars->dock2TextColorF = QColor(210, 210, 210);      // (#d2d2d2) Светло сив.
      SVars->dock2TextColorB = QColor(48, 48, 48);         // (#303030) Тъмно сив.
      SVars->oldTestamentColorF = QColor(0, 170, 170);     // (#00aaaa) Тъмно зелен/син.
      SVars->newTestamentColorF = QColor(255, 96, 80);     // (#f51e00) Светло червен (Tomato).
      SVars->oldTestamentAlphaF = 50;
      SVars->newTestamentAlphaF = 50;
      SVars->textInBracketsColorF = QColor(100, 100, 100); // (#646464) Сив.
      SVars->JesusWordsColorF = QColor(255, 170, 0);       // (#ffaa00) Оранжев.
      SVars->JesusWordsColorFEnable = true;
      SVars->compareEqColorF = QColor(210, 210, 210);      // (#d2d2d2) Светло сив.
      SVars->compareNoEqColorF = QColor(100, 100, 100);    // (#646464) Сив.
      SVars->appColorF = QColor(48, 48, 48);               // (#303030) Тъмно сив.
      SVars->appColorB = QColor(210, 210, 210);            // (#d2d2d2) Светло сив.
      SVars->docks3DTitleBar = false;
    }

    QPixmap pix(16, 16);
    pix.fill(SVars->dock1TextColorF);      dock1TextColorFBtn->setIcon(pix);
    pix.fill(SVars->dock1TextColorB);      dock1TextColorBBtn->setIcon(pix);
    pix.fill(SVars->dock2TextColorF);      dock2TextColorFBtn->setIcon(pix);
    pix.fill(SVars->dock2TextColorB);      dock2TextColorBBtn->setIcon(pix);
    pix.fill(SVars->oldTestamentColorF);   oldTestamentColorFBtn->setIcon(pix);
    pix.fill(SVars->newTestamentColorF);   newTestamentColorFBtn->setIcon(pix);
    oldTestamentAlphaFSpinBox->setValue(SVars->oldTestamentAlphaF);
    newTestamentAlphaFSpinBox->setValue(SVars->newTestamentAlphaF);
    pix.fill(SVars->textInBracketsColorF); textInBracketsColorFBtn->setIcon(pix);
    pix.fill(SVars->JesusWordsColorF);     JesusWordsColorFBtn->setIcon(pix);
    JesusWordsColorFEnableCheckBox->setChecked(true);
    JesusWordsColorFBtn->setEnabled(SVars->JesusWordsColorFEnable);
    pix.fill(SVars->compareEqColorF);      compareEqColorFBtn->setIcon(pix);
    pix.fill(SVars->compareNoEqColorF);    compareNoEqColorFBtn->setIcon(pix);
    pix.fill(SVars->appColorF);            appColorFBtn->setIcon(pix);
    pix.fill(SVars->appColorB);            appColorBBtn->setIcon(pix);
    docks3DTitleBarCheckBox->setChecked(SVars->docks3DTitleBar);
  }
}




// View ---------------------------------------------------------------------------------------------------------------------------------------------------------
ViewTab::ViewTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;
  QFontDatabase db;

  // TMenu
  QGroupBox *tMenuGroup = new QGroupBox(MW->MO->TS->TVTMenu_v1);

  tMenuTopRBtn = new QRadioButton(MW->MO->TS->PositionTop_v1, this);
  tMenuTopRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(tMenuTopRBtn, SIGNAL(toggled(bool)), this, SLOT(slotTMenuTopRBtn_Toggled(bool)));

  tMenuBottomRBtn = new QRadioButton(MW->MO->TS->PositionBottom_v1, this);
  tMenuBottomRBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(tMenuBottomRBtn, SIGNAL(toggled(bool)), this, SLOT(slotTMenuBottomRBtn_Toggled(bool)));

  if (SVars->TMenuPosition == POSITION_TOP)
    tMenuTopRBtn->setChecked(true);
  else // POSITION_BOTTOM
    tMenuBottomRBtn->setChecked(true);

  toolBarSizeComboBox = new QComboBox(this);
  toolBarSizeComboBox->setToolTip(MW->MO->TS->TVFontSize_v1);
  foreach(int fSize, db.standardSizes())
    if (fSize >= 6 && fSize <= 48)
      toolBarSizeComboBox->addItem(QString::number(fSize));
  toolBarSizeComboBox->setCurrentIndex(toolBarSizeComboBox->findText(QString::number(SVars->otherToolBarFontSize)));
  toolBarSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(toolBarSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotToolBarFontSize(const QString)));

  tMenuIconSizeComboBox = new QComboBox(this);
  tMenuIconSizeComboBox->setToolTip(MW->MO->TS->TVTMenuIconSize_v1);
  for (int size = 16; size <= 96; size += 8)
    tMenuIconSizeComboBox->addItem(QString::number(size));
  if (tMenuIconSizeComboBox->findText(QString::number(SVars->TMenuIconSize)) == -1) tMenuIconSizeComboBox->addItem(QString::number(SVars->TMenuIconSize));
  tMenuIconSizeComboBox->setCurrentIndex(tMenuIconSizeComboBox->findText(QString::number(SVars->TMenuIconSize)));
  tMenuIconSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(tMenuIconSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotTMenuIconSize(const QString)));

  QHBoxLayout *positionBtnsLayout = new QHBoxLayout;
  positionBtnsLayout->addWidget(tMenuTopRBtn);
  positionBtnsLayout->addWidget(tMenuBottomRBtn);
  positionBtnsLayout->addWidget(tMenuIconSizeComboBox);
  positionBtnsLayout->addWidget(toolBarSizeComboBox);

  //QVBoxLayout *tMenuLayout = new QVBoxLayout;
  //tMenuLayout->addLayout(positionBtnsLayout);
  tMenuGroup->setLayout(positionBtnsLayout);

  // booksToolBar
  QGroupBox *booksToolBarGroup = new QGroupBox(MW->MO->TS->TVBooksToolBar_v1);

  booksLeftRBtn = new QRadioButton(MW->MO->TS->PositionLeft_v1, this);
  booksLeftRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(booksLeftRBtn, SIGNAL(toggled(bool)), this, SLOT(slotBooksLeftRBtn_Toggled(bool)));

  booksRightRBtn = new QRadioButton(MW->MO->TS->PositionRight_v1, this);
  booksRightRBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(booksRightRBtn, SIGNAL(toggled(bool)), this, SLOT(slotBooksRightRBtn_Toggled(bool)));

  if (SVars->booksToolBarPosition == POSITION_LEFT)
    booksLeftRBtn->setChecked(true);
  else // POSITION_RIGHT
    booksRightRBtn->setChecked(true);

  booksFontSizeComboBox = new QComboBox(this);
  booksFontSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  booksFontSizeComboBox->setEditable(false);
  foreach(int fSize, db.standardSizes())
    if (fSize >= 6 && fSize <= 20)
      booksFontSizeComboBox->addItem(QString::number(fSize));
  booksFontSizeComboBox->setCurrentIndex(booksFontSizeComboBox->findText(QString::number(SVars->booksToolBarFontSize)));
  booksFontSizeComboBox->setToolTip(MW->MO->TS->TVFontSize_v1);
  connect(booksFontSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotBooksFontSize(const QString)));

  QHBoxLayout *hBooksToolBarLayout = new QHBoxLayout;
  hBooksToolBarLayout->addWidget(booksLeftRBtn);
  hBooksToolBarLayout->addWidget(booksRightRBtn);
  hBooksToolBarLayout->addWidget(booksFontSizeComboBox);

  QVBoxLayout *vBooksToolBarLayout = new QVBoxLayout;
  vBooksToolBarLayout->addLayout(hBooksToolBarLayout);

  booksToolBarGroup->setLayout(vBooksToolBarLayout);

  // searchToolBar
  QGroupBox *searchToolBarGroup = new QGroupBox(MW->MO->TS->TVSearchToolBar_v1);

  searchLeftRBtn = new QRadioButton(MW->MO->TS->PositionLeft_v1, this);
  searchLeftRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(searchLeftRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchLeftRBtn_Toggled(bool)));

  searchRightRBtn = new QRadioButton(MW->MO->TS->PositionRight_v1, this);
  searchRightRBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(searchRightRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchRightRBtn_Toggled(bool)));

  if (SVars->searchToolBarPosition == POSITION_LEFT)
    searchLeftRBtn->setChecked(true);
  else // POSITION_RIGHT
    searchRightRBtn->setChecked(true);

  searchToolBarWidthComboBox = new QComboBox(this);
  searchToolBarWidthComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  searchToolBarWidthComboBox->setEditable(false);
  for (int i = 100; i < 1000; i+=20)
    searchToolBarWidthComboBox->addItem(QString::number(i));
  if (searchToolBarWidthComboBox->findText(QString::number(SVars->searchToolBarWidth)) == -1) searchToolBarWidthComboBox->insertItem(0, QString::number(SVars->searchToolBarWidth));
  searchToolBarWidthComboBox->setCurrentIndex(searchToolBarWidthComboBox->findText(QString::number(SVars->searchToolBarWidth)));
  searchToolBarWidthComboBox->setToolTip(MW->MO->TS->TVSearchToolBarWidth_v1);
  connect(searchToolBarWidthComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotSearchToolBarWidth(const QString)));

  searchFontSizeComboBox = new QComboBox(this);
  searchFontSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  searchFontSizeComboBox->setEditable(false);
  foreach(int fSize, db.standardSizes())
    if (fSize >= 6 && fSize <= 20)
      searchFontSizeComboBox->addItem(QString::number(fSize));
  searchFontSizeComboBox->setCurrentIndex(searchFontSizeComboBox->findText(QString::number(SVars->searchToolBarFontSize)));
  searchFontSizeComboBox->setToolTip(MW->MO->TS->TVFontSize_v1);
  connect(searchFontSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotSearchFontSize(const QString)));

  QHBoxLayout *searchToolBarLayout = new QHBoxLayout;
  searchToolBarLayout->addWidget(searchLeftRBtn);
  searchToolBarLayout->addWidget(searchRightRBtn);
  searchToolBarLayout->addWidget(searchToolBarWidthComboBox);
  searchToolBarLayout->addWidget(searchFontSizeComboBox);
  searchToolBarGroup->setLayout(searchToolBarLayout);

  // projectorToolBar
  QGroupBox *projectorToolBarGroup = new QGroupBox(MW->MO->TS->TVProjectorToolBar_v1);

  projectorLeftRBtn = new QRadioButton(MW->MO->TS->PositionLeft_v1, this);
  projectorLeftRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(projectorLeftRBtn, SIGNAL(toggled(bool)), this, SLOT(slotProjectorLeftRBtn_Toggled(bool)));

  projectorRightRBtn = new QRadioButton(MW->MO->TS->PositionRight_v1, this);
  projectorRightRBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(projectorRightRBtn, SIGNAL(toggled(bool)), this, SLOT(slotProjectorRightRBtn_Toggled(bool)));

  if (SVars->projectorToolBarPosition == POSITION_LEFT)
    projectorLeftRBtn->setChecked(true);
  else // POSITION_RIGHT
    projectorRightRBtn->setChecked(true);

  projectorPrevSizeComboBox = new QComboBox(this);
  projectorPrevSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  projectorPrevSizeComboBox->setEditable(false);
  for (int i = 160; i <= 512; i+=16)
    projectorPrevSizeComboBox->addItem(QString::number(i));
  projectorPrevSizeComboBox->setCurrentIndex(projectorPrevSizeComboBox->findText(QString::number(SVars->projectorToolBarPrevSize)));
  projectorPrevSizeComboBox->setToolTip(MW->MO->TS->TVProjectorPrevScreenWidth_v1);
  connect(projectorPrevSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotProjectorPrevSize(const QString)));

  projectorFontSizeComboBox = new QComboBox(this);
  projectorFontSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  projectorFontSizeComboBox->setEditable(false);
  foreach(int fSize, db.standardSizes())
    if (fSize >= 6 && fSize <= 20)
      projectorFontSizeComboBox->addItem(QString::number(fSize));
  projectorFontSizeComboBox->setCurrentIndex(projectorFontSizeComboBox->findText(QString::number(SVars->projectorToolBarFontSize)));
  projectorFontSizeComboBox->setToolTip(MW->MO->TS->TVFontSize_v1);
  connect(projectorFontSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotProjectorFontSize(const QString)));

  QHBoxLayout *projectorToolBarLayout = new QHBoxLayout;
  projectorToolBarLayout->addWidget(projectorLeftRBtn);
  projectorToolBarLayout->addWidget(projectorRightRBtn);
  projectorToolBarLayout->addWidget(projectorPrevSizeComboBox);
  projectorToolBarLayout->addWidget(projectorFontSizeComboBox);
  projectorToolBarGroup->setLayout(projectorToolBarLayout);
  
  //// GUI Style
  //QGroupBox *GUIStyleGroup = new QGroupBox(MW->MO->TS->TVGUIStyle);
  //
  ////QRegExp regExp(".(.*)\\+?Style");
  ////QString defaultStyle = QApplication::style()->metaObject()->className();
  ////if (regExp.exactMatch(defaultStyle)) defaultStyle = regExp.cap(1);
  //guiStyleComboBox = new QComboBox(this);
  //guiStyleComboBox->addItem(QString("<System Style>")); // Това е стилът по подразбиране за съответната OS.
  //guiStyleComboBox->addItems(QStyleFactory::keys()); // Това ще добави всички възможни стилове.
  //if (SVars->GUIStyle == "")
  //  guiStyleComboBox->setCurrentIndex(0);
  //else
  //  guiStyleComboBox->setCurrentIndex(guiStyleComboBox->findText(SVars->GUIStyle, Qt::MatchContains)); // Вместо SVars->GUIStyle беше defaultStyle.
  //guiStyleComboBox->setToolTip(MW->MO->TS->TVGUIStyleTT);
  //connect(guiStyleComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotGuiStyle(const QString)));
  //
  //QHBoxLayout *GUIStyleLayout = new QHBoxLayout;
  //GUIStyleLayout->addWidget(guiStyleComboBox);
  //GUIStyleGroup->setLayout(GUIStyleLayout);

  // ----------------------------------------------------
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tMenuGroup);
  mainLayout->addWidget(booksToolBarGroup);
  mainLayout->addWidget(searchToolBarGroup);
  mainLayout->addWidget(projectorToolBarGroup);
  //mainLayout->addWidget(GUIStyleGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void ViewTab::slotTMenuTopRBtn_Toggled(const bool checked)
{
  if (checked) SVars->TMenuPosition = POSITION_TOP;
}

void ViewTab::slotTMenuBottomRBtn_Toggled(const bool checked)
{
  if (checked) SVars->TMenuPosition = POSITION_BOTTOM;
}

void ViewTab::slotToolBarFontSize(const QString size)
{
  SVars->otherToolBarFontSize = size.toInt();
  MW->MO->SVars.otherToolBarFontSize = SVars->otherToolBarFontSize;

  MW->setTMenuFontSize();

  MW->mDockBooks->slotSetTitleBarFontSize();
  MW->mDockBookmarks->slotSetTitleBarFontSize();
  MW->mDockProjector->slotSetTitleBarFontSize();
  MW->mDockSearch->slotSetTitleBarFontSize();
  for (int index = 0; index < MW->HDocks.length(); index++)
  {
    MW->HDocks[index].dockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  }
  for (int index = 0; index < MW->ODocks.length(); index++)
  {
    MW->ODocks[index].dockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  }
}

void ViewTab::slotTMenuIconSize(const QString size)
{
  SVars->TMenuIconSize = size.toInt();
}

void ViewTab::slotBooksLeftRBtn_Toggled(const bool checked)
{
  if (checked) SVars->booksToolBarPosition = POSITION_LEFT;
}

void ViewTab::slotBooksRightRBtn_Toggled(const bool checked)
{
  if (checked) SVars->booksToolBarPosition = POSITION_RIGHT;
}

void ViewTab::slotBooksFontSize(const QString size)
{
  SVars->booksToolBarFontSize = size.toInt();
  MW->MO->SVars.booksToolBarFontSize = SVars->booksToolBarFontSize;

  QFont font = MW->booksWidget->font();
  font.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  MW->booksWidget->setFont(font);
  
  font = MW->fastAccessWidget->font();
  font.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  MW->fastAccessWidget->setFont(font);
  
  font = MW->bookmarksWidget->font();
  font.setPointSize(MW->MO->SVars.booksToolBarFontSize);
  MW->bookmarksWidget->setFont(font);
  // F    6    7    8    9   10   11   12   14   16   18   20 - възможни размери на шрифта.
  // W  100  110  120  130  140  150  160  180  200  220  260 - широчина на тулбара за книгите.
  // W  130  145  160  175  190  205  220  250  280  310  340 - широчина на тулбара за отметките.
  //
  // W = F * 10 + 40
  // W = F * 15 + 40
  //
  int W = MW->MO->SVars.booksToolBarFontSize * 10 + 40;
  MW->mDockBooks->setMinimumWidth(W);
  MW->mDockBooks->setMaximumWidth(W);
  W = MW->MO->SVars.booksToolBarFontSize * 15 + 40;
  MW->mDockBookmarks->setMinimumWidth(W);
  MW->mDockBookmarks->setMaximumWidth(W);
}

void ViewTab::slotSearchLeftRBtn_Toggled(const bool checked)
{
  if (checked) SVars->searchToolBarPosition = POSITION_LEFT;
}

void ViewTab::slotSearchRightRBtn_Toggled(const bool checked)
{
  if (checked) SVars->searchToolBarPosition = POSITION_RIGHT;
}

void ViewTab::slotSearchToolBarWidth(const QString size)
{
  SVars->searchToolBarWidth = size.toInt();
  MW->MO->SVars.searchToolBarWidth = SVars->searchToolBarWidth;
  MW->mDockSearch->setMinimumWidth(SVars->searchToolBarWidth);
  MW->mDockSearch->setMaximumWidth(SVars->searchToolBarWidth);
  MW->mDockSearch->slotSetFontSize(); // Това е, за да се преоразмерят картинките от филтъра.
}

void ViewTab::slotSearchFontSize(const QString size)
{
  SVars->searchToolBarFontSize = size.toInt();
  MW->MO->SVars.searchToolBarFontSize = SVars->searchToolBarFontSize;
  MW->mDockSearch->slotSetFontSize();
  for (int index = 0; index < MW->ODocks.length(); index++)
  {
    if (MW->ODocks[index].dockWidget->getDockWidgetType() == DOCK_TYPE__DICTIONARY) MW->ODocks[index].dictionary->setDicFontSize();
  }
}

void ViewTab::slotProjectorLeftRBtn_Toggled(const bool checked)
{
  if (checked) SVars->projectorToolBarPosition = POSITION_LEFT;
}

void ViewTab::slotProjectorRightRBtn_Toggled(const bool checked)
{
  if (checked) SVars->projectorToolBarPosition = POSITION_RIGHT;
}

void ViewTab::slotProjectorPrevSize(const QString size)
{
  SVars->projectorToolBarPrevSize = size.toInt();
  MW->MO->SVars.projectorToolBarPrevSize = SVars->projectorToolBarPrevSize;
  MW->projectorWidget->slotSetPrevSize();
  MW->mDockProjector->resetMinimumWidth();
}

void ViewTab::slotProjectorFontSize(const QString size)
{
  SVars->projectorToolBarFontSize = size.toInt();
  MW->MO->SVars.projectorToolBarFontSize = SVars->projectorToolBarFontSize;
  MW->projectorWidget->slotSetProjectorFontSize();
}

void ViewTab::slotGuiStyle(const QString styleName)
{
  //qApp->setStyle(styleName); // Това ще смени стила незабавно, но умишлено не се използва, първо заради долния код и второ, защото незабавното сменяне на стила прави нещата грозни и си трябва рестарт.
  if (styleName == QString("<System Style>"))
    SVars->GUIStyle = "";
  else
    SVars->GUIStyle = styleName;
}



// Text ---------------------------------------------------------------------------------------------------------------------------------------------------------
TextTab::TextTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;
  QFontDatabase db;
  
  // Global
  globalSizeComboBox = new QComboBox(this);
  globalSizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  globalSizeComboBox->setToolTip(MW->MO->TS->TTGlobalFontSizeTT_v1);
  foreach(int fSize, db.standardSizes())
    if (fSize >= 6 && fSize <= 20)
      globalSizeComboBox->addItem(QString::number(fSize));
  globalSizeComboBox->setCurrentIndex(globalSizeComboBox->findText(QString::number(SVars->globalFontSize)));
  connect(globalSizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotGlobalFontSize(const QString)));

  globalAntialiasCheckBox = new QCheckBox(MW->MO->TS->TTAntialias_v1, this);
  globalAntialiasCheckBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  if (SVars->globalFontAntialias) globalAntialiasCheckBox->setChecked(true);
  connect(globalAntialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotGlobalAntialias_Toggled(bool)));

  QHBoxLayout *hGlobalLayout = new QHBoxLayout;
  hGlobalLayout->addWidget(new QLabel(MW->MO->TS->TTGlobalFontSize_v1));
  hGlobalLayout->addWidget(globalSizeComboBox);
  hGlobalLayout->addWidget(globalAntialiasCheckBox);

  
  // font
  QGroupBox *fontGroup = new QGroupBox(MW->MO->TS->TTTheHolyTextFont_v1);

  familyComboBox = new QFontComboBox(this);
  familyComboBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  if (familyComboBox->findText(QString("Serif")) == -1) // Ако фамилията "Serif" я нама в списъка.
    familyComboBox->insertItem(0, QString("Serif")); // Добавя фамилията "Serif" (която е по подразбиране) към списъка.
  if (familyComboBox->findText(QString("Sans")) == -1) // Ако фамилията "Sans" я нама в списъка.
    familyComboBox->insertItem(0, QString("Sans")); // Добавя фамилията "Sans" (която е по подразбиране) към списъка.
  if (familyComboBox->findText(SVars->fontFamily) == -1) // Ако текущата фамилия/шрифт е написан на ръка и го няма в списъка.
    familyComboBox->insertItem(0, SVars->fontFamily); // Добавя фамилията/шрифта към списъка.
  familyComboBox->setCurrentIndex(familyComboBox->findText(SVars->fontFamily));
  connect(familyComboBox, SIGNAL(editTextChanged(const QString)), this, SLOT(slotFontFamily(const QString)));

  sizeComboBox = new QComboBox(this);
  sizeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  foreach(int fSize, db.standardSizes())
    sizeComboBox->addItem(QString::number(fSize));
  sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(SVars->fontSize)));
  connect(sizeComboBox, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotFontSize(const QString)));

  numberBoldCheckBox = new QCheckBox(MW->MO->TS->TTVerseNumberBold_v1, this);
  if (SVars->verseNumberBold) numberBoldCheckBox->setChecked(true);
  connect(numberBoldCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotNumberBold_Toggled(bool)));

  numberSupCheckBox = new QCheckBox(MW->MO->TS->TTVerseNumberSup_v1, this);
  if (SVars->verseNumberSup) numberSupCheckBox->setChecked(true);
  connect(numberSupCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotNumberSup_Toggled(bool)));

  defaultFontBtn = new QPushButton(MW->MO->TS->GetDefaultSettings_v1);
  connect(defaultFontBtn, SIGNAL(clicked()), this, SLOT(slotDefaultFont()));

  QHBoxLayout *hFontLayout = new QHBoxLayout;
  hFontLayout->addWidget(familyComboBox);
  hFontLayout->addWidget(sizeComboBox);

  QVBoxLayout *vFontLayout = new QVBoxLayout;
  vFontLayout->addLayout(hFontLayout, 1);
  vFontLayout->addWidget(numberBoldCheckBox);
  vFontLayout->addWidget(numberSupCheckBox);
  vFontLayout->addWidget(defaultFontBtn);
  fontGroup->setLayout(vFontLayout);


  // Text features
  QGroupBox *textGroup = new QGroupBox(MW->MO->TS->TTTheHolyTextFeatures_v1); 

  verseStructComboBox = new QComboBox(this);
  verseStructComboBox->setToolTip(MW->MO->TS->TTVerseStruct_v1);
  verseStructComboBox->addItem(QString("1. Xxxx xxx xxx"));
  verseStructComboBox->addItem(QString("%1 1:1. Xxxx xxx xxx").arg(MW->MO->bookMinNameArr[MW->MO->toEasternBookCodeIfNeed(60)]));   // Фил.       // Използва се Филипяни, защото е достатъчно дълга дума на кой да е
  verseStructComboBox->addItem(QString("%1 1:1. Xxxx xxx xxx").arg(MW->MO->bookShortNameArr[MW->MO->toEasternBookCodeIfNeed(60)])); // Филипяни   // език и със сигурност ще има разлика между Min и Short името.
  verseStructComboBox->setCurrentIndex(SVars->verseStruct - 1);
  connect(verseStructComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotVerseStruct(const int)));

  numerationComboBox = new QComboBox(this);
  numerationComboBox->setToolTip(MW->MO->TS->TTNumerationTT_v1);
  numerationComboBox->addItem(MW->MO->TS->TTNumeration1_v1); // NUMERATION__1
  numerationComboBox->addItem(MW->MO->TS->TTNumeration2_v1); // NUMERATION__2
  numerationComboBox->setCurrentIndex(SVars->newNumeration - 1);
  connect(numerationComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotNumeration(const int)));

  booksOrderComboBox = new QComboBox(this);
  //booksOrderComboBox->setEditable(false);
  booksOrderComboBox->setToolTip(MW->MO->TS->TTBooksOrderTT_v1);
  booksOrderComboBox->addItem(MW->MO->TS->TTBooksOrder1_v1); // BOOKS_ORDER__WESTERN
  booksOrderComboBox->addItem(MW->MO->TS->TTBooksOrder2_v1); // BOOKS_ORDER__EASTERN
  booksOrderComboBox->setCurrentIndex(SVars->newBooksOrder - 1);
  connect(booksOrderComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotBooksOrder(const int)));

  showDeutrocanonicalCheckBox = new QCheckBox(MW->MO->TS->TTShowDeuterocanonical_v1, this);
  if (SVars->newShowDeuterocanonical) showDeutrocanonicalCheckBox->setChecked(true);
  connect(showDeutrocanonicalCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotShowDeutrocanonical_Toggled(bool)));

  showAbsVerseNumberCheckBox = new QCheckBox(MW->MO->TS->TTShowAbsVerseNumber_v1, this);
  if (SVars->showAbsVerseNumber) showAbsVerseNumberCheckBox->setChecked(true);
  connect(showAbsVerseNumberCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotShowAbsVerseNumber_Toggled(bool)));

  QVBoxLayout *vTextLayout = new QVBoxLayout;
  vTextLayout->addWidget(verseStructComboBox);
  vTextLayout->addWidget(numerationComboBox);
  vTextLayout->addWidget(booksOrderComboBox);
  vTextLayout->addWidget(showDeutrocanonicalCheckBox);
  vTextLayout->addWidget(showAbsVerseNumberCheckBox);
  textGroup->setLayout(vTextLayout);


  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(hGlobalLayout);
  mainLayout->addWidget(fontGroup);
  mainLayout->addWidget(textGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void TextTab::slotGlobalFontSize(const QString size)
{
  SVars->globalFontSize = size.toInt();
  QFont font = QApplication::font();
  font.setPointSize(SVars->globalFontSize);
  QApplication::setFont(font);
}

void TextTab::slotGlobalAntialias_Toggled(const bool checked)
{
  SVars->globalFontAntialias = checked;
  MW->MO->SVars.globalFontAntialias = SVars->globalFontAntialias;

  QFont font = qApp->font();
  if (SVars->globalFontAntialias) // Antialias на шрифта за всички обекти.
    font.setStyleStrategy(QFont::PreferAntialias);
  else
    font.setStyleStrategy(QFont::NoAntialias);
  qApp->setFont(font);
}

void TextTab::slotFontFamily(const QString family)
{
  SVars->fontFamily = family;
  //MW->MO->SVars.fontFamily = SVars->fontFamily; -- Този ред не трябва да се разкоментира, за да излиза съобщението за промяна след конкретно действие.
  //MW->fontChanged(family); -- Да не се разкоментира! Този метод се извиква по-горе - след съобщението за промяна след конкретно действие.
}

void TextTab::slotFontSize(const QString size)
{
  SVars->fontSize = size.toInt();
  MW->MO->SVars.fontSize = SVars->fontSize;
  MW->fontSizeChanged();
}

void TextTab::slotNumberBold_Toggled(bool checked)
{
  SVars->verseNumberBold = checked;
}

void TextTab::slotNumberSup_Toggled(bool checked)
{
  SVars->verseNumberSup = checked;
}

void TextTab::slotVerseStruct(const int index)
{
  SVars->verseStruct = index + 1;
}

void TextTab::slotDefaultFont()
{
  if ( QMessageBox::question(this, MW->MO->TS->Settings_v1, MW->MO->TS->GetDefaultSettingsQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
  {
    SVars->fontFamily = QString("Sans");
    SVars->fontSize = 8;

    SVars->verseNumberBold = true;
    SVars->verseNumberSup = false;

    familyComboBox->setCurrentIndex(familyComboBox->findText(SVars->fontFamily));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(SVars->fontSize)));
    numberBoldCheckBox->setChecked(true);
    numberSupCheckBox->setChecked(false);
  }
}

void TextTab::slotNumeration(const int index)
{
  SVars->newNumeration = index + 1;
}

void TextTab::slotBooksOrder(const int index)
{
  SVars->newBooksOrder = index + 1;
}

void TextTab::slotShowDeutrocanonical_Toggled(const bool checked)
{
  SVars->newShowDeuterocanonical = checked;
}

void TextTab::slotShowAbsVerseNumber_Toggled(const bool checked)
{
  SVars->showAbsVerseNumber = checked;
}




// Search ---------------------------------------------------------------------------------------------------------------------------------------------------------
SearchTab::SearchTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;
  
  QPixmap pix(16, 16);

  // foundWordFormat
  QGroupBox *foundWordsFormatGroup = new QGroupBox(MW->MO->TS->TSFoundWordsFormat_v1);

  boldCheckBox = new QCheckBox(MW->MO->TS->TSWordsFormatBold_v1, this);
  if (SVars->foundWordsBold) boldCheckBox->setChecked(true);
  connect(boldCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotBold_Toggled(bool)));

  underlineCheckBox = new QCheckBox(MW->MO->TS->TSWordsFormatUnderline_v1, this);
  if (SVars->foundWordsUnderline) underlineCheckBox->setChecked(true);
  connect(underlineCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotUnderline_Toggled(bool)));

  colorCheckBoxF = new QCheckBox(MW->MO->TS->TSWordsFormatColorF_v1, this);
  colorCheckBoxF->setToolTip(MW->MO->TS->TSWordsFormatColorFTT_v1);
  if (SVars->foundWordsColorF) colorCheckBoxF->setChecked(true);
  connect(colorCheckBoxF, SIGNAL(toggled(bool)), this, SLOT(slotColorF_Toggled(bool)));

  color1FBtn = new QToolButton();
  color1FBtn->setToolTip(MW->MO->TS->TSWordsFormatColor1F_v1);
  color1FBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor1F);
  color1FBtn->setIcon(pix);
  connect(color1FBtn, SIGNAL(clicked()), this, SLOT(slotColor1F()));

  color2FBtn = new QToolButton();
  color2FBtn->setToolTip(MW->MO->TS->TSWordsFormatColor2F_v1);
  color2FBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor2F);
  color2FBtn->setIcon(pix);
  connect(color2FBtn, SIGNAL(clicked()), this, SLOT(slotColor2F()));

  color3FBtn = new QToolButton();
  color3FBtn->setToolTip(MW->MO->TS->TSWordsFormatColor3F_v1);
  color3FBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor3F);
  color3FBtn->setIcon(pix);
  connect(color3FBtn, SIGNAL(clicked()), this, SLOT(slotColor3F()));

  color4FBtn = new QToolButton();
  color4FBtn->setToolTip(MW->MO->TS->TSWordsFormatColor4F_v1);
  color4FBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor4F);
  color4FBtn->setIcon(pix);
  connect(color4FBtn, SIGNAL(clicked()), this, SLOT(slotColor4F()));

  color5FBtn = new QToolButton();
  color5FBtn->setToolTip(MW->MO->TS->TSWordsFormatColor5F_v1);
  color5FBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor5F);
  color5FBtn->setIcon(pix);
  connect(color5FBtn, SIGNAL(clicked()), this, SLOT(slotColor5F()));

  defaultColorsFBtn = new QPushButton(MW->MO->TS->GetDefaultSettings_v1);
  defaultColorsFBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(defaultColorsFBtn, SIGNAL(clicked()), this, SLOT(slotDefaultColorsF()));

  QHBoxLayout *foundWordsColorsFLayout = new QHBoxLayout;
  foundWordsColorsFLayout->addWidget(color1FBtn);
  foundWordsColorsFLayout->addWidget(color2FBtn);
  foundWordsColorsFLayout->addWidget(color3FBtn);
  foundWordsColorsFLayout->addWidget(color4FBtn);
  foundWordsColorsFLayout->addWidget(color5FBtn);
  foundWordsColorsFLayout->addWidget(defaultColorsFBtn);

  colorCheckBoxB = new QCheckBox(MW->MO->TS->TSWordsFormatColorB_v1, this);
  colorCheckBoxB->setToolTip(MW->MO->TS->TSWordsFormatColorBTT_v1);
  if (SVars->foundWordsColorB) colorCheckBoxB->setChecked(true);
  connect(colorCheckBoxB, SIGNAL(toggled(bool)), this, SLOT(slotColorB_Toggled(bool)));

  color1BBtn = new QToolButton();
  color1BBtn->setToolTip(MW->MO->TS->TSWordsFormatColor1B_v1);
  color1BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor1B);
  color1BBtn->setIcon(pix);
  connect(color1BBtn, SIGNAL(clicked()), this, SLOT(slotColor1B()));

  color2BBtn = new QToolButton();
  color2BBtn->setToolTip(MW->MO->TS->TSWordsFormatColor2B_v1);
  color2BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor2B);
  color2BBtn->setIcon(pix);
  connect(color2BBtn, SIGNAL(clicked()), this, SLOT(slotColor2B()));

  color3BBtn = new QToolButton();
  color3BBtn->setToolTip(MW->MO->TS->TSWordsFormatColor3B_v1);
  color3BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor3B);
  color3BBtn->setIcon(pix);
  connect(color3BBtn, SIGNAL(clicked()), this, SLOT(slotColor3B()));

  color4BBtn = new QToolButton();
  color4BBtn->setToolTip(MW->MO->TS->TSWordsFormatColor4B_v1);
  color4BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor4B);
  color4BBtn->setIcon(pix);
  connect(color4BBtn, SIGNAL(clicked()), this, SLOT(slotColor4B()));

  color5BBtn = new QToolButton();
  color5BBtn->setToolTip(MW->MO->TS->TSWordsFormatColor5B_v1);
  color5BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->foundWordsColor5B);
  color5BBtn->setIcon(pix);
  connect(color5BBtn, SIGNAL(clicked()), this, SLOT(slotColor5B()));

  defaultColorsBBtn = new QPushButton(MW->MO->TS->GetDefaultSettings_v1);
  defaultColorsBBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(defaultColorsBBtn, SIGNAL(clicked()), this, SLOT(slotDefaultColorsB()));

  QHBoxLayout *foundWordsColorsBLayout = new QHBoxLayout;
  foundWordsColorsBLayout->addWidget(color1BBtn);
  foundWordsColorsBLayout->addWidget(color2BBtn);
  foundWordsColorsBLayout->addWidget(color3BBtn);
  foundWordsColorsBLayout->addWidget(color4BBtn);
  foundWordsColorsBLayout->addWidget(color5BBtn);
  foundWordsColorsBLayout->addWidget(defaultColorsBBtn);

  QVBoxLayout *foundWordsFormatLayout = new QVBoxLayout;
  foundWordsFormatLayout->addWidget(boldCheckBox);
  foundWordsFormatLayout->addWidget(underlineCheckBox);
  foundWordsFormatLayout->addWidget(colorCheckBoxF);
  foundWordsFormatLayout->addLayout(foundWordsColorsFLayout);
  foundWordsFormatLayout->addWidget(colorCheckBoxB);
  foundWordsFormatLayout->addLayout(foundWordsColorsBLayout);
  foundWordsFormatGroup->setLayout(foundWordsFormatLayout);


  // extraSelection
  QGroupBox *extraSelectionGroup = new QGroupBox(MW->MO->TS->TSExtraSelectionColor_v1);

  extraSelectColor1BBtn = new QToolButton();
  extraSelectColor1BBtn->setToolTip(MW->MO->TS->TSExtraSelectionColor1B_v1);
  extraSelectColor1BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->extraSelectColor1B);
  extraSelectColor1BBtn->setIcon(pix);
  connect(extraSelectColor1BBtn, SIGNAL(clicked()), this, SLOT(slotExtraSelectColor1B()));

  extraSelectColor2BBtn = new QToolButton();
  extraSelectColor2BBtn->setToolTip(MW->MO->TS->TSExtraSelectionColor2B_v1);
  extraSelectColor2BBtn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
  pix.fill(SVars->extraSelectColor2B);
  extraSelectColor2BBtn->setIcon(pix);
  connect(extraSelectColor2BBtn, SIGNAL(clicked()), this, SLOT(slotExtraSelectColor2B()));

  defaultExtraSelectColorsBBtn = new QPushButton(MW->MO->TS->GetDefaultSettings_v1);
  defaultExtraSelectColorsBBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(defaultExtraSelectColorsBBtn, SIGNAL(clicked()), this, SLOT(slotDefaultExtraSelectColorsB()));

  QHBoxLayout *extraSelectionLayout = new QHBoxLayout;
  extraSelectionLayout->addWidget(extraSelectColor1BBtn);
  extraSelectionLayout->addWidget(extraSelectColor2BBtn);
  extraSelectionLayout->addWidget(defaultExtraSelectColorsBBtn);
  extraSelectionGroup->setLayout(extraSelectionLayout);



  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(foundWordsFormatGroup);
  mainLayout->addWidget(extraSelectionGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void SearchTab::slotBold_Toggled(const bool checked)
{
  SVars->foundWordsBold = checked;
}

void SearchTab::slotUnderline_Toggled(const bool checked)
{
  SVars->foundWordsUnderline = checked;
}

void SearchTab::slotColorF_Toggled(const bool checked)
{
  SVars->foundWordsColorF = checked;
}

void SearchTab::slotColorB_Toggled(const bool checked)
{
  SVars->foundWordsColorB = checked;
}

void SearchTab::slotColor1F()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor1F, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color1FBtn->setIcon(pix);
	SVars->foundWordsColor1F = col;
}

void SearchTab::slotColor2F()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor2F, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color2FBtn->setIcon(pix);
	SVars->foundWordsColor2F = col;
}

void SearchTab::slotColor3F()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor3F, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color3FBtn->setIcon(pix);
	SVars->foundWordsColor3F = col;
}

void SearchTab::slotColor4F()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor4F, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color4FBtn->setIcon(pix);
	SVars->foundWordsColor4F = col;
}

void SearchTab::slotColor5F()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor5F, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color5FBtn->setIcon(pix);
	SVars->foundWordsColor5F = col;
}

void SearchTab::slotColor1B()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor1B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color1BBtn->setIcon(pix);
	SVars->foundWordsColor1B = col;
}

void SearchTab::slotColor2B()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor2B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color2BBtn->setIcon(pix);
	SVars->foundWordsColor2B = col;
}

void SearchTab::slotColor3B()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor3B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color3BBtn->setIcon(pix);
	SVars->foundWordsColor3B = col;
}

void SearchTab::slotColor4B()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor4B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color4BBtn->setIcon(pix);
	SVars->foundWordsColor4B = col;
}

void SearchTab::slotColor5B()
{
    QColor col = QColorDialog::getColor(SVars->foundWordsColor5B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    color5BBtn->setIcon(pix);
	SVars->foundWordsColor5B = col;
}

void SearchTab::slotDefaultColorsF()
{
  if ( QMessageBox::question(this, MW->MO->TS->Settings_v1, MW->MO->TS->GetDefaultSettingsQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
  {
    SVars->foundWordsColor1F = QColor(255,128,  0);
    SVars->foundWordsColor2F = QColor(255, 85,255);
    SVars->foundWordsColor3F = QColor(170,  0,127);
    SVars->foundWordsColor4F = QColor(  0,150,  0);
    SVars->foundWordsColor5F = QColor(130,130,100);

    QPixmap pix(16, 16);
    pix.fill(SVars->foundWordsColor1F);     color1FBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor2F);     color2FBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor3F);     color3FBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor4F);     color4FBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor5F);     color5FBtn->setIcon(pix);
  }
}

void SearchTab::slotDefaultColorsB()
{
  if ( QMessageBox::question(this, MW->MO->TS->Settings_v1, MW->MO->TS->GetDefaultSettingsQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
  {
    SVars->foundWordsColor1B = QColor(255,210,185);
    SVars->foundWordsColor2B = QColor(255,210,255);
    SVars->foundWordsColor3B = QColor(225,200,200);
    SVars->foundWordsColor4B = QColor(185,255,185);
    SVars->foundWordsColor5B = QColor(210,210,156);

    QPixmap pix(16, 16);
    pix.fill(SVars->foundWordsColor1B);     color1BBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor2B);     color2BBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor3B);     color3BBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor4B);     color4BBtn->setIcon(pix);
    pix.fill(SVars->foundWordsColor5B);     color5BBtn->setIcon(pix);
  }
}

void SearchTab::slotExtraSelectColor1B()
{
    QColor col = QColorDialog::getColor(SVars->extraSelectColor1B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    extraSelectColor1BBtn->setIcon(pix);
	SVars->extraSelectColor1B = col;
}

void SearchTab::slotExtraSelectColor2B()
{
    QColor col = QColorDialog::getColor(SVars->extraSelectColor2B, this);
    if (!col.isValid()) return;
    QPixmap pix(16, 16);
    pix.fill(col);
    extraSelectColor2BBtn->setIcon(pix);
	SVars->extraSelectColor2B = col;
}

void SearchTab::slotDefaultExtraSelectColorsB()
{
  if ( QMessageBox::question(this, MW->MO->TS->Settings_v1, MW->MO->TS->GetDefaultSettingsQuestion_v1, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes )
  {
    SVars->extraSelectColor1B = QColor(  0, 170, 170); // Зелен/син       // (  0, 255,   0 - зелен)
    SVars->extraSelectColor2B = QColor(255,  96,  80); // Доматено червен // (255, 240,   0 - жълт )

    QPixmap pix(16, 16);
    pix.fill(SVars->extraSelectColor1B);     extraSelectColor1BBtn->setIcon(pix);
    pix.fill(SVars->extraSelectColor2B);     extraSelectColor2BBtn->setIcon(pix);
  }
}




// Other ---------------------------------------------------------------------------------------------------------------------------------------------------------
OtherTab::OtherTab(SETTINGS_VARIABLES *SVars, MainWindow *MW , QWidget *parent) : QWidget(parent)
{
  this->SVars = SVars;
  this->MW = MW;

  // Path
  QGroupBox *iniPathGroup = new QGroupBox(MW->MO->TS->TOIniPath_v1);

  iniHomePathRBtn = new QRadioButton(MW->MO->TS->TOIniPathHome_v1);
  iniHomePathRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(iniHomePathRBtn, SIGNAL(toggled(bool)), this, SLOT(slotIniHomePathRBtn_Toggled(bool)));
  //
  QLineEdit *homePathEdit = new QLineEdit( QDir::toNativeSeparators(QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath())) );
  homePathEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  homePathEdit->setReadOnly(true);
  //
  openFileManagerHomePathBtn = new QPushButton("...");
  openFileManagerHomePathBtn->setToolTip(MW->MO->TS->TOOpenTheFolder_v1);
  openFileManagerHomePathBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  openFileManagerHomePathBtn->setMinimumWidth(30);
  openFileManagerHomePathBtn->setMaximumWidth(30);
  openFileManagerHomePathBtn->setVisible(false); // Този бутон го скривам за постоянно, защото някак няма смисъл от него. Но не го изтривам, за да го върна, ако един ден реша друго.
  connect(openFileManagerHomePathBtn, SIGNAL(clicked()), this, SLOT(slotOpenFileManagerHomePathBtn_clicked()));

  iniLocalPathRBtn = new QRadioButton(MW->MO->TS->TOIniPathLocal_v1);
  iniLocalPathRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(iniLocalPathRBtn, SIGNAL(toggled(bool)), this, SLOT(slotIniLocalPathRBtn_Toggled(bool)));
  //
  QLineEdit *localPathEdit = new QLineEdit( QDir::toNativeSeparators(QString("%1/Settings").arg(QCoreApplication::applicationDirPath())) );
  localPathEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  localPathEdit->setReadOnly(true);
  //
  openFileManagerLocalPathBtn = new QPushButton("...");
  openFileManagerLocalPathBtn->setToolTip(MW->MO->TS->TOOpenTheFolder_v1);
  openFileManagerLocalPathBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  openFileManagerLocalPathBtn->setMinimumWidth(30);
  openFileManagerLocalPathBtn->setMaximumWidth(30);
  openFileManagerLocalPathBtn->setVisible(false); // Този бутон го скривам за постоянно, защото някак няма смисъл от него. Но не го изтривам, за да го върна, ако един ден реша друго.
  connect(openFileManagerLocalPathBtn, SIGNAL(clicked()), this, SLOT(slotOpenFileManagerLocalPathBtn_clicked()));

  iniOtherPathRBtn = new QRadioButton(MW->MO->TS->TOIniPathOther_v1);
  iniOtherPathRBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(iniOtherPathRBtn, SIGNAL(toggled(bool)), this, SLOT(slotIniOtherPathRBtn_Toggled(bool)));
  //
  otherPathEdit = new QLineEdit("");
  otherPathEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  otherPathEdit->setReadOnly(true); // Не е добре да се дава свобода да пишат на ръка. Ако искат да пишат, да пишат във файла.
  //
  choiceOtherPathBtn = new QPushButton("...");
  choiceOtherPathBtn->setToolTip(MW->MO->TS->TOChoiceFolder_v1);
  choiceOtherPathBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  choiceOtherPathBtn->setMinimumWidth(30);
  choiceOtherPathBtn->setMaximumWidth(30);
  choiceOtherPathBtn->setEnabled(false);
  connect(choiceOtherPathBtn, SIGNAL(clicked()), this, SLOT(slotChoiceOtherPathBtn_clicked()));

  //
  if ( SVars->pathToSettings == QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath()) )
  {
    iniHomePathRBtn->setChecked(true);
  }
  else if (SVars->pathToSettings == QString("%1/Settings").arg(QCoreApplication::applicationDirPath()) )
  {
    iniLocalPathRBtn->setChecked(true);
  }
  else
  {
    otherPathEdit->setText( QDir::toNativeSeparators(SVars->pathToSettings) ); // Този ред трябва да е преди долния.
    iniOtherPathRBtn->setChecked(true);
  }

  // URL
  QLabel *mbURLLabel = new QLabel(MW->MO->TS->TOOfficialMatCrossBibleWebSite_v1);
  mbURLLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  QLineEdit *mbURLEdit = new QLineEdit( SVars->MatCrossBibleURL );
  mbURLEdit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  mbURLEdit->setReadOnly(true);

  // Proxy
  QGroupBox *proxyGroup = new QGroupBox(QString("Proxy"));

  QLabel *proxyTypeLabel = new QLabel(QString("Type:"));
  proxyTypeComboBox = new QComboBox;
  proxyTypeComboBox->setToolTip(MW->MO->TS->TOProxyTypeTT_v1);
  proxyTypeComboBox->setEditable(false);
  proxyTypeComboBox->addItem(QString("No Proxy"));
  proxyTypeComboBox->addItem(QString("Http Proxy"));
  proxyTypeComboBox->addItem(QString("Socks5 Proxy"));
  proxyTypeComboBox->setCurrentIndex(SVars->proxyType);
  proxyTypeComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(proxyTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotProxyType(int)));

  QLabel *proxyHostNameLabel = new QLabel(QString("HostName:"));
  proxyHostNameEdit = new QLineEdit(SVars->proxyHostName);
  proxyHostNameEdit->setToolTip(MW->MO->TS->TOProxyHostNameTT_v1);
  proxyHostNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(proxyHostNameEdit, SIGNAL(textChanged(const QString)), this, SLOT(slotProxyHostName(const QString)));

  QLabel *proxyPortLabel = new QLabel(QString("Port:"));
  proxyPortEdit = new QLineEdit(QString("%1").arg(SVars->proxyPort));
  proxyPortEdit->setToolTip(MW->MO->TS->TOProxyPortTT_v1);
  proxyPortEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(proxyPortEdit, SIGNAL(textChanged(const QString)), this, SLOT(slotProxyPort(const QString)));

  if (proxyTypeComboBox->currentIndex() == PROXY__NO_PROXY)
  {
    proxyHostNameEdit->setEnabled(false);
    proxyPortEdit->setEnabled(false);
    proxyHostNameEdit->setVisible(false);
    proxyPortEdit->setVisible(false);
  }

  QGridLayout *proxyLayout = new QGridLayout;
  proxyLayout->addWidget(proxyTypeLabel, 0, 0);
  proxyLayout->addWidget(proxyTypeComboBox, 0, 1);
  proxyLayout->addWidget(proxyHostNameLabel, 1, 0);
  proxyLayout->addWidget(proxyHostNameEdit, 1, 1);
  proxyLayout->addWidget(proxyPortLabel, 2, 0);
  proxyLayout->addWidget(proxyPortEdit, 2, 1);
  proxyGroup->setLayout(proxyLayout);

  // TrayIcon
  trayIconCheckBox = new QCheckBox(MW->MO->TS->TOMinimizeWindowToTray_v1, this);
  trayIconCheckBox->setToolTip(MW->MO->TS->TOMinimizeWindowToTrayTT_v1);
  if (!QSystemTrayIcon::isSystemTrayAvailable()) trayIconCheckBox->setEnabled(false); // Ако няма system tray.
  if (SVars->enableTrayIcon) trayIconCheckBox->setChecked(true);
  connect(trayIconCheckBox, SIGNAL(toggled(bool)), this, SLOT(slotTrayIcon_Toggled(bool)));

  // Generate Dct/Cmt Example Files
  createExampleDctCmtBtn = new QPushButton(MW->MO->TS->TOCreateDctCmtExampleFiles_v1);
  createExampleDctCmtBtn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  connect(createExampleDctCmtBtn, SIGNAL(clicked()), this, SLOT(slotCreateExampleDctCmtBtn_clicked()));

  QHBoxLayout *hLayoutIniPathHome = new QHBoxLayout;
  hLayoutIniPathHome->addItem(new QSpacerItem(20, 10, QSizePolicy::Ignored, QSizePolicy::Ignored));
  hLayoutIniPathHome->addWidget(homePathEdit);
  hLayoutIniPathHome->addWidget(openFileManagerHomePathBtn);

  QHBoxLayout *hLayoutIniPathLocal = new QHBoxLayout;
  hLayoutIniPathLocal->addItem(new QSpacerItem(20, 10, QSizePolicy::Ignored, QSizePolicy::Ignored));
  hLayoutIniPathLocal->addWidget(localPathEdit);
  hLayoutIniPathLocal->addWidget(openFileManagerLocalPathBtn);

  QHBoxLayout *hLayoutIniPathOther = new QHBoxLayout;
  hLayoutIniPathOther->addItem(new QSpacerItem(20, 10, QSizePolicy::Ignored, QSizePolicy::Ignored));
  hLayoutIniPathOther->addWidget(otherPathEdit);
  hLayoutIniPathOther->addWidget(choiceOtherPathBtn);

  QVBoxLayout *hLayoutIniPath = new QVBoxLayout;
  hLayoutIniPath->addWidget(iniHomePathRBtn);
  hLayoutIniPath->addLayout(hLayoutIniPathHome);
  hLayoutIniPath->addWidget(iniLocalPathRBtn);
  hLayoutIniPath->addLayout(hLayoutIniPathLocal);
  hLayoutIniPath->addWidget(iniOtherPathRBtn);
  hLayoutIniPath->addLayout(hLayoutIniPathOther);
  iniPathGroup->setLayout(hLayoutIniPath);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(iniPathGroup);
  mainLayout->addWidget(mbURLLabel);
  mainLayout->addWidget(mbURLEdit);
  mainLayout->addItem( new QSpacerItem(0, 20, QSizePolicy::Ignored, QSizePolicy::Expanding) );
  mainLayout->addWidget(proxyGroup);
  mainLayout->addWidget(trayIconCheckBox);
  mainLayout->addWidget(createExampleDctCmtBtn);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void OtherTab::slotIniHomePathRBtn_Toggled(const bool /*checked*/)
{
  SVars->pathToSettings = QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath());
  choiceOtherPathBtn->setEnabled(false); // Това е важно за логиката на програмата.
}

void OtherTab::slotIniLocalPathRBtn_Toggled(const bool /*checked*/)
{
  SVars->pathToSettings = QString("%1/Settings").arg(QCoreApplication::applicationDirPath());
  choiceOtherPathBtn->setEnabled(false); // Това е важно за логиката на програмата.
}

void OtherTab::slotIniOtherPathRBtn_Toggled(const bool /*checked*/)
{
  SVars->pathToSettings = QDir::fromNativeSeparators( otherPathEdit->text() ); // Ако е празен стринг, няма да има ефект при натискане на OK бутона.
  choiceOtherPathBtn->setEnabled(true); // Това е важно за логиката на програмата.
}

void OtherTab::slotOpenFileManagerHomePathBtn_clicked()
{
  //QString fileManager = "dir";
//#ifdef Q_WS_MAC
  //fileManager = "open";
//#else //#ifdef Q_WS_WIN
  //fileManager = "explorer"; // dir
//#endif

  //QStringList atr;
  //atr << QDir::toNativeSeparators( QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath()) );
  //QProcess::startDetached(fileManager, atr);

  QString path = QDir::toNativeSeparators( QString("%1/.MatCraft/MatCrossBible").arg(QDir::homePath()) );
  QDesktopServices::openUrl(QUrl("file:///" + path));
}

void OtherTab::slotOpenFileManagerLocalPathBtn_clicked()
{
  //QString fileManager = "dir";
//#ifdef Q_WS_MAC
  //fileManager = "open";
//#else //#ifdef Q_WS_WIN
  //fileManager = "explorer"; // dir
//#endif

  //QStringList atr;
  //atr << QDir::toNativeSeparators( QString("%1/Settings").arg(QCoreApplication::applicationDirPath()) );
  //QProcess::startDetached(fileManager, atr);

  QString path = QDir::toNativeSeparators( QString("%1/Settings").arg(QCoreApplication::applicationDirPath()) );
  QDesktopServices::openUrl(QUrl("file:///" + path));
}

void OtherTab::slotChoiceOtherPathBtn_clicked()
{
  QString path = otherPathEdit->text();
  if (path.isEmpty()) path = QString("%1/Settings").arg(QCoreApplication::applicationDirPath());

  QString d = QFileDialog::getExistingDirectory(this, QString("Open Directory"), path, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (d == "") return; // Ако не се избере нов път. Ако SVars->pathToSettings е бил празен стринг ще си остане празен стринг и няма да има ефект при натискане на OK бутона.
  SVars->pathToSettings = d;
  otherPathEdit->setText( QDir::toNativeSeparators(d) );
}

void OtherTab::slotProxyType(const int index)
{
  SVars->proxyType = (quint8)index;

  if (proxyTypeComboBox->currentIndex() == PROXY__NO_PROXY)
  {
    proxyHostNameEdit->setEnabled(false);
    proxyPortEdit->setEnabled(false);
    proxyHostNameEdit->setVisible(false);
    proxyPortEdit->setVisible(false);
  }
  else
  {
    proxyHostNameEdit->setEnabled(true);
    proxyPortEdit->setEnabled(true);
    proxyHostNameEdit->setVisible(true);
    proxyPortEdit->setVisible(true);
  }
}

void OtherTab::slotProxyHostName(const QString proxyHostName)
{
  SVars->proxyHostName = proxyHostName;
}

void OtherTab::slotProxyPort(const QString proxyPort)
{
  SVars->proxyPort = (quint16)proxyPort.toUInt();
}

void OtherTab::slotTrayIcon_Toggled(const bool checked)
{
  SVars->enableTrayIcon = checked;
}

void OtherTab::slotCreateExampleDctCmtBtn_clicked()
{
  QFile *file;
  QString fileName;
  QString text;

  // Създава примерен речник:
  text = QString(
    "STRUCTURE_VERSION=1\n"
    "LAST_MODIFY_DATE=2013.06.20\n"
    "FONT_FAMILY=\n"
    "LAYOUT_DIRECTION=LeftToRight\n"
    "DICT_NAME=<Example Dictionary>\n"
    "DICT_VERSION=1.0\n"
    "DICT_AUTHOR=MatCrossBible\n"
    "DICT_SHORT_DESCRIPTION=Example Dictionary\n"
    "DICT_DESCRIPTION__BEGIN\n"
    "<b>Example Dictionary</b><br />\n"
    "This is example dictionary.\n"
    "DICT_DESCRIPTION__END\n"
    "\n"
    "CHARSET_1__ENABLE=yes\n"
    "CHARSET_1__CHARS=abcdefghijklmnopqrstuvwxyzàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ\n"
    "CHARSET_1__COLOR=#000000\n"
    "CHARSET_1__BOLD=yes\n"
    "CHARSET_1__ITALIC=no\n"
    "CHARSET_1__UNDERLINE=no\n"
    "\n"
    "CHARSET_2__ENABLE=no\n"
    "CHARSET_2__CHARS=1234567890\n"
    "CHARSET_2__COLOR=#800000\n"
    "CHARSET_2__BOLD=no\n"
    "CHARSET_2__ITALIC=no\n"
    "CHARSET_2__UNDERLINE=no\n"
    "\n"
    "CHARSET_3__ENABLE=no\n"
    "CHARSET_3__CHARS=\n"
    "CHARSET_3__COLOR=\n"
    "CHARSET_3__BOLD=\n"
    "CHARSET_3__ITALIC=\n"
    "CHARSET_3__UNDERLINE=\n"
    "\n"
    "TEXT_IN_BRACKET__ENABLE=yes\n"
    "TEXT_IN_BRACKET__COLOR=#777777\n"
    "TEXT_IN_BRACKET__BOLD=\n"
    "TEXT_IN_BRACKET__ITALIC=\n"
    "TEXT_IN_BRACKET__UNDERLINE=\n"
    "\n"
    "TEXT_IN_SQUARE_BRACKET__ENABLE=yes\n"
    "TEXT_IN_SQUARE_BRACKET__COLOR=#00AAAA\n"
    "TEXT_IN_SQUARE_BRACKET__BOLD=yes\n"
    "TEXT_IN_SQUARE_BRACKET__ITALIC=no\n"
    "TEXT_IN_SQUARE_BRACKET__UNDERLINE=no\n"
    "\n"
    "TEXT_IN_BRACE__ENABLE=yes\n"
    "TEXT_IN_BRACE__COLOR=\n"
    "TEXT_IN_BRACE__BOLD=\n"
    "TEXT_IN_BRACE__ITALIC=yes\n"
    "TEXT_IN_BRACE__UNDERLINE=\n"
    "\n"
    "LATIN_NUMERATION__ENABLE=yes\n"
    "LATIN_NUMERATION__COLOR=#0080FF\n"
    "LATIN_NUMERATION__BOLD=yes\n"
    "LATIN_NUMERATION__ITALIC=no\n"
    "LATIN_NUMERATION__UNDERLINE=no\n"
    "\n"
    "ARABIC_NUMERATION__ENABLE=yes\n"
    "ARABIC_NUMERATION__COLOR=#FF6050\n"
    "ARABIC_NUMERATION__BOLD=yes\n"
    "ARABIC_NUMERATION__ITALIC=no\n"
    "ARABIC_NUMERATION__UNDERLINE=no\n"
    "\n"
    "EQUAL_SYMBOLS__ENABLE=no\n"
    "EQUAL_SYMBOLS__EXPRESSIONS=à=a,á=a,â=a,ã=a,ä=a,å=a,ç=c,è=e,é=e,ê=e,ë=e,ì=i,í=i,î=i,ï=i,ñ=n,ò=o,ó=o,ô=o,õ=o,ö=o,ù=u,ú=u,û=u,ü=u,ý=y,ÿ=y,æ=æ,ð=ð,þ=þ\n"
    "\n"
    "##Word\n"
    "[wə:d]\n"
    "I. Description Описание Description...\n"
    "1. Description Описание (Description)...\n"
    "2. Description Описание [Description]...\n"
    "3. Description Описание {Description}...\n"
    "II. Description Описание Description...\n"
    "1. Description Описание Description 1\n"
    "2. Description Описание Description 2\n"
    "##Word2\n"
    "Description Описание 2\n"
    "Description Описание 2\n"
    "##Word3\n"
    "Description Описание 3\n"
    "Description Описание 3\n"
    "##Word4\n"
    "Description Описание 4\n"
    "Description Описание 4\n"
    "##Word5\n"
    "Description Описание 5\n"
    "Description Описание 5\n"
    "##GOD\n"
    "[gɔd]\n"
    "I. n бог\n"
    "false GODs кумири\n"
    "to depart to GOD отивам си от тоя свят\n"
    "by G.! ей богу! GOD damn! дявол да го вземе! по дяволите! GOD forbid! не дай боже! да не дава господ! пази боже! GOD grant that дай боже\n"
    "GOD helps those who help themselves помогни си сам и бог ще ти помогне, бог дава, ала в кошара не вкарва\n"
    "to make a GOD of боготворя, правя кумир от\n"
    "to be with GOD умрял/починал съм\n"
    "eye GODs and little fishes! я гледай! дявол да го вземе! (изразява учудване престорено негодувание)\n"
    "to play GOD смятам се за все силен\n"
    "GOD's own country земен рай\n"
    "GOD's plenty/quantity разг. изобилие\n"
    "it's on the knees/in the lap of the GODs един господ знае, съдбата ще реши\n"
    "II. v (-dd-) боготворя, издигам в кумир\n"
    "to GOD it разг. придавам си важност, смятам се за господ\n"
    "##БОГ\n"
    "1. God; the Lord; Ancient of Days;\n"
    "(при многобожие) god, deity;\n"
    "(идеал, кумир) god. idol;\n"
    "БОГ ми е свидетел I call heaven to witness помогни си сам, за да ти помогне БОГ God helps those who help themselves;\n"
    "когото БОГ иска да накаже, най-напред му взема ума whom God would ruin he first deprives of reason;\n"
    "БОГът на морето the god of the see;\n"
    "2. (възклицание, обръщение);\n"
    "(страх, болке) боже! боже мой! божичко! good Lord! good Gracious! goodness! dear me! oh, dear! леле боже! goodness! goodness gracious' great/good God! (почуда, изненада) боже мой! bless my soul/life! разг. ам. Holy Mackerel! (опасения) боже опази! пази боже! (God) save the mark! не дай боже God/ Heaven forbid;\n"
    "БОГ да е на помощ на... heaven help...;\n"
    "(задоволство, благодар-ност) слава БОГ у, благодаря на БОГа, сполай ти боже thank God/goodness/heavens;\n"
    "(благо-словия, благопожелание, клетва) да даде-БОГ, дай боже may it please God;God grant;may it come true;may it be so;\n"
    "БОГ да те поживи God bless you;\n"
    "(клетва) БОГ да те убие (God) damn you;\n"
    "(увещание, уверяване) за БОГ a in God's name. in the name of God'. for mercy's sake! разг. for the love of Mike;\n"
    "ей БОГу honestly, really; really and truly;\n"
    "(неувереност) БОГ знае God knows;\n"
    "БОГ знае къде goodness knows where, (много далече) at the back of beyond;\n"
    "не е БОГ знае колко далеч it isn't as far away as all that;\n"
    "един БОГ знае God only knows;\n"
    "ако даде БОГ, ако е рекъл БОГ God willing;Deo volente;\n"
    "БОГ да го прости may he rest in peace. God rest his soul;\n"
    "ради БОГa for God's/goodness' sake;\n"
    "за нрава БОГа in vain;undeservedly;\n"
    "предавам БОГу дух give up the ghost;\n"
    "yield up the ghost/soul/spirit, предал БОГу дух departed to God; with God.\n"
    );

  QDir dir; dir.mkpath(QString("%1/DictAndComm").arg(QCoreApplication::applicationDirPath())); // Създава директорията, ако не е създадена.
  fileName = QString("%1/DictAndComm/_ExampleDictionary.dct").arg(QCoreApplication::applicationDirPath());
  file = new QFile(fileName);
  if (file->open(QFile::ReadWrite | QFile::Text | QIODevice::Truncate))
  {
    QTextStream out(file);
    out << text;
  }
  file->close();
  delete file;

  // Създава примерен коментар:
  text = QString(
    "STRUCTURE_VERSION=1\n"
    "LAST_MODIFY_DATE=2013.06.20\n"
    "FONT_FAMILY=Arial,Tahoma\n"
    "LAYOUT_DIRECTION=LeftToRight\n"
    "DICT_NAME=<Example Commentary>\n"
    "DICT_VERSION=1.0\n"
    "DICT_AUTHOR=MatCrossBible\n"
    "DICT_SHORT_DESCRIPTION=Example Commentary\n"
    "DICT_DESCRIPTION__BEGIN\n"
    "<b>Example Commentary</b><br />\n"
    "This is example commentary.\n"
    "DICT_DESCRIPTION__END\n"
    "\n"
    "CHARSET_1__ENABLE=no\n"
    "CHARSET_1__CHARS=abcdefghijklmnopqrstuvwxyz\n"
    "CHARSET_1__COLOR=#000000\n"
    "CHARSET_1__BOLD=yes\n"
    "CHARSET_1__ITALIC=no\n"
    "CHARSET_1__UNDERLINE=no\n"
    "\n"
    "CHARSET_2__ENABLE=no\n"
    "CHARSET_2__CHARS=1234567890\n"
    "CHARSET_2__COLOR=#800000\n"
    "CHARSET_2__BOLD=yes\n"
    "CHARSET_2__ITALIC=no\n"
    "CHARSET_2__UNDERLINE=no\n"
    "\n"
    "CHARSET_3__ENABLE=no\n"
    "CHARSET_3__CHARS=\n"
    "CHARSET_3__COLOR=\n"
    "CHARSET_3__BOLD=\n"
    "CHARSET_3__ITALIC=\n"
    "CHARSET_3__UNDERLINE=\n"
    "\n"
    "TEXT_IN_BRACKET__ENABLE=yes\n"
    "TEXT_IN_BRACKET__COLOR=#777777\n"
    "TEXT_IN_BRACKET__BOLD=\n"
    "TEXT_IN_BRACKET__ITALIC=\n"
    "TEXT_IN_BRACKET__UNDERLINE=\n"
    "\n"
    "TEXT_IN_SQUARE_BRACKET__ENABLE=no\n"
    "TEXT_IN_SQUARE_BRACKET__COLOR=\n"
    "TEXT_IN_SQUARE_BRACKET__BOLD=\n"
    "TEXT_IN_SQUARE_BRACKET__ITALIC=\n"
    "TEXT_IN_SQUARE_BRACKET__UNDERLINE=\n"
    "\n"
    "TEXT_IN_BRACE__ENABLE=no\n"
    "TEXT_IN_BRACE__COLOR=\n"
    "TEXT_IN_BRACE__BOLD=\n"
    "TEXT_IN_BRACE__ITALIC=\n"
    "TEXT_IN_BRACE__UNDERLINE=\n"
    "\n"
    "LATIN_NUMERATION__ENABLE=no\n"
    "LATIN_NUMERATION__COLOR=#0080FF\n"
    "LATIN_NUMERATION__BOLD=yes\n"
    "LATIN_NUMERATION__ITALIC=no\n"
    "LATIN_NUMERATION__UNDERLINE=no\n"
    "\n"
    "ARABIC_NUMERATION__ENABLE=no\n"
    "ARABIC_NUMERATION__COLOR=#FF6050\n"
    "ARABIC_NUMERATION__BOLD=yes\n"
    "ARABIC_NUMERATION__ITALIC=no\n"
    "ARABIC_NUMERATION__UNDERLINE=no\n"
    "\n"
    "EQUAL_SYMBOLS__ENABLE=no\n"
    "EQUAL_SYMBOLS__EXPRESSIONS=\n"
    "\n"
    "##1-37993\n"
    "Commentary for the <u>all</u> Bible.<br />Коментар за <b>цялата</b> Библия.\n\n"
    "Custom <font color=#FF6050><b>HTML</b></font> format.<br />Потребителски <font color=#FF6050><b>HTML</b></font> формат.\n\n"
    "<a href=\"160\"><font color=#00AAAA><b>Бит. 6:22</b></font></a><br /><a href=\"30125\">Мат. 5:3-11</a><br /><a href=\"37993\">Откр. 22:21</a><br />\n"
    "<a href=\"160\"><font color=#00AAAA><b>Gen. 6:22</b></font></a><br /><a href=\"30125\">Matt. 5:3-11</a><br /><a href=\"37993\">Rev. 22:21</a>\n"
    "##1-30032\n"
    "Commentary for the all Old Testament.<br />Коментар за целия Стар Завет.\n"
    "##30033-37993\n"
    "Commentary for the all New Testament.<br />Коментар за целия Нов Завет.\n"
    "##1-31\n"
    "Commentary for one chapter - Genesis 1.<br />Коментар за една цяла глава - Битие 1.\n"
    "##3\n"
    "Commentary for one verse - Genesis 1:3.<br />Коментар за един стих - Битие 1:3.\n"
    "##1-20;34;46-66\n"
    "Commentary for different verses - Genesis 1:1-20; Genesis 1:31; Genesis 2:15-25; Genesis 3:1-10.<br />Коментар за множество стихове - Битие 1:1-20; Битие 2:3; Битие 2:15-25; Битие 3:1-10.\n"
    "##1548-1590\n"
    "Commentary for Exodus 1:15 to Exodus 3:10.<br />Коментар за части от две и повече съседни глави - Изход 1:15 - Изход 3:10.\n"
    "##30033-31103\n"
    "Commentary for the book Matthew - all chapters.<br />Коментар за една цяла книга - Матей.\n"
    );

  fileName = QString("%1/DictAndComm/_ExampleCommentary.cmt").arg(QCoreApplication::applicationDirPath());
  file = new QFile(fileName);
  if (file->open(QFile::ReadWrite | QFile::Text | QIODevice::Truncate))
  {
    QTextStream out(file);
    out << text;
  }
  file->close();
  delete file;

  QMessageBox::information(this, QCoreApplication::applicationName(), QString("%1\n%2/DictAndComm").arg(MW->MO->TS->TOCreateDctCmtExampleFilesDone_v1).arg(QCoreApplication::applicationDirPath()));
}

