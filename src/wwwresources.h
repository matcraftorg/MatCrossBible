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

#ifndef WWWRESOURCES_H
#define WWWRESOURCES_H

#include <QWidget>
#include <QTextBrowser>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpacerItem>
#include <QIODevice>
#include <QFile>
#include "mainwindow.h"

class MainWindow;

struct URL_DESC
{
  QString url;         // Адрес на линка.
  QString description; // Описание на линка.
};

class WWWResources : public QWidget
{
  Q_OBJECT

private:
  MainWindow *MW;
  QList<URL_DESC> UD; // Списък, съдържащ всички линкове.
  bool modified;      // Дали има промени в списъка.

  void init(); // Начални инициализации.
  void loadFile(); // Чете от файла.
  void showLinks(bool withNumber); // Показва линковете със или без номера на редовете.
  void writeNewFile(); // Създава нов файл (ако не е създаден).
  void save(); // Записва във файла.
  void refreshCombo(); // Обновява комбобоксовете.

public:
  QTextBrowser *textBrowser;
  QGroupBox *AddGroupBox;
  QLineEdit *AddURLLineEdit;
  QLineEdit *AddDescriptionLineEdit;
  QPushButton *InsertBtn;
  QComboBox *InsertComboBox;
  QGroupBox *EditDelGroupBox;
  QLineEdit *EditURLLineEdit;
  QLineEdit *EditDescriptionLineEdit;
  QComboBox *ChoiceComboBox;
  QPushButton *SaveBtn;
  QPushButton *DeleteBtn;
  QPushButton *AddPanelBtn;
  QPushButton *EditDelPanelBtn;
  QPushButton *CloseBtn;

  WWWResources(MainWindow *mainWindow);
  ~WWWResources();

protected:
  virtual void closeEvent(QCloseEvent *e);

private slots:
  void slotInsertBtn();
  void slotChoiceComboBox(int index);
  void slotSaveBtn();
  void slotDeleteBtn();
  void slotAddPanelBtn_Toggled(bool checked);
  void slotEditDelPanelBtn_Toggled(bool checked);
};

#endif // WWWRESOURCES_H
