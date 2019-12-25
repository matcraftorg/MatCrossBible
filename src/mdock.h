/***************************************************************************
 *   MDock                                                                 *
 *   Copyright (C) 2015-2020 by MatCraft, Bulgaria                         *
 *   matcraft.org@gmail.com                                                *
 *   http://www.matcraft.org/                                              *
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

#ifndef MDOCK_H
#define MDOCK_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include <QCloseEvent>
#include <QToolTip>
#include <QPixmap>
#include <QPainter>
#include <QDateTime>
#include <QDebug>

class MDockWidget;
struct TabList;
class BLabel;

// Клас за реализиране на док-widget.
// Възможност за реализиране на тулбарове.
class MDock : public QWidget
{
Q_OBJECT

private:
  friend class MDockWidget;

  QRect    mDockGeometry;
  QMargins mDockMargins;
  QColor   mDockBgColor;
  int      mDockRows; // Брой на редовете.
  int      mDockWidgetPadding;
  QSize    mDockWidgetMinSizePr; // Минимален размер на прозорците.
  bool     mDockWidgetTabbedTitleBar; // Указва дали табовете да са вградени в заглавната лента.
  int      selectedSplitterY; // Запомня кой е селектираният сплитер по Y, при натискане и задържане на бутона на мишката. -1, ако не е селектиран сплитер по Y; >=0, ако е селектиран по Y или по X.
  int      selectedSplitterX; // Запомня кой е селектираният сплитер по X, при натискане и задържане на бутона на мишката. -1, ако не е селектиран сплитер по X.
  QFrame  *trackFrame; // Рамка, която се показва при местене на прозорец в дока.
  QColor   trackFrameColor;
  QList<MDockWidget*> mDockWidgetList;
  QList<TabList> tabList; // Списък с всички прозорци, които са на една и съща позиция т.е. разположени са в табове. Позицията е записана във всеки един от прозорците.

  QList<int>  spYpr; // Масив с позициите на сплитерите по Y в проценти. Винаги има най-малко 2 сплитера, като първият е винаги 0%, а последният - винаги 100%.
  QList<int> *spXpr; // Двумерен масив с позициите на сплитерите по X, за всеки ред, в проценти. Винаги има най-малко 2 сплитера (на ред), като първият е винаги 0%, а последният винаги 100%.

  QList<int>  spYpx; // Масив с позициите на сплитерите по Y в пиксели. Винаги има най-малко 2 сплитера, като първият е винаги 0, а последният - винаги височината на MDock.
  QList<int> *spXpx; // Двумерен масив с позициите на сплитерите по X, за всеки ред, в пиксели. Винаги има най-малко 2 сплитера (на ред), като първият е винаги 0, а последният винаги е равен на широчината на MDock.

  QList<int> dockWidgetCount;  // Масив с броя на прозорците във всеки ред (масивът съдържа по едно число за всеки ред).

  bool allowMoveSplitters;
  bool allowMoveDockWidgets;
  bool allowTabbedDockWidgets;
  bool allowMaximizeDockWidgets;

  bool registerToTabList(MDockWidget *mDockWidget); // Добавя прозореца към специален списък, в който се помни кои прозорци са комбинирани в табове.
  bool unregisterFromTabList(MDockWidget *mDockWidget); // Премахва прозореца от този списък.
  void recombineTabbedDockWidgets(int posXInDock, int posYInDock); // Преизчертава табовете на прозорците на тази позиция, ако са в комбинация в табове. Това е нужно при добавяне или премахване на прозорец.
  QRect getDockWidgetGeometry(int posXInDock, int posYInDock); // Връща позицията и размера на указания прозорец.
  bool insertRow(int row); // Вмъква нов ред с място за един нов прозорец на указаната позиция (0 - най-отгоре) и предизвиква преизчисляване на мрежата.
  bool removeRow(int row); // Премахва указания ред с всички места на прозорци в него и предизвиква преизчисляване на мрежата.
  bool insertDockWidget(int row, int dockPos); // Вмъква място за нов прозорец на указаната позиция в ред row и предизвиква преизчисляване на мрежата.
  bool removeDockWidget(int row, int dockPos); // Премахва мястото на прозореца на указаната позиция в ред row и предизвиква преизчисляване на мрежата.
  bool moveRow(int currPos, int newPos); // Премества реда на указаното място и предизвиква преизчисляване на мрежата.
  bool moveDockWidget(int row, int currPos, int newPos); // Премества прозореца на указаното място и предизвиква преизчисляване на мрежата.
  bool setSpYpx(int splitter, int splitterPos); // Установява позицията в пиксели на вертикален сплитер splitter (сплитерите между редовете) и предизвиква преизчисляване на мрежата.
  bool setSpXpx(int row, int splitter, int splitterPos); // Установява позицията в пиксели на хоризонтален сплитер splitter от ред row и предизвиква преизчисляване на мрежата.
  int getSpYpx(int splitter); // Връща позицията в пиксели на вертикален сплитер splitter (сплитерите между редовете).
  int getSpXpx(int row, int splitter); // Връща позицията в пиксели на хоризонтален сплитер splitter от ред row.
  int getSpYpr(int splitter); // Връща позицията в проценти на вертикален сплитер splitter (сплитерите между редовете).
  int getSpXpr(int row, int splitter); // Връща позицията в проценти на хоризонтален сплитер splitter от ред row.
  void recalculateGrid(); // Този метод ще се извиква при ресайз на прозореца и ще преизчислява координатите на мрежата в пиксели според зададените такива в проценти.
  void dockWidgetClosed(MDockWidget *dockWidget);
  void dockWidgetMoving(MDockWidget *dockWidget, int mouseX, int mouseY, bool done);
  void dockWidgetTabPressed(MDockWidget *dockWidget, int tabIndex);
  void dockWidgetTitleBarMouseDoubleClick(MDockWidget *dockWidget);

protected:
  void resizeEvent(QResizeEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

public:
  MDock(QWidget *parent = 0);
  void setDockMargins(int left, int top, int right, int bottom);
  QMargins getDockMargins();
  void setDockWidgetPadding(int padding);
  int getDockWidgetPadding();
  void setDockWidgetMinSizePr(QSize minSizePr);
  QSize getDockWidgetMinSizePr();
  void setDockWidgetTabbedTitleBar(bool tabbedTitleBar);
  int getDockWidgetTabbedTitleBar();
  void setProperties(bool allowMoveSplitters = true, bool allowMoveDockWidgets = true, bool allowTabbedDockWidgets = true, bool allowMaximizeDockWidgets = true);
  void setDockBgColor(QColor color);
  QColor getDockBgColor();
  void setTrackFrameColor(QColor color);
  QColor getTrackFrameColor();
  void setAllDockWidgets3DTitleBar(bool dockWidget3DTitleBar);
  bool setDockGridState(QString dockGridState); // Установява/зарежда състоянието на мрежата от стринг, прочетен от INI файл. Връща false, ако нещо не е наред.
  QString getDockGridState(); // Връща състоянието на мрежата във вид на стринг подходящ за записване в INI файл.
  int getRowCount(); // Връща броя на редовете в мрежата.
  int getDockWidgetCount(int row); // Връща броя на прозорците в указания ред на мрежата.
  QList<MDockWidget*> *getAllDockWidgets(); // Връща указател към списъка от всички прозорци в дока.
  QList<MDockWidget*>  getAllTabbedDockWidgets(int posXInDock, int posYInDock); // Връща списък от всички прозорци на тази позиция, комбинирани в табове. Ако има само един прозорец на тази позиция, връща празен списък.
  void addDockWidget(MDockWidget *mDockWidget, int posXInDock, int posYInDock); // Добавя нов прозорец на указаните координати.
  void insertDockWidget(MDockWidget *mDockWidget, int posXInDock, int posYInDock); // Създава ново място (между два други прозореца) и поставя прозореца там.
  void insertDockWidget(MDockWidget *mDockWidget, int posYInDock); // Създава нов ред (между два други реда) и поставя прозореца там.
};

// -----------------------------------------------------------------------------------------------------------------------------------

class MDockWidget : public QWidget
{
Q_OBJECT

private:
  friend class MDock;

  MDock *mDock;
  int    dockWidgetID; // ID на прозореца (за нуждите на клиента).
  quint8 dockWidgetType; // Тип на прозореца (за нуждите на клиента).
  QColor dockWidgetTitleBarColor;
  QColor dockWidgetTitleBarTextColor;
  QColor dockWidgetTitleBarButtonColor;
  QColor dockWidgetBgColor;
  bool dockWidget3DTitleBar;
  bool dockWidgetMaximized;
  bool dockWidgetDisallowCloseLevel1;
  bool dockWidgetDisallowCloseLevel2;
  bool dockWidgetDisallowCloseFromButton;
  bool dockWidgetTabPressed;
  bool dockWidgetMoving;
  qint64 currentMSecs; // Запомня времето, в което е натиснат бутона на мишката за да се сравни с времето на отпускане на бутона.

  int posYInDock; // Позиция по Y в дока.
  int posXInDock; // Позиция по X в дока.

  int tabIndex;

  BLabel  *titleBar;
  QLabel  *titleBar_Label;
  BLabel  *titleBar_NewBtn;
  BLabel  *titleBar_MaximizeBtn;
  BLabel  *titleBar_CloseBtn;
  QWidget *mainContainer;
  QWidget *mainWidget; // Указател към Widget-а, който ще се постави в mainContainer на MDockWidget.
  QFrame  *tabMarkLine; // Черта на активния таб (ако има такъв).
  QWidget *tabBar;
  QList<BLabel*> tabBar_Labels;

  void setPosInDock(int posXInDock, int posYInDock = -1);
  void setTabs(QStringList tabTitles, int tabIndex); // Показва табове. Броят им е равен на броя на заглавията в tabTitles, а текущ таб е зададен с tabIndex (започва от 0).
  void refreshAllTabs(); // Извиква се при смяна на шрифт или цвят на заглавната лента, за да може това да се отрази и в табовете (ако има такива).
  void refreshTabs(); // Извиква се при смяна на шрифт или цвят на заглавната лента, за да може това да се отрази и в табовете (ако има такива).
  void resizeWidget();
  QPixmap createNewPixmap();
  QPixmap createMaximizePixmap(bool maximize);
  QPixmap createClosePixmap();

public:
  MDockWidget(MDock *mDock, const QString dockWidgetTitle = "", const bool dockWidgetShowNewButton = false, const bool dockWidgetShowMaximizeButton = true, const bool dockWidget3DTitleBar = true, const int dockWidgetID = 0, const quint8 dockWidgetType = 0);
  ~MDockWidget();
  void setWidget(QWidget *widget, int leftMargin = 0, int topMargin = 0, int rightMargin = 0, int bottomMargin = 0);
  void deleteWidget();
  QWidget *getWidget();
  QWidget *getTitleBar(); // Указател към заглавната лента. Позволява потребителя да прави някакви негови си неща.
  QLabel  *getTitleBarLabel(); // Указател към етикета в заглавната лента. Позволява на потребителя да сложи икона например.
  QWidget *getMainContainer(); // Указател към контейнера, в който се поставя съдържанието. Отново за повече свобода на потребителя.
  int getPosXInDock();
  int getPosYInDock();
  void setCurrentTab(); // Прави прозореца да е текущ таб (ако участва в табове).
  int getTabIndex(); // Връща индекса на таба или -1, ако няма табове.
  void setDockWidgetDisallowCloseLevel1(bool disallow); // Забранява/разрешава затварянето на прозореца. Бутона за затваряне е скрит/показан.
  bool getDockWidgetDisallowCloseLevel1();
  void setDockWidgetDisallowCloseLevel2(bool disallow); // Забранява/разрешава затварянето на прозореца. Бутона за затваряне е Disabled/Enabled.
  bool getDockWidgetDisallowCloseLevel2();
  void setDockWidgetDisallowCloseFromButton(bool disallow); // Забранява/разрешава затварянето на прозореца от бутона за затваряне, но при натискането на бутона винаги ще се излъчи сигнал.
  bool getDockWidgetDisallowCloseFromButton();
  void setDockWidgetTitle(QString title);
  QString getDockWidgetTitle();
  void setDockWidgetID(int ID);
  int getDockWidgetID();
  void setDockWidgetType(int type);
  quint8 getDockWidgetType();
  void setDockWidgetTitleBarFont(QFont font);
  QFont getDockWidgetTitleBarFont();
  void setDockWidgetTitleBarFontSize(int size);
  int getDockWidgetTitleBarFontSize();
  void setDockWidgetTitleBarFontBold(bool bold);
  bool getDockWidgetTitleBarFontBold();
  void setDockWidgetTitleBarFontItalic(bool italic);
  bool getDockWidgetTitleBarFontItalic();
  void setDockWidgetTitleBarTextColor(QColor color);
  QColor getDockWidgetTitleBarTextColor();
  void setDockWidgetTitleBarButtonColor(QColor color);
  QColor getDockWidgetTitleBarButtonColor();
  void setDockWidgetTitleBarColor(QColor color);
  QColor getDockWidgetTitleBarColor();
  void setDockWidgetBgColor(QColor color);
  QColor getDockWidgetBgColor();
  void setDockWidget3DTitleBar(bool dockWidget3DTitleBar);
  bool getDockWidget3DTitleBar();
  bool isDockWidgetMaximized();
  void setNewBtnToolTip(const QString tip);
  void setMaximizeBtnToolTip(const QString tip);
  void setCloseBtnToolTip(const QString tip);

public slots:
  void newDockWidget();
  void maximizeDockWidget(); // Максимизира/нормализира прозореца.
  void closeDockWidget();

private slots:
  void closeButtonPressed();
  void tabPressed(int tabIndex);
  void titleBarHeightChange();

protected:
  //void closeEvent(QCloseEvent *event);
  //void resizeEvent(QResizeEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);

signals:
  void dockWidgetNewButtonPressed(MDock *dock, MDockWidget *dockWidget, int dockWidgetID = 0, quint8 dockWidgetType = 0, QString objectName = "");
  void dockWidgetCloseButtonPressed(MDock *dock, MDockWidget *dockWidget, int dockWidgetID = 0, quint8 dockWidgetType = 0, QString objectName = "");
  void dockWidgetTitleBarMouseMove(MDock *dock, MDockWidget *dockWidget, QMouseEvent *event = 0);
  void dockWidgetTitleBarMousePress(MDock *dock, MDockWidget *dockWidget, QMouseEvent *event = 0);
  void dockWidgetTitleBarMouseRelease(MDock *dock, MDockWidget *dockWidget, QMouseEvent *event = 0);
  void dockWidgetRaised(MDock *dock, MDockWidget *dockWidget); // Излъчва се или при натискане върху заглавната лента или при натискане върху таб.
};

// -----------------------------------------------------------------------------------------------------------------------------------

struct TabList
{
  QList<MDockWidget*> mDockWidgetList; // Списък с всички прозорци, които са на една и съща позиция т.е. разположени са в табове. Позицията е записана във всеки един от прозорците.
};

// -----------------------------------------------------------------------------------------------------------------------------------

class BLabel : public QLabel
{
Q_OBJECT

private:
  bool isButton;
  bool show3DBackground;
  int ID;
  int h, s, v, hgt;
  QColor color;

public:
  BLabel(const QString &text, const bool &isButton = true, const bool &show3DBackground = true, const int &ID = -1, QWidget *parent = 0, Qt::WindowFlags f = 0) : QLabel(text, parent, f)
  {
    setTextFormat(Qt::RichText); // Това указва текстът на заглавната лента да се третира винаги като HTML. По подразбиране е Qt::AutoText, което прави проверка на текста какъв е и според проверката решава дали да го покаже като HTML или като Qt::PlainText.
    setOpenExternalLinks(false); // Това не знам дали е нужно, но ако в заглавната лента се появи линк, да не разрешава отварянето му в браузър.
    setTextInteractionFlags(Qt::NoTextInteraction); // Това е много нужно, защото когато текст-формата е Qt::RichText, се блокират някои от ивентите на етикета (свързани с кликването с мишката) и заглавната лента не може да се използва за преместване на прозореца.
    this->isButton = isButton; // true - ако е бутон, false - ако е етикет (върху който също може да се кликва).
    this->show3DBackground = show3DBackground;
    this->ID = ID;
    h = 0; s = 0; v = 0; hgt = height();
  }
  void set3DBackground(bool show3DBackground)
  {
    this->show3DBackground = show3DBackground;
    update();
  }

protected:
  void mouseMoveEvent(QMouseEvent *event)
  {
    if (!isButton) QLabel::mouseMoveEvent(event); // Ако е бутон не извиква базовия метод.
  }
  void mousePressEvent(QMouseEvent *event)
  {
    if (event->x() >= 0 && event->y() >= 0 && event->x() < width() && event->y() < height()) emit buttonPress(ID);
    if (!isButton) QLabel::mousePressEvent(event); // Ако е бутон излъчва само сигнал, без да извиква базовия метод.
  }
  void mouseReleaseEvent(QMouseEvent *event)
  {
    if (event->x() >= 0 && event->y() >= 0 && event->x() < width() && event->y() < height()) emit buttonRelease(ID);
    if (!isButton) QLabel::mouseReleaseEvent(event); // Ако е бутон излъчва само сигнал, без да извиква базовия метод.
  }
  void mouseDoubleClickEvent(QMouseEvent *event)
  {
    if (event->x() >= 0 && event->y() >= 0 && event->x() < width() && event->y() < height()) emit buttonDoubleClick(ID);
    if (!isButton) QLabel::mouseDoubleClickEvent(event); // Ако е бутон излъчва само сигнал, без да извиква базовия метод.
  }
  void paintEvent(QPaintEvent *event)
  {
    if (show3DBackground)
    {
      color = this->palette().brush(QPalette::Active, QPalette::Button).color(); // Цвят на фона.
      color.getHsv(&h, &s, &v);
      v += 20; if (v > 255) v = 255;
      s -= 10; if (s < 0) s = 0;
      color.setHsv(h, s, v); // Изсветлява цвета на фона.
      color.setAlpha(40); // Прави го прозрачен.

      QPainter painter(this);
      h = height()-2;
      v = 1;
      while (h > 0)
      {
        painter.fillRect(0, v, width(), h, color); // Наслагва цвета, така че да се получи 3D изпъкване.
        h -= 2;
        v += 1;
      }
    }
    QLabel::paintEvent(event);
  }
  void resizeEvent(QResizeEvent *event)
  {
    QLabel::resizeEvent(event);
    if (hgt != height())
    {
      hgt = height();
      emit heightChange(height(), ID);
    }
  }

signals:
  void buttonPress(int ID = -1);
  void buttonRelease(int ID = -1);
  void buttonDoubleClick(int ID = -1);
  void heightChange(int height = -1, int ID = -1);
};

#endif // MDOCK_H
