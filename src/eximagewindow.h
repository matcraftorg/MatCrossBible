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

#ifndef EXIMAGEWINDOW_H
#define EXIMAGEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QDir>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include <QSettings>

class QTextEdit;

class ExImageWindow : public QMainWindow
{
  Q_OBJECT

public:
  ExImageWindow(QString iniFile, QWidget *parent = 0);

private:
  QString      iniFile;
  QDir         dir;
  QString      imagesPath;
  QComboBox   *cbImages;
  QPushButton *btnImagesPath;
  QPushButton *btnZoomIn;
  QPushButton *btnZoomOut;
  QPushButton *btnNormalSize;
  QLabel      *imageLabel;
  QSize        imageNormalSize;
  double       scaleFactor;
  QGraphicsScene *scene;
  QGraphicsView  *view;

private slots:  
  void slotViewImage(const QString image);
  void slotImagesPath();
  void slotZoomIn();
  void slotZoomOut();
  void slotNormalSize();
};

#endif
