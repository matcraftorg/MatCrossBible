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

#include "icons.h"

///NavigationToolBar ---------------------------------------------------------------------------------------------------------------------
QIcon Icons::icon_New(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff,  10.5*coeff),  QPointF(13.5*coeff, 10.5*coeff)}, 2); // Стандартен плюс.
  //painter.drawPolyline(new QPointF[2]{QPointF(10.5*coeff, 7.5*coeff),   QPointF(10.5*coeff, 13.5*coeff)}, 2); //
  //painter.drawPolyline(new QPointF[2]{QPointF(5.5*coeff, 7.5*coeff),  QPointF(9.5*coeff, 7.5*coeff)}, 2); // По-малък плюс.
  //painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 5.5*coeff),  QPointF(7.5*coeff, 9.5*coeff)}, 2); //

  return QIcon(pixmap);
}

QIcon Icons::icon_Books(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),    QPointF(10.5*coeff, 1.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 7.5*coeff),    QPointF(16.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 13.5*coeff),   QPointF(16.5*coeff, 13.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 19.5*coeff),   QPointF(16.5*coeff, 19.5*coeff)}, 2);
  
  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[3]{QPointF(16.5*coeff, 1.5*coeff),    QPointF(22.5*coeff, 1.5*coeff),    QPointF(22.5*coeff, 22.5*coeff)}, 3);

  // Старата икона (дърво):
  //pen.setBrush(generalColor);
  //painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[3]{QPointF(1.5*coeff, 1.5*coeff),    QPointF(1.5*coeff, 16.5*coeff),    QPointF(13.5*coeff, 16.5*coeff)}, 3);
  //painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 4.5*coeff),    QPointF(13.5*coeff, 4.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 10.5*coeff),   QPointF(13.5*coeff, 10.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 22.5*coeff),   QPointF(13.5*coeff, 22.5*coeff)}, 2);
  //
  //pen.setBrush(additionalColor);
  //painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[2]{QPointF(19.5*coeff, 4.5*coeff),    QPointF(22.5*coeff, 4.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(19.5*coeff, 10.5*coeff),   QPointF(22.5*coeff, 10.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(19.5*coeff, 16.5*coeff),   QPointF(22.5*coeff, 16.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(19.5*coeff, 22.5*coeff),   QPointF(22.5*coeff, 22.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Bookmark(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[8]{QPointF(13.5*coeff, 7.5*coeff),    QPointF(10.5*coeff, 7.5*coeff),    QPointF(4.5*coeff, 1.5*coeff),    QPointF(4.5*coeff, 15.5*coeff),    QPointF(12.5*coeff, 22.5*coeff),    QPointF(19.5*coeff, 15.5*coeff),    QPointF(19.5*coeff, 1.5*coeff),    QPointF(13.5*coeff, 1.5*coeff)}, 8);

  return QIcon(pixmap);
}

QIcon Icons::icon_ArrowBack(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[9]{QPointF(13.5*coeff, 7.5*coeff),    QPointF(10.5*coeff, 7.5*coeff),    QPointF(10.5*coeff, 1.5*coeff),    QPointF(1.5*coeff, 12.5*coeff),    QPointF(10.5*coeff, 22.5*coeff),    QPointF(10.5*coeff, 16.5*coeff),    QPointF(22.5*coeff, 16.5*coeff),    QPointF(22.5*coeff, 10.5*coeff),    QPointF(19.5*coeff, 7.5*coeff)}, 9);

  return QIcon(pixmap);
}

QIcon Icons::icon_ArrowForward(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[9]{QPointF(1.5*coeff, 10.5*coeff),    QPointF(1.5*coeff, 7.5*coeff),    QPointF(13.5*coeff, 7.5*coeff),    QPointF(13.5*coeff, 1.5*coeff),    QPointF(22.5*coeff, 12.5*coeff),    QPointF(13.5*coeff, 22.5*coeff),    QPointF(13.5*coeff, 16.5*coeff),    QPointF(3.5*coeff, 16.5*coeff),    QPointF(1.5*coeff, 14.5*coeff)}, 9);

  return QIcon(pixmap);
}

QIcon Icons::icon_ArrowPrevious(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[3]{QPointF(16.5*coeff, 1.5*coeff),    QPointF(4.5*coeff, 12.5*coeff),    QPointF(16.5*coeff, 22.5*coeff)}, 3);

  return QIcon(pixmap);
}

QIcon Icons::icon_ArrowNext(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[3]{QPointF(7.5*coeff, 1.5*coeff),    QPointF(19.5*coeff, 12.5*coeff),    QPointF(7.5*coeff, 22.5*coeff)}, 3);

  return QIcon(pixmap);
}

QIcon Icons::icon_DailyRead(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(((qreal)width)/2.0, ((qreal)height)/2.0), ((qreal)width-penWidth)/2.0, ((qreal)height-penWidth)/2.0);

  pen.setBrush(additionalColor);
  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[3]{QPointF(12.0*coeff, 8.0*coeff),    QPointF(12.0*coeff, 12.0*coeff),    QPointF(16.0*coeff, 16.0*coeff)}, 3);

  return QIcon(pixmap);
}

///TextToolBar ---------------------------------------------------------------------------------------------------------------------
QIcon Icons::icon_Search(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawArc(QRectF(1.5*coeff, 1.5*coeff, 15.0*coeff, 15.0*coeff), 40 * 16, 320 * 16); // Дъга започваща от 40 градуса и продължаваща 320 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  painter.drawPolyline(new QPointF[2]{QPointF(17.5*coeff, 17.5*coeff),    QPointF(22.5*coeff, 22.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_BibleTexts(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 15.0*coeff, 15.0*coeff));
  
  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(7.5*coeff, 7.5*coeff, 15.0*coeff, 15.0*coeff));

  // Старата икона (Правоъгълник с буква T вътре):
  //pen.setBrush(generalColor);
  //painter.setPen(pen);  
  //painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));
  //
  //pen.setBrush(additionalColor);
  //painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[2]{QPointF(10.5*coeff, 7.5*coeff),   QPointF(10.5*coeff, 13.5*coeff)}, 2);
  //painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 7.5*coeff),    QPointF(13.5*coeff, 7.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Audio(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 7.5*coeff, 9.0*coeff, 9.0*coeff));

  painter.drawPolygon(new QPointF[4]{QPointF(13.5*coeff, 17.5*coeff),   QPointF(22.5*coeff, 22.5*coeff),   QPointF(22.5*coeff, 1.5*coeff),   QPointF(13.5*coeff, 6.5*coeff)}, 4);

  return QIcon(pixmap);
}

QIcon Icons::icon_ZoomIn(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(4.5*coeff, 1.5*coeff),   QPointF(4.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),   QPointF(7.5*coeff, 1.5*coeff)}, 2);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(13.5*coeff, 7.5*coeff),   QPointF(13.5*coeff, 19.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 13.5*coeff),   QPointF(19.5*coeff, 13.5*coeff)}, 2);

  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawArc(QRectF(4.0*coeff, 4.0*coeff, 19.0*coeff, 19.0*coeff), 170 * 16, 310 * 16); // Дъга започваща от 170 градуса и продължаваща 310 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  return QIcon(pixmap);
}

QIcon Icons::icon_ZoomOut(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(4.5*coeff, 1.5*coeff),   QPointF(4.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),   QPointF(7.5*coeff, 1.5*coeff)}, 2);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 13.5*coeff),   QPointF(19.5*coeff, 13.5*coeff)}, 2);

  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawArc(QRectF(4.0*coeff, 4.0*coeff, 19.0*coeff, 19.0*coeff), 170 * 16, 310 * 16); // Дъга започваща от 170 градуса и продължаваща 310 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  return QIcon(pixmap);
}

QIcon Icons::icon_ZoomNormal(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(4.5*coeff, 1.5*coeff),   QPointF(4.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),   QPointF(7.5*coeff, 1.5*coeff)}, 2);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(9.5*coeff, 17.5*coeff),   QPointF(17.5*coeff, 9.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(9.5*coeff, 9.5*coeff),    QPointF(17.5*coeff, 17.5*coeff)}, 2);

  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawArc(QRectF(4.0*coeff, 4.0*coeff, 19.0*coeff, 19.0*coeff), 170 * 16, 310 * 16); // Дъга започваща от 170 градуса и продължаваща 310 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  return QIcon(pixmap);
}

QIcon Icons::icon_SelectAll(int width, int height, QColor generalColor, QColor /*additionalColor*/)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  //qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[3]{QPointF( 1.5*coeff,  4.5*coeff),    QPointF( 1.5*coeff,  1.5*coeff),    QPointF( 4.5*coeff,  1.5*coeff)}, 3);
  painter.drawPolyline(new QPointF[3]{QPointF(19.5*coeff,  1.5*coeff),    QPointF(22.5*coeff,  1.5*coeff),    QPointF(22.5*coeff,  4.5*coeff)}, 3);
  painter.drawPolyline(new QPointF[3]{QPointF(22.5*coeff, 19.5*coeff),    QPointF(22.5*coeff, 22.5*coeff),    QPointF(19.5*coeff, 22.5*coeff)}, 3);
  painter.drawPolyline(new QPointF[3]{QPointF( 4.5*coeff, 22.5*coeff),    QPointF( 1.5*coeff, 22.5*coeff),    QPointF( 1.5*coeff, 19.5*coeff)}, 3);

  painter.drawPolyline(new QPointF[2]{QPointF(10.5*coeff,  1.5*coeff),    QPointF(13.5*coeff,  1.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(22.5*coeff, 10.5*coeff),    QPointF(22.5*coeff, 13.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(13.5*coeff, 22.5*coeff),    QPointF(10.5*coeff, 22.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF( 1.5*coeff, 13.5*coeff),    QPointF( 1.5*coeff, 10.5*coeff)}, 2);

  // Старата икона (V с пресечна черта):
  //painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[3]{QPointF(3.5*coeff, 6.5*coeff),    QPointF(12.0*coeff, 22.5*coeff),    QPointF(20.5*coeff, 1.5*coeff)}, 3);
  //
  //pen.setBrush(additionalColor);
  //pen.setWidth(penWidthS);
  //painter.setPen(pen);  
  //painter.drawPolyline(new QPointF[2]{QPointF(3.0*coeff, 14.0*coeff),    QPointF(21.0*coeff, 10.0*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Copy(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolygon(new QPointF[4]{QPointF(7.5*coeff, 11.5*coeff),   QPointF(7.5*coeff, 22.5*coeff),   QPointF(22.5*coeff, 15.5*coeff),   QPointF(22.5*coeff, 4.5*coeff)}, 4);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[5]{QPointF(16.5*coeff, 3.5*coeff),    QPointF(16.5*coeff, 1.5*coeff),    QPointF(1.5*coeff, 8.5*coeff),    QPointF(1.5*coeff, 19.5*coeff),    QPointF(4.0*coeff, 18.250*coeff)}, 5);

  return QIcon(pixmap);
}

QIcon Icons::icon_CaseSensitive(int width, int height, QColor generalColor, QColor additionalColor)
{
  // Тази икона е на половин височина.
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 9.0*coeff, 9.0*coeff));

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(16.5*coeff, 4.5*coeff, 6.0*coeff, 6.0*coeff));

  return QIcon(pixmap);
}

QIcon Icons::icon_WholeWords(int width, int height, QColor generalColor, QColor additionalColor)
{
  // Тази икона е на половин височина.
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(7.5*coeff, 1.5*coeff, 9.0*coeff, 9.0*coeff));

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),    QPointF(1.5*coeff, 10.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(22.5*coeff, 1.5*coeff),   QPointF(22.5*coeff, 10.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Statistics(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(5.5*coeff, 5.5*coeff), 4.0*coeff, 4.0*coeff);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(18.5*coeff, 18.5*coeff), 4.0*coeff, 4.0*coeff);
  painter.drawPolyline(new QPointF[2]{QPointF(5.5*coeff, 20.5*coeff),   QPointF(18.5*coeff, 3.5*coeff)}, 2);

  return QIcon(pixmap);
}

///OtherToolBar ---------------------------------------------------------------------------------------------------------------------
QIcon Icons::icon_Pad(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 7.5*coeff),    QPointF(16.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 13.5*coeff),   QPointF(16.5*coeff, 13.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Dictionary(int width, int height, QColor generalColor, QColor /*additionalColor*/)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));

  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 7.5*coeff),    QPointF(22.5*coeff, 7.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_ExternalImages(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolygon(new QPointF[8]{QPointF(12.0*coeff, 20.5*coeff),   QPointF(15.0*coeff, 15.0*coeff),   QPointF(20.5*coeff, 12.0*coeff),   QPointF(15.0*coeff, 9.0*coeff),   QPointF(12.0*coeff, 3.5*coeff),   QPointF(9.0*coeff, 9.0*coeff),   QPointF(3.5*coeff, 12.0*coeff),   QPointF(9.0*coeff, 15.0*coeff)}, 8);

  return QIcon(pixmap);
}

QIcon Icons::icon_WWW(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(additionalColor);
  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[5]{QPointF(21.74*coeff, 8.84*coeff),    QPointF(18.62*coeff, 5.70*coeff),    QPointF(15.94*coeff, 5.12*coeff),    QPointF(12.89*coeff, 4.15*coeff),    QPointF(14.30*coeff, 2.59*coeff)}, 5);
  painter.drawPolyline(new QPointF[5]{QPointF(6.12*coeff, 20.00*coeff),    QPointF(5.25*coeff, 16.85*coeff),    QPointF(5.45*coeff, 13.65*coeff),    QPointF(3.71*coeff, 12.25*coeff),    QPointF(2.18*coeff, 10.31*coeff)}, 5);
  painter.drawPolyline(new QPointF[16]{QPointF(15.66*coeff, 18.28*coeff),    QPointF(17.67*coeff, 15.82*coeff),    QPointF(17.77*coeff, 13.22*coeff),    QPointF(19.32*coeff, 11.05*coeff),    QPointF(17.28*coeff, 7.90*coeff),    QPointF(15.30*coeff, 7.54*coeff),    QPointF(13.08*coeff, 6.83*coeff),    QPointF(10.87*coeff, 6.84*coeff),    QPointF(9.12*coeff, 8.43*coeff),    QPointF(8.75*coeff, 10.46*coeff),    QPointF(9.81*coeff, 11.70*coeff),    QPointF(12.65*coeff, 11.94*coeff),    QPointF(13.54*coeff, 13.87*coeff),    QPointF(13.58*coeff, 16.12*coeff),    QPointF(14.19*coeff, 18.12*coeff),    QPointF(15.66*coeff, 18.28*coeff)}, 16);

  pen.setBrush(generalColor);
  pen.setWidth(penWidth);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(((qreal)width)/2.0, ((qreal)height)/2.0), ((qreal)width-penWidth)/2.0, ((qreal)height-penWidth)/2.0);

  return QIcon(pixmap);
}

QIcon Icons::icon_Projector(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = penWidth - ((qreal)width)/24; // По-малък размер (ако основния е 3 точки, този е 2 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolygon(new QPointF[4]{QPointF(19.5*coeff, 22.5*coeff),   QPointF(22.5*coeff, 19.5*coeff),   QPointF(22.5*coeff, 8.5*coeff),   QPointF(8.5*coeff, 22.5*coeff)}, 4);
  //painter.drawPolygon(new QPointF[4]{QPointF(19.5*coeff, 1.5*coeff),   QPointF(8.5*coeff, 1.5*coeff),   QPointF(22.5*coeff, 15.5*coeff),   QPointF(22.5*coeff, 4.5*coeff)}, 4);

  pen.setBrush(additionalColor);
  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(10.0*coeff, 15.0*coeff),    QPointF(1.0*coeff, 8.0*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(12.0*coeff, 12.0*coeff),    QPointF(1.0*coeff, 1.0*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(15.0*coeff, 10.0*coeff),    QPointF(8.0*coeff, 1.0*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Settings(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),    QPointF(22.5*coeff, 1.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 7.5*coeff),    QPointF(22.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 16.5*coeff),   QPointF(22.5*coeff, 16.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 22.5*coeff),   QPointF(22.5*coeff, 22.5*coeff)}, 2);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(4.5*coeff, 1.5*coeff),    QPointF(4.5*coeff, 4.0*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(15.5*coeff, 7.5*coeff),   QPointF(15.5*coeff, 10.0*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(18.5*coeff, 16.5*coeff),  QPointF(18.5*coeff, 14.0*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(9.5*coeff, 22.5*coeff),   QPointF(9.5*coeff, 20.0*coeff)}, 2);

  return QIcon(pixmap);
}

///HelpToolBar ---------------------------------------------------------------------------------------------------------------------
QIcon Icons::icon_Help(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));

  QFont font("Serif", height/2, QFont::Bold, false);
  font.setStyleHint(QFont::SansSerif, QFont::PreferAntialias);
  painter.setFont(font);

  pen.setBrush(additionalColor);
  painter.setPen(pen); 
  painter.drawText(QRectF(0.0, 0.0, width, height), Qt::AlignCenter, QString("?"));  

  return QIcon(pixmap);
}

QIcon Icons::icon_Info(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  pen.setBrush(generalColor);
  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff));

  QFont font("Monospace", height/2, QFont::Bold, true);
  font.setStyleHint(QFont::Monospace, QFont::PreferAntialias);
  painter.setFont(font);

  pen.setBrush(additionalColor);
  painter.setPen(pen); 
  painter.drawText(QRectF(0.0, 0.0, width, height), Qt::AlignCenter, QString("i"));  

  return QIcon(pixmap);
}

QIcon Icons::icon_NewAppVersion(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolygon(new QPointF[8]{QPointF(12.0*coeff, 20.5*coeff),   QPointF(15.0*coeff, 15.0*coeff),   QPointF(20.5*coeff, 12.0*coeff),   QPointF(15.0*coeff, 9.0*coeff),   QPointF(12.0*coeff, 3.5*coeff),   QPointF(9.0*coeff, 9.0*coeff),   QPointF(3.5*coeff, 12.0*coeff),   QPointF(9.0*coeff, 15.0*coeff)}, 8); // Същото като на Map.
  painter.drawPolygon(new QPointF[8]{QPointF(12.0*coeff, 16.25*coeff),   QPointF(18.0*coeff, 18.0*coeff),   QPointF(16.25*coeff, 12.0*coeff),   QPointF(18.0*coeff, 6.0*coeff),   QPointF(12.0*coeff, 7.75*coeff),   QPointF(6.0*coeff, 6.0*coeff),   QPointF(7.75*coeff, 12.0*coeff),   QPointF(6.0*coeff, 18.0*coeff)}, 8);

  return QIcon(pixmap);
}

///FileToolBar ---------------------------------------------------------------------------------------------------------------------
QIcon Icons::icon_FileMenu(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[4]{QPointF(1.5*coeff, 19.5*coeff),    QPointF(1.5*coeff, 22.5*coeff),    QPointF(22.5*coeff, 22.5*coeff),    QPointF(22.5*coeff, 19.5*coeff)}, 4);
  painter.drawPolyline(new QPointF[5]{QPointF(1.5*coeff, 13.5*coeff),    QPointF(1.5*coeff, 1.5*coeff),    QPointF(17.5*coeff, 1.5*coeff),    QPointF(22.5*coeff, 6.5*coeff),    QPointF(22.5*coeff, 13.5*coeff)}, 5);

  return QIcon(pixmap);
}

QIcon Icons::icon_ExportTxt(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 1.5*coeff),     QPointF(7.5*coeff, 16.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 22.5*coeff),     QPointF(13.5*coeff, 22.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[3]{QPointF(1.5*coeff, 13.5*coeff),     QPointF(7.5*coeff, 19.5*coeff),     QPointF(13.5*coeff, 13.5*coeff)}, 3);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(19.5*coeff, 1.5*coeff),     QPointF(19.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 1.5*coeff),     QPointF(22.5*coeff, 1.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_ExportHtm(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 1.5*coeff),     QPointF(7.5*coeff, 16.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 22.5*coeff),     QPointF(13.5*coeff, 22.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[3]{QPointF(1.5*coeff, 13.5*coeff),     QPointF(7.5*coeff, 19.5*coeff),     QPointF(13.5*coeff, 13.5*coeff)}, 3);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 1.5*coeff),     QPointF(16.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(22.5*coeff, 1.5*coeff),     QPointF(22.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 4.5*coeff),     QPointF(22.5*coeff, 4.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_ExportPdf(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 1.5*coeff),     QPointF(7.5*coeff, 16.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 22.5*coeff),     QPointF(13.5*coeff, 22.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[3]{QPointF(1.5*coeff, 13.5*coeff),     QPointF(7.5*coeff, 19.5*coeff),     QPointF(13.5*coeff, 13.5*coeff)}, 3);

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 1.5*coeff),     QPointF(16.5*coeff, 10.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 1.5*coeff),     QPointF(19.5*coeff, 1.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(16.5*coeff, 7.5*coeff),     QPointF(19.5*coeff, 7.5*coeff)}, 2);
  painter.drawArc(QRectF(16.5*coeff, 1.5*coeff, 6.0*coeff, 6.0*coeff), 270 * 16, 180 * 16); // Дъга започваща от 270 градуса и продължаваща 180 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  return QIcon(pixmap);
}

QIcon Icons::icon_PrintPreview(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = ((qreal)width)/16; // По-малък размер (ако основния е 3 точки, този е 1.5 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 13.5*coeff, 21.0*coeff, 9.0*coeff));
  painter.drawRect(QRectF(4.5*coeff, 1.5*coeff, 15.0*coeff, 12.0*coeff));

  pen.setBrush(additionalColor);
  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(18.0*coeff, 18.0*coeff), 0.75*coeff, 0.75*coeff); // Точката.
  painter.drawEllipse(QPointF(11.5*coeff, 6.5*coeff), 2.25*coeff, 2.25*coeff); // Лупата.
  painter.drawPolyline(new QPointF[2]{QPointF(12.75*coeff, 8.25*coeff),    QPointF(15.25*coeff, 10.75*coeff)}, 2); // Дръжката на лупата.

  return QIcon(pixmap);
}

QIcon Icons::icon_Print(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  qreal penWidthS = ((qreal)width)/16; // По-малък размер (ако основния е 3 точки, този е 1.5 при големина на иконата 24x24).
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawRect(QRectF(1.5*coeff, 13.5*coeff, 21.0*coeff, 9.0*coeff));
  painter.drawRect(QRectF(4.5*coeff, 1.5*coeff, 15.0*coeff, 12.0*coeff));

  pen.setBrush(additionalColor);
  pen.setWidth(penWidthS);
  painter.setPen(pen);  
  painter.drawEllipse(QPointF(18.0*coeff, 18.0*coeff), 0.75*coeff, 0.75*coeff); // Точката.

  return QIcon(pixmap);
}

QIcon Icons::icon_Session(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 7.5*coeff),     QPointF(22.5*coeff, 7.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[3]{QPointF(18.5*coeff, 3.5*coeff),    QPointF(22.5*coeff, 7.5*coeff),    QPointF(18.5*coeff, 11.5*coeff)}, 3);
  
  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 16.5*coeff),    QPointF(16.5*coeff, 16.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[3]{QPointF(5.5*coeff, 12.5*coeff),    QPointF(1.5*coeff, 16.5*coeff),    QPointF(5.5*coeff, 20.5*coeff)}, 3);

  return QIcon(pixmap);
}

QIcon Icons::icon_Close(int width, int height, QColor generalColor, QColor additionalColor)
{
  Q_UNUSED(additionalColor)
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 1.5*coeff),     QPointF(22.5*coeff, 22.5*coeff)}, 2);
  painter.drawPolyline(new QPointF[2]{QPointF(1.5*coeff, 22.5*coeff),     QPointF(22.5*coeff, 1.5*coeff)}, 2);

  return QIcon(pixmap);
}

QIcon Icons::icon_Exit(int width, int height, QColor generalColor, QColor additionalColor)
{
  qreal coeff = ((qreal)width)/24; // Всички координати по-долу са за иконка с размер 24x24 точки. Ето защо трябва да се умножат с коефициент, в случай, че иконката трябва да бъде с други размери.
  qreal penWidth = ((qreal)width)/8;
  QPen pen(generalColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin); // Тук се правят някакви инициализации.
  QPixmap pixmap(width, height); // Това е картинката, която ще се получи и използва като икона.
  pixmap.fill(QColor(0, 0, 0, 0)); // Инициализира я с прозрачност (последната нула).
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(pen);  
  painter.drawArc(QRectF(1.5*coeff, 1.5*coeff, 21.0*coeff, 21.0*coeff), 150 * 16, 300 * 16); // Дъга започваща от 150 градуса и продължаваща 300 градуса. The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).

  pen.setBrush(additionalColor);
  painter.setPen(pen);  
  painter.drawPolyline(new QPointF[2]{QPointF(7.5*coeff, 1.5*coeff),    QPointF(7.5*coeff, 13.5*coeff)}, 2);

  return QIcon(pixmap);
}
