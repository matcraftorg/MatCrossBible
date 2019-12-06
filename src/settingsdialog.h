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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtGui>
#include <QDialog>
#include <QPushButton>
#include <QToolButton>
#include <QColorDialog>
#include <QComboBox>
#include <QListWidget>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStyleFactory>

#include "mainwindow.h"
#include "datatypes.h"
#include "httpaccess.h"

class QDialogButtonBox;
class QTabWidget;
class MainObject;
class MainWindow;
class MoreTRFilesWindow;

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  SETTINGS_VARIABLES SVars;

  SettingsDialog(MainWindow *MW);

private:
  MainWindow *MW;
  bool effectAfterRestart; // Флаг, указващ, че ефект от промените ще има след рестартиране на програмата.
  bool effectAfterChange;  // Флаг, указващ, че ефект от промените ще има след действие свързано с конкретната настройка.

  QTabWidget *tabWidget;
  QDialogButtonBox *buttomBox;

private slots:
  void slotAccept();
  void slotReject();
};


// Language
class LanguageTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow  *MW;
  QListWidget *appLanguageListWidget;
  QListWidget *booksLanguageListWidget;

private slots:
  void slotAppLanguage(const QString &language);
  void slotSelectOldLanguage();
  void slotDownloadTRFileFinished();
  void slotBooksLanguage(const QString &language);

public:
  LanguageTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent = 0);
};

// Colors
class ColorsTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow  *MW;
  QToolButton *dock1TextColorFBtn;
  QToolButton *dock1TextColorBBtn;
  QCheckBox   *dock1BGImageCheckBox;
  QToolButton *dock2TextColorFBtn;
  QToolButton *dock2TextColorBBtn;
  QCheckBox   *dock2BGImageCheckBox;
  QToolButton *oldTestamentColorFBtn;
  QSpinBox    *oldTestamentAlphaFSpinBox;
  QToolButton *newTestamentColorFBtn;
  QSpinBox    *newTestamentAlphaFSpinBox;
  QToolButton *textInBracketsColorFBtn;
  QToolButton *JesusWordsColorFBtn;
  QCheckBox   *JesusWordsColorFEnableCheckBox;
  QToolButton *compareEqColorFBtn;
  QToolButton *compareNoEqColorFBtn;
  QToolButton *appColorFBtn;
  QToolButton *appColorBBtn;
  QCheckBox   *docks3DTitleBarCheckBox;
  QPushButton *defaultColorsBtn;

private slots:
  void slotDock1TextColorF();
  void slotDock1TextColorB();
  void slotDock1BGImage_Toggled(const bool checked);
  void slotDock2TextColorF();
  void slotDock2TextColorB();
  void slotDock2BGImage_Toggled(const bool checked);
  void slotOldTestamentColorF();
  void slotOldTestamentAlphaF_valueChanged(int i);
  void slotNewTestamentColorF();
  void slotNewTestamentAlphaF_valueChanged(int i);
  void slotTextInBracketsColorF();
  void slotJesusWordsColorF();
  void slotJesusWordsColorFEnable_Toggled(const bool checked);
  void slotCompareEqColorF();
  void slotCompareNoEqColorF();
  void slotAppColorF();
  void slotAppColorB();
  void slotDocks3DTitleBar_Toggled(const bool checked);
  void slotDefaultColors();

public:
  ColorsTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent = 0);
};

// View
class ViewTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow   *MW;
  QRadioButton *tMenuTopRBtn;
  QRadioButton *tMenuBottomRBtn;
  QComboBox    *toolBarSizeComboBox;
  QComboBox    *tMenuIconSizeComboBox;
  QRadioButton *booksLeftRBtn;
  QRadioButton *booksRightRBtn;
  QComboBox    *booksFontSizeComboBox;
  QRadioButton *searchLeftRBtn;
  QRadioButton *searchRightRBtn;
  QComboBox    *searchToolBarWidthComboBox;
  QComboBox    *searchFontSizeComboBox;
  QRadioButton *projectorLeftRBtn;
  QRadioButton *projectorRightRBtn;
  QComboBox    *projectorPrevSizeComboBox;
  QComboBox    *projectorFontSizeComboBox;
  QComboBox    *guiStyleComboBox;

private slots:
  void slotTMenuTopRBtn_Toggled(const bool checked);
  void slotTMenuBottomRBtn_Toggled(const bool checked);
  void slotToolBarFontSize(const QString size);
  void slotTMenuIconSize(const QString size);
  void slotBooksLeftRBtn_Toggled(const bool checked);
  void slotBooksRightRBtn_Toggled(const bool checked);
  void slotBooksFontSize(const QString size);
  void slotSearchLeftRBtn_Toggled(const bool checked);
  void slotSearchRightRBtn_Toggled(const bool checked);
  void slotSearchToolBarWidth(const QString size);
  void slotSearchFontSize(const QString size);
  void slotProjectorLeftRBtn_Toggled(const bool checked);
  void slotProjectorRightRBtn_Toggled(const bool checked);
  void slotProjectorPrevSize(const QString size);
  void slotProjectorFontSize(const QString size);
  void slotGuiStyle(const QString styleName);

public:
  ViewTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent = 0);
};

// Text
class TextTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow  *MW;
  QComboBox   *globalSizeComboBox;
  QCheckBox   *globalAntialiasCheckBox;
  QFontComboBox *familyComboBox;
  QComboBox   *sizeComboBox;
  QCheckBox   *numberBoldCheckBox;
  QCheckBox   *numberSupCheckBox;
  QPushButton *defaultFontBtn;
  QComboBox   *verseStructComboBox;
  QComboBox   *numerationComboBox;
  QComboBox   *booksOrderComboBox;
  QCheckBox   *showDeutrocanonicalCheckBox;
  QCheckBox   *showAbsVerseNumberCheckBox;

private slots:
  void slotGlobalFontSize(const QString size);
  void slotGlobalAntialias_Toggled(const bool checked);
  void slotFontFamily(const QString family);
  void slotFontSize(const QString size);
  void slotNumberBold_Toggled(const bool checked);
  void slotNumberSup_Toggled(const bool checked);
  void slotDefaultFont();
  void slotVerseStruct(const int index);
  void slotNumeration(const int index);
  void slotBooksOrder(const int index);
  void slotShowDeutrocanonical_Toggled(const bool checked);
  void slotShowAbsVerseNumber_Toggled(const bool checked);

public:
  TextTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent = 0);
};

// Search
class SearchTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow  *MW;
  QCheckBox   *boldCheckBox;
  QCheckBox   *underlineCheckBox;
  QCheckBox   *colorCheckBoxF;
  QCheckBox   *colorCheckBoxB;
  QToolButton *color1FBtn;
  QToolButton *color2FBtn;
  QToolButton *color3FBtn;
  QToolButton *color4FBtn;
  QToolButton *color5FBtn;
  QToolButton *color1BBtn;
  QToolButton *color2BBtn;
  QToolButton *color3BBtn;
  QToolButton *color4BBtn;
  QToolButton *color5BBtn;
  QPushButton *defaultColorsFBtn;
  QPushButton *defaultColorsBBtn;
  QToolButton *extraSelectColor1BBtn;
  QToolButton *extraSelectColor2BBtn;
  QPushButton *defaultExtraSelectColorsBBtn;

private slots:
  void slotBold_Toggled(const bool checked);
  void slotUnderline_Toggled(const bool checked);
  void slotColorF_Toggled(const bool checked);
  void slotColorB_Toggled(const bool checked);
  void slotColor1F();
  void slotColor2F();
  void slotColor3F();
  void slotColor4F();
  void slotColor5F();
  void slotColor1B();
  void slotColor2B();
  void slotColor3B();
  void slotColor4B();
  void slotColor5B();
  void slotDefaultColorsF();
  void slotDefaultColorsB();
  void slotExtraSelectColor1B();
  void slotExtraSelectColor2B();
  void slotDefaultExtraSelectColorsB();

public:
  SearchTab(SETTINGS_VARIABLES *SVars, MainWindow *MW, QWidget *parent = 0);
};

// Other
class OtherTab : public QWidget
{
  Q_OBJECT

private:
  SETTINGS_VARIABLES *SVars;
  MainWindow   *MW;
  QRadioButton *iniHomePathRBtn;
  QRadioButton *iniLocalPathRBtn;
  QRadioButton *iniOtherPathRBtn;
  QPushButton  *openFileManagerHomePathBtn;
  QPushButton  *openFileManagerLocalPathBtn;
  QPushButton  *choiceOtherPathBtn;
  QLineEdit    *otherPathEdit;
  QComboBox    *proxyTypeComboBox;
  QLineEdit    *proxyHostNameEdit;
  QLineEdit    *proxyPortEdit;
  QCheckBox    *trayIconCheckBox;
  QPushButton  *createExampleDctCmtBtn;

private slots:
  void slotIniHomePathRBtn_Toggled(const bool checked);
  void slotIniLocalPathRBtn_Toggled(const bool checked);
  void slotIniOtherPathRBtn_Toggled(const bool checked);
  void slotOpenFileManagerHomePathBtn_clicked();
  void slotOpenFileManagerLocalPathBtn_clicked();
  void slotChoiceOtherPathBtn_clicked();
  void slotProxyType(const int index);
  void slotProxyHostName(const QString proxyHostName);
  void slotProxyPort(const QString proxyPort);
  void slotTrayIcon_Toggled(const bool checked);
  void slotCreateExampleDctCmtBtn_clicked();

public:
  OtherTab(SETTINGS_VARIABLES *SVars, MainWindow *MW ,QWidget *parent = 0);
};
#endif
