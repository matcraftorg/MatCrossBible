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

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
  // Цветове за Foreground
  searchWordsColorF[0] = QColor(255,128,  0);
  searchWordsColorF[1] = QColor(255, 85,255);
  searchWordsColorF[2] = QColor(170,  0,127);
  searchWordsColorF[3] = QColor(  0,150,  0);
  searchWordsColorF[4] = QColor( 85,170,255);

  // Цветове за Background
  searchWordsColorB[0] = QColor(255,210,185);
  searchWordsColorB[1] = QColor(255,210,255);
  searchWordsColorB[2] = QColor(225,200,200);
  searchWordsColorB[3] = QColor(185,255,185);
  searchWordsColorB[4] = QColor(220,235,255);

  searchWordsColorIndex = 0;
  enableHighlighter = true;
}

void Highlighter::initializeHighlighter(MainWindow *MW, TextView *textView)
{
  this->MW = MW;
  this->textView = textView;

  // Цветове за Foreground
  searchWordsColorF[0] = MW->MO->SVars.foundWordsColor1F; //QColor(255,128,  0);
  searchWordsColorF[1] = MW->MO->SVars.foundWordsColor2F; //QColor(255, 85,255);
  searchWordsColorF[2] = MW->MO->SVars.foundWordsColor3F; //QColor(170,  0,127);
  searchWordsColorF[3] = MW->MO->SVars.foundWordsColor4F; //QColor(  0,150,  0);
  searchWordsColorF[4] = MW->MO->SVars.foundWordsColor5F; //QColor( 85,170,255);

  // Цветове за Background
  searchWordsColorB[0] = MW->MO->SVars.foundWordsColor1B; //QColor(255,210,185);
  searchWordsColorB[1] = MW->MO->SVars.foundWordsColor2B; //QColor(255,210,255);
  searchWordsColorB[2] = MW->MO->SVars.foundWordsColor3B; //QColor(225,200,200);
  searchWordsColorB[3] = MW->MO->SVars.foundWordsColor4B; //QColor(185,255,185);
  searchWordsColorB[4] = MW->MO->SVars.foundWordsColor5B; //QColor(220,235,255);

  highlightingRules.clear();
  searchWordsColorIndex = 0;

  if (textView->textMode == TEXT_MODE__SEARCH) return; // Ако този ред се коментира, Highlighter-а ще работи и със searchView - текстът поставен в различните видове скоби ще се оцвети в сиво. Това обаче ще забави показването на резултата от търсенето.

  QTextCharFormat cFormat;
  HighlightingRule rule;

  // 0-9
  //if (MW->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
  //{
  //  if (MW->currentTestament == TESTAMENT__OLD || textView->textMode == TEXT_MODE__SEARCH)
  //    cFormat.setForeground(MW->MO->SVars.oldTestamentColorF);
  //  else
  //    cFormat.setForeground(MW->MO->SVars.newTestamentColorF);
  //}
  //else // Ако е в режим на систематично четене.
  //{
  //  if (MW->currentDailyReadDailyGroup[MW->currentDailyReadChapterInDailyGroup-1].testamentCode == TESTAMENT__OLD)
  //    cFormat.setForeground(MW->MO->SVars.oldTestamentColorF);
  //  else
  //    cFormat.setForeground(MW->MO->SVars.newTestamentColorF);
  //}
  ////cFormat.setFontItalic(false);
  //rule.format = cFormat;
  //rule.pattern = QRegExp(QString("[0-9]"));
  //rule.isCurrentNumber = false;
  //rule.isCustomText = false;
  //highlightingRules.append(rule);

  if (textView->textMode == TEXT_MODE__COMPARE) return; // Ако този ред се коментира, Highlighter-а ще оцветява текста поставен в различните видове скоби в сиво. Това може да доведе до объркване.

  // [text]
  //cFormat.setForeground(MW->MO->SVars.textInBracketsColorF);
  ////cFormat.setFontItalic(false); // Ако този ред се разкоментира, текстът в скоби ще е винаги нормален (не наклонен).
  //cFormat.setFontWeight(QFont::Normal);
  //rule.format = cFormat;
  //rule.pattern = QRegExp(QString("\\[[^\\[]*\\]")); // Това значи всеки текст, който е в [] скоби и който не съдържа [ скоба.
  //rule.isCurrentNumber = false;
  //rule.isCustomText = false;
  //highlightingRules.append(rule);

  // (text)
  //cFormat.setForeground(MW->MO->SVars.textInBracketsColorF);
  ////cFormat.setFontItalic(false); // Ако този ред се разкоментира, текстът в скоби ще е винаги нормален (не наклонен).
  //cFormat.setFontWeight(QFont::Normal);
  //rule.format = cFormat;
  //rule.pattern = QRegExp(QString("\\([^\\(]*\\)")); // Това значи всеки текст, който е в () скоби и който не съдържа ( скоба.
  //rule.isCurrentNumber = false;
  //rule.isCustomText = false;
  //highlightingRules.append(rule);

  // {text}
  cFormat.setForeground(MW->MO->SVars.textInBracketsColorF);
  //cFormat.setFontItalic(false); // Ако този ред се разкоментира, текстът в скоби ще е винаги нормален (не наклонен).
  cFormat.setFontWeight(QFont::Normal);
  rule.format = cFormat;
  rule.pattern = QRegExp(QString("\\{[^\\{]*\\}")); // Това значи всеки текст, който е в {} скоби и който не съдържа { скоба.
  rule.isCurrentNumber = false;
  rule.isCustomText = false;
//  highlightingRules.append(rule);
}

void Highlighter::addPatterns(const QStringList searchWordsList, Qt::CaseSensitivity caseSensitivitySearch)
{
  if (searchWordsList.size() == 0) return;
  HighlightingRule rule;

  // Оцветява откритите думи:
  foreach (QString searchWord, searchWordsList)
  {
    QTextCharFormat cFormat;

    if (MW->MO->SVars.foundWordsBold) cFormat.setFontWeight(QFont::Bold);
    if (MW->MO->SVars.foundWordsUnderline) cFormat.setFontUnderline(true);
    if (MW->MO->SVars.foundWordsColorB) cFormat.setBackground(searchWordsColorB[searchWordsColorIndex]);
    if (MW->MO->SVars.foundWordsColorF) cFormat.setForeground(searchWordsColorF[searchWordsColorIndex]);
    searchWordsColorIndex++;
    if (searchWordsColorIndex == 5) searchWordsColorIndex = 0;
    rule.format = cFormat;
    rule.pattern = QRegExp(searchWord, caseSensitivitySearch);
    rule.isCurrentNumber = false;
    rule.isCustomText = false;
    highlightingRules.append(rule);
  }

  // Самият линк се болдва и оцветява с html стилове още при формирането на открития стих, но ако искаме да се болдне и оцвети и номерът на стиха, това става тук.
  if (textView->textMode == TEXT_MODE__SEARCH)
  {
    QTextCharFormat cFormat;

    // Битие 1:1.
    cFormat.setForeground(MW->MO->SVars.dock2TextColorF);
    cFormat.setFontWeight(QFont::Bold);
    cFormat.setFontItalic(false);
    //cFormat.setFontUnderline(true);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("^[0-9\\w ]+:[0-9]+\\.")); // Всичко от начало на ред, съдържащо само букви, цифри и двуеточие, завършващо с цифра плюс точка.
    rule.isCurrentNumber = false;
    rule.isCustomText = false;
    highlightingRules.append(rule);
  }

  rehighlight(); // Refresh
}

void Highlighter::addCustomPattern(const QString customText)
{
  // Оцветява селектирания текст.
  if (!customText.isEmpty())
  {
    HighlightingRule rule;
    QTextCharFormat cFormat;
    cFormat.setBackground(QColor(255, 239, 11)); // Ярко жълт фон.
    rule.format = cFormat;
    rule.pattern = QRegExp(QRegExp::escape(customText), Qt::CaseInsensitive); // escape връща стринг, в който пред специалните за QRegExp символи е поставена \ за да се третират като обикновени символи.
    rule.isCurrentNumber = false;
    rule.isCustomText = true;
    highlightingRules.append(rule);
    rehighlight(); // Refresh
  }
}

void Highlighter::delCustomPattern(const QString customText)
{
  // Определя и премахва оцветяването на селектирания текст.
  int forDel;
  for (forDel = 0; forDel < highlightingRules.size(); forDel++)
  {
    if (highlightingRules[forDel].isCustomText && highlightingRules[forDel].pattern == QRegExp(QRegExp::escape(customText), Qt::CaseInsensitive))
    {
      break;
    }
  }
  if (forDel < highlightingRules.size())
  {
    highlightingRules.remove(forDel);
    delCustomPattern(customText);
  }
  rehighlight(); // Refresh
}

void Highlighter::delCustomPatterns()
{
  // Определя и премахва оцветяването на всичкия потребителски оцветен текст.
  int forDel;
  for (forDel = 0; forDel < highlightingRules.size(); forDel++)
  {
    if (highlightingRules[forDel].isCustomText)
    {
      break;
    }
  }
  if (forDel < highlightingRules.size())
  {
    highlightingRules.remove(forDel);
    delCustomPatterns();
  }
  rehighlight(); // Refresh
}

void Highlighter::setDictPatterns(DICT_PROPERTIES *DP)
{
  highlightingRules.clear();
  QTextCharFormat cFormat;
  HighlightingRule rule;

  // charSet3
  if (DP->charSet3_Enable && !DP->charSet3_Chars.isEmpty())
  {
    if (QColor::isValidColor(DP->charSet3_Color))
      cFormat.setForeground(QColor(DP->charSet3_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->charSet3_Bold);
    cFormat.setFontItalic(DP->charSet1_Italic);
    cFormat.setFontUnderline(DP->charSet3_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("[%1]").arg(DP->charSet3_Chars), Qt::CaseInsensitive);
    highlightingRules.append(rule);
  }

  // charSet2
  if (DP->charSet2_Enable && !DP->charSet2_Chars.isEmpty())
  {
    if (QColor::isValidColor(DP->charSet2_Color))
      cFormat.setForeground(QColor(DP->charSet2_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->charSet2_Bold);
    cFormat.setFontItalic(DP->charSet2_Italic);
    cFormat.setFontUnderline(DP->charSet2_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("[%1]").arg(DP->charSet2_Chars), Qt::CaseInsensitive);
    highlightingRules.append(rule);
  }

  // charSet1
  if (DP->charSet1_Enable && !DP->charSet1_Chars.isEmpty())
  {
    if (QColor::isValidColor(DP->charSet1_Color))
      cFormat.setForeground(QColor(DP->charSet1_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->charSet1_Bold);
    cFormat.setFontItalic(DP->charSet1_Italic);
    cFormat.setFontUnderline(DP->charSet1_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("[%1]").arg(DP->charSet1_Chars), Qt::CaseInsensitive);
    highlightingRules.append(rule);
  }

  // I. II. IX.
  if (DP->latinNumeration_Enable)
  {
    if (QColor::isValidColor(DP->latinNumeration_Color))
      cFormat.setForeground(QColor(DP->latinNumeration_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->latinNumeration_Bold);
    cFormat.setFontItalic(DP->latinNumeration_Italic);
    cFormat.setFontUnderline(DP->latinNumeration_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("[IVX]+\\."), Qt::CaseSensitive); // Всичко от начало на реда, съдържащо римските цифри, завършващо с точка.
    highlightingRules.append(rule);
  }

  // 1. 2. 9.
  if (DP->arabicNumeration_Enable)
  {
    if (QColor::isValidColor(DP->arabicNumeration_Color))
      cFormat.setForeground(QColor(DP->arabicNumeration_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->arabicNumeration_Bold);
    cFormat.setFontItalic(DP->arabicNumeration_Italic);
    cFormat.setFontUnderline(DP->arabicNumeration_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("[0-9]+\\."), Qt::CaseSensitive); // Всичко от начало на реда, съдържащо латински цифри, завършващо с точка.
    highlightingRules.append(rule);
  }

  // (text)
  if (DP->textInBracket_Enable)
  {
    if (QColor::isValidColor(DP->textInBracket_Color))
      cFormat.setForeground(QColor(DP->textInBracket_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->textInBracket_Bold);
    cFormat.setFontItalic(DP->textInBracket_Italic);
    cFormat.setFontUnderline(DP->textInBracket_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("\\([^\\(]*\\)")); // Това значи всеки текст, който е в () скоби и който не съдържа ( скоба.
    highlightingRules.append(rule);
  }

  // [text]
  if (DP->textInSquareBracket_Enable)
  {
    if (QColor::isValidColor(DP->textInSquareBracket_Color))
      cFormat.setForeground(QColor(DP->textInSquareBracket_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->textInSquareBracket_Bold);
    cFormat.setFontItalic(DP->textInSquareBracket_Italic);
    cFormat.setFontUnderline(DP->textInSquareBracket_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("\\[[^\\[]*\\]")); // Това значи всеки текст, който е в [] скоби и който не съдържа [ скоба.
    highlightingRules.append(rule);
  }

  // {text}
  if (DP->textInBrace_Enable)
  {
    if (QColor::isValidColor(DP->textInBrace_Color))
      cFormat.setForeground(QColor(DP->textInBrace_Color));
    else
      cFormat.clearForeground();
    cFormat.setFontWeight(DP->textInBrace_Bold);
    cFormat.setFontItalic(DP->textInBrace_Italic);
    cFormat.setFontUnderline(DP->textInBrace_Underline);
    rule.format = cFormat;
    rule.pattern = QRegExp(QString("\\{[^\\{]*\\}")); // Това значи всеки текст, който е в {} скоби и който не съдържа { скоба.
    highlightingRules.append(rule);
  }
}

//void Highlighter::setCurrentNumber(const int cNumber)
//{//"^\\W %1\\. [^\n]*"
//  QString text = QString(QString("^\\W %1\\.")).arg(cNumber, 0, 10); // ^ - начало на ред; \W - коя да е НЕ буква. Това ще оцвети първите два интервала, номера на стиха и точката след номера без следващия го интервал.
//  //QString text = QString(QString("^\\W %1\\b")).arg(cNumber, 0, 10); // ^ - начало на ред; \W - коя да е НЕ буква; \b - край на дума. Това ще оцвети първите два интервала и номера на стиха без следващата го точка и интервал.
//
//  // Определя и премахва оцветяването на предишния маркиран ред.
//  int forDel;
//  for (forDel = 0; forDel < highlightingRules.size(); forDel++)
//  {
//    if (highlightingRules[forDel].isCurrentNumber)
//    {
//      break;
//    }
//  }
//  if (forDel < highlightingRules.size()) highlightingRules.remove(forDel);
//
//  QTextCharFormat cFormat;
//  HighlightingRule rule;
//
//  if (MW->readMode == READ_MODE__NORMAL) // Ако е в режим на нормално четене.
//  {
//    if (MW->currentTestament == TESTAMENT__OLD)
//      cFormat.setBackground(MW->MO->SVars.oldTestamentColorF);
//    else
//      cFormat.setBackground(MW->MO->SVars.newTestamentColorF);
//  }
//  else // Ако е в режим на систематично четене.
//  {
//    if (MW->currentDailyReadDailyGroup[MW->currentDailyReadChapterInDailyGroup-1].testamentCode == TESTAMENT__OLD)
//      cFormat.setBackground(MW->MO->SVars.oldTestamentColorF);
//    else
//      cFormat.setBackground(MW->MO->SVars.newTestamentColorF);
//  }
//  cFormat.setForeground(MW->MO->SVars.dock1TextColorB); // Цвят на фона.
//  rule.pattern = QRegExp(text);
//  rule.format = cFormat;
//  rule.isCurrentNumber = true;
//  rule.isCustomText = false;
//  highlightingRules.append(rule);
//
//  rehighlight(); // Refresh
//}

void Highlighter::setEnableHighlighter(bool enable)
{
  enableHighlighter = enable;
}

void Highlighter::highlightBlock(const QString &text)
{
  if (!enableHighlighter) return;
  foreach (const HighlightingRule &rule, highlightingRules)
  {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = expression.indexIn(text, index + length);
    }
  }
  //setCurrentBlockState(0);
}
