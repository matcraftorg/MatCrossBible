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

#ifndef FASTACCESSWIDGET_H
#define FASTACCESSWIDGET_H

#include <QLineEdit>
#include <QCompleter>
#include <QPalette>
#include "mainwindow.h"

class MainWindow;

class FastAccessWidget : public QLineEdit
{
Q_OBJECT
  
public:
  QCompleter *completer;

  FastAccessWidget(MainWindow *MW);
  void showGreyText(bool show); // Показва/скрива изписването на сивия текст "Бърз достъп".

private:
  MainWindow *MW;
  QPalette palN; // Нормална палитра.
  QPalette palG; // Сив цвят на буквите.
  bool isInactive; // Флаг, указващ дали полето е неактивно.

  void keyPressEvent(QKeyEvent *event);
  quint8 toBookCode(QString text);
  QString concatenate(const QStringList words, quint8 count);
};
#endif
