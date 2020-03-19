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

#include "httpaccess.h"

HttpDownloadManager::HttpDownloadManager(QNetworkProxy proxy, QProgressBar *progressBar, ProgressDialog *progressDialog)
{
  reply = 0;
  fileName = "";
  fileContent = "";
  inProcess = false;
  this->progressBar = progressBar;
  this->progressDialog = progressDialog;

  manager.setProxy(proxy);
  //manager.setProxy(QNetworkProxy::applicationProxy());
  //manager.setProxy(QNetworkProxy::DefaultProxy);

  connect(&manager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(slotAuthenticationRequired(QNetworkReply*, QAuthenticator*)));
  connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(slotDownloadFinished(QNetworkReply*)));
}

HttpDownloadManager::~HttpDownloadManager()
{
  if (reply != 0)
  {
    disconnect(reply, 0, 0, 0);
    reply->abort(); // Това е излишно.
  }
  disconnect(&manager, 0, 0, 0);
}

bool HttpDownloadManager::download(const QString url, const QString destDir, bool overwrite)
{
  // Ако url е празен, връща false.
  // Ако destDir не е празен, но не съществува, връща false.
  // Ако destDir е празна, сваля файла, но не го записва на диска.
  // Ако destDir съдържа валидна директория, извлича името на файла от url-а или генерира служебно име.
  if (url.isEmpty()) return false;
  if (!destDir.isEmpty() && !QDir(destDir).exists()) return false; // Ако съдържа директория, но тя не съществува на диска.
  if (destDir.isEmpty()) return downloadToFile(url, "", "", overwrite);

  QString destFileName = QFileInfo(url).fileName(); // Съдържа само името на файла.
  if (destFileName.isEmpty()) // Ако НЕ е установено името на файла.
  {
    destFileName = "_download"; // Задава служебно име на файл.
    overwrite = false; // Забранява презаписването на файла, защото това име е служебно и е възможно да съществува такъв файл.
  }

  if (!overwrite)
  {
    QFileInfo fileInfo(destDir, destFileName); // Свързва името на файла с директорията в която трябва да се запише.

    if (QFile::exists(fileInfo.filePath())) // Ако файлът съществува.
    {
      int i = 0;
      while (QFile::exists(fileInfo.filePath() + QString(".%1").arg(i)))
        i++;
      destFileName += QString(".%1").arg(i);
    }
  }

  return downloadToFile(url, destDir, destFileName, overwrite);
}

bool HttpDownloadManager::downloadToFile(const QString url, const QString destDir, const QString destFileName, const bool overwrite)
{
  // Ако url е празен, връща false.
  // Ако destDir не е празен, а destFileName е празен, връща false, защото това не е нормално за този метод (трябва да се използва другия в този случай).
  // Ако destDir не е празен, но не съществува, връща false.
  // Ако destDir е празен, а destFileName не е празен, проверява дали destFileName не съдържа и пътя и името. Ако не - връща false.
  // Ако destDir и destFileName са празни, сваля файла, но не го записва на диска.
  if (url.isEmpty()) return false;
  if (!destDir.isEmpty() && destFileName.isEmpty()) return false;
  if (!destDir.isEmpty() && !QDir(destDir).exists()) return false; // Ако съдържа директория, но тя не съществува на диска.

  if (inProcess) return false;
  inProcess = true;

  if (destDir.isEmpty() && !destFileName.isEmpty())
  {
    QFileInfo fileInfo(destFileName);
    if (QDir(fileInfo.absolutePath()).exists() && !fileInfo.fileName().isEmpty()) // Ако пътят (без името на файла) съществува и отделно има зададено име на файл.
    {
      this->fileName = destFileName;
    }
    else
    {
      return false;
    }
  }
  else if (!destDir.isEmpty() && !destFileName.isEmpty())
  {
    this->fileName = QFileInfo(destDir, destFileName).filePath(); // Съдържа името на файла + директорията.
  }
  else //if (destDir.isEmpty())
  {
    this->fileName = "";
  }
  this->fileContent = "";

  if (!overwrite && QFile(fileName).exists()) // Ако файлът не трябва да се овъррайдва и съществува на диска.
  {
    //emit downloadFinished(url, fileName, true, "The file exists!");
    //return true;
    return false;
  }

  QNetworkRequest request(url);
  reply = manager.get(request); // Започва свалянето.
  if (progressBar != 0)
  {
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    progressBar->setValue(0);
  }
  if (progressDialog != 0)
  {
    progressDialog->setMinimum(0);
    progressDialog->setMaximum(0);
    progressDialog->setValue(0);
  }
  connect(reply, SIGNAL(downloadProgress(qint64, qint64)), SLOT(slotDownloadProgress(qint64, qint64)));
  return true;
}

void HttpDownloadManager::abort()
{
  if (reply != 0 && reply->isRunning())
  {
    reply->abort();
    //reply->close();
    disconnect(reply, SIGNAL(downloadProgress(qint64, qint64)), 0, 0);
  }
}

void HttpDownloadManager::slotAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
  QDialog dlg;
  Ui::Dialog ui;
  ui.setupUi(&dlg);
  dlg.adjustSize();
  ui.siteDescription->setText(QString("%1 at %2").arg(authenticator->realm()).arg(reply->url().host()));

  if (dlg.exec() == QDialog::Accepted)
  {
    authenticator->setUser(ui.userEdit->text());
    authenticator->setPassword(ui.passwordEdit->text());
  }
}

void HttpDownloadManager::slotDownloadFinished(QNetworkReply *reply)
{
  QUrl url = reply->url();

  disconnect(reply, SIGNAL(downloadProgress(qint64, qint64)), 0, 0);

  inProcess = false;
  if (reply->error()) // Ако има грешка при свалянето.
  {
    emit downloadFinished(url.toEncoded().constData(), fileName, true, qPrintable(reply->errorString()));
  }
  else // Ако няма грешка при свалянето.
  {
    if (fileName.isEmpty()) // Ако не трябва да се записва на диска.
    {
      fileContent = reply->readAll();
      emit downloadFinished(url.toEncoded().constData(), fileName, false, "");
    }
    else // Ако трябва да се запише на диска.
    {
      // Записва файла на диска.
      QFile file(fileName);
      if (file.exists()) // Ако файлът съществува на диска. Тази проверка е излишна, защото се прави в началото.
      {
        emit downloadFinished(url.toEncoded().constData(), fileName, true, "The file exists!");
      }
      else if (file.open(QIODevice::WriteOnly)) // Ако няма грешка при записването.
      {
        file.write(reply->readAll());
        file.close();
        emit downloadFinished(url.toEncoded().constData(), fileName, false, "");
      }
      else // Ако има грешка при записването.
      {
        emit downloadFinished(url.toEncoded().constData(), fileName, true, qPrintable(file.errorString()));
      }
    }
  }

  //reply->deleteLater(); // Това не трябва да се прави - води до крашване при затваряне на формата.
  reply = 0;
}

void HttpDownloadManager::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  if (progressBar != 0 && bytesReceived >= 0 && bytesTotal > 0)
  {
    if (progressBar->maximum() != bytesTotal) progressBar->setMaximum(bytesTotal);
    progressBar->setValue(bytesReceived);
  }

  if (progressDialog != 0 && bytesReceived >= 0 && bytesTotal > 0)
  {
    if (progressDialog->maximum() != bytesTotal) progressDialog->setMaximum(bytesTotal);
    progressDialog->setValue(bytesReceived);
  }

  emit downloadProgress(bytesReceived, bytesTotal);
}

// =========================================================================================================================================================

NewAppVerWindow::NewAppVerWindow(MainWindow *MW, QWidget *parent) : QTextBrowser(parent)
{
  this->MW = MW;
  resize(500, 170);
  setMinimumSize(30, 30);
  if (parent != 0) move(parent->pos().x()+30, parent->pos().y()+30);

  setWindowTitle(MW->MO->TS->CheckNewAppVersion_v1 + " - " + QCoreApplication::applicationName());
  setFrameShape(QFrame::NoFrame);
  setOpenExternalLinks(true); // За отваряне на линковете.
  setOpenLinks(true);         // За отваряне на линковете.
  setReadOnly(true);
  setMaximumHeight(200);
  setHtml(QString("<span style=\"color: #00aaaa;\"><b>%1</b></span>").arg(MW->MO->TS->Connecting_v1));
  QPalette pal = palette();
  pal.setBrush(QPalette::Base, QColor(255, 255, 255)); // Може да е бледо жълт цвят на фона (255, 255, 225), но не стои добре като цвят на целия прозорец и затова е бял.
  setPalette(pal);

  QNetworkProxy proxy;
  if (MW->MO->SVars.proxyType == PROXY__NO_PROXY)
    proxy.setType(QNetworkProxy::NoProxy);
  else if (MW->MO->SVars.proxyType == PROXY__HTTP_PROXY)
    proxy.setType(QNetworkProxy::HttpProxy);
  else if (MW->MO->SVars.proxyType == PROXY__SOCKS_5_PROXY)
    proxy.setType(QNetworkProxy::Socks5Proxy);
  proxy.setHostName(MW->MO->SVars.proxyHostName);
  proxy.setPort(MW->MO->SVars.proxyPort);

  DM = new HttpDownloadManager(proxy, 0, 0);
  connect(DM, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished(QString, QString, bool, QString)));
  DM->download(MW->MO->SVars.MatCrossBibleURL + QString("CurrentAppVer.txt"), ""); // Файлът няма да се записва на диска, затова не се указва директория за запис.
}

void NewAppVerWindow::closeEvent(QCloseEvent *event)
{
  delete DM; // Това крашва.

  event->accept();
}

void NewAppVerWindow::slotDownloadFinished(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  if (error)
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->InaccessibleInfo_v1) +
            QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->ConnectingError_v1) +
            QString("<div><font color=#a0a0a0>%1: \"%2\"</font></div><div>&nbsp;</div>").arg(MW->MO->TS->Error_v1).arg(errorString) +
            QString("<div><b>%1: <font color=#00aaaa>%2</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->CurrentVersion_v1).arg(QCoreApplication::applicationVersion()) +
            QString("<div>%1</div><div><a href=\"%2\"><font color=#0080ff>%2</font></a></div>").arg(MW->MO->TS->CheckNewAppVersionOnWEB_v1).arg(MW->MO->SVars.MatCrossBibleURL));
  }
  else
  {
    if (DM->fileContent.isEmpty())
    {
      setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->InaccessibleInfoFileError_v1) +
              QString("<div><b>%1: <font color=#00aaaa>%2</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->CurrentVersion_v1).arg(QCoreApplication::applicationVersion()) +
              QString("<div>%1</div><div><a href=\"%2\"><font color=#0080ff>%2</font></a></div>").arg(MW->MO->TS->CheckNewAppVersionOnWEB_v1).arg(MW->MO->SVars.MatCrossBibleURL));
    }
    else
    {
      showInfo( DM->fileContent.split(QRegExp("\n")) );
    }
  }
}

void NewAppVerWindow::showInfo(QStringList rows)
{
  // Ако всичко е наред трябва да се получи 1 ред съдържащ версията на програмата във формат X.X.X (например 3.0.1).

  if (rows.count() > 0)
  {
    QString text = "";
    text += QString("<div><b>%1: <font color=#00aaaa>%2</font></b></div>").arg(MW->MO->TS->CurrentVersion_v1).arg(QCoreApplication::applicationVersion());
    text += QString("<div>%1: <font color=#00aaaa>%2</font></div><div>&nbsp;</div>").arg(MW->MO->TS->LastReleaseVersion_v1).arg(rows.at(0).trimmed());

    if ( MW->MO->appVersionToInt(rows.at(0).trimmed()) > MW->MO->appVersionToInt(QCoreApplication::applicationVersion()) ) // Ако има по-нова официална версия.
    {
      text += QString("<div><b><font color=#ff8000>%1</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->HasNewReleaseVersion_v1);
      text += QString("<div>%1<div></div><a href=\"%2\"><font color=#0080ff>%2</font></a></div>").arg(MW->MO->TS->DownloadNewAppVerFromWEB_v1).arg(MW->MO->SVars.MatCrossBibleURL);
    }
    else // Ако няма по-нова официална версия.
    {
      text += QString("<div><b><font color=#00aaaa>%1</font></b></div>").arg(MW->MO->TS->NoNewReleaseVersion_v1);
    }

    setHtml(text);
  }
  else
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->InaccessibleInfoFileError_v1) +
            QString("<div><b>%1: <font color=#00aaaa>%2</font></b></div><div>&nbsp;</div>").arg(MW->MO->TS->CurrentVersion_v1).arg(QCoreApplication::applicationVersion()) +
            QString("<div>%1</div><div><a href=\"%2\"><font color=#0080ff>%2</font></a></div>").arg(MW->MO->TS->CheckNewAppVersionOnWEB_v1).arg(MW->MO->SVars.MatCrossBibleURL));
  }
}

// =========================================================================================================================================================

MoreBibleTextsWindow::MoreBibleTextsWindow(MainWindow *MW, QWidget *parent) : QTextBrowser(parent)
{
  this->MW = MW;
  resize(900, 500);
  setMinimumSize(30, 30);
  if (parent != 0) move(parent->pos().x()+30, parent->pos().y()+30);

  setWindowTitle(MW->MO->TS->MoreBibleTexts_v1 + " - " + QCoreApplication::applicationName());
  setFrameShape(QFrame::NoFrame);
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setOpenExternalLinks(true); // За отваряне на линковете.
  setOpenLinks(true);         // За отваряне на линковете.
  setReadOnly(true);
  setHtml(QString("<span style=\"color: #00aaaa;\"><b>%1</b></span>").arg(MW->MO->TS->Connecting_v1));
  connect(this, SIGNAL(anchorClicked (const QUrl &)), this, SLOT(slotAnchorClicked(const QUrl &)));

  progressDialog = new ProgressDialog(this);
  progressDialog->setWindowTitle(windowTitle());
  progressDialog->setMinimumWidth(320);
  progressDialog->hide();
  connect(progressDialog, SIGNAL(canceled()), this, SLOT(slotCancelDownload()));

  QNetworkProxy proxy;
  if (MW->MO->SVars.proxyType == PROXY__NO_PROXY)
    proxy.setType(QNetworkProxy::NoProxy);
  else if (MW->MO->SVars.proxyType == PROXY__HTTP_PROXY)
    proxy.setType(QNetworkProxy::HttpProxy);
  else if (MW->MO->SVars.proxyType == PROXY__SOCKS_5_PROXY)
    proxy.setType(QNetworkProxy::Socks5Proxy);
  proxy.setHostName(MW->MO->SVars.proxyHostName);
  proxy.setPort(MW->MO->SVars.proxyPort);

  DM_T = new HttpDownloadManager(proxy, 0, 0);
  connect(DM_T, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished_T(QString, QString, bool, QString)));
  DM_T->download(MW->MO->SVars.MatCrossBibleURL + QString("BibleTexts/v%1/AllBibleTexts.txt").arg(STRUCTURE_VERSION), ""); // Файлът няма да се записва на диска, затова не се указва директория за запис.

  DM_F = new HttpDownloadManager(proxy, 0, progressDialog);
  connect(DM_F, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished_F(QString, QString, bool, QString)));
}

void MoreBibleTextsWindow::closeEvent(QCloseEvent *event)
{
  //delete progressDialog;
  progressDialog->deleteLater(); // Това е ОК.
  progressDialog = 0;
  delete DM_T;
  delete DM_F;

  event->accept();
}

void MoreBibleTextsWindow::slotDownloadFinished_T(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  if (error)
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->InaccessibleInfo_v1) +
            QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->ConnectingError_v1) +
            QString("<div><font color=#a0a0a0>%1: \"%2\"</font></div><div>&nbsp;</div>").arg(MW->MO->TS->Error_v1).arg(errorString) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->AlternativeDownload_v1) +
            getMoreBibleTextsInfo());
  }
  else
  {
    showTable( DM_T->fileContent.split(QRegExp("\n")) );
  }
}

void MoreBibleTextsWindow::slotDownloadFinished_F(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  progressDialog->hide();
  if (error)
  {
    QMessageBox::information(this, windowTitle(), QString("%1\nError: %3").arg(MW->MO->TS->DownloadFailure_v1).arg(errorString)); // Това става, ако например сайтът е невалиден или недостъпен или няма такъв файл.
  }
  else
  {
    QMessageBox::information(this, windowTitle(),  MW->MO->TS->DownloadDoneNeedToResraer_v1);
    MW->slotRestart(true);

    // Презарежда таблицата:
    DM_T->download(MW->MO->SVars.MatCrossBibleURL + QString("BibleTexts/v%1/AllBibleTexts.txt").arg(STRUCTURE_VERSION), ""); // Файлът няма да се записва на диска, затова не се указва директория за запис.
  }
}

void MoreBibleTextsWindow::slotCancelDownload()
{
  DM_F->abort();
}

void MoreBibleTextsWindow::showTable(QStringList rows)
{
  // Ако всичко е наред трябва да се получи файл, съдържащ по 7 реда за всеки текст:
  //
  // Bulgarian
  // ВЕРЕН (2001)
  // Ревизирано издание от 2001 г. на Издателство "Верен"
  // Bulgarian_VEREN2001.hbt
  // https://www.matcraft.org/MatCrossBible/BibleTexts/v3/Bulgarian_VEREN2001.hbt
  // enable/disable
  // ============================================================
  //
  // Информацията за следващия текст започва непосредствено след този (няма празни редове, а също и не завършва с празен ред).
  //
  if (rows.count() > 0 && (rows.count() % 7) == 0) // Ако файлът не е празен и ако не е непълен.
  {
    // Започва изграждането на таблицата и попълването на масивите с номерата и линковете към файловете.
    QString text = QString("<style type=\"text/css\"> a:link {color: #0080ff;} td {background-color: #fefceb; color: #202020;} </style>"
                           "<div><font color=#202020><b>%1</b></font></div>"
                           "<div><font color=#202020>%2</font></div>"
                           "<div><font color=#202020>%3</font></div><div>&nbsp;</div>"
                           "<table style=\"background-color: #00aaaa;\" border=\"0\" cellpadding=\"3\" cellspacing=\"1\"><tbody>").arg(MW->MO->TS->DownloadTextInfo1_v1).arg(MW->MO->TS->DownloadTextInfo2_v1).arg(MW->MO->TS->DownloadTextInfo3_v1);
    text += QString("<tr>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%1</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%2</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%3</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%4</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%5</b></div></td>"
                    "</tr>").arg(MW->MO->TS->Language_v1).arg(MW->MO->TS->Text_v1).arg(MW->MO->TS->ShortDescription_v1).arg(MW->MO->TS->File_v1).arg(MW->MO->TS->Note_v1);
    for (int i = 0; i < rows.count(); i += 7)
    {
      bool expect = (rows.at(i+5) == "disable");

      if (QFile::exists( QString("%1/BibleTexts/%2").arg(MW->MO->applicationDirPath).arg(rows.at(i+3)) )) // Ако файлът съществува в директорията.
      {
        text += QString("<tr>"
                        "<td style=\"color: #00aaaa;\"><div>%1</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%2</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%3</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%4</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%5</div></td>"
                        "</tr>").arg(rows.at(i)).arg(rows.at(i+1)).arg(rows.at(i+2)).arg(rows.at(i+3)).arg(MW->MO->TS->Available_v1);
      }
      else if (expect) // Ако не е разрешен за ползване.
      {
        text += QString("<tr>"
                        "<td style=\"color: #ff6050;\"><div>%1</div></td>"
                        "<td style=\"color: #ff6050;\"><div>%2</div></td>"
                        "<td style=\"color: #ff6050;\"><div>%3</div></td>"
                        "<td style=\"color: #ff6050;\"><div>%4</div></td>"
                        "<td style=\"color: #ff6050;\"><div>%5</div></td>"
                        "</tr>").arg(rows.at(i)).arg(rows.at(i+1)).arg(rows.at(i+2)).arg(rows.at(i+3)).arg(MW->MO->TS->ExpectRightToUse_v1);
      }
      else
      {
        text += QString("<tr>"
                        "<td><div>%1</div></td>"
                        "<td><div><a href=\"%2\">%3</a></div></td>"
                        "<td><div>%4</div></td>"
                        "<td><div>%5</div></td>"
                        "<td></td>"
                        "</tr>").arg(rows.at(i)).arg(rows.at(i+4)).arg(rows.at(i+1)).arg(rows.at(i+2)).arg(rows.at(i+3));
      }
    }
    text += QString("</tbody></table>");
    setHtml(text);
    setOpenExternalLinks(false); // За да не отваря линковете във външния браузър.
    setOpenLinks(false);         // За да не отваря линковете във външния браузър.
  }
  else
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->InaccessibleInfoFileError_v1) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->FileDataError_v1) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->AlternativeDownload_v1) +
            getMoreBibleTextsInfo());
  }
}

void MoreBibleTextsWindow::slotAnchorClicked(const QUrl &link)
{
  // Примерен път до файл и разделянето му на трите съставки; host, path и fileName:
  //
  // https://www.matcraft.org/MatCrossBible/BibleTexts/v3/Bulgarian_Prot1940.hbt
  // |            host        |           path            |      fileName      |
  //
  // Ако сайтът (host), името на файла (fileName) или пътят до него (path) са грешни ще го хване в момента на свалянето и ще даде съобщение за грешка.

  QFileInfo fileInfo(QUrl(link.toString()).path());
  if (fileInfo.fileName().isEmpty()) // Ако няма име. Тази проверка е излишна.
  {
    QMessageBox::information(this, windowTitle(), QString("%1\n'%2'").arg(MW->MO->TS->DownloadFailureInvalidLink_v1).arg(link.toString()));
    return;
  }

  progressDialog->setLabelText(fileInfo.fileName());
  progressDialog->show();
  DM_F->download(link.toString(), QString("%1/BibleTexts/").arg(MW->MO->applicationDirPath), false);
}

QString MoreBibleTextsWindow::getMoreBibleTextsInfo()
{
  QString text;

  if (MW->MO->bibleTextList.count() > 0) // Ако има налични текстове.
  {
    text += QString("<div><font color=#00aaaa><b>%1</b></font></div><div>&nbsp;</div>").arg(MW->MO->TS->GetMoreBibleTextsInfo1_v1);
    foreach (BIBLE_TEXT bl, MW->MO->bibleTextList)
    {
      text += QString("<div><font color=#00aaaa>● <b>%1</b> -- %2</font></div>").arg(bl.name).arg(bl.short_description);
    }
    text += QString("<div>&nbsp;</div><div>%1</div>").arg(MW->MO->TS->GetMoreBibleTextsInfo3_v1);
  }
  else // Ако няма налични текстове (например след изтегляне и компилиране на сорс-кода, в пакета няма никакви текстове).
  {
    text += QString(
      "<div><font color=#00aaaa><b>%1</b></font></div><div>&nbsp;</div>"
      "<div>%2</div><div><br /></div>").arg(MW->MO->TS->GetMoreBibleTextsInfo2_v1).arg(MW->MO->TS->GetMoreBibleTextsInfo4_v1);
  }

  text += QString(
    "<div>%1</div><div><a href=\"%2BibleTexts/\"><font color=#0080ff>%2BibleTexts/</font></a></div>"
    "<div>&nbsp;</div>"
    "<div>%3</div>"
    "<div>%4</div>"
    "<div><b><code>%5</code></b></div>"
    "<div>%6</div>")
    .arg(MW->MO->TS->GetMoreBibleTextsInfo5_v1)
    .arg(MW->MO->SVars.MatCrossBibleURL)
    .arg(MW->MO->TS->GetMoreBibleTextsInfo6_v1)
    .arg(MW->MO->TS->GetMoreBibleTextsInfo7_v1)
    .arg(QDir::toNativeSeparators(MW->MO->applicationDirPath + QString("/BibleTexts")))
    .arg(MW->MO->TS->GetMoreBibleTextsInfo8_v1);
  return text;
}

// =========================================================================================================================================================

MoreTRFilesWindow::MoreTRFilesWindow(MainWindow *MW, QWidget *parent) : QTextBrowser(parent)
{
  this->MW = MW;
  resize(600, 500);
  setMinimumSize(30, 30);
  if (parent != 0) move(parent->pos().x()+30, parent->pos().y()+30);

  setWindowTitle(MW->MO->TS->MoreTRFiles_v1 + " - " + QCoreApplication::applicationName());
  setFrameShape(QFrame::NoFrame);
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setOpenExternalLinks(true); // За отваряне на линковете.
  setOpenLinks(true);         // За отваряне на линковете.
  setReadOnly(true);
  setHtml(QString("<span style=\"color: #00aaaa;\"><b>%1</b></span>").arg(MW->MO->TS->Connecting_v1));
  connect(this, SIGNAL(anchorClicked (const QUrl &)), this, SLOT(slotAnchorClicked(const QUrl &)));

  progressDialog = new ProgressDialog(this);
  progressDialog->setWindowTitle(windowTitle());
  progressDialog->setMinimumWidth(320);
  progressDialog->hide();
  connect(progressDialog, SIGNAL(canceled()), this, SLOT(slotCancelDownload()));

  QNetworkProxy proxy;
  if (MW->MO->SVars.proxyType == PROXY__NO_PROXY)
    proxy.setType(QNetworkProxy::NoProxy);
  else if (MW->MO->SVars.proxyType == PROXY__HTTP_PROXY)
    proxy.setType(QNetworkProxy::HttpProxy);
  else if (MW->MO->SVars.proxyType == PROXY__SOCKS_5_PROXY)
    proxy.setType(QNetworkProxy::Socks5Proxy);
  proxy.setHostName(MW->MO->SVars.proxyHostName);
  proxy.setPort(MW->MO->SVars.proxyPort);

  DM_T = new HttpDownloadManager(proxy, 0, 0);
  connect(DM_T, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished_T(QString, QString, bool, QString)));
  DM_T->download(MW->MO->SVars.MatCrossBibleURL + QString("Tr/v%1/AllTrFiles.txt").arg(QCoreApplication::applicationVersion()), ""); // Файлът няма да се записва на диска, затова не се указва директория за запис.

  DM_F = new HttpDownloadManager(proxy, 0, progressDialog);
  connect(DM_F, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished_F(QString, QString, bool, QString)));
}

void MoreTRFilesWindow::closeEvent(QCloseEvent *event)
{
  //delete progressDialog;
  progressDialog->deleteLater(); // Това е ОК.
  progressDialog = 0;
  delete DM_T;
  delete DM_F;

  event->accept();
}

void MoreTRFilesWindow::slotDownloadFinished_T(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  if (error)
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->InaccessibleInfo_v1) +
            QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->ConnectingError_v1) +
            QString("<div><font color=#a0a0a0>%1: \"%2\"</font></div><div>&nbsp;</div>").arg(MW->MO->TS->Error_v1).arg(errorString) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->AlternativeDownload_v1) +
            getMoreTRFilesInfo());
  }
  else
  {
    showTable( DM_T->fileContent.split(QRegExp("\n")) );
  }
}

void MoreTRFilesWindow::slotDownloadFinished_F(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  progressDialog->hide();
  if (error)
  {
    QMessageBox::information(this, windowTitle(), QString("%1\nError: %3").arg(MW->MO->TS->DownloadFailure_v1).arg(errorString)); // Това става ако например сайтът е невалиден или недостъпен или няма такъв файл.
  }
  else
  {
    QMessageBox::information(this, windowTitle(), MW->MO->TS->DownloadDone_v1);

    // Презарежда таблицата:
    DM_T->download(MW->MO->SVars.MatCrossBibleURL + QString("Tr/v%1/AllTrFiles.txt").arg(QCoreApplication::applicationVersion()), ""); // Файлът няма да се записва на диска, затова не се указва директория за запис.

    // Рефрешва комбобокса:
    emit downloadTRFileFinished();
  }
}

void MoreTRFilesWindow::slotCancelDownload()
{
  DM_F->abort();
}

void MoreTRFilesWindow::showTable(QStringList rows)
{
  // Ако всичко е наред, трябва да се получи файл съдържащ по 7 реда за всеки TR файл:
  //
  // Hungarian
  // Generated by MatCrossBible
  // 2019.04.30
  // Hungarian.tr
  // https://www.matcraft.org/MatCrossBible/Tr/v3.0.0/Hungarian.tr
  // full/partial
  // ============================================================
  //
  // Информацията за следващия TR файл започва непосредствено след този (няма празни редове, а също и не завършва с празен ред).
  //
  if (rows.count() > 0 && (rows.count() % 7) == 0) // Ако файлът не е празен и ако не е непълен.
  {
    // Започва изграждането на таблицата и попълването на масивите с номерата и линковете към файловете.
    QString text = QString("<style type=\"text/css\"> a:link {color: #0080ff;} td {background-color: #fefceb; color: #202020;} </style>"
                           "<div><font color=#202020><b>%1</b></font></div>"
                           "<div><font color=#202020>%2</font></div><div>&nbsp;</div>"
                           "<table style=\"background-color: #00aaaa;\" border=\"0\" cellpadding=\"3\" cellspacing=\"1\"><tbody>").arg(MW->MO->TS->DownloadTRFilesInfo1_v1).arg(MW->MO->TS->DownloadTRFilesInfo2_v1);
    text += QString("<tr>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%1</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%2</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%3</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%4</b></div></td>"
                    "<td style=\"background-color: #00aaaa; color: #ffffff;\"><div><b>%5</b></div></td>"
                    "</tr>").arg(MW->MO->TS->Language_v1).arg(MW->MO->TS->Translator_v1).arg(MW->MO->TS->LastModify_v1).arg(MW->MO->TS->File_v1).arg(MW->MO->TS->Note_v1);
    for (int i = 0; i < rows.count(); i += 7)
    {
      QString partial = (rows.at(i+5) == "partial") ? MW->MO->TS->PartialTranslated_v1 : "";

      if (QFile::exists( QString("%1/Tr/%2").arg(MW->MO->applicationDirPath).arg(rows.at(i+3)) )) // Ако файлът съществува в директорията.
      {
        text += QString("<tr>"
                        "<td style=\"color: #00aaaa;\"><div>%1</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%2</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%3</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%4</div></td>"
                        "<td style=\"color: #00aaaa;\"><div>%5</div></td>"
                        "</tr>").arg(rows.at(i)).arg(rows.at(i+1)).arg(rows.at(i+2)).arg(rows.at(i+3)).arg(partial);
      }
      else
      {
        text += QString("<tr>"
                        "<td><div>%1</div></td>"
                        "<td><div>%2</div></td>"
                        "<td><div>%3</div></td>"
                        "<td><div><a href=\"%4\">%5</a></div></td>"
                        "<td><div>%6</div></td>"
                        "</tr>").arg(rows.at(i)).arg(rows.at(i+1)).arg(rows.at(i+2)).arg(rows.at(i+4)).arg(rows.at(i+3)).arg(partial);
      }
    }
    text += QString("</tbody></table>");
    setHtml(text);
    setOpenExternalLinks(false); // За да не отваря линковете във външния браузър.
    setOpenLinks(false);         // За да не отваря линковете във външния браузър.
  }
  else
  {
    setHtml(QString("<div><b><font color=#ff0000>%1</font></b></div>").arg(MW->MO->TS->InaccessibleInfoFileError_v1) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->FileDataError_v1) +
            QString("<div>%1</div><div>&nbsp;</div>").arg(MW->MO->TS->AlternativeDownload_v1) +
            getMoreTRFilesInfo());
  }
}

void MoreTRFilesWindow::slotAnchorClicked(const QUrl &link)
{
  // Примерен път до файл и разделянето му на трите съставки; host, path и fileName:
  //
  // https://www.matcraft.org/MatCrossBible/Tr/v3.0.0/Hungarian.tr
  // |            host       |         path          | fileName |
  //
  // Ако сайтът (host), името на файла (fileName) или пътят до него (path) са грешни ще го хване в момента на свалянето и ще даде съобщение за грешка.

  QFileInfo fileInfo(QUrl(link.toString()).path());
  if (fileInfo.fileName().isEmpty()) // Ако няма име. Тази проверка е излишна.
  {
    QMessageBox::information(this, windowTitle(), QString("%1\n'%2'").arg(MW->MO->TS->DownloadFailureInvalidLink_v1).arg(link.toString()));
    return;
  }

  progressDialog->setLabelText(fileInfo.fileName());
  progressDialog->show();
  DM_F->download(link.toString(), QString("%1/Tr/").arg(MW->MO->applicationDirPath), false);
}

QString MoreTRFilesWindow::getMoreTRFilesInfo()
{
  QString text;

  text += QString("<div><font color=#00aaaa><b>%1</b></font></div><div>&nbsp;</div>").arg(MW->MO->TS->GetMoreTRFilesInfo1_v1);
  foreach (QString trFile, MW->MO->TS->allAppTranslation)
  {
    text += QString("<div><font color=#00aaaa>● <b>%1</b> &nbsp;(%1.tr)</font></div>").arg(trFile);
  }
  text += QString("<div>&nbsp;</div><div>%1</div>").arg(MW->MO->TS->GetMoreTRFilesInfo2_v1);

  text += QString(
    "<div>%1</div><div><a href=\"%2Tr/\"><font color=#0080ff>%2Tr/</font></a></div>"
    "<div>&nbsp;</div>"
    "<div>%3</div>"
    "<div><b><code>%4</code></b></div>"
    "<div>%5</div>")
    .arg(MW->MO->TS->GetMoreTRFilesInfo3_v1)
    .arg(MW->MO->SVars.MatCrossBibleURL)
    .arg(MW->MO->TS->GetMoreTRFilesInfo4_v1)
    .arg(QDir::toNativeSeparators(MW->MO->applicationDirPath + QString("/Tr")))
    .arg(MW->MO->TS->GetMoreTRFilesInfo5_v1);
  return text;
}
