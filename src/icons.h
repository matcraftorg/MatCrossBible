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

#ifndef ICONS_H
#define ICONS_H

#include <QObject>
#include <QWheelEvent>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QPen>

class Icons
{
  // UTF-8 енкодинг.

public:
  ///NavigationToolBar
  static QIcon icon_New(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Books(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Bookmark(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ArrowBack(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ArrowForward(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ArrowPrevious(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ArrowNext(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_DailyRead(int width, int height, QColor generalColor, QColor additionalColor);
  ///TextToolBar
  static QIcon icon_Search(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_BibleTexts(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Audio(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ZoomIn(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ZoomOut(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ZoomNormal(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_SelectAll(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Copy(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_CaseSensitive(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_WholeWords(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Statistics(int width, int height, QColor generalColor, QColor additionalColor);
  ///OtherToolBar
  static QIcon icon_Pad(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Dictionary(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ExternalImages(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_WWW(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Projector(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Settings(int width, int height, QColor generalColor, QColor additionalColor);
  ///HelpToolBar
  static QIcon icon_Help(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Info(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_NewAppVersion(int width, int height, QColor generalColor, QColor additionalColor);
  ///FileToolBar
  static QIcon icon_FileMenu(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ExportTxt(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ExportHtm(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_ExportPdf(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_PrintPreview(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Print(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Session(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Exit(int width, int height, QColor generalColor, QColor additionalColor);
  static QIcon icon_Close(int width, int height, QColor generalColor, QColor additionalColor);
};

#endif // ICONS_H
