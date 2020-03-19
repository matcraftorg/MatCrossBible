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

#ifndef TMENU_H
#define TMENU_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QKeySequence>

#include "icons.h"
#include "trstrings.h"

class MainToolBar;

class TMenu : public QWidget
{
Q_OBJECT

private:
  QWidget *panelTMenu;      // Указател към съдържанието на контейнера (в случая указател към обект на MainToolBar).
  QWidget *panelAudio;      // Указател към съдържанието на контейнера (в случая указател към обект на AudioToolBar).
  QWidget *panelBibleTexts; // Указател към съдържанието на контейнера (в случая указател към панела с бутоните за избор на текстове).
  QWidget *panelSession;    // Указател към съдържанието на контейнера (в случая указател към панела с бутоните за избор на сесия).
  
  QWidget *panelTMenuCont;      // Контейнер.
  QWidget *panelAudioCont;      // Контейнер.
  QWidget *panelBibleTextsCont; // Контейнер.
  QWidget *panelSessionCont;    // Контейнер.
  
  QWidget *panelTMenuNav;       // Панел за навигация (за преместване на съдържанието на контейнера).
  QWidget *panelAudioNav;       // Панел за навигация (за преместване на съдържанието на контейнера).
  QWidget *panelBibleTextsNav;  // Панел за навигация (за преместване на съдържанието на контейнера).
  QWidget *panelSessionNav;     // Панел за навигация (за преместване на съдържанието на контейнера).
  
  QToolButton *btnPanelTMenuNavL;
  QToolButton *btnPanelTMenuNavR;
  
  QToolButton *btnPanelAudioNavL;
  QToolButton *btnPanelAudioNavR;
  
  QToolButton *btnPanelBibleTextsNavL;
  QToolButton *btnPanelBibleTextsNavR;
  
  QToolButton *btnPanelSessionNavL;
  QToolButton *btnPanelSessionNavR;
  
  bool leftToRightDirection;
  bool show3DTitleBar;

  void resizeEvent(QResizeEvent *event);
  void wheelEvent(QWheelEvent *event);
  void paintEvent(QPaintEvent *event);

public:
  TMenu(QWidget *panelTMenu, QWidget *panelAudio, QWidget *panelBibleTexts, QWidget *panelSession, QColor appColorF, QColor appColorB, bool positionTop = true, QWidget *parent = 0);
  ~TMenu();
  void setAudioToolBarVisible(bool visible);
  void setBibleTextsToolBarVisible(bool visible);
  void setSessionToolBarVisible(bool visible);
  void setColors(QColor appColorF, QColor appColorB);
  void set3DTitleBar(bool show3DTitleBar);
  void setToolBarsHeight(int height); // Сетва височината на тулбаровете. Този метод се извиква при смяна на размера на шрифта на тулбаровете.

public slots:
  void slotBtnPanelTMenuNavL_Clicked();
  void slotBtnPanelTMenuNavR_Clicked();
  void slotBtnPanelAudioNavL_Clicked();
  void slotBtnPanelAudioNavR_Clicked();
  void slotBtnPanelBibleTextsNavL_Clicked();
  void slotBtnPanelBibleTextsNavR_Clicked();
  void slotBtnPanelSessionNavL_Clicked();
  void slotBtnPanelSessionNavR_Clicked();
};

// -----------------------------------------------------------------------------------------------------------------------------------

class MainToolBar : public QWidget
{
Q_OBJECT
  // UTF-8 енкодинг.

private:
  TrStrings *TS;
  int shift; // X координата на следващия бутон.
  QPalette lineEdit_SearchInText_PaletteYellow; // За lineEdit_SearchInText: Жълт фон, черен цвят на буквите.
  QPalette lineEdit_SearchInText_PaletteAlpha;   // За lineEdit_SearchInText: Сив фон, цвят на буквите като на иконите.
  bool leftToRightDirection;

  void createNavigationToolBar();
  void createTextToolBar();
  void createOtherToolBar();
  void createHelpToolBar();
  void createFileToolBar();
  QString composeToolTip(QString toolTip, QString key = "", QKeySequence::StandardKey standardKey = QKeySequence::UnknownKey); // Връща toolTip + клавишната комбинация.
  QKeySequence composeShortcut(QKeySequence key, QKeySequence::StandardKey standardKey = QKeySequence::UnknownKey); // Връща key, ако за тази платформа няма стандартна клавишна комбинация standardKey.

public:
  int btnsIconSize; // Големина на иконите на бутоните от тул-бара.
  int btnsHeightSize; // Височина на бутоните от тул-бара.
  ///NavigationToolBar
  QToolButton *btnNavigation_New;
  QToolButton *btnNavigation_Books;
  QToolButton *btnNavigation_Bookmarks;
  QToolButton *btnNavigation_GoBack;
  QToolButton *btnNavigation_GoForward;
  QLabel *labelBook;
  QLabel *labelChapter;
  QLabel *labelVerse;
  QLabel *dailyReadGrLabel;
  QLabel *dailyReadChLabel;
  QToolButton *btnNavigation_PreviousBook;
  QToolButton *btnNavigation_NextBook;
  QToolButton *btnNavigation_PreviousChapter;
  QToolButton *btnNavigation_NextChapter;
  QToolButton *btnNavigation_PreviousVerse;
  QToolButton *btnNavigation_NextVerse;
  QToolButton *btnNavigation_PreviousChaptersDailyRead;
  QToolButton *btnNavigation_NextChaptersDailyRead;
  QToolButton *btnNavigation_PreviousChapterDailyRead;
  QToolButton *btnNavigation_NextChapterDailyRead;
  QToolButton *btnNavigation_DailyRead;
  ///TextToolBar
  QToolButton *btnText_Search;
  QToolButton *btnText_BibleTexts;
  QToolButton *btnText_Audio;
  QToolButton *btnText_ZoomIn;
  QToolButton *btnText_ZoomOut;
  QToolButton *btnText_ZoomNormal;
  QLineEdit   *lineEdit_SearchInText;
  bool         lineEdit_SearchInText_IsInactive; // Флаг, указващ дали полето е неактивно.
  QToolButton *btnText_SearchInTextPrevious;
  QToolButton *btnText_SearchInTextCaseSensitive;
  QToolButton *btnText_SearchInTextWholeWords;
  QToolButton *btnText_SearchInTextNext;
  QToolButton *btnText_Statistics;
  ///OtherToolBar
  QToolButton *btnOther_Pad;
  QToolButton *btnOther_Dictionary;
  QToolButton *btnOther_ExternalImages;
  QToolButton *btnOther_WWW;
  QToolButton *btnOther_Projector;
  QToolButton *btnOther_Settings;
  ///HelpToolBar
  QToolButton *btnHelp_Help;
  QToolButton *btnHelp_AboutMatCrossBible;
  ///FileToolBar
  QToolButton *btnFile_FileMenu;
  QToolButton *btnFile_Session;
  //QToolButton *btnFile_Close;
  QToolButton *btnFile_Exit;

  MainToolBar(TrStrings *trStrings, int buttonsIconSize, QColor tMenuColorB, QColor iconColor, QWidget *parent = 0);
  ~MainToolBar();
  void setIconsColor(QColor tMenuColorB, QColor iconColor);
  void showDailyReadPanel(bool show);
  void showAlphaPalette_LineEdit_SearchInText(bool show);
};

#endif // TMENU_H
