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

#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QtGui>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QIODevice>
#include <QFile>

#include "datatypes.h"
#include "mainobject.h"
#include "mdock.h"
#include "textview.h"
#include "dictionary.h"

class MDockWidget;
class MainObject;
class TextView;
class Dictionary;

struct DOCKS
{
  // Тази структура ще държи всички отворени раздели.
  MDockWidget *dockWidget; // Раздел.
  TextView    *textView;   // Изглед в раздела (ако има такъв).
  Dictionary  *dictionary; // Речник или коментар (ако има такъв).
  // --- Тук ще се добавят и други обекти в бъдеще, като се направят разделите с друго съдържание.
};

// =========================================================================================================================================================

class ReorderBibleTextsWindow : public QDialog
{
Q_OBJECT

private:
  MainObject *MO;
  bool *needToRestart;
  QStringList allFileBaseNames;
  QStringList allNames;
  int currentRow;
  QListWidget *listWidget;
  QPushButton *btnUp;
  QPushButton *btnDown;
  QPushButton *btnOK;
  QPushButton *btnCancel;

public:
  ReorderBibleTextsWindow(MainObject *mainObject, bool *needToRestart, QWidget *parent = 0);
  ~ReorderBibleTextsWindow();

private slots:
  void slotUp();
  void slotDown();
  void slotOK();
};

// =========================================================================================================================================================

class ProgressDialog : public QDialog
{
Q_OBJECT

// Този клас имитира QProgressDialog.
// Идеята на QProgressDialog е да се покаже в момента на създаването си, но не точно веднага, а със закъснение от minimumDuration милисекунди с цел,
// ако процесът, който трябва да покаже е по-кратък от това време, прогрес-диалогът изобщо да не се покаже (за да не се получава ефект на премигване).
// Проблемът идва тогава, когато прогрес-диалогът се използва многократно - получава се един страничен ефект: при създаване му, той се показва след
// изтичане на minimumDuration времето (по подразбиране е 4 секунди). Не можах да открия начин да му забраня да се показва сам, затова ми беше по-лесно
// да пренапиша този QProgressDialog без тази функционалност. :)

private:
  bool isAutoShow;
  bool isAutoHide;
  QLabel       *label;
  QProgressBar *progressBar;
  QPushButton  *btnCancel;

public:
  ProgressDialog(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
  ProgressDialog(const QString &labelText, const QString &cancelButtonText, int minimum, int maximum, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
  ~ProgressDialog();
  QString labelText();
  void setLabelText(const QString &text);
  QString cancelButtonText();
  void setCancelButtonText(const QString &cancelButtonText);
  int minimum();
  int maximum();
  int value();
  bool autoShow();
  void setAutoShow(bool autoShow);
  bool autoHide();
  void setAutoHide(bool autoHide);

private slots:
  void btnCancelClicked();

public slots:
  void reset();
  void setMinimum(int minimum);
  void setMaximum(int maximum);
  void setRange(int minimum, int maximum);
  void setValue(int progress);

signals:
  void canceled();
};

// =========================================================================================================================================================

class BibleTextConvertor : public QWidget
{
Q_OBJECT

private:
  MainObject *MO;

  QLineEdit   *lineEditCrossBgBibleFile;
  QPushButton *btnChoiceCrossBgBibleFile;
  QPushButton *btnConvertCrossBgBibleFile;

  QLineEdit   *lineEditTheWordFile;
  QPushButton *btnChoiceTheWordFile;
  QPushButton *btnConvertTheWordFile;
  QCheckBox   *chBoxAddNumbersToVerses;

public:
  BibleTextConvertor(MainObject *mainObject, QWidget *parent = 0);
  ~BibleTextConvertor();

private slots:
  void btnChoiceCrossBgBibleFileClicked();
  void btnConvertCrossBgBibleFileClicked();
  void btnChoiceTheWordFileClicked();
  void btnConvertTheWordFileClicked();
};

#endif // UTILITY_H
