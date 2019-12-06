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

#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setApplicationName("MatCrossBible");
  QCoreApplication::setApplicationVersion("3.0.0");

  //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); // Програмата работи изцяло с UTF-8 кодировка.

  Q_INIT_RESOURCE(resources);
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/resources/images/logo128x128.png"));
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins"); //app.addLibraryPath("./Plugins");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/audio"); //app.addLibraryPath("./Plugins/audio");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/bearer"); //app.addLibraryPath("./Plugins/bearer");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/iconengines"); //app.addLibraryPath("./Plugins/iconengines");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/imageformats"); //app.addLibraryPath("./Plugins/imageformats");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/mediaservice"); //app.addLibraryPath("./Plugins/mediaservice");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/platforms"); //app.addLibraryPath("./Plugins/platforms"); // ???
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/playlistformats"); //app.addLibraryPath("./Plugins/playlistformats");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/printsupport"); //app.addLibraryPath("./Plugins/printsupport");
  app.addLibraryPath(QCoreApplication::applicationDirPath() + "/Plugins/styles"); //app.addLibraryPath("./Plugins/styles");

  MainWindow *MW = new MainWindow();
  MW->show();
  //MW->MO->CloseSplashScreen(); // Затваря началния прозорец (логото).
  return app.exec();
}
