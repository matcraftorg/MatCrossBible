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

#ifndef HTTPACCESS_H
#define HTTPACCESS_H

#include <QtGui>
#include <QMainWindow>
#include <QtNetwork>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>
#include <QProgressBar>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "datatypes.h"
#include "mainobject.h"
#include "mainwindow.h"
#include "utility.h"
#include "ui_authenticationdialog.h"

class ProgressDialog;

class HttpDownloadManager: public QObject
{
Q_OBJECT

private:
  QNetworkAccessManager manager;
  QNetworkReply *reply;
  QString path;
  QString fileName;
  bool inProcess;
  QProgressBar *progressBar;
  ProgressDialog *progressDialog;

public:
  QString fileContent;

  HttpDownloadManager(QNetworkProxy proxy, QProgressBar *progressBar = 0, ProgressDialog *progressDialog = 0);
  ~HttpDownloadManager();
  bool download(const QString url, const QString destDir, bool overwrite = false); // Сваля файла от url-а, като го записва в директория destDir и във файл, чието име извлича от url-а.
  bool downloadToFile(const QString url, const QString destDir, const QString destFileName, bool overwrite = false); // Сваля файла от url-а, като го записва в директория destDir, във файл destFileName.
  void abort();

private slots:
  void slotAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
  void slotDownloadFinished(QNetworkReply *reply);
  void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

signals:
  void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
  void downloadFinished(QString url, QString filePath, bool error, QString errorString);
};

// =========================================================================================================================================================

class NewAppVerWindow : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  QTextBrowser *editorNew;
  QTextBrowser *editorComment;
  HttpDownloadManager *DM;

  void closeEvent(QCloseEvent *event);
  void showInfo(QStringList rows);

public:
  NewAppVerWindow(MainWindow *MW, QWidget *parent = 0);

private slots:
  void slotDownloadFinished(QString url, QString filePath, bool error, QString errorString);
};

// =========================================================================================================================================================

class MoreBibleTextsWindow : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  HttpDownloadManager *DM_T; // За изтегляне на таблицата.
  HttpDownloadManager *DM_F; // За изтегляне на файловете.
  ProgressDialog *progressDialog;

  void closeEvent(QCloseEvent *event);
  void showTable(QStringList rows);
  QString getMoreBibleTextsInfo();

public:
  MoreBibleTextsWindow(MainWindow *MW, QWidget *parent = 0);

private slots:
  void slotCancelDownload();
  void slotAnchorClicked(const QUrl &link);
  void slotDownloadFinished_T(QString url, QString filePath, bool error, QString errorString);
  void slotDownloadFinished_F(QString url, QString filePath, bool error, QString errorString);
};

// =========================================================================================================================================================

class MoreTRFilesWindow : public QTextBrowser
{
Q_OBJECT

private:
  MainWindow *MW;
  HttpDownloadManager *DM_T; // За изтегляне на таблицата.
  HttpDownloadManager *DM_F; // За изтегляне на файловете.
  QTextBrowser *browser;
  ProgressDialog *progressDialog;

  void closeEvent(QCloseEvent *event);
  void showTable(QStringList rows);
  QString getMoreTRFilesInfo();

public:
  MoreTRFilesWindow(MainWindow *MW, QWidget *parent = 0);

private slots:
  void slotCancelDownload();
  void slotAnchorClicked(const QUrl &link);
  void slotDownloadFinished_T(QString url, QString filePath, bool error, QString errorString);
  void slotDownloadFinished_F(QString url, QString filePath, bool error, QString errorString);

signals:
  void downloadTRFileFinished();
};

#endif
