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

#ifndef PROJECTORTOOLBAR_H
#define PROJECTORTOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QComboBox>
#include <QCheckBox>
#include <QComboBox>
#include <QFontComboBox>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "datatypes.h"
#include "utility.h"
#include "mainwindow.h"

class ProjectorWindow;
class CircleWidget;

class ProjectorWidget : public QWidget
{
Q_OBJECT

private:
  MainWindow *MW;
  int     projectorScreenXAuto;             // Отместване по X, където трябва да се покаже екранът на проектора, когато местоположението му се определя автоматично.
  int     projectorScreenX;                 // Отместване по X, където трябва да се покаже екранът на проектора, когато местоположението му се определя ръчно.
  int     projectorScreenY;                 // Отместване по Y, където трябва да се покаже екранът на проектора, когато местоположението му се определя ръчно.
  int     projectorScreenWidth;             // Широчина на екрана на проектора, когато местоположението му се определя ръчно.
  int     projectorScreenHeight;            // Височина на екрана на проектора, когато местоположението му се определя ръчно.
  int     previewScreenWidth;               // Широчина на малкия екран. Изчислява се автоматично.
  int     previewScreenHeight;              // Височина на малкия екран. Изчислява се автоматично.
  int     titlePanelHeight;                 // Широчина/височина на заглавния панел.
  QPixmap embeddedWallpaperPreviewScreen;   // Вграден фон за малкия екран.
  QPixmap embeddedWallpaperProjectorScreen; // Вграден фон за проектора.
  QPixmap customWallpaperPreviewScreen;     // Външно изображение за фон за малкия екран.
  QPixmap customWallpaperProjectorScreen;   // Външно изображение за фон за проектора.
  QPixmap colorWallpaperPreviewScreen;      // Цвят на фон за малкия екран.
  QPixmap colorWallpaperProjectorScreen;    // Цвят на фон за проектора.
  QPixmap currentWallpaperPreviewScreen;    // Текущ фон за малкия екран (един от горните, според състоянието на радио-бутоните).
  QPixmap currentWallpaperProjectorScreen;  // Текущ фон за проектора (един от горните, според състоянието на радио-бутоните).
  QRect   textArea;    // Достъпната площ, върху която ще се изписва текстът (X, Y, Width, Height).
  QFont   textFont;    // Шрифтът на текста показан на екрана (FontFamily, PointSize, Bold, Italic).
  QFont   cTextFont;   // Преизчислен шрифта (textFont) на текста показан на екрана, така че да се събира целият текст (PointSize се изчислява автоматично и е по-малък или равен на зададения с цел да се покаже целият текст).
  int     lineSpacing; // Разстояние между редовете (по-точно от началото на единия ред до началото на другия).
  int     textHeight;  // Височина на текста, когато е събран целият на екрана.
  bool    textUpper;   // Дали е с главни букви текстът показан на екрана.
  QColor  textColor;   // Цвят на шрифта. Контурът на текста е винаги черен и не се помни тук.
  int     textOutline; // Дебелина на контура на текста в пиксели (от 0 до 2).
  int     textShadow;  // Отместване на сянката на текста в пиксели (от 0 до 5). Сянка може да има само когато контурът е 0.
  QColor  textOutlineColor; // Цвят на контура на текста.
  QColor  wallpaperColor;   // Цвят на фона, когато е избрано "Цвят".
  QString wallpaperFile;    // Име на файла на външното изображение за фон. Ако е празен се използва черен цвят вместо картинка.
  QString wallpapersPath;   // Път до последно отворената директория за изображение.
  QString bibleText;   // Името на текста, който се показва в момента.
  QString chapter;     // Книгата + главата, която се показва в момента.
  QString verse;       // Стихът, който се показва в момента.
  QString nativeFontFamily; // Собствен шрифт на стиха (в случай, че не се използва шрифта от комбобокса на проектора).
  int     embeddedWallpaperCircleBrightness; // Яркостта на кръговете на Embedded Wallpaper.
  QMap<quint16, PROJECTOR_HISTORY> historyMap; // Сортиран списък (по абсолютен номер на стих) с историята на проектора.

  CircleWidget *circleWidgetPreview;
  CircleWidget *circleWidgetProjector;
  // Projector Screen
  ProjectorWindow *projectorWindow;
  // Preview Screen
  QWidget *previewWindow;
  QLabel *lblPreviewBlack;
  QLabel *lblPreviewBackground;
  QLabel *lblPreviewText;
  // Control
  QFrame *frameControl;
  QPushButton *btnProjector;
  QToolButton *btnHideText;
  QCheckBox *chbHideText;
  QCheckBox *chbDisable;
  QCheckBox *chbHideName;
  // Text
  QFrame *frameText;
  QPushButton *btnTextZoomIn;
  QPushButton *btnTextZoomOut;
  QPushButton *btnTextBold;
  QPushButton *btnTextItalic;
  QPushButton *btnTextUpper;
  QPushButton *btnTextColor;
  QLabel *lblFontPointSize;
  QFontComboBox *cbFont;
  QPushButton *btnFontMan;
  QComboBox *cbTextAlignH;
  QComboBox *cbTextAlignV;
  QComboBox *cbTextOutline;
  QPushButton *btnTextOutlineColor;
  QComboBox *cbTitleBarPosition;
  QComboBox *cbTitleBarAlpha;
  // Background
  //QFrame *frameBackground;
  QComboBox *cbWallpaperPosition;
  QComboBox *cbWallpaper;
  QPushButton *btnWallpaperEmbedded;
  QPushButton *btnWallpaperCustom;
  QPushButton *btnWallpaperColor;
  // Other
  QPushButton *btnSaveAsPic;
  // History
  QListWidget *lwHistory;

  void refreshScreens();

public:
  bool isinitProjectorToolBar; // Флаг указващ, че тулбара е инициализиран т.е. отворен/създаден. По този флаг се решава дали да се запомнят настройките при затваряне на програмата.

  ProjectorWidget(MainWindow *MW);
  ~ProjectorWidget();
  void initProjectorToolBar(); // Извиква се само веднъж - за първоначално създаване на съдържанието на тулбара. Така, самият тулбар се създава при пускане на програмата, но съдържанието му при първо показване на тулбара.
  void loadSettings();
  void saveSettings();
  void resizeGeometry();
  void splitText(QFont font, QString text, QStringList *textLines);
  void setScreenText(QString bibleText, QString chapter, QString verse, quint16 absIndex, QString nativeFontFamily);

private slots:
  void slotBtnProjector_clicked();
  void slotBtnHideText_clicked();
  void slotChbHideText_clicked();
  void slotChbHideName_clicked();
  void slotBtnTextSizeIn_clicked();
  void slotBtnTextSizeOut_clicked();
  void slotBtnTextBold_clicked();
  void slotBtnTextItalic_clicked();
  void slotBtnTextUpper_clicked();
  void slotBtnTextColor_clicked();
  void slotCbFont_currentFontChanged(const QFont &font);
  void slotBtnFontMan_clicked();
  void slotCbTextAlignH_currentIndexChanged(int index);
  void slotCbTextAlignV_currentIndexChanged(int index);
  void slotCbTextOutline_currentIndexChanged(int index);
  void slotChbTextOutlineColor_clicked();
  void slotCbTitleBarPosition_currentIndexChanged(int index);
  void slotCbTitleBarAlpha_currentIndexChanged(int index);
  void slotCbWallpaperPosition_currentIndexChanged(int index);
  void slotCbWallpaper_currentIndexChanged(int index);
  void slotBtnWallpaperEmbedded_clicked();
  void slotBtnWallpaperCustom_clicked();
  void slotBtnWallpaperColor_clicked();
  void slotBtnSaveAsPic_clicked();
  void slotLwHistory_itemClicked(QListWidgetItem *item);
  void slotProjectorWindowMaximized();

public slots:
  void slotSetPrevSize();
  void slotSetProjectorFontSize();
};

// ==========================================================================================================================================================


class ProjectorWindow : public QWidget
{
Q_OBJECT

private:
  bool projectorMaximized; // Флаг, чрез който ивентът за максимизиране се извиква само веднъж. Използва се заради Убунту Линукс.

public:
  QLabel *lblProjectorBlack;
  QLabel *lblProjectorBackground;
  QLabel *lblProjectorText;
  ProjectorWindow(QWidget *parent = 0);
  ~ProjectorWindow();

protected:
  void showEvent(QShowEvent *event); // Този ивент се използва за предварително премащабиране на картинките за формата за проектора. Заради Windows.
  void resizeEvent(QResizeEvent *event); // Този ивент се използва за предварително премащабиране на картинките за формата за проектора. Заради Linux.

private slots:
  void slotHideWindow();

signals:
  void projectorWindowMaximized();
};

// ==========================================================================================================================================================

#define CIRCLE_COUNT 3

class CircleWidget : public QLabel
{
Q_OBJECT

private:
  struct CIRCLE // Преоразмерени картинки.
  {
    int X;
    int Y;
    double diameter;
  };

  QTimer *timer;
  int circleBrightness; // Яркостта на кръговете.
  double maxDiameter;
  CIRCLE circles[CIRCLE_COUNT];

  int randomInt(int from, int to);

public:
  CircleWidget(QWidget *parent = 0);
  void enableCircles(bool enable); // Чрез този метод ще разрешава или забранява показването на кръговете.
  void setCircleBrightness(int circleBrightness = 0);

private slots:
  void nextStep();

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
};

// ==========================================================================================================================================================

class ProjectorToolBar : public MDock
{
  Q_OBJECT

private:
  MainWindow *MW;
  ProjectorWidget *projectorWidget;
  MDockWidget *mDockWidget;

private slots:
  void slotCloseDock(MDock *dock, MDockWidget *dockWidget, int dockWidgetID, quint8 dockWidgetType); // Скрива панела.

public slots:
  void slotSetTitleBarFontSize(); // Ще сетне размера на текста на заглавната лента.
  void slotSetColors(); // Ще сетне цветовете на фона и на прозорците.
  void slotSet3DTitleBar();

public:
  ProjectorToolBar(MainWindow *mainWindow, ProjectorWidget *projectorWidget, QWidget *parent = 0);
  virtual ~ProjectorToolBar();
  void resetMinimumWidth(); // Преизчислява широчината на панела според размера на обектите в него.
};

#endif // PROJECTORTOOLBAR_H
