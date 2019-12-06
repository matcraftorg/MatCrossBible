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

#ifndef AUDIOTOOLBAR_H
#define AUDIOTOOLBAR_H

#include <QWidget>
#include <QFile>
#include <QXmlStreamReader>
#include <QToolButton>
#include <QComboBox>
#include <QSlider>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QTimer>
#include <QSpacerItem>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include "datatypes.h"
#include "utility.h"
#include "mainwindow.h"
#include "textview.h"
#include "httpaccess.h"

class HttpDownloadManager;

class AudioToolBar : public QWidget
{
Q_OBJECT

private:
  MainWindow *MW;
  TextView *targetHolyTextView; // Указател към изгледа с който ще се синхронизира аудиото.
  QMediaPlayer *player;
  QMediaPlaylist *playlist;
  QList<AUDIO_LOCATION_FILE> audioLocationFileList;
  QMap<QString, QString> urlPathMap; // Всички налични URL-и (ключ - името на главата, стойност - URL-a).
  QMap<QString, QString> localPathMap; // Всички налични локални файлове-и (ключ - името на главата, стойност - пътя+името на файла).

  QComboBox   *audioLocationComboBox;
  QToolButton *playChapterBtn;
  QToolButton *playBookBtn;
  QToolButton *playGroupBtn;
  QToolButton *stopBtn;
  QToolButton *pauseBtn;
  QToolButton *repeatBtn;
  QToolButton *synchronizeBtn;
  QToolButton *previousBtn;
  QLabel      *labelInfo;
  QToolButton *nextBtn;
  QSlider     *seekSlider;
  QComboBox   *rateComboBox;
  QSlider     *volumeSlider;
  QToolButton *editBtn;
  QToolButton *newBtn;
  quint8       currentBook;

  void loadAudioLocationFilesInfo(); // Открива всички налични AudioLocation файлове и запомня информацията за тях в структура audioLocationFileList.
  void loadAudioLocationFiles(QString filePath); // Зарежда желания AudioLocation файл.
  QString createBlankAudioLocationFile(); // Създава празен AudioLocation файл за да може да се попълни от потребителя.
  QString getLocalPath(const quint8 book, const quint8 chapter);
  QString getUrlPath(const quint8 book, const quint8 chapter);

private slots:
  void slotAudioLocation(const int index);
  void slotPlayChapter();
  void slotPlayBook();
  void slotPlayGroup();
  void slotStop();
  void slotPause();
  void slotRepeat();
  void slotPrevious();
  void slotNext();
  void slotStateChanged(QMediaPlayer::State state);
  void slotStatusChanged(QMediaPlayer::MediaStatus status);
  void slotError(QMediaPlayer::Error error);
  void slotPlaylistCurrentIndexChanged(int position);
  void slotSeekSliderMoved(int position);
  void slotPlayerDurationChanged(qint64 duration);
  void slotPlayerPositionChanged(qint64 progress);
  void slotRate(const int index);
  void slotVolumeSliderMoved(int volume);
  void slotEdit();
  void slotEditEnd(QString fileName);
  void slotNew();
public slots:
  void slotPlayCurrentChapterNow();
  void slotForceStop();
  void slotSetToolBarFontSize();

public:
  AudioToolBar(MainWindow *MW, QWidget *parent = 0);
  void enableButtonPlayGroup(bool enable);
};

// =============================================================================================================================================================

class AudioLocationFileEditor : public QWidget
{
Q_OBJECT

private:
  MainWindow   *MW;
  HttpDownloadManager *DM;
  QLineEdit    *leShortDescription;
  QLabel       *lblFileName;
  QGroupBox    *grBoxDownload;
  QLineEdit    *leTargetDir;
  QPushButton  *btnTargetDirChoice;
  QCheckBox    *chBoxAutoFillLocalPath;
  QTextEdit    *teLog;
  QPushButton  *btnDownload;
  QPushButton  *btnStop;
  QProgressBar *prgBarChapter;
  QProgressBar *prgBarAll;
  QPushButton  *btnDelete;
  QPushButton  *showDownloadPanelBtn;
  QPushButton  *btnSave;
  QPushButton  *btnClose;
  QListWidget  *lwBooks;
  QTableWidget *tablePaths;
  
  // За редактора:
  QMap<QString, QString> urlPathMap; // Всички налични URL-и (ключ - името на главата, стойност - URL-a).
  QMap<QString, QString> localPathMap; // Всички налични локални файлове-и (ключ - името на главата, стойност - пътя+името на файла).
  QString currentFileName; // Име на аудио файла.
  int currentBook; // Текущо показана книга.
  bool isModified; // Указва, че документът е модифициран. След записване този флаг е false и не може да се използва за излъчване на сигнал при затваряне на формата.
  bool isSaved; // Указва, че документът е бил записан на хардиска. Това ще разреши излъчване на сигнал при затваряне на формата.
  bool isRenamed; // Указва, че документът е бил преименуван. Това ще разреши излъчване на сигнал при запис или при затваряне на формата.

  // За свалянето на аудиото:
  QStringList allDownloadUrlPathKeys; // Списък с ключовете на всички URL-и, които ще се свалят. Генерира се при натискане на бутона за сваляне.
  QStringList allDownloadLocalPaths; // Списък с пътя+името на файла на всички глави, които имат Url-и. Генерира се при натискане на бутона за сваляне.
  int currentDownloadChapter; // Текущ индекс в горните два списъка т.е. текущата глава (аудио файл), която се сваля.
  QString targetDownloadDir; // Текуща директория, в която ще се сваля аудиото.
  bool enableDownload; // Флаг указващ, че е натиснат бутонът за старт на свалянето. Флагът ще бъде свален при натискане на бутон стоп.
  bool currentDownloadDone; // Флаг указващ, че текущият файл е изтеглен.
  QTimer *downloadTimer;

  void closeEvent(QCloseEvent *event);
  bool loadXML(); // Чете от XML-а.
  bool saveXML(); // Записва в XML-а.
  void loadUrls(); // Зарежда Url-ите в таблицата.
  void writeUrls(); // Записва Url-ите от таблицата.
  QString getLocalPath(const quint8 book, const quint8 chapter);
  void setLocalPath(const quint8 book, const quint8 chapter, QString localPath);
  QString getUrlPath(const quint8 book, const quint8 chapter);
  void setUrlPath(const quint8 book, const quint8 chapter, QString urlPath);
  bool getFreeFileName(QString &newFileName, QString &newFilePath);
  QString getUrlFileName(const QString url); // Извлича името на файла от Url-а. Ако няма ясно обособено име, връща празен стринг.
  QString getUrlFileSuffix(const QString url); // Извлича разширението на файла от Url-а. Ако няма ясно обособено разширение, връща празен стринг.
  void enableEditFile(bool enable); // Enable/Disable на контролите за редактиране на файла.

private slots:
  void slotShortDescriptionChanged(const QString &text);
  void slotBookChanged(int currentRow);
  void slotTargetDirChoice();
  void slotStartDownload();
  void slotStopDownload();
  void slotDownloadTimer();
  void slotDownloadFinished(QString url, QString filePath, bool error, QString errorString);
  void slotDelete();
  void slotShowDownloadPanel(bool checked);
  void slotSave();

public:
  AudioLocationFileEditor(MainWindow *MW, QString fileName, QWidget *parent = 0);

signals:
  void modified(QString fileName); // Излъчва се при затваряне на прозореца и носи като аргумент името на файла, за да се сетне комбобокса.
};

#endif // AUDIOTOOLBAR_H
