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

#include "tmenu.h"
#include <QMessageBox> // QMessageBox::information(this, QString(""), QString(""));

TMenu::TMenu(QWidget *panelTMenu, QWidget *panelAudio, QWidget *panelBibleTexts, QWidget *panelSession, QColor appColorF, QColor appColorB, bool positionTop, QWidget *parent) : QWidget(parent)
{
  this->panelTMenu = panelTMenu;
  this->panelAudio = panelAudio;
  this->panelBibleTexts = panelBibleTexts;
  this->panelSession = panelSession;
  
  leftToRightDirection = QApplication::layoutDirection() == Qt::LeftToRight;
  show3DTitleBar = true;

  if (!appColorF.isValid())
  {
    appColorF = QColor(230, 230, 230);
  }
  if (!appColorB.isValid())
  {
    appColorB = QColor(100, 100, 100);
  }
  
  QPalette pal;
  pal.setBrush(QPalette::Button, appColorF);
  pal.setBrush(QPalette::Window, appColorF);
  //pal.setBrush(QPalette::Base, appColorF);
  this->setPalette(pal);
  this->setAutoFillBackground(true);

  setContentsMargins(0, 0, 0, 0);

  panelTMenuCont = new QWidget(this);
  panelTMenuCont->setContentsMargins(0, 0, 0, 0);

  panelAudioCont = new QWidget(this);
  panelAudioCont->setContentsMargins(0, 0, 0, 0);

  panelBibleTextsCont = new QWidget(this);
  panelBibleTextsCont->setContentsMargins(0, 0, 0, 0);

  panelSessionCont = new QWidget(this);
  panelSessionCont->setContentsMargins(0, 0, 0, 0);

  panelTMenuNav = new QWidget(panelTMenuCont);
  panelTMenuNav->setContentsMargins(0, 0, 0, 0);
  panelTMenuNav->setAutoFillBackground(true);

  panelAudioNav = new QWidget(panelAudioCont);
  panelAudioNav->setContentsMargins(0, 0, 0, 0);
  panelAudioNav->setAutoFillBackground(true);

  panelBibleTextsNav = new QWidget(panelBibleTextsCont);
  panelBibleTextsNav->setContentsMargins(0, 0, 0, 0);
  panelBibleTextsNav->setAutoFillBackground(true);

  panelSessionNav = new QWidget(panelSessionCont);
  panelSessionNav->setContentsMargins(0, 0, 0, 0);
  panelSessionNav->setAutoFillBackground(true);
  
  QColor color = appColorF; color.setAlpha(210); // Ако се смени тук да се смени и в метода setColors.
  pal = panelTMenuNav->palette();
  pal.setBrush(QPalette::Button, color);
  pal.setBrush(QPalette::Window, color);
  pal.setBrush(QPalette::Text, appColorB);
  pal.setBrush(QPalette::WindowText, appColorB);
  pal.setBrush(QPalette::ButtonText, appColorB);
  panelTMenuNav->setPalette(pal);
  panelAudioNav->setPalette(pal);
  panelBibleTextsNav->setPalette(pal);
  panelSessionNav->setPalette(pal);

  QPainterPath pathL;
  pathL.addPolygon(QPolygonF() << QPointF(48.0, 0.0) << QPointF(48.0, 48.0) << QPointF(0.0, 24.0));
  QPixmap pixL(48, 48);
  pixL.fill(QColor(0, 0, 0, 0));
  QPainter painterL(&pixL);
  painterL.setRenderHints(QPainter::Antialiasing, true);
  painterL.fillPath(pathL, panelTMenuNav->palette().brush(QPalette::Active, QPalette::Text).color());
  //
  QPainterPath pathR;
  pathR.addPolygon(QPolygonF() << QPointF(0.0, 0.0) << QPointF(0.0, 48.0) << QPointF(48.0, 24.0));
  QPixmap pixR(48, 48);
  pixR.fill(QColor(0, 0, 0, 0));
  QPainter painterR(&pixR);
  painterR.setRenderHints(QPainter::Antialiasing, true);
  painterR.fillPath(pathR, panelTMenuNav->palette().brush(QPalette::Active, QPalette::Text).color());

  btnPanelTMenuNavL = new QToolButton();
  btnPanelTMenuNavL->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelTMenuNavL->setIcon(pixL);
  btnPanelTMenuNavL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelTMenuNavL->setAutoRaise(true);
  btnPanelTMenuNavL->setAutoRepeat(true);
  btnPanelTMenuNavL->setAutoRepeatDelay(200);
  btnPanelTMenuNavL->setAutoRepeatInterval(100);
  //btnPanelTMenuNavL->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelTMenuNavL, SIGNAL(clicked()), this, SLOT(slotBtnPanelTMenuNavL_Clicked()));

  btnPanelTMenuNavR = new QToolButton();
  btnPanelTMenuNavR->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelTMenuNavR->setIcon(pixR);
  btnPanelTMenuNavR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelTMenuNavR->setAutoRaise(true);
  btnPanelTMenuNavR->setAutoRepeat(true);
  btnPanelTMenuNavR->setAutoRepeatDelay(200);
  btnPanelTMenuNavR->setAutoRepeatInterval(100);
  //btnPanelTMenuNavR->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelTMenuNavR, SIGNAL(clicked()), this, SLOT(slotBtnPanelTMenuNavR_Clicked()));

  QHBoxLayout *panelTMenuNavLayout = new QHBoxLayout(panelTMenuNav);
  panelTMenuNavLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  panelTMenuNavLayout->setSpacing(1);
  if (!leftToRightDirection) panelTMenuNavLayout->setDirection(QBoxLayout::RightToLeft); // Ако дирекшъна на цялото приложение е RightToLeft, бутоните в този лайаут ще се обърнат автоматично, затова тук се прави повторно обръщане.
  panelTMenuNavLayout->addWidget(btnPanelTMenuNavL);
  panelTMenuNavLayout->addWidget(btnPanelTMenuNavR);

  btnPanelAudioNavL = new QToolButton();
  btnPanelAudioNavL->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelAudioNavL->setIcon(pixL);
  btnPanelAudioNavL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelAudioNavL->setAutoRaise(true);
  btnPanelAudioNavL->setAutoRepeat(true);
  btnPanelAudioNavL->setAutoRepeatDelay(200);
  btnPanelAudioNavL->setAutoRepeatInterval(100);
 //btnPanelAudioNavL->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelAudioNavL, SIGNAL(clicked()), this, SLOT(slotBtnPanelAudioNavL_Clicked()));

  btnPanelAudioNavR = new QToolButton();
  btnPanelAudioNavR->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelAudioNavR->setIcon(pixR);
  btnPanelAudioNavR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelAudioNavR->setAutoRaise(true);
  btnPanelAudioNavR->setAutoRepeat(true);
  btnPanelAudioNavR->setAutoRepeatDelay(200);
  btnPanelAudioNavR->setAutoRepeatInterval(100);
  //btnPanelAudioNavR->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelAudioNavR, SIGNAL(clicked()), this, SLOT(slotBtnPanelAudioNavR_Clicked()));

  QHBoxLayout *panelAudioNavLayout = new QHBoxLayout(panelAudioNav);
  panelAudioNavLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  panelAudioNavLayout->setSpacing(1);
  if (!leftToRightDirection) panelAudioNavLayout->setDirection(QBoxLayout::RightToLeft); // Ако дирекшъна на цялото приложение е RightToLeft, бутоните в този лайаут ще се обърнат автоматично, затова тук се прави повторно обръщане.
  panelAudioNavLayout->addWidget(btnPanelAudioNavL);
  panelAudioNavLayout->addWidget(btnPanelAudioNavR);

  btnPanelBibleTextsNavL = new QToolButton();
  btnPanelBibleTextsNavL->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelBibleTextsNavL->setIcon(pixL);
  btnPanelBibleTextsNavL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelBibleTextsNavL->setAutoRaise(true);
  btnPanelBibleTextsNavL->setAutoRepeat(true);
  btnPanelBibleTextsNavL->setAutoRepeatDelay(200);
  btnPanelBibleTextsNavL->setAutoRepeatInterval(100);
  //btnPanelBibleTextsNavL->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelBibleTextsNavL, SIGNAL(clicked()), this, SLOT(slotBtnPanelBibleTextsNavL_Clicked()));

  btnPanelBibleTextsNavR = new QToolButton();
  btnPanelBibleTextsNavR->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelBibleTextsNavR->setIcon(pixR);
  btnPanelBibleTextsNavR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelBibleTextsNavR->setAutoRaise(true);
  btnPanelBibleTextsNavR->setAutoRepeat(true);
  btnPanelBibleTextsNavR->setAutoRepeatDelay(200);
  btnPanelBibleTextsNavR->setAutoRepeatInterval(100);
  //btnPanelBibleTextsNavR->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelBibleTextsNavR, SIGNAL(clicked()), this, SLOT(slotBtnPanelBibleTextsNavR_Clicked()));

  QHBoxLayout *panelBibleTextsNavLayout = new QHBoxLayout(panelBibleTextsNav);
  panelBibleTextsNavLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  panelBibleTextsNavLayout->setSpacing(1);
  if (!leftToRightDirection) panelBibleTextsNavLayout->setDirection(QBoxLayout::RightToLeft); // Ако дирекшъна на цялото приложение е RightToLeft, бутоните в този лайаут ще се обърнат автоматично, затова тук се прави повторно обръщане.
  panelBibleTextsNavLayout->addWidget(btnPanelBibleTextsNavL);
  panelBibleTextsNavLayout->addWidget(btnPanelBibleTextsNavR);

  btnPanelSessionNavL = new QToolButton();
  btnPanelSessionNavL->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelSessionNavL->setIcon(pixL);
  btnPanelSessionNavL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelSessionNavL->setAutoRaise(true);
  btnPanelSessionNavL->setAutoRepeat(true);
  btnPanelSessionNavL->setAutoRepeatDelay(200);
  btnPanelSessionNavL->setAutoRepeatInterval(100);
  //btnPanelSessionNavL->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelSessionNavL, SIGNAL(clicked()), this, SLOT(slotBtnPanelSessionNavL_Clicked()));

  btnPanelSessionNavR = new QToolButton();
  btnPanelSessionNavR->setToolButtonStyle(Qt::ToolButtonIconOnly);
  btnPanelSessionNavR->setIcon(pixR);
  btnPanelSessionNavR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  btnPanelSessionNavR->setAutoRaise(true);
  btnPanelSessionNavR->setAutoRepeat(true);
  btnPanelSessionNavR->setAutoRepeatDelay(200);
  btnPanelSessionNavR->setAutoRepeatInterval(100);
  //btnPanelSessionNavR->setFocusPolicy(Qt::NoFocus);
  connect(btnPanelSessionNavR, SIGNAL(clicked()), this, SLOT(slotBtnPanelSessionNavR_Clicked()));

  QHBoxLayout *panelSessionNavLayout = new QHBoxLayout(panelSessionNav);
  panelSessionNavLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  panelSessionNavLayout->setSpacing(1);
  if (!leftToRightDirection) panelSessionNavLayout->setDirection(QBoxLayout::RightToLeft); // Ако дирекшъна на цялото приложение е RightToLeft, бутоните в този лайаут ще се обърнат автоматично, затова тук се прави повторно обръщане.
  panelSessionNavLayout->addWidget(btnPanelSessionNavL);
  panelSessionNavLayout->addWidget(btnPanelSessionNavR);

  this->panelTMenu->setParent(panelTMenuCont); // The widget is moved to position (0, 0) in its new parent.
  this->panelAudio->setParent(panelAudioCont); // The widget is moved to position (0, 0) in its new parent.
  this->panelBibleTexts->setParent(panelBibleTextsCont); // The widget is moved to position (0, 0) in its new parent.
  this->panelSession->setParent(panelSessionCont); // The widget is moved to position (0, 0) in its new parent.
  
  panelTMenuCont->setMinimumHeight(panelTMenu->height());
  panelTMenuCont->setMaximumHeight(panelTMenu->height());
  panelAudioCont->setMinimumHeight(panelAudio->height());           // Тези панели са винаги с еднаква височина.
  panelAudioCont->setMaximumHeight(panelAudio->height());           //
  panelBibleTextsCont->setMinimumHeight(panelBibleTexts->height()); //
  panelBibleTextsCont->setMaximumHeight(panelBibleTexts->height()); //
  panelSessionCont->setMinimumHeight(panelSession->height());       //
  panelSessionCont->setMaximumHeight(panelSession->height());       //
  
  QVBoxLayout *mainContainerLayout = new QVBoxLayout(this);
  mainContainerLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  mainContainerLayout->setSpacing(0);
  if (positionTop)
  {
    mainContainerLayout->addWidget(panelTMenuCont, 0, Qt::AlignTop);      // AlignTop прави така, че панелът да стои в горния край и при скриване на някой от другите панели, този да не се премества към средата, а да си стои винаги горе (така няма премигване).
    mainContainerLayout->addWidget(panelAudioCont, 0, Qt::AlignTop);      //
    mainContainerLayout->addWidget(panelBibleTextsCont, 0, Qt::AlignTop); //
    mainContainerLayout->addWidget(panelSessionCont, 0, Qt::AlignTop);    //
  }
  else // POSITION_BOTTOM
  {
    mainContainerLayout->addWidget(panelSessionCont, 0, Qt::AlignBottom);    // AlignBottom прави така, че панелът да стои в долния край и при скриване на някой от другите панели, този да не се премества към средата, а да си стои винаги долу (така няма премигване).
    mainContainerLayout->addWidget(panelBibleTextsCont, 0, Qt::AlignBottom); //
    mainContainerLayout->addWidget(panelAudioCont, 0, Qt::AlignBottom);      //
    mainContainerLayout->addWidget(panelTMenuCont, 0, Qt::AlignBottom);      //
  }
}

TMenu::~TMenu()
{
}

void TMenu::setAudioToolBarVisible(bool visible)
{
  panelAudioCont->setVisible(visible);
}

void TMenu::setBibleTextsToolBarVisible(bool visible)
{
  panelBibleTextsCont->setVisible(visible);
}

void TMenu::setSessionToolBarVisible(bool visible)
{
  panelSessionCont->setVisible(visible);
}

void TMenu::setColors(QColor appColorF, QColor appColorB)
{
  if (!appColorF.isValid())
  {
    appColorF = QColor(225, 225, 225);
  }
  if (!appColorB.isValid())
  {
    appColorB = QColor(100, 100, 100);
  }
  
  QPalette paletteB;
  paletteB.setBrush(QPalette::Button, appColorF);
  paletteB.setBrush(QPalette::Window, appColorF);
  //paletteB.setBrush(QPalette::Base, appColorF);
  this->setPalette(paletteB);
  this->setAutoFillBackground(true);
  
  QColor color = appColorF; color.setAlpha(210); // Ако се смени тук, да се смени и в конструктора.
  QPalette pal = panelTMenuNav->palette();
  pal.setBrush(QPalette::Button, color);
  pal.setBrush(QPalette::Window, color);
  pal.setBrush(QPalette::Text, appColorB);
  pal.setBrush(QPalette::WindowText, appColorB);
  pal.setBrush(QPalette::ButtonText, appColorB);
  panelTMenuNav->setPalette(pal);
  panelAudioNav->setPalette(pal);
  panelBibleTextsNav->setPalette(pal);
  panelSessionNav->setPalette(pal);

  QPainterPath pathL;
  pathL.addPolygon(QPolygonF() << QPointF(48.0, 0.0) << QPointF(48.0, 48.0) << QPointF(0.0, 24.0));
  QPixmap pixL(48, 48);
  pixL.fill(QColor(0, 0, 0, 0));
  QPainter painterL(&pixL);
  painterL.setRenderHints(QPainter::Antialiasing, true);
  painterL.fillPath(pathL, appColorB);
  //
  QPainterPath pathR;
  pathR.addPolygon(QPolygonF() << QPointF(0.0, 0.0) << QPointF(0.0, 48.0) << QPointF(48.0, 24.0));
  QPixmap pixR(48, 48);
  pixR.fill(QColor(0, 0, 0, 0));
  QPainter painterR(&pixR);
  painterR.setRenderHints(QPainter::Antialiasing, true);
  painterR.fillPath(pathR, appColorB);
  //
  btnPanelTMenuNavL->setIcon(pixL);
  btnPanelTMenuNavR->setIcon(pixR);
  btnPanelAudioNavL->setIcon(pixL);
  btnPanelAudioNavR->setIcon(pixR);
  btnPanelBibleTextsNavL->setIcon(pixL);
  btnPanelBibleTextsNavR->setIcon(pixR);
  btnPanelSessionNavL->setIcon(pixL);
  btnPanelSessionNavR->setIcon(pixR);
}

void TMenu::set3DTitleBar(bool show3DTitleBar)
{
  this->show3DTitleBar = show3DTitleBar;
  update();
}

void TMenu::setToolBarsHeight(int height)
{
  panelAudioCont->setMinimumHeight(height);
  panelAudioCont->setMaximumHeight(height);
  
  panelBibleTextsCont->setMinimumHeight(height);
  panelBibleTextsCont->setMaximumHeight(height);
  
  panelSessionCont->setMinimumHeight(height);
  panelSessionCont->setMaximumHeight(height);
  
  int pixHeight = (double)height / 2.6; // 2.6 е най-добрият размер.
  btnPanelTMenuNavL->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelTMenuNavR->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelAudioNavL->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelAudioNavR->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelBibleTextsNavL->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelBibleTextsNavR->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelSessionNavL->setIconSize(QSize(pixHeight, pixHeight));
  btnPanelSessionNavR->setIconSize(QSize(pixHeight, pixHeight));
}

void TMenu::slotBtnPanelTMenuNavL_Clicked()
{
  if (!panelTMenuNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelTMenu->pos().x() + (panelTMenu->height() - 1);
  if (leftToRightDirection)
  {
    if (px >= 0) px = 0;
  }
  else
  {
    if (px >= (panelTMenuNav->pos().x() + panelTMenuNav->width() + panelTMenuNav->width()/2 - 1)) return;
  }
  panelTMenu->move(px, panelTMenu->pos().y());
}

void TMenu::slotBtnPanelTMenuNavR_Clicked()
{
  if (!panelTMenuNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelTMenu->pos().x() - (panelTMenu->height() - 1);
  if (leftToRightDirection)
  {
    int availableWidth = width() - panelTMenuNav->width(); // Ширината на видимото (достъпното) място.
    int visiblePart = panelTMenu->width() + panelTMenu->pos().x(); // Ширината на панела с бутони, която е надясно от позиция нула.
    if (visiblePart <= availableWidth) return; // Това спира движението на панела наляво, когато най-десният бутон стане видим.
  }
  else
  {
    if ( px < (width() - panelTMenu->width()) ) return;
  }
  panelTMenu->move(px, panelTMenu->pos().y());
}

void TMenu::slotBtnPanelAudioNavL_Clicked()
{
  if (!panelAudioNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelAudio->pos().x() + panelAudio->height();
  if (leftToRightDirection)
  {
    if (px >= 0) px = 0;
  }
  else
  {
    if (px >= (panelAudioNav->pos().x() + panelAudioNav->width() + panelAudioNav->width()/2 - 1)) return;
  }
  panelAudio->move(px, panelAudio->pos().y());
}

void TMenu::slotBtnPanelAudioNavR_Clicked()
{
  if (!panelAudioNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelAudio->pos().x() - panelAudio->height();
  if (leftToRightDirection)
  {
    int availableWidth = width() - panelAudioNav->width(); // Ширината на видимото (достъпното) място.
    int visiblePart = panelAudio->width() + panelAudio->pos().x(); // Ширината на панела с бутони, която е надясно от позиция нула.
    if (visiblePart <= availableWidth) return; // Това спира движението на панела наляво, когато най-десният бутон стане видим.
  }
  else
  {
    if ( px < (width() - panelAudio->width()) ) return;
  }
  panelAudio->move(px, panelAudio->pos().y());
}

void TMenu::slotBtnPanelBibleTextsNavL_Clicked()
{
  if (!panelBibleTextsNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelBibleTexts->pos().x() + panelBibleTexts->height();
  if (leftToRightDirection)
  {
    if (px >= 0) px = 0;
  }
  else
  {
    if (px >= (panelBibleTextsNav->pos().x() + panelBibleTextsNav->width() + panelBibleTextsNav->width()/2 - 1)) return;
  }
  panelBibleTexts->move(px, panelBibleTexts->pos().y());
}

void TMenu::slotBtnPanelBibleTextsNavR_Clicked()
{
  if (!panelBibleTextsNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelBibleTexts->pos().x() - panelBibleTexts->height();
  if (leftToRightDirection)
  {
    int availableWidth = width() - panelBibleTextsNav->width(); // Ширината на видимото (достъпното) място.
    int visiblePart = panelBibleTexts->width() + panelBibleTexts->pos().x(); // Ширината на панела с бутони, която е надясно от позиция нула.
    if (visiblePart <= availableWidth) return; // Това спира движението на панела наляво, когато най-десният бутон стане видим.
  }
  else
  {
    if ( px < (width() - panelBibleTexts->width()) ) return;
  }
  panelBibleTexts->move(px, panelBibleTexts->pos().y());
}

void TMenu::slotBtnPanelSessionNavL_Clicked()
{
  if (!panelSessionNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelSession->pos().x() + panelSession->height();
  if (leftToRightDirection)
  {
    if (px >= 0) px = 0;
  }
  else
  {
    if (px >= (panelSessionNav->pos().x() + panelSessionNav->width() + panelSessionNav->width()/2 - 1)) return;
  }
  panelSession->move(px, panelSession->pos().y());
}

void TMenu::slotBtnPanelSessionNavR_Clicked()
{
  if (!panelSessionNav->isVisible()) return; // Ако панелът с бутоните за навигация е скрит. Този слот се извиква и при въртене на колелцето на мишката, затова е важна тази проверка.

  int px = panelSession->pos().x() - panelSession->height();
  if (leftToRightDirection)
  {
    int availableWidth = width() - panelSessionNav->width(); // Ширината на видимото (достъпното) място.
    int visiblePart = panelSession->width() + panelSession->pos().x(); // Ширината на панела с бутони, която е надясно от позиция нула.
    if (visiblePart <= availableWidth) return; // Това спира движението на панела наляво, когато най-десният бутон стане видим.
  }
  else
  {
    if ( px < (width() - panelSession->width()) ) return;
  }
  panelSession->move(px, panelSession->pos().y());
}

void TMenu::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  bool vResize = (event->oldSize().width() != event->size().width()); // Указва дали има хоризонтално ресайзване (защото при показване на тулбар, има само вертикално).
  int iniPos = 0; // Първоначална позиция на панела. Нормално е да е 0, но за RightToLeft дирекшън, се изчислява според дължината на панела.

  // За panelTMenu ---------------------------------------------------------------------------
  iniPos = leftToRightDirection ? 0 : (width() - panelTMenu->width());
  if (vResize && panelTMenu->pos().x() != iniPos) // Ако панелът е изместен.
  {
    panelTMenu->move(iniPos, panelTMenu->pos().y()); // Възстановява позицията на панела.
  }
  
  int panelTMenuHeight = panelTMenu->height();
  panelTMenuNav->resize(panelTMenuHeight*2+1, panelTMenuHeight);
  panelTMenuNav->setMinimumSize(QSize(0, panelTMenuHeight));
  panelTMenuNav->setMaximumSize(QSize(16777215, panelTMenuHeight));
  
  if (panelTMenu->width() <= width()) // Ако има достатъчно място за да се съберат всички бутони.
  {
    panelTMenuNav->setVisible(false); // Скрива бутоните за навигация.
  }
  else // Ако няма достатъчно място за да се съберат всички бутони.
  {
    int x = leftToRightDirection ? (width() - panelTMenuNav->width()) : 0;
    panelTMenuNav->move(x, 0);
    panelTMenuNav->setVisible(true); // Показва бутоните за навигация.
    panelTMenuNav->raise();
  }
  
  // За panelAudio ---------------------------------------------------------------------------
  iniPos = leftToRightDirection ? 0 : (width() - panelAudio->width());
  if (vResize && panelAudio->pos().x() != iniPos) // Ако панелът е изместен.
  {
    panelAudio->move(iniPos, panelAudio->pos().y()); // Възстановява позицията на панела.
  }
  
  int panelAudioHeight = panelAudio->height();
  panelAudioNav->resize(panelTMenuHeight*2+1, panelAudioHeight); // Тук се използва дължината на бутоните на тулбара с бутоните.
  panelAudioNav->setMinimumSize(QSize(0, panelAudioHeight));
  panelAudioNav->setMaximumSize(QSize(16777215, panelAudioHeight));
  
  if (panelAudio->width() <= width()) // Ако има достатъчно място за да се съберат всички бутони.
  {
    panelAudioNav->setVisible(false); // Скрива бутоните за навигация.
  }
  else // Ако няма достатъчно място за да се съберат всички бутони.
  {
    int x = leftToRightDirection ? (width() - panelAudioNav->width()) : 0;
    panelAudioNav->move(x, 0);
    panelAudioNav->setVisible(true); // Показва бутоните за навигация.
    panelAudioNav->raise();
  }
  
  // За panelBibleTexts ---------------------------------------------------------------------------
  iniPos = leftToRightDirection ? 0 : (width() - panelBibleTexts->width());
  if (vResize && panelBibleTexts->pos().x() != iniPos) // Ако панелът е изместен.
  {
    panelBibleTexts->move(iniPos, panelBibleTexts->pos().y()); // Възстановява позицията на панела.
  }
  
  int panelBibleTextsHeight = panelBibleTexts->height();
  panelBibleTextsNav->resize(panelTMenuHeight*2+1, panelBibleTextsHeight); // Тук се използва дължината на бутоните на тулбара с бутоните.
  panelBibleTextsNav->setMinimumSize(QSize(0, panelBibleTextsHeight));
  panelBibleTextsNav->setMaximumSize(QSize(16777215, panelBibleTextsHeight));
  
  if (panelBibleTexts->width() <= width()) // Ако има достатъчно място за да се съберат всички бутони.
  {
    panelBibleTextsNav->setVisible(false); // Скрива бутоните за навигация.
  }
  else // Ако няма достатъчно място за да се съберат всички бутони.
  {
    int x = leftToRightDirection ? (width() - panelBibleTextsNav->width()) : 0;
    panelBibleTextsNav->move(x, 0);
    panelBibleTextsNav->setVisible(true); // Показва бутоните за навигация.
    panelBibleTextsNav->raise();
  }
  
  // За panelSession ---------------------------------------------------------------------------
  iniPos = leftToRightDirection ? 0 : (width() - panelSession->width());
  if (vResize && panelSession->pos().x() != iniPos) // Ако панелът е изместен.
  {
    panelSession->move(iniPos, panelSession->pos().y()); // Възстановява позицията на панела.
  }
  
  int panelSessionHeight = panelSession->height();
  panelSessionNav->resize(panelTMenuHeight*2+1, panelSessionHeight); // Тук се използва дължината на бутоните на тулбара с бутоните.
  panelSessionNav->setMinimumSize(QSize(0, panelSessionHeight));
  panelSessionNav->setMaximumSize(QSize(16777215, panelSessionHeight));
  
  if (panelSession->width() <= width()) // Ако има достатъчно място за да се съберат всички бутони.
  {
    panelSessionNav->setVisible(false); // Скрива бутоните за навигация.
  }
  else // Ако няма достатъчно място за да се съберат всички бутони.
  {
    int x = leftToRightDirection ? (width() - panelSessionNav->width()) : 0;
    panelSessionNav->move(x, 0);
    panelSessionNav->setVisible(true); // Показва бутоните за навигация.
    panelSessionNav->raise();
  }
}

void TMenu::wheelEvent(QWheelEvent *event)
{
  QWidget::wheelEvent(event);
  
  bool forward = event->delta() > 0;
  if (!leftToRightDirection) forward = !forward;

  if (event->y() < (panelTMenuCont->geometry().y() + panelTMenuCont->size().height()))
  {
    if (forward) // При въртене на колелцето на мишката напред.
    {
      slotBtnPanelTMenuNavL_Clicked();
    }
    else // При въртене назад.
    {
      slotBtnPanelTMenuNavR_Clicked();
    }
  }
  else if (panelAudioCont->isVisible() && event->y() < (panelAudioCont->geometry().y() + panelAudioCont->size().height()))
  {
    if (forward) // При въртене на колелцето на мишката напред.
    {
      slotBtnPanelAudioNavL_Clicked();
    }
    else // При въртене назад.
    {
      slotBtnPanelAudioNavR_Clicked();
    }
  }
  else if (panelBibleTextsCont->isVisible() && event->y() < (panelBibleTextsCont->geometry().y() + panelBibleTextsCont->size().height()))
  {
    if (forward) // При въртене на колелцето на мишката напред.
    {
      slotBtnPanelBibleTextsNavL_Clicked();
    }
    else // При въртене назад.
    {
      slotBtnPanelBibleTextsNavR_Clicked();
    }
  }
  else if (panelSessionCont->isVisible() && event->y() < (panelSessionCont->geometry().y() + panelSessionCont->size().height()))
  {
    if (forward) // При въртене на колелцето на мишката напред.
    {
      slotBtnPanelSessionNavL_Clicked();
    }
    else // При въртене назад.
    {
      slotBtnPanelSessionNavR_Clicked();
    }
  }
}

void TMenu::paintEvent(QPaintEvent *event)
{
  // 3D изпъкнал панел:
  if (show3DTitleBar)
  {
    QColor color = this->palette().brush(QPalette::Active, QPalette::Button).color(); // Цвят на фона.
    int h, s, v;
    color.getHsv(&h, &s, &v);
    v += 20; if (v > 255) v = 255;
    s -= 10; if (s < 0) s = 0;
    color.setHsv(h, s, v); // Изсветлява цвета на фона.
    color.setAlpha(40); // Прави го прозрачен.
    
    QPainter painter(this);
    h = height()-2; // Тук би трябвало да е 4, но става по-тъмен тулбарът, затова е 2.
    v = 1;          // Тук би трябвало да е 2, но става по-тъмен тулбарът, затова е 1.
    while (h > 0)
    {
      painter.fillRect(0, v, width(), h, color); // Наслагва цвета, така че да се получи 3D изпъкване.
      h -= 4;
      v += 2;
    }
  }
  
  QWidget::paintEvent(event);
}

// -----------------------------------------------------------------------------------------------------------------------------------

MainToolBar::MainToolBar(TrStrings *trStrings, int buttonsIconSize, QColor tMenuColorB, QColor iconColor, QWidget *parent) : QWidget(parent)
{
  //setStyleSheet(QString("QToolBar { border-bottom: 0px solid #646464; }")); // border-bottom-color: #646464; border-color: rgb(0, 0, 0, 0);

  if (!tMenuColorB.isValid())
  {
    tMenuColorB = QColor(230, 230, 230);
  }
  if (!iconColor.isValid())
  {
    iconColor = QColor(100, 100, 100);
  }

  TS = trStrings;
  leftToRightDirection = QApplication::layoutDirection() == Qt::LeftToRight;

  this->btnsIconSize = buttonsIconSize; // 24 32 40 48 ... 96
  this->btnsHeightSize = this->btnsIconSize + 8;

  shift = 1; // Всички бутони се разполагат в нещо като grid с точно фиксиран размер, равен на btnsHeightSize + 1. shift е мястото, където трябва да се разположи следващият бутон.
  lineEdit_SearchInText_IsInactive = true;

  if (leftToRightDirection)
  {
    createNavigationToolBar();
    createTextToolBar();
    createOtherToolBar();
    createHelpToolBar();
    createFileToolBar();
  }
  else
  {
    createFileToolBar();
    createHelpToolBar();
    createOtherToolBar();
    createTextToolBar();
    createNavigationToolBar();
  }

  setContentsMargins(0, 0, 0, 0);
  setMinimumHeight(btnsHeightSize + 2); // 2 е за 1 точка горен и 1 точка долен маргин на тулбара.
  setMaximumHeight(btnsHeightSize + 2); //
  resize(shift, btnsHeightSize + 2);    //

  setIconsColor(tMenuColorB, iconColor);
}

MainToolBar::~MainToolBar()
{
}

void MainToolBar::createNavigationToolBar()
{
  QFont fontLabels;
  fontLabels.setPointSize(btnsIconSize / 3 + 2);
  //if (btnsIconSize >= 20) fontLabels.setBold(true);

  btnNavigation_New = new QToolButton(this);
  btnNavigation_New->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_New->setToolTip(composeToolTip(TS->NewDockWindow_v1, "Ctrl+N", QKeySequence::New));
  btnNavigation_New->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_N, QKeySequence::New));
  btnNavigation_New->setAutoRaise(true);
  //btnNavigation_New->setFocusPolicy(Qt::NoFocus);

  btnNavigation_Books = new QToolButton(this);
  btnNavigation_Books->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_Books->setToolTip(composeToolTip(TS->Books_v1, "F12"));
  btnNavigation_Books->setShortcut(composeShortcut(Qt::Key_F12));
  btnNavigation_Books->setAutoRaise(true);
  btnNavigation_Books->setCheckable(true);
  //btnNavigation_Books->setFocusPolicy(Qt::NoFocus);

  btnNavigation_Bookmarks = new QToolButton(this);
  btnNavigation_Bookmarks->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_Bookmarks->setToolTip(composeToolTip(TS->Bookmarks_v1));
  btnNavigation_Bookmarks->setAutoRaise(true);
  btnNavigation_Bookmarks->setCheckable(true);
  //btnNavigation_Bookmarks->setFocusPolicy(Qt::NoFocus);

  labelBook = new QLabel(TS->BookShort_v1, this);
  labelBook->setFont(fontLabels);
  labelBook->setAlignment(Qt::AlignCenter);

  labelChapter = new QLabel(TS->ChapterShort_v1, this);
  labelChapter->setFont(fontLabels);
  labelChapter->setAlignment(Qt::AlignCenter);

  labelVerse = new QLabel(TS->VerseShort_v1, this);
  labelVerse->setFont(fontLabels);
  labelVerse->setAlignment(Qt::AlignCenter);

  dailyReadGrLabel = new QLabel("", this);
  dailyReadGrLabel->setToolTip(TS->DailyReadGroup_v1);
  dailyReadGrLabel->setFont(fontLabels);
  dailyReadGrLabel->setAlignment(Qt::AlignCenter); // Qt::AlignBottom|Qt::AlignHCenter
  dailyReadGrLabel->setVisible(false);

  dailyReadChLabel = new QLabel("", this);
  dailyReadChLabel->setToolTip(TS->DailyReadChapterInGroup_v1);
  dailyReadChLabel->setFont(fontLabels);
  dailyReadChLabel->setAlignment(Qt::AlignCenter); // Qt::AlignBottom|Qt::AlignHCenter
  dailyReadChLabel->setVisible(false);

  btnNavigation_GoBack = new QToolButton(this);
  btnNavigation_GoBack->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_GoBack->setToolTip(composeToolTip(TS->GoBack_v1, "Alt+Left", QKeySequence::Back));
  btnNavigation_GoBack->setShortcut(composeShortcut(Qt::ALT + Qt::Key_Left, QKeySequence::Back));
  btnNavigation_GoBack->setAutoRaise(true);
  //btnNavigation_GoBack->setEnabled(false);
  //btnNavigation_GoBack->setFocusPolicy(Qt::NoFocus);

  btnNavigation_GoForward = new QToolButton(this);
  btnNavigation_GoForward->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_GoForward->setToolTip(composeToolTip(TS->GoForward_v1, "Alt+Right", QKeySequence::Forward));
  btnNavigation_GoForward->setShortcut(composeShortcut(Qt::ALT + Qt::Key_Right, QKeySequence::Forward));
  btnNavigation_GoForward->setAutoRaise(true);
  //btnNavigation_GoForward->setEnabled(false);
  //btnNavigation_GoForward->setFocusPolicy(Qt::NoFocus);

  btnNavigation_PreviousBook = new QToolButton(this);
  btnNavigation_PreviousBook->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_PreviousBook->setToolTip(composeToolTip(TS->PreviousBook_v1, "Ctrl+Home"));
  btnNavigation_PreviousBook->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Home));
  btnNavigation_PreviousBook->setAutoRaise(true);
  //btnNavigation_PreviousBook->setFocusPolicy(Qt::NoFocus);

  btnNavigation_NextBook = new QToolButton(this);
  btnNavigation_NextBook->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_NextBook->setToolTip(composeToolTip(TS->NextBook_v1, "Ctrl+End"));
  btnNavigation_NextBook->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_End));
  btnNavigation_NextBook->setAutoRaise(true);
  //btnNavigation_NextBook->setFocusPolicy(Qt::NoFocus);

  btnNavigation_PreviousChapter = new QToolButton(this);
  btnNavigation_PreviousChapter->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_PreviousChapter->setToolTip(composeToolTip(TS->PreviousChapter_v1, "Ctrl+PageUp"));
  btnNavigation_PreviousChapter->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_PageUp));
  btnNavigation_PreviousChapter->setAutoRaise(true);
  //btnNavigation_PreviousChapter->setFocusPolicy(Qt::NoFocus);

  btnNavigation_NextChapter = new QToolButton(this);
  btnNavigation_NextChapter->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_NextChapter->setToolTip(composeToolTip(TS->NextChapter_v1, "Ctrl+PageDown"));
  btnNavigation_NextChapter->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_PageDown));
  btnNavigation_NextChapter->setAutoRaise(true);
  //btnNavigation_NextChapter->setFocusPolicy(Qt::NoFocus);

  btnNavigation_PreviousVerse = new QToolButton(this);
  btnNavigation_PreviousVerse->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_PreviousVerse->setToolTip(composeToolTip(TS->PreviousVerse_v1, "Ctrl+Up"));
  btnNavigation_PreviousVerse->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Up));
  btnNavigation_PreviousVerse->setAutoRaise(true);
  //btnNavigation_PreviousVerse->setFocusPolicy(Qt::NoFocus);

  btnNavigation_NextVerse = new QToolButton(this);
  btnNavigation_NextVerse->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_NextVerse->setToolTip(composeToolTip(TS->NextVerse_v1, "Ctrl+Down"));
  btnNavigation_NextVerse->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Down));
  btnNavigation_NextVerse->setAutoRaise(true);
  //btnNavigation_NextVerse->setFocusPolicy(Qt::NoFocus);

  btnNavigation_PreviousChaptersDailyRead = new QToolButton(this);
  btnNavigation_PreviousChaptersDailyRead->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_PreviousChaptersDailyRead->setToolTip(composeToolTip(TS->PreviousChaptersDailyRead_v1));
  btnNavigation_PreviousChaptersDailyRead->setAutoRaise(true);
  btnNavigation_PreviousChaptersDailyRead->setVisible(false);
  //btnNavigation_PreviousChaptersDailyRead->setFocusPolicy(Qt::NoFocus);

  btnNavigation_NextChaptersDailyRead = new QToolButton(this);
  btnNavigation_NextChaptersDailyRead->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_NextChaptersDailyRead->setToolTip(composeToolTip(TS->NextChaptersDailyRead_v1));
  btnNavigation_NextChaptersDailyRead->setAutoRaise(true);
  btnNavigation_NextChaptersDailyRead->setVisible(false);
  //btnNavigation_NextChaptersDailyRead->setFocusPolicy(Qt::NoFocus);

  btnNavigation_PreviousChapterDailyRead = new QToolButton(this);
  btnNavigation_PreviousChapterDailyRead->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_PreviousChapterDailyRead->setToolTip(composeToolTip(TS->PreviousChapterDailyRead_v1));
  btnNavigation_PreviousChapterDailyRead->setAutoRaise(true);
  btnNavigation_PreviousChapterDailyRead->setVisible(false);
  //btnNavigation_PreviousChapterDailyRead->setFocusPolicy(Qt::NoFocus);

  btnNavigation_NextChapterDailyRead = new QToolButton(this);
  btnNavigation_NextChapterDailyRead->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_NextChapterDailyRead->setToolTip(composeToolTip(TS->NextChapterDailyRead_v1));
  btnNavigation_NextChapterDailyRead->setAutoRaise(true);
  btnNavigation_NextChapterDailyRead->setVisible(false);
  //btnNavigation_NextChapterDailyRead->setFocusPolicy(Qt::NoFocus);

  btnNavigation_DailyRead = new QToolButton(this);
  btnNavigation_DailyRead->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnNavigation_DailyRead->setToolTip(composeToolTip(TS->DailyRead_v1));
  btnNavigation_DailyRead->setAutoRaise(true);
  btnNavigation_DailyRead->setCheckable(true);
  //btnNavigation_DailyRead->setFocusPolicy(Qt::NoFocus);


  if (leftToRightDirection)
  {
    btnNavigation_New->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_Books->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_Bookmarks->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_GoBack->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_GoForward->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousBook->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextBook->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousChapter->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextChapter->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousVerse->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextVerse->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_DailyRead->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    
	btnNavigation_PreviousChaptersDailyRead->setGeometry(QRect(btnNavigation_GoBack->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_NextChaptersDailyRead->setGeometry(QRect(btnNavigation_PreviousBook->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_PreviousChapterDailyRead->setGeometry(QRect(btnNavigation_NextBook->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_NextChapterDailyRead->setGeometry(QRect(btnNavigation_NextChapter->pos().x(), 1, btnsHeightSize, btnsHeightSize));

    labelBook->setGeometry(QRect(btnNavigation_PreviousBook->pos().x(), 2, (btnNavigation_NextBook->pos().x() - btnNavigation_PreviousBook->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    labelChapter->setGeometry(QRect(btnNavigation_PreviousChapter->pos().x(), 2, (btnNavigation_NextChapter->pos().x() - btnNavigation_PreviousChapter->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    labelVerse->setGeometry(QRect(btnNavigation_PreviousVerse->pos().x(), 2, (btnNavigation_NextVerse->pos().x() - btnNavigation_PreviousVerse->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    dailyReadGrLabel->setGeometry(QRect(btnNavigation_PreviousChaptersDailyRead->pos().x(), 2, (btnNavigation_NextChaptersDailyRead->pos().x() - btnNavigation_PreviousChaptersDailyRead->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    dailyReadChLabel->setGeometry(QRect(btnNavigation_PreviousChapterDailyRead->pos().x(), 2, (btnNavigation_NextChapterDailyRead->pos().x() - btnNavigation_PreviousChapterDailyRead->pos().x() + btnsHeightSize), btnsHeightSize - 2));
  }
  else
  {
    btnNavigation_DailyRead->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextVerse->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousVerse->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextChapter->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousChapter->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_NextBook->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_PreviousBook->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_GoForward->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
	btnNavigation_GoBack->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_Bookmarks->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_Books->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnNavigation_New->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;

    btnNavigation_NextChapterDailyRead->setGeometry(QRect(btnNavigation_NextChapter->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_PreviousChapterDailyRead->setGeometry(QRect(btnNavigation_NextBook->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_NextChaptersDailyRead->setGeometry(QRect(btnNavigation_PreviousBook->pos().x(), 1, btnsHeightSize, btnsHeightSize));
    btnNavigation_PreviousChaptersDailyRead->setGeometry(QRect(btnNavigation_GoBack->pos().x(), 1, btnsHeightSize, btnsHeightSize));

    labelBook->setGeometry(QRect(btnNavigation_NextBook->pos().x(), 2, (btnNavigation_PreviousBook->pos().x() - btnNavigation_NextBook->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    labelChapter->setGeometry(QRect(btnNavigation_NextChapter->pos().x(), 2, (btnNavigation_PreviousChapter->pos().x() - btnNavigation_NextChapter->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    labelVerse->setGeometry(QRect(btnNavigation_NextVerse->pos().x(), 2, (btnNavigation_PreviousVerse->pos().x() - btnNavigation_NextVerse->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    dailyReadGrLabel->setGeometry(QRect(btnNavigation_NextChaptersDailyRead->pos().x(), 2, (btnNavigation_PreviousChaptersDailyRead->pos().x() - btnNavigation_NextChaptersDailyRead->pos().x() + btnsHeightSize), btnsHeightSize - 2));
    dailyReadChLabel->setGeometry(QRect(btnNavigation_NextChapterDailyRead->pos().x(), 2, (btnNavigation_PreviousChapterDailyRead->pos().x() - btnNavigation_NextChapterDailyRead->pos().x() + btnsHeightSize), btnsHeightSize - 2));
  }
}

void MainToolBar::createTextToolBar()
{
  btnText_Search = new QToolButton(this);
  btnText_Search->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_Search->setToolTip(composeToolTip(TS->SearchInBible_v1, "F2"));
  btnText_Search->setShortcut(composeShortcut(Qt::Key_F2));
  btnText_Search->setAutoRaise(true);
  btnText_Search->setCheckable(true);
  //btnText_Search->setFocusPolicy(Qt::NoFocus);

  btnText_BibleTexts = new QToolButton(this);
  btnText_BibleTexts->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_BibleTexts->setToolTip(composeToolTip(TS->BibleTexts_v1));
  btnText_BibleTexts->setAutoRaise(true);
  btnText_BibleTexts->setCheckable(true);
  //btnText_BibleTexts->setFocusPolicy(Qt::NoFocus);

  btnText_Audio = new QToolButton(this);
  btnText_Audio->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_Audio->setToolTip(composeToolTip(TS->Audio_v1, "Ctrl+L"));
  btnText_Audio->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_L));
  btnText_Audio->setAutoRaise(true);
  btnText_Audio->setCheckable(true);
  //btnText_Audio->setFocusPolicy(Qt::NoFocus);

  btnText_ZoomIn = new QToolButton(this);
  btnText_ZoomIn->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_ZoomIn->setToolTip(composeToolTip(TS->ZoomInText_v1, "Ctrl++", QKeySequence::ZoomIn));
  btnText_ZoomIn->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Plus, QKeySequence::ZoomIn));
  btnText_ZoomIn->setAutoRaise(true);
  //btnText_ZoomIn->setFocusPolicy(Qt::NoFocus);

  btnText_ZoomOut = new QToolButton(this);
  btnText_ZoomOut->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_ZoomOut->setToolTip(composeToolTip(TS->ZoomOutText_v1, "Ctrl+-", QKeySequence::ZoomOut));
  btnText_ZoomOut->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Minus, QKeySequence::ZoomOut));
  btnText_ZoomOut->setAutoRaise(true);
  //btnText_ZoomOut->setFocusPolicy(Qt::NoFocus);

  btnText_ZoomNormal = new QToolButton(this);
  btnText_ZoomNormal->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_ZoomNormal->setToolTip(composeToolTip(TS->RestoreDefaultZoom_v1, "Ctrl+0"));
  btnText_ZoomNormal->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_0));
  btnText_ZoomNormal->setAutoRaise(true);
  //btnText_ZoomNormal->setFocusPolicy(Qt::NoFocus);

  lineEdit_SearchInText = new QLineEdit(this); // Създава се тук, преди следващите четири бутона, за да е под тях.
  //lineEdit_SearchInText->setFocusPolicy(Qt::NoFocus);

  btnText_SearchInTextPrevious = new QToolButton(this);
  btnText_SearchInTextPrevious->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_SearchInTextPrevious->setToolTip(composeToolTip(TS->FindPrevious_v1, "Shift+F3", QKeySequence::FindPrevious));
  btnText_SearchInTextPrevious->setShortcut(composeShortcut(Qt::SHIFT + Qt::Key_F3, QKeySequence::FindPrevious));
  btnText_SearchInTextPrevious->setAutoRaise(true);
  //btnText_SearchInTextPrevious->setFocusPolicy(Qt::NoFocus);

  btnText_SearchInTextCaseSensitive = new QToolButton(this);
  btnText_SearchInTextCaseSensitive->setIconSize(QSize(btnsIconSize, btnsIconSize / 2));
  btnText_SearchInTextCaseSensitive->setToolTip(composeToolTip(TS->CaseSensitive_v1));
  btnText_SearchInTextCaseSensitive->setAutoRaise(true);
  btnText_SearchInTextCaseSensitive->setCheckable(true);
  //btnText_SearchInTextCaseSensitive->setFocusPolicy(Qt::NoFocus);

  btnText_SearchInTextWholeWords = new QToolButton(this);
  btnText_SearchInTextWholeWords->setIconSize(QSize(btnsIconSize, btnsIconSize / 2));
  btnText_SearchInTextWholeWords->setToolTip(composeToolTip(TS->WholeWords_v1));
  btnText_SearchInTextWholeWords->setAutoRaise(true);
  btnText_SearchInTextWholeWords->setCheckable(true);
  //btnText_SearchInTextWholeWords->setFocusPolicy(Qt::NoFocus);

  lineEdit_SearchInText->setToolTip(TS->SearchInTheText_v1);
  lineEdit_SearchInText->setFrame(false);
  lineEdit_SearchInText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

  btnText_SearchInTextNext = new QToolButton(this);
  btnText_SearchInTextNext->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_SearchInTextNext->setToolTip(composeToolTip(TS->FindNext_v1, "F3", QKeySequence::FindNext));
  btnText_SearchInTextNext->setShortcut(composeShortcut(Qt::Key_F3, QKeySequence::FindNext));
  btnText_SearchInTextNext->setAutoRaise(true);
  //btnText_SearchInTextNext->setFocusPolicy(Qt::NoFocus);

  btnText_Statistics = new QToolButton(this);
  btnText_Statistics->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnText_Statistics->setToolTip(composeToolTip(TS->StatisticsMenu_v1));
  btnText_Statistics->setAutoRaise(true);
  //btnText_Statistics->setFocusPolicy(Qt::NoFocus);

  if (leftToRightDirection)
  {
    btnText_Search->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_BibleTexts->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_Audio->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomIn->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomOut->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomNormal->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_SearchInTextPrevious->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_SearchInTextCaseSensitive->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize / 2 + 2));   shift += btnsHeightSize*2 + 2;
    btnText_SearchInTextWholeWords->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize / 2 + 2));   shift += btnsHeightSize + 1;
    lineEdit_SearchInText->setGeometry(QRect(btnText_SearchInTextCaseSensitive->pos().x(), btnsHeightSize / 2 , btnsHeightSize*3 + 2, btnsHeightSize / 2));
    btnText_SearchInTextNext->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_Statistics->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
  else
  {
    btnText_Statistics->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_SearchInTextNext->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_SearchInTextCaseSensitive->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize / 2 + 2));   shift += btnsHeightSize*2 + 2;
    btnText_SearchInTextWholeWords->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize / 2 + 2));   shift += btnsHeightSize + 1;
    lineEdit_SearchInText->setGeometry(QRect(btnText_SearchInTextCaseSensitive->pos().x(), btnsHeightSize / 2 , btnsHeightSize*3 + 2, btnsHeightSize / 2));
    btnText_SearchInTextPrevious->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomNormal->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomOut->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_ZoomIn->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_Audio->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_BibleTexts->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnText_Search->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }

  QFont fontSearchInText = lineEdit_SearchInText->font();
  if (btnsIconSize > 24)
    fontSearchInText.setPointSize(lineEdit_SearchInText->height() - 8);
  else if (btnsIconSize > 16)
    fontSearchInText.setPointSize(lineEdit_SearchInText->height() - 6);
  else
    fontSearchInText.setPointSize(lineEdit_SearchInText->height() - 4);
  lineEdit_SearchInText->setFont(fontSearchInText);
}

void MainToolBar::createOtherToolBar()
{
  btnOther_Pad = new QToolButton(this);
  btnOther_Pad->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_Pad->setToolTip(composeToolTip(TS->Pad_v1));
  btnOther_Pad->setAutoRaise(true);
  //btnOther_Pad->setFocusPolicy(Qt::NoFocus);

  btnOther_Dictionary = new QToolButton(this);
  btnOther_Dictionary->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_Dictionary->setToolTip(composeToolTip(TS->DictionaryCommentary_v1));
  btnOther_Dictionary->setAutoRaise(true);
  //btnOther_Dictionary->setFocusPolicy(Qt::NoFocus);

  btnOther_ExternalImages = new QToolButton(this);
  btnOther_ExternalImages->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_ExternalImages->setToolTip(composeToolTip(TS->ExternalImages_v1));
  btnOther_ExternalImages->setAutoRaise(true);
  //btnOther_ExternalImages->setFocusPolicy(Qt::NoFocus);

  btnOther_WWW = new QToolButton(this);
  btnOther_WWW->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_WWW->setToolTip(composeToolTip(TS->Links_v1));
  btnOther_WWW->setAutoRaise(true);
  //btnOther_WWW->setFocusPolicy(Qt::NoFocus);

  btnOther_Projector = new QToolButton(this);
  btnOther_Projector->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_Projector->setToolTip(composeToolTip(TS->Projector_v1));
  btnOther_Projector->setAutoRaise(true);
  btnOther_Projector->setCheckable(true);
  //btnOther_Projector->setFocusPolicy(Qt::NoFocus);

  btnOther_Settings = new QToolButton(this);
  btnOther_Settings->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnOther_Settings->setToolTip(composeToolTip(TS->Settings_v1));
  btnOther_Settings->setAutoRaise(true);
  //btnOther_Settings->setFocusPolicy(Qt::NoFocus);

  if (leftToRightDirection)
  {
    btnOther_Pad->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Dictionary->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_ExternalImages->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_WWW->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Projector->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Settings->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
  else
  {
    btnOther_Settings->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Projector->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_WWW->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_ExternalImages->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Dictionary->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnOther_Pad->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
}

void MainToolBar::createHelpToolBar()
{
  btnHelp_Help = new QToolButton(this);
  btnHelp_Help->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnHelp_Help->setToolTip(composeToolTip(TS->Help_v1, "F1"));
  btnHelp_Help->setShortcut(composeShortcut(Qt::Key_F1));
  btnHelp_Help->setAutoRaise(true);
  //btnHelp_Help->setFocusPolicy(Qt::NoFocus);

  btnHelp_AboutMatCrossBible = new QToolButton(this);
  btnHelp_AboutMatCrossBible->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnHelp_AboutMatCrossBible->setToolTip(composeToolTip(TS->About_v1));
  btnHelp_AboutMatCrossBible->setAutoRaise(true);
  //btnHelp_AboutMatCrossBible->setFocusPolicy(Qt::NoFocus);

  if (leftToRightDirection)
  {
    btnHelp_Help->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnHelp_AboutMatCrossBible->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
  else
  {
    btnHelp_AboutMatCrossBible->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnHelp_Help->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
}

void MainToolBar::createFileToolBar()
{
  btnFile_FileMenu = new QToolButton(this);
  btnFile_FileMenu->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnFile_FileMenu->setToolTip(composeToolTip(TS->FileMenu_v1));
  btnFile_FileMenu->setAutoRaise(true);
  //btnFile_FileMenu->setFocusPolicy(Qt::NoFocus);

  btnFile_Session = new QToolButton(this);
  btnFile_Session->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnFile_Session->setToolTip(composeToolTip(TS->Session_v1));
  btnFile_Session->setAutoRaise(true);
  btnFile_Session->setCheckable(true);
  //btnFile_Session->setFocusPolicy(Qt::NoFocus);

  //btnFile_Close = new QToolButton(this);
  //btnFile_Close->setIconSize(QSize(btnsIconSize, btnsIconSize));
  //btnFile_Close->setToolTip(composeToolTip(TS->CloseCurrentDock, "Ctrl+W", QKeySequence::Close));
  //btnFile_Close->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_W, QKeySequence::Close));
  //btnFile_Close->setAutoRaise(true);
  //btnFile_Close->setFocusPolicy(Qt::NoFocus);

  btnFile_Exit = new QToolButton(this);
  btnFile_Exit->setIconSize(QSize(btnsIconSize, btnsIconSize));
  btnFile_Exit->setToolTip(composeToolTip(TS->Exit_v1, "Ctrl+Q", QKeySequence::Quit));
  btnFile_Exit->setShortcut(composeShortcut(Qt::CTRL + Qt::Key_Q, QKeySequence::Quit));
  btnFile_Exit->setAutoRaise(true);
  //btnFile_Exit->setFocusPolicy(Qt::NoFocus);

  if (leftToRightDirection)
  {
    btnFile_FileMenu->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnFile_Session->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    //btnFile_Close->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnFile_Exit->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
  else
  {
    btnFile_Exit->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    //btnFile_Close->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnFile_Session->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
    btnFile_FileMenu->setGeometry(QRect(shift, 1, btnsHeightSize, btnsHeightSize));   shift += btnsHeightSize + 1;
  }
}

void MainToolBar::setIconsColor(QColor tMenuColorB, QColor iconColor)
{
  if (!tMenuColorB.isValid())
  {
    tMenuColorB = QColor(225, 225, 225);
  }
  if (!iconColor.isValid())
  {
    iconColor = QColor(100, 100, 100);
  }

  // Определя дали темата е светла или тъмна.
  //bool lightTheme; // Светла тема (дали цвета на прозореца е определен като светъл).
  //QColor iconsColor = this->palette().brush(QPalette::Active, QPalette::Button).color(); // Цвят на прозорците.
  //int h = 0, s = 0, v = 0;
  //iconsColor.getHsv(&h, &s, &v);
  //if (v > 127) // Ако темата на прозорците е светла.
  //{
  //  lightTheme = true;
  //}
  //else // Ако темата на прозорците е тъмна.
  //{
  //  lightTheme = false;
  //}

  // Определя допълнителния цвят (според lightTheme).
  QColor additionalColor = iconColor;
  //h = 0, s = 0, v = 0;
  //additionalColor.getHsv(&h, &s, &v);
  //if (lightTheme) // Ако темата на прозорците е светла.
  //{
  //  v = v + 40; if (v > 255) v = 255;
  //  additionalColor.setHsv(h, s, v);
  //}
  //else // Ако темата на прозорците е тъмна.
  //{
  //  v = v - 40; if (v < 0) v = 0;
  //  additionalColor.setHsv(h, s, v);
  //}

  // Panel Navigation
  //btnNavigation_New->setIcon( QIcon(":/resources/images/new.png") );
  btnNavigation_New->setIcon( Icons::icon_New(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_Books->setIcon( Icons::icon_Books(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_Bookmarks->setIcon( Icons::icon_Bookmark(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_GoBack->setIcon( leftToRightDirection ? Icons::icon_ArrowBack(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowForward(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_GoForward->setIcon( leftToRightDirection ? Icons::icon_ArrowForward(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowBack(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_PreviousBook->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_NextBook->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_PreviousChapter->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_NextChapter->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_PreviousVerse->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_NextVerse->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_PreviousChaptersDailyRead->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_NextChaptersDailyRead->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_PreviousChapterDailyRead->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_NextChapterDailyRead->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnNavigation_DailyRead->setIcon( Icons::icon_DailyRead(btnsIconSize, btnsIconSize, iconColor, additionalColor) );

  QBrush brush(iconColor);
  brush.setStyle(Qt::SolidPattern);
  QPalette pal;
  pal.setBrush(QPalette::ButtonText, brush);
  pal.setBrush(QPalette::WindowText, brush);
  labelBook->setPalette(pal);
  labelChapter->setPalette(pal);
  labelVerse->setPalette(pal);
  dailyReadGrLabel->setPalette(pal);
  dailyReadChLabel->setPalette(pal);

  // Panel Text
  btnText_Search->setIcon( Icons::icon_Search(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_BibleTexts->setIcon( Icons::icon_BibleTexts(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_Audio->setIcon( Icons::icon_Audio(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_ZoomIn->setIcon( Icons::icon_ZoomIn(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_ZoomOut->setIcon( Icons::icon_ZoomOut(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_ZoomNormal->setIcon( Icons::icon_ZoomNormal(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_SearchInTextPrevious->setIcon( leftToRightDirection ? Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_SearchInTextCaseSensitive->setIcon( Icons::icon_CaseSensitive(btnsIconSize, btnsIconSize / 2, iconColor, additionalColor) );
  btnText_SearchInTextWholeWords->setIcon( Icons::icon_WholeWords(btnsIconSize, btnsIconSize / 2, iconColor, additionalColor) );
  btnText_SearchInTextNext->setIcon( leftToRightDirection ? Icons::icon_ArrowNext(btnsIconSize, btnsIconSize, iconColor, additionalColor) : Icons::icon_ArrowPrevious(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnText_Statistics->setIcon( Icons::icon_Statistics(btnsIconSize, btnsIconSize, iconColor, additionalColor) );

  lineEdit_SearchInText_PaletteYellow = palette();
  lineEdit_SearchInText_PaletteYellow.setBrush(QPalette::Base, QColor(255,255,210)); // Бледожълт цвят за фон.
  lineEdit_SearchInText_PaletteYellow.setBrush(QPalette::Text, QColor(0, 0, 0)); // Черен цвят за буквите.

  lineEdit_SearchInText_PaletteAlpha = palette(); // Неактивно поле.
  lineEdit_SearchInText_PaletteAlpha.setBrush(QPalette::Base, QColor(0,0,0,0)); // Цвета на фона. Прозрачност.
  QColor colorA = iconColor;   colorA.setAlpha(80);
  lineEdit_SearchInText_PaletteAlpha.setBrush(QPalette::Text, colorA); // Текст на буквите по-тъмен от фона.
  
  showAlphaPalette_LineEdit_SearchInText(false); // Превключва, за да се смени цвета.
  showAlphaPalette_LineEdit_SearchInText(true);

  // Panel Other
  btnOther_Pad->setIcon( Icons::icon_Pad(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnOther_Dictionary->setIcon( Icons::icon_Dictionary(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnOther_ExternalImages->setIcon( Icons::icon_ExternalImages(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnOther_WWW->setIcon( Icons::icon_WWW(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnOther_Projector->setIcon( Icons::icon_Projector(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnOther_Settings->setIcon( Icons::icon_Settings(btnsIconSize, btnsIconSize, iconColor, additionalColor) );

  // Panel Help
  btnHelp_Help->setIcon( Icons::icon_Help(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnHelp_AboutMatCrossBible->setIcon( Icons::icon_Info(btnsIconSize, btnsIconSize, iconColor, additionalColor) );

  // Panel File
  btnFile_FileMenu->setIcon( Icons::icon_FileMenu(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnFile_Session->setIcon( Icons::icon_Session(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  //btnFile_Close->setIcon( Icons::icon_Close(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
  btnFile_Exit->setIcon( Icons::icon_Exit(btnsIconSize, btnsIconSize, iconColor, additionalColor) );
}

QString MainToolBar::composeToolTip(QString toolTip, QString key, QKeySequence::StandardKey standardKey)
{
  if (standardKey == QKeySequence::UnknownKey)
  {
    if (key == "")
      return toolTip;
    else
      return QString("%1 (%2)").arg(toolTip).arg(key);
  }

  QList<QKeySequence>	list = QKeySequence::keyBindings(standardKey);

  if (list.isEmpty()) // Ако няма стандартен клавиш за тази платформа се взима стойността на key за такъв.
  {
    return QString("%1 (%2)").arg(toolTip).arg(key);
  }
  else // Ако има стандартен клавиш за тази платформа, стойността на key се игнорира.
  {
    QString keys = "";
    for(int i = 0; i < list.count(); i ++) // Може да има повече от една клавишни комбинации, затова е този for.
    {
      keys += list[i].toString();
      if (i < (list.count()-1)) keys += ", ";
    }
    return QString("%1 (%2)").arg(toolTip).arg(keys);
  }
}

QKeySequence MainToolBar::composeShortcut(QKeySequence key, QKeySequence::StandardKey standardKey)
{
  if (standardKey == QKeySequence::UnknownKey) return key;
  if (QKeySequence::keyBindings(standardKey).isEmpty()) return key; // Ако за тази платформа няма стандартна клавишна комбинация.
  return standardKey;
}

void MainToolBar::showDailyReadPanel(bool show)
{
  btnNavigation_GoBack->setVisible(!show);
  btnNavigation_GoForward->setVisible(!show);
  btnNavigation_PreviousBook->setVisible(!show);
  btnNavigation_NextBook->setVisible(!show);
  btnNavigation_PreviousChapter->setVisible(!show);
  btnNavigation_NextChapter->setVisible(!show);
  labelBook->setVisible(!show);
  labelChapter->setVisible(!show);

  btnNavigation_PreviousChaptersDailyRead->setVisible(show);
  btnNavigation_NextChaptersDailyRead->setVisible(show);
  btnNavigation_PreviousChapterDailyRead->setVisible(show);
  btnNavigation_NextChapterDailyRead->setVisible(show);
  dailyReadGrLabel->setVisible(show);
  dailyReadChLabel->setVisible(show);
}

void MainToolBar::showAlphaPalette_LineEdit_SearchInText(bool show)
{
  if (show) // Ако трябва да покаже прозрачен фон.
  {
    if (lineEdit_SearchInText->text().isEmpty()) // Ако полето е празно.
    {
      lineEdit_SearchInText->setPalette(lineEdit_SearchInText_PaletteAlpha);
      lineEdit_SearchInText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      lineEdit_SearchInText->setText(QString("• %1 •").arg(TS->Search_v1));
      lineEdit_SearchInText_IsInactive = true;
    }
  }
  else // Ако трябва да покаже жълтия фон.
  {
    if (lineEdit_SearchInText_IsInactive) // Ако е показан прозрачният фон.
    {
      lineEdit_SearchInText->setPalette(lineEdit_SearchInText_PaletteYellow);
      lineEdit_SearchInText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      lineEdit_SearchInText->setText(""); // Премахва бледия текст.
      lineEdit_SearchInText_IsInactive = false;
    }
  }
}
