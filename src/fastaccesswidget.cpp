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

#include "fastaccesswidget.h"

FastAccessWidget::FastAccessWidget(MainWindow *MW) : QLineEdit(MW)
{
  setMinimumWidth(1);
  this->MW = MW;

  QStringList wordList;
  for(quint8 i = 0; i < 77; i++)
  {
    if ( (!MW->MO->SVars.showDeuterocanonical) && (i >= 39 && i <= 49) ) continue;
    wordList << MW->MO->bookShortNameArr[i]; // Търсенето става в късите имена, а не в съкратените, защото съкратените могат да бъдат много шантави букви и става невъзможно да се работи с тях по този начин.
  }
  completer = new QCompleter(wordList, this);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setCompletionMode(QCompleter::PopupCompletion);
  completer->setModelSorting(QCompleter::UnsortedModel);
  completer->setFilterMode(Qt::MatchContains); // Указва кои съвпадения да показва: Qt::MatchStartsWith - тези, които започват с написания текст (по подразбиране); Qt::MatchContains - тези, които съдържат написания текст.

  setCompleter(completer);

  QString e1 = MW->MO->bookShortNameArr[0].left(3); if (e1.isEmpty()) e1 = MW->MO->bookShortNameArr[0]; // "Бит"
  QString e2 = QString("%1 3").arg(e1);                                                                 // "Бит 3"
  QString e3 = QString("%1 2").arg(e2).toLower();                                                       // "бит 3 2"
  QString e4 = QString("%1 1 14").arg(MW->MO->bookShortNameArr[52]).toLower();                          // "лука 1 14"
  setToolTip(QString("%1 (F11)\n\n%2:\n  %3\n  %4\n  %5\n  %6").arg(MW->MO->TS->FastAccess_v1, MW->MO->TS->ValidExpression_v1, e1, e2, e3, e4)); //"Fast Access"

  palN = palette(); // Нормална палитра.
  palN.setBrush(QPalette::Base, QColor(255,255,210)); // Бледожълт цвят за фон.
  palN.setBrush(QPalette::Window, QColor(255,255,210)); // Бледожълт цвят за фон.
  palN.setBrush(QPalette::Text, QColor(0,0,0)); // Текст на буквите.
  
  palG = palette(); // Неактивно поле.
  palG.setBrush(QPalette::Base, QColor(0,0,0,0)); // Цвета на фона. Прозрачност. // palG.brush(QPalette::Window).color()
  QColor tColor = palG.brush(QPalette::Text).color();   tColor.setAlpha(80); // Този цвят се взима след като е сетнат цветът на фона (горният ред).
  palG.setBrush(QPalette::Text, tColor); // Текст на буквите по-тъмен от фона.

  isInactive = true;

  showGreyText(true);
}

void FastAccessWidget::showGreyText(bool show)
{
  if (show) // Ако трябва да покаже сивия текст.
  {
    if (text().isEmpty()) // Ако полето е празно.
    {
      setPalette(palG);
      setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      setText(QString("• %1 •").arg(MW->MO->TS->FastAccess_v1));
      isInactive = true;
    }
  }
  else // Ако трябва да скрие сивия текст.
  {
    if (isInactive) // Ако е показан сивия текст.
    {
      setPalette(palN);
      setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      setText(""); // Премахва сивия текст.
      isInactive = false;
    }
  }
}

void FastAccessWidget::keyPressEvent(QKeyEvent *event)
{
  QLineEdit::keyPressEvent(event);
  if (event->key() != Qt::Key_Return  &&  event->key() != Qt::Key_Enter) return;
  
  quint8 bookCode = 0;
  quint8 chapterCode = 0;
  quint8 verseCode = 0;
  
  QStringList words = text().split(QRegExp("[ :]"), QString::SkipEmptyParts); // Преди за разделител използвах какъв да е символ QRegExp("\\W"), но не е добре така. Например, не разпознава 3,4 Макавей. Сега за разделител се използва само интервал или двуеточие и е ОК.

  if (words.size() == 0) return;

  if (words.size() == 1) // При една дума. Предполага се че е текст.
  {
    bookCode = toBookCode(words[0]);
    if (bookCode > 0)
    {
      chapterCode = 1;
      verseCode = 1;
    }
  }
  else if (words.size() == 2) // При две думи. Първата се предполага че е текст. Втората може да е число, а може и да е текст, затова се проверява.
  {
    bool ok;
    words[1].toUInt(&ok); // Проверява дали втората дума е число (ok ще е true ако е число).
    if (ok) // Ако е число.
    {
      bookCode = toBookCode(words[0]);
      if (bookCode > 0)
      {
        chapterCode = (quint8)words[1].toUInt();
        verseCode = 1;
      }
    }
    else // Ако не е число (значи е част от името).
    {
      bookCode = toBookCode( concatenate(words, 2) );
      if (bookCode > 0)
      {
        chapterCode = 1;
        verseCode = 1;
      }
    }
  }
  else if (words.size() > 2) // При повече от две думи. Първите се предполага че са текст. Последните две може да са числа, а може и да са текст, затова се проверяват.
  {
    quint8 wCount = words.size(); 
    bool ok;
    words[wCount-2].toUInt(&ok); // Проверява дали предпоследната дума е число (ok ще е true ако е число).
    if (ok) // Ако предпоследната дума е число.
    {
      bookCode = toBookCode( concatenate(words, wCount-2) ); // bookCode се определя от всички думи без последните две.
      if (bookCode > 0)
      {
        chapterCode = (quint8)words[wCount-2].toUInt(); // Предпоследната се предполага че е chapterCode.
        verseCode = (quint8)words[wCount-1].toUInt(); // Последната се предполага че е verseCode.
      }
    }
    else // Ако предпоследната дума не е число (значи е част от името).
    {
      words[wCount-1].toUInt(&ok); // Проверява дали последната дума е число (ok ще е true ако е число).
      if (ok) // Ако е число.
      {
        bookCode = toBookCode( concatenate(words, wCount-1) ); // bookCode се определя от всички думи без последната.
        if (bookCode > 0)
        {
          chapterCode = (quint8)words[wCount-1].toUInt(); // Последната се предполага че е chapterCode.
          verseCode = 1;
        }
      }
      else // Ако не е число (значи е част от името).
      {
        bookCode = toBookCode( concatenate(words, wCount) ); // bookCode се определя от всички думи.
        if (bookCode > 0)
        {
          chapterCode = 1;
          verseCode = 1;
        }
      }
    }
  }

  if ( MW->MO->verification(bookCode, chapterCode, verseCode) ) // Ако написаните кодове са верни.
  {
    if (!MW->MO->SVars.showDeuterocanonical) // Ако Второканоничните книги са скрити.
    {
      if ( bookCode >= 40 && bookCode <= 50 ) return; // Тази проверка е излишна, но да има.
      if ( (bookCode==19 && chapterCode==151) || (bookCode==27 && (chapterCode==13 || chapterCode==14)) ) return;
    }

    setText("");

    MW->switchToNormalMode();
    MW->currentHolyTextView->showBibleText(MW->MO->toAbsIndex(bookCode, chapterCode, verseCode)); // Тук ще стане проблем, ако избраната глава съдържа Второканонични стихове, които не са показани, но здраве да е.
  }
}

quint8 FastAccessWidget::toBookCode(QString text)
{
  for (quint8 i = 0; i < 77; i++)
  {
    //if ( MW->MO->bookShortNameArr[i].indexOf(text, 0, Qt::CaseInsensitive) == 0 ) // При completer->setFilterMode(Qt::MatchStartsWith) - ако името на някоя от книгите съвпада/започва с написания текст. Това внася някои ограничения. Например не може да се напише Навин, а трябва задължително Исус Навин.
    if ( MW->MO->bookShortNameArr[i].contains(text, Qt::CaseInsensitive) ) // При completer->setFilterMode(Qt::MatchContains) - ако името на някоя от книгите съдържа написания текст.
    {
      return i+1;
    }
  }
  return 0; // Ако няма съвпадение, връща нула.
}

// Съединява първите count стринга от списъка words, като добавя интервал помежду им.
QString FastAccessWidget::concatenate(const QStringList words, quint8 count)
{
  if (count > words.size()) count = (quint8)words.size();
  QString txt = "";
  for (quint8 i = 0; i < count; i++)
  {
    if (i > 0) txt += " ";
    txt += words[i];
  }
  return txt;
}
