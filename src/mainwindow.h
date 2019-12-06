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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QButtonGroup>
#include <QBitArray>
#include <QSystemTrayIcon>

#include "trstrings.h"
#include "datatypes.h"
#include "mainobject.h"
#include "utility.h"
#include "icons.h"
#include "mdock.h"
#include "tmenu.h"
#include "textview.h"
#include "dictionary.h"
#include "searchtoolbar.h"
#include "fastaccesswidget.h"
#include "bookswidget.h"
#include "bookmarkswidget.h"
#include "settingsdialog.h"
#include "extextwindow.h"
#include "eximagewindow.h"
#include "httpaccess.h"
#include "audiotoolbar.h"
#include "projectortoolbar.h"
#include "wwwresources.h"

struct DOCKS;
class QAction;
class QMenu;
class QTextEdit;
class QCheckBox;
class QButtonGroup;
class TrStrings;
class TMenu;
class MainToolBar;
class AudioToolBar;
class MDock;
class MDockWidget;
class MainObject;
class TextView;
class FastAccessWidget;
class BooksWidget;
class BooksToolBar;
class BookmarksWidget;
class BookmarksToolBar;
class SearchToolBar;
class ProjectorWidget;
class ProjectorToolBar;
class SettingsDialog;
class ExTextWindow;
class ExImageWindow;
class HelpSystem;
class NewAppVerWindow;
class MoreBibleTextsWindow;
class WWWResources;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainObject       *MO;
  TMenu            *tMenu;
  MainToolBar      *mainToolBar;
  AudioToolBar     *audioToolBar;
  QWidget          *bibleTextsToolBar;
  QWidget          *sessionToolBar;
  MDock            *mDockMain;
  QList<DOCKS>      HDocks; // Раздели с изгледи на Библията (H-Holy).
  QList<DOCKS>      ODocks; // Раздели с всякакви други изгледи - резултат от търсенето, речници и т.н (O-Other).
  TextView         *currentHolyTextView; // Указател към текущия (активен) изглед показващ текст от Библията (не който е на фокус, а който е текущ).
  TextView         *currentTextView;     // Указател към текущия (активен) изглед показващ текст от Библията, речник/коментар, резултат от търсенето (който е на фокус в момента - върху който е било щракнато последно).
  FastAccessWidget *fastAccessWidget;
  BooksWidget      *booksWidget;
  BookmarksWidget  *bookmarksWidget;
  ProjectorWidget  *projectorWidget;
  BooksToolBar     *mDockBooks;
  BookmarksToolBar *mDockBookmarks;
  SearchToolBar    *mDockSearch;
  ProjectorToolBar *mDockProjector;
  quint16           currentDR_Day;                 // DR = DailyRead
  quint8            currentDR_ChapterInDailyGroup; //
  quint16           currentDR_AbsIndex;            //
  QUInt16List       currentDR_DailyGroup;          //
  bool       padIsOpen;    // Този флаг е вдигнат докато бележника е отворен.
  bool       WWWResIsOpen; // Този флаг е вдигнат докато WWWResources е отворен.
  bool       ctrlKeyPressed;    // Този флаг е вдигнат докато е натиснат клавиша Crtl.
  bool       altOnlyKeyPressed; // Този флаг е вдигнат докато е натиснат клавиша Alt, но само Alt, без комбинация с други клавиши.
  bool       needToRestart; // Флаг указващ, че програмата трябва да се рестартира, за да влязат в сила направените настройки.
  QColor     iconColorForms; // Цвят на едноцветните икони някъде във формата (автоматично генериран според темата). Този цвят може да е различен от този в главното и контекстното меню, защото техните цветове може да са други.
  QColor     iconColorMenus; // Цвят на едноцветните икони в контекстното меню (автоматично генериран според темата). Този цвят може да е различен от този в главното меню и формата, защото техните цветове може да са други.
  //bool       lightTheme; // Светла тема (дали цветът на прозореца е определен като светъл).

  QStatusBar *statusBar;

  MainWindow();
  virtual ~MainWindow();
  void newHDock(bool loadSession = false, int posXInDock = -1, int posYInDock = -1, int textZoom = 0, QBitArray activeBibleTexts = QBitArray(), quint16 activeBibleTextsCount = 255, quint16 absIndex = MAX_VERSES);
  void newDictionary(bool loadSession = false, int posXInDock = -1, int posYInDock = -1, int textZoom = 0, int dictIndex = 0, int currIndex = 0, bool btnCState = false, bool btnAState = false);
  void showFoundVerse(quint16 absIndex, bool highlightSearchWords = false);
  void showBookmark(quint16 absIndex); // Този метод ще се извиква както от панела с отметките, така и от панела на проектора (от историята).
  void showSearchCenter(bool show); // Показва/скрива центъра за търсене.
  void switchToNormalMode(); // Превключва в режим на нормално четене.
  void set3DTitleBars();
  void colorChanged();
  void fontChanged();
  void fontSizeChanged();
  void setTMenuFontSize();
  void currentHolyTextViewChanged(TextView *newCurrentTextView); // Задава новия изглед, поставен на фокус.
  void currentTextViewChanged(TextView *newCurrentTextView);
  void setProjectorText(QString bibleText, QString chapter, QString verse, quint16 absIndex, QBitArray *activeBibleTexts, quint16 position); // Показва текста на проектора.
  void showStatusBarMessage(QString message, int timeout);
  void setVisible(bool visible); // Reimplement // For TrayIcon.
  QFrame *getVSeparator(); // Връща вертикален сепаратор. Използва се в тулбаровете.

public slots:
  void slotShow();
  void slotNewSelectedText(QString text); // Вдига сигнал с изчистен първи ред от селектирания текст в HDocks и searchView разделите. Използва се от речниците.
  void slotNewSelectedVerse(quint16 absIndex, QString reference); // Вдига сигнал с абсолютния индекс на текущия, селектиран стих. Използва се от коментарите.

  /// NavigationToolBar
  void slotNavigation_newHDock(MDock *dock = 0, MDockWidget *dockWidget = 0);
  void slotNavigation_BooksToolBar();
  void slotNavigation_BookmarksToolBar();
  void slotNavigation_GoBack();
  void slotNavigation_GoForward();
  void slotNavigation_PreviousBook();
  void slotNavigation_NextBook();
  void slotNavigation_PreviousChapter();
  void slotNavigation_NextChapter();
  void slotNavigation_PreviousVerse();
  void slotNavigation_NextVerse();
  void slotNavigation_PreviousChaptersDailyRead();
  void slotNavigation_NextChaptersDailyRead();
  void slotNavigation_PreviousChapterDailyRead();
  void slotNavigation_NextChapterDailyRead();
  void slotNavigation_DailyReadToolBar();
  /// TextToolBar
  void slotText_SearchCenter();
  void slotText_BibleTextsToolBar();
  void slotText_AudioToolBar();
  void slotText_PlayCurrentChapter();
  void slotText_ZoomIn();
  void slotText_ZoomOut();
  void slotText_ZoomNormal();
  //void slotText_SelectAll();
  //void slotText_Copy();
  //void slotText_SearchInTextPrevious();
  //void slotText_SearchInTextCaseSensitive();
  //void slotText_SearchInTextWholeWords();
  //void slotText_SearchInTextNext();
  void slotText_Statistics();
  void slotText_CompareTwoTexts();
  void slotText_UniqueWordsInBible();
  void slotText_UniqueWordsInOT();
  void slotText_UniqueWordsInNT();
  void slotText_UniqueWordsInBook();
  void slotText_UniqueWordsInChapter();
  /// OtherToolBar
  void slotOther_Pad();
  void slotOther_Dictionary(MDock *dock = 0, MDockWidget *dockWidget = 0);
  void slotOther_ExternalImages();
  void slotOther_ProjectorToolBar();
  void slotOther_Links();
  void slotOther_Settings();
  /// FileToolBar
  void slotFile_Exit();
  void slotFile_SessionToolBar();
  void slotLoadSession();
  void slotRestart(bool question); // Този слот е тук, защото е почти същия като горния и е добре да са един до друг.
  /// HelpToolBar
  void slotHelp_Help();
  void slotHelp_About();
  void slotHelp_NewAppVersion();

private slots:
  void slotOnFormCreated(); // Извиква се еднократно след създаване на формата (главния прозорец). Извиква се от таймер.
  void slotBibleTexts();
  void slotFastAccessWidgetInFocus();
  void slotReorderBibleTexts();
  void slotBibleTextsInfo();
  void slotMoreBibleTexts();
  void slotConvertBibleTexts();
  void slotShowWinDimensions();
  void slotFocusChanged(QWidget *old, QWidget *now);
  void slotDockWidgetRaised(MDock *dock, MDockWidget *dockWidget);
  void slotCloseDock(MDock *dock, MDockWidget *dockWidget, int dockWidgetID = 0, quint8 dockWidgetType = 0);
  void slotIconActivated(QSystemTrayIcon::ActivationReason reason); // For TrayIcon.
  void slotResizeEvent(); // Извиква се от resizeEvent метода с няколко милисекунди закъснение, защото при изпълнение на resizeEvent методът не отразява правилно състоянието на прозореца.

private:
  ExTextWindow *pad;
  WWWResources *WWWRes;

  QToolButton *reorderBibleTextsBtn;
  QToolButton *bibleTextsInfoBtn;
  QToolButton *moreBibleTextsBtn;
  QToolButton *convertBibleTextsBtn;
  QList<QToolButton*> bibleTextBtn;
  QCheckBox *saveSessionChBox[9]; // Чекче указващо дали да се помни всяка от 9-те сесии.
  QToolButton *sessionBtn[9]; // 9-те сесии.

  QString exeName;      // Запомня пътя и името на изпълнимия файл. Използва се при рестарт или зареждане на друга сесия (т.е. пак рестарт).
  quint8  startSession; // Запомня коя сесия трябва да се отвори след рестарта. Използва се при рестарт или зареждане на друга сесия (т.е. пак рестарт).

  QString findInTextString;
  QTextDocument::FindFlags findInTextOptions;

  QRect	normGeometry;    // Помни размерите на прозореца, когато е в нормално състояние (не е максимизиран). Методът normalGeometry() би трябвало да връща това, но когато прозорецът е максимизиран връща размера на максимизирания прозорец (явно е бъг).
  bool  windowMaximized; // Помни състоянието на прозореца (дали е бил максимизиран в момента на затварянето, за да го отвори отново максимизиран).

  quint8 currentSession; // Видът на сесията - нормална (0) или специална (от 1 до 8). Приема стойност 9, ако няма да запомня сесия.
  bool showWinDimensions;

  QAction *compareTwoTextsAction;
  QAction *uniqueWordsInBibleAct;
  QAction *uniqueWordsInOTAct;
  QAction *uniqueWordsInNTAct;
  QAction *uniqueWordsInBookAct;
  QAction *uniqueWordsInChapterAct;
  QAction *showWindowsAction; // For TrayIcon.
  QAction *closeAct;          // For TrayIcon.
  QMenu *trayIconMenu;        // For TrayIcon.
  QSystemTrayIcon *trayIcon;  // For TrayIcon.

  qint32 commandLineAbsIndex; // Съдържа абсолютният индекс на стиха, който трябва да се покаже при първоначално пускане на програмата, ако е стартирана с аргументи. Ако не - стойността му е -1 или MAX_VERSES.

  void setAppColors(); // Сменя цветовете на формите и тулбаровете и определя цвета на иконите във формата и в контекстното меню.
  void createViews(); // Създава тулбаровете и разделите.
  void createTrayIcon(); // For TrayIcon.
  void loadSessionSettings(quint8 currentSession);
  void saveSessionSettings(quint8 currentSession);
  QMenu *createPopupMenu();
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void resizeEvent(QResizeEvent *event);
  void moveEvent(QMoveEvent *event);
  void dailyReadPanel_HideDeuterocanonical(); // Скрива Второканоничните книги от панела за ежедневно четене. Този метод се извиква в 5-те слота при превключване на групите в режим на ежедневно четене.

signals:
  void playCurrentChapterNow(); // Сигнал към аудио панела, указващ незабавно прослушване на текущата глава.
  void newSelectedText(QString text); // Пренася изчистен първи ред от селектирания текст в HDocks и searchView разделите. Използва се от речниците.
  void newSelectedVerse(quint16 absIndex, QString reference); // Пренася абсолютния индекс на текущия селектиран стих. Използва се от коментарите.
};
#endif
