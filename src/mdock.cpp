/***************************************************************************
 *   MDock                                                                 *
 *   Copyright (C) 2015-2020 by MatCraft, Bulgaria                         *
 *   matcraft.org@gmail.com                                                *
 *   https://www.matcraft.org/                                             *
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

#include "mdock.h"
//#include <QMessageBox> // QMessageBox::information(this, QString(""), QString(""));

MDock::MDock(QWidget *parent) : QWidget(parent)
{
  mDockBgColor = QColor(100, 100, 100);
  QPalette palette;
  palette.setBrush(QPalette::Window, mDockBgColor);
  palette.setBrush(QPalette::Button, mDockBgColor);
  //palette.setBrush(QPalette::Base, mDockBgColor);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  trackFrameColor = QColor(255, 0, 0);
  palette.setBrush(QPalette::WindowText, trackFrameColor);
  QColor trackFrameColorAlpha = trackFrameColor;
  trackFrameColorAlpha.setAlpha(96);
  palette.setBrush(QPalette::Window, trackFrameColorAlpha);
  palette.setBrush(QPalette::Button, trackFrameColorAlpha);
  //palette.setBrush(QPalette::Base, trackFrameColorAlpha);
  trackFrame = new QFrame(this);
  trackFrame->setGeometry(QRect(-100, -100, 10, 10));
  trackFrame->setFrameShape(QFrame::Box);
  trackFrame->setFrameShadow(QFrame::Plain);
  trackFrame->setPalette(palette);
  trackFrame->setAutoFillBackground(true);

  //this->setCursor(QCursor(Qt::SizeAllCursor));

  mDockGeometry = QRect(0, 0, 100, 100);
  mDockMargins = QMargins(2, 2, 2, 2);
  mDockRows = 1;
  mDockWidgetPadding = 2;
  mDockWidgetMinSizePr = QSize(1, 1);
  mDockWidgetTabbedTitleBar = true;
  selectedSplitterY = -1;
  selectedSplitterX = -1;

  spYpr = QList<int>();
  spYpx = QList<int>();
  spXpr = new QList<int>[mDockRows];
  spXpx = new QList<int>[mDockRows];
  for (int i = 0; i < mDockRows; i++)
  {
    spXpr[i] = QList<int>();
    spXpx[i] = QList<int>();
  }
  dockWidgetCount = QList<int>();

  for (int i = 0; i < mDockRows; i++)
  {
    spYpr << 0;
    spYpx << 0;
    spXpr[i] << 0 << 100;
    spXpx[i] << 0 << 100;
    dockWidgetCount << 0;
  }
  spYpr << 100;
  spYpx << 100;

  allowMoveSplitters = true;
  allowMoveDockWidgets = true;
  allowTabbedDockWidgets = true;
  allowMaximizeDockWidgets = true;

#ifndef QT_NO_CURSOR
  setCursor(Qt::SizeBDiagCursor); // Qt::SizeAllCursor
#endif
}

void MDock::setDockMargins(int left, int top, int right, int bottom)
{
  mDockMargins = QMargins(left, top, right, bottom);
  recalculateGrid();
}

QMargins MDock::getDockMargins()
{
  return mDockMargins;
}

void MDock::setDockWidgetPadding(int padding)
{
  if (padding < 0) padding = 0;
  mDockWidgetPadding = padding;
  recalculateGrid();
}

int MDock::getDockWidgetPadding()
{
  return mDockWidgetPadding;
}

void MDock::setDockWidgetMinSizePr(QSize minSizePr)
{
  if (minSizePr.width() < 0) minSizePr.setWidth(0);
  if (minSizePr.height() < 0) minSizePr.setHeight(0);
  mDockWidgetMinSizePr = minSizePr;
}

QSize MDock::getDockWidgetMinSizePr()
{
  return mDockWidgetMinSizePr;
}

void MDock::setDockWidgetTabbedTitleBar(bool tabbedTitleBar)
{
  mDockWidgetTabbedTitleBar = tabbedTitleBar;
}

int MDock::getDockWidgetTabbedTitleBar()
{
  return mDockWidgetTabbedTitleBar;
}

void MDock::setProperties(bool allowMoveSplitters, bool allowMoveDockWidgets, bool allowTabbedDockWidgets, bool allowMaximizeDockWidgets)
{
  this->allowMoveSplitters = allowMoveSplitters;
  this->allowMoveDockWidgets = allowMoveDockWidgets;
  this->allowTabbedDockWidgets = allowTabbedDockWidgets;
  this->allowMaximizeDockWidgets = allowMaximizeDockWidgets;

#ifndef QT_NO_CURSOR
  if (allowMoveSplitters)
    setCursor(Qt::SizeBDiagCursor); // Qt::SizeAllCursor
  else
    setCursor(Qt::ArrowCursor);
#endif
}

void MDock::setDockBgColor(QColor color)
{
  mDockBgColor = color;

  QPalette palette;
  palette.setBrush(QPalette::Window, mDockBgColor);
  palette.setBrush(QPalette::Button, mDockBgColor);
  //palette.setBrush(QPalette::Base, mDockBgColor);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  for (int i = 0; i < mDockWidgetList.count(); i++)
  {
    mDockWidgetList[i]->setDockWidgetTitleBarColor( mDockWidgetList[i]->getDockWidgetTitleBarColor() ); // Това няма да промени цвета на заглавната лента, но ще промени цвета на табчетата (ако има такива).
  }
}

QColor MDock::getDockBgColor()
{
  return mDockBgColor;
}

void MDock::setTrackFrameColor(QColor color)
{
  trackFrameColor = color;

  QPalette palette;
  palette.setBrush(QPalette::WindowText, trackFrameColor);
  color.setAlpha(96);
  palette.setBrush(QPalette::Window, color);
  palette.setBrush(QPalette::Button, color);
  //palette.setBrush(QPalette::Base, color);
  trackFrame->setPalette(palette);
}

QColor MDock::getTrackFrameColor()
{
  return trackFrameColor;
}

void MDock::setAllDockWidgets3DTitleBar(bool dockWidget3DTitleBar)
{
  for (int i = 0; i < mDockWidgetList.count(); i++)
  {
    mDockWidgetList[i]->setDockWidget3DTitleBar(dockWidget3DTitleBar);
  }
}

bool MDock::setDockGridState(QString dockGridState)
{
  QStringList rows = dockGridState.split("_", QString::SkipEmptyParts); // 0^25^50^75^100_1^4^2^1_0^100_0^10^30^55^100_0^50^100_0^100 // Частта преди първата долна черта се отнася за сплитерите по вертикала (редовете). Следващата част е броят на прозорците на всеки ред. Останалите са за сплитерите по хоризонтала за всеки ред.
  if (rows.count() <= 2) return false;
  int dockRowsH = rows.count() - 2;

  bool OK = true;
  int spI;
  QStringList digits;
  QList<int>  spYprH = QList<int>();
  QList<int> *spXprH = new QList<int>[dockRowsH];
  for (int i = 0; i < dockRowsH; i++)
  {
    spXprH[i] = QList<int>();
  }
  QList<int> dockCountH = QList<int>();

  digits = rows[0].split("^", QString::SkipEmptyParts);
  if ((digits.count()-1) != dockRowsH) OK = false;
  for (int i = 0; i < digits.count(); i++)
  {
    spI = digits[i].toInt();
    if (spI < 0 || spI > 100) OK = false;
    spYprH << spI;
  }
  if (spYprH[0] != 0) OK = false;
  if (spYprH[spYprH.count()-1] != 100) OK = false;

  digits = rows[1].split("^", QString::SkipEmptyParts);
  if (digits.count() != dockRowsH) OK = false;
  for (int i = 0; i < digits.count(); i++)
  {
    spI = digits[i].toInt();
    if (spI < 0 || spI > 500) OK = false;
    dockCountH << spI;
  }

  for (int i = 2; i < rows.count(); i++)
  {
    digits = rows[i].split("^", QString::SkipEmptyParts);
    if ((digits.count()) < 2) OK = false;
    for (int j = 0; j < digits.count(); j++)
    {
      spI = digits[j].toInt();
      if (spI < 0 || spI > 100) OK = false;
      spXprH[i-2] << spI;
    }
    if (spXprH[i-2][0] != 0) OK = false;
    if (spXprH[i-2][spXprH[i-2].count()-1] != 100) OK = false;
  }

  if (!OK)
  {
    delete[] spXprH;
    return false;
  }


  // Инициализиране:
  for (int i = 0; i < mDockRows; i++)
  {
    spXpx[i].clear();
  }
  delete[] spXpx;
  spXpx = new QList<int>[dockRowsH];

  mDockRows = dockRowsH;
  spYpr = spYprH;
  delete[] spXpr;
  spXpr = spXprH;
  dockWidgetCount = dockCountH;

  recalculateGrid();
  return true;
}

QString MDock::getDockGridState()
{
  QString res = ""; // 0^25^50^75^100_1^4^2^1_0^100_0^10^30^55^100_0^50^100_0^100 // Частта преди първата долна черта се отнася за сплитерите по вертикала (редовете). Следващата част е броят на прозорците на всеки ред. Останалите са за сплитерите по хоризонтала за всеки ред.
  for (int i = 0; i < spYpr.count(); i++)
  {
    res += QString("%1").arg(spYpr[i]);
    if (i < spYpr.count()-1) res += "^";
  }
  res += "_";
  for (int i = 0; i < dockWidgetCount.count(); i++)
  {
    res += QString("%1").arg(dockWidgetCount[i]);
    if (i < dockWidgetCount.count()-1) res += "^";
  }
  res += "_";
  for (int i = 0; i < mDockRows; i++)
  {
    for (int j = 0; j < spXpr[i].count(); j++)
    {
      res += QString("%1").arg(spXpr[i][j]);
      if (j < spXpr[i].count()-1) res += "^";
    }
    if (i < mDockRows-1) res += "_";
  }
  return res;
}

int MDock::getRowCount()
{
  return mDockRows;
}

int MDock::getDockWidgetCount(int row)
{
  if (row < 0 || row >= mDockRows) return -1;
  return dockWidgetCount[row];
}

QList<MDockWidget*> *MDock::getAllDockWidgets()
{
  return &mDockWidgetList;
}

QList<MDockWidget*> MDock::getAllTabbedDockWidgets(int posXInDock, int posYInDock)
{
  QList<MDockWidget*> list;
  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == posXInDock && tabList[i].mDockWidgetList[0]->getPosYInDock() == posYInDock) // Ако на тази позиция има табове.
    {
      for (int w = 0; w < tabList[i].mDockWidgetList.count(); w++) // Минава през всички прозорци на тази позиция.
      {
        list << tabList[i].mDockWidgetList[w];
      }
      break;
    }
  }
  return list;
}

void MDock::addDockWidget(MDockWidget *mDockWidget, int posXInDock, int posYInDock)
{
  // Този метод добавя нов прозорец на указаните координати.
  // Ако на тези координати вече има прозорец, новият се добавя в таб.
  // Ако са зададени координати по-големи или по-малки от съществуващите в мрежата, първо се
  // създава ново място в мрежата (в края/началото) и после прозорецът се добавя на това място.
  // Така например:
  // Ако posYInDock <= 0, новият прозорец ще се добави над всички други;
  // Ако posYInDock >= броя на редовете, новият прозорец ще се добави под всички други;
  // Ако posXInDock <= 0, новият прозорец ще се добави вляво от всички други на този ред;
  // Ако posXInDock >= броя на прозорците на този ред, новият прозорец ще се добави вдясно от всички други на този ред;
  // Този метод не дава възможност за вмъкване на прозореца на ново място между други прозорци.

  if (mDockWidget == 0) return;
  
  for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
  {
    if (mDockWidgetList[i]->dockWidgetMaximized) // Ако прозореца е максимизиран.
    {
      dockWidgetTitleBarMouseDoubleClick(mDockWidgetList[i]); // Нормализира го.
      break;
    }
  }
  
  if (posYInDock < 0) // Ако трябва да се добави нов ред най-отгоре.
  {
    posXInDock = 0;
    posYInDock = 0;
    if (insertRow(posYInDock) && insertDockWidget(posYInDock, posXInDock)) // Ако редът е бил добавен успешно.
    {
      for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
      {
        if (mDockWidgetList[i]->getPosYInDock() >= posYInDock) // Ако този прозорец е под новия ред.
        {
          mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()+1); // Премества всички прозорци след новия ред с една позиция надолу.
        }
      }
      recalculateGrid();
    }
    else
    {
      posXInDock = 0;
      posYInDock = 0;
    }
  }
  else if (posYInDock >= mDockRows) // Ако трябва да се добави нов ред най-отдолу.
  {
    posXInDock = 0;
    posYInDock = mDockRows;
    if (insertRow(posYInDock) && insertDockWidget(posYInDock, posXInDock))
    {
      recalculateGrid();
    }
    else
    {
      posXInDock = 0;
      posYInDock = 0;
    }
  }
  else if (posXInDock < 0) // Ако трябва да се добави нов прозорец в началото на този ред.
  {
    posXInDock = 0;
    if (insertDockWidget(posYInDock, posXInDock)) // Ако прозорецът е бил добавен успешно.
    {
      for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
      {
        if (mDockWidgetList[i]->getPosYInDock() == posYInDock && mDockWidgetList[i]->getPosXInDock() >= posXInDock) // Ако този прозорец е в дясно от добавения, на същия ред.
        {
          mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след добавения с една позиция надясно.
        }
      }
      recalculateGrid();
    }
    else
    {
      posXInDock = 0;
      posYInDock = 0;
    }
  }
  else if (posXInDock >= dockWidgetCount[posYInDock]) // Ако трябва да се добави нов прозорец в края на този ред.
  {
    posXInDock = dockWidgetCount[posYInDock];
    if (insertDockWidget(posYInDock, posXInDock))
    {
      recalculateGrid();
    }
    else
    {
      posXInDock = 0;
      posYInDock = 0;
    }
  }

  mDockWidget->setPosInDock(posXInDock, posYInDock);
  mDockWidget->resizeWidget();

  mDockWidgetList << mDockWidget;
  registerToTabList(mDockWidget); // Проверява дали трябва да се комбинира с друг прозорец в табове.
  recombineTabbedDockWidgets(posXInDock, posYInDock); // Ако трябва да се комбинира с друг прозорец в табове.

  mDockWidget->show();
}

void MDock::insertDockWidget(MDockWidget *mDockWidget, int posXInDock, int posYInDock)
{
  // Този метод създава ново място на указаните координати и добавя новия прозорец там.
  // Ако са зададени координати много по-големи или по-малки от съществуващите в мрежата,
  // те се преизчисляват.
  // Така например:
  // Ако posYInDock <= 0, новият прозорец ще се добави над всички други;
  // Ако posYInDock >= броя на редовете, новият прозорец ще се добави под всички други;
  // Ако posXInDock <= 0, новият прозорец ще се добави вляво от всички други на този ред;
  // Ако posXInDock >= броя на прозорците на този ред, новият прозорец ще се добави вдясно от всички други на този ред;
  // Ако posYInDock = 1 ще се създаде нов ред между редове 0 и 1 и новият прозорец ще се добави в него;
  // Ако posXInDock = 1 ще се създаде ново място между прозорец 0 и 1 и новият прозорец ще се добави в него;
  // Този метод винаги вмъква прозореца на ново място между други прозорци.

  if (mDockWidget == 0) return;
  
  if (posYInDock < 0)
  {
    insertDockWidget(mDockWidget, 0);
    return;
  }
  if (posYInDock >= mDockRows)
  {
    insertDockWidget(mDockWidget, mDockRows);
    return;
  }
  
  for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
  {
    if (mDockWidgetList[i]->dockWidgetMaximized) // Ако прозореца е максимизиран.
    {
      dockWidgetTitleBarMouseDoubleClick(mDockWidgetList[i]); // Нормализира го.
      break;
    }
  }
  
  if (posXInDock < 0) posXInDock = 0;
  if (posXInDock > dockWidgetCount[posYInDock]) posXInDock = dockWidgetCount[posYInDock];

  if (insertDockWidget(posYInDock, posXInDock)) // Ако прозорецът е бил добавен успешно.
  {
    for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
    {
      if (mDockWidgetList[i]->getPosYInDock() == posYInDock && mDockWidgetList[i]->getPosXInDock() >= posXInDock) // Ако този прозорец е в дясно от добавения, на същия ред.
      {
        mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след добавения с една позиция надясно.
      }
    }
    recalculateGrid();
  }
  else
  {
    posXInDock = 0;
    posYInDock = 0;
  }

  mDockWidget->setPosInDock(posXInDock, posYInDock);
  mDockWidget->resizeWidget();

  mDockWidgetList << mDockWidget;
  registerToTabList(mDockWidget); // Проверява дали трябва да се комбинира с друг прозорец в табове.
  recombineTabbedDockWidgets(posXInDock, posYInDock); // Ако трябва да се комбинира с друг прозорец в табове.

  mDockWidget->show();
}

void MDock::insertDockWidget(MDockWidget *mDockWidget, int posYInDock)
{
  // Този метод създава нов ред на указаните координати и добавя новия прозорец там.
  // Ако са зададени координати много по-големи или по-малки от съществуващите в мрежата,
  // те се преизчисляват.
  // Така например:
  // Ако posYInDock <= 0, новият прозорец ще се добави над всички други;
  // Ако posYInDock >= броя на редовете, новият прозорец ще се добави под всички други;
  // Ако posYInDock = 1 ще се създаде нов ред между редове 0 и 1 и новият прозорец ще се добави в него;
  // Този метод винаги вмъква прозореца на нов ред.

  if (mDockWidget == 0) return;
  
  for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
  {
    if (mDockWidgetList[i]->dockWidgetMaximized) // Ако прозорецът е максимизиран.
    {
      dockWidgetTitleBarMouseDoubleClick(mDockWidgetList[i]); // Нормализира го.
      break;
    }
  }
  
  if (posYInDock < 0) posYInDock = 0;
  if (posYInDock > mDockRows) posYInDock = mDockRows;

  if (insertRow(posYInDock) && insertDockWidget(posYInDock, 0)) // Ако прозорецът е бил добавен успешно.
  {
    for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
    {
      if (mDockWidgetList[i]->getPosYInDock() >= posYInDock) // Ако този прозорец е под новия ред.
      {
        mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()+1); // Премества всички прозорци след новия ред с една позиция надолу.
      }
    }
    recalculateGrid();
  }
  else
  {
    posYInDock = 0;
  }

  mDockWidget->setPosInDock(0, posYInDock);
  mDockWidget->resizeWidget();

  mDockWidgetList << mDockWidget;
  registerToTabList(mDockWidget); // Проверява дали трябва да се комбинира с друг прозорец в табове.
  recombineTabbedDockWidgets(0, posYInDock); // Ако трябва да се комбинира с друг прозорец в табове.

  mDockWidget->show();
}

bool MDock::registerToTabList(MDockWidget *mDockWidget)
{
  // Проверява, дали на тази позиция има повече от един прозорец:
  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == mDockWidget->getPosXInDock() && tabList[i].mDockWidgetList[0]->getPosYInDock() == mDockWidget->getPosYInDock()) // Ако вече има повече от един прозорец на тази позиция.
    {
      tabList[i].mDockWidgetList << mDockWidget; // Добавя прозореца към списъка с другите прозорци на тази позиция.
      return true;
    }
  }

  // Проверява, дали на тази позиция има един прозорец:
  for (int i = 0; i < mDockWidgetList.count(); i++)
  {
    if (mDockWidgetList[i] != mDockWidget && mDockWidgetList[i]->getPosXInDock() == mDockWidget->getPosXInDock() && mDockWidgetList[i]->getPosYInDock() == mDockWidget->getPosYInDock()) // Ако има един прозорец на тази позиция.
    {
      TabList tl;
      tl.mDockWidgetList << mDockWidgetList[i]; // Добавя първо прозореца, който вече съществува на тази позиция.
      tl.mDockWidgetList << mDockWidget; // Добавя и новия прозорец.
      tabList << tl;
      return true;
    }
  }
  return false; // Това означава, че прозорецът не участва в комбинация с други прозорци.
}

bool MDock::unregisterFromTabList(MDockWidget *mDockWidget)
{
  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == mDockWidget->getPosXInDock() && tabList[i].mDockWidgetList[0]->getPosYInDock() == mDockWidget->getPosYInDock()) // Ако този прозорец участва в комбинация с други прозорци.
    {
      if (tabList[i].mDockWidgetList.count() <= 2) // Ако са само 2 прозореца.
      {
        tabList.removeAt(i); // Изтрива целия списък.
      }
      else // Ако са повече от два прозореца.
      {
        tabList[i].mDockWidgetList.removeAll(mDockWidget); // Изтрива само този прозорец от списъка.
      }
      mDockWidget->setTabs(QStringList(), -1);
      return true;
    }
  }
  return false; // Това означава, че прозорецът не участва в комбинация с други прозорци.
}

void MDock::recombineTabbedDockWidgets(int posXInDock, int posYInDock)
{
  // Проверява, дали на тази позиция има повече от един регистриран прозорец:
  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == posXInDock && tabList[i].mDockWidgetList[0]->getPosYInDock() == posYInDock) // Ако на тази позиция има табове.
    {
      QStringList titles;
      for (int w = 0; w < tabList[i].mDockWidgetList.count(); w++) // Минава през всички прозорци на тази позиция.
      {
        titles << tabList[i].mDockWidgetList[w]->getDockWidgetTitle();
      }

      for (int w = 0; w < tabList[i].mDockWidgetList.count(); w++) // Минава през всички прозорци на тази позиция.
      {
        tabList[i].mDockWidgetList[w]->setTabs(titles, w);
      }
      return;
    }
  }

  // Проверява, дали на тази позиция има един прозорец, който евентуално е останал с показани табове, но не трябва да участва в комбинация с другите прозорци:
  for (int i = 0; i < mDockWidgetList.count(); i++)
  {
    if (mDockWidgetList[i]->getPosXInDock() == posXInDock && mDockWidgetList[i]->getPosYInDock() == posYInDock) // Ако има един прозорец на тази позиция.
    {
      mDockWidgetList[i]->setTabs(QStringList(), -1);
      //return; // Тук не трябва да се прекратява цикълът, защото премахнатият прозорец вече не съществува в списъка с табове и не е открит в горния цикъл.
    }
  }
}

QRect MDock::getDockWidgetGeometry(int posXInDock, int posYInDock)
{
  bool OK = true;
  if (posYInDock < 0 || posYInDock >= mDockRows) OK = false;
  if (posXInDock < 0 || posXInDock >= dockWidgetCount[posYInDock]) OK = false;

  if (OK)
    return QRect(spXpx[posYInDock][posXInDock]+mDockWidgetPadding,   spYpx[posYInDock]+mDockWidgetPadding,   spXpx[posYInDock][posXInDock+1]-spXpx[posYInDock][posXInDock]-mDockWidgetPadding-mDockWidgetPadding+1,   spYpx[posYInDock+1]-spYpx[posYInDock]-mDockWidgetPadding-mDockWidgetPadding+1);
  else
    return QRect(-200,-200,100,100);
}

bool MDock::insertRow(int row)
{
  if (row < 0) row = 0;
  if (row > mDockRows) row = mDockRows;

  QList<int> *spXprH = new QList<int>[mDockRows+1];
  for (int i = 0; i < mDockRows; i++)
  {
    spXprH[ (i >= row) ? (i+1) : i ] = spXpr[i];
  }
  spXprH[row] = QList<int>();

  if (mDockRows == 0) // Ако няма никакви редове.
  {
    spYpr.clear();
    spYpr << 0;
    spYpr << 100;
    dockWidgetCount.clear();
    dockWidgetCount << 0;
    delete[] spXpr;
    spXpr = new QList<int>[1]; // Това не е нужно, но да има...
    spXpr[0] << 0;             //
    spXpr[0] << 100;           //
  }
  else if (row == 0) // Ако е в началото.
  {
    spYpr[0] = (spYpr[1] - spYpr[0]) / 2; // Прави първия ред два-пъти по-малък (т.е. прави първия сплитер по средата на първия ред).
    spYpr.insert(0, 0); // Инсъртва нов начален сплитер.
    dockWidgetCount.insert(0, 0);
    delete[] spXpr;
    spXpr = spXprH;
  }
  else if (row == mDockRows) // Ако е в края.
  {
    spYpr[row] = 100 - (spYpr[row] - spYpr[row-1]) / 2; // Прави последния ред два-пъти по-малък (т.е. прави последния сплитер по средата на последния ред).
    spYpr << 100; // Добавя нов краен сплитер.
    dockWidgetCount << 0;
    delete[] spXpr;
    spXpr = spXprH;
  }
  else // Ако е между два реда.
  {
    spYpr.insert(row, spYpr[row]); // Инсъртва нов сплитер със същата позиция, като този, който трябва да се раздели за да се вмъкне новият ред.
    spYpr[row] = spYpr[row] - (spYpr[row] - spYpr[row-1]) / 3; // Прави горния ред 2/3 от големината му.
    spYpr[row+1] = spYpr[row+1] + (spYpr[row+2] - spYpr[row+1]) / 3; // Прави долния ред 2/3 от големината му.
    dockWidgetCount.insert(row, 0);
    delete[] spXpr;
    spXpr = spXprH;
  }
  mDockRows++;

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците (редовете).
  return true;
}

bool MDock::removeRow(int row)
{
  if (row < 0 || row >= mDockRows) return false;
  //if (dockWidgetCount[row] > 1) return false; // Ако в реда има повече от един прозорец. По-добре да не се прави тази проверка, а който вика този метод да си я прави.

  QList<int> *spXprH = new QList<int>[mDockRows-1];
  int k = 0;
  for (int i = 0; i < mDockRows; i++)
  {
    if (i != row) spXprH[k++] = spXpr[i];
  }

  if (mDockRows == 1) // Ако има само един ред.
  {
    // Изтрива реда, но създава нов, защото трябва винаги да има поне един ред с начални и крайни сплитери:
    spYpr.clear();
    spYpr << 0;   // Това не е нужно, но да има...
    spYpr << 100; //
    dockWidgetCount.clear();
    delete[] spXpr;
    spXpr = new QList<int>[1]; // Това не е нужно, но да има...
    spXpr[0] << 0;             //
    spXpr[0] << 100;           //
  }
  else if (row == 0) // Ако е в началото.
  {
    spYpr.removeFirst(); // Изтрива първия сплитер.
    spYpr[0] = 0; // Бившия втори сплитер го прави първи.
    dockWidgetCount.removeFirst();
    delete[] spXpr;
    spXpr = spXprH;
  }
  else if (row == (mDockRows-1)) // Ако е в края.
  {
    spYpr.removeAt(row); // Изтрива предпоследния сплитер.
    //spYpr.removeLast(); // Изтрива последния сплитер.
    //spYpr.removeLast(); // Изтрива предпоследния сплитер.
    //spYpr << 100; // Добавя нов последен сплитер.
    dockWidgetCount.removeAt(row);
    delete[] spXpr;
    spXpr = spXprH;
  }
  else // Ако е между два реда.
  {
    spYpr[row+1] = spYpr[row+1] - (spYpr[row+1] - spYpr[row]) / 2; // Премества долния сплитер по средата на реда, който ще се премахне.
    spYpr.removeAt(row); // Изтрива горния сплитер.
    dockWidgetCount.removeAt(row);
    delete[] spXpr;
    spXpr = spXprH;
  }
  mDockRows--;

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците (редовете).
  return true;
}

bool MDock::insertDockWidget(int row, int dockPos)
{
  if (row < 0 || row >= mDockRows) return false;
  if (dockPos < 0) dockPos = 0;
  if (dockPos > dockWidgetCount[row]) dockPos = dockWidgetCount[row];

  if (dockWidgetCount[row] == 0) // Ако няма никакви прозорци.
  {
    spXpr[row].clear();
    spXpr[row] << 0;
    spXpr[row] << 100;
  }
  else if (dockPos == 0) // Ако е в началото.
  {
    spXpr[row][0] = (spXpr[row][1] - spXpr[row][0]) / 2; // Прави първия прозорец два-пъти по-малък (т.е. прави първия сплитер по средата на първия прозорец).
    spXpr[row].insert(0, 0); // Инсъртва нов начален сплитер.
  }
  else if (dockPos == dockWidgetCount[row]) // Ако е в края.
  {
    spXpr[row][dockPos] = 100 - (spXpr[row][dockPos] - spXpr[row][dockPos-1]) / 2; // Прави последния прозорец два-пъти по-малък (т.е. прави последния сплитер по средата на последния прозорец).
    spXpr[row] << 100; // Добавя нов краен сплитер.
  }
  else // Ако е между два прозореца.
  {
    spXpr[row].insert(dockPos, spXpr[row][dockPos]); // Инсъртва нов сплитер със същата позиция, като този, който трябва да се раздели за да се вмъкне новият прозорец.
    spXpr[row][dockPos] = spXpr[row][dockPos] - (spXpr[row][dockPos] - spXpr[row][dockPos-1]) / 3; // Прави левия прозорец 2/3 от големината му.
    spXpr[row][dockPos+1] = spXpr[row][dockPos+1] + (spXpr[row][dockPos+2] - spXpr[row][dockPos+1]) / 3; // Прави десния прозорец 2/3 от големината му.
  }
  dockWidgetCount[row]++;

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците.
  return true;
}

bool MDock::removeDockWidget(int row, int dockPos)
{
  if (row < 0 || row >= mDockRows) return false;
  if (dockWidgetCount[row] <= 0) return false;
  if (dockPos < 0) return false;
  if (dockPos >= dockWidgetCount[row]) return false;

  if (dockWidgetCount[row] == 1) // Ако има само един прозорец.
  {
    spXpr[row].clear();
    spXpr[row] << 0;   // Това не е нужно, но да има...
    spXpr[row] << 100; //
  }
  else if (dockPos == 0) // Ако е в началото.
  {
    spXpr[row].removeFirst(); // Изтрива първия сплитер.
    spXpr[row][0] = 0; // Бившия втори сплитер го прави първи.
  }
  else if (dockPos == (dockWidgetCount[row]-1)) // Ако е в края.
  {
    spXpr[row].removeAt(dockPos); // Изтрива предпоследния сплитер.
    //spXpr[row].removeLast(); // Изтрива последния сплитер.
    //spXpr[row].removeLast(); // Изтрива предпоследния сплитер.
    //spXpr[row] << 100; // Добавя нов последен сплитер.
  }
  else // Ако е между два прозореца.
  {
    spXpr[row][dockPos+1] = spXpr[row][dockPos+1] - (spXpr[row][dockPos+1] - spXpr[row][dockPos]) / 2; // Премества десния сплитер по средата на прозореца, който ще се премахне.
    spXpr[row].removeAt(dockPos); // Изтрива левия сплитер.
  }
  dockWidgetCount[row]--;

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците.
  return true;
}

bool MDock::moveRow(int currPos, int newPos)
{
  if (currPos < 0) return false;
  if (currPos >= mDockRows) return false;
  if (newPos < 0) return false;
  if (newPos >= mDockRows) return false;
  if (currPos == newPos) return true;

  // Преместването на реда ще стане, като един или няколко пъти размества
  // местата на два съседни реда, докато редът отиде на желаното място:
  if (newPos > currPos) // Преместване надолу.
  {
    for (int i = 0; i < (newPos - currPos); i++)
    {
      int r1 = spYpr[currPos+i+1] - spYpr[currPos+i];   // Височината на горния ред.
      int r2 = spYpr[currPos+i+2] - spYpr[currPos+i+1]; // Височината на долния ред.
      spYpr[currPos+i+1] += r2 - r1; // С колко позиции трябва да се отмести сплитерът между въпросните два реда.

      QList<int> spXprH = spXpr[currPos+i];
      spXpr[currPos+i] = spXpr[currPos+i+1];
      spXpr[currPos+i+1] = spXprH;

      int dockWidgetCountH = dockWidgetCount[currPos+i];
      dockWidgetCount[currPos+i] = dockWidgetCount[currPos+i+1];
      dockWidgetCount[currPos+i+1] = dockWidgetCountH;
    }
  }
  else // Преместване нагоре.
  {
    for (int i = 0; i < (currPos - newPos); i++)
    {
      int r1 = spYpr[currPos-i+1] - spYpr[currPos-i]; // Височината на долния ред.
      int r2 = spYpr[currPos-i] - spYpr[currPos-i-1]; // Височината на горния ред.
      spYpr[currPos-i] += r1 - r2; // С колко позиции трябва да се отмести сплитерът между въпросните два реда.

      QList<int> spXprH = spXpr[currPos-i];
      spXpr[currPos-i] = spXpr[currPos-i-1];
      spXpr[currPos-i-1] = spXprH;

      int dockWidgetCountH = dockWidgetCount[currPos-i];
      dockWidgetCount[currPos-i] = dockWidgetCount[currPos-i-1];
      dockWidgetCount[currPos-i-1] = dockWidgetCountH;
    }
  }

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците (редовете).
  return true;
}

bool MDock::moveDockWidget(int row, int currPos, int newPos)
{
  if (row < 0 || row >= mDockRows) return false;
  if (dockWidgetCount[row] < 2) return false;
  if (currPos < 0) return false;
  if (currPos >= dockWidgetCount[row]) return false;
  if (newPos < 0) return false;
  if (newPos >= dockWidgetCount[row]) return false;
  if (currPos == newPos) return true;

  // Преместването на прозореца ще стане, като един или няколко пъти размества
  // местата на два съседни прозореца, докато прозорецът отиде на желаното място:
  if (newPos > currPos) // Преместване надясно.
  {
    for (int i = 0; i < (newPos - currPos); i++)
    {
      int w1 = spXpr[row][currPos+i+1] - spXpr[row][currPos+i];   // Широчината на левия прозорец.
      int w2 = spXpr[row][currPos+i+2] - spXpr[row][currPos+i+1]; // Широчината на десния прозорец.
      spXpr[row][currPos+i+1] += w2 - w1; // С колко позиции трябва да се отмести сплитерът между въпросните два прозореца.
    }
  }
  else // Преместване наляво.
  {
    for (int i = 0; i < (currPos - newPos); i++)
    {
      int w1 = spXpr[row][currPos-i+1] - spXpr[row][currPos-i]; // Широчината на десния прозорец.
      int w2 = spXpr[row][currPos-i] - spXpr[row][currPos-i-1]; // Широчината на левия прозорец.
      spXpr[row][currPos-i] += w1 - w2; // С колко позиции трябва да се отмести сплитерът между въпросните два прозореца.
    }
  }

  //recalculateGrid(); // Това ще предизвика преоразмеряване (изискващо време), но е излишно, защото този метод ще се извика отново след разместването на прозорците.
  return true;
}

bool MDock::setSpYpx(int splitter, int splitterPos)
{
  if (splitter <= 0 || splitter >= (spYpx.count()-1)) return false;

  spYpr[splitter] = ((splitterPos-mDockGeometry.top()) * 100) / (mDockGeometry.height()-1); // percent = (pixels / height) * 100      pixels = (percent * height) / 100
  if ((spYpr[splitter] - spYpr[splitter-1]) <= mDockWidgetMinSizePr.height()) spYpr[splitter] = spYpr[splitter-1] + mDockWidgetMinSizePr.height();
  else if ((spYpr[splitter+1] - spYpr[splitter]) <= mDockWidgetMinSizePr.height()) spYpr[splitter] = spYpr[splitter+1] - mDockWidgetMinSizePr.height();

  recalculateGrid();
  return true;
}

bool MDock::setSpXpx(int row, int splitter, int splitterPos)
{
  if (row < 0 || row >= mDockRows) return false;
  if (splitter <= 0 || splitter >= (spXpx[row].count()-1)) return false;

  spXpr[row][splitter] = ((splitterPos-mDockGeometry.left()) * 100) / (mDockGeometry.width()-1); // percent = (pixels / width) * 100      pixels = (percent * width) / 100
  if ((spXpr[row][splitter] - spXpr[row][splitter-1]) <= mDockWidgetMinSizePr.width()) spXpr[row][splitter] = spXpr[row][splitter-1] + mDockWidgetMinSizePr.width();
  else if ((spXpr[row][splitter+1] - spXpr[row][splitter]) <= mDockWidgetMinSizePr.width()) spXpr[row][splitter] = spXpr[row][splitter+1] - mDockWidgetMinSizePr.width();

  recalculateGrid();
  return true;
}

int MDock::getSpYpx(int splitter)
{
  if (splitter < 0 || splitter >= spYpx.count()) return -1;
  return spYpx[splitter];
}

int MDock::getSpXpx(int row, int splitter)
{
  if (row < 0 || row >= mDockRows) return -1;
  if (splitter < 0 || splitter >= spXpx[row].count()) return -1;
  return spXpx[row][splitter];
}

int MDock::getSpYpr(int splitter)
{
  if (splitter < 0 || splitter >= spYpx.count()) return -1;
  return spYpr[splitter];
}

int MDock::getSpXpr(int row, int splitter)
{
  if (row < 0 || row >= mDockRows) return -1;
  if (splitter < 0 || splitter >= spXpx[row].count()) return -1;
  return spXpr[row][splitter];
}

void MDock::recalculateGrid()
{
  mDockGeometry = QRect(mDockMargins.left() - mDockWidgetPadding, mDockMargins.top() - mDockWidgetPadding, width() - mDockMargins.left() - mDockMargins.right() + (2*mDockWidgetPadding), height() - mDockMargins.top() - mDockMargins.bottom() + (2*mDockWidgetPadding));

  // Инициализиране:
  spYpx.clear();
  delete[] spXpx;
  spXpx = new QList<int>[mDockRows];
  spYpx << 0;
  for (int i = 0; i < mDockRows; i++)
  {
    spYpx << 0;
    for (int j = 0; j < spXpr[i].count(); j++)
    {
      spXpx[i] << 0;
    }
  }

  // Изчисляване на процентите в пиксели:
  for (int i = 0; i < spYpr.count(); i++)
  {
    spYpx[i] = (spYpr[i] * (mDockGeometry.height()-1)) / 100 + mDockGeometry.top(); // percent = (pixels / height) * 100      pixels = (percent * height) / 100
  }

  for (int i = 0; i < mDockRows; i++)
  {
    for (int j = 0; j < spXpr[i].count(); j++)
    {
      spXpx[i][j] = (spXpr[i][j] * (mDockGeometry.width()-1)) / 100 + mDockGeometry.left(); // percent = (pixels / width) * 100      pixels = (percent * width) / 100
    }
  }

  for (int i = 0; i < mDockWidgetList.count(); i++)
  {
    mDockWidgetList[i]->resizeWidget();
  }



//  QString res = ""; // 0^25^50^75^100_1^4^2^1_0^100_0^10^30^55^100_0^50^100_0^100 // Частта преди първата долна черта се отнася за сплитерите по вертикала (редовете). Следващата част е броят на прозорците на всеки ред. Останалите са за сплитерите по хоризонтала за всеки ред.
//  for (int i = 0; i < spYpx.count(); i++)
//  {
//    res += QString("%1").arg(spYpx[i]);
//    if (i < spYpx.count()-1) res += "^";
//  }
//  res += "_";
//  for (int i = 0; i < dockWidgetCount.count(); i++)
//  {
//    res += QString("%1").arg(dockWidgetCount[i]);
//    if (i < dockWidgetCount.count()-1) res += "^";
//  }
//  res += "_";
//  for (int i = 0; i < dockRows; i++)
//  {
//    for (int j = 0; j < spXpx[i].count(); j++)
//    {
//      res += QString("%1").arg(spXpx[i][j]);
//      if (j < spXpx[i].count()-1) res += "^";
//    }
//    if (i < dockRows-1) res += "_";
//  }
//  qDebug() << res;
}

void MDock::dockWidgetClosed(MDockWidget *dockWidget)
{
  int posXInDock = dockWidget->getPosXInDock();
  int posYInDock = dockWidget->getPosYInDock();

  if (unregisterFromTabList(dockWidget)) // Проверява дали участва в табове с други прозорци.
  {
    recombineTabbedDockWidgets(posXInDock, posYInDock); // Премахва таба.
  }
  else // Ако няма друг прозорец на тази позиция.
  {
    if (removeDockWidget(posYInDock, posXInDock)) // Ако прозорецът е бил изтрит успешно.
    {
      for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се изтрива).
      {
        if (mDockWidgetList[i]->getPosYInDock() == posYInDock && mDockWidgetList[i]->getPosXInDock() > posXInDock) // Ако този прозорец е в дясно от изтрития, на същия ред.
        {
          mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()-1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след изтрития с една позиция наляво.
        }
      }
    }

    if (dockWidgetCount[posYInDock] == 0) // Ако е останал празен ред.
    {
      if (removeRow(posYInDock)) // Ако празният ред е изтрит успешно.
      {
        for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се изтрива).
        {
          if (mDockWidgetList[i]->getPosYInDock() > posYInDock) // Ако този прозорец е под изтрития ред.
          {
            mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()-1); // Премества всички прозорци след изтрития ред с една позиция нагоре.
          }
        }
      }
    }

    recalculateGrid();
  }

  mDockWidgetList.removeAll(dockWidget); // Премахва прозореца от списъка.

#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor); // Това е необходимо, защото ако е щракнато с мишката върху бутона на затваряне, след затваряне на прозореца курсорът става стрелка за преместване.
#endif
  //qDebug("~~~~ remove");
}

void MDock::dockWidgetMoving(MDockWidget *dockWidget, int mouseX, int mouseY, bool done)
{
  if (!allowMoveDockWidgets) return;

  int mouseXpr = ((mouseX-mDockGeometry.left()) * 100) / (mDockGeometry.width()-1); // percent = (pixels / width) * 100      pixels = (percent * width) / 100
  int mouseYpr = ((mouseY-mDockGeometry.top()) * 100) / (mDockGeometry.height()-1); // percent = (pixels / height) * 100     pixels = (percent * height) / 100
  int onePrX = mDockGeometry.width() / 100; // Колко пиксела заема 1% по X.
  int onePrY = mDockGeometry.height() / 100; // Колко пиксела заема 1% по Y.
  bool localized = false;
  QRect dockWidgetGeometry;
  int selectedSpY = -1; // Указва селектирания сплитер по Y, ако има такъв, ако няма = -1.
  int selectedSpX = -1; // Указва селектирания сплитер по X, ако има такъв, ако няма = -1.
  int selectedRow = -1; // Указва селектирания ред, ако няма = -1.
  int selectedWin = -1; // Указва селектирания прозорец, ако има такъв, ако няма = -1.

  // Определя местоположението на мишката по Y - дали е в близост до хоризонтален сплитер:
  for (int y = 0; y <= getRowCount(); y++)
  {
    if (mouseX >= 0 && mouseX <= width() && mouseYpr >= (getSpYpr(y)-1) && mouseYpr <= (getSpYpr(y)+1)) // Ако е на 1% преди или след хоризонталния сплитер.
    {
      trackFrame->setGeometry(QRect(mDockMargins.left(),   getSpYpx(y)-2*onePrY-mDockWidgetPadding/2,   width()-mDockMargins.left()-mDockMargins.right(),   4*onePrY+mDockWidgetPadding));
      trackFrame->raise();
      selectedSpY = y;
      selectedSpX = -1;
      localized = true;
      break;
    }
  }

  if (!localized) // Ако мишката е далеч от хоризонтален сплитер.
  {
    // Определя в кой ред е мишката:
    for (int y = 1; y <= getRowCount(); y++)
    {
      if (mouseY <= getSpYpx(y))
      {
        selectedRow = y-1;
        break;
      }
    }

    if (selectedRow >= 0)
    {
      // Определя местоположението на мишката по X - дали е в близост до вертикален сплитер:
      for (int x = 0; x <= dockWidgetCount[selectedRow]; x++)
      {
        if (mouseY >= getDockWidgetGeometry(x, selectedRow).y() && mouseXpr >= (getSpXpr(selectedRow, x)-1) && mouseXpr <= (getSpXpr(selectedRow, x)+1)) // Ако е на 1% преди или след вертикалния сплитер.
        {
          trackFrame->setGeometry(QRect(getSpXpx(selectedRow, x)-2*onePrX-mDockWidgetPadding/2,   getSpYpx(selectedRow)+mDockWidgetPadding,   4*onePrX+mDockWidgetPadding,   getSpYpx(selectedRow+1)-getSpYpx(selectedRow)-2*mDockWidgetPadding+1));
          trackFrame->raise();
          selectedSpY = -1;
          selectedSpX = x;
          localized = true;
          break;
        }
      }

      if (!localized && allowTabbedDockWidgets) // Ако мишката е далеч от вертикален сплитер и е разрешено прозорците да се обединяват в табове.
      {
        // Определя местоположението на мишката по X - дали е в прозорец, далеч от сплитери:
        for (int x = 1; x <= dockWidgetCount[selectedRow]; x++)
        {
          dockWidgetGeometry = getDockWidgetGeometry(x-1, selectedRow);
          if (mouseY >= dockWidgetGeometry.y() && mouseX >= dockWidgetGeometry.x() && mouseX <= (dockWidgetGeometry.x() + dockWidgetGeometry.width())) // Ако е в конкретен прозорец.
          {
            trackFrame->setGeometry(dockWidgetGeometry);
            trackFrame->raise();
            selectedSpY = -1;
            selectedSpX = -1;
            selectedWin = x-1;
            localized = true;
            break;
          }
        }
      }
    }
  }

  if (!localized) // Ако мишката не е на нито едно от горните места (когато е извън рамките на прозореца).
  {
    trackFrame->setGeometry(QRect(-100, -100, 10, 10)); // Скрива рамката.
    return;
  }

  // ======= Местене на прозореца =======

  if (done)
  {
    trackFrame->setGeometry(QRect(-100, -100, 10, 10)); // Скрива рамката.
    //qDebug() << "-- Window Move:  selectedSpY=" << selectedSpY << "  selectedSpX=" << selectedSpX << "  selectedRow=" << selectedRow << "  selectedWin=" << selectedWin;

    int currPosXInDock = dockWidget->getPosXInDock();
    int currPosYInDock = dockWidget->getPosYInDock();
    bool isTabbed = (dockWidget->getTabIndex() >= 0); // Запомня дали прозорецът участва в комбинация в табове.

    if (selectedSpY >= 0 && selectedSpX == -1) // Ако е посочен хоризонтален сплитер. ---------------------------------------------------------------------------------------------
    {
      if (isTabbed) // Ако прозорецът е в таб. -----------------------------------------------------------------------------------
      {
        if (insertRow(selectedSpY) && insertDockWidget(selectedSpY, 0)) // Ако редът е бил добавен успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
          {
            if (mDockWidgetList[i]->getPosYInDock() >= selectedSpY) // Ако този прозорец е под новия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()+1); // Премества всички прозорци след новия ред с една позиция надолу.
            }
          }
        }
        if (unregisterFromTabList(dockWidget)) // Проверява дали участва в табове с други прозорци и го премахва от там.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на останалите прозорци на тази позиция (ако има табове).
        }
        dockWidget->setPosInDock(0, selectedSpY); // Премества прозореца.
      }
      else if (dockWidgetCount[currPosYInDock] == 1) // Ако прозорецът е единствен на този ред. ----------------------------------
      {
        if (selectedSpY == currPosYInDock || selectedSpY == (currPosYInDock+1)) return; // Ако е посочен съседен на прозореца сплитер (отгоре или отдолу).
        int newPosYInDock = (selectedSpY < currPosYInDock) ? selectedSpY : (selectedSpY-1);

        if (moveRow(currPosYInDock, newPosYInDock)) // Премества реда.
        {
          if (newPosYInDock < currPosYInDock) // Ако редът е преместен нагоре.
          {
            for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
            {
              if (mDockWidgetList[i]->getPosYInDock() >= newPosYInDock && mDockWidgetList[i]->getPosYInDock() <= currPosYInDock) // Ако този прозорец е под новия и над стария ред.
              {
                mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()+1); // Премества всички прозорци между новото и старото място на реда с една позиция надолу.
              }
            }
          }
          else // Ако редът е преместен надолу.
          {
            for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
            {
              if (mDockWidgetList[i]->getPosYInDock() >= currPosYInDock && mDockWidgetList[i]->getPosYInDock() <= newPosYInDock) // Ако този прозорец е под стария и над новия ред.
              {
                mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()-1); // Премества всички прозорци между новото и старото място на реда с една позиция нагоре.
              }
            }
          }
        }
        dockWidget->setPosInDock(0, newPosYInDock); // Премества прозореца.
      }
      else if (dockWidgetCount[currPosYInDock] >= 1) // Ако прозорецът не е единствен на този ред. -------------------------------
      {
        if (removeDockWidget(currPosYInDock, currPosXInDock)) // Ако прозорецът е бил изтрит успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се мести).
          {
            if (mDockWidgetList[i]->getPosYInDock() == currPosYInDock && mDockWidgetList[i]->getPosXInDock() > currPosXInDock) // Ако този прозорец е в дясно от местения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()-1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след местения с една позиция наляво.
            }
          }
        }
        if (insertRow(selectedSpY) && insertDockWidget(selectedSpY, 0)) // Ако редът е бил добавен успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
          {
            if (mDockWidgetList[i]->getPosYInDock() >= selectedSpY) // Ако този прозорец е под новия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()+1); // Премества всички прозорци след новия ред с една позиция надолу.
            }
          }
        }
        dockWidget->setPosInDock(0, selectedSpY); // Премества прозореца.
      }
      recalculateGrid();
    }
    else if (selectedSpY == -1 && selectedSpX >= 0) // Ако е посочен вертикален сплитер. ------------------------------------------------------------------------------------------
    {
      if (isTabbed) // Ако прозорецът е в таб. -----------------------------------------------------------------------------------
      {
        if (insertDockWidget(selectedRow, selectedSpX)) // Ако прозорецът е бил добавен успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
          {
            if (mDockWidgetList[i]->getPosYInDock() == selectedRow && mDockWidgetList[i]->getPosXInDock() >= selectedSpX) // Ако този прозорец е в дясно от добавения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след добавения с една позиция надясно.
            }
          }
        }
        if (unregisterFromTabList(dockWidget)) // Проверява дали участва в табове с други прозорци и го премахва от там.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на останалите прозорци на тази позиция (ако има табове).
        }
        dockWidget->setPosInDock(selectedSpX, selectedRow); // Премества прозореца.
      }
      else if (currPosYInDock == selectedRow) // Ако прозорецът ще остане на същия ред. ------------------------------------------
      {
        if (selectedSpX == currPosXInDock || selectedSpX == (currPosXInDock+1)) return; // Ако е посочен съседен на прозореца сплитер (отляво или отдясно).
        int newPosXInDock = (selectedSpX < currPosXInDock) ? selectedSpX : (selectedSpX-1);

        if (moveDockWidget(selectedRow, currPosXInDock, newPosXInDock)) // Премества прозореца.
        {
          if (newPosXInDock < currPosXInDock) // Ако прозорецът е преместен наляво.
          {
            for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
            {
              if (mDockWidgetList[i]->getPosYInDock() == selectedRow && mDockWidgetList[i]->getPosXInDock() >= newPosXInDock && mDockWidgetList[i]->getPosXInDock() <= currPosXInDock) // Ако този прозорец е след новия и преди стария ред.
              {
                mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци между новото и старото място на реда с една позиция наляво.
              }
            }
          }
          else // Ако прозорецът е преместен надясно.
          {
            for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
            {
              if (mDockWidgetList[i]->getPosYInDock() == selectedRow && mDockWidgetList[i]->getPosXInDock() >= currPosXInDock && mDockWidgetList[i]->getPosXInDock() <= newPosXInDock) // Ако този прозорец е след стария и преди новия ред.
              {
                mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()-1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци между новото и старото място на реда с една позиция надясно.
              }
            }
          }
        }
        dockWidget->setPosInDock(newPosXInDock, selectedRow); // Премества прозореца.
      }
      else if (dockWidgetCount[currPosYInDock] == 1) // Ако прозорецът ще се мести на друг ред и е единствен на този ред. --------
      {
        if (insertDockWidget(selectedRow, selectedSpX)) // Ако прозорецът е бил добавен успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
          {
            if (mDockWidgetList[i]->getPosYInDock() == selectedRow && mDockWidgetList[i]->getPosXInDock() >= selectedSpX) // Ако този прозорец е в дясно от добавения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след добавения с една позиция надясно.
            }
          }
        }
        dockWidget->setPosInDock(selectedSpX, selectedRow); // Премества прозореца.
        if (removeRow(currPosYInDock)) // Ако празният ред е изтрит успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се мести).
          {
            if (mDockWidgetList[i]->getPosYInDock() > currPosYInDock) // Ако този прозорец е под изтрития ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()-1); // Премества всички прозорци след изтрития ред с една позиция нагоре.
            }
          }
        }
      }
      else if (dockWidgetCount[currPosYInDock] >= 1) // Ако прозорецът ще се мести на друг ред и не е единствен на този ред. -----
      {
        if (removeDockWidget(currPosYInDock, currPosXInDock)) // Ако прозорецът е бил изтрит успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се мести).
          {
            if (mDockWidgetList[i]->getPosYInDock() == currPosYInDock && mDockWidgetList[i]->getPosXInDock() > currPosXInDock) // Ако този прозорец е в дясно от местения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()-1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след местения с една позиция наляво.
            }
          }
        }
        if (insertDockWidget(selectedRow, selectedSpX)) // Ако прозорецът е бил добавен успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци.
          {
            if (mDockWidgetList[i]->getPosYInDock() == selectedRow && mDockWidgetList[i]->getPosXInDock() >= selectedSpX) // Ако този прозорец е в дясно от добавения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()+1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след добавения с една позиция надясно.
            }
          }
        }
        dockWidget->setPosInDock(selectedSpX, selectedRow); // Премества прозореца.
      }
      recalculateGrid();
    }
    else if (selectedSpY == -1 && selectedSpX == -1 && selectedWin >= 0) // Ако е посочен прозорец. -------------------------------------------------------------------------------
    {
      if (dockWidget->getPosYInDock() == selectedRow && dockWidget->getPosXInDock() == selectedWin)  return; // Ако е посочено мястото на същия прозорец.

      if (isTabbed) // Ако прозорецът е в таб. -----------------------------------------------------------------------------------
      {
        if (unregisterFromTabList(dockWidget)) // Проверява дали участва в табове с други прозорци и го премахва от там.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на останалите прозорци на тази позиция (ако има табове).
        }
        dockWidget->setPosInDock(selectedWin, selectedRow); // Премества прозореца.
        if (registerToTabList(dockWidget)) // Комбинира прозореца с друг прозорец в табове.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на прозорците на новата позиция.
          dockWidget->raise();
        }
      }
      else if (dockWidgetCount[currPosYInDock] == 1) // Ако прозорецът е единствен на този ред. ----------------------------------
      {
        dockWidget->setPosInDock(selectedWin, selectedRow); // Премества прозореца.
        if (registerToTabList(dockWidget)) // Комбинира прозореца с друг прозорец в табове.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на прозорците на новата позиция.
          dockWidget->raise();
        }
        if (removeRow(currPosYInDock)) // Ако празният ред е изтрит успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се мести).
          {
            if (mDockWidgetList[i]->getPosYInDock() > currPosYInDock) // Ако този прозорец е под изтрития ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock(), mDockWidgetList[i]->getPosYInDock()-1); // Премества всички прозорци след изтрития ред с една позиция нагоре.
            }
          }
        }
      }
      else if (dockWidgetCount[currPosYInDock] >= 1) // Ако прозорецът не е единствен на този ред. -------------------------------
      {
        dockWidget->setPosInDock(selectedWin, selectedRow); // Премества прозореца.
        if (registerToTabList(dockWidget)) // Комбинира прозореца с друг прозорец в табове.
        {
          recombineTabbedDockWidgets(dockWidget->getPosXInDock(), dockWidget->getPosYInDock()); // Преизчертава табовете на прозорците на новата позиция.
          dockWidget->raise();
        }
        if (removeDockWidget(currPosYInDock, currPosXInDock)) // Ако прозорецът е бил изтрит успешно.
        {
          for (int i = 0; i < mDockWidgetList.count(); i++) // Минава през всички прозорци (включително и през този, който се мести).
          {
            if (mDockWidgetList[i]->getPosYInDock() == currPosYInDock && mDockWidgetList[i]->getPosXInDock() > currPosXInDock) // Ако този прозорец е в дясно от местения, на същия ред.
            {
              mDockWidgetList[i]->setPosInDock(mDockWidgetList[i]->getPosXInDock()-1, mDockWidgetList[i]->getPosYInDock()); // Премества всички прозорци след местения с една позиция наляво.
            }
          }
        }
      }
      recalculateGrid();
    }
  }

  //qDebug() << "-- Window Move:  " << mouseXpr << mouseYpr << mouseX << mouseY << selectedRow;
}

void MDock::dockWidgetTabPressed(MDockWidget *dockWidget, int tabIndex)
{
  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == dockWidget->getPosXInDock() && tabList[i].mDockWidgetList[0]->getPosYInDock() == dockWidget->getPosYInDock()) // Ако това е търсената група прозорци.
    {
      if (tabIndex >= 0 && tabIndex < tabList[i].mDockWidgetList.count())
      {
        tabList[i].mDockWidgetList[tabIndex]->raise();
        //if (tabList[i].mDockWidgetList[tabIndex]->getWidget() != 0) tabList[i].mDockWidgetList[tabIndex]->getWidget()->setFocus(); // Това не работи добре под Ubuntu - ако Widget-а е QTextBrowser, при setFocus се получава скрол към мястото където е курсорът т.е. където е било щракнато с мишката.
        return;
      }
    }
  }
}

void MDock::dockWidgetTitleBarMouseDoubleClick(MDockWidget *dockWidget)
{
  if (!allowMaximizeDockWidgets) return;

  dockWidget->dockWidgetMaximized = !dockWidget->dockWidgetMaximized;

  for (int i = 0; i < tabList.count(); i++)
  {
    if (tabList[i].mDockWidgetList[0]->getPosXInDock() == dockWidget->getPosXInDock() && tabList[i].mDockWidgetList[0]->getPosYInDock() == dockWidget->getPosYInDock()) // Ако на тази позиция има табове.
    {
      for (int w = 0; w < tabList[i].mDockWidgetList.count(); w++) // Минава през всички прозорци на тази позиция.
      {
        tabList[i].mDockWidgetList[w]->dockWidgetMaximized = dockWidget->dockWidgetMaximized;
      }
      break;
    }
  }

  dockWidget->raise();
  //if (object->getWidget() != 0) object->getWidget()->setFocus(); // Това не работи добре под Ubuntu - ако Widget-а е QTextBrowser, при setFocus се получава скрол към мястото, където е курсорът т.е. където е било щракнато с мишката.
  recalculateGrid();
}

void MDock::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  recalculateGrid();
}

void MDock::mouseMoveEvent(QMouseEvent *event)
{
  QWidget::mouseMoveEvent(event);
  //qDebug() << "Splitter Move " << event->x() << event->y();

  if (allowMoveSplitters)
  {
    if (selectedSplitterX >= 0 && selectedSplitterY >= 0) // Движение на вертикален сплитер (между прозорци).
    {
#ifndef QT_NO_CURSOR
      setCursor(Qt::SizeHorCursor);
#endif
      setSpXpx(selectedSplitterY, selectedSplitterX, event->x());
      QToolTip::showText(QCursor::pos(), QString("%1%").arg(getSpXpr(selectedSplitterY, selectedSplitterX)));
    }
    else if (selectedSplitterX == -1 && selectedSplitterY >= 0) // Движение на хоризонтален сплитер (между редове).
    {
#ifndef QT_NO_CURSOR
      setCursor(Qt::SizeVerCursor);
#endif
      setSpYpx(selectedSplitterY, event->y());
      QToolTip::showText(QCursor::pos(), QString("%1%").arg(getSpYpr(selectedSplitterY)));
    }
  }
}

void MDock::mousePressEvent(QMouseEvent *event)
{
  QWidget::mousePressEvent(event);
  //qDebug() << "Mouse Press" << event->x() << event->y();

  if (allowMoveSplitters)
  {
    trackFrame->lower();
    trackFrame->setGeometry(QRect(-1, -1, width()+2, height()+2)); // Показва рамката на зададен план и така осветява само сплитерите.

    // Определя дали е избран хоризонтален сплитер (между редове):
    for (int y = 1; y < getRowCount(); y++)
    {
      if (event->y() >= (getSpYpx(y) - mDockWidgetPadding) && event->y() <= (getSpYpx(y) + mDockWidgetPadding))
      {
        selectedSplitterY = y;
        selectedSplitterX = -1;
        //qDebug() << "selectedSplitterY = " << selectedSplitterY << "     selectedSplitterX = " << selectedSplitterX;
        QToolTip::showText(QCursor::pos(), QString("%1%").arg(getSpYpr(selectedSplitterY)));
        return;
      }
    }

    // Определя дали е избран вертикален сплитер (между прозорци):
    for (int y = 0; y < getRowCount(); y++)
    {
      for (int x = 1; x < getDockWidgetCount(y); x++)
      {
        if (event->y() >= getSpYpx(y) && event->y() <= getSpYpx(y+1) && event->x() >= (getSpXpx(y, x) - mDockWidgetPadding) && event->x() <= (getSpXpx(y, x) + mDockWidgetPadding))
        {
          selectedSplitterY = y;
          selectedSplitterX = x;
          //qDebug() << "selectedSplitterY = " << selectedSplitterY << "     selectedSplitterX = " << selectedSplitterX;
          QToolTip::showText(QCursor::pos(), QString("%1%").arg(getSpXpr(selectedSplitterY, selectedSplitterX)));
          return;
        }
      }
    }

    // Избран е начален или краен сплитер, който не може да се мести:
    selectedSplitterY = -1;
    selectedSplitterX = -1;
    //qDebug() << "selectedSplitterY = " << selectedSplitterY << "     selectedSplitterX = " << selectedSplitterX;
  }
}

void MDock::mouseReleaseEvent(QMouseEvent *event)
{
  QWidget::mouseReleaseEvent(event);
  trackFrame->setGeometry(QRect(-100, -100, 10, 10)); // Скрива рамката.
  //qDebug() << "Mouse Release" << event->x() << event->y();
#ifndef QT_NO_CURSOR
  setCursor(Qt::SizeBDiagCursor); // Qt::SizeAllCursor
#endif
}

// -----------------------------------------------------------------------------------------------------------------------------------

MDockWidget::MDockWidget(MDock *mDock, const QString dockWidgetTitle, const bool dockWidgetShowNewButton, const bool dockWidgetShowMaximizeButton, const bool dockWidget3DTitleBar, const int dockWidgetID, const quint8 dockWidgetType) : QWidget(mDock)
{
  this->mDock = mDock;
  this->dockWidget3DTitleBar = dockWidget3DTitleBar;
  this->dockWidgetID = dockWidgetID;
  this->dockWidgetType = dockWidgetType;
  dockWidgetTitleBarColor = QColor(235, 235, 235);
  dockWidgetTitleBarTextColor = this->mDock->getDockBgColor();
  dockWidgetTitleBarButtonColor = this->mDock->getDockBgColor();
  dockWidgetBgColor = QColor(235, 235, 235);
  dockWidgetMaximized = false;
  dockWidgetDisallowCloseLevel1 = false;
  dockWidgetDisallowCloseLevel2 = false;
  dockWidgetDisallowCloseFromButton = false;
  dockWidgetTabPressed = false;
  dockWidgetMoving = false;
  currentMSecs = QDateTime::currentMSecsSinceEpoch();
  posYInDock = -1;
  posXInDock = -1;
  tabIndex = -1;

  //setLayoutDirection(Qt::RightToLeft); // Qt::RightToLeft  Qt::LeftToRight

  titleBar = new BLabel(" ", false, dockWidget3DTitleBar); // Тук трябва да има интервал в етикета, за да може да се преоразмерява правилно.
  titleBar->setMargin(2);
  titleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  titleBar_Label = new QLabel(dockWidgetTitle, titleBar);
  titleBar_Label->setMargin(2);
  titleBar_Label->setIndent(1);
  titleBar_Label->setFont(titleBar->font());
  titleBar_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  titleBar_Label->setTextFormat(Qt::RichText); // Това указва текстът на заглавната лента да се третира винаги като HTML. По подразбиране е Qt::AutoText, което прави проверка на текста какъв е и според проверката решава дали да го покаже като HTML или като Qt::PlainText.
  titleBar_Label->setOpenExternalLinks(false); // Това не знам дали е нужно, но ако в заглавната лента се появи линк, да не разрешава отварянето му в браузър.
  titleBar_Label->setTextInteractionFlags(Qt::NoTextInteraction); // Това е много нужно, защото когато текст-формата е Qt::RichText, се блокират някои от ивентите на етикета (свързани с кликването с мишката) и заглавната лента не може да се използва за преместване на прозореца.

  titleBar_NewBtn = new BLabel("", true, false, -1, titleBar);
  titleBar_NewBtn->setMargin(titleBar_Label->margin());
  titleBar_NewBtn->setPixmap(createNewPixmap());
  titleBar_NewBtn->setAlignment(Qt::AlignCenter);
  titleBar_NewBtn->setFont(titleBar->font());
  titleBar_NewBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  titleBar_NewBtn->setVisible(dockWidgetShowNewButton);
  connect(titleBar_NewBtn, SIGNAL(buttonRelease()), this, SLOT(newDockWidget()));

  titleBar_MaximizeBtn = new BLabel("", true, false, -1, titleBar);
  titleBar_MaximizeBtn->setMargin(titleBar_Label->margin());
  titleBar_MaximizeBtn->setPixmap(createMaximizePixmap(dockWidgetMaximized));
  titleBar_MaximizeBtn->setAlignment(Qt::AlignCenter);
  titleBar_MaximizeBtn->setFont(titleBar->font());
  titleBar_MaximizeBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  titleBar_MaximizeBtn->setVisible(dockWidgetShowMaximizeButton);
  connect(titleBar_MaximizeBtn, SIGNAL(buttonRelease()), this, SLOT(maximizeDockWidget()));

  titleBar_CloseBtn = new BLabel("", true, false, -1, titleBar);
  titleBar_CloseBtn->setMargin(titleBar_Label->margin());
  titleBar_CloseBtn->setPixmap(createClosePixmap());
  titleBar_CloseBtn->setAlignment(Qt::AlignCenter);
  titleBar_CloseBtn->setFont(titleBar->font());
  titleBar_CloseBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  connect(titleBar_CloseBtn, SIGNAL(buttonRelease()), this, SLOT(closeButtonPressed()));

  connect(titleBar, SIGNAL(heightChange()), this, SLOT(titleBarHeightChange())); // Това трябва да е тук (след бутоните).

  mainContainer = new QWidget();
  mainContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QHBoxLayout *mainContainerLayout = new QHBoxLayout(mainContainer);
  mainContainerLayout->setContentsMargins(0, 0, 0, 0); // LTRB

  mainWidget = 0;
  tabMarkLine = 0;

  tabBar = new QWidget();
  tabBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  tabBar->hide();
  QHBoxLayout *tabBarLayout = new QHBoxLayout(tabBar);
  tabBarLayout->setSpacing(1);
  if (layoutDirection() == Qt::LeftToRight) // Този код го има и в setDockWidgetDisallowCloseLevel1 метода.
    tabBarLayout->setContentsMargins(0, 0, mDock->getDockWidgetTabbedTitleBar() ? 1:0, 0); // LTRB
  else
    tabBarLayout->setContentsMargins(mDock->getDockWidgetTabbedTitleBar() ? 1:0, 0, 0, 0); // LTRB

  QPalette palette;

  palette = titleBar_Label->palette();
  palette.setBrush(QPalette::Text, dockWidgetTitleBarTextColor);
  palette.setBrush(QPalette::WindowText, dockWidgetTitleBarTextColor);
  titleBar_Label->setPalette(palette);

  palette = this->palette();
  palette.setBrush(QPalette::Window, this->mDock->getDockBgColor());
  palette.setBrush(QPalette::Button, this->mDock->getDockBgColor());
  //palette.setBrush(QPalette::Base, this->mDock->getDockBgColor());
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  palette = titleBar->palette();
  palette.setBrush(QPalette::Window, dockWidgetTitleBarColor);
  palette.setBrush(QPalette::Button, dockWidgetTitleBarColor);
  //palette.setBrush(QPalette::Base, dockWidgetTitleBarColor);
  titleBar->setPalette(palette);
  titleBar->setAutoFillBackground(true);

  palette = mainContainer->palette();
  palette.setBrush(QPalette::Window, dockWidgetBgColor);
  palette.setBrush(QPalette::Button, dockWidgetBgColor);
  //palette.setBrush(QPalette::Base, dockWidgetBgColor);
  mainContainer->setPalette(palette);
  mainContainer->setAutoFillBackground(true);

  palette = tabBar->palette();
  palette.setBrush(QPalette::Window, this->mDock->getDockBgColor());
  palette.setBrush(QPalette::Button, this->mDock->getDockBgColor());
  //palette.setBrush(QPalette::Base, this->mDock->getDockBgColor());
  tabBar->setPalette(palette);
  tabBar->setAutoFillBackground(true);

  QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
  titleLayout->setSpacing(0);
  titleLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  titleLayout->addWidget(titleBar_Label);
  if (mDock->getDockWidgetTabbedTitleBar()) titleLayout->addWidget(tabBar);
  titleLayout->addWidget(titleBar_NewBtn);
  titleLayout->addWidget(titleBar_MaximizeBtn);
  titleLayout->addWidget(titleBar_CloseBtn);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(titleBar);
  mainLayout->addWidget(mainContainer);
  if (!mDock->getDockWidgetTabbedTitleBar()) mainLayout->addWidget(tabBar);
  mainLayout->setSpacing(1);
  mainLayout->setContentsMargins(0, 0, 0, 0); // LTRB
  setLayout(mainLayout);

  setAttribute(Qt::WA_DeleteOnClose, true); // При извикване на close() ще извика и деструктора.

#ifndef QT_NO_CURSOR
  setCursor(Qt::ArrowCursor);
#endif
}

MDockWidget::~MDockWidget()
{
  mDock->dockWidgetClosed(this);
  //qDebug() << "~MDockWidget:" << this;
}

void MDockWidget::closeDockWidget()
{
  //if (!dockWidgetDisallowCloseLevel1 || !dockWidgetDisallowCloseLevel2) close(); // Ако няма забрана за затваряне на прозореца.
  close();
}

void MDockWidget::closeButtonPressed()
{
  emit dockWidgetCloseButtonPressed(mDock, this, dockWidgetID, dockWidgetType, objectName());
  if (!dockWidgetDisallowCloseFromButton) close(); // Ако няма забрана за затваряне на прозореца от бутона.
  // Ако има забрана за затваряне на прозореца от бутона, някой може да приеме горния сигнал, да
  // направи каквото трябва и после да извика горния слот с който да затвори прозореца окончателно.
  // Ако пък с дока е направен тул-бар (един док съдържа само един прозорец, който не трябва да се затваря),
  // вместо да се извиква горния слот за затваряне на прозореца, се извиква метода за скриване на целия док,
  // (така се реализира скриване на тулбара при натискане на бутона за затваряне на прозореца).
}

//void MDockWidget::closeEvent(QCloseEvent *event)
//{
//  // Извиква се при изпълняване на close() от горните два слото или от вън.
//  if (!dockWidgetDisallowCloseLevel1 || !dockWidgetDisallowCloseLevel2) // Ако няма забрана за затваряне на прозореца от бутона.
//  {
//    event->accept();
//    //deleteLater(); // Това е излишно защото е сетнат флага Qt::WA_DeleteOnClose в конструктора. От тук и целия closeEvent метод е излишен.
//  }
//  else
//  {
//    event->ignore();
//  }
//}

void MDockWidget::tabPressed(int tabIndex)
{
  if (tabIndex != this->tabIndex)
  {
    dockWidgetTabPressed = true;  // Това забранява преместване на прозореца в момента, в който се извършва действието смяна на табовете. Без този флаг винаги се премества активният прозорец, без значение кой таб е натиснат и провлачен.
    QList<MDockWidget*> allTabbedDockWidgets = mDock->getAllTabbedDockWidgets(posXInDock, posYInDock);
    for (int i = 0; i < allTabbedDockWidgets.count(); i++)
    {
      if (allTabbedDockWidgets[i]->getTabIndex() == tabIndex)
      {
        // allTabbedDockWidgets[i] е указател към новоизбрания прозорец (в този момент this ще сочи към текущия - стария прозорец).
        mDock->dockWidgetTabPressed(allTabbedDockWidgets[i], tabIndex);
        emit dockWidgetRaised(mDock, allTabbedDockWidgets[i]);
        break;
      }
    }
  }
}

void MDockWidget::titleBarHeightChange()
{
  titleBar_NewBtn->setPixmap(createNewPixmap()); // Преизчертава картинката, съобразно новия размер.
  titleBar_MaximizeBtn->setPixmap(createMaximizePixmap(dockWidgetMaximized)); // Преизчертава картинката, съобразно новия размер и цвят.
  titleBar_CloseBtn->setPixmap(createClosePixmap()); // Преизчертава картинката, съобразно новия размер.
}

//void MDockWidget::resizeEvent(QResizeEvent *event)
//{
//  QWidget::resizeEvent(event);
//}

void MDockWidget::mouseMoveEvent(QMouseEvent *event)
{
  //QWidget::mouseMoveEvent(event); // За да се игнорира ивентът.
  if (!dockWidgetMaximized && !dockWidgetTabPressed)
  {
    if ((QDateTime::currentMSecsSinceEpoch() - currentMSecs) > 200) // Ако има реално влачене с мишката, а не трепване с ръката докато се щраква еднократно върху заглавната лента.
    {
      mDock->dockWidgetMoving(this, event->x()+x(), event->y()+y(), false);
      dockWidgetMoving = true;
    }
  }
  emit dockWidgetTitleBarMouseMove(mDock, this, event);
}
void MDockWidget::mousePressEvent(QMouseEvent *event)
{
  //QWidget::mousePressEvent(event); // За да се игнорира ивентът.
  currentMSecs = QDateTime::currentMSecsSinceEpoch(); // Запомня времето на натискане на бутона.
  emit dockWidgetTitleBarMousePress(mDock, this, event);
  //if (!dockWidgetTabPressed && getWidget() != 0) getWidget()->setFocus(); // Това не работи добре под Ubuntu - ако Widget-а е QTextBrowser, при setFocus се получава скрол към мястото, където е курсорът т.е. където е било щракнато с мишката.
}
void MDockWidget::mouseReleaseEvent(QMouseEvent *event)
{
  //QWidget::mouseReleaseEvent(event); // За да се игнорира ивентът.
  if (!dockWidgetMaximized && !dockWidgetTabPressed)
  {
    if (dockWidgetMoving) mDock->dockWidgetMoving(this, event->x()+x(), event->y()+y(), true); // Ако прозорецът е бил теглен с мишката и сега бутонът е отпуснат. Това не позволява прозорецът да се отдели от таб групата при еднократно щракване върху заглавната лента (трябва да има влачене преди това).
    dockWidgetMoving = false;
  }
  
  if (!dockWidgetTabPressed) // Ако не е натиснато върху таб (а върху заглавната лента).
  {
    // Тези сигнали няма да се излъчат когато е натиснато върху таб, защото:
    emit dockWidgetTitleBarMouseRelease(mDock, this, event); // ...защото табът не е TitleBar, дори когато е разположен в TitleBar-а.
    emit dockWidgetRaised(mDock, this); // ...защото вече е бил излъчен по-горе в tabPressed слота (но ако не е натиснато върху таб трябва да се излъчи от тук).
  }
  dockWidgetTabPressed = false;
}
void MDockWidget::mouseDoubleClickEvent(QMouseEvent */*event*/)
{
  //QWidget::mouseDoubleClickEvent(event); // За да се игнорира ивентът.
  maximizeDockWidget();
}

void MDockWidget::newDockWidget()
{
  emit dockWidgetNewButtonPressed(mDock, this, dockWidgetID, dockWidgetType, objectName());
}

void MDockWidget::maximizeDockWidget()
{
  // Всичко необходимо за максимизирането на прозореца може да се направи тук, но
  // ако има други прозорци на тази позиция, разположени в табове, те също трябва
  // да се максимизират, а това не може да стане от тук.  Ето защо тук се изпраща
  // сигнал, който се приема от MDock и от там се максимизират всички прозорци на
  // тази позиция, включително и този.
  mDock->dockWidgetTitleBarMouseDoubleClick(this); // Тук прозорецът ще се максимизира. Тук this сочи към новия таб, в случай, че е щракнато два пъти върху таб, който не е бил на фокус.
}

void MDockWidget::setWidget(QWidget *widget, int leftMargin, int topMargin, int rightMargin, int bottomMargin)
{
  mainWidget = widget;

  mainContainer->layout()->setContentsMargins(leftMargin, topMargin, rightMargin, bottomMargin);
  mainContainer->layout()->addWidget(widget);
}

void MDockWidget::deleteWidget()
{
  //if (mainWidget != 0) delete mainWidget; // Това ще премахне Widget-а от Layout-а.
  if (mainWidget != 0) mainWidget->deleteLater(); // Това ще премахне Widget-а от Layout-а.
  mainWidget = 0;
}

QWidget *MDockWidget::getWidget()
{
  return mainWidget;
}

QWidget *MDockWidget::getTitleBar()
{
  return titleBar;
}

QLabel *MDockWidget::getTitleBarLabel()
{
  return titleBar_Label;
}

QWidget *MDockWidget::getMainContainer()
{
  return mainContainer;
}

void MDockWidget::setPosInDock(int posXInDock, int posYInDock)
{
  this->posXInDock = posXInDock;
  if (posYInDock >= 0) this->posYInDock = posYInDock;
}

int MDockWidget::getPosXInDock()
{
  return this->posXInDock;
}

int MDockWidget::getPosYInDock()
{
  return this->posYInDock;
}

void MDockWidget::setTabs(QStringList tabTitles, int tabIndex)
{
  this->tabIndex = tabIndex;

  if (tabMarkLine != 0) delete tabMarkLine;
  tabMarkLine = 0;
  for (int i = 0; i < tabBar_Labels.count(); i++)
  {
    tabBar_Labels[i]->disconnect();
    delete tabBar_Labels[i]; // Това ще премахне старите етикети от Layout-а.
  }
  tabBar_Labels.clear();

  if (tabTitles.isEmpty())
  {
    if (mDock->getDockWidgetTabbedTitleBar()) titleBar_Label->show();
    tabBar->hide();
  }
  else
  {
    BLabel *bLabel;
    QPalette palette;
    QList<MDockWidget*> allTabbedDockWidgets = mDock->getAllTabbedDockWidgets(posXInDock, posYInDock);

    for (int i = 0; i < tabTitles.count(); i++)
    {
      bLabel = new BLabel(tabTitles[i], false, dockWidget3DTitleBar, i, tabBar);
      bLabel->setMargin(2);
      bLabel->setIndent(1);
      bLabel->setAutoFillBackground(true);
      bLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
      bLabel->setFont(allTabbedDockWidgets[i]->getDockWidgetTitleBarFont());

      palette = bLabel->palette();
      palette.setBrush(QPalette::Window, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
      palette.setBrush(QPalette::Button, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
      //palette.setBrush(QPalette::Base, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
      palette.setBrush(QPalette::Text, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
      palette.setBrush(QPalette::WindowText, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
      bLabel->setPalette(palette);

      if (i == tabIndex)
      {
        // Черта на активния таб.
        tabMarkLine = new QFrame(bLabel);
        tabMarkLine->setGeometry(QRect(0, 1, 5000, 2));
        tabMarkLine->setFrameShadow(QFrame::Plain);
        tabMarkLine->setAutoFillBackground(true);
        palette = tabMarkLine->palette();
        QColor markColor(this->mDock->getDockBgColor()); //getTrackFrameColor() // Ако се смени цвета на фона (mDockBgColor), това няма да се отрази веднага на цвета на тази черта.
        markColor.setAlpha(128); // Ако се промени тук, да се промени и в setDockWidgetTitleBarColor метода.
        palette.setBrush(QPalette::Window, markColor);
        palette.setBrush(QPalette::Button, markColor);
        //palette.setBrush(QPalette::Base, markColor);
        tabMarkLine->setPalette(palette);
      }

      connect(bLabel, SIGNAL(buttonPress(int)), this, SLOT(tabPressed(int)));

      tabBar->layout()->addWidget(bLabel);
      tabBar_Labels << bLabel;
    }

    if (mDock->getDockWidgetTabbedTitleBar()) titleBar_Label->hide();
    tabBar->show();
  }
}

void MDockWidget::setCurrentTab()
{
  if (tabIndex >= 0) raise(); // Ако участва в табове го прави да е текущия таб.
}

int MDockWidget::getTabIndex()
{
  return tabIndex;
}

void MDockWidget::setDockWidgetDisallowCloseLevel1(bool disallow)
{
  dockWidgetDisallowCloseLevel1 = disallow;
  titleBar_CloseBtn->setVisible(!disallow);
  if (!titleBar_NewBtn->isVisible() && !titleBar_MaximizeBtn->isVisible() && !titleBar_CloseBtn->isVisible()) // Ако всички бутони са скрити.
  {
    tabBar->layout()->setContentsMargins(0,0,0,0); // LTRB // Премахва маргина от страна на бутоните.
  }
  else // Ако поне един от бутоните е видим.
  {
    if (layoutDirection() == Qt::LeftToRight) // Този код го има и в конструктора.
      tabBar->layout()->setContentsMargins(0, 0, mDock->getDockWidgetTabbedTitleBar() ? 1:0, 0); // LTRB // Добавя маргин от страна на бутоните.
    else
      tabBar->layout()->setContentsMargins(mDock->getDockWidgetTabbedTitleBar() ? 1:0, 0, 0, 0); // LTRB // Добавя маргин от страна на бутоните.
  }
}

bool MDockWidget::getDockWidgetDisallowCloseLevel1()
{
  return dockWidgetDisallowCloseLevel1;
}

void MDockWidget::setDockWidgetDisallowCloseLevel2(bool disallow)
{
  dockWidgetDisallowCloseLevel2 = disallow;
  titleBar_CloseBtn->setEnabled(!disallow);
}

bool MDockWidget::getDockWidgetDisallowCloseLevel2()
{
  return dockWidgetDisallowCloseLevel2;
}

void MDockWidget::setDockWidgetDisallowCloseFromButton(bool disallow)
{
  dockWidgetDisallowCloseFromButton = disallow;
}

bool MDockWidget::getDockWidgetDisallowCloseFromButton()
{
  return dockWidgetDisallowCloseFromButton;
}

void MDockWidget::setDockWidgetTitle(QString title)
{
  titleBar_Label->setText(title);
  if (tabIndex >= 0) refreshAllTabs(); // Ако участва в табове.
}

QString MDockWidget::getDockWidgetTitle()
{
  return titleBar_Label->text();
}

void MDockWidget::setDockWidgetID(int ID)
{
  dockWidgetID = ID;
}

int MDockWidget::getDockWidgetID()
{
  return dockWidgetID;
}

void MDockWidget::setDockWidgetType(int type)
{
  dockWidgetType = type;
}

quint8 MDockWidget::getDockWidgetType()
{
  return dockWidgetType;
}

void MDockWidget::setDockWidgetTitleBarFont(QFont font)
{
  titleBar->setFont(font);
  titleBar_Label->setFont(font);
  titleBar_NewBtn->setFont(font);
  titleBar_MaximizeBtn->setFont(font);
  titleBar_CloseBtn->setFont(font);

  refreshAllTabs();
}

QFont MDockWidget::getDockWidgetTitleBarFont()
{
  return titleBar_Label->font();
}

void MDockWidget::setDockWidgetTitleBarFontSize(int size)
{
  QFont font = titleBar_Label->font();
  font.setPointSize(size);
  titleBar->setFont(font);
  titleBar_Label->setFont(font);
  titleBar_NewBtn->setFont(font);
  titleBar_MaximizeBtn->setFont(font);
  titleBar_CloseBtn->setFont(font);

  refreshAllTabs();
}

int MDockWidget::getDockWidgetTitleBarFontSize()
{
  return titleBar_Label->font().pointSize();
}

void MDockWidget::setDockWidgetTitleBarFontBold(bool bold)
{
  QFont font = titleBar_Label->font();
  font.setBold(bold);
  titleBar->setFont(font);
  titleBar_Label->setFont(font);
  titleBar_NewBtn->setFont(font);
  titleBar_MaximizeBtn->setFont(font);
  titleBar_CloseBtn->setFont(font);

  refreshAllTabs();
}

bool MDockWidget::getDockWidgetTitleBarFontBold()
{
  return titleBar_Label->font().bold();
}

void MDockWidget::setDockWidgetTitleBarFontItalic(bool italic)
{
  QFont font = titleBar_Label->font();
  font.setItalic(italic);
  titleBar->setFont(font);
  titleBar_Label->setFont(font);
  titleBar_NewBtn->setFont(font);
  titleBar_MaximizeBtn->setFont(font);
  titleBar_CloseBtn->setFont(font);

  refreshAllTabs();
}

bool MDockWidget::getDockWidgetTitleBarFontItalic()
{
  return titleBar_Label->font().italic();
}

void MDockWidget::setDockWidgetTitleBarTextColor(QColor color)
{
  dockWidgetTitleBarTextColor = color;

  QPalette palette;
  palette = titleBar_Label->palette();
  palette.setBrush(QPalette::Text, dockWidgetTitleBarTextColor);
  palette.setBrush(QPalette::WindowText, dockWidgetTitleBarTextColor);
  titleBar_Label->setPalette(palette);

  refreshAllTabs();
}

QColor MDockWidget::getDockWidgetTitleBarTextColor()
{
  return dockWidgetTitleBarTextColor;
}

void MDockWidget::setDockWidgetTitleBarButtonColor(QColor color)
{
  dockWidgetTitleBarButtonColor = color;
  titleBar_NewBtn->setPixmap(createNewPixmap()); // Преизчертава картинката, съобразно новия цвят.
  titleBar_MaximizeBtn->setPixmap(createMaximizePixmap(dockWidgetMaximized)); // Преизчертава картинката, съобразно новия размер.
  titleBar_CloseBtn->setPixmap(createClosePixmap()); // Преизчертава картинката, съобразно новия цвят.
}

QColor MDockWidget::getDockWidgetTitleBarButtonColor()
{
  return dockWidgetTitleBarButtonColor;
}

void MDockWidget::setDockWidgetTitleBarColor(QColor color)
{
  // Първо променя цвета на фона и цвета на фона на табовете (без значение дали има или не табове):
  QPalette palette;
  palette = this->palette();
  palette.setBrush(QPalette::Window, this->mDock->getDockBgColor());
  palette.setBrush(QPalette::Button, this->mDock->getDockBgColor());
  //palette.setBrush(QPalette::Base, this->mDock->getDockBgColor());
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  palette = tabBar->palette();
  palette.setBrush(QPalette::Window, this->mDock->getDockBgColor());
  palette.setBrush(QPalette::Button, this->mDock->getDockBgColor());
  //palette.setBrush(QPalette::Base, this->mDock->getDockBgColor());
  tabBar->setPalette(palette);
  tabBar->setAutoFillBackground(true);

  dockWidgetTitleBarColor = color;

  // Променя цвета на заглавната лента.
  palette = titleBar->palette();
  palette.setBrush(QPalette::Window, dockWidgetTitleBarColor);
  palette.setBrush(QPalette::Button, dockWidgetTitleBarColor);
  //palette.setBrush(QPalette::Base, dockWidgetTitleBarColor);
  titleBar->setPalette(palette);
  titleBar->setAutoFillBackground(true);

  // Накрая променя цвета на табовете (ако има табове):
  QList<MDockWidget*> allTabbedDockWidgets = mDock->getAllTabbedDockWidgets(posXInDock, posYInDock);
  for (int i = 0; i < tabBar_Labels.count(); i++)
  {
    palette = tabBar_Labels[i]->palette();
    palette.setBrush(QPalette::Window, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    palette.setBrush(QPalette::Button, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    //palette.setBrush(QPalette::Base, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    palette.setBrush(QPalette::Text, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
    palette.setBrush(QPalette::WindowText, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
    tabBar_Labels[i]->setPalette(palette);
  }
  if (tabMarkLine != 0)
  {
    palette = tabMarkLine->palette();
    QColor markColor(this->mDock->getDockBgColor()); //getTrackFrameColor()
    markColor.setAlpha(128); // Ако се промени тук, да се промени и в setTabs метода.
    palette.setBrush(QPalette::Window, markColor);
    palette.setBrush(QPalette::Button, markColor);
    //palette.setBrush(QPalette::Base, markColor);
    tabMarkLine->setPalette(palette);
  }
}

QColor MDockWidget::getDockWidgetTitleBarColor()
{
  return dockWidgetTitleBarColor;
}

void MDockWidget::setDockWidgetBgColor(QColor color)
{
  dockWidgetBgColor = color;

  QPalette palette;
  palette.setBrush(QPalette::Window, dockWidgetBgColor);
  palette.setBrush(QPalette::Button, dockWidgetBgColor);
  //palette.setBrush(QPalette::Base, dockWidgetBgColor);
  mainContainer->setPalette(palette);
  mainContainer->setAutoFillBackground(true);
}

QColor MDockWidget::getDockWidgetBgColor()
{
  return dockWidgetBgColor;
}

void MDockWidget::setDockWidget3DTitleBar(bool dockWidget3DTitleBar)
{
  this->dockWidget3DTitleBar = dockWidget3DTitleBar;
  titleBar->set3DBackground(dockWidget3DTitleBar);
  for (int i = 0; i < tabBar_Labels.count(); i++)
  {
    tabBar_Labels[i]->set3DBackground(dockWidget3DTitleBar);
  }
}

bool MDockWidget::getDockWidget3DTitleBar()
{
  return dockWidget3DTitleBar;
}

bool MDockWidget::isDockWidgetMaximized()
{
  return dockWidgetMaximized;
}

void MDockWidget::setNewBtnToolTip(const QString tip)
{
  titleBar_NewBtn->setToolTip(tip);
}

void MDockWidget::setMaximizeBtnToolTip(const QString tip)
{
  titleBar_MaximizeBtn->setToolTip(tip);
}

void MDockWidget::setCloseBtnToolTip(const QString tip)
{
  titleBar_CloseBtn->setToolTip(tip);
}

void MDockWidget::refreshAllTabs()
{
  foreach (MDockWidget *dw, mDock->getAllTabbedDockWidgets(posXInDock, posYInDock)) // Ако има табове.
  {
    dw->refreshTabs();
  }
}

void MDockWidget::refreshTabs()
{
  QPalette palette;
  QList<MDockWidget*> allTabbedDockWidgets = mDock->getAllTabbedDockWidgets(posXInDock, posYInDock);

  for (int i = 0; i < tabBar_Labels.count(); i++)
  {
    tabBar_Labels[i]->setFont(allTabbedDockWidgets[i]->getDockWidgetTitleBarFont());

    palette = tabBar_Labels[i]->palette();
    palette.setBrush(QPalette::Window, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    palette.setBrush(QPalette::Button, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    //palette.setBrush(QPalette::Base, allTabbedDockWidgets[i]->getDockWidgetTitleBarColor());
    palette.setBrush(QPalette::Text, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
    palette.setBrush(QPalette::WindowText, allTabbedDockWidgets[i]->getDockWidgetTitleBarTextColor());
    tabBar_Labels[i]->setPalette(palette);
	
    tabBar_Labels[i]->setText(allTabbedDockWidgets[i]->getDockWidgetTitle());
  }
}

void MDockWidget::resizeWidget()
{
  if (dockWidgetMaximized)
  {
    setGeometry(mDock->getDockMargins().left(), mDock->getDockMargins().top(), mDock->geometry().width()-mDock->getDockMargins().left()-mDock->getDockMargins().right(), mDock->geometry().height()-mDock->getDockMargins().top()-mDock->getDockMargins().bottom());
  }
  else
  {
    setGeometry(mDock->getDockWidgetGeometry(posXInDock, posYInDock));
  }

  titleBar_MaximizeBtn->setPixmap(createMaximizePixmap(dockWidgetMaximized)); // Преизчертава картинката заради промяна в цвета й (размерът й си е същият).
}

QPixmap MDockWidget::createNewPixmap()
{
  int h = titleBar->height() - 2*titleBar_Label->margin() - 2;
  qreal d = 2.3; // Дебелина на линията. С 2.2 се получава слаб ореол. Ако се изчертава плюс стои по-добре с 2.3.
  if (h > 60) d = 8.0;
  else if (h > 30) d = 4.0;

  //if ((int)h % 2 != 0) h--; // Този ред е нужен, ако се изчертава плюс (закоментираните два реда по-долу). Ако числото не е четно се прави четно (за да не се размазва плюса).

  QPixmap pix(h, h);
  pix.fill(QColor(0, 0, 0, 0)); // Инициализиране с прозрачност.
  QPainter painter(&pix);
  painter.setRenderHints(QPainter::Antialiasing, true);
  painter.setPen(QPen(dockWidgetTitleBarButtonColor, d));
  //painter.drawLine(QLineF(h/2.0, 2.0, h/2.0, h-2.0)); // Изчертава плюс.
  //painter.drawLine(QLineF(2.0, h/2.0, h-2.0, h/2.0)); //
  painter.drawRect(QRectF(2.0, 2.0, h-4.0, h-4.0)); // Изчертава правоъгълник.

  return pix;
}

QPixmap MDockWidget::createMaximizePixmap(bool maximize)
{
  int h = titleBar->height() - 2*titleBar_Label->margin() - 2;
  qreal d = 2.0; // Дебелина на линията. Тук с 2.2 се получава слаб ореол, но е грозно, защото има едно удебеляване в ръба на стрелката.
  if (h > 60) d = 8.0;
  else if (h > 30) d = 4.0;

  QPixmap pix(h, h);
  pix.fill(QColor(0, 0, 0, 0)); // Инициализиране с прозрачност.
  QPainter painter(&pix);
  painter.setRenderHints(QPainter::Antialiasing, true);
  if (!maximize)
  {
    painter.setPen(QPen(dockWidgetTitleBarButtonColor, d));
    painter.drawLine(QLineF(h-2.0, 2.0, 2.0, h-2.0));
    painter.drawLine(QLineF(h-2.0-(h/3.0), 2.0, h-2.0, 2.0));
    painter.drawLine(QLineF(h-2.0, 2.0+(h/3.0), h-2.0, 2.0));
  }
  else
  {
    painter.setPen(QPen(mDock->getTrackFrameColor(), d));
    painter.drawLine(QLineF(h-2.0, 2.0, 2.0, h-2.0));
    painter.drawLine(QLineF(2.0, h-2.0-(h/3.0), 2.0, h-2.0));
    painter.drawLine(QLineF(2.0+(h/3.0), h-2.0, 2.0, h-2.0));
  }

  return pix;
}

QPixmap MDockWidget::createClosePixmap()
{
  int h = titleBar->height() - 2*titleBar_Label->margin() - 2;
  qreal d = 2.2; // Дебелина на линията. С 2.2 се получава слаб ореол.
  if (h > 60) d = 8.0;
  else if (h > 30) d = 4.0;

  QPixmap pix(h, h);
  pix.fill(QColor(0, 0, 0, 0)); // Инициализиране с прозрачност.
  QPainter painter(&pix);
  painter.setRenderHints(QPainter::Antialiasing, true);
  painter.setPen(QPen(dockWidgetTitleBarButtonColor, d));
  painter.drawLine(QLineF(h-2.0, 2.0, 2.0, h-2.0));
  painter.drawLine(QLineF(2.0, 2.0, h-2.0, h-2.0));

  return pix;
}
