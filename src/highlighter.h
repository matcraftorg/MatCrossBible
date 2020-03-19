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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QtGui>
#include <QHash>
#include <QTextCharFormat>
#include "mainobject.h"
#include "mainwindow.h"
#include "textview.h"
#include "datatypes.h"

class QTextDocument;
class MainObject;
class MainWindow;
class TextView;

class Highlighter : public QSyntaxHighlighter
{
  Q_OBJECT

private:
  struct HighlightingRule
  {
    QTextCharFormat format;
    QRegExp pattern;
    bool isCurrentNumber; // Дали е за оцветяване на текущия номер.
    bool isCustomText;    // Дали е за оцветяване на текст, зададен от потребителя.
  };
  QVector<HighlightingRule> highlightingRules;
  MainObject *MO;
  MainWindow *MW;
  TextView   *textView;
  QColor searchWordsColorF[5];
  QColor searchWordsColorB[5];
  uchar searchWordsColorIndex;
  bool enableHighlighter;

public:
  Highlighter(QTextDocument *parent = 0);
  void initializeHighlighter(MainWindow *MW, TextView *textView);
  void addPatterns(const QStringList searchWordsList, Qt::CaseSensitivity caseSensitivitySearch);
  void addCustomPattern(const QString customText);
  void delCustomPattern(const QString customText);
  void delCustomPatterns();
  void setDictPatterns(DICT_PROPERTIES *DP);
  //void setCurrentNumber(const int cNumber);
  void setEnableHighlighter(bool enable);

protected:
  void highlightBlock(const QString &text);
};
#endif
