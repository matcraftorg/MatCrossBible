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

#ifndef EXTEXTWINDOW_H
#define EXTEXTWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QTextBrowser>
#include <QTextStream>

#include "mainwindow.h"

class QToolBar;
class QToolButton;
class QTextBrowser;
class MainObject;
class MainWindow;

class ExTextWindow : public QMainWindow
{
  Q_OBJECT

public:
  QTextBrowser *editor;

  ExTextWindow(MainWindow *mainWindow, int Width, int Height, bool isPad = false, QWidget *parent = 0);
  ~ExTextWindow();
  void openFile(QString fileName, bool acceptRichText);
  void setEditorFont(QFont font);
  void setEditorAcceptRichTextt(bool acceptRichText);
  void setWordWrapMode(bool wordWrap);
  void setReadOnly(bool readOnly);
  void setHtmlText(QString text);
  void setPlainText(QString text);
  void setSearchPaths(const QStringList &paths); // Списък с директориите, където да търси картинки и други документи за показване (например при показване на HTML файлове, ще търси картинките в тези директории).

private:
  MainWindow *MW;
  bool isPad; // TRUE - ако се използва като бележник; FALSE - за други цели.
  QString fileName;
  QToolBar    *toolBar;
  QToolButton *btnSelectAll;
  QToolButton *btnCopy;
  QToolButton *btnSave;
  QToolButton *btnClose;

  bool maybeSave();
  bool fileSave();
  void keyPressEvent(QKeyEvent *event);
  void closeEvent(QCloseEvent *event);

private slots:
  void slotSave();
  //void SlotAnchorClicked(const QUrl &link);
};

#endif
