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

#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <QString>
#include <QBitArray>
#include <QColor>
#include <QFile>

#define STRUCTURE_VERSION             3     // Версия на структурата която използват файловете с текстовете на Библията.

#define TEXT_MODE__SHOW               1     // Режим на показване на глави от Библията.
#define TEXT_MODE__SEARCH             2     // Режим на показване на търсени стихове.
#define TEXT_MODE__COMPARE            3     // Режим на сравняване на глави от Библията.
#define TEXT_MODE__OTHER              4     // Показване на друг текст (например помощна информация).

#define READ_MODE__NORMAL             1     // Режим на нормално четене.
#define READ_MODE__DAILY_READ         2     // Режим на ежедневно четене.

#define NUMERATION__1                 1     // Номерация 1 на стиховете (разликите са само в Псалми - от Псалм 9 до Псалм 147).
#define NUMERATION__2                 2     // Номерация 2 на стиховете.

#define BOOKS_ORDER__WESTERN          1     // Ред на книгите в Новия Завет. Западен стандарт.
#define BOOKS_ORDER__EASTERN          2     // Ред на книгите в Новия Завет. Източен стандарт.

#define VERSE_STRUCT__NUMBER_ONLY     1     // Структура на показаните стихове: показва само номера на стиха.
#define VERSE_STRUCT__MIN_BOOK_NAME   2     // Структура на показаните стихове: показва съкратено име на главата + номера на стиха.
#define VERSE_STRUCT__SHORT_BOOK_NAME 3     // Структура на показаните стихове: показва късо име на главата + номера на стиха.

#define DOCK_TYPE__UNSET              0     // Тип на раздела: неустановен.
#define DOCK_TYPE__HOLY_TEXT_VIEW     1     // Тип на раздела: показване на глави от Библията.
#define DOCK_TYPE__SEARCH_VIEW        2     // Тип на раздела: резултати от търсене в Библията (това не е раздел, но се третира като раздел за улесняване при работа със сесиите).
#define DOCK_TYPE__DICTIONARY         3     // Тип на раздела: речник или коментар.

#define OT_START_INDEX                0     // Абсолютен индекс на първия стих от Стария Завет.
#define DC_START_INDEX                23491 // Абсолютен индекс на първия стих от Второканоничните книги. DC = Deuterocanonical
#define NT_START_INDEX                30032 // Абсолютен индекс на първия стих от Новия Завет.
#define ONT_END_INDEX                 37992 // Абсолютен индекс на последния стих от Библията.
#define MAX_VERSES                    37993 // Максимален брой на стиховете (редовете) в универсалната структура.
#define MAX_CHAPTERS                  1380  // Максимален брой на главите в универсалната структура.
#define MAX_BOOKMARKS                 100   // Максимален брой на отметките.
#define DAILY_READ_TOTAL_DAYS         270   // За колко дни ще се прочете цялата Библия в режим на ежедневно четене.

#define SEARCH_METHOD__RANDOM         1     // Търсене по произволна част от дума.
#define SEARCH_METHOD__ROOT           2     // Търсене по корен на дума.
#define SEARCH_METHOD__WORD           3     // Търсене по точна дума.

#define SEARCH_WORDS_LOGIC__ALL       1     // Всички търсени думи.
#define SEARCH_WORDS_LOGIC__ANY       2     // Поне една от думите.
#define SEARCH_WORDS_LOGIC__PHRASE    3     // Фраза.

#define POSITION_TOP                  1     // Позиция горе  (само за лентата с инструменти).
#define POSITION_BOTTOM               2     // Позиция долу  (само за лентата с инструменти).
#define POSITION_LEFT                 3     // Позиция ляво  (само за дървото с книгите).
#define POSITION_RIGHT                4     // Позиция дясно (само за дървото с книгите).

#define PROXY__NO_PROXY               0     // Без прокси.
#define PROXY__HTTP_PROXY             1     // Http прокси.
#define PROXY__SOCKS_5_PROXY          2     // Socks5 прокси.

typedef QList<quint8>  QUInt8List; 
typedef QList<quint16> QUInt16List; 
typedef QList<quint32> QUInt32List; 
typedef QList<quint64> QUInt64List; 
typedef QList<qint8>   QInt8List; 
typedef QList<qint16>  QInt16List; 
typedef QList<qint32>  QInt32List; 
typedef QList<qint64>  QInt64List; 

struct BIBLE_TEXT
{
  QFile   *file;              // Файл.
  QString  fileName;          // Име на файла (плюс пътя и разширението му).
  QString  fileBaseName;      // Име на файла (без пътя и без разширението му).
  QString  name;              // Име на текста, което ще се изписва в TextView.
  QString  short_description; // Късо описание.
  QString  description;       // Описание.
  QString  nativeFontFamily;  // Собствен шрифт на текста (зададен е в hbt файла).
  QString  fontFamily;        // Собствен шрифт на текста + шрифта на текста по подразбиране (зададен в настройките на програмата).
  QString  language;          // На какъв език е текстът.
  QString  lastModifyDate;    // Дата на последната промяна на самия текст, а не на файла или структурата на файла.
  bool     nativeVerseNum;    // Дали има собствена номерация на стиховете.
  quint8  *booksExtArr;       // Указател към масива с главите (booksExtArr).
  quint8  *chaptersExtArr;    // Указател към масива с главите (chapters66ExtArr или chapters77ExtArr).
  Qt::LayoutDirection layoutDirection; // Посока на изписване на текста (от ляво на дясно или от дясно на ляво).
  qint32   seekBookArr[77];   // Масив съдържащ отместването във файла на всяка книга.
  //qint32   seekVerseArr[MAX_VERSES];   // Масив съдържащ отместването във файла на всеки стих.
};

struct SEARCH_OPTIONS       // Опциите за търсене в текста на Библията. Използва се в метода Search.
{
  quint8 searchMethod;      // Метод на търсене.
  quint8 searchWordsLogic;  // Логика на търсене.
  Qt::CaseSensitivity caseSensitivitySearch; // Различава главни/малки букви.
};

struct BOOKMARKS
{
  QString label;     // Етикета, който ще се показва в панела на отметките.
  quint16 absIndex;  // Абсолютният индекс на стиха в глобалната структура. Започва от 0.
  QString verseCode; // Реалният номер на стиха, който се взима от самия стих, за който се прави отметка (или въпросителен знак, ако номерът не е бил определен). Необходим е единствено за да се запише в етикета.
};

//struct LOCATION
//{
//  quint8  bookCode;
//  quint8  chapterCode;
//  quint8  verseCode;
//  quint16 absIndex;  // Абсолютният индекс на стиха в глобалната структура. Започва от 0.
//};

struct AUDIO_LOCATION_FILE
{
  QString fileName;         // Име на файла без пътя.
  QString filePath;         // Име на файла с пътя.
  QString shortDescription; // Късо описание (което ще се изписва в комбобок).
};

struct PROJECTOR_HISTORY
{
  quint16 absIndex;  // Абсолютният индекс на стиха в глобалната структура.
  QString bibleText; // Име на текста.
  QString chapter;   // Име на книгата + номера на главата.
  QString verse;     // Самият стих (с номера на стиха, ако има такъв).
  QString nativeFontFamily; // Шрифт на този стих.
};

struct DICT_PROPERTIES
{
  int     structureVersion;
  QString lastModifyDate;
  QString fontFamily;
  Qt::LayoutDirection layoutDirection;
  QString dictName;
  QString dictVersion;
  QString dictAuthor;
  QString dictShortDescription;
  QString dictDescription;

  bool    charSet1_Enable;
  QString charSet1_Chars;
  QString charSet1_Color;
  int     charSet1_Bold; // QFont::Normal QFont::Bold
  bool    charSet1_Italic;
  bool    charSet1_Underline;

  bool    charSet2_Enable;
  QString charSet2_Chars;
  QString charSet2_Color;
  int     charSet2_Bold; // QFont::Normal QFont::Bold
  bool    charSet2_Italic;
  bool    charSet2_Underline;

  bool    charSet3_Enable;
  QString charSet3_Chars;
  QString charSet3_Color;
  int     charSet3_Bold; // QFont::Normal QFont::Bold
  bool    charSet3_Italic;
  bool    charSet3_Underline;

  bool    textInBracket_Enable;
  QString textInBracket_Color;
  int     textInBracket_Bold; // QFont::Normal QFont::Bold
  bool    textInBracket_Italic;
  bool    textInBracket_Underline;

  bool    textInSquareBracket_Enable;
  QString textInSquareBracket_Color;
  int     textInSquareBracket_Bold; // QFont::Normal QFont::Bold
  bool    textInSquareBracket_Italic;
  bool    textInSquareBracket_Underline;

  bool    textInBrace_Enable;
  QString textInBrace_Color;
  int     textInBrace_Bold; // QFont::Normal QFont::Bold
  bool    textInBrace_Italic;
  bool    textInBrace_Underline;

  bool    latinNumeration_Enable;
  QString latinNumeration_Color;
  int     latinNumeration_Bold; // QFont::Normal QFont::Bold
  bool    latinNumeration_Italic;
  bool    latinNumeration_Underline;

  bool    arabicNumeration_Enable;
  QString arabicNumeration_Color;
  int     arabicNumeration_Bold; // QFont::Normal QFont::Bold
  bool    arabicNumeration_Italic;
  bool    arabicNumeration_Underline;

  bool    equalSymbols_Enable;
  QStringList equalSymbols1;
  QStringList equalSymbols2;
};

struct SETTINGS_VARIABLES           // Съдържа настройките на потребителя.
{
  // Language
  QString currentAppTranslation;    // Помощна. Използва се само във формата за настройки за установяване дали има избран друг език.
  QString currentBooksTranslation;  // Запомня езика, на който ще се изписват книгите. Ако е празен стринг - ще взима от TR файла.
  // Colors
  QColor  dock1TextColorF;          // Цвят на текста в стандартен раздел.
  QColor  dock1TextColorB;          // Цвят на фона в стандартен раздел.
  QString dock1BGImage;             // Картинка за фон на стандартен раздел.
  QColor  dock2TextColorF;          // Цвят на текста в специализиран раздел/панел.
  QColor  dock2TextColorB;          // Цвят на фона в специализиран раздел/панел.
  QString dock2BGImage;             // Картинка за фон на специализиран раздел/панел.
  QColor  oldTestamentColorF;       // Цвят на имената на книгите и номерата на стиховете в Стария Завет.
  QColor  oldTestamentColorFA;      // Цвят на имената на книгите в Стария Завет, но полу-прозрачен. Ще се използва главно за цвят на Второканоничните книги в панела с книгите и отметките и при генериране на HTML MatCrossBible.
  QColor  newTestamentColorF;       // Цвят на имената на книгите и номерата на стиховете в Новия Завет.
  int     oldTestamentAlphaF;       // Alpha съставка на цвета на имената на книгите и номерата на стиховете в Стария Завет.
  int     newTestamentAlphaF;       // Alpha съставка на цвета на имената на книгите и номерата на стиховете в Новия Завет.
  QColor  textInBracketsColorF;     // Цвят на текста в скоби (оцветява се от highlighter-а).
  QColor  JesusWordsColorF;         // Цвят на думите на Исус Христос.
  bool    JesusWordsColorFEnable;   // Разрешава оцветяването на думите на Исус Христос.
  QColor  compareEqColorF;          // Цвят на еднаквите думи в режим на сравняване.
  QColor  compareNoEqColorF;        // Цвят на различните думи в режим на сравняване.
  QColor  appColorF;                // Цвят на прозорците и панелите с инструменти.
  QColor  appColorB;                // Цвят на фона на прозорците и панелите с инструменти и цвят на иконите.
  bool    docks3DTitleBar;          // Указва, дали заглавните ленти да са 3D.
  // View
  quint8  TMenuPosition;            // Позиция на TMenu и другите ленти с инструменти (горе или долу).
  int     TMenuIconSize;            // Големина на иконите в TMenu.
  int     otherToolBarFontSize;     // Големина на шрифта на бутоните в останалите тул-барове.
  quint8  booksToolBarPosition;     // Позиция на панела с книгите и отметките (ляво или дясно).
  int     booksToolBarFontSize;     // Големина на шрифта на панела с книгите и отметките.
  quint8  searchToolBarPosition;    // Позиция на панела с инструменти за търсене в Библията (ляво или дясно).
  int     searchToolBarWidth;       // Широчина на панела с инструменти за търсене в Библията.
  int     searchToolBarFontSize;    // Големина на шрифта на панела с инструменти за търсене в Библията.
  quint8  projectorToolBarPosition; // Позиция на панела с инструменти за проектора (ляво или дясно).
  int     projectorToolBarPrevSize; // Големина (широчина) на малкия екран на проектора.
  int     projectorToolBarFontSize; // Големина на шрифта на панела с инструменти за проектора.
  QString GUIStyle;                 // Стил на потребителския интерфейс (GUI).
  // Text
  int     globalFontSize;           // Големина на шрифта за цялото приложение (менюта, подсказки и всичко, за което не е указана друга големина на шрифта).
  bool    globalFontAntialias;      // Antialias на шрифта за цялото приложение.
  QString fontFamily;               // Шрифт на текста.
  int     fontSize;                 // Големина на шрифта.
  bool    verseNumberBold;          // Удебелен шрифт на номерата на стиховете в режим четене.
  bool    verseNumberSup;           // Умален (sup) шрифт на номерата на стиховете в режим четене.
  quint8  verseStruct;              // Структура на показаните стихове: показва само номера на стиха или номера плюс съкратено или късото име на книгата.
  quint8  newNumeration;            // Указва коя да бъде подразбиращата се номерация при показване на два и повече текста с различни номерации на стиховете (разликите са само в Псалми - от Псалм 9 до Псалм 147). Това е параметърът, който се променя от настройките и влиза в сила след рестарт.
  quint8  currentNumeration;        // Указва коя да бъде подразбиращата се номерация при показване на два и повече текста с различни номерации на стиховете (разликите са само в Псалми - от Псалм 9 до Псалм 147). Инициализира се при пускане на програмата и не се променя повече, дори при промяна от настройките.
  quint8  newBooksOrder;            // Указва подредбата (реда) на книгите в Новия Завет. Това е параметърът, който се променя от настройките и влиза в сила след рестарт.
  quint8  currentBooksOrder;        // Указва подредбата (реда) на книгите в Новия Завет. Инициализира се при пускане на програмата и не се променя повече, дори при промяна от настройките.
  bool    newShowDeutrocanonical;   // Указва дали да се показват Второканоничните книги от Стария Завет. Това е параметърът, който се променя от настройките и влиза в сила след рестарт.
  bool    newShowDeuterocanonical;  // Указва дали да се показват Второканоничните книги от Стария Завет. Това е параметърът, който се променя от настройките и влиза в сила след рестарт.
  bool    showDeuterocanonical;     // Указва дали да се показват Второканоничните книги от Стария Завет. Инициализира се при пускане на програмата и не се променя повече, дори при промяна от настройките.
  bool    showAbsVerseNumber;       // Указва дали да се показват глобалните (абсолютни) номера на стиховете.
  // Search
  bool    foundWordsBold;           // Търсените думи се удебеляват.
  bool    foundWordsUnderline;      // Търсените думи се подчертават.
  bool    foundWordsColorF;         // Търсените думи се оцветяват.
  bool    foundWordsColorB;         // Фона на търсените думи се оцветява.
  QColor  foundWordsColor1F;        // Цвят на първата, шестата и т.н. търсени думи.
  QColor  foundWordsColor2F;        // Цвят на втората, седмата и т.н. търсени думи.
  QColor  foundWordsColor3F;        // Цвят на третата, осмата и т.н. търсени думи.
  QColor  foundWordsColor4F;        // Цвят на четвъртата, деветата и т.н. търсени думи.
  QColor  foundWordsColor5F;        // Цвят на петата, десетата и т.н. търсени думи.
  QColor  foundWordsColor1B;        // Фонов цвят на първата, шестата и т.н. търсени думи.
  QColor  foundWordsColor2B;        // Фонов цвят на втората, седмата и т.н. търсени думи.
  QColor  foundWordsColor3B;        // Фонов цвят на третата, осмата и т.н. търсени думи.
  QColor  foundWordsColor4B;        // Фонов цвят на четвъртата, деветата и т.н. търсени думи.
  QColor  foundWordsColor5B;        // Фонов цвят на петата, десетата и т.н. търсени думи.
  QColor  extraSelectColor1B;       // Фонов цвят на текста, съвпадащ със селектирания текст, селектиран чрез мишката (първа мултиселекция).
  QColor  extraSelectColor2B;       // Фонов цвят на текста, съвпадащ със селектирания текст, селектиран чрез контекстното меню (втора мултиселекция).
  QString searchTargetText;         // Библейския текст, в който ще се търси. Това е помощна променлива - вместо долния индекс, запомня името на текста в настройките, а после от името се изчислява долния индекс.
  quint8  searchTargetTextIndex;    // Индекс на Библейския текст, в който ще се търси.
  // Audio
  QString currentAudioLocation;     // Име на текущо избрания AudioLocation файл.
  // Other
  QString pathToSettings;           // Път до директорията, където се запомнят настройките, бележника и другите ресурси. Тази помощна променлива не се записва в INI файла, а се използва само във формата за настройки, за установяване на промяна.
  QString MatCrossBibleURL;         // Линк към официалния сайт на MatCrossBible.
  quint8  proxyType;                // Proxy Type (NoProxy=0, HttpProxy=1 or Socks5Proxy=2).
  QString proxyHostName;            // Proxy HostName (192.168.2.222).
  quint16 proxyPort;                // Proxy Port (3128).
  bool    enableTrayIcon;           // Минимизира прозореца в системния трей при натискане на бутона за затваряне в заглавната лента на прозореца.
};
#endif // __DATATYPES_H__
