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

#include "projectortoolbar.h"
#include <QDebug>

ProjectorWidget::ProjectorWidget(MainWindow *MW) : QWidget()
{
  this->MW = MW;

  titlePanelHeight = 92;
  textFont.setFamily(MW->MO->SVars.fontFamily);
  textFont.setPointSize(80);
  textFont.setFixedPitch(true);
  textFont.setBold(false);
  textFont.setItalic(false);
  textFont.setStyleStrategy(QFont::PreferAntialias); // (PreferAntialias NoAntialias). Ако този ред се коментирта, Antialias ще е като на цялата програма.
  cTextFont = textFont;
  lineSpacing = 100;
  textHeight = 0;
  textUpper = false;
  textOutline = 0;
  textShadow = 2;
  embeddedWallpaperCircleBrightness = 40;

  projectorWindow = 0;
  isinitProjectorToolBar = false;

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setSpacing(3); // Разстояние между обектите.
  mainLayout->setContentsMargins(1, 1, 1, 1); // LTRB
}

ProjectorWidget::~ProjectorWidget()
{
  if (projectorWindow != 0)
  {
    projectorWindow->close();
    delete projectorWindow;
  }
}

void ProjectorWidget::initProjectorToolBar()
{
  // Този метод ще се извиква при всяко показване на тулбара на проектора, но реално ще се изпълни само веднъж - първия път.
  if (isinitProjectorToolBar) return;
  isinitProjectorToolBar = true;

  slotSetProjectorFontSize();

  projectorWindow = new ProjectorWindow();
  connect(projectorWindow, SIGNAL(projectorWindowMaximized()), this, SLOT(slotProjectorWindowMaximized())); // Този слот ще се изпълни при максимизиране на формата на проектора (максимизира се само веднъж - в началото).

  //QFrame *frameHLine1 = new QFrame;
  //frameHLine1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  //frameHLine1->setMinimumHeight(3);
  //frameHLine1->setMaximumHeight(3);
  //frameHLine1->setFrameShape(QFrame::HLine); //StyledPanel Panel NoFrame
  //frameHLine1->setFrameShadow(QFrame::Sunken); // Raised Sunken Plain

  //QFrame *frameHLine2 = new QFrame;
  //frameHLine2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  //frameHLine2->setMinimumHeight(3);
  //frameHLine2->setMaximumHeight(3);
  //frameHLine2->setFrameShape(QFrame::HLine); //StyledPanel Panel NoFrame
  //frameHLine2->setFrameShadow(QFrame::Sunken); // Raised Sunken Plain

  // MiniScreen
  previewWindow = new QWidget();
  previewWindow->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  lblPreviewBlack = new QLabel(previewWindow);
  QPalette palette;
  QBrush brush(QColor(0, 0, 0));
  brush.setStyle(Qt::SolidPattern);
  palette.setBrush(QPalette::Window, brush);
  palette.setBrush(QPalette::Button, brush);
  palette.setBrush(QPalette::Base, brush);
  lblPreviewBlack->setAutoFillBackground(true);
  lblPreviewBlack->setPalette(palette);
  lblPreviewBackground = new QLabel(previewWindow);
  lblPreviewBackground->setAlignment(Qt::AlignCenter);
  lblPreviewText = new QLabel(previewWindow);

  layout()->addWidget(previewWindow);

  // Control
  frameControl = new QFrame;
  frameControl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); // Тук трябва да е Fixed, за да не се свива панелът, защото ще се свият и бутоните и полетата в него.
  frameControl->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameControl->setFrameShadow(QFrame::Plain); // Raised Sunken Plain

  btnProjector = new QPushButton();
  btnProjector->setText(MW->MO->TS->Projector_v1.toUpper());
    QFont fontB = btnProjector->font();
    fontB.setBold(true);
  btnProjector->setFont(fontB);
  btnProjector->setCheckable(true);
  btnProjector->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(btnProjector, SIGNAL(clicked()), this, SLOT(slotBtnProjector_clicked()));

  btnHideText = new QToolButton();
  btnHideText->setText("X");
  btnHideText->setToolTip(MW->MO->TS->HideText_v1);
  btnHideText->setAutoRaise(true);
  connect(btnHideText, SIGNAL(clicked()), this, SLOT(slotBtnHideText_clicked()));

  chbHideText = new QCheckBox();
  chbHideText->setText(MW->MO->TS->HideText_v1);
  connect(chbHideText, SIGNAL(clicked()), this, SLOT(slotChbHideText_clicked()));

  chbDisable = new QCheckBox();
  chbDisable->setText(MW->MO->TS->LockScreen_v1);

  chbHideName = new QCheckBox();
  chbHideName->setText(MW->MO->TS->HideTheName_v1);
  connect(chbHideName, SIGNAL(clicked()), this, SLOT(slotChbHideName_clicked()));

  QHBoxLayout *controlHTLayout = new QHBoxLayout();
  controlHTLayout->setSpacing(0); // Разстояние между обектите.
  controlHTLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  controlHTLayout->addWidget(chbHideText);
  controlHTLayout->addWidget(btnHideText);

  QVBoxLayout *controlChbLayout = new QVBoxLayout();
  controlChbLayout->setSpacing(0); // Разстояние между обектите.
  controlChbLayout->setContentsMargins(2, 0, 0, 0); // LTRB
  controlChbLayout->addLayout(controlHTLayout);
  controlChbLayout->addWidget(chbDisable);
  controlChbLayout->addWidget(chbHideName);

  QGridLayout *controlLayout = new QGridLayout(frameControl);
  controlLayout->setSpacing(3); // Разстояние между обектите.
  controlLayout->setContentsMargins(0, 0, 0, 0);  // LTRB // Маргини на самия грид.
  controlLayout->addWidget(btnProjector, 0, 0, 1, 1);
  controlLayout->addLayout(controlChbLayout, 0, 1, 1, 1);
  //controlLayout->addWidget(frameHLine1, 1, 0, 1, 2);

  layout()->addWidget(frameControl);

  // Text
  frameText = new QFrame;
  frameText->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding); // Ако няма списък с история, тук трябва да е Fixed вместо Expanding, за да не се свива панелът, защото ще се свият и бутоните и полетата в него.
  frameText->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  frameText->setFrameShadow(QFrame::Plain); // Raised Sunken Plain

  btnTextZoomIn = new QPushButton();
  btnTextZoomIn->setFont(fontB);
  btnTextZoomIn->setText(QString("+"));
  btnTextZoomIn->setAutoRepeat(true);
  btnTextZoomIn->setAutoRepeatDelay(200);
  btnTextZoomIn->setAutoRepeatInterval(100);
  btnTextZoomIn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnTextZoomIn, SIGNAL(clicked()), this, SLOT(slotBtnTextSizeIn_clicked()));

  btnTextZoomOut = new QPushButton();
  btnTextZoomOut->setFont(fontB);
  btnTextZoomOut->setText(QString("-"));
  btnTextZoomOut->setAutoRepeat(true);
  btnTextZoomOut->setAutoRepeatDelay(200);
  btnTextZoomOut->setAutoRepeatInterval(100);
  btnTextZoomOut->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnTextZoomOut, SIGNAL(clicked()), this, SLOT(slotBtnTextSizeOut_clicked()));

  btnTextBold = new QPushButton();
  btnTextBold->setFont(fontB);
  btnTextBold->setCheckable(true);
  btnTextBold->setText(QString("B"));
  btnTextBold->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnTextBold, SIGNAL(clicked()), this, SLOT(slotBtnTextBold_clicked()));

  btnTextItalic = new QPushButton();
    QFont fontI = btnTextItalic->font();
    fontI.setItalic(true);
  btnTextItalic->setFont(fontI);
  btnTextItalic->setCheckable(true);
  btnTextItalic->setText(QString("I"));
  btnTextItalic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnTextItalic, SIGNAL(clicked()), this, SLOT(slotBtnTextItalic_clicked()));

  btnTextUpper = new QPushButton();
  btnTextUpper->setCheckable(true);
  btnTextUpper->setText(QString("UP"));
  btnTextUpper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnTextUpper, SIGNAL(clicked()), this, SLOT(slotBtnTextUpper_clicked()));

  btnTextColor = new QPushButton();
  btnTextColor->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  btnTextColor->setToolTip(MW->MO->TS->TextColor_v1);
  connect(btnTextColor, SIGNAL(clicked()), this, SLOT(slotBtnTextColor_clicked()));


  lblFontPointSize = new QLabel();
  lblFontPointSize->setFrameShape(QFrame::StyledPanel); //StyledPanel Panel NoFrame
  lblFontPointSize->setFrameShadow(QFrame::Raised); // Raised Sunken Plain
  lblFontPointSize->setAlignment(Qt::AlignCenter);
  lblFontPointSize->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  cbFont = new QFontComboBox();
  cbFont->setEditable(false);
  cbFont->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  if (cbFont->findText(QString("Serif")) == -1) // Ако фамилията "Serif" я нама в списъка.
    cbFont->insertItem(0, QString("Serif")); // Добавя фамилията "Serif" (която е по подразбиране) към списъка.
  if (cbFont->findText(QString("Sans")) == -1) // Ако фамилията "Sans" я нама в списъка.
    cbFont->insertItem(0, QString("Sans")); // Добавя фамилията "Sans" (която е по подразбиране) към списъка.
  cbFont->setToolTip(MW->MO->TS->CustomFont_v1);
  connect(cbFont, SIGNAL(currentFontChanged(QFont)), this, SLOT(slotCbFont_currentFontChanged(QFont)));

  QPainterPath path;
  path.addPolygon(QPolygonF() << QPointF(8.0, 0.0) << QPointF(8.0, 8.0) << QPointF(0.0, 4.0));
  QPixmap pix(8, 8);
  pix.fill(QColor(0, 0, 0, 0));
  QPainter painter(&pix);
  painter.setRenderHints(QPainter::Antialiasing, true);
  painter.fillPath(path, MW->MO->SVars.appColorB); // Ако се смени цветът на формата, тази икона ще си смени цвета едва след рестарт на програмата, но това не е фатално и не си струва да се прави по-сложно.
  btnFontMan = new QPushButton(pix, QString(""));
  btnFontMan->setCheckable(true);
  btnFontMan->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  btnFontMan->setToolTip(MW->MO->TS->EnableCustomFont_v1);
  connect(btnFontMan, SIGNAL(clicked()), this, SLOT(slotBtnFontMan_clicked()));

  cbTextAlignH = new QComboBox();
  cbTextAlignH->addItem(MW->MO->TS->Left_v1);
  cbTextAlignH->addItem(MW->MO->TS->Center_v1);
  cbTextAlignH->addItem(MW->MO->TS->Right_v1);
  //cbTextAlignH->addItem(QString("Двустранно")); // Justify // Това не мога да го направя по начина, по който правя нещата. Не че не мога, но е много сложно и не ми се занимава сега, а и няма да е приятно за четене в такъв режим.
  cbTextAlignH->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(cbTextAlignH, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbTextAlignH_currentIndexChanged(int)));

  cbTextAlignV = new QComboBox();
  cbTextAlignV->addItem(MW->MO->TS->Top_v1);
  cbTextAlignV->addItem(MW->MO->TS->Center_v1);
  cbTextAlignV->addItem(MW->MO->TS->Bottom_v1);
  cbTextAlignV->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(cbTextAlignV, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbTextAlignV_currentIndexChanged(int)));

  cbTextOutline = new QComboBox();
  cbTextOutline->addItem(QString("0"));  // Without outline
  cbTextOutline->addItem(QString("1o")); // Outline - 1px
  cbTextOutline->addItem(QString("2o")); // Outline - 2px
  cbTextOutline->addItem(QString("1s")); // Shadow - 1px
  cbTextOutline->addItem(QString("2s")); // Shadow - 2px
  cbTextOutline->addItem(QString("3s")); // Shadow - 3px
  cbTextOutline->addItem(QString("4s")); // Shadow - 4px
  cbTextOutline->addItem(QString("5s")); // Shadow - 5px
  cbTextOutline->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  cbTextOutline->setToolTip(MW->MO->TS->TextOutlineShadow_v1);
  connect(cbTextOutline, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbTextOutline_currentIndexChanged(int)));

  btnTextOutlineColor = new QPushButton();
  btnTextOutlineColor->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  btnTextOutlineColor->setToolTip(MW->MO->TS->OutlineShadowColor_v1);
  connect(btnTextOutlineColor, SIGNAL(clicked()), this, SLOT(slotChbTextOutlineColor_clicked()));

  cbTitleBarPosition = new QComboBox();
  cbTitleBarPosition->addItem(MW->MO->TS->LeftTitleBar_v1);
  cbTitleBarPosition->addItem(MW->MO->TS->TopTitleBar_v1);
  cbTitleBarPosition->addItem(MW->MO->TS->RightTitleBar_v1);
  cbTitleBarPosition->addItem(MW->MO->TS->BottomTitleBar_v1);
  cbTitleBarPosition->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(cbTitleBarPosition, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbTitleBarPosition_currentIndexChanged(int)));

  cbTitleBarAlpha = new QComboBox();
  cbTitleBarAlpha->addItem(MW->MO->TS->SemiTransparentTitleBar_v1);
  cbTitleBarAlpha->addItem(MW->MO->TS->TransparentTitleBar_v1);
  cbTitleBarAlpha->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(cbTitleBarAlpha, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbTitleBarAlpha_currentIndexChanged(int)));

  // Background
  //frameBackground = new QFrame;
  //frameBackground->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); // Тук трябва да е Fixed, за да не се свива панелът, защото ще се свият и бутоните и полетата в него.
  //frameBackground->setFrameShape(QFrame::NoFrame); //StyledPanel Panel NoFrame
  //frameBackground->setFrameShadow(QFrame::Plain); // Raised Sunken Plain

  cbWallpaperPosition = new QComboBox();
  cbWallpaperPosition->addItem(MW->MO->TS->PicFit_v1);     // Fit - Съразмерно
  cbWallpaperPosition->addItem(MW->MO->TS->PicFitEx_v1);   // FitEx - Съразмерно, Разширено
  cbWallpaperPosition->addItem(MW->MO->TS->PicStretch_v1); // Stretch - Разтеглено, Разширено, Разпънато
  cbWallpaperPosition->addItem(MW->MO->TS->PicCenter_v1);  // Center - 1:1
  cbWallpaperPosition->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  cbWallpaperPosition->setCurrentIndex(-1); // Това е важна инициализация!
  connect(cbWallpaperPosition, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbWallpaperPosition_currentIndexChanged(int)));

  cbWallpaper = new QComboBox();
  cbWallpaper->addItem(MW->MO->TS->EmbededPicture_v1);
  cbWallpaper->addItem(MW->MO->TS->ExternalPicture_v1);
  cbWallpaper->addItem(MW->MO->TS->Color_v1);
  cbWallpaper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  cbWallpaper->setCurrentIndex(-1); // Това е важна инициализация!
  connect(cbWallpaper, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCbWallpaper_currentIndexChanged(int)));

  btnWallpaperEmbedded = new QPushButton();
  btnWallpaperEmbedded->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  btnWallpaperEmbedded->setToolTip(MW->MO->TS->Brightness_v1);
  connect(btnWallpaperEmbedded, SIGNAL(clicked()), this, SLOT(slotBtnWallpaperEmbedded_clicked()));

  btnWallpaperCustom = new QPushButton();
  btnWallpaperCustom->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  connect(btnWallpaperCustom, SIGNAL(clicked()), this, SLOT(slotBtnWallpaperCustom_clicked()));

  btnWallpaperColor = new QPushButton();
  btnWallpaperColor->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  btnWallpaperColor->setToolTip(MW->MO->TS->Color_v1);
  connect(btnWallpaperColor, SIGNAL(clicked()), this, SLOT(slotBtnWallpaperColor_clicked()));

  btnSaveAsPic = new QPushButton();
  btnSaveAsPic->setText(MW->MO->TS->SaveAsPic_v1);
  btnSaveAsPic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  connect(btnSaveAsPic, SIGNAL(clicked()), this, SLOT(slotBtnSaveAsPic_clicked()));

  lwHistory = new QListWidget();
  //lwHistory->setFrameShape(QFrame::Box);
  //lwHistory->setFrameShadow(QFrame::Plain);
  lwHistory->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  lwHistory->setMinimumHeight(10);
  connect(lwHistory, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotLwHistory_itemClicked(QListWidgetItem *)));
  
  QGridLayout *textLayout = new QGridLayout(frameText);
  textLayout->setSpacing(3); // Разстояние между обектите.
  textLayout->setContentsMargins(0, 0, 0, 0);  // LTRB // Маргини на самия грид.
  textLayout->addWidget(btnTextZoomIn, 0, 0, 1, 1);
  textLayout->addWidget(btnTextZoomOut, 0, 1, 1, 1);
  textLayout->addWidget(btnTextBold, 0, 2, 1, 1);
  textLayout->addWidget(btnTextItalic, 0, 3, 1, 1);
  textLayout->addWidget(btnTextUpper, 0, 4, 1, 1);
  textLayout->addWidget(btnTextColor, 0, 5, 1, 1);
  textLayout->addWidget(lblFontPointSize, 1, 0, 1, 2);
  textLayout->addWidget(cbFont, 1, 2, 1, 3);
  textLayout->addWidget(btnFontMan, 1, 5, 1, 1);
  textLayout->addWidget(cbTextAlignH, 2, 0, 1, 2);
  textLayout->addWidget(cbTextAlignV, 2, 2, 1, 2);
  textLayout->addWidget(cbTextOutline, 2, 4, 1, 1);
  textLayout->addWidget(btnTextOutlineColor, 2, 5, 1, 1);
  textLayout->addWidget(cbTitleBarPosition, 3, 0, 1, 2);
  textLayout->addWidget(cbTitleBarAlpha, 3, 2, 1, 4);
  //textLayout->addWidget(frameHLine2, 4, 0, 1, 6);
  textLayout->addWidget(cbWallpaperPosition, 4, 0, 1, 2);
  textLayout->addWidget(cbWallpaper, 4, 2, 1, 3);
  textLayout->addWidget(btnWallpaperEmbedded, 4, 5, 1, 1); // Тези три бутона са разположени
  textLayout->addWidget(btnWallpaperCustom, 4, 5, 1, 1);   // на едно място, но винаги се
  textLayout->addWidget(btnWallpaperColor, 4, 5, 1, 1);    // показва само един от тях.
  textLayout->addWidget(btnSaveAsPic, 5, 0, 1, 6);
  textLayout->addWidget(lwHistory, 6, 0, 1, 6);

  layout()->addWidget(frameText);

  //QGridLayout *backgroundLayout = new QGridLayout(frameBackground);
  //backgroundLayout->setSpacing(3); // Разстояние между обектите.
  //backgroundLayout->setContentsMargins(0, 0, 0, 0);  // LTRB // Маргини на самия грид. <-- Тук трябва да е 1, ако се използва frameHLine2 разделителна линия.
  //backgroundLayout->addWidget(cbWallpaperPosition, 0, 0, 1, 2);
  //backgroundLayout->addWidget(cbWallpaper, 0, 2, 1, 3);
  //backgroundLayout->addWidget(btnWallpaperEmbedded, 0, 5, 1, 1); // Тези три бутона са разположени
  //backgroundLayout->addWidget(btnWallpaperCustom, 0, 5, 1, 1);   // на едно място, но винаги се
  //backgroundLayout->addWidget(btnWallpaperColor, 0, 5, 1, 1);    // показва само един от тях.
  //
  //layout()->addWidget(frameBackground);

  // Ако няма списък с история, долните три реда трябва да се разкоментират, за да се добави спейсър, който да избутва нещата нагоре. Също и по-горе трябва да се направи SizePolicy на frameText да е Fixed.
  //QSpacerItem *verticalSpacer;
  //verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  //layout()->addItem(verticalSpacer);

  circleWidgetPreview = new CircleWidget(this->lblPreviewBlack);
  circleWidgetProjector = new CircleWidget(projectorWindow->lblProjectorBlack);

  loadSettings();

  if (projectorScreenWidth > 10 && projectorScreenHeight > 10) // Ако в INI файла са зададени стойности от потребителя (на ръка).
  {
    projectorWindow->move(projectorScreenX, projectorScreenY);
    projectorWindow->setMinimumSize(QSize(projectorScreenWidth, projectorScreenHeight));
    projectorWindow->setMaximumSize(QSize(projectorScreenWidth, projectorScreenHeight));

    projectorWindow->lblProjectorBlack->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));
    projectorWindow->lblProjectorBackground->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));
    projectorWindow->lblProjectorText->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));

    resizeGeometry();
  }
  else // Ако размерите на проектора трябва да се изчислят автоматично.
  {
    projectorWindow->move(projectorScreenXAuto, 0); // Отмества формата на projectorScreenXAuto точки, за да се покаже на другият екран (т.е. на проектора). Ако компютърът е само с един екран (без проектор), формата ще се покаже на този екран.
    projectorWindow->showFullScreen(); //projectorWindow->showMaximized(); // Показва формата максимизирана, но почти веднага след това (в слота slotProjectorWindowMaximized) ще я скрие. Идеята е да се вземе размера ѝ, след като се максимизира.

    //resizeGeometry(); - този метод се извиква в слота slotProjectorWindowMaximized.
  }

  if (cbWallpaper->currentIndex() == 0) // Embedded Wallpaper.
  {
    circleWidgetPreview->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetProjector->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetPreview->enableCircles(true);
    circleWidgetProjector->enableCircles(true);
  }
}

void ProjectorWidget::slotProjectorWindowMaximized()
{
  // Тази функция се извиква еднократно при първо максимизиране на прозореца за проектора.
  // Използва се за скриване на прозореца и за предварително премащабиране на картинките за фон.

  projectorScreenX = projectorWindow->geometry().x(); // rect() geometry()
  projectorScreenY = projectorWindow->geometry().y();
  projectorScreenWidth = projectorWindow->geometry().width();
  projectorScreenHeight = projectorWindow->geometry().height();

  projectorWindow->lblProjectorBlack->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));
  projectorWindow->lblProjectorBackground->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));
  projectorWindow->lblProjectorText->setGeometry(QRect(0, 0, projectorScreenWidth, projectorScreenHeight));

  projectorWindow->lower(); // Това ще постави на заден план екрана на проектора, под другите екрани (на други програми-проектори).
  projectorWindow->setVisible(false); // Скрива прозореца за проектора.
  //MW->raise();
  //MW->activateWindow(); // Това ще изкара на преден план прозореца на програмата (това е много важно иначе може програмата да остане зад екрана на проектора).

  resizeGeometry();

#ifdef Q_OS_LINUX //Q_WS_WIN  Q_OS_LINUX  Q_OS_MAC  Q_OS_UNIX  Q_OS_WIN
  // Това е заради Линукс:
  // Ако ги няма долните редове се показва другия десктоп (Workspace) и остава на него, като в същото време прозорецът остава някак невидим. Голяма каша е в този Линукс...
  QTimer::singleShot(500, btnProjector, SLOT(click())); // Симулира натискане на бутона за показване на прозореца на проектора.
  QTimer::singleShot(900, btnProjector, SLOT(click())); // Симулира натискане на бутона за скриване на прозореца на проектора.
#endif
}

void ProjectorWidget::loadSettings()
{
  chbDisable->setChecked(true); // Това ще забрани опресняването на малкия екран (проекторът не е включен в този момент) докато се сетнат всички настройки.

  QSettings settings(MW->MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  settings.beginGroup("Projector");
    chbHideName->setChecked(settings.value("hideTheName", false).toBool());
    btnFontMan->setChecked(settings.value("textFontMan", false).toBool());
    cbFont->setEnabled(btnFontMan->isChecked());
    textFont.setFamily(settings.value("textFamily", MW->MO->SVars.fontFamily).toString());
    textFont.setPointSize(settings.value("textPointSize", 80).toInt());
    textFont.setBold(settings.value("textBold", true).toBool());
    textFont.setItalic(settings.value("textItalic", true).toBool());
    textUpper = settings.value("textUpper", false).toBool();
    textColor.setNamedColor( settings.value("textColor", "").toString() );
      if (!textColor.isValid()) textColor = QColor(255,255,255); // Бял.
    int index = settings.value("textAlignH", 1).toInt();
      if (index < 0 || index > 2) index = 1;
    cbTextAlignH->setCurrentIndex(index);
    index = settings.value("textAlignV", 1).toInt();
      if (index < 0 || index > 2) index = 0;
    cbTextAlignV->setCurrentIndex(index);
    textShadow = settings.value("textShadow", 2).toInt();
      if (textShadow < 0 || textShadow > 5) textShadow = 2;
    textOutline = settings.value("textOutline", 0).toInt();
      if (textOutline < 0 || textOutline > 2 || textShadow > 0) textOutline = 0; // Ако има сянка, контурът става 0.
    if (textShadow > 0)
      cbTextOutline->setCurrentIndex(textShadow+2);
    else
      cbTextOutline->setCurrentIndex(textOutline);
    textOutlineColor.setNamedColor( settings.value("textOutlineColor", "").toString() );
      if (!textOutlineColor.isValid()) textOutlineColor = QColor(68,68,68); // Сив.
    index = settings.value("titleBarPosition", 1).toInt();
      if (index < 0 || index > 4) index = 1;
      cbTitleBarPosition->setCurrentIndex(index);
    index = settings.value("titleBarAlpha", 0).toInt();
      if (index < 0 || index > 1) index = 0;
      cbTitleBarAlpha->setCurrentIndex(index);
    index = settings.value("wallpaperPosition", 1).toInt();
      if (index < 0 || index > 3) index = 1;
      cbWallpaperPosition->setCurrentIndex(index);
    index = settings.value("wallpaperType", 0).toInt();
      if (index < 0 || index > 2) index = 0;
      cbWallpaper->setCurrentIndex(index);
      cbWallpaperPosition->setEnabled(index == 1);
    embeddedWallpaperCircleBrightness = settings.value("wallpaperEmCircleBrightness", 40).toInt();
	if (embeddedWallpaperCircleBrightness < 20 || embeddedWallpaperCircleBrightness > 120 || (embeddedWallpaperCircleBrightness % 10) != 0) embeddedWallpaperCircleBrightness = 40;
    btnWallpaperEmbedded->setText(QString("%1").arg(embeddedWallpaperCircleBrightness));
    wallpaperFile = settings.value("wallpaperFile", "").toString();
    wallpapersPath = settings.value("wallpapersPath", "").toString();
    wallpaperColor.setNamedColor( settings.value("wallpaperColor", "").toString() );
      if (!wallpaperColor.isValid()) wallpaperColor = QColor(0,0,0); // Черен.

    // Следващите са само за четене (програмата не променя стойностите им - потребителят може да ги промени само на ръка от файла).
    projectorScreenXAuto = settings.value("projectorScreenXAuto", -10000).toInt();
    if (projectorScreenXAuto == -10000) settings.setValue("projectorScreenXAuto", 2000); // За да се появи в ini-файла, за да може потребителят да смени стойността му от там.
    projectorScreenX = settings.value("projectorScreenX", -10000).toInt();
    if (projectorScreenX == -10000) settings.setValue("projectorScreenX", 0);// За да се появи в ini-файла, за да може потребителят да смени стойността му от там.
    projectorScreenY = settings.value("projectorScreenY", -10000).toInt();
    if (projectorScreenY == -10000) settings.setValue("projectorScreenY", 0);// За да се появи в ini-файла, за да може потребителят да смени стойността му от там.
    projectorScreenWidth = settings.value("projectorScreenWidth", -10000).toInt();
    if (projectorScreenWidth == -10000) settings.setValue("projectorScreenWidth", 0);// За да се появи в ini-файла, за да може потребителят да смени стойността му от там.
    projectorScreenHeight = settings.value("projectorScreenHeight", -10000).toInt();
    if (projectorScreenHeight == -10000) settings.setValue("projectorScreenHeight", 0);// За да се появи в ini-файла, за да може потребителят да смени стойността му от там.
  settings.endGroup();

  lblFontPointSize->setText(QString("%1 (Max %2)").arg(textFont.pointSize()).arg(textFont.pointSize()));

  QPixmap pmColor(16, 16);

  btnTextBold->setChecked(textFont.bold());
  btnTextItalic->setChecked(textFont.italic());
  btnTextUpper->setChecked(textUpper);
  pmColor.fill(textColor);
  btnTextColor->setIcon(pmColor);
  cbFont->setCurrentIndex(cbFont->findText(textFont.family()));
  pmColor.fill(textOutlineColor);
  btnTextOutlineColor->setIcon(pmColor);
  pmColor.fill(wallpaperColor);
  btnWallpaperColor->setIcon(pmColor);
  pmColor.fill(QColor(0,0,0,50)); // Полупрозрачност.
  btnWallpaperCustom->setIcon(pmColor);

  chbDisable->setChecked(false);
}

void ProjectorWidget::saveSettings()
{
  if (!isinitProjectorToolBar) return;

  QSettings settings(MW->MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

  settings.beginGroup("Projector");
    settings.setValue("hideTheName", chbHideName->isChecked());
    settings.setValue("textFontMan", btnFontMan->isChecked());
    settings.setValue("textFamily", cbFont->currentText());
    settings.setValue("textPointSize", textFont.pointSize());
    settings.setValue("textBold", textFont.bold());
    settings.setValue("textItalic", textFont.italic());
    settings.setValue("textUpper", textUpper);
    settings.setValue("textColor", textColor.name());
    settings.setValue("textAlignH", cbTextAlignH->currentIndex());
    settings.setValue("textAlignV", cbTextAlignV->currentIndex());
    settings.setValue("textShadow", textShadow);
    settings.setValue("textOutline", textOutline);
    settings.setValue("textOutlineColor", textOutlineColor.name());
    settings.setValue("titleBarPosition", cbTitleBarPosition->currentIndex());
    settings.setValue("titleBarAlpha", cbTitleBarAlpha->currentIndex());
    settings.setValue("wallpaperPosition", cbWallpaperPosition->currentIndex());
    settings.setValue("wallpaperType", cbWallpaper->currentIndex());
    settings.setValue("wallpaperEmCircleBrightness", embeddedWallpaperCircleBrightness);
    settings.setValue("wallpaperFile", wallpaperFile);
    settings.setValue("wallpapersPath", wallpapersPath);
    settings.setValue("wallpaperColor", wallpaperColor.name());
  settings.endGroup();
}

void ProjectorWidget::resizeGeometry()
{
  previewScreenWidth = MW->MO->SVars.projectorToolBarPrevSize;

  frameControl->setMinimumWidth(previewScreenWidth);
  frameControl->setMaximumWidth(previewScreenWidth);
  frameText->setMinimumWidth(previewScreenWidth);
  frameText->setMaximumWidth(previewScreenWidth);
  //frameBackground->setMinimumWidth(previewScreenWidth);
  //frameBackground->setMaximumWidth(previewScreenWidth);

  // Формата на малкия екран трябва да е пропорционална на тази на проектора. Ето защо малкият екран е с константна
  // широчина, а височината му се преоразмерява в този метод, за да стане пропорционален на проектора.
  //
  // Mh/Mw = Gh/Gw   Mh = Mw * Gh / Gw
  // Mw/Mh = Gw/Gh   Mw = Mh * Gw / Gh
  //
  previewScreenHeight = previewScreenWidth * projectorScreenHeight / projectorScreenWidth;

  previewWindow->setMinimumSize(QSize(previewScreenWidth, previewScreenHeight));
  previewWindow->setMaximumSize(QSize(previewScreenWidth, previewScreenHeight));
  lblPreviewBlack->setGeometry(QRect(0, 0, previewScreenWidth, previewScreenHeight));
  lblPreviewBackground->setGeometry(QRect(0, 0, previewScreenWidth, previewScreenHeight));
  lblPreviewText->setGeometry(QRect(0, 0, previewScreenWidth, previewScreenHeight));

  circleWidgetPreview->resize(previewScreenWidth, previewScreenHeight);
  circleWidgetProjector->resize(projectorScreenWidth, projectorScreenHeight);
  if (cbWallpaper->currentIndex() == 0) // Embedded Wallpaper.
  {
    circleWidgetPreview->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetProjector->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetPreview->enableCircles(true);
    circleWidgetProjector->enableCircles(true);
  }

  // Целта на следващите редове е да мащабира вградената картинка така, че да се намести на всякакъв екран.
  QPixmap embeddedPic(":/resources/images/embeddedbg_text.png"); // // Това е вградената картинка, която трябва да се покаже. Ако е по-голяма ще се намали, ако е по-малка ще се увелични. Ако не е пропорционална ще стърчи и ще е центрирана.
  embeddedWallpaperProjectorScreen = embeddedPic.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation); // Qt::FastTransformation   Qt::SmoothTransformation
  embeddedWallpaperPreviewScreen = embeddedPic.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation); // Qt::FastTransformation   Qt::SmoothTransformation

  // Мащабира картинките с цвят на фона, които се използват когато е избран цвят, а не картина.
  QPixmap pmcolorPj(projectorScreenWidth, projectorScreenHeight);
  QPixmap pmcolorPv(previewScreenWidth, previewScreenHeight);

  pmcolorPj.fill(wallpaperColor);
  pmcolorPv.fill(wallpaperColor);
  colorWallpaperProjectorScreen = pmcolorPj;
  colorWallpaperPreviewScreen = pmcolorPv;

  pmcolorPj.fill(QColor(0,0,0));
  pmcolorPv.fill(QColor(0,0,0));
  customWallpaperProjectorScreen = pmcolorPj; // Инициализира се с черен цвят.
  customWallpaperPreviewScreen = pmcolorPv;   // Инициализира се с черен цвят.
  if (!wallpaperFile.isEmpty())
  {
    QPixmap pmWallpaper(wallpaperFile);
    
    if (!pmWallpaper.isNull()) // Ако е картинка.
    {
      if (cbWallpaperPosition->currentIndex() == 0) // Fit
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 1) // Fit Expanding
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 2) // Stretch
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 3) // Center
      {
        int width = (int)( (double)previewScreenWidth / (double)projectorScreenWidth * (double)pmWallpaper.width() );
        customWallpaperPreviewScreen =  pmWallpaper.scaledToWidth(width, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper;
      }
      btnWallpaperCustom->setIcon(pmWallpaper.scaled(16, 16));
    }
  }

  if (cbWallpaper->currentIndex() == 0)
  {
    currentWallpaperProjectorScreen = embeddedWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = embeddedWallpaperPreviewScreen;
  }
  else if (cbWallpaper->currentIndex() == 1)
  {
    currentWallpaperProjectorScreen = customWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = customWallpaperPreviewScreen;
  }
  else if (cbWallpaper->currentIndex() == 2)
  {
    currentWallpaperProjectorScreen = colorWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = colorWallpaperPreviewScreen;
  }

  projectorWindow->lblProjectorBackground->setPixmap(currentWallpaperProjectorScreen);
  lblPreviewBackground->setPixmap(currentWallpaperPreviewScreen);

  if (cbTitleBarPosition->currentIndex() == 0) // Left
  {
    textArea.setX(20 + titlePanelHeight);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (cbTitleBarPosition->currentIndex() == 2) // Right
  {
    textArea.setX(20);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20 - titlePanelHeight); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (cbTitleBarPosition->currentIndex() == 1) // Top
  {
    textArea.setX(20);
    textArea.setY(15 + titlePanelHeight);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (cbTitleBarPosition->currentIndex() == 3) // Bottom
  {
    textArea.setX(20);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15 - titlePanelHeight); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }

  refreshScreens();
}

void ProjectorWidget::splitText(QFont font, QString text, QStringList *textLines)
{
  // Този метод разделя текста на няколко реда.

  textLines->clear();
  QStringList textList = text.split(" ", QString::SkipEmptyParts); // Разделя текста (стиха) на думи, като за разделител е използван интервал.

  cTextFont = font;
  QFontMetrics fm(cTextFont);
  lineSpacing = fm.lineSpacing();
  QString word, wordPlusSpace;
  int wordWidth, wordWidthPlusSpace;
  QString currLine = "";  
  int currLineWidth = 0;
  for (int w = 0; w < textList.length(); w++)
  {
    word = textList[w];           wordPlusSpace = word + " ";
    wordWidth = fm.width(word);   wordWidthPlusSpace = fm.width(word + " ");

    if ( wordWidth > textArea.width() && cTextFont.pointSize() > 1 ) // Ако думата е по-голяма от дължината на един ред.
    {
      cTextFont.setPointSize(cTextFont.pointSize() - 1);
      splitText(cTextFont, text, textLines); // Рекурсивно извикване на този метод, но с по-малък размер на шрифта.
      return;
    }

    if ( (currLineWidth + wordWidth) < textArea.width() )
    {
      currLine += wordPlusSpace;
      currLineWidth += wordWidthPlusSpace;
    }
    else
    {
      *textLines << currLine.trimmed(); // Това е текущия ред с премахнат последен интервал.
      currLine = wordPlusSpace;
      currLineWidth = wordWidthPlusSpace;
    }
  }
  *textLines << currLine.trimmed();

  // Проверка дали се събират всички редове на текста:
  textHeight = ((*textLines).length() * lineSpacing) - (lineSpacing - cTextFont.pointSize()); // Изважда се последното разстояние между редовете.
  if ((*textLines).length() > 1 && textHeight > textArea.height()) // Ако редовете не се събират.
  {
    // Прави се изчисление дали текстът ще се събере, ако се намали разстоянието между редовете.
    int spacing = (textArea.height() - ((*textLines).length() * cTextFont.pointSize())) / (*textLines).length() - 1; // Това е разстоянието между редовете, ако се направи така, че всички редове да се съберат.
    if (spacing > 15) // Ако това разстояние е достатъчно за да не се получи припокриване на редовете.
    {
      lineSpacing = cTextFont.pointSize() + spacing;
      textHeight = ((*textLines).length() * lineSpacing) - (lineSpacing - cTextFont.pointSize()); // Изважда се последното разстояние между редовете.
    }
    else // Ако това разстояние е твърде малко вследствие на което ще се получи припокриване на редовете.
    {
      if (cTextFont.pointSize() > 1)
      {
        cTextFont.setPointSize(cTextFont.pointSize() - 1);
        splitText(cTextFont, text, textLines); // Рекурсивно извикване на този метод, но с по-малък размер на шрифта.
        return;
      }
    }
  }
}

void ProjectorWidget::setScreenText(QString bibleText, QString chapter, QString verse, quint16 absIndex, QString nativeFontFamily)
{
  if (absIndex < MAX_VERSES && !historyMap.contains(absIndex)) // Ако този метод е извикан от списъка с историята, absIndex ще бъде MAX_VERSES.
  {
    // Първо изтрива списъка, ако е нараснал твърде много (грубо, но няма нужда от специална логика, която да остави най-новите, а и ще е излишно сложна за направа):
    if (historyMap.size() > 500) // Това е достатъчно голяма стойност, при която хисторито става неизползваемо, а и едва ли някой ще достигне, в същото време няма да натоварва много.
    {
      historyMap.clear();
      lwHistory->clear();
    }

    // Добавя новия стих:
    PROJECTOR_HISTORY ph;
    ph.bibleText = bibleText;
    ph.chapter = chapter;
    ph.verse = verse;
    ph.absIndex = absIndex;
    ph.nativeFontFamily = nativeFontFamily;
    historyMap.insert(absIndex, ph);

    // Трябва да се открие на кой индекс е новозаписаният стих, но няма метод в QMap, който да връща поредния индекс и се налага по този тъп начин:
    int index = -1;
    QMapIterator<quint16, PROJECTOR_HISTORY> iterator(historyMap);
    while (iterator.hasNext())
    {
      iterator.next();
      index++;
      if (iterator.key() == absIndex)
      {
        lwHistory->insertItem(index, chapter);
        break;
      }
    }
  }

  this->bibleText = bibleText;
  this->chapter = chapter;
  this->verse = verse;
  this->nativeFontFamily = nativeFontFamily;
  refreshScreens();
}

void ProjectorWidget::refreshScreens()
{
  projectorWindow->lblProjectorText->setVisible(!chbHideText->isChecked());
  lblPreviewText->setVisible(!chbHideText->isChecked());
  if (chbHideText->isChecked()) return; // Този ред трябва да е преди долния, за да е с по-голям приоритет.
  if (chbDisable->isChecked()) return;

  if (btnFontMan->isChecked())
  {
    textFont.setFamily(cbFont->currentText());
  }
  else
  {
    textFont.setFamily(nativeFontFamily);
  }

  QStringList textLines;
  splitText(textFont, textUpper ? verse.toUpper() : verse, &textLines);
  lblFontPointSize->setText(QString("%1 (Max %2)").arg(cTextFont.pointSize()).arg(textFont.pointSize()));


  QPixmap pixmap(projectorScreenWidth, projectorScreenHeight); // Върху тази картинка ще се изписва текстът и страничният панел с името на текста и главата.
  pixmap.fill(QColor(0, 0, 0, 0)); // Прозрачност.

  QPainter painter(&pixmap);
  painter.setFont(cTextFont);
  painter.setRenderHints(QPainter::Antialiasing, false); // Това не важи за текста, защото се взима Antialias на cTextFont. Важи за всички други обекти, като панел за името на текста и книгата.

  int shiftY = 0;
  if (cbTextAlignV->currentIndex() == 1) // Ако текстът е по средата.
    shiftY = (textArea.height() - textHeight) / 2;
  else if (cbTextAlignV->currentIndex() == 2) // Ако текстът е долу.
    shiftY = textArea.height() - textHeight;
  int Y = textArea.y() + shiftY + cTextFont.pointSize(); // Положение по Y на първия ред.
  int X; // Положение по X за всеки ред.
  QFontMetrics fm(cTextFont);

  if (textOutline > 0) // Ако трябва да се изпише контур.
  {
    painter.setPen(textOutlineColor);
    for (int i = 0; i < textLines.count(); i++)
    {
      X = textArea.x();
      if (cbTextAlignH->currentIndex() == 1) // Ако текстът е по средата.
        X = X + (textArea.width() - fm.width(textLines[i])) / 2;
      else if (cbTextAlignH->currentIndex() == 2) // Ако текстът е в дясно.
        X = X + textArea.width() - fm.width(textLines[i]);

      painter.drawText(X + textOutline, Y + (i*lineSpacing) + textOutline, textLines[i]);
      painter.drawText(X + textOutline, Y + (i*lineSpacing) - textOutline, textLines[i]);
      painter.drawText(X - textOutline, Y + (i*lineSpacing) - textOutline, textLines[i]);
      painter.drawText(X - textOutline, Y + (i*lineSpacing) + textOutline, textLines[i]);
    }
  }
  else if (textShadow > 0) // Ако трябва да се изпише сянка.
  {
    painter.setPen(textOutlineColor);
    for (int i = 0; i < textLines.count(); i++)
    {
      X = textArea.x();
      if (cbTextAlignH->currentIndex() == 1) // Ако текстът е по средата.
        X = X + (textArea.width() - fm.width(textLines[i])) / 2;
      else if (cbTextAlignH->currentIndex() == 2) // Ако текстът е в дясно.
        X = X + textArea.width() - fm.width(textLines[i]);

      painter.drawText(X + textShadow, Y + (i*lineSpacing) + textShadow, textLines[i]);
    }
  }

  painter.setPen(textColor);
  for (int i = 0; i < textLines.count(); i++)
  {
    X = textArea.x();
    if (cbTextAlignH->currentIndex() == 1) // Ако текстът е по средата.
      X = X + (textArea.width() - fm.width(textLines[i])) / 2;
    else if (cbTextAlignH->currentIndex() == 2) // Ако текстът е в дясно.
      X = X + textArea.width() - fm.width(textLines[i]);

    painter.drawText(X, Y + (i*lineSpacing), textLines[i]);
  }

  // Заглавният панел:
  if (!chapter.isEmpty() || !bibleText.isEmpty())
  {
    if (cbTitleBarPosition->currentIndex() == 0) // Left
    {
      painter.setPen(QPen(textColor, 1));
      //painter.drawRect(textArea);
      QColor titlePanelColor(textColor);
      if (cbTitleBarAlpha->currentIndex() == 0)
        titlePanelColor.setAlpha(80);
      else
        titlePanelColor.setAlpha(0);
      painter.setBrush(titlePanelColor);
      painter.drawRect(-1, -1, titlePanelHeight, projectorScreenHeight+2);

      painter.rotate(270); // -90
      QFont titlePanelFont(cTextFont);
      titlePanelFont.setBold(true);
      titlePanelFont.setItalic(true);

      // Изписва книгата:
      titlePanelFont.setPointSize(40);
      QFontMetrics fmC(titlePanelFont);
      int wordWidthC = fmC.width(chapter); // Дължина на думата в точки.
      painter.setFont(titlePanelFont);
      painter.setPen(textOutlineColor);
      painter.drawText(-wordWidthC-19, 80, chapter);
      painter.setPen(textColor);
      painter.drawText(-wordWidthC-20, 79, chapter);

      // Изписва името на текста:
      if (!chbHideName->isChecked())
      {
        titlePanelFont.setPointSize(24);
        painter.setFont(titlePanelFont);
        painter.setPen(textOutlineColor);
        painter.drawText(-projectorScreenHeight+16, 31, bibleText);
        painter.setPen(textColor);
        painter.drawText(-projectorScreenHeight+15, 30, bibleText);
      }
    }
    else if (cbTitleBarPosition->currentIndex() == 2) // Right
    {
      painter.setPen(QPen(textColor, 1));
      //painter.drawRect(textArea);
      QColor titlePanelColor(textColor);
      if (cbTitleBarAlpha->currentIndex() == 0)
        titlePanelColor.setAlpha(80);
      else
        titlePanelColor.setAlpha(0);
      painter.setBrush(titlePanelColor);
      painter.drawRect(projectorScreenWidth-titlePanelHeight, -1, titlePanelHeight, projectorScreenHeight+2);

      painter.rotate(270); // -90
      QFont titlePanelFont(cTextFont);
      titlePanelFont.setBold(true);
      titlePanelFont.setItalic(true);

      // Изписва книгата:
      titlePanelFont.setPointSize(40);
      QFontMetrics fmC(titlePanelFont);
      int wordWidthC = fmC.width(chapter); // Дължина на думата в точки.
      painter.setFont(titlePanelFont);
      painter.setPen(textOutlineColor);
      painter.drawText(-wordWidthC-19, projectorScreenWidth+35-79, chapter);
      painter.setPen(textColor);
      painter.drawText(-wordWidthC-20, projectorScreenWidth+35-80, chapter);

      // Изписва името на текста:
      if (!chbHideName->isChecked())
      {
        titlePanelFont.setPointSize(24);
        painter.setFont(titlePanelFont);
        painter.setPen(textOutlineColor);
        painter.drawText(-projectorScreenHeight+16, projectorScreenWidth+23-30, bibleText);
        painter.setPen(textColor);
        painter.drawText(-projectorScreenHeight+15, projectorScreenWidth+23-31, bibleText);
      }
    }
    else if (cbTitleBarPosition->currentIndex() == 1) // Top
    {
      painter.setPen(QPen(textColor, 1));
      //painter.drawRect(textArea);
      QColor titlePanelColor(textColor);
      if (cbTitleBarAlpha->currentIndex() == 0)
        titlePanelColor.setAlpha(80);
      else
        titlePanelColor.setAlpha(0);
      painter.setBrush(titlePanelColor);
      painter.drawRect(-1, -1, projectorScreenWidth+2, titlePanelHeight);

      QFont titlePanelFont(cTextFont);
      titlePanelFont.setBold(true);
      titlePanelFont.setItalic(true);

      // Изписва книгата:
      titlePanelFont.setPointSize(40);
      QFontMetrics fmC(titlePanelFont);
      int wordWidthC = fmC.width(chapter); // Дължина на думата в точки.
      painter.setFont(titlePanelFont);
      painter.setPen(textOutlineColor);
      painter.drawText(projectorScreenWidth-wordWidthC-19, 80, chapter);
      painter.setPen(textColor);
      painter.drawText(projectorScreenWidth-wordWidthC-20, 79, chapter);

      // Изписва името на текста:
      if (!chbHideName->isChecked())
      {
        titlePanelFont.setPointSize(24);
        painter.setFont(titlePanelFont);
        painter.setPen(textOutlineColor);
        painter.drawText(16, 31, bibleText);
        painter.setPen(textColor);
        painter.drawText(15, 30, bibleText);
      }
    }
    else if (cbTitleBarPosition->currentIndex() == 3) // Bottom
    {
      painter.setPen(QPen(textColor, 1));
      //painter.drawRect(textArea);
      QColor titlePanelColor(textColor);
      if (cbTitleBarAlpha->currentIndex() == 0)
        titlePanelColor.setAlpha(80);
      else
        titlePanelColor.setAlpha(0);
      painter.setBrush(titlePanelColor);
      painter.drawRect(-1, projectorScreenHeight-titlePanelHeight, projectorScreenWidth+2, titlePanelHeight);

      QFont titlePanelFont(cTextFont);
      titlePanelFont.setBold(true);
      titlePanelFont.setItalic(true);

      // Изписва книгата:
      titlePanelFont.setPointSize(40);
      QFontMetrics fmC(titlePanelFont);
      int wordWidthC = fmC.width(chapter); // Дължина на думата в точки.
      painter.setFont(titlePanelFont);
      painter.setPen(textOutlineColor);
      painter.drawText(projectorScreenWidth-wordWidthC-19, projectorScreenHeight+35-79, chapter);
      painter.setPen(textColor);
      painter.drawText(projectorScreenWidth-wordWidthC-20, projectorScreenHeight+35-80, chapter);

      // Изписва името на текста:
      if (!chbHideName->isChecked())
      {
        titlePanelFont.setPointSize(24);
        painter.setFont(titlePanelFont);
        painter.setPen(textOutlineColor);
        painter.drawText(16, projectorScreenHeight+23-30, bibleText);
        painter.setPen(textColor);
        painter.drawText(15, projectorScreenHeight+23-31, bibleText);
      }
    }
  }

  projectorWindow->lblProjectorText->setPixmap(pixmap); // Тази картинка трябва да се показва винаги, даже когато екранът на проектора е скрит, защото се използва от бутона SaveAsPic.
  lblPreviewText->setPixmap( pixmap.scaled(previewScreenWidth, previewScreenHeight) ); // Първо премащабира голямата картинка и после я показва.
}

void ProjectorWidget::slotBtnProjector_clicked()
{
  if (btnProjector->isChecked())
  {
    refreshScreens();

    projectorWindow->setVisible(true); // Показва прозореца на проектора.
    projectorWindow->raise();   projectorWindow->activateWindow(); // Това ще изкара на преден план екрана на проектора над другите екрани (на други програми-проектори).
    MW->raise();                MW->activateWindow();              // Това ще изкара на преден план прозореца на програмата (това е много важно иначе може програмата да остане зад екрана на проектора).

    // Зелен цвят на текста на бутон "ПРОЕКТОР".
    QPalette palette;
    palette.setBrush(QPalette::ButtonText, QColor(0, 170, 170));
    btnProjector->setPalette(palette);
  }
  else
  {
    projectorWindow->lower(); // Това ще постави на заден план екрана на проектора под другите екрани (на други програми-проектори).
    projectorWindow->setVisible(false); // Скрива прозореца на проектора.

    // Цвят по подразбиране на текста на бутон "ПРОЕКТОР".
    QPalette palette;
    palette.setBrush(QPalette::ButtonText, btnTextUpper->palette().brush(QPalette::Active, QPalette::ButtonText).color());
    btnProjector->setPalette(palette);
  }
}

void ProjectorWidget::slotBtnHideText_clicked()
{
  bibleText = "";
  chapter = "";
  verse = "";
  refreshScreens();
}

void ProjectorWidget::slotChbHideText_clicked()
{
  refreshScreens();
}

void ProjectorWidget::slotChbHideName_clicked()
{
  refreshScreens();
}

void ProjectorWidget::slotBtnTextSizeIn_clicked()
{
  int ps = textFont.pointSize();
  ps++;
  textFont.setPointSize(ps);
  refreshScreens();
}

void ProjectorWidget::slotBtnTextSizeOut_clicked()
{
  int ps = textFont.pointSize();
  ps--;
  textFont.setPointSize(ps);
  refreshScreens();
}

void ProjectorWidget::slotBtnTextBold_clicked()
{
  textFont.setBold(btnTextBold->isChecked());
  refreshScreens();
}

void ProjectorWidget::slotBtnTextItalic_clicked()
{
  textFont.setItalic(btnTextItalic->isChecked());
  refreshScreens();
}

void ProjectorWidget::slotBtnTextUpper_clicked()
{
  textUpper = btnTextUpper->isChecked();
  refreshScreens();
}

void ProjectorWidget::slotBtnTextColor_clicked()
{
  QColor color = QColorDialog::getColor(textColor, this);
  if (color.isValid())
  {
    textColor = color;
    QPixmap pmColor(16, 16);
    pmColor.fill(textColor);
    btnTextColor->setIcon(pmColor);
    refreshScreens();
  }
}

void ProjectorWidget::slotCbFont_currentFontChanged(const QFont &font)
{
  bool isBold = textFont.bold(); // Взима текущата настройка за Bold преди шрифтът да бъде сменен.
  bool isItalic = textFont.italic(); // Взима текущата настройка за Italic преди шрифтът да бъде сменен.
  textFont.setFamily(font.family());
  //textFont = font; // Запомня новия шрифт.
  textFont.setBold(isBold); // Възтановява настройката за Bold.
  textFont.setItalic(isItalic); // Възтановява настройката за Italic.
  refreshScreens();
}

void ProjectorWidget::slotBtnFontMan_clicked()
{
  cbFont->setEnabled(btnFontMan->isChecked());
  refreshScreens();
}

void ProjectorWidget::slotCbTextAlignH_currentIndexChanged(int /*index*/)
{
  refreshScreens();
}

void ProjectorWidget::slotCbTextAlignV_currentIndexChanged(int /*index*/)
{
  refreshScreens();
}

void ProjectorWidget::slotCbTextOutline_currentIndexChanged(int index)
{
  if (index == 0)
  {
    textOutline = 0;
    textShadow = 0;
  }
  else if (index > 2)
  {
    textOutline = 0;
    textShadow = index - 2;
  }
  else
  {
    textOutline = index;
    textShadow = 0;
  }
  refreshScreens();
}

void ProjectorWidget::slotChbTextOutlineColor_clicked()
{
  QColor color = QColorDialog::getColor(textOutlineColor, this);
  if (color.isValid())
  {
    textOutlineColor = color;
    QPixmap pmColor(16, 16);
    pmColor.fill(textOutlineColor);
    btnTextOutlineColor->setIcon(pmColor);
    refreshScreens();
  }
}

void ProjectorWidget::slotCbTitleBarPosition_currentIndexChanged(int index)
{
  if (index == 0) // Left
  {
    textArea.setX(20 + titlePanelHeight);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (index == 2) // Right
  {
    textArea.setX(20);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20 - titlePanelHeight); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (index == 1) // Top
  {
    textArea.setX(20);
    textArea.setY(15 + titlePanelHeight);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  else if (index == 3) // Bottom
  {
    textArea.setX(20);
    textArea.setY(15);
    textArea.setWidth(projectorScreenWidth - textArea.x() - 20); // Това е максималната дължина на един ред. По нея ще се определя колко думи да влязат в един ред.
    textArea.setHeight(projectorScreenHeight - textArea.y() - 15 - titlePanelHeight); // Това е височината на целия текст. По нея ще се пресмята разстоянието между редовете, така че да се съберат всички.
  }
  refreshScreens();
}

void ProjectorWidget::slotCbTitleBarAlpha_currentIndexChanged(int /*index*/)
{
  refreshScreens();
}

void ProjectorWidget::slotCbWallpaperPosition_currentIndexChanged(int index)
{
  if (customWallpaperPreviewScreen.isNull()) return; // Това е важно при първоначално инициализиране на комбобокса.

  QPixmap pmWallpaper(wallpaperFile);
  
  if (!pmWallpaper.isNull()) // Ако е картинка.
  {
    if (index == 0) // Fit
    {
      customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
    }
    else if (index == 1) // Fit Expanding
    {
      customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
      customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
    }
    else if (index == 2) // Stretch
    {
      customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
    }
    else if (index == 3) // Center
    {
      int width = (int)( (double)previewScreenWidth / (double)projectorScreenWidth * (double)pmWallpaper.width() );
      customWallpaperPreviewScreen =  pmWallpaper.scaledToWidth(width, Qt::FastTransformation); // Qt::SmoothTransformation
      customWallpaperProjectorScreen = pmWallpaper;
    }

    if (cbWallpaper->currentIndex() == 1) // Custom Wallpaper.
    {
      currentWallpaperProjectorScreen = customWallpaperProjectorScreen;
      currentWallpaperPreviewScreen = customWallpaperPreviewScreen;
      projectorWindow->lblProjectorBackground->setPixmap(currentWallpaperProjectorScreen);
      lblPreviewBackground->setPixmap(currentWallpaperPreviewScreen);
      refreshScreens();
    }
  }
}

void ProjectorWidget::slotCbWallpaper_currentIndexChanged(int index)
{
  if (index == 0) // Embedded Wallpaper.
  {
    currentWallpaperProjectorScreen = embeddedWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = embeddedWallpaperPreviewScreen;
    cbWallpaperPosition->setEnabled(false);
    btnWallpaperEmbedded->setVisible(true);
    btnWallpaperCustom->setVisible(false);
    btnWallpaperColor->setVisible(false);

    circleWidgetPreview->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetProjector->setCircleBrightness(embeddedWallpaperCircleBrightness);
    circleWidgetPreview->enableCircles(true);
    circleWidgetProjector->enableCircles(true);
  }
  else if (index == 1) // Custom Wallpaper.
  {
    currentWallpaperProjectorScreen = customWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = customWallpaperPreviewScreen;
    cbWallpaperPosition->setEnabled(true);
    btnWallpaperEmbedded->setVisible(false);
    btnWallpaperCustom->setVisible(true);
    btnWallpaperColor->setVisible(false);

    circleWidgetPreview->enableCircles(false);
    circleWidgetProjector->enableCircles(false);
  }
  else if (index == 2) // Color.
  {
    currentWallpaperProjectorScreen = colorWallpaperProjectorScreen;
    currentWallpaperPreviewScreen = colorWallpaperPreviewScreen;
    cbWallpaperPosition->setEnabled(false);
    btnWallpaperEmbedded->setVisible(false);
    btnWallpaperCustom->setVisible(false);
    btnWallpaperColor->setVisible(true);

    circleWidgetPreview->enableCircles(false);
    circleWidgetProjector->enableCircles(false);
  }

  projectorWindow->lblProjectorBackground->setPixmap(currentWallpaperProjectorScreen);
  lblPreviewBackground->setPixmap(currentWallpaperPreviewScreen);
  refreshScreens();
}

void ProjectorWidget::slotBtnWallpaperEmbedded_clicked()
{
  embeddedWallpaperCircleBrightness += 10;
  if (embeddedWallpaperCircleBrightness > 120) embeddedWallpaperCircleBrightness = 20;
  btnWallpaperEmbedded->setText(QString("%1").arg(embeddedWallpaperCircleBrightness));
  
  circleWidgetPreview->setCircleBrightness(embeddedWallpaperCircleBrightness);
  circleWidgetProjector->setCircleBrightness(embeddedWallpaperCircleBrightness);
}

void ProjectorWidget::slotBtnWallpaperCustom_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, QString("Wallpaper"), wallpapersPath, QString("Wallpaper (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm *.tiff *.mng *.svg *.tga);;All Files (*.*)"));
  if (!fileName.isEmpty())
  {
    QPixmap pmWallpaper(fileName);
    
    if (!pmWallpaper.isNull()) // Ако е картинка.
    {
      wallpapersPath = QFileInfo(fileName).absolutePath(); // Запомня текущата директория.
      wallpaperFile = fileName; // Запомня файла.

      // Преоразмерява картинката, за да е готова за употреба.
      if (cbWallpaperPosition->currentIndex() == 0) // Fit
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 1) // Fit Expanding
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::KeepAspectRatioByExpanding, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 2) // Stretch
      {
        customWallpaperPreviewScreen = pmWallpaper.scaled(previewScreenWidth, previewScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper.scaled(projectorScreenWidth, projectorScreenHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation); // Qt::SmoothTransformation
      }
      else if (cbWallpaperPosition->currentIndex() == 3) // Center
      {
        int width = (int)( (double)previewScreenWidth / (double)projectorScreenWidth * (double)pmWallpaper.width() );
        customWallpaperPreviewScreen =  pmWallpaper.scaledToWidth(width, Qt::FastTransformation); // Qt::SmoothTransformation
        customWallpaperProjectorScreen = pmWallpaper;
      }
      btnWallpaperCustom->setIcon(pmWallpaper.scaled(16, 16));

      //if (cbWallpaper->currentIndex() == 1)
      //{
        slotCbWallpaper_currentIndexChanged(1);
      //}
    }
    else
    {
      QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->FileReadError_v1); // или MW->MO->TS->Error
    }
  }
}

void ProjectorWidget::slotBtnWallpaperColor_clicked()
{
  QColor color = QColorDialog::getColor(wallpaperColor, this);
  if (color.isValid())
  {
    wallpaperColor = color;

    QPixmap pmcolorPj(projectorScreenWidth, projectorScreenHeight);
    QPixmap pmcolorPv(previewScreenWidth, previewScreenHeight);
    pmcolorPj.fill(wallpaperColor);
    pmcolorPv.fill(wallpaperColor);
    colorWallpaperProjectorScreen = pmcolorPj;
    colorWallpaperPreviewScreen = pmcolorPv;

    QPixmap pmColor(16, 16);
    pmColor.fill(wallpaperColor);
    btnWallpaperColor->setIcon(pmColor);

    //if (cbWallpaper->currentIndex() == 2)
    //{
      slotCbWallpaper_currentIndexChanged(2);
    //}
  }
}

void ProjectorWidget::slotBtnSaveAsPic_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString("current_screen.png"), QString("Images (*.png *.jpg *.jpeg *.gif *.bmp);;All files (*.*)"));
  if (fileName.isEmpty()) return;
  
  QPixmap pixmap(projectorWindow->lblProjectorBackground->pixmap()->size());
  pixmap.fill(0,0,0); // Това се налага в случай, че в картинката за фон има прозрачни части (както е във вградената картинка).
  QPainter painter(&pixmap);
  painter.drawPixmap(0, 0, *projectorWindow->lblProjectorBackground->pixmap()); // Фона.
  if (!chbHideText->isChecked()) painter.drawPixmap(0, 0, *projectorWindow->lblProjectorText->pixmap()); // Текста.

  if(!pixmap.save(fileName, 0, 100)) // Може да се напише "PNG" вместо 0, но тогава винаги ще се записва в PNG формат, дори ако потребителят е избрал друго разширение (така например файлът ще е current_screen.jpg, но реално ще е PNG файл). Ако не се напише разширение, се записва като PNG.
  {
    QMessageBox::warning(this, QString("Save File"), QString("Save File Error!"));
  }
}

void ProjectorWidget::slotLwHistory_itemClicked(QListWidgetItem */*item*/)
{
  if (lwHistory->count() == historyMap.size()) // Излишна проверка, но да има...
  {
    // Трябва да се върне стойността по индекс, но няма метод в QMap, който да връща стойност по индекс и се налага по този тъп начин:
    int index = -1;
    QMapIterator<quint16, PROJECTOR_HISTORY> iterator(historyMap);
    while (iterator.hasNext())
    {
      iterator.next();
      index++;
      if (index == lwHistory->currentRow())
      {
        PROJECTOR_HISTORY ph = iterator.value();
        setScreenText(ph.bibleText, ph.chapter, ph.verse, MAX_VERSES, ph.nativeFontFamily); // Тук не се използва ph.absIndex, а MAX_VERSES, за да укаже, че стихът идва от историята, а не от рекущия раздел.
        MW->showBookmark(ph.absIndex); // Показва стиха в текущия раздел.
        break;
      }
    }
  }
}

void ProjectorWidget::slotSetPrevSize()
{
  if (isinitProjectorToolBar) resizeGeometry();
}

void ProjectorWidget::slotSetProjectorFontSize()
{
  QFont font = this->font();
  font.setPointSize(MW->MO->SVars.projectorToolBarFontSize);
  this->setFont(font);
}

// ==========================================================================================================================================================


ProjectorWindow::ProjectorWindow(QWidget *parent) : QWidget(parent)
{
  setWindowTitle(QString("Projector screen - %1").arg(QCoreApplication::applicationName())); // Важно е заглавието на този прозорец да е различно от това на основния прозорец, за да може този прозорец да се избира за вграждане в софтуер за видеозапис.
  setWindowFlags(Qt::FramelessWindowHint);//Qt::SplashScreen
  setGeometry(QRect(0, 0, 256, 144));
  projectorMaximized = false;

  lblProjectorBlack = new QLabel(this);
  QPalette palette;
  QBrush brush(QColor(0, 0, 0));
  brush.setStyle(Qt::SolidPattern);
  palette.setBrush(QPalette::Window, brush);
  palette.setBrush(QPalette::Button, brush);
  palette.setBrush(QPalette::Base, brush);
  lblProjectorBlack->setAutoFillBackground(true);
  lblProjectorBlack->setPalette(palette);

  lblProjectorBackground = new QLabel(this);
  lblProjectorBackground->setAlignment(Qt::AlignCenter);
  lblProjectorText = new QLabel(this);
}

ProjectorWindow::~ProjectorWindow()
{
  delete lblProjectorBackground;
  delete lblProjectorText;
}

void ProjectorWindow::showEvent(QShowEvent *event)
{
  QWidget::showEvent(event);

  // Този слот се извиква многократно и затова се прави така, че сигналът за
  // максимизиране да се изпрати само веднъж - при първото извикване на този слот.
  if (!projectorMaximized)
  {
    if (isMaximized() || isFullScreen()) // Ако формата е максимизирана.
    {
      if (height() > 500) // Ако размерът ѝ е по-голям от начално заложения (тази проверка е заради Линукс).
      {
        projectorMaximized = true;
        emit projectorWindowMaximized(); // Излъчва сигнал, който ще се прихване от главната форма.
        QTimer::singleShot(200, this, SLOT(slotHideWindow()));
      }
    }
  }
}

void ProjectorWindow::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);

  // Този слот се извиква няколко пъти, особено в Линукс и затова се прави така, че сигналът за
  // максимизиране да се изпрати само веднъж.
  if (!projectorMaximized)
  {
    if (isMaximized() || isFullScreen()) // Ако формата е максимизирана.
    {
      if (height() > 500) // Ако размерът ѝ е по-голям от начално заложения (тази проверка е заради Линукс).
      {
        projectorMaximized = true;
        emit projectorWindowMaximized(); // Излъчва сигнал, който ще се прихване от главната форма.
        QTimer::singleShot(200, this, SLOT(slotHideWindow()));
      }
    }
  }
}

void ProjectorWindow::slotHideWindow()
{
  // Това е някакво безумие, но не можах да реша този проблем (в Windows)...
  // След излъчване на горния сигнал, този прозорец се скрива, но поради някаква причина не се скрива, а става невидим, но си е там
  // и е над другите прозорци и практически блокира достъпа до компютъра. Ето защо се принудих да използвам таймер, който след 200 ms
  // извиква този слот, където прозорецът се скрива реално. Тъй като извикването на setVisible(false) няма ефект, защото официално
  // прозорецът се води скрит, се налага първо да се извика setVisible(true), което да покаже прозореца. Безумие...

  setVisible(true);  // Показва прозореца за проектора.
  setVisible(false); // Скрива прозореца за проектора.
}


// ==========================================================================================================================================================

CircleWidget::CircleWidget(QWidget *parent) : QLabel(parent)
{
  circleBrightness = 40;
  maxDiameter = width() * 2;
  for (int i = 0; i < CIRCLE_COUNT; i++)
  {
    circles[i].X = randomInt(-width(), width());
    circles[i].Y = randomInt(-width(), width());
    circles[i].diameter = (double)randomInt(0, (int)maxDiameter);
  }
  
  QPalette pal = palette();
  pal.setBrush(QPalette::Base, QColor(0, 0, 0)); // 000000 // 191, 142, 74 (bf8e4a), ако се използва оранжевият фон.
  pal.setBrush(QPalette::Window, QColor(0, 0, 0)); // 000000 // 191, 142, 74 (bf8e4a), ако се използва оранжевият фон.
  setPalette(pal);
  setAutoFillBackground(true);

  setBackgroundRole(QPalette::Base);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(nextStep()));
}

int CircleWidget::randomInt(int from, int to)
{
  //qrand() returns a value between 0 and RAND_MAX.
  int interval = to - from;
  double randIntD = (double)qrand() / (double)RAND_MAX * (double)interval;
  int randInt = (int)randIntD + from;
  if (randInt < from) randInt = from;
  if (randInt > to) randInt = to;
  return randInt;
}

void CircleWidget::enableCircles(bool enable)
{
  if (enable)
  {
    maxDiameter = width() * 2;
    for (int i = 0; i < CIRCLE_COUNT; i++)
    {
      circles[i].X = randomInt(-width(), width());
      circles[i].Y = randomInt(-width(), width());
      circles[i].diameter = (double)randomInt(0, (int)maxDiameter);
    }

    timer->start(70);
    setVisible(true);
  }
  else
  {
    timer->stop();
    setVisible(false);
  }
}

void CircleWidget::setCircleBrightness(int circleBrightness)
{
  if (circleBrightness > 0 && this->circleBrightness <= 255) this->circleBrightness = circleBrightness;
}

void CircleWidget::nextStep()
{
  maxDiameter = width() * 2;
  for (int i = 0; i < CIRCLE_COUNT; i++)
  {
    circles[i].diameter += (width() > 600) ? 5.0 : 2.0;
    if (circles[i].diameter > maxDiameter)
    {
      circles[i].X = randomInt(-width(), width());
      circles[i].Y = randomInt(-width(), width());
      circles[i].diameter = 1.0; // Не трябва да е 0!
    }
  }
  update();
}

void CircleWidget::resizeEvent(QResizeEvent *event)
{
  QLabel::resizeEvent(event);

  // Този метод е нужен при преоразмеряването на панела.
  maxDiameter = width() * 2;
  for (int i = 0; i < CIRCLE_COUNT; i++)
  {
    circles[i].X = randomInt(-width(), width());
    circles[i].Y = randomInt(-width(), width());
    circles[i].diameter = (double)randomInt(0, (int)maxDiameter);
  }
}

void CircleWidget::paintEvent(QPaintEvent */*event*/)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, false); // Това (true) заглажда кръговете, но в случая няма значение дали са груби, защото са на заден план.
  painter.translate(width() / 2, height() / 2); // Това премества началото на координатната система в средата на екрана.

  for (int i = 0; i < CIRCLE_COUNT; i++)
  {
    double radius = circles[i].diameter / 2.0;
    double w = width() / 5;

    double delta1 = circles[i].diameter / w;   if (delta1 > 1) delta1 = 1; // Тази делта ще направи невидимо (избледнено) създаването на кръга (защото рязкото появяване на нов кръг, макар и да започва с размер нула, е някак дразнещо).
    double delta2 = circles[i].diameter / maxDiameter; // Тази делта ще направи невидимо (избледнено) изчезването на кръга (защото изчезване на кръга, е дразнещо).

    int alpha = 255.0
              - (255.0 - delta1 * 255.0) // Това причинява избледняване на кръга в началото. Става постепенно.
              - (delta2 * delta2 * delta2 * delta2 * 255.0); // Това причинява избледняване на кръга в края. По този начин кръгът избледнява в последния момент (заради повдигането на 4-та степен), а не плавно.

    if (alpha > 0 && alpha < 256)
    {
      //painter.setPen(QPen(QColor(20, 20, 20, alpha), (radius > w) ? w : radius)); // Едноцветно. // 141414 // 207, 159, 90 (cf9f5a), ако се използва оранжевия фон.
      painter.setPen(QPen(QColor::fromHsl((int)((double)alpha*1.407), 128, circleBrightness, alpha), (radius > w) ? w : radius)); // Цветно. H съставката (hue - цвят, нюанс) сменя всички цветове (приема стойности от 0 до 359, затова alpha, която тук се използва не по предназначение, се умножава по 1.407 - 255*1.407=358). S съставката (saturation) определя наситеността на цветовете (255 - най-ярки, 128 - пастелени). L съставката (lightness) е яркостта (circleBrightness=40 - бледи цветове).
      painter.drawEllipse(QRectF(-radius + circles[i].X, -radius + circles[i].Y, circles[i].diameter, circles[i].diameter)); // По този начин кръговете се разширяват.
    }
  }
}

// ==========================================================================================================================================================

ProjectorToolBar::ProjectorToolBar(MainWindow *mainWindow, ProjectorWidget *projectorWidget, QWidget *parent) : MDock(parent)
{
  this->MW = mainWindow;
  this->projectorWidget = projectorWidget;

  setDockWidgetTabbedTitleBar(true);
  setProperties(false, false, true, false);
  setDockGridState("0^100_1_0^100"); // Един ред с един раздел.
  setMinimumSize(1, 1); // Не трябва да е 0, защото няма ефект.

  mDockWidget = new MDockWidget(this, QString("<b>%1</b>").arg(MW->MO->TS->Projector_v1), false, false, MW->MO->SVars.docks3DTitleBar, 1, 0);
  mDockWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mDockWidget->setWidget(projectorWidget);
  mDockWidget->setDockWidgetDisallowCloseFromButton(true); // Забранява на раздела да се затваря от Close бутона му, който ще излъчва само сигнал.
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
  mDockWidget->setCloseBtnToolTip(MW->MO->TS->HideToolBar_v1);
  connect(mDockWidget, SIGNAL(dockWidgetCloseButtonPressed(MDock *, MDockWidget *, int, quint8)), this, SLOT(slotCloseDock(MDock *, MDockWidget *, int, quint8))); // Излъчения от Close бутона сигнал.

  addDockWidget(mDockWidget, 0, 0);


  QFont currfont = this->font();
  currfont.setPointSize(MW->MO->SVars.projectorToolBarFontSize);
  this->setFont(currfont);
  
  slotSetColors();
}

ProjectorToolBar::~ProjectorToolBar()
{
  delete mDockWidget;
}

void ProjectorToolBar::slotCloseDock(MDock */*dock*/, MDockWidget */*dockWidget*/, int /*dockWidgetID*/, quint8 /*dockWidgetType*/)
{
  //setVisible(false); // Това ще скрие (затвори) панела, но бутонът в TMenu няма да се отпусне.
  MW->mainToolBar->btnOther_Projector->click(); // Това косвено ще извика setVisible(false).
}

void ProjectorToolBar::slotSetTitleBarFontSize()
{
  mDockWidget->setDockWidgetTitleBarFontSize(MW->MO->SVars.otherToolBarFontSize);
}

void ProjectorToolBar::slotSetColors()
{
  setDockBgColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetBgColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarColor(MW->MO->SVars.appColorF);
  mDockWidget->setDockWidgetTitleBarTextColor(MW->MO->SVars.appColorB);
  mDockWidget->setDockWidgetTitleBarButtonColor(MW->MO->SVars.appColorB);
}

void ProjectorToolBar::slotSet3DTitleBar()
{
  mDockWidget->setDockWidget3DTitleBar(MW->MO->SVars.docks3DTitleBar);
}

void ProjectorToolBar::resetMinimumWidth()
{
  int left; int top; int right; int bottom;
  projectorWidget->layout()->getContentsMargins(&left, &top, &right, &bottom);
  setMinimumWidth(MW->MO->SVars.projectorToolBarPrevSize + left + right + getDockMargins().left() + getDockMargins().right());
  setMaximumWidth(minimumWidth());
}
