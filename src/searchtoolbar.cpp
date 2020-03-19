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

#include "searchtoolbar.h"

SearchWidget::SearchWidget(MainWindow *mainWindow) : QWidget()
{
  // За преоразмеряването на панела в реално време е важно всички настройки
  // в методите setSizePolicy() да са такива каквито са! Да не се пипат!
  // Потребителят може да задава максимална широчина, но ако е по-голяма от 270,
  // тулбарът не ще да стане по-голям (стои си на широчина 270 точки). За целта
  // използвам един етикет, който не се вижда, но е с много дълъг текст.
  // Той кара тулбара да се разтегне максимално, като широчината му вече зависи
  // от потребителската настройка. Цялата тази работа, е защото не искам да
  // използвам setMinimumWidth за тулбара. Ако го използвам то потребителски
  // зададената широчина на тулбара става автоматчино и минимална широчина на
  // главния прозорец.
  // Има нерешен проблем, който не е фатален. Ако е избран голям размер на шрифта и от
  // настройките започне да се намаля, всичко в тулбара се намаля в реално време с
  // изключение на височината на комбобокса. Така и не разбрах защо става така.
  // Освен това понякога си е наред. След рестает на програмата той е с нормален размер.

  MW = mainWindow;

  setMinimumSize(1, 1); // Не трябва да е 0, защото няма ефект.

  percentIconHeight = MW->MO->SVars.searchToolBarFontSize;
  if (MW->MO->SVars.searchToolBarFontSize > 16)
    percentIconHeight = 16;
  
  if (MW->MO->SVars.searchToolBarWidth <= 220)
    percentIconWidth = 40;
  else if (MW->MO->SVars.searchToolBarWidth > 400)
    percentIconWidth = 160;
  else
    percentIconWidth = 80;

  searchWords = "";
  searchWordsList.clear();
  caseSensitivitySearch = Qt::CaseInsensitive;


  searchLineEdit = new QLineEdit("");
  //searchLineEdit->setToolTip(MW->MO->TS->SearchInBible);
  searchLineEdit->setMinimumSize(1, 1);
  searchLineEdit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed); // Това е важно (Ignored и Fixed) за преоразмеряването на панела при смяна на големината на шрифта.

  targetTextComBox = new QComboBox;
  targetTextComBox->setToolTip(MW->MO->TS->SearchInBibleTargetText_v1);
  targetTextComBox->setEditable(false);
  targetTextComBox->setMinimumSize(1, 1);
  //targetTextComBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength); // Това не е важно за преоразмеряването.
  targetTextComBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed); // Това е важно (Ignored и Fixed) за преоразмеряването на панела при смяна на големината на шрифта.
  connect(targetTextComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTargetText(int)));

  searchBtn = new QToolButton;
  searchBtn->setIconSize(QSize(32, 32)); // Задава се голяма икона, а то само си я намаля според размера на бутона.
  searchBtn->setIcon( Icons::icon_Search(32, 32, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) );
  searchBtn->setToolTip(MW->MO->TS->SearchInBible_v1);
  searchBtn->setMinimumSize(1, 1);
  searchBtn->setAutoRaise(true);
  searchBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred); // Това е важно (Fixed и Preferred) за преоразмеряването на панела при смяна на големината на шрифта.
  connect(searchBtn, SIGNAL(clicked()), this, SLOT(slotSearchGo()));

  showOptionsBtn = new QToolButton;
  showOptionsBtn->setIconSize(QSize(32, 32)); // Задава се голяма икона, а то само си я намаля според размера на бутона.
  showOptionsBtn->setIcon( Icons::icon_Settings(32, 32, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) );
  showOptionsBtn->setToolTip(MW->MO->TS->ShowHideOptions_v1);
  showOptionsBtn->setMinimumSize(1, 1);
  showOptionsBtn->setAutoRaise(true);
  showOptionsBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred); // Това е важно (Fixed и Preferred) за преоразмеряването на панела при смяна на големината на шрифта.
  connect(showOptionsBtn, SIGNAL(clicked()), this, SLOT(slotShowOptions()));

  frameOptions1 = new QFrame;
  frameOptions1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  frameOptions1->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameOptions1->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameOptions1->setMinimumWidth(10);
  frameOptions1->setVisible(false);

  searchRandomRBtn = new QRadioButton(MW->MO->TS->OptSearchRandom_v1, frameOptions1);
  searchRandomRBtn->setToolTip(MW->MO->TS->OptSearchRandomTT_v1);
  searchRandomRBtn->setMinimumWidth(10);
  connect(searchRandomRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchRandom(bool)));

  searchRootRBtn = new QRadioButton(MW->MO->TS->OptSearchRoot_v1, frameOptions1);
  searchRootRBtn->setToolTip(MW->MO->TS->OptSearchRootTT_v1);
  searchRootRBtn->setMinimumWidth(10);
  connect(searchRootRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchRoot(bool)));

  searchWordRBtn = new QRadioButton(MW->MO->TS->OptSearchWord_v1, frameOptions1);
  searchWordRBtn->setToolTip(MW->MO->TS->OptSearchWordTT_v1);
  searchWordRBtn->setMinimumWidth(10);
  connect(searchWordRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchWord(bool)));

  frameOptions2 = new QFrame;
  frameOptions2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  frameOptions2->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameOptions2->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameOptions2->setMinimumWidth(10);
  frameOptions2->setVisible(false);

  searchAllWordsRBtn = new QRadioButton(MW->MO->TS->OptSearchAll_v1, frameOptions2);
  searchAllWordsRBtn->setToolTip(MW->MO->TS->OptSearchAllTT_v1);
  searchAllWordsRBtn->setMinimumWidth(10);
  connect(searchAllWordsRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchAllWords(bool)));

  searchAnyWordsRBtn = new QRadioButton(MW->MO->TS->OptSearchAny_v1, frameOptions2);
  searchAnyWordsRBtn->setToolTip(MW->MO->TS->OptSearchAnyTT_v1);
  searchAnyWordsRBtn->setMinimumWidth(10);
  connect(searchAnyWordsRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchAnyWords(bool)));

  searchPhraseRBtn = new QRadioButton(MW->MO->TS->OptSearchPhrase_v1, frameOptions2);
  searchPhraseRBtn->setToolTip(MW->MO->TS->OptSearchPhraseTT_v1);
  searchPhraseRBtn->setMinimumWidth(10);
  connect(searchPhraseRBtn, SIGNAL(toggled(bool)), this, SLOT(slotSearchPhrase(bool)));

  frameOptions3 = new QFrame;
  frameOptions3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  frameOptions3->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameOptions3->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameOptions3->setMinimumWidth(10);
  frameOptions3->setVisible(false);

  searchWildCardChBox = new QCheckBox(MW->MO->TS->OptSearchWildCard_v1, frameOptions3);
  searchWildCardChBox->setToolTip(MW->MO->TS->OptSearchWildCardTT_v1);
  searchWildCardChBox->setChecked(false);
  searchWildCardChBox->setMinimumWidth(10);
  connect(searchWildCardChBox, SIGNAL(toggled(bool)), this, SLOT(slotSearchWildCard(bool)));

  searchCaseSensitivityChBox = new QCheckBox(MW->MO->TS->OptSearchCaseSensitive_v1, frameOptions3);
  searchCaseSensitivityChBox->setToolTip(MW->MO->TS->OptSearchCaseSensitivityTT_v1);
  searchCaseSensitivityChBox->setChecked(false);
  searchCaseSensitivityChBox->setMinimumWidth(10);
  connect(searchCaseSensitivityChBox, SIGNAL(toggled(bool)), this, SLOT(slotSearchCaseSensitivity(bool)));

  searchInChapter = new QCheckBox(MW->MO->TS->OptSearchInChapter_v1, frameOptions3);
  searchInChapter->setToolTip(MW->MO->TS->OptSearchInChapterTT_v1);
  searchInChapter->setChecked(false);
  searchInChapter->setMinimumWidth(10);
  connect(searchInChapter, SIGNAL(toggled(bool)), this, SLOT(slotSearchInChapter(bool)));

  mDock = new MDock();
  mDock->setDockWidgetTabbedTitleBar(true);
  mDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mDock->setDockMargins(0, 1, 0, 0); // LTRB
  //mDock->setDockWidgetMinSizePr(QSize(10, 10));
  //mDock->setDockWidgetPadding(2);
  //mDock->setDockBgColor(QColor(225, 225, 225));
  //mDock->setTrackFrameColor(QColor(0, 170, 170));
  mDock->setProperties(false, false, true, false);
  mDock->setDockGridState("0^100_1_0^100"); // Един ред с един раздел.
  mDock->setMinimumSize(1, 30); // Не трябва да е 0, защото няма ефект.

  mDockWidget1 = new MDockWidget(mDock, QString("<b>%1</b>").arg(MW->MO->TS->Filter_v1), false, false, MW->MO->SVars.docks3DTitleBar, 1, 0);
  mDockWidget2 = new MDockWidget(mDock, QString("<b>%1</b>").arg(MW->MO->TS->Results_v1), false, false, MW->MO->SVars.docks3DTitleBar, 2, 0);
  mDockWidget3 = new MDockWidget(mDock, QString("<b>%1</b>").arg(MW->MO->TS->Map_v1), false, false, MW->MO->SVars.docks3DTitleBar, 3, 0);

  mDockWidget1->setDockWidgetDisallowCloseLevel1(true);
  mDockWidget2->setDockWidgetDisallowCloseLevel1(true);
  mDockWidget3->setDockWidgetDisallowCloseLevel1(true);

  // Ако тези редове се използват тук, големината на шрифта ще е като тази на заглавните ленти на всички прозорци, но е
  // някак по-логично да е като големината на текста на компонентите в тулбара, затова долните редове са закоментирани.
  //mDockWidget1->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  //mDockWidget2->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  //mDockWidget3->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  mDockWidget1->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);
  mDockWidget2->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);
  mDockWidget3->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);

  mDockWidget1->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget2->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget3->setDockWidgetBgColor(MW->MO->SVars.appColorF);

  mDockWidget1->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget2->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget3->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  
  mDockWidget1->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget2->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget3->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  
  mDockWidget1->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  mDockWidget2->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  mDockWidget3->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);

  connect(mDockWidget1, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotDockWidgetRaised(MDock *, MDockWidget *)));
  connect(mDockWidget2, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotDockWidgetRaised(MDock *, MDockWidget *)));
  connect(mDockWidget3, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotDockWidgetRaised(MDock *, MDockWidget *)));

  mDock->addDockWidget(mDockWidget1, 0, 0); // Всички са на една позиция, за да участват в табове.
  mDock->addDockWidget(mDockWidget2, 0, 0);
  mDock->addDockWidget(mDockWidget3, 0, 0);

  mDockWidget2->setCurrentTab();

  QWidget *tab1 = new QWidget();
  tab1->setMinimumSize(1, 1);
  //tab1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QGridLayout *tab1GridLayout = new QGridLayout(tab1);
  tab1GridLayout->setContentsMargins(0, 0, 0, 0);
  mDockWidget1->setWidget(tab1);

  QWidget *tab2 = new QWidget();
  tab2->setMinimumSize(1, 1);
  //tab2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QGridLayout *tab2GridLayout = new QGridLayout(tab2);
  tab2GridLayout->setContentsMargins(0, 0, 0, 0);
  mDockWidget2->setWidget(tab2);

  QWidget *tab3 = new QWidget();
  tab3->setMinimumSize(1, 1);
  //tab3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QGridLayout *tab3GridLayout = new QGridLayout(tab3);
  tab3GridLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  tab3GridLayout->setSpacing(0); // Разстояние между обектите. Тук е 0, защото по-долу, в маргините на трите бутона, има зададен долен маргин 1 (разстоянието между бутоните и картата).
  //tab3GridLayout->setHorizontalSpacing(1);
  //tab3GridLayout->setVerticalSpacing(1);
  mDockWidget3->setWidget(tab3);

  booksTreeWidget = new QTreeWidget(tab1);
  booksTreeWidget->setIconSize(QSize(percentIconWidth, percentIconHeight));
  booksTreeWidget->setMinimumSize(10, 1);
  booksTreeWidget->setFrameShape(QFrame::NoFrame);
  booksTreeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Това е важно (Expanding и Expanding) за преоразмеряването на панела при смяна на големината на шрифта.
  booksTreeWidget->setColumnCount(3);
  booksTreeWidget->setHeaderHidden(true); // Това скрива заглавната лента.
  booksTreeWidget->setIndentation(-1); // Това премахва полето, където е очертанието на дървото.
  booksTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
  //connect(booksTreeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
  connect(booksTreeWidget, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(slotItemActivated(QTreeWidgetItem*, int)));
  connect(booksTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemClicked(QTreeWidgetItem*, int)));
  tab1GridLayout->addWidget(booksTreeWidget, 0, 0, 1, 1);

  treeWidgetItemAll = new QTreeWidgetItem(booksTreeWidget);
  treeWidgetItemAll->setHidden(true);
  booksTreeWidget->addTopLevelItem(treeWidgetItemAll);
  treeWidgetItemOld = new QTreeWidgetItem(booksTreeWidget);
  treeWidgetItemOld->setHidden(true);
  booksTreeWidget->addTopLevelItem(treeWidgetItemOld);
  treeWidgetItemNew = new QTreeWidgetItem(booksTreeWidget);
  treeWidgetItemNew->setHidden(true);
  booksTreeWidget->addTopLevelItem(treeWidgetItemNew);
  for (quint8 i = 0; i < 77; i++)
  {
    treeWidgetItem[i] = new QTreeWidgetItem(booksTreeWidget);
    treeWidgetItem[i]->setHidden(true);
    booksTreeWidget->addTopLevelItem(treeWidgetItem[i]);
  }
  booksTreeWidget->resizeColumnToContents(0);
  booksTreeWidget->resizeColumnToContents(1);
  booksTreeWidget->resizeColumnToContents(2);

  QFont font;
  font.setFamily(MW->MO->SVars.fontFamily);
  font.setPointSize(MW->MO->SVars.fontSize);
  font.setFixedPitch(false);
  searchView = new TextView(MW, tab2);
  searchView->setFont(font);
  searchView->setMinimumSize(10, 20);
  searchView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  searchView->initializeTextView(TEXT_MODE__SEARCH);
  searchView->setHtml(getSearchMethodInfo());
  searchView->dockWidget = 0;
  tab2GridLayout->addWidget(searchView, 0, 0, 1, 1);

  imageSaveBtn = new QToolButton;
  imageSaveBtn->setText(MW->MO->TS->Save_v1);
  imageSaveBtn->setMinimumSize(1, 10);
  imageSaveBtn->setAutoRaise(false);
  imageSaveBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // Това е важно (Preferred и Preferred).
  connect(imageSaveBtn, SIGNAL(clicked()), this, SLOT(slotImageSave()));

  imageWidthDecreaseBtn = new QToolButton;
  imageWidthDecreaseBtn->setText(QString(">●<")); // >●•< W-
  //imageWidthDecreaseBtn->setMinimumSize(1, 10);
  imageWidthDecreaseBtn->setAutoRaise(false);
  connect(imageWidthDecreaseBtn, SIGNAL(clicked()), this, SLOT(slotImageWidthDecrease()));

  imageWidthIncreaseBtn = new QToolButton;
  imageWidthIncreaseBtn->setText(QString("<●>")); // <●•> W+
  //imageWidthIncreaseBtn->setMinimumSize(1, 10);
  imageWidthIncreaseBtn->setAutoRaise(false);
  connect(imageWidthIncreaseBtn, SIGNAL(clicked()), this, SLOT(slotImageWidthIncrease()));

  imageWidth = MW->MO->SVars.searchToolBarWidth - 60; // Стойностите на searchToolBarWidthса през 20 (от 100 до 980).
  imageWidth/=2; imageWidth*=2; // Това е, за да стане четно число, в случай, че някой е задал произволно число в INI файла.
  imageLabel = new Label("");
  //imageLabel->setContentsMargins(0, 3, 0, 3); //left, top, right, bottom - Това е коментирано, защото е указано картинката да е в центъра на етикета, а размерът на самия етикет е малко по-голям от картинката.
  imageLabel->setAlignment(Qt::AlignCenter);
  connect(imageLabel, SIGNAL(mouseMoveOrPressEvent(int, int, bool)), this, SLOT(slotImageMouseMoveOrPressEvent(int, int, bool)));

  imageScrollArea = new QScrollArea;
  imageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  imageScrollArea->setWidget(imageLabel);
  imageScrollArea->setFrameShape(QFrame::NoFrame);

  QHBoxLayout *tab3ButtonsLayout = new QHBoxLayout();
  tab3ButtonsLayout->setSpacing(1); // Разстояние между обектите.
  tab3ButtonsLayout->setContentsMargins(1, 1, 1, 1); // LTRB
  tab3ButtonsLayout->addWidget(imageSaveBtn);
  tab3ButtonsLayout->addWidget(imageWidthDecreaseBtn);
  tab3ButtonsLayout->addWidget(imageWidthIncreaseBtn);
  tab3GridLayout->addLayout(tab3ButtonsLayout, 0, 0);
  tab3GridLayout->addWidget(imageScrollArea, 1, 0);
  //tab3GridLayout->addWidget(imageSaveBtn, 0, 0);
  //tab3GridLayout->addWidget(imageWidthDecreaseBtn, 0, 1);
  //tab3GridLayout->addWidget(imageWidthIncreaseBtn, 0, 2);
  //tab3GridLayout->addWidget(imageScrollArea, 1, 0, 1, 3);

  QFrame *frameButtons = new QFrame;
  frameButtons->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); // Тук трябва да е Fixed, за да не се свива панелът, защото ще се свият и бутоните и полетата в него.
  frameButtons->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameButtons->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameButtons->setMinimumWidth(10);

  QGridLayout *frameButtonsLayout = new QGridLayout(frameButtons);
  frameButtonsLayout->setSpacing(1); // Разстояние между обектите.
  frameButtonsLayout->setContentsMargins(1, 1, 1, 1); // LTRB
  frameButtonsLayout->addWidget(searchLineEdit, 0, 0);
  frameButtonsLayout->addWidget(searchBtn, 0, 1);
  frameButtonsLayout->addWidget(targetTextComBox, 1, 0);
  frameButtonsLayout->addWidget(showOptionsBtn, 1, 1);

  QColor colorA = MW->MO->SVars.appColorB;   colorA.setAlpha(80); // Този цвят ще се сменя само при пускане на програмата, не и при смяна на цветовете от настройките, но това не е фатално.
  QPalette pal;
  pal.setBrush(QPalette::WindowText, colorA);

  QFrame *frameHLine1 = new QFrame;
  frameHLine1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  frameHLine1->setMinimumHeight(3);
  frameHLine1->setMaximumHeight(3);
  frameHLine1->setFrameShape(QFrame::HLine); //StyledPanel Panel NoFrame
  frameHLine1->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameHLine1->setMinimumWidth(10);
  frameHLine1->setPalette(pal);

  QFrame *frameHLine2 = new QFrame;
  frameHLine2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  frameHLine2->setMinimumHeight(3);
  frameHLine2->setMaximumHeight(3);
  frameHLine2->setFrameShape(QFrame::HLine); //StyledPanel Panel NoFrame
  frameHLine2->setFrameShadow(QFrame::Plain); // Raised Sunken Plain
  frameHLine2->setMinimumWidth(10);
  frameHLine2->setPalette(pal);

  QVBoxLayout *frameOptions1Layout = new QVBoxLayout(frameOptions1);
  frameOptions1Layout->setSpacing(0); // Разстояние между обектите.
  frameOptions1Layout->setContentsMargins(3, 0, 3, 0);
  frameOptions1Layout->addWidget(searchRandomRBtn);
  frameOptions1Layout->addWidget(searchRootRBtn);
  frameOptions1Layout->addWidget(searchWordRBtn);
  frameOptions1Layout->addWidget(frameHLine1);

  QVBoxLayout *frameOptions2Layout = new QVBoxLayout(frameOptions2);
  frameOptions2Layout->setSpacing(0); // Разстояние между обектите.
  frameOptions2Layout->setContentsMargins(3, 0, 3, 0);
  frameOptions2Layout->addWidget(searchAllWordsRBtn);
  frameOptions2Layout->addWidget(searchAnyWordsRBtn);
  frameOptions2Layout->addWidget(searchPhraseRBtn);
  frameOptions2Layout->addWidget(frameHLine2);

  QVBoxLayout *frameOptions3Layout = new QVBoxLayout(frameOptions3);
  frameOptions3Layout->setSpacing(0); // Разстояние между обектите.
  frameOptions3Layout->setContentsMargins(3, 0, 3, 0);
  frameOptions3Layout->addWidget(searchWildCardChBox);
  frameOptions3Layout->addWidget(searchCaseSensitivityChBox);
  frameOptions3Layout->addWidget(searchInChapter);

  QVBoxLayout *frameMain = new QVBoxLayout(this);
  frameMain->layout()->setMargin(0); // Марджини.
  frameMain->layout()->setSpacing(0); // Разстояние между обектите.
  frameMain->addWidget(frameButtons);
  frameMain->addWidget(frameOptions1);
  frameMain->addWidget(frameOptions2);
  frameMain->addWidget(frameOptions3);
  frameMain->addWidget(mDock);

  searchView->setColorScheme();
  searchLineEdit->setFocus();  // Поставя полето за търсене в Библията на фокус.
  searchLineEdit->selectAll(); // Селектира текста, за да е по-лесно да се напише нов.


  targetBooks = "";
  for (quint8 i = 0; i < 77; i++)
  {
    searchIn[i] = 0;
  }

  currentRow = 0;

  searchTargetTextIndex = MW->MO->SVars.searchTargetTextIndex; // Долната инициализация ще промени MW->MO->SVars.searchTargetText, но веднага след нея ще се възстанови истинската ѝ стойност.
  for (int i = 0; i < MW->MO->bibleTextList.size(); i++)
  {
    targetTextComBox->addItem(MW->MO->bibleTextList.at(i).name);
  }
  targetTextComBox->setCurrentIndex(searchTargetTextIndex); // Тук MW->MO->SVars.searchTargetText ще вземе отново първоначалната си стойност, която е била променена по време на горната инизиализация (поради извикването на слота slotTargetText).

  searchMethod = SEARCH_METHOD__RANDOM;
  searchRandomRBtn->setChecked(true);

  searchWordsLogic = SEARCH_WORDS_LOGIC__ALL;
  searchAllWordsRBtn->setChecked(true);

  searchWildCardChBox->setChecked(false);
  caseSensitivitySearch = Qt::CaseInsensitive;
  searchCaseSensitivityChBox->setChecked(false);
  searchInChapter->setChecked(false);

  if (MW->MO->bibleTextList.size() > 0)
  {
    tBibleText = &MW->MO->bibleTextList[MW->MO->SVars.searchTargetTextIndex];
    targetBibleText = tBibleText;
    slotSetFontSize(); //slotRefreshPalette(); - този се извиква в slotSetFontSize(). // Този слот трябва да е в if-а, за да не изгърми, ако няма нито един текст.
  }
  else
  {
    tBibleText = 0;
    targetBibleText = 0;
  }

  slotSetColors();
}

SearchWidget::~SearchWidget()
{
  delete mDockWidget1; // Без тези програмата крашва при спиране.
  delete mDockWidget2; //
  delete mDockWidget3; //
}

void SearchWidget::slotTargetText(int index)
{
  if (index < 0) return;
  MW->MO->SVars.searchTargetTextIndex = index;
  tBibleText = &MW->MO->bibleTextList[index];

  QFont font = searchLineEdit->font();
  font.setFamily(MW->MO->bibleTextList[index].fontFamily);
  searchLineEdit->setFont(font);

  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotShowOptions()
{
  frameOptions1->setVisible(!frameOptions1->isVisible());
  frameOptions2->setVisible(!frameOptions2->isVisible());
  frameOptions3->setVisible(!frameOptions3->isVisible());
}

void SearchWidget::slotSearchRandom(bool checked)
{
  if (checked) searchMethod = SEARCH_METHOD__RANDOM;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchRoot(bool checked)
{
  if (checked) searchMethod = SEARCH_METHOD__ROOT;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchWord(bool checked)
{
  if (checked) searchMethod = SEARCH_METHOD__WORD;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchAllWords(bool checked)
{
  if (checked) searchWordsLogic = SEARCH_WORDS_LOGIC__ALL;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchAnyWords(bool checked)
{
  if (checked) searchWordsLogic = SEARCH_WORDS_LOGIC__ANY;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchPhrase(bool checked)
{
  if (checked) searchWordsLogic = SEARCH_WORDS_LOGIC__PHRASE;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchWildCard(bool checked)
{
  if (!checked) return;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchCaseSensitivity(bool /*checked*/)
{
  // Този if НЕ трябва да е тук, а в слота slotSearchGo, за да се запомня състоянието на caseSensitivity в момента на търсене, а не при произволно щракване в чекбокса.
  //if (checked)
  //  caseSensitivitySearch = Qt::CaseSensitive;
  //else
  //  caseSensitivitySearch = Qt::CaseInsensitive;

  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotSearchInChapter(bool checked)
{
  if (!checked) return;
  //searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

//void SearchWidget::slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
//{
//}

void SearchWidget::slotItemActivated(QTreeWidgetItem *item, int column)
{
  if (item == 0) return;
  if (currentRow == booksTreeWidget->indexOfTopLevelItem(item)) return;
  currentRow = booksTreeWidget->indexOfTopLevelItem(item);
  slotCurrentItemChanged(item, column);
}

void SearchWidget::slotItemClicked(QTreeWidgetItem *item, int column)
{
  if (item == 0) return;
  if (currentRow == booksTreeWidget->indexOfTopLevelItem(item)) return;
  currentRow = booksTreeWidget->indexOfTopLevelItem(item);
  slotCurrentItemChanged(item, column);
}

void SearchWidget::slotCurrentItemChanged(QTreeWidgetItem */*item*/, int /*column*/)
{
  if (currentRow == 0)
  {
    for (quint8 i = 0; i < 77; i++)
      searchIn[i] = 1;

    if (!MW->MO->SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити не трябва да се търси в тях.
    {
      searchIn[39] = 0; searchIn[40] = 0; searchIn[41] = 0;
      searchIn[42] = 0; searchIn[43] = 0; searchIn[44] = 0;
      searchIn[45] = 0; searchIn[46] = 0; searchIn[47] = 0;
      searchIn[48] = 0; searchIn[49] = 0;
    }

    targetBooks = MW->MO->TS->AllBooks_v1;
    searchGo(false);
  }
  else if (currentRow == 1)
  {
    for (quint8 i = 0; i < 50; i++)
      searchIn[i] = 1;
    for (quint8 i = 50; i < 77; i++)
      searchIn[i] = 0;

    if (!MW->MO->SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити не трябва да се търси в тях.
    {
      searchIn[39] = 0; searchIn[40] = 0; searchIn[41] = 0;
      searchIn[42] = 0; searchIn[43] = 0; searchIn[44] = 0;
      searchIn[45] = 0; searchIn[46] = 0; searchIn[47] = 0;
      searchIn[48] = 0; searchIn[49] = 0;
    }

    targetBooks = MW->MO->TS->TheOldTestament_v1;
    searchGo(false);
  }
  else if (currentRow == 2)
  {
    for (quint8 i = 0; i < 50; i++)
      searchIn[i] = 0;
    for (quint8 i = 50; i < 77; i++)
      searchIn[i] = 1;

    targetBooks = MW->MO->TS->TheNewTestament_v1;
    searchGo(false);
  }
  else
  {
    for (quint8 i = 0; i < 77; i++)
      searchIn[i] = 0;

    searchIn[currentRow-3] = 1;

    targetBooks = MW->MO->bookShortNameArr[currentRow-3]; // Тук да е bookShortNameArr, дори ако на другите места се използва bookMinNameArr.
    searchGo(false);
  }
}

void SearchWidget::slotSearchGo()
{
  searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
  
  QString text = searchLineEdit->text().trimmed(); // Премахва началните и крайните интервали и табулации.

  if ( text.isEmpty() ) return;
  if ( MW->MO->bibleTextList.size() == 0 ) return;

  if (searchCaseSensitivityChBox->isChecked()) // Този if трябва да е тук, а не в слота slotSearchCaseSensitivity, за да се запомня състоянието на caseSensitivity в момента на търсене, а не при произволно щракване в чекбокса.
    caseSensitivitySearch = Qt::CaseSensitive;
  else
    caseSensitivitySearch = Qt::CaseInsensitive;

  searchWordsList.clear();

  searchWords = "";
  if (searchWildCardChBox->isChecked()) searchWords += MW->MO->TS->OptSearchWildCard_v1 + "<br>";

  if (caseSensitivitySearch == Qt::CaseSensitive)
    searchWords += MW->MO->TS->OptSearchCaseSensitive_v1 + "<br>";
  else
    searchWords += MW->MO->TS->OptSearchCaseInsensitive_v1 + "<br>";

  if (searchInChapter->isChecked()) searchWords += MW->MO->TS->OptSearchInChapter_v1 + "<br>";

  if (!searchInChapter->isChecked()) // Ако се прави стандартно търсене (в стих).
  {
    if (searchWordsLogic == SEARCH_WORDS_LOGIC__ALL) searchWords += MW->MO->TS->VersesContainAllSearchedWords_v1;
    else if (searchWordsLogic == SEARCH_WORDS_LOGIC__ANY) searchWords += MW->MO->TS->VersesContainAnySearchedWord_v1;
    else if (searchWordsLogic == SEARCH_WORDS_LOGIC__PHRASE) searchWords += MW->MO->TS->VersesContainSearchedPhrase_v1;
  }
  else // Ако се прави нестандартно търсене (в глава).
  {
    if (searchWordsLogic == SEARCH_WORDS_LOGIC__ALL) searchWords += MW->MO->TS->ChaptersContainAllSearchedWords_v1;
    else if (searchWordsLogic == SEARCH_WORDS_LOGIC__ANY) searchWords += MW->MO->TS->ChaptersContainAnySearchedWord_v1;
    else if (searchWordsLogic == SEARCH_WORDS_LOGIC__PHRASE) searchWords += MW->MO->TS->ChaptersContainSearchedPhrase_v1;
  }
  searchWords += QString("<br>");

  // Модифициране на думите за търсене
  if (searchMethod == SEARCH_METHOD__RANDOM) // Търсене по произволна част от дума. ------------------------------------------------------------------
  {
    if (searchWildCardChBox->isChecked())
    {
      if (text == QString("*")) return; // Ако в полето за търсене е написана само една звездичка (ще причини увисване на програмата).
    }
    if (searchWordsLogic == SEARCH_WORDS_LOGIC__PHRASE)
      searchWordsList << text;
    else
      searchWordsList = text.split(QRegExp("\\s+"), QString::SkipEmptyParts); // \s+ - за разделител се приемат само интервалите.
    if (searchWordsList.count() == 0) return;
    searchWords = MW->MO->TS->OptSearchRandom_v1 + "<br>" + searchWords;
    for (int n = 0; n < searchWordsList.size(); n++)
    {
      searchWords += " <u><b>" + searchWordsList[n] + "</b></u>";
      searchWordsList[n] = QRegExp::escape(searchWordsList[n]);
      if (searchWildCardChBox->isChecked())
      {
        searchWords.replace(QString("*"), QString("<font color=%1>*</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWords.replace(QString("?"), QString("<font color=%1>?</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWordsList[n].replace(QString("*"), QString("w*"));
        searchWordsList[n].replace(QString("?"), QString("w"));
      }
    }
  }
  else if (searchMethod == SEARCH_METHOD__ROOT) // Търсене по корен на дума. -------------------------------------------------------------------------
  {
    if (searchWildCardChBox->isChecked())
    {
      if (text == QString("*")) return; // Ако в полето за търсене е написана само една звездичка (ще причини увисване на програмата).
      text.replace(QString("*"), QString("___111___")); // Замества символа * с ___111___, защото * е специален символ и ще бъде разпознат като разделител.
      text.replace(QString("?"), QString("___222___")); // Замества символа ? с ___222___, защото ? е специален символ и ще бъде разпознат като разделител.
    }

    if (searchWordsLogic == SEARCH_WORDS_LOGIC__PHRASE)
      searchWordsList << text;
    else
      searchWordsList = text.split(QRegExp("\\W+"), QString::SkipEmptyParts); // \W+ - за разделител се приемат всички символи различни от букви.
    if (searchWordsList.count() == 0) return;
    searchWords = MW->MO->TS->OptSearchRoot_v1 + "<br>" + searchWords;
    for (int n = 0; n < searchWordsList.size(); n++)
    {
      searchWords += " <u><b>" + searchWordsList[n] + "</b></u>";
      if (searchWildCardChBox->isChecked())
      {
        searchWords.replace(QString("___111___"), QString("<font color=%1>*</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWords.replace(QString("___222___"), QString("<font color=%1>?</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWordsList[n].replace(QString("___111___"), QString("\\w*"));
        searchWordsList[n].replace(QString("___222___"), QString("\\w"));
      }
      searchWordsList[n] = QString("\\b%1").arg(searchWordsList[n]);
    }
  }
  else if (searchMethod == SEARCH_METHOD__WORD) // Търсене по точна дума. ------------------------------------------------------------------------
  {
    if (searchWildCardChBox->isChecked())
    {
      if (text == QString("*")) return; // Ако в полето за търсене е написана само една звездичка (ще причини увисване на програмата).
      text.replace(QString("*"), QString("___111___")); // Замества символа * с ___111___, защото * е специален символ и ще бъде разпознат като разделител.
      text.replace(QString("?"), QString("___222___")); // Замества символа ? с ___222___, защото ? е специален символ и ще бъде разпознат като разделител.
    }

    if (searchWordsLogic == SEARCH_WORDS_LOGIC__PHRASE)
      searchWordsList << text;
    else
      searchWordsList = text.split(QRegExp("\\W+"), QString::SkipEmptyParts); // // \W+ - за разделител се приемат всички символи различни от букви.
    if (searchWordsList.count() == 0) return;
    searchWords = MW->MO->TS->OptSearchWord_v1 + "<br>" + searchWords;
    for (int n = 0; n < searchWordsList.size(); n++)
    {
      searchWords += " <u><b>" + searchWordsList[n] + "</b></u>";
      if (searchWildCardChBox->isChecked())
      {
        searchWords.replace(QString("___111___"), QString("<font color=%1>*</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWords.replace(QString("___222___"), QString("<font color=%1>?</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
        searchWordsList[n].replace(QString("___111___"), QString("\\w*"));
        searchWordsList[n].replace(QString("___222___"), QString("\\w"));
      }
      searchWordsList[n] = QString("\\b%1\\b").arg(searchWordsList[n]);
    }
  }

  for (quint8 i = 0; i < 77; i++)
    searchIn[i] = 1;

  if (!MW->MO->SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити не трябва да се търси в тях.
  {
    searchIn[39] = 0; searchIn[40] = 0; searchIn[41] = 0;
    searchIn[42] = 0; searchIn[43] = 0; searchIn[44] = 0;
    searchIn[45] = 0; searchIn[46] = 0; searchIn[47] = 0;
    searchIn[48] = 0; searchIn[49] = 0;
  }

  searchTargetTextIndex = MW->MO->SVars.searchTargetTextIndex;
  targetBibleText = tBibleText;
  targetBooks = MW->MO->TS->AllBooks_v1;
  searchGo(true);
}

void SearchWidget::searchGo(bool newSearch)
{
//QTime timer1, timer2, timer3;   int te1=0, te2=0, te3=0;   timer3.start(); //---------------------------------------------------------------------------------------------------------------
  searchView->reInitializeTextView();
  searchView->highlighter->addPatterns(searchWordsList, caseSensitivitySearch);
  searchView->highlighter->setEnableHighlighter(false);

  quint8 targetBook; // Целева книга (в която ще се търси).
  quint16 allVerses = 0;    // Всички стихове във всички целеви книги.
  quint16 allVersesInTargetBook = 0;    // Всички стихове в целевата книга.
  int foundVersesCountInTargetBook = 0; // Откритите стихове в целевата книга.
  int foundVersesCountAll = 0; // Откритите стихове във всички целеви книги.
  int foundVersesCount[77]; // Масив от откритите стихове в целевите книги.
  for (quint8 i = 0; i < 77; i++)
    foundVersesCount[i] = 0;
  quint32 *foundWordCount = new quint32[searchWordsList.count()]; // Брой срещания на отделните търсени думи само в откритите стихове.
  for (int i = 0; i < searchWordsList.count(); i++)
    foundWordCount[i] = 0;
  QString foundVerses = ""; // Самите открити стихове.
  QString statistics = "";  // Статистика.
  SEARCH_OPTIONS sOpt;      // Опции за търсене.
    sOpt.searchMethod = searchMethod;
    sOpt.searchWordsLogic = searchWordsLogic;
    sOpt.caseSensitivitySearch = caseSensitivitySearch;
  if (searchImageArray.size() != MAX_VERSES) searchImageArray.resize(MAX_VERSES); // При първоначално използване на масива.
  /*if (newSearch)*/ searchImageArray.fill(false);

//timer1.start(); //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
  bool searchRes = false;
  for (targetBook = 0; targetBook < 77; targetBook++)
  {
    if (searchIn[targetBook] == 1) // Ако трябва да се търси в тази книга.
    {
      if (!searchInChapter->isChecked()) // Ако се прави стандартно търсене (в стих).
        searchRes = MW->MO->searchInVerse(targetBibleText, targetBook+1, searchWordsList, sOpt, &foundVersesCountInTargetBook, &allVersesInTargetBook, foundWordCount, &searchImageArray, &foundVerses);
      else // Ако се прави нестандартно търсене (в глава).
        searchRes = MW->MO->searchInChapter(targetBibleText, targetBook+1, searchWordsList, sOpt, &foundVersesCountInTargetBook, &allVersesInTargetBook, foundWordCount, &searchImageArray, &foundVerses);

      if (!searchRes)
      {
        searchView->setPlainText(MW->MO->TS->SearchError_v1);
        return;
      }

      foundVersesCount[targetBook] = foundVersesCountInTargetBook;

      foundVersesCountAll += foundVersesCountInTargetBook;
      allVerses += allVersesInTargetBook;
    }
  }

  // Статистика:
  // ВЕРЕН (2001)
  // Всички книги
  // Търси част от дума
  // Не различава главни/малки букви
  // Стихове съдържащи всички търсени думи:
  // началото Бог: 5 (от общо 31102)
  // В откритите стихове:
  // началото: 5
  // Бог: 6

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
    statistics += QString("<div align=\"left\">");
  else // Ако текстът е с дясно подравняване.
    statistics += QString("<div align=\"right\">");

  if (foundVersesCountAll == 0)
  {
    statistics += QString("<font color=%1><b><div>%2</div></b></font><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg((!searchInChapter->isChecked()) ? MW->MO->TS->NoMatchesVerses_v1 : MW->MO->TS->NoMatchesChapters_v1);
    statistics += QString("<font color=%1><div>%2</div></font><br><hr>").arg(MW->MO->SVars.textInBracketsColorF.name()).arg(MW->MO->TS->ChangeSearchOptions_v1);
  }

  statistics += QString("<b>%1</b><br>").arg(MW->MO->TS->Statistics_v1);
  statistics += QString("<font color=%1>%2<br>%3</font><br>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(targetBibleText->name).arg(targetBooks);
  statistics += searchWords;

  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
    statistics += QString(": <font color=%1>%2</font> <font color=%3>(%4 %5)</font>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(foundVersesCountAll).arg(MW->MO->SVars.textInBracketsColorF.name()).arg(MW->MO->TS->TotalOf_v1).arg(allVerses);
  else // Ако текстът е с дясно подравняване.
    statistics.insert(statistics.lastIndexOf("<br>") + 4, QString("<font color=%1>%2</font> <font color=%3>%4 %5</font> ").arg(MW->MO->SVars.newTestamentColorF.name()).arg(foundVersesCountAll).arg(MW->MO->SVars.textInBracketsColorF.name()).arg(MW->MO->TS->TotalOf_v1).arg(allVerses)); // Тук не се използват скоби и двуеточия, защото разместват текста.

  if (foundVersesCountAll > 0)
  {
    if (!searchInChapter->isChecked()) // Ако се прави стандартно търсене (в стих).
      statistics += "<br>" + MW->MO->TS->InTheFoundVerses_v1;
    else // Ако се прави нестандартно търсене (в глава).
      statistics += "<br>" + MW->MO->TS->InTheFoundChapters_v1;

    int c = 0;
    foreach (QString word, searchWordsList)
    {
      word.remove(QString("\\b"));
      word.replace(QString("\\w*"), QString("<font color=%1>*</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
      word.replace(QString("\\w"), QString("<font color=%1>?</font>").arg(MW->MO->SVars.oldTestamentColorF.name()));
      word.replace(QString("\\("), QString("("));
      word.replace(QString("\\)"), QString(")"));
      word.replace(QString("\\["), QString("["));
      word.replace(QString("\\]"), QString("]"));
      word.replace(QString("\\{"), QString("{"));
      word.replace(QString("\\}"), QString("}"));
      word.replace(QString("\\$"), QString("$"));
      word.replace(QString("\\+"), QString("+"));
      word.replace(QString("\\."), QString("."));
      word.replace(QString("\\^"), QString("^"));
      word.replace(QString("\\|"), QString("|"));
      if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
        statistics += QString("<br><u><b>%1</b></u>: <font color=%2>%3</font>").arg(word).arg(MW->MO->SVars.newTestamentColorF.name()).arg(foundWordCount[c]);
      else // Ако текстът е с дясно подравняване.
        statistics += QString("<br><font color=%1>%2</font> <u><b>%3</b></u>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(foundWordCount[c]).arg(word);
      c++;
    }
  }
  statistics += QString("<hr></div>"); // div е заради първия, който съдържа align.
//te1 = timer1.elapsed(); //------------------------------------------------------------------------------------------------------------------------------------------------------------

//timer2.start(); //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
  if (foundVersesCountAll > 2500)
  {
    searchView->tvSetHtml(
      ((MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) ? QString("<div align=\"left\">") : QString("<div align=\"right\">")) +
      QString("<font color=%1><div><b>%2</b></div><div>%3</div></font><br>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->TS->TooManyMatches_v1).arg(MW->MO->TS->UseFilter_v1) +
      QString("<font color=%1><div>%2</div></font><br><hr></div>").arg(MW->MO->SVars.textInBracketsColorF.name()).arg(MW->MO->TS->ChangeSearchOptions_v1) +
      statistics);
  }
  else if (foundVersesCountAll > 0)
  {
    searchView->highlighter->setEnableHighlighter(true);
//    searchView->tvSetHtml(QString("<div align=\"%1\">%2%3</div>").arg((targetBibleText->layoutDirection == Qt::LeftToRight) ? QString("left") : QString("right")).arg(foundVerses).arg(statistics));
    searchView->tvSetHtml(QString("%1%2").arg(foundVerses).arg(statistics));
  }
  else // Ако няма открити стихове.
  {
    searchView->tvSetHtml(statistics);
  }
//te2 = timer2.elapsed(); //------------------------------------------------------------------------------------------------------------------------------------------------------------

  if (newSearch) // При ново търсене (натиснат е бутон "Търси").
  {
    int foundOldVersesCount = 0;
    int foundNewVersesCount = 0;
    int foundMaxVersesCount = 0; // Помни най-голямото число от foundOldVersesCount и foundNewVersesCount. Използва се само за изчисляване на relativePercent.
    double percent = 0; // Нормално процентно съдържание.
	double relativePercent = 0; // Относително процентно съдържание. Използва се само за графичното показване на процентите. Показва най-голямото число като 100%.

    for (quint8 i = 0; i < 77; i++)
    {
      if (foundMaxVersesCount < foundVersesCount[i])
      {
        foundMaxVersesCount = foundVersesCount[i];
      }
    }

    for (quint8 i = 0; i < 50; i++)
    {
      if (foundVersesCount[i] > 0)
      {
        percent = ((double)foundVersesCount[i] / (double)foundVersesCountAll) * 100.0;
        relativePercent = ((double)foundVersesCount[i] / (double)foundMaxVersesCount) * 100.0;
        treeWidgetItem[i]->setIcon(0, percentIcon(MW->MO->SVars.oldTestamentColorF, MW->MO->SVars.dock2TextColorB, relativePercent));
        treeWidgetItem[i]->setText(1, QString("%1").arg(foundVersesCount[i]));
        treeWidgetItem[i]->setText(2, QString("%1%").arg(percent, 0, 'f', 1));
        treeWidgetItem[i]->setHidden(false);
        foundOldVersesCount += foundVersesCount[i];
      }
      else
      {
        treeWidgetItem[i]->setHidden(true);
      }
    }

    for (quint8 i = 50; i < 77; i++)
    {
      if (foundVersesCount[i] > 0)
      {
        percent = ((double)foundVersesCount[i] / (double)foundVersesCountAll) * 100.0;
        relativePercent = ((double)foundVersesCount[i] / (double)foundMaxVersesCount) * 100.0;
        treeWidgetItem[i]->setIcon(0, percentIcon(MW->MO->SVars.newTestamentColorF, MW->MO->SVars.dock2TextColorB, relativePercent));
        treeWidgetItem[i]->setText(1, QString("%1").arg(foundVersesCount[i]));
        treeWidgetItem[i]->setText(2, QString("%1%").arg(percent, 0, 'f', 1));
        treeWidgetItem[i]->setHidden(false);
        foundNewVersesCount += foundVersesCount[i];
      }
      else
      {
        treeWidgetItem[i]->setHidden(true);
      }
    }

    if (foundVersesCountAll > 0)
    {
      percent = ((double)foundNewVersesCount / (double)foundVersesCountAll) * 100.0;
      treeWidgetItemNew->setIcon(0, percentIcon(MW->MO->SVars.dock2TextColorF, MW->MO->SVars.dock2TextColorB, percent));
      treeWidgetItemNew->setText(1, QString("%1").arg(foundNewVersesCount));
      treeWidgetItemNew->setText(2, QString("%1%").arg(percent, 0, 'f', 1));
      treeWidgetItemNew->setHidden(false);
    }
    else
    {
      treeWidgetItemNew->setHidden(true);
    }

    if (foundVersesCountAll > 0)
    {
      percent = ((double)foundOldVersesCount / (double)foundVersesCountAll) * 100.0;
      treeWidgetItemOld->setIcon(0, percentIcon(MW->MO->SVars.dock2TextColorF, MW->MO->SVars.dock2TextColorB, percent));
      treeWidgetItemOld->setText(1, QString("%1").arg(foundOldVersesCount));
      treeWidgetItemOld->setText(2, QString("%1%").arg(percent, 0, 'f', 1));
      treeWidgetItemOld->setHidden(false);
    }
    else
    {
      treeWidgetItemOld->setHidden(true);
    }

    if (foundVersesCountAll > 0)
    {
      percent = 100.0;
      treeWidgetItemAll->setIcon(0, percentIcon(MW->MO->SVars.dock2TextColorF, MW->MO->SVars.dock2TextColorB, percent));
      treeWidgetItemAll->setText(1, QString("%1").arg(foundVersesCountAll));
      treeWidgetItemAll->setText(2, QString("100%"));
      treeWidgetItemAll->setHidden(false);
      booksTreeWidget->setCurrentItem(treeWidgetItemAll); // Това ще селектира първия ред.
      currentRow = 0;
    }
    else
    {
      treeWidgetItemAll->setHidden(true);
    }

    booksTreeWidget->resizeColumnToContents(0);
    booksTreeWidget->resizeColumnToContents(1);
    booksTreeWidget->resizeColumnToContents(2);
  }
//te3 = timer3.elapsed(); MW->ShowStatusBarMessage(QString("<<< %1 ms търсене >>>  <<< %2 ms показване >>>  <<< %3 ms общо >>>").arg(te1).arg(te2).arg(te3), 300000); //----------------

  raiseSearchView(); // Показва на преден план изгледа "Резултати от търсенето"
  searchLineEdit->setFocus(); // Поставя полето за търсене в Библията на фокус.
}

void SearchWidget::slotRefreshPalette()
{
  QFont boldFont = booksTreeWidget->font();
  boldFont.setBold(true);

  QColor textColorSearchAlpha = MW->MO->SVars.dock2TextColorF;        textColorSearchAlpha.setAlpha(150); //setAlphaF(0.6)
  QColor oldTestamentColorAlpha = MW->MO->SVars.oldTestamentColorF;   oldTestamentColorAlpha.setAlpha(150); //setAlphaF(0.6)
  QColor newTestamentColorAlpha = MW->MO->SVars.newTestamentColorF;   newTestamentColorAlpha.setAlpha(150); //setAlphaF(0.6)

  QPalette pal = booksTreeWidget->palette();
  pal.setBrush(QPalette::Base, MW->MO->SVars.dock2TextColorB);   // Цвят на фона.
  pal.setBrush(QPalette::Window, MW->MO->SVars.dock2TextColorB); // Това не прави нищо.
  //pal.setBrush(QPalette::Button, MW->MO->SVars.appColorF);     // Това оцветява само скрол-бара. Реално указва влияние само на скролбара и затова е избран да е appColorF - за да бъдат всички скролбарове еднакви на цвят, но по-добре е редът да е закоментиран, за да си взима цветовете автоматично.
  booksTreeWidget->setPalette(pal);


  treeWidgetItemAll->setForeground(0, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemAll->setForeground(1, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemAll->setForeground(2, textColorSearchAlpha);
  treeWidgetItemAll->setExpanded(false);
  treeWidgetItemAll->setFont(0, boldFont);
  //treeWidgetItemAll->setFont(1, boldFont);
  treeWidgetItemAll->setTextAlignment(0, Qt::AlignLeft);  // Това, освен че мести текста го надига
  treeWidgetItemAll->setTextAlignment(1, Qt::AlignRight); // малко нагоре, затова трябва да го има
  treeWidgetItemAll->setTextAlignment(2, Qt::AlignLeft);  // и за трите колони.
  treeWidgetItemAll->setText(0, MW->MO->TS->Total_v1);

  treeWidgetItemOld->setForeground(0, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemOld->setForeground(1, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemOld->setForeground(2, textColorSearchAlpha);
  treeWidgetItemOld->setExpanded(false);
  treeWidgetItemOld->setFont(0, boldFont);
  //treeWidgetItemOld->setFont(1, boldFont);
  treeWidgetItemOld->setTextAlignment(0, Qt::AlignLeft);  // Това, освен че мести текста го надига
  treeWidgetItemOld->setTextAlignment(1, Qt::AlignRight); // малко нагоре, затова трябва да го има
  treeWidgetItemOld->setTextAlignment(2, Qt::AlignLeft);  // и за трите колони.
  treeWidgetItemOld->setText(0, MW->MO->TS->OT_v1);

  treeWidgetItemNew->setForeground(0, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemNew->setForeground(1, MW->MO->SVars.dock2TextColorF);
  treeWidgetItemNew->setForeground(2, textColorSearchAlpha);
  treeWidgetItemNew->setExpanded(false);
  treeWidgetItemNew->setFont(0, boldFont);
  //treeWidgetItemNew->setFont(1, boldFont);
  treeWidgetItemNew->setTextAlignment(0, Qt::AlignLeft);  // Това, освен че мести текста го надига
  treeWidgetItemNew->setTextAlignment(1, Qt::AlignRight); // малко нагоре, затова трябва да го има
  treeWidgetItemNew->setTextAlignment(2, Qt::AlignLeft);  // и за трите колони.
  treeWidgetItemNew->setText(0, MW->MO->TS->NT_v1);

  for (quint8 i = 0; i < 50; i++)
  {
    treeWidgetItem[i]->setForeground(0, MW->MO->SVars.oldTestamentColorF);
    treeWidgetItem[i]->setForeground(1, MW->MO->SVars.oldTestamentColorF);
    treeWidgetItem[i]->setForeground(2, oldTestamentColorAlpha);
    treeWidgetItem[i]->setExpanded(false);
    treeWidgetItem[i]->setFont(0, boldFont);
    //treeWidgetItem[i]->setFont(1, boldFont);
    treeWidgetItem[i]->setTextAlignment(0, Qt::AlignLeft);  // Това, освен че мести текста го надига
    treeWidgetItem[i]->setTextAlignment(1, Qt::AlignRight); // малко нагоре, затова трябва да го има
    treeWidgetItem[i]->setTextAlignment(2, Qt::AlignLeft);  // и за трите колони.
    treeWidgetItem[i]->setText(0, QString("%1").arg(MW->MO->bookMinNameArr[i]));
  }

  for (quint8 i = 50; i < 77; i++)
  {
    treeWidgetItem[i]->setForeground(0, MW->MO->SVars.newTestamentColorF);
    treeWidgetItem[i]->setForeground(1, MW->MO->SVars.newTestamentColorF);
    treeWidgetItem[i]->setForeground(2, newTestamentColorAlpha);
    treeWidgetItem[i]->setExpanded(false);
    treeWidgetItem[i]->setFont(0, boldFont);
    //treeWidgetItem[i]->setFont(1, boldFont);
    treeWidgetItem[i]->setTextAlignment(0, Qt::AlignLeft);  // Това, освен че мести текста го надига
    treeWidgetItem[i]->setTextAlignment(1, Qt::AlignRight); // малко нагоре, затова трябва да го има
    treeWidgetItem[i]->setTextAlignment(2, Qt::AlignLeft);  // и за трите колони.
    treeWidgetItem[i]->setText(0, QString("%1").arg(MW->MO->bookMinNameArr[i]));
  }

  slotDockWidgetRaised(mDock, mDockWidget3); // Това ще предизвика преизчертаване на картата с новата широчина.
}

void SearchWidget::slotSetTitleBarFontSize()
{
  // Ако тези редове се използват тук, големината на шрифта ще е като тази на заглавните ленти на всички прозорци, но е
  // някак по-логично да е като големината на текста на компонентите в тулбара, затова долните редове са закоментирани.
  
  //mDockWidget1->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  //mDockWidget2->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  //mDockWidget3->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
}

void SearchWidget::slotSetFontSize()
{
  QFont font;// Тук не трябва да се взима шрифта на някой обект, като например searchLineEdit.
  font.setPointSize(MW->MO->SVars.searchToolBarFontSize);
  //font.setFixedPitch(false);

  QSize size;
  // 6    7    8    9   10   11   12   14   16   18   20 - възможни размери на шрифта.
  if (MW->MO->SVars.searchToolBarFontSize >= 20) size = QSize(32, 32);
  else if (MW->MO->SVars.searchToolBarFontSize >= 14) size = QSize(24, 24);
  else size = QSize(16, 16);
  //searchBtn->setFont(font);
  //showOptionsBtn->setFont(font);
  searchBtn->setIconSize(size);
  showOptionsBtn->setIconSize(size);

  searchLineEdit->setFont(font); // Тук ще се промени размерът, но също така и шрифтът, затова по-долу се сетва само шрифтът на текстовото поле (който е същият, като на текста, в който се търси).
  targetTextComBox->setFont(font);
  searchRandomRBtn->setFont(font);
  searchRootRBtn->setFont(font);
  searchWordRBtn->setFont(font);
  searchAllWordsRBtn->setFont(font);
  searchAnyWordsRBtn->setFont(font);
  searchPhraseRBtn->setFont(font);
  searchWildCardChBox->setFont(font);
  searchCaseSensitivityChBox->setFont(font);
  searchInChapter->setFont(font);
  imageSaveBtn->setFont(font);
  imageWidthIncreaseBtn->setFont(font);
  imageWidthDecreaseBtn->setFont(font);

  mDockWidget1->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);
  mDockWidget2->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);
  mDockWidget3->setDockWidgetTitleBarFontSize(MW->MO->SVars.searchToolBarFontSize);

  font = searchLineEdit->font();
  font.setFamily(MW->MO->bibleTextList[searchTargetTextIndex].fontFamily);
  searchLineEdit->setFont(font); // Тук се връща шрифта, който трябва да бъде (по-горе беше заменен със стандартния).

  font = booksTreeWidget->font();
  font.setPointSize(MW->MO->SVars.searchToolBarFontSize);
  //font.setFixedPitch(false);

  booksTreeWidget->setFont(font);
  slotRefreshPalette(); // Това трябва да се извика, за да промени болднатия шрифт в booksTreeWidget.
  booksTreeWidget->resizeColumnToContents(0);
  booksTreeWidget->resizeColumnToContents(1);
  booksTreeWidget->resizeColumnToContents(2);
  
  percentIconHeight = MW->MO->SVars.searchToolBarFontSize;
  if (MW->MO->SVars.searchToolBarFontSize > 16)
    percentIconHeight = 16;
  
  if (MW->MO->SVars.searchToolBarWidth <= 220)
    percentIconWidth = 40;
  else if (MW->MO->SVars.searchToolBarWidth > 400)
    percentIconWidth = 160;
  else
    percentIconWidth = 80;
  booksTreeWidget->setIconSize(QSize(percentIconWidth, percentIconHeight));
}

void SearchWidget::slotSetColors()
{
  mDock->setDockBgColor(MW->MO->SVars.appColorB);
  mDockWidget1->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget1->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget1->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget1->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  mDockWidget2->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget2->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget2->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget2->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  mDockWidget3->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget3->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget3->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget3->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  
  QPalette imageScrollAreaPalette = imageScrollArea->palette();
  imageScrollAreaPalette.setBrush(QPalette::Base, MW->MO->SVars.dock2TextColorB);   // Това не прави нищо.
  imageScrollAreaPalette.setBrush(QPalette::Window, MW->MO->SVars.dock2TextColorB); // Това оцветява само фона, без скрол-бава, но оцветява и рамките на скрол-бата (което не се забелязва много, ако фонът е в нюансите на скрол-бара).
  //imageScrollAreaPalette.setBrush(QPalette::Button, MW->MO->SVars.appColorF);     // Това оцветява само скрол-бара. Реално указва влияние само на скролбара и затова е избран да е appColorF - за да бъдат всички скролбарове еднакви на цвят, но по-добре е редът да е закоментиран, за да си взима цветовете автоматично.
  imageScrollArea->setPalette(imageScrollAreaPalette);
  
  imageScrollAreaPalette.setBrush(QPalette::Button, MW->MO->SVars.appColorF);
  imageScrollAreaPalette.setBrush(QPalette::ButtonText, MW->MO->SVars.appColorB);
  mDockWidget3->getWidget()->setPalette(imageScrollAreaPalette);
  mDockWidget3->getWidget()->setAutoFillBackground(true);

  QPalette searchLineEditPalette = searchLineEdit->palette();
  searchLineEditPalette.setBrush(QPalette::Base, MW->MO->SVars.dock1TextColorB);
  searchLineEditPalette.setBrush(QPalette::Text, MW->MO->SVars.dock1TextColorF);
  searchLineEdit->setPalette(searchLineEditPalette);
  searchLineEdit->setAutoFillBackground(false); // Това да е задължително false, защото иначе ръбовете на текстовото поле не са закръглени и са с цвета на фона на полето.

  searchBtn->setIcon( Icons::icon_Search(32, 32, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) );
  showOptionsBtn->setIcon( Icons::icon_Settings(32, 32, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) );
}

void SearchWidget::slotSet3DTitleBar()
{
  mDockWidget1->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
  mDockWidget2->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
  mDockWidget3->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
}

void SearchWidget::slotDockWidgetRaised(MDock */*dock*/, MDockWidget *dockWidget)
{
  if (dockWidget != mDockWidget3) return;

  imageW = imageWidth / 2; // Тук imageW се използва като брой точки на ред, а imageWidth е потребителски зададената широчина, която може да не е реалната.
  imageH = (MAX_VERSES / imageW) + 1;
  imageW *= 2; // Реална, изчислена широчина на картата.
  imageH *= 2; // Реална, изчислена височина на картата.

  QPixmap imagePixmap(imageW, imageH);
  imagePixmap.fill(QColor(255, 255, 255, 0)); // Прозрачност.

  QPainter painter(&imagePixmap);
  int current = 0;
  int currBookCode = 0;
  int modify = -10; // Модификатор на цвят на фона.
  quint8 b = 0; // Код на книгата.
  quint8 c = 0; // Код на стиха в книгата.

  QColor newTestamentColorB = MW->MO->mergeColors(QColor(255, 255, 255), MW->MO->getTransparentColor(MW->MO->SVars.newTestamentColorF, MW->MO->SVars.newTestamentAlphaF));
  QColor oldTestamentColorB = MW->MO->mergeColors(QColor(255, 255, 255), MW->MO->getTransparentColor(MW->MO->SVars.oldTestamentColorF, MW->MO->SVars.oldTestamentAlphaF));
  QColor oldTestamentColorB2 = MW->MO->mergeColors(QColor(255, 255, 255), MW->MO->getTransparentColor(MW->MO->SVars.oldTestamentColorF, MW->MO->SVars.oldTestamentAlphaF - 20)); // Цвят за второканоничните книги.
  
  for (int y = 0; y < imageH; y+=2)
  {
    for (int x = 0; x < imageW; x+=2)
    {
      b = targetBibleText->booksExtArr[current];
      c = targetBibleText->chaptersExtArr[current];
      if (current < searchImageArray.size())
      {
        if (currBookCode != b) // Ако номерът на главата се е сменил току-що.
        {
          modify = (modify == -10) ? 0 : -10; // Модификаторът на цвета приема другата стойност (0 - няма промяна в цвета, XX - има промяна).
          currBookCode = b;
        }
        if (current >= MAX_VERSES) break;
        if (searchImageArray.testBit(current))
        {
          if (b > 50) // Н.З.
          {
            painter.setPen(MW->MO->colorModify(MW->MO->SVars.newTestamentColorF, modify));
          }
          else // С.З.
          {
            painter.setPen(MW->MO->colorModify(MW->MO->SVars.oldTestamentColorF, modify));
          }
        }
        else
        {
          if (b > 50) // Н.З.
          {
            painter.setPen(MW->MO->colorModify(newTestamentColorB, modify));
          }
          else // С.З.
          {
            if ( (b >= 40 && b <= 50) || (b == 19 && c == 151) || (b == 27 && (c == 13 || c == 14)) ) // Второканоничните.
            {
              painter.setPen(MW->MO->colorModify(oldTestamentColorB2, modify));
            }
            else
            {
              painter.setPen(MW->MO->colorModify(oldTestamentColorB, modify));
            }
          }
        }
        if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
        {
          painter.drawPoint(x, y);   painter.drawPoint(x+1, y);   painter.drawPoint(x, y+1);   painter.drawPoint(x+1, y+1);
        }
        else // Ако текстът е с дясно подравняване.
        {
          painter.drawPoint(imageW-x-1, y);   painter.drawPoint(imageW-x-2, y);   painter.drawPoint(imageW-x-1, y+1);   painter.drawPoint(imageW-x-2, y+1);
        }
      }
      current++;
    }
  }

  imageLabel->resize(imageW + 2, imageH + 2); // Ако това се промени да се променят сметките в slotImageMouseMoveOrPressEvent!!!
  imageLabel->setPixmap(imagePixmap);
}

void SearchWidget::slotImageSave()
{
  QString searchWords = searchLineEdit->text();
  searchWords.replace(QString("*"), QString("_"));
  searchWords.replace(QString("?"), QString("_"));
  searchWords = searchWords.trimmed(); // Премахва интервалите в началото и края.
  if (searchWords.isEmpty()) searchWords = QString("EmptyImage");

  QString fileName = QFileDialog::getSaveFileName(this, QString("Save As Pixmap"), QString("%1.png").arg(searchWords), QString("*.png"));
  if (!fileName.isEmpty())
  {
    if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(QString(".png"));
    imageLabel->pixmap()->save(fileName, "PNG", -1);
  }
}

void SearchWidget::slotImageWidthIncrease()
{
  if (imageWidth >= 1200) return;
  imageWidth += 20;
  slotDockWidgetRaised(mDock, mDockWidget3); // Това ще предизвика преизчертаване на картата с новата широчина.
}

void SearchWidget::slotImageWidthDecrease()
{
  if (imageWidth <= 20) return;
  imageWidth -= 20;
  slotDockWidgetRaised(mDock, mDockWidget3); // Това ще предизвика преизчертаване на картата с новата широчина.
}

void SearchWidget::slotImageMouseMoveOrPressEvent(int X, int Y, bool press)
{
  // Сметките в този слот са тясно свързани с размера на етикета, който в случая е с две точки по-голям
  // от този на картинката (това е указано в предпоследния ред на slotDockWidgetRaised).
  // По този начин първата точка на картинката е на координати 1,1 и затова се изважда единица:
  X--; Y--;

  // Броят на редовете и колоните в картата е два пъти по-малък, защото една точка е 2x2 пиксела.
  int colCount = imageW/2; // Брой на колоните. imageW е четно число.
  int rowCount = imageH/2; // Брой на редовете. imageH е четно число.

  int col; // Текуща точка в ред. Започва от нула.
  int row; // Текущ ред. Започва от нула.
  int index; // Изчисления абсолютен индекс.
  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
    col = (X+2)/2 - 1;
  else // Ако текстът е с дясно подравняване.
    col = colCount - ((X+2)/2 - 1) - 1;
  row = (Y+2)/2 - 1;
  if (col < 0 || col >= colCount || row < 0 || row >= rowCount) return;
  index = (row * colCount) + col;
  if (index < 0 || index >= MAX_VERSES || targetBibleText == 0) return;

  quint8 book = targetBibleText->booksExtArr[index];
  quint8 chapter = targetBibleText->chaptersExtArr[index];
  quint8 verse = 0; // Инициализира се с 0, защото със сигурност ще мине през долния цикъл поне веднъж.
  for (int i = index; i >= 0; i--)
  {
    if (targetBibleText->chaptersExtArr[i] != chapter || targetBibleText->booksExtArr[i] != book) break;
    verse++;
  }

  if ( book >= 1 && book <= 77 ) // Тук не трябва да се използва verification метода, защото връща false, ако са скрити второканоничните книги.
  {
    QString deutrocanonical = "";
    if ( (book >= 40 && book <= 50) || (book == 19 && chapter == 151) || (book == 27 && (chapter == 13 || chapter == 14)) )
    {
      deutrocanonical = QString("(%1)").arg(MW->MO->TS->Deuterocanonical_v1);
    }
    if (searchImageArray.size() > 0) // Ако има карта. Картата се показва след първото търсене. Преди това няма показана карта и не е добре да се показват тултип-овете върху невидимата карта.
    {
      if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
        QToolTip::showText(QCursor::pos(), QString("%1 %2:%3 %4").arg(MW->MO->bookShortNameArr[book-1]).arg(chapter).arg(verse).arg(deutrocanonical));
      else // Ако текстът е с дясно подравняване.
        QToolTip::showText(QCursor::pos(), QString("%1 %2:%3 %4").arg(deutrocanonical).arg(verse).arg(chapter).arg(MW->MO->bookShortNameArr[book-1]));
    }

    if (searchImageArray.size() > 0 && press && MW->MO->verification(book, chapter, verse)) // Ако има карта и е щракнато върху нея. Тук се използва verification методът, защото връща false, ако са скрити второканоничните книги и няма да позволи отваряне на такава книга.
    {
      if (MW->ctrlKeyPressed) // Ако е натиснат клавиш Ctrl по време на кликването.
      {
        MW->newHDock(false, -1, -1, 0, QBitArray(), 0, index); // Отваря нов прозорец и показва главата в него. Четвъртият параметър трябва да е 0.
        MW->ctrlKeyPressed = false; // Сваля флага, защото този прозорец вече не е на фокус и не може да прихване keyReleaseEvent-а, който отговаря за свалянето на флага.
      }
      else // Ако не е натиснат клавиш Ctrl по време на кликването.
      {
        MW->showFoundVerse(index, true); // Показва главата с открития стих.
      }
    }
  }
}

QIcon SearchWidget::percentIcon(QColor color, QColor colorBG, double percent)
{
  QPixmap pixmap(percentIconWidth, percentIconHeight);

  QPainter painter(&pixmap);

  painter.fillRect(0, 0, percentIconWidth, percentIconHeight, colorBG); // Това практически изтрива иконата. Нужно е, защото на това място ще има прозрачност.
  colorBG = color;   colorBG.setAlpha(48); // Прозрачност.
  painter.fillRect(0, 0, percentIconWidth, percentIconHeight, colorBG);
  painter.setPen(MW->MO->colorModify(colorBG, 50));
  painter.drawRect(0, 0, percentIconWidth-1, percentIconHeight-1);

  int width = (int)((percent * (double)percentIconWidth) / 100.0);
  if (MW->MO->TS->globalLayoutDirection == Qt::LeftToRight) // Ако текстът е с ляво подравняване.
    painter.fillRect(0, 0, width, percentIconHeight, color);
  else // Ако текстът е с дясно подравняване.
    painter.fillRect(percentIconWidth - width, 0, width, percentIconHeight, color);

  QIcon ico;
  ico.addPixmap(pixmap);
  return ico;
}

void SearchWidget::raiseSearchView()
{
  mDockWidget2->setCurrentTab();
  searchView->setFocus();
}

void SearchWidget::setSearchLineText(QString searchText)
{
  searchLineEdit->setText(searchText);
  setSearchLineInFocus(true);
}

void SearchWidget::setSearchLineInFocus(bool select)
{
  searchLineEdit->setFocus();  // Поставя полето за търсене в Библията на фокус.
  if (select) searchLineEdit->selectAll(); // Селектира текста, за да е по-лесно да се напише нов.
}

void SearchWidget::keyPressEvent(QKeyEvent *event)
{
  QWidget::keyPressEvent(event);

  if (event->modifiers() == Qt::ControlModifier) // Ако е натиснат Ctrl.
  {
  }
  else if (event->modifiers() == Qt::ShiftModifier) // Ако е натиснат Shift.
  {
  }
  else // Ако НЕ е натиснат Ctrl или Shift.
  {
    if (searchLineEdit->hasFocus())
    {
      if (event->key() == Qt::Key_Return  ||  event->key() == Qt::Key_Enter) slotSearchGo();
    }
  }
}

QString SearchWidget::getSearchMethodInfo()
{
  // Много е важно всеки стринг да бъде поставен в собствен div таг. По този начин се изписват правилно стрингове,
  // които са с различен Layout. Например, ако имаме RightToLeft Layout на цялото приложение и някъде измежду стринговете
  // има един непреведен, т.е. с LeftToRight Layout, то той ще се изпише както трябва. В противен случай ще се получи
  // разместване на някои знаци в него и освен това ще се изпише в дясно.
  // Таг <p> върши същата работа, но той вкарва допълнителен празен ред след себе си, докато <div> вкарва само един, затова след <div> не се слага <br>.
  QString text;
  text += QString("<font color=%1><b><div>%2</div></b></font><br>").arg(MW->MO->SVars.oldTestamentColorF.name()).arg(MW->MO->TS->SearchMethodInfo1_v1);
  text += QString("<font color=%1><b><div>%2</div></b><br>").arg(MW->MO->SVars.dock2TextColorF.name()).arg(MW->MO->TS->SearchMethodInfo2_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><div>%4</div><div>%5</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchRandom_v1).arg(MW->MO->TS->SearchMethodInfo31_v1).arg(MW->MO->TS->SearchMethodInfo32_v1).arg(MW->MO->TS->SearchMethodInfo33_v1); // •
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><div>%4</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchRoot_v1).arg(MW->MO->TS->SearchMethodInfo41_v1).arg(MW->MO->TS->SearchMethodInfo42_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><div>%4</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchWord_v1).arg(MW->MO->TS->SearchMethodInfo51_v1).arg(MW->MO->TS->SearchMethodInfo52_v1);
  text += QString("<font color=%1><i><b><div>%2<br>%3</div></b></i></font><div>%4</div><div>%5</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchAll_v1).arg(MW->MO->TS->OptSearchAny_v1).arg(MW->MO->TS->SearchMethodInfo61_v1).arg(MW->MO->TS->SearchMethodInfo62_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><div>%4</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchPhrase_v1).arg(MW->MO->TS->SearchMethodInfo71_v1).arg(MW->MO->TS->SearchMethodInfo72_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><div>%4</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchWildCard_v1).arg(MW->MO->TS->SearchMethodInfo81_v1).arg(MW->MO->TS->SearchMethodInfo82_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div><br>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchCaseSensitive_v1).arg(MW->MO->TS->SearchMethodInfo9_v1);
  text += QString("<font color=%1><i><b><div>%2</div></b></i></font><div>%3</div></font>").arg(MW->MO->SVars.newTestamentColorF.name()).arg(MW->MO->TS->OptSearchInChapter_v1).arg(MW->MO->TS->SearchMethodInfo10_v1);
  return text;
}

// ==========================================================================================================================================================

Label::Label(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f)
{
  setMouseTracking(true); // Това е, за да се вдига ивент при движение на мишката когато не е натиснат бутонът ѝ. Обратното - ако е false, ще вдига ивента ако мишката се движи с натиснат бутон. 
}

Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f) : QLabel(text, parent, f)
{
  setMouseTracking(true); // Това е, за да се вдига ивент при движение на мишката когато не е натиснат бутонът ѝ. Обратното - ако е false, ще вдига ивента ако мишката се движи с натиснат бутон. 
}

void Label::mouseMoveEvent(QMouseEvent *event)
{
  QLabel::mouseMoveEvent(event);
  emit mouseMoveOrPressEvent(event->x(), event->y(), false);
}

void Label::mousePressEvent(QMouseEvent *event)
{
  QLabel::mousePressEvent(event);
  emit mouseMoveOrPressEvent(event->x(), event->y(), true);
}

// ==========================================================================================================================================================

SearchToolBar::SearchToolBar(MainWindow *mainWindow, QWidget *parent) : MDock(parent)
{
  MW = mainWindow;

  setDockWidgetTabbedTitleBar(true);
  setProperties(false, false, true, false);
  setDockGridState("0^100_1_0^100"); // Един ред с един раздел.
  setMinimumSize(1, 30); // Не трябва да е 0, защото няма ефект.

  slotNewSearchToolBar(); // Създава първия тулбар.

  mDockWidget[0]->setCurrentTab();
  currentSearchWidget = searchWidget[0];
  
  slotSetColors();
}

SearchToolBar::~SearchToolBar()
{
  currentSearchWidget = 0;

  for (int i = 0; i < searchWidget.count(); i++)
  {
    delete searchWidget[i];
  }

  for (int i = 0; i < mDockWidget.count(); i++)
  {
    delete mDockWidget[i];
  }

  searchWidget.clear();
  mDockWidget.clear();
}

void SearchToolBar::slotNewSearchToolBar()
{
  if (searchWidget.count() == 8) return;

  SearchWidget *newSearchWidget = new SearchWidget(MW);

  MDockWidget *newMDockWidget = new MDockWidget(this, QString("<b>%1</b>").arg(MW->MO->TS->SearchInBible_v1), true, false, MW->MO->SVars.docks3DTitleBar, searchWidget.count() + 1, DOCK_TYPE__SEARCH_VIEW);
  newMDockWidget->setWidget(newSearchWidget);
  newMDockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само сигнал.
  newMDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  newMDockWidget->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  newMDockWidget->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  newMDockWidget->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  newMDockWidget->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  newMDockWidget->setNewBtnToolTip(MW->MO->TS->NewDockWindow_v1);
  newMDockWidget->setCloseBtnToolTip(MW->MO->TS->HideToolBar_v1);
  connect(newMDockWidget, SIGNAL(dockWidgetNewButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotNewSearchToolBar()));
  connect(newMDockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotHideSearchToolBar(MDock *, MDockWidget *, int, quint8))); // Излъчения от Close бутона сигнал.
  connect(newMDockWidget, SIGNAL(dockWidgetRaised(MDock *, MDockWidget *)), this, SLOT(slotSearchToolBarRaised(MDock *, MDockWidget *)));
  addDockWidget(newMDockWidget, 0, 0); // Всички са на една позиция, за да участват в табове.

  searchWidget << newSearchWidget;
  mDockWidget << newMDockWidget;

  currentSearchWidget = newSearchWidget;
  currentSearchWidget->setSearchLineInFocus(true);
}

void SearchToolBar::slotHideSearchToolBar(MDock */*dock*/, MDockWidget */*dockWidget*/, int /*dockWidgetID*/, quint8 /*dockWidgetType*/)
{
  //setVisible(false); // Това ще скрие (затвори) панела, но бутонът в TMenu няма да се отпусне.
  MW->mainToolBar->btnText_Search->click(); // Това косвено ще извика setVisible(false).
}

void SearchToolBar::slotSearchToolBarRaised(MDock */*dock*/, MDockWidget *dockWidget)
{
  for (int i = 0; i < mDockWidget.count(); i++)
  {
    if (dockWidget == mDockWidget[i])
    {
      currentSearchWidget = searchWidget[i];
      searchWidget[i]->setSearchLineInFocus(false);
      break;
    }
  }
}

void SearchToolBar::slotRefreshPalette()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->slotRefreshPalette();
  }
}

void SearchToolBar::slotSetTitleBarFontSize()
{
  for (int i = 0; i < mDockWidget.count(); i++)
  {
    mDockWidget[i]->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  }

  // Ако тези редове се използват тук, големината на шрифта ще е като тази на заглавните ленти на всички прозорци, но е
  // някак по-логично да е като големината на текста на компонентите в тулбара, затова долните редове са закоментирани.
  //for (int i = 0; i < searchWidget.count(); i++)
  //{
  //  searchWidget[i]->slotSetTitleBarFontSize();
  //}
}

void SearchToolBar::slotSetFontSize()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->slotSetFontSize();
  }
}

void SearchToolBar::slotSetColorScheme_AllSearchView()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->searchView->setColorScheme();
  }
}

void SearchToolBar::slotSetColors()
{
  setDockBgColor(MW->MO->SVars.appColorB);

  for (int i = 0; i < mDockWidget.count(); i++)
  {
    mDockWidget[i]->setDockWidgetBgColor(MW->MO->SVars.appColorF);
    mDockWidget[i]->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
    mDockWidget[i]->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
    mDockWidget[i]->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
  }
  
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->slotSetColors();
  }
}

void SearchToolBar::slotSet3DTitleBar()
{
  setAllDockWidgets3DTitleBar(MW->MO->SVars.docks3DTitleBar);

  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->slotSet3DTitleBar();
  }
}

void SearchToolBar::slotSetFontSize_AllSearchView(int fontSize, int textZoom)
{
  QFont font;

  for (int i = 0; i < searchWidget.count(); i++)
  {
    font = searchWidget[i]->searchView->font();
    font.setPointSize(fontSize);
    searchWidget[i]->searchView->setFont(font);
    searchWidget[i]->searchView->textZoom = textZoom;
    searchWidget[i]->searchView->zoomIn(textZoom);
  }
}

void SearchToolBar::slotZoomIn_AllSearchView()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->searchView->textZoom++;
    searchWidget[i]->searchView->zoomIn(1);
  }
}

void SearchToolBar::slotZoomOut_AllSearchView()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->searchView->textZoom--;
    searchWidget[i]->searchView->zoomOut(1);
  }
}

void SearchToolBar::slotZoomNormal_AllSearchView()
{
  for (int i = 0; i < searchWidget.count(); i++)
  {
    searchWidget[i]->searchView->zoomOut(searchWidget[i]->searchView->textZoom);
    searchWidget[i]->searchView->textZoom = 0;
  }
}
