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

#include "eximagewindow.h"

ExImageWindow::ExImageWindow(QString iniFile, QWidget *parent) : QMainWindow(parent)
{
  setMinimumSize(10, 10);
  resize(640, 512);

  imageNormalSize = QSize(10, 10);
  scaleFactor = 1.0;

  this->iniFile = iniFile;
  QSettings settings(iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  imagesPath = settings.value(QString("ImagesPath"), QString("%1/Images").arg(QCoreApplication::applicationDirPath())).toString();

  QStringList extFilters;
  extFilters << "*.bmp" << "*.gif" << "*.jpg" << "*.jpeg" << "*.png" << "*.pbm" << "*.pgm" << "*.ppm" << "*.xbm" << "*.xpm" << "*.tiff" << "*.mng" << "*.svg" << "*.tga"; 
  dir.setSorting(QDir::Name);
  dir.setNameFilters(extFilters);
  dir.setPath(imagesPath);
  cbImages = new QComboBox;
  cbImages->setMinimumWidth(35);
  cbImages->setEditable(false);
  cbImages->addItems(dir.entryList());
  //cbImages->addItem(QString("Родословие-линия (Genealogy-Line, Ver 1.0, Bulgarian, embedded image)")); // Тези двете трябва да са задължително последните два елемента!  //"Родословие" "Pedigree" "Genealogy" "Generations"
  //cbImages->addItem(QString("Родословие-дърво (Genealogy-Tree, Ver 1.0, Bulgarian, embedded image)"));
  cbImages->setCurrentIndex(0);
  cbImages->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); //Expanding
  connect(cbImages, SIGNAL(activated(const QString)), this, SLOT(slotViewImage(const QString)));

  btnImagesPath = new QPushButton(QString("..."));
  btnImagesPath->setMinimumWidth(30);
  btnImagesPath->setMaximumWidth(30);
  btnImagesPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  connect(btnImagesPath, SIGNAL(clicked()), this, SLOT(slotImagesPath()));

  btnZoomIn = new QPushButton(QString("+"));
  btnZoomIn->setMinimumWidth(30);
  btnZoomIn->setMaximumWidth(30);
  btnZoomIn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  btnZoomIn->setEnabled(false);
  connect(btnZoomIn, SIGNAL(clicked()), this, SLOT(slotZoomIn()));

  btnZoomOut = new QPushButton(QString("-"));
  btnZoomOut->setMinimumWidth(30);
  btnZoomOut->setMaximumWidth(30);
  btnZoomOut->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  btnZoomOut->setEnabled(false);
  connect(btnZoomOut, SIGNAL(clicked()), this, SLOT(slotZoomOut()));

  btnNormalSize = new QPushButton(QString("1:1"));
  btnNormalSize->setMinimumWidth(30);
  btnNormalSize->setMaximumWidth(30);
  btnNormalSize->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  btnNormalSize->setEnabled(false);
  connect(btnNormalSize, SIGNAL(clicked()), this, SLOT(slotNormalSize()));

  QPushButton *closeBtn = new QPushButton(QString("X"));
  closeBtn->setToolTip(QString("Close"));
  closeBtn->setMinimumWidth(30);
  closeBtn->setMaximumWidth(30);
  closeBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

  imageLabel = new QLabel();
  imageLabel->setScaledContents(true);
  imageLabel->setAlignment(Qt::AlignCenter);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  QPalette palette;
  QBrush brush(QColor(255, 255, 255, 255));
  brush.setStyle(Qt::SolidPattern);
  palette.setBrush(QPalette::Button, brush);
  palette.setBrush(QPalette::Window, brush);
  imageLabel->setPalette(palette);
  imageLabel->setAutoFillBackground(true);

  scene = new QGraphicsScene();
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->addWidget(imageLabel);

  view = new QGraphicsView(scene);
  view->setMinimumSize(30, 10);
  view->setRenderHint(QPainter::Antialiasing);
  view->setCacheMode(QGraphicsView::CacheBackground);
  view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view->setDragMode(QGraphicsView::ScrollHandDrag);

  QWidget *centralwidget = new QWidget(this);
  centralwidget->setContentsMargins(0, 0, 0, 0);

  QGridLayout *gridLayout = new QGridLayout(centralwidget);
  gridLayout->setContentsMargins(1, 1, 1, 1);
  gridLayout->addWidget(btnImagesPath, 0, 0);
  gridLayout->addWidget(cbImages, 0, 1);
  gridLayout->addWidget(btnZoomIn, 0, 2);
  gridLayout->addWidget(btnZoomOut, 0, 3);
  gridLayout->addWidget(btnNormalSize, 0, 4);
  gridLayout->addWidget(closeBtn, 0, 5);
  gridLayout->addWidget(view, 1, 0, 1, 6);

  setCentralWidget(centralwidget);
  closeBtn->setFocus();

  if (cbImages->count() > 0) slotViewImage(cbImages->currentText());
}

void ExImageWindow::slotImagesPath()
{
  QString d = QFileDialog::getExistingDirectory(this, QString("Open Directory"), imagesPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (d == "" || d == imagesPath) return;
  imagesPath = d;
  dir.setPath(imagesPath);
  cbImages->clear();
  imageLabel->setPixmap(QPixmap());
  cbImages->addItems(dir.entryList());
  //cbImages->addItem(QString("Родословие-линия (Genealogy-Line, Ver 1.0, Bulgarian, embedded image)")); // Тези двете трябва да са задължително последните два елемента!  //"Родословие" "Pedigree" "Genealogy" "Generations"
  //cbImages->addItem(QString("Родословие-дърво (Genealogy-Tree, Ver 1.0, Bulgarian, embedded image)"));

  btnZoomIn->setEnabled(false);
  btnZoomOut->setEnabled(false);
  btnNormalSize->setEnabled(false);
  if (cbImages->count() > 0) slotViewImage(cbImages->currentText());

  QSettings settings(iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  settings.setValue(QString("ImagesPath"), imagesPath);
}

void ExImageWindow::slotViewImage(const QString image)
{
  //if (cbImages->currentIndex() == (cbImages->count() - 2)) // Ако е родословието-линия (то е винаги добавено като предпоследен елемент в комбобокса).
  //  imageLabel->setPixmap(QPixmap(QString(":/resources/genealogy/Genealogy-Line, Ver 1.0, Bulgarian.png")));
  //else if (cbImages->currentIndex() == (cbImages->count() - 1)) // Ако е родословието-дърво (то е винаги добавено като последен елемент в комбобокса).
  //  imageLabel->setPixmap(QPixmap(QString(":/resources/genealogy/Genealogy-Tree, Ver 1.0, Bulgarian.png")));
  //else // Ако е изображение от външен файл.
    imageLabel->setPixmap(QPixmap(QString("%1/%2").arg(imagesPath).arg(image)));

  if (imageLabel->pixmap()->isNull())
  {
    btnZoomIn->setEnabled(false);
    btnZoomOut->setEnabled(false);
    btnNormalSize->setEnabled(false);
    imageLabel->setText(QString("Error: %1").arg(image));
    imageLabel->adjustSize();
    scene->setSceneRect(imageLabel->rect());
  }
  else
  {
    btnZoomIn->setEnabled(true);
    btnZoomOut->setEnabled(true);
    btnNormalSize->setEnabled(true);
    imageNormalSize = imageLabel->pixmap()->size();
    slotNormalSize();
  }
}

void ExImageWindow::slotZoomIn()
{
  if (imageLabel->pixmap()->isNull()) return;

  scaleFactor *= 1.25; // +20%
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
  scene->setSceneRect(imageLabel->rect());
}

void ExImageWindow::slotZoomOut()
{
  if (imageLabel->pixmap()->isNull()) return;

  scaleFactor *= 0.8; // -20%
  imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
  scene->setSceneRect(imageLabel->rect());
}

void ExImageWindow::slotNormalSize()
{
  if (imageLabel->pixmap()->isNull()) return;

  scaleFactor = 1.0;
  imageLabel->resize(imageNormalSize);
  scene->setSceneRect(imageLabel->rect());
}
