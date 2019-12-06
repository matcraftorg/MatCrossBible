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

#include "audiotoolbar.h"

AudioToolBar::AudioToolBar(MainWindow *MW, QWidget *parent) : QWidget(parent)
{
  this->MW = MW;
  connect(MW, SIGNAL(playCurrentChapterNow()), this, SLOT(slotPlayCurrentChapterNow()));
  targetHolyTextView = 0;

  currentBook = 0;

  QFont font;
  font.setPointSize(MW->MO->SVars.otherToolBarFontSize);
  setFont(font);

  QDir dir; // Създава (ако не съществуват) директория Audio.
  dir.mkpath(QString("%1/Audio").arg(MW->MO->applicationDirPath));
  loadAudioLocationFilesInfo();

  audioLocationComboBox = new QComboBox();
  audioLocationComboBox->setMinimumContentsLength(5); // Може и без това, но да не се получава твърде малък комбобокс. Жалко, че няма и Max функция.
  //audioLocationComboBox->setMaximumWidth(180); // Това се прави на друго място - в слота slotSetToolBarFontSize.
  audioLocationComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents); // Това е важно за да може комбото да се преоразмерява след промяна на името на текущия файл.
  audioLocationComboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  int currentAudioLocation = 0;
  for (int i = 0; i < audioLocationFileList.count(); i++)
  {
    if (audioLocationFileList[i].fileName == MW->MO->SVars.currentAudioLocation) currentAudioLocation = i; // Ако запомненото име не е открито, ще се позиционира на първия в списъка.
    audioLocationComboBox->addItem(audioLocationFileList[i].shortDescription);
  }
  if (audioLocationFileList.count() > 0) audioLocationComboBox->setCurrentIndex(currentAudioLocation);
  loadAudioLocationFiles(audioLocationFileList[currentAudioLocation].filePath);
  connect(audioLocationComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotAudioLocation(const int)));

  playChapterBtn = new QToolButton();
  playChapterBtn->setText(MW->MO->TS->PlayChapter_v1);
  playChapterBtn->setToolTip(MW->MO->TS->PlayChapterTT_v1);
  playChapterBtn->setAutoRaise(true);
  connect(playChapterBtn, SIGNAL(clicked()), this, SLOT(slotPlayChapter()));

  playBookBtn = new QToolButton();
  playBookBtn->setText(MW->MO->TS->PlayBook_v1);
  playBookBtn->setToolTip(MW->MO->TS->PlayBookTT_v1);
  playBookBtn->setAutoRaise(true);
  connect(playBookBtn, SIGNAL(clicked()), this, SLOT(slotPlayBook()));

  playGroupBtn = new QToolButton();
  playGroupBtn->setText(MW->MO->TS->PlayGroup_v1);
  playGroupBtn->setToolTip(MW->MO->TS->PlayGroupTT_v1);
  playGroupBtn->setAutoRaise(true);
  connect(playGroupBtn, SIGNAL(clicked()), this, SLOT(slotPlayGroup()));

  stopBtn = new QToolButton();
  stopBtn->setText(MW->MO->TS->Stop_v1);
  stopBtn->setToolTip(MW->MO->TS->Stop_v1);
  stopBtn->setAutoRaise(true);
  stopBtn->setEnabled(false);
  connect(stopBtn, SIGNAL(clicked()), this, SLOT(slotStop()));

  pauseBtn = new QToolButton();
  pauseBtn->setText(MW->MO->TS->Pause_v1);
  pauseBtn->setToolTip(MW->MO->TS->Pause_v1);
  pauseBtn->setAutoRaise(true);
  pauseBtn->setCheckable(true);
  pauseBtn->setChecked(false);
  pauseBtn->setEnabled(false);
  connect(pauseBtn, SIGNAL(clicked()), this, SLOT(slotPause()));

  repeatBtn = new QToolButton();
  repeatBtn->setText(QString("R")); // R ∞
  repeatBtn->setToolTip(MW->MO->TS->Repeat_v1);
  repeatBtn->setAutoRaise(true);
  repeatBtn->setCheckable(true);
  repeatBtn->setChecked(false);
  connect(repeatBtn, SIGNAL(clicked()), this, SLOT(slotRepeat()));

  synchronizeBtn = new QToolButton();
  synchronizeBtn->setText(QString("S")); // S ↔
  synchronizeBtn->setToolTip(MW->MO->TS->Synchronize_v1);
  synchronizeBtn->setAutoRaise(true);
  synchronizeBtn->setCheckable(true);
  synchronizeBtn->setChecked(false);

  labelInfo = new QLabel("--");
  labelInfo->setToolTip(MW->MO->TS->CurrentChapter_v1);

  previousBtn = new QToolButton();
  previousBtn->setText(QString(" < "));
  previousBtn->setToolTip(MW->MO->TS->PreviousChapter_v1);
  previousBtn->setAutoRaise(true);
  previousBtn->setEnabled(false);
  connect(previousBtn, SIGNAL(clicked()), this, SLOT(slotPrevious()));

  nextBtn = new QToolButton();
  nextBtn->setText(QString(" > "));
  nextBtn->setToolTip(MW->MO->TS->NextChapter_v1);
  nextBtn->setAutoRaise(true);
  nextBtn->setEnabled(false);
  connect(nextBtn, SIGNAL(clicked()), this, SLOT(slotNext()));

  newBtn = new QToolButton();
  newBtn->setText(MW->MO->TS->NewALF_v1);
  newBtn->setToolTip(MW->MO->TS->NewALFTT_v1);
  newBtn->setAutoRaise(true);
  connect(newBtn, SIGNAL(clicked()), this, SLOT(slotNew()));

  editBtn = new QToolButton();
  editBtn->setText(MW->MO->TS->EditALF_v1);
  editBtn->setToolTip(MW->MO->TS->EditALFTT_v1);
  editBtn->setAutoRaise(true);
  connect(editBtn, SIGNAL(clicked()), this, SLOT(slotEdit()));



  // За MediaPlayer:
  playlist = new QMediaPlaylist();
  connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(slotPlaylistCurrentIndexChanged(int)));

  player = new QMediaPlayer();
  player->setPlaylist(playlist);
  connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(slotStateChanged(QMediaPlayer::State)));
  connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(slotStatusChanged(QMediaPlayer::MediaStatus)));
  connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(slotError(QMediaPlayer::Error)));

  seekSlider = new QSlider(Qt::Horizontal);
  seekSlider->setToolTip(MW->MO->TS->Seek_v1);
  seekSlider->setRange(0, player->duration());
  seekSlider->setMinimumWidth(30);
  seekSlider->setMaximumWidth(20000);
  //connect(seekSlider, SIGNAL(sliderMoved(int)), player, SLOT(setPosition(qint64))); // Така не става, затова с долния ред.
  connect(seekSlider, SIGNAL(sliderMoved(int)), this, SLOT(slotSeekSliderMoved(int)));
  connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(slotPlayerDurationChanged(qint64)));
  connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(slotPlayerPositionChanged(qint64)));

  rateComboBox = new QComboBox();
  rateComboBox->setToolTip(MW->MO->TS->Rate_v1);
  rateComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred); // Preferred Expanding
  rateComboBox->addItem("x 1.0", QVariant(1.0));
  rateComboBox->addItem("x 1.5", QVariant(1.5));
  rateComboBox->addItem("x 2.0", QVariant(2.0));
  rateComboBox->setCurrentIndex(0);
  connect(rateComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotRate(const int)));

  volumeSlider = new QSlider(Qt::Horizontal);
  volumeSlider->setToolTip(MW->MO->TS->Volume_v1);
  volumeSlider->setRange(0, 10);
  volumeSlider->setValue(player->volume());
  volumeSlider->setMinimumWidth(30);
  volumeSlider->setMaximumWidth(100);
  connect(volumeSlider, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
  connect(player, SIGNAL(volumeChanged(int)), this, SLOT(slotVolumeSliderMoved(int)));

  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->setContentsMargins(1, 1, 1, 1); // LTRB
  hLayout->setSpacing(1); // Разстояние между обектите.
  hLayout->addWidget(audioLocationComboBox);
  hLayout->addWidget(playChapterBtn);
  hLayout->addWidget(playBookBtn);
  hLayout->addWidget(playGroupBtn);
  hLayout->addWidget(stopBtn);
  hLayout->addWidget(pauseBtn);
  hLayout->addWidget(repeatBtn);
  hLayout->addWidget(synchronizeBtn);
  hLayout->addWidget(previousBtn);
  hLayout->addWidget(labelInfo);
  hLayout->addWidget(nextBtn);
  hLayout->addWidget(seekSlider);
  hLayout->addWidget(rateComboBox);
  hLayout->addWidget(volumeSlider);
  hLayout->addWidget(MW->getVSeparator());
  hLayout->addWidget(newBtn);
  hLayout->addWidget(editBtn);

  resize(editBtn->x() + editBtn->width() + 10, MW->MO->SVars.otherToolBarFontSize + 12); // 12 е най-добрата добавка към размера на шрифта - нито повече, нито по-малко.
}

void AudioToolBar::loadAudioLocationFilesInfo()
{
  audioLocationFileList.clear();

  QFile *file;
  QString filePath;
  QStringList allFileNames = QDir( QString("%1/Audio").arg(MW->MO->applicationDirPath) ).entryList(QDir::Files, QDir::Name); // QDir::Name QDir::Time QDir::Unsorted
  for (int n = 0; n < allFileNames.count(); n++)
  {
    filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(allFileNames[n]);
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().toLower() != QString("alf")) continue; // Ако разширението на файла не е .alf го игнорира.
  
    if (QFile::exists(filePath))
    {
      file = new QFile(filePath);
      if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) continue;

      QXmlStreamReader xml(file); // Лошото тук е, че за да се прочете shortDescription-на се зарежда целия файл в паметта.
      QString currentTag;
      while (!xml.atEnd() && !xml.hasError())
      {
        xml.readNext();
        currentTag = xml.name().toString(); // xml.name() връща само името (например "title"), а xml.qualifiedName() връща неймспейса+името (например "media:title").

        if (xml.isStartElement())
        {
          if (currentTag.compare("AudioLocationFile", Qt::CaseInsensitive) == 0)
          {
            if ( xml.attributes().value("", "structureVersion").toString().trimmed() != "1" ) break; // Ако версията на файла е различна.

            AUDIO_LOCATION_FILE alf;
            alf.fileName = allFileNames[n];// Име на файла без пътя.
            alf.filePath = filePath; // Име на файла с пътя.
            alf.shortDescription = xml.attributes().value("", "shortDescription").toString().trimmed();
            if (alf.shortDescription.isEmpty()) alf.shortDescription = alf.fileName;
            audioLocationFileList << alf;
          }
        }
      }

      file->close();
      delete file;
    }
  }
  
  if (audioLocationFileList.count() == 0) // Ако няма нито един ALF файл.
  {
    // Създава празен ALF файл:
    AUDIO_LOCATION_FILE alf;
    alf.fileName = createBlankAudioLocationFile();
    if (alf.fileName.isEmpty()) alf.fileName = "AudioLocation.alf"; // Ако има проблем при създаването на нов файл, задава "служебно" име за да не гръмне програмата (така в комбобокса винаги ще има поне един елемент и логиката ще върви).
    alf.filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(alf.fileName);
    alf.shortDescription = alf.fileName;
    audioLocationFileList << alf;
  }
}

void AudioToolBar::loadAudioLocationFiles(QString filePath)
{
  urlPathMap.clear();
  localPathMap.clear();

  if (QFile::exists(filePath))
  {
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QXmlStreamReader xml(file);
    QString currentTag;
    QString chapter;
    QString urlPath;
    QString localPath;
    while (!xml.atEnd() && !xml.hasError())
    {
      xml.readNext();
      currentTag = xml.name().toString(); // xml.name() връща само името (например "title"), а xml.qualifiedName() връща неймспейса+името (например "media:title").

      if (xml.isStartElement())
      {
        if (currentTag.compare("AudioLocationFile", Qt::CaseInsensitive) == 0)
        {
          if ( xml.attributes().value("", "structureVersion").toString().trimmed() != "1" ) break; // Ако версията на файла е различна.
        }
        else if (currentTag.compare("Location", Qt::CaseInsensitive) == 0)
        {
          chapter = xml.attributes().value("", "chapter").toString().trimmed();
          urlPath = xml.attributes().value("", "urlPath").toString().trimmed();
          localPath = xml.attributes().value("", "localPath").toString().trimmed();

          if (!chapter.isEmpty())
          {
            if (!urlPath.isEmpty()) urlPathMap.insert(chapter, urlPath);
            if (!localPath.isEmpty()) localPathMap.insert(chapter, localPath);
          }
        }
      }
    }

    file->close();
    delete file;
  }
}

QString AudioToolBar::createBlankAudioLocationFile()
{
  // Структурата на AudioLocation XML файла е следната:
  //
  // Празен:
  //
  // <?xml version="1.0"?>
  // <AudioLocationFile structureVersion="1" shortDescription="" targetDownloadDir="">
  //   <Location chapter="Genesis_1" urlPath="" localPath="" />
  //   <Location chapter="Genesis_2" urlPath="" localPath="" />
  //   <Location chapter="Genesis_3" urlPath="" localPath="" />
  //   ...
  //   <Location chapter="Revelation_21" urlPath="" localPath="" />
  //   <Location chapter="Revelation_22" urlPath="" localPath="" />
  // </AudioLocationFile>
  //
  // Примерен:
  //
  // <?xml version="1.0"?>
  // <AudioLocationFile structureVersion="1" shortDescription="Audio AKJV" targetDownloadDir="">
  //   <Location chapter="Genesis_1" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_01.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_01.mp3" />
  //   <Location chapter="Genesis_2" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_02.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_02.mp3" />
  //   <Location chapter="Genesis_3" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_03.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_03.mp3" />
  //   ...
  //   <Location chapter="Revelation_21" urlPath="http://audiobible.net/AKJV/Revelation/Revelation_21.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Revelation/Revelation_21.mp3" />
  //   <Location chapter="Revelation_22" urlPath="http://audiobible.net/AKJV/Revelation/Revelation_22.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Revelation/Revelation_22.mp3" />
  // </AudioLocationFile>

  QString num = "";
  QString text = "<?xml version=\"1.0\"?>\n";
  text += "<AudioLocationFile structureVersion=\"1\" shortDescription=\"\" targetDownloadDir=\"\">\n";
  for (int i = 0; i < 77; i++)
  {
    for (int c = 1; c <= MW->MO->chaptersCountArr[i]; c++)
    {
      num = (c < 10) ? QString("0%1").arg(c) : QString("%1").arg(c);
      text += QString("	<Location chapter=\"%1_%2\" urlPath=\"\" localPath=\"\" />\n").arg(MW->MO->bookFileNameArr[i]).arg(num);
    }
  }
  text += "</AudioLocationFile>\n";

  QDir dir; // Създава (ако не съществуват) директория Audio.
  dir.mkpath(QString("%1/Audio").arg(MW->MO->applicationDirPath));

  // Определя името на файла.
  QString fileName = "";
  QString filePath = "";
  for (quint16 n = 1; n <= 500; n++)
  {
    fileName = QString("AudioLocation_%1.alf").arg(n);
    filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(fileName);
    if (!QFile::exists(filePath))
    {
      break;
    }
    if (n == 500) return ""; // Ако няма свободни имена.
  }

  QFile *alf = new QFile(filePath);
  if (alf->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(alf);
    out << text;
    alf->close();
  }
  else
  {
    fileName = ""; // Изтрива името, ако поради някаква причина не може да се запише, за да върне празен стринг.
  }
  delete alf;

  return fileName;
}

QString AudioToolBar::getLocalPath(const quint8 book, const quint8 chapter)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  QString path = localPathMap.value(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), ""); // Връща празен стринг, ако няма път.
  return (QFile::exists(path) ? path : "");
}

QString AudioToolBar::getUrlPath(const quint8 book, const quint8 chapter)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  QString path = urlPathMap.value(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), ""); // Връща празен стринг, ако няма път.
  return path;
}

void AudioToolBar::enableButtonPlayGroup(bool enable)
{
  //playGroupBtn->setEnabled(enable);
  if (enable)
  {
    playGroupBtn->setVisible(true);
    synchronizeBtn->setVisible(false);
  }
  else
  {
    playGroupBtn->setVisible(false);
    synchronizeBtn->setVisible(true);
  }
}

void AudioToolBar::slotSetToolBarFontSize()
{
  QFontMetrics fm(this->font());
  int tbBtnMargins = MW->MO->SVars.otherToolBarFontSize + 2*(5 + MW->MO->SVars.otherToolBarFontSize/3); // Опита показва, че горният и долният маргин (разстоянието между надписа на бутона и стените му) се изчисляват най-добре по тази формула за да се показват бутоните добре.
  int lrBtnMargins = 2 * (5 + fm.width(" ")); // Опита показва, че левият и десният маргин (разстоянието между надписа на бутона и стените му) са равни на 5 точни + широчината на един интервал. Ето защо това разстояние се добавя към дължината на надписа на бутона.
  int panelWidth = 0; // Дължина на панела. Ще се изчисли така, че всички компоненти да се съберат в него.

  audioLocationComboBox->setMaximumWidth(30 * fm.width("А")); // Това се прави тук защото няма метод setMaximumContentsLength(30).

  panelWidth += (20 * fm.width("А")); // За audioLocationComboBox - грубо - някаква средна стойност (seekSlider ще обере разликите).
  panelWidth += fm.width(playChapterBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(playBookBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(playGroupBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(stopBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(pauseBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(repeatBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(synchronizeBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(previousBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(labelInfo->text());
  panelWidth += fm.width(nextBtn->text()) + lrBtnMargins;
  panelWidth += 240; // За seekSlider - грубо. Той ще обере разликите.
  panelWidth += fm.width("x 1.0") + lrBtnMargins + 10; // За rateComboBox - грубо.
  panelWidth += 100; // За volumeSlider.
  panelWidth += fm.width(editBtn->text()) + lrBtnMargins;
  panelWidth += fm.width(newBtn->text()) + lrBtnMargins;

  this->resize(panelWidth, tbBtnMargins); // Това ще бъде новият размер на панела. Всички компоненти трябва да се съберат в него.
}

void AudioToolBar::slotAudioLocation(const int index)
{
  MW->MO->SVars.currentAudioLocation = audioLocationFileList[index].fileName;
  QSettings settings(MW->MO->iniFile, QSettings::IniFormat, this);
  settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
  settings.beginGroup(QString("Audio"));
    settings.setValue(QString("currentAudioLocation"), MW->MO->SVars.currentAudioLocation);
  settings.endGroup();

  loadAudioLocationFiles(audioLocationFileList[index].filePath);
}

void AudioToolBar::slotPlayChapter()
{
  if (targetHolyTextView != 0) return;
  targetHolyTextView = MW->currentHolyTextView;
  
  QString localPath;
  QString urlPath;
  quint8  book;
  quint8  chapter;

  if (targetHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в нормален режим на четене.
  {
    book = MW->MO->toBookCode(targetHolyTextView->currentAbsIndex);
    chapter = MW->MO->toChapterCode(targetHolyTextView->currentAbsIndex);
    localPath = getLocalPath(book, chapter); // Връща пътя до файла само ако съществува реално на диска.
    urlPath = getUrlPath(book, chapter);
  
    currentBook = MW->MO->toBookCode(targetHolyTextView->currentAbsIndex);
  }
  else // Ако е в режим на ежедневно четене.
  {
    book = MW->MO->toBookCode(MW->currentDR_AbsIndex);
    chapter = MW->MO->toChapterCode(MW->currentDR_AbsIndex);
    localPath = getLocalPath(book, chapter); // Връща пътя до файла само ако съществува реално на диска.
    urlPath = getUrlPath(book, chapter);
  }

  if (localPath.isEmpty() && urlPath.isEmpty()) // Ако няма аудио за тази книга.
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->NoAudioForThisBook_v1);
    targetHolyTextView = 0;
    return;
  }
  
  player->stop();

  playlist->clear();
  playlist->addMedia( localPath.isEmpty() ? QUrl(urlPath) : QUrl::fromLocalFile(localPath) );

  player->play();
  
  previousBtn->setEnabled(false);
  nextBtn->setEnabled(false);
}

void AudioToolBar::slotPlayBook()
{
  if (targetHolyTextView != 0) return;
  targetHolyTextView = MW->currentHolyTextView;
  
  QString localPath;
  QString urlPath;
  quint8  book;
  quint8  endChapter;

  if (targetHolyTextView->readMode == READ_MODE__NORMAL) // Ако е в нормален режим на четене.
  {
    book = MW->MO->toBookCode(targetHolyTextView->currentAbsIndex);
    endChapter = MW->MO->chaptersCountArr[book-1];
  
    currentBook = MW->MO->toBookCode(targetHolyTextView->currentAbsIndex);
  }
  else // Ако е в режим на ежедневно четене.
  {
    book = MW->MO->toBookCode(MW->currentDR_AbsIndex);
    endChapter = MW->MO->chaptersCountArr[book-1];
  }
  
  player->stop();

  playlist->clear();
  bool hasAudioFiles = false;
  for (quint8 i = 1; i <= endChapter; i++)
  {
    localPath = getLocalPath(book, i); // Връща пътя до файла само ако съществува реално на диска.
    urlPath = getUrlPath(book, i);
    if (!localPath.isEmpty())
    {
      hasAudioFiles = true;
      playlist->addMedia( QUrl::fromLocalFile(localPath) );
    }
    else if (!urlPath.isEmpty())
    {
      hasAudioFiles = true;
      playlist->addMedia( QUrl(urlPath) );
    }
    else
    {
      playlist->addMedia( QUrl::fromLocalFile("NoAudioFile") ); // Добавя някакво измислено име на файл само за да не остава празно. Разбира се, при опит да се изпълни ще даде грешка.
    }
  }
  
  if (!hasAudioFiles) // Ако няма нито един аудио файл за тази книга.
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->NoAudioForThisBook_v1);
    targetHolyTextView = 0;
    return;
  }

  player->play();
  
  previousBtn->setEnabled(true);
  nextBtn->setEnabled(true);
}

void AudioToolBar::slotPlayGroup()
{
  if (targetHolyTextView != 0) return;
  targetHolyTextView = MW->currentHolyTextView;
  if (targetHolyTextView->readMode != READ_MODE__DAILY_READ) return;
  
  QString localPath;
  QString urlPath;
  quint8  book = MW->MO->toBookCode(MW->currentDR_AbsIndex);
  quint8  beginChapter = MW->MO->toChapterCode(MW->currentDR_DailyGroup[0]);
  quint8  endChapter = MW->MO->toChapterCode(MW->currentDR_DailyGroup[MW->currentDR_DailyGroup.size()-1]);
  
  player->stop();

  playlist->clear();
  bool hasAudioFiles = false;
  for (quint8 i = beginChapter; i <= endChapter; i++)
  {
    localPath = getLocalPath(book, i); // Връща пътя до файла само ако съществува реално на диска.
    urlPath = getUrlPath(book, i);
    if (!localPath.isEmpty())
    {
      hasAudioFiles = true;
      playlist->addMedia( QUrl::fromLocalFile(localPath) );
    }
    else if (!urlPath.isEmpty())
    {
      hasAudioFiles = true;
      playlist->addMedia( QUrl(urlPath) );
    }
    else
    {
      playlist->addMedia( QUrl::fromLocalFile("NoAudioFile") ); // Добавя някакво измислено име на файл само за да не остава празно. Разбира се, при опит да се изпълни ще даде грешка.
    }
  }
  
  if (!hasAudioFiles) // Ако няма нито един аудио файл за тази книга.
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->NoAudioForThisBook_v1);
    targetHolyTextView = 0;
    return;
  }

  player->play();
  
  previousBtn->setEnabled(true);
  nextBtn->setEnabled(true);
}

void AudioToolBar::slotStop()
{
  player->stop();
  previousBtn->setEnabled(false);
  nextBtn->setEnabled(false);
  pauseBtn->setChecked(false);
  labelInfo->setText("--");

  if (targetHolyTextView != 0)
  {
    targetHolyTextView->dockWidget->setDockWidgetDisallowCloseLevel2(false); // Отблокира раздела за да може да се затвори.
    targetHolyTextView = 0; // Това е нужно защото слота slotStateChanged се извиква със закъснение, а тогава вече разделът е затворен и targetHolyTextView сочи към нищото.
  }
}

void AudioToolBar::slotForceStop()
{
  slotStop();
}

void AudioToolBar::slotPlayCurrentChapterNow()
{
  slotStop(); // Принудителен край на слушането (ако е пуснато).
  slotPlayChapter(); // Пуска текущата глава.
}

void AudioToolBar::slotPause()
{
  if ( pauseBtn->isChecked() )
  {
    player->pause();
  }
  else
  {
    player->play();
  }
}

void AudioToolBar::slotRepeat()
{
  if ( repeatBtn->isChecked() )
  {
    playlist->setPlaybackMode(QMediaPlaylist::Loop); // Започва отначало.
  }
  else
  {
    playlist->setPlaybackMode(QMediaPlaylist::Sequential); // Не започва отначало.
  }
}

void AudioToolBar::slotPrevious()
{
  int index = playlist->currentIndex() - 1;
  if (index < 0) return;

  pauseBtn->setChecked(false); // Това не задейства ивента, а само сменя състоянието на бутона.

  playlist->previous();
}

void AudioToolBar::slotNext()
{
  int index = playlist->currentIndex() + 1;
  if (index >= playlist->mediaCount() && !repeatBtn->isChecked()) return;

  pauseBtn->setChecked(false); // Това не задейства ивента, а само сменя състоянието на бутона.

  playlist->next();
}

void AudioToolBar::slotStateChanged(QMediaPlayer::State state)
{
  switch (state)
  {
  case QMediaPlayer::PlayingState:
    playChapterBtn->setEnabled(false);
    playBookBtn->setEnabled(false);
    playGroupBtn->setEnabled(false);
    pauseBtn->setEnabled(true);
    stopBtn->setEnabled(true);
    if (targetHolyTextView != 0) targetHolyTextView->dockWidget->setDockWidgetDisallowCloseLevel2(true); // Блокира раздела за да не може да се затвори.
    break;
  case QMediaPlayer::StoppedState:
    playChapterBtn->setEnabled(true);
    playBookBtn->setEnabled(true);
    playGroupBtn->setEnabled(true);
    pauseBtn->setEnabled(false);
    stopBtn->setEnabled(false);
    previousBtn->setEnabled(false);
    nextBtn->setEnabled(false);
    labelInfo->setText("--");
    if (targetHolyTextView != 0) targetHolyTextView->dockWidget->setDockWidgetDisallowCloseLevel2(false); // Отблокира раздела за да може да се затвори.
  break;
  case QMediaPlayer::PausedState:
    //playChapterBtn->setEnabled(true);
    //playBookBtn->setEnabled(true);
    //playGroupBtn->setEnabled(true);
    pauseBtn->setEnabled(true);
    stopBtn->setEnabled(true);
    if (targetHolyTextView != 0) targetHolyTextView->dockWidget->setDockWidgetDisallowCloseLevel2(true); // Блокира раздела за да не може да се затвори.
    break;
  default:
    ;
  }
}

void AudioToolBar::slotStatusChanged(QMediaPlayer::MediaStatus status)
{
  switch (status)
  {
  case QMediaPlayer::UnknownMediaStatus:
  case QMediaPlayer::NoMedia:
  case QMediaPlayer::LoadedMedia:
  case QMediaPlayer::BufferingMedia:
  case QMediaPlayer::BufferedMedia:
    break;
  case QMediaPlayer::LoadingMedia:
    break;
  case QMediaPlayer::StalledMedia:
    break;
  case QMediaPlayer::EndOfMedia:
    QApplication::alert(MW, 2000); // За Windows - иконата в таскбара ще пресвятка за 2 секунди при смяна на аудио главата (но само ако прозорецът не е активен в момента).
    break;
  case QMediaPlayer::InvalidMedia:
    MW->showStatusBarMessage(QString("MediaPlayer: Invalid Media Error"), 30000);
    break;
  }
}

void AudioToolBar::slotError(QMediaPlayer::Error error)
{
  QString err = player->errorString();
  if (err.isEmpty())
  {
    switch (error)
    {
    case QMediaPlayer::NoError:
      break;
    case QMediaPlayer::ResourceError: // Ако няма такъв аудио файл.
      MW->showStatusBarMessage(QString("MediaPlayer: Resource Error (A media resource couldn't be resolved)"), 30000);
      break;
    case QMediaPlayer::FormatError:
      MW->showStatusBarMessage(QString("MediaPlayer: Format Error (The format of a media resource isn't (fully) supported. Playback may still be possible, but without an audio or video component)"), 30000);
      break;
    case QMediaPlayer::NetworkError:
      MW->showStatusBarMessage(QString("MediaPlayer: Network Error (A network error occurred)"), 30000);
      break;
    case QMediaPlayer::AccessDeniedError:
      MW->showStatusBarMessage(QString("MediaPlayer: Access Denied Error (There are not the appropriate permissions to play a media resource)"), 30000);
      break;
    case QMediaPlayer::ServiceMissingError:
      MW->showStatusBarMessage(QString("MediaPlayer: Service Missing Error (A valid playback service was not found, playback cannot proceed)"), 30000);
      break;
	default:
      break;
    }
  }
  else
  {
    MW->showStatusBarMessage(QString("MediaPlayer Error: %1").arg(err), 30000);
  }
}

void AudioToolBar::slotPlaylistCurrentIndexChanged(int position)
{
  if (position < 0 || position >= playlist->mediaCount()) return;

  if (synchronizeBtn->isVisible() && synchronizeBtn->isChecked() && targetHolyTextView != 0 && targetHolyTextView->readMode == READ_MODE__NORMAL)
    targetHolyTextView->showBibleText(MW->MO->toAbsIndex(currentBook, (quint8)(position+1), 1));

  // Този ред трябва да е след горния (showBibleText)
  labelInfo->setText(QString("%1").arg(position+1));
}

void AudioToolBar::slotSeekSliderMoved(int position)
{
  player->setPosition(position);
}

void AudioToolBar::slotPlayerDurationChanged(qint64 duration)
{
  seekSlider->setMaximum(duration);
}

void AudioToolBar::slotPlayerPositionChanged(qint64 progress)
{
  if (!seekSlider->isSliderDown()) seekSlider->setValue(progress);
}

void AudioToolBar::slotRate(const int index)
{
  if (index == 2)
    player->setPlaybackRate(2.0);
  else if (index == 1)
    player->setPlaybackRate(1.5);
  else //if (index == 0)
    player->setPlaybackRate(1.0);
}

void AudioToolBar::slotVolumeSliderMoved(int volume)
{
  volumeSlider->setValue(volume);
}

void AudioToolBar::slotEdit()
{
  slotForceStop(); // За всеки случай спира аудиото (ако е пуснато).
  AudioLocationFileEditor *alfEditor = new AudioLocationFileEditor(MW, audioLocationFileList[audioLocationComboBox->currentIndex()].fileName);
  connect(alfEditor, SIGNAL(modified(QString)), this, SLOT(slotEditEnd(QString)));
  alfEditor->show();
}

void AudioToolBar::slotEditEnd(QString fileName)
{
  slotForceStop(); // Спира аудиото (ако е пуснато).

  audioLocationComboBox->disconnect();
  audioLocationComboBox->clear();

  loadAudioLocationFilesInfo();

  int currentAudioLocation = 0;
  for (int i = 0; i < audioLocationFileList.count(); i++)
  {
    audioLocationComboBox->addItem(audioLocationFileList[i].shortDescription);
    if (audioLocationFileList[i].fileName == fileName) currentAudioLocation = i;
  }

  audioLocationComboBox->setCurrentIndex(currentAudioLocation);
  loadAudioLocationFiles(audioLocationFileList[currentAudioLocation].filePath);
  connect(audioLocationComboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(slotAudioLocation(const int)));
}

void AudioToolBar::slotNew()
{
  slotForceStop(); // Спира аудиото (ако е пуснато).
  QString fileName = createBlankAudioLocationFile();
  if (!fileName.isEmpty())
  {
    slotEditEnd(fileName); // Добавя го в комбобокса и го прави текущ.
    slotEdit(); // Отваря формата за редакриране и го зарежда.
  }
}

// =============================================================================================================================================================

AudioLocationFileEditor::AudioLocationFileEditor(MainWindow *MW, QString fileName, QWidget *parent) : QWidget(parent)
{
  this->MW = MW;

  resize(880, 550);
  setWindowTitle(MW->MO->TS->ALFEditor_v1 + " - " + QCoreApplication::applicationName());
  
  leShortDescription = new QLineEdit(this);
  leShortDescription->setMaximumWidth(200);
  //connect(leShortDescription, SIGNAL(textChanged(const QString &)), this, SLOT(slotShortDescriptionChanged(const QString &))); // Този ред трябва да е след сетването на текста!!!

  lblFileName = new QLabel(fileName, this);
  lblFileName->setMinimumWidth(10);
  lblFileName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  QFont font;
  font.setBold(true);
  lblFileName->setFont(font);

  lwBooks = new QListWidget(this);
  lwBooks->setMaximumWidth(160);
  lwBooks->setFocus();
  for (int i = 0; i < 77; i++)
  {
    lwBooks->addItem(MW->MO->bookShortNameArr[i]);
  }
  lwBooks->setCurrentRow(0);
  connect(lwBooks, SIGNAL(currentRowChanged(int)), this, SLOT(slotBookChanged(int)));

  tablePaths = new QTableWidget(this);
  tablePaths->setColumnCount(2);
  tablePaths->horizontalHeader()->setStretchLastSection(true);
  tablePaths->verticalHeader()->setDefaultSectionSize(20);
  tablePaths->verticalHeader()->setMinimumSectionSize(16);
  tablePaths->setSelectionMode(QAbstractItemView::NoSelection);
  
  QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem(QString("URL Path"));
  tablePaths->setHorizontalHeaderItem(0, __qtablewidgetitem1);
  QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem(QString("Local Path"));
  tablePaths->setHorizontalHeaderItem(1, __qtablewidgetitem2);
  tablePaths->setColumnWidth(0, 350);
  //tablePaths->setColumnWidth(1, 350);
  
  // Download ==========================================================================================================================
  grBoxDownload = new QGroupBox(MW->MO->TS->DownloadAudioBibleTT_v1, this);
  grBoxDownload->setMaximumHeight(250);
  grBoxDownload->setVisible(false);

  leTargetDir = new QLineEdit(grBoxDownload);

  btnTargetDirChoice = new QPushButton(MW->MO->TS->TargetDirChoose_v1, grBoxDownload);
  connect(btnTargetDirChoice, SIGNAL(clicked()), this, SLOT(slotTargetDirChoice()));

  chBoxAutoFillLocalPath = new QCheckBox(MW->MO->TS->AutoFillLocalPath_v1, grBoxDownload);
  chBoxAutoFillLocalPath->setChecked(true);

  teLog = new QTextEdit(grBoxDownload);
  teLog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  teLog->setUndoRedoEnabled(false);
  teLog->setReadOnly(true);

  btnDownload = new QPushButton(MW->MO->TS->Download_v1, grBoxDownload);
  btnDownload->setMinimumSize(QSize(0, 40));
  btnDownload->setFont(font);
  connect(btnDownload, SIGNAL(clicked()), this, SLOT(slotStartDownload()));

  btnStop = new QPushButton(MW->MO->TS->DownloadStop_v1, grBoxDownload);
  btnStop->setMinimumSize(QSize(0, 40));
  btnStop->setFont(font);
  btnStop->setEnabled(false);
  connect(btnStop, SIGNAL(clicked()), this, SLOT(slotStopDownload()));

  QLabel *lblChapter = new QLabel(MW->MO->TS->CurrentChapter_v1, grBoxDownload);
  lblChapter->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

  prgBarChapter = new QProgressBar(grBoxDownload);
  prgBarChapter->setMinimum(0);
  prgBarChapter->setMaximum(100);
  prgBarChapter->setTextVisible(false);

  QLabel *lblAll = new QLabel(MW->MO->TS->AllChapters_v1, grBoxDownload);
  lblAll->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

  prgBarAll = new QProgressBar(grBoxDownload);
  prgBarAll->setMinimum(0);
  prgBarAll->setMaximum(100);
  prgBarAll->setTextVisible(false);
  // Download ==========================================================================================================================

  btnDelete = new QPushButton(MW->MO->TS->DeleteALF_v1, this);
  btnDelete->setToolTip(MW->MO->TS->DeleteALFTT_v1);
  connect(btnDelete, SIGNAL(clicked()), this, SLOT(slotDelete()));

  showDownloadPanelBtn = new QPushButton(MW->MO->TS->DownloadAudioBible_v1, this);
  showDownloadPanelBtn->setToolTip(MW->MO->TS->DownloadAudioBibleTT_v1);
  showDownloadPanelBtn->setCheckable(true);
  connect(showDownloadPanelBtn, SIGNAL(clicked(bool)), this, SLOT(slotShowDownloadPanel(bool)));

  btnSave = new QPushButton(MW->MO->TS->Save_v1, this);
  btnSave->setShortcut(QKeySequence::Save);
  btnSave->setToolTip(QKeySequence(QKeySequence::Save).toString());
  connect(btnSave, SIGNAL(clicked()), this, SLOT(slotSave()));

  btnClose = new QPushButton(MW->MO->TS->CloseWindow_v1, this);
  connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));

  QHBoxLayout *hLayout1 = new QHBoxLayout();
  hLayout1->setSpacing(3);
  hLayout1->addWidget(new QLabel(MW->MO->TS->ALFShortDescription_v1, this));
  hLayout1->addWidget(leShortDescription);
  hLayout1->addItem(new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum));
  hLayout1->addWidget(new QLabel(MW->MO->TS->ALFFileName_v1, this));
  hLayout1->addWidget(lblFileName);

  QHBoxLayout *hLayout2 = new QHBoxLayout();
  hLayout2->setSpacing(3);
  hLayout2->addWidget(lwBooks);
  hLayout2->addWidget(tablePaths);

  QHBoxLayout *hLayout3 = new QHBoxLayout();
  hLayout3->setSpacing(3);
  hLayout3->addWidget(btnDelete);
  hLayout3->addWidget(showDownloadPanelBtn);
  hLayout3->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
  hLayout3->addWidget(btnSave);
  hLayout3->addWidget(btnClose);

  QHBoxLayout *hLayoutD1 = new QHBoxLayout();
  hLayoutD1->setSpacing(3);
  hLayoutD1->addWidget(leTargetDir);
  hLayoutD1->addWidget(btnTargetDirChoice);
  
  QGridLayout *gridLayoutD1 = new QGridLayout();
  gridLayoutD1->setHorizontalSpacing(10);
  gridLayoutD1->setVerticalSpacing(3);
  gridLayoutD1->addWidget(teLog, 0, 0, 5, 3);
  gridLayoutD1->addWidget(btnDownload, 0, 3, 1, 1);
  gridLayoutD1->addWidget(btnStop, 0, 4, 1, 1);
  gridLayoutD1->addWidget(lblChapter, 1, 3, 1, 2);
  gridLayoutD1->addWidget(prgBarChapter, 2, 3, 1, 2);
  gridLayoutD1->addWidget(lblAll, 3, 3, 1, 2);
  gridLayoutD1->addWidget(prgBarAll, 4, 3, 1, 2);
  
  QVBoxLayout *vLayoutD1 = new QVBoxLayout(grBoxDownload);
  vLayoutD1->setSpacing(15);
  vLayoutD1->setContentsMargins(3, 3, 3, 3);
  vLayoutD1->addLayout(hLayoutD1);
  vLayoutD1->addWidget(chBoxAutoFillLocalPath);
  vLayoutD1->addLayout(gridLayoutD1);

  QVBoxLayout *vLayout = new QVBoxLayout(this);
  vLayout->setSpacing(3);
  vLayout->setContentsMargins(3, 3, 3, 3);
  vLayout->addLayout(hLayout1);
  vLayout->addLayout(hLayout2);
  vLayout->addWidget(grBoxDownload);
  vLayout->addLayout(hLayout3);

  currentFileName = fileName;
  currentBook = 0;
  isModified = false; // Това, че е модифициран не значи, че е записан.
  isSaved = false; // Това значи, че е и модифициран и записан.
  isRenamed = false;

  currentDownloadChapter = -1;
  targetDownloadDir = "";
  enableDownload = false;
  currentDownloadDone = true;

  if (!loadXML())
  {
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->FileReadError_v1);
    leShortDescription->setEnabled(false);
    btnSave->setEnabled(false);
    lwBooks->setEnabled(false);
    tablePaths->setEnabled(false);
    showDownloadPanelBtn->setEnabled(false);
    return;
  }
  loadUrls();

  DM = 0;            // Ще ги създаде при първо отваряне на панела за изтегляне.
  downloadTimer = 0; //
}

void AudioLocationFileEditor::closeEvent(QCloseEvent *event)
{
  writeUrls(); // Това, в случай, че са направени промени и не е избрана друга книга (за да извика този метод) и не е натиснат бутон Save.
  if (isModified || isRenamed)
  {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->SaveChangesQuestion_v1,
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                               QMessageBox::Save);
    if (ret == QMessageBox::Save)
    {
      saveXML();
    }
    else if (ret == QMessageBox::Cancel)
    {
      event->ignore();
      return;
    }
  }

  enableDownload = false;
  if (downloadTimer != 0)
  {
    downloadTimer->stop();
    delete downloadTimer;
    downloadTimer = 0;
  }

  if (isSaved) emit modified(currentFileName);

  if (DM != 0)
  {
    DM->abort(); // Това ще прекрати моментално свалянето на текущия файл (ако се сваля в момента) и би трябвало да не го записва частично свален (но не съм сигурен за последното).
    delete DM;
  }
  event->accept();
}

bool AudioLocationFileEditor::loadXML()
{
  QString filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(currentFileName);

  if (QFile::exists(filePath))
  {
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QXmlStreamReader xml(file);
    QString currentTag;
    QString chapter;
    QString urlPath;
    QString localPath;
    while (!xml.atEnd() && !xml.hasError())
    {
      xml.readNext();
      currentTag = xml.name().toString(); // xml.name() връща само името (например "title"), а xml.qualifiedName() връща неймспейса+името (например "media:title").

      if (xml.isStartElement())
      {
        if (currentTag.compare("AudioLocationFile", Qt::CaseInsensitive) == 0)
        {
          if ( xml.attributes().value("", "structureVersion").toString().trimmed() != "1" ) return false; // Ако версията на файла е различна.
          leShortDescription->setText( xml.attributes().value("", "shortDescription").toString().trimmed() );
          connect(leShortDescription, SIGNAL(textChanged(const QString &)), this, SLOT(slotShortDescriptionChanged(const QString &)));
          targetDownloadDir = QDir::fromNativeSeparators( xml.attributes().value("", "targetDownloadDir").toString().trimmed() );
          leTargetDir->setText(targetDownloadDir);
        }
        else if (currentTag.compare("Location", Qt::CaseInsensitive) == 0)
        {
          chapter = xml.attributes().value("", "chapter").toString().trimmed();
          urlPath = xml.attributes().value("", "urlPath").toString().trimmed();
          localPath = xml.attributes().value("", "localPath").toString().trimmed();

          if (!chapter.isEmpty())
          {
            if (!urlPath.isEmpty()) urlPathMap.insert(chapter, urlPath);
            if (!localPath.isEmpty()) localPathMap.insert(chapter, localPath);
          }
        }
      }
    }

    file->close();
    delete file;
  }
  return true;
}

bool AudioLocationFileEditor::saveXML()
{
  // Структурата на AudioLocation XML файла е следната:
  //
  // Празен:
  //
  // <?xml version="1.0"?>
  // <AudioLocationFile structureVersion="1" shortDescription="" targetDownloadDir="">
  //   <Location chapter="Genesis_1" urlPath="" localPath="" />
  //   <Location chapter="Genesis_2" urlPath="" localPath="" />
  //   <Location chapter="Genesis_3" urlPath="" localPath="" />
  //   ...
  //   <Location chapter="Revelation_21" urlPath="" localPath="" />
  //   <Location chapter="Revelation_22" urlPath="" localPath="" />
  // </AudioLocationFile>
  //
  // Примерен:
  //
  // <?xml version="1.0"?>
  // <AudioLocationFile structureVersion="1" shortDescription="Audio AKJV" targetDownloadDir="">
  //   <Location chapter="Genesis_1" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_01.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_01.mp3" />
  //   <Location chapter="Genesis_2" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_02.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_02.mp3" />
  //   <Location chapter="Genesis_3" urlPath="http://audiobible.net/AKJV/Genesis/Genesis_03.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Genesis/Genesis_03.mp3" />
  //   ...
  //   <Location chapter="Revelation_21" urlPath="http://audiobible.net/AKJV/Revelation/Revelation_21.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Revelation/Revelation_21.mp3" />
  //   <Location chapter="Revelation_22" urlPath="http://audiobible.net/AKJV/Revelation/Revelation_22.mp3" localPath="D:/MatCrossBible/AudioBible/AKJV/Revelation/Revelation_22.mp3" />
  // </AudioLocationFile>

  QString shortDescription = leShortDescription->text().trimmed();

  QString num = "";
  QString chapter = "";
  QString text = "<?xml version=\"1.0\"?>\n";
  text += QString("<AudioLocationFile structureVersion=\"1\" shortDescription=\"%1\" targetDownloadDir=\"%2\">\n").arg(shortDescription).arg(targetDownloadDir);
  for (int i = 0; i < 77; i++)
  {
    for (int c = 1; c <= MW->MO->chaptersCountArr[i]; c++)
    {
      num = (c < 10) ? QString("0%1").arg(c) : QString("%1").arg(c);
      chapter = QString("%1_%2").arg(MW->MO->bookFileNameArr[i]).arg(num);
      text += QString("	<Location chapter=\"%1\" urlPath=\"%2\" localPath=\"%3\" />\n").arg(chapter).arg(urlPathMap.value(chapter, "")).arg(localPathMap.value(chapter, ""));
    }
  }
  text += "</AudioLocationFile>\n";

  QDir dir; // Създава (ако не съществуват) директория Audio.
  dir.mkpath(QString("%1/Audio").arg(MW->MO->applicationDirPath));

  // Определя името на файла.
  QString filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(currentFileName); // Ако файлът не е преименуван, това ще бъде името му.
  if (isRenamed) // Ако е бил преименуван.
  {
    // Тук се прави повторно генериране на името на файла за да е сигурно, че не се е появил същият файл от друг отворен редактор.
    QString newFileName = "";
    QString newFilePath = "";
    if (getFreeFileName(newFileName, newFilePath))
    {
      if (QFile::rename(filePath, newFilePath)) // Ако преименува файла реално.
      {
        currentFileName = newFileName;
        lblFileName->setText(currentFileName);
        filePath = newFilePath;
      }
      else // Ако поради някаква причина не може да преименува файла реално.
      {
        lblFileName->setText(currentFileName); // Връща старото име в етикета.
        isRenamed = false;
      }
    }
  }

  QFile *alf = new QFile(filePath);
  if (alf->open(QIODevice::WriteOnly | QIODevice::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text, записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(alf);
    out << text;
    alf->close();
    delete alf;

    if (isRenamed)
    {
      emit modified(currentFileName); // Това по принцип се излъчва само при затваряне на формата и то само при модифициран и записан документ. Но ако документът е преименуван се излъчва и тук, сега - при сейв, за да предизвика незабавно презареждане на комбобокса.
      isSaved = false; // Това е защото е излъчен сигнал, че документът е бил променен.
    }		
    else
    {
      isSaved = true;
    }		
    isModified = false;
    isRenamed = false;
    return true;
  }
  else
  {
    delete alf;
    return false;
  }
}

void AudioLocationFileEditor::loadUrls()
{
  for (int i = 0; i < tablePaths->rowCount(); i++)
  {
    tablePaths->removeRow(0);
  }
  tablePaths->setRowCount(0);

  for (int i = 0; i < (MW->MO->chaptersCountArr[currentBook]); i++)
  {
    tablePaths->insertRow(i);

    //tablePaths->setItem(i, 0, new QTableWidgetItem("")); // Тези не са нужни защото за всяка клетка от таблицата се използва съответния обект, но заради правилната работа на таблицата,
    //tablePaths->setItem(i, 1, new QTableWidgetItem("")); // от гледна точка на селектиране на текущата клетка, е необходимо подобно инициализиране за всяка клетка.

    QLineEdit *le1 = new QLineEdit( getUrlPath(currentBook+1, i+1) );
    le1->setFrame(false);
    QLineEdit *le2 = new QLineEdit( getLocalPath(currentBook+1, i+1) );
    le2->setFrame(false);

    tablePaths->setCellWidget(i, 0, le1);
    tablePaths->setCellWidget(i, 1, le2);
  }
}

void AudioLocationFileEditor::writeUrls()
{
  if (tablePaths->rowCount() == 0) return; // Обикновено при първо пускане на редактора.
  
  QString urlPath;
  QString localPath;
  for (int i = 0; i < (MW->MO->chaptersCountArr[currentBook]); i++)
  {
    urlPath = ((QLineEdit*)tablePaths->cellWidget(i, 0))->text().trimmed();
    localPath = ((QLineEdit*)tablePaths->cellWidget(i, 1))->text().trimmed();
    localPath = QDir::fromNativeSeparators(localPath);

    if (getUrlPath(currentBook+1, i+1) != urlPath) isModified = true;
    if (getLocalPath(currentBook+1, i+1) != localPath) isModified = true;

    setUrlPath(currentBook+1, i+1, urlPath);
    setLocalPath(currentBook+1, i+1, localPath);
  }
}

QString AudioLocationFileEditor::getLocalPath(const quint8 book, const quint8 chapter)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  QString path = localPathMap.value(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), ""); // Връща празен стринг, ако няма път.
  return path;
}

void AudioLocationFileEditor::setLocalPath(const quint8 book, const quint8 chapter, QString localPath)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  localPathMap.insert(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), localPath);
}

QString AudioLocationFileEditor::getUrlPath(const quint8 book, const quint8 chapter)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  QString path = urlPathMap.value(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), ""); // Връща празен стринг, ако няма път.
  return path;
}

void AudioLocationFileEditor::setUrlPath(const quint8 book, const quint8 chapter, QString urlPath)
{
  QString num = (chapter < 10) ? QString("0%1").arg(chapter) : QString("%1").arg(chapter);
  urlPathMap.insert(QString("%1_%2").arg(MW->MO->bookFileNameArr[book-1]).arg(num), urlPath);
}

bool AudioLocationFileEditor::getFreeFileName(QString &newFileName, QString &newFilePath)
{
  QString num = "";
  QString simpShortDescription = leShortDescription->text().simplified().remove(" "); // Премахва всякакви специални знаци и интервали от написаното име.
  for (quint16 n = 0; n <= 500; n++) // Ако не се открие свободно име или има проблем с преименуването, името си остава старото.
  {
    num = ((n == 0) ? "" : QString("_%1").arg(n));
    newFileName = QString("AudioLocation_%1%2.alf").arg(simpShortDescription).arg(num);
    newFilePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(newFileName);

    if (newFileName == currentFileName) // Ако е изписано текущото име.
    {
      return false;
    }
    if (!QFile::exists(newFilePath)) // Ако няма файл с такова име.
    {
      return true;
    }
  }
  return false;
}

QString AudioLocationFileEditor::getUrlFileName(const QString url)
{
  return QFileInfo(url).fileName(); // Съдържа само името на файла или празен стринг, ако няма ясно обособено име.
}

QString AudioLocationFileEditor::getUrlFileSuffix(const QString url)
{
  return QFileInfo(url).suffix(); // Съдържа само разширението на файла или празен стринг, ако няма ясно обособено разширение.
}

void AudioLocationFileEditor::enableEditFile(bool enable)
{
  // Този метод ще се извиква от бутоните за старт и стоп на свалянето.
  leShortDescription->setEnabled(enable);
  leTargetDir->setEnabled(enable);
  btnTargetDirChoice->setEnabled(enable);
  //chBoxAutoFillLocalPath->setEnabled(enable);
  btnDownload->setEnabled(enable);
  btnStop->setEnabled(!enable); // Забранен, когато другите са разрешени.
  btnDelete->setEnabled(enable);
  btnSave->setEnabled(enable);
  lwBooks->setEnabled(enable);
  tablePaths->setEnabled(enable);
  if (enable)
  {
    prgBarChapter->setMinimum(0);
    prgBarChapter->setMaximum(100);
    prgBarChapter->setValue(0);
    prgBarAll->setMinimum(0);
    prgBarAll->setMaximum(100);
    prgBarAll->setValue(0);
  }
}

void AudioLocationFileEditor::slotShortDescriptionChanged(const QString &/*text*/)
{
  // Името на файла се променя само при писане в полето leShortDescription!!!
  QString newFileName = "";
  QString newFilePath = "";
  if (getFreeFileName(newFileName, newFilePath))
  {
    // Истинското преименуване няма да става тук, а в момента на запис.
    // По време на запис се прави повторно генериране на името на файла за да е сигурно, че не се е появил същият файл от друг отворен редактор.
    lblFileName->setText(newFileName);
    isRenamed = true; // Това ще предизвика излъчване на сигнал при записване (заради промененото име).
  }
  else // Ако поради някаква причина не може да преименува файла реално или е изписано текущото име.
  {
    lblFileName->setText(currentFileName);
    isRenamed = false;
  }
}

void AudioLocationFileEditor::slotBookChanged(int currentRow)
{
  writeUrls(); // Записва текущите редове.
  currentBook = currentRow;
  loadUrls(); // Зарежда новите в таблицата.
}

void AudioLocationFileEditor::slotTargetDirChoice()
{
  QString oldPath = QDir::fromNativeSeparators(leTargetDir->text().trimmed());
  QString newPath = QFileDialog::getExistingDirectory(this, QString("Open Directory"), oldPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!newPath.isEmpty() && newPath != oldPath)
  {
    leTargetDir->setText(newPath);
    targetDownloadDir = newPath;
    isModified = true;
  }
}

void AudioLocationFileEditor::slotStartDownload()
{
  bool error;

  // Проверява директорията и ако не съществува извежда съобщение:
  QString path = QDir::fromNativeSeparators(leTargetDir->text().trimmed());
  if (path.right(1) == "/") path.remove(path.length()-1, 1); // Премахва последната наклонена черта, ако има такава.
  QDir targetDir(path);
  if (path.isEmpty() || !targetDir.exists())
  {
    teLog->append("<font color=#ff0000><b>" + MW->MO->TS->TargetDirNotExist_v1 + "</b></font>");
    QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->TargetDirNotExist_v1);
    return;
  }

  // Прави опит за създаване на поддиректориите. Ако има проблем ще изведе съобщение:
  for (int i = 0; i < 77; i++)
  {
    if ( !targetDir.mkpath(QString("%1/%2").arg(path).arg(MW->MO->bookFileNameArr[i])) ) // mkdir създава директория в текущата, но връща false, ако тя вече съществува, а mkpath създава директория по абсолютен път и връща true ако вече съществува.
    {
      teLog->append("<font color=#ff0000><b>" + MW->MO->TS->MakeDirProblem_v1 + "</b></font>");
      QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->MakeDirProblem_v1);
      return;
    }
  }

  // Вдига флага за промяна на файла, ако директорията за изтегляне е различна от заредената от XML-а:
  if (targetDownloadDir != path)
  {
    targetDownloadDir = path;
    isModified = true;
  }

  // Показва Битие:
  lwBooks->setCurrentRow(0); // Това е важно, защото в края на изтеглянето ще се заредят редовете на таблицата с Битие.

  // Проверява дали има списък с URL-и и ако няма извежда съобщение:
  error = true;
  QMapIterator<QString, QString> iterator1(urlPathMap);
  while (iterator1.hasNext())
  {
    iterator1.next();
    if (!iterator1.value().isEmpty()) // Ако има поне един URL запис (дори и невалиден).
    {
      error = false;
      break;
    }
  }
  if (error)
  {
    teLog->append("<font color=#ff0000><b>" + MW->MO->TS->NoUrlPaths_v1 + "</b></font>");
    QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->NoUrlPaths_v1);
    return;
  }

  // Генерира списъците с url-ите за сваляне и имената на файловете, в които ще се запишат:
  allDownloadUrlPathKeys.clear();
  allDownloadLocalPaths.clear();
  currentDownloadChapter = -1;
  QString currentUrl = "";
  QString currentLocal = "";
  QString currentFileName = ""; // Името на файла, който ще се сваля. В случая не е важно името, а дали Url-a съдържа валидно име.
  QString currentFileSuffix = ""; // Разширение на това име. Това вече е важно, защото се използва същото за запис на файла на диска.
  QString num = "";
  QString chapter = "";
  error = true;
  for (int i = 0; i < 77; i++)
  {
    for (int c = 1; c <= MW->MO->chaptersCountArr[i]; c++)
    {
      num = (c < 10) ? QString("0%1").arg(c) : QString("%1").arg(c);
      chapter = QString("%1_%2").arg(MW->MO->bookFileNameArr[i]).arg(num); // Създава ключа, който се явява и името на файла, в който ще се записва.
      
      currentUrl = urlPathMap.value(chapter, ""); // Ще върне Url-a, ако има такъв или празен стринг.
      currentFileName = getUrlFileName(currentUrl); // Ще върне името на файла, ако има такъв или празен стринг.
      currentFileSuffix = getUrlFileSuffix(currentUrl).toLower(); // Ще върне разширението на файла, ако има такъв или празен стринг.
      if (!currentUrl.isEmpty() && !currentFileName.isEmpty() && !currentFileSuffix.isEmpty()) // Ако има Url за тази глава и Url-a съдържа валидно име на файл (с ясно разширение).
      {
        error = false; // Има поне едно валидно име на файл. В следващата проверка може да се укаже, че е вече свален и да не влезе в списъка, но това не променя факта, че има поне едно валидно име на файл (няма да изведе съобщение за грешка).
        currentLocal = QString("%1/%2/%3.%4").arg(targetDownloadDir).arg(MW->MO->bookFileNameArr[i]).arg(chapter).arg(currentFileSuffix); // Съдържа името на файла, в който ще се записва + пътя.
        if (!QFile::exists(currentLocal)) // Ако файлът несъществува (все ище не е изтеглен).
        {
          allDownloadUrlPathKeys << chapter;
          allDownloadLocalPaths << currentLocal;
        }
        else // Ако вече е изтеглен.
        {
          if (chBoxAutoFillLocalPath->isChecked() && localPathMap.value(chapter, "") != currentLocal)
          {
            localPathMap.insert(chapter, currentLocal);
            isModified = true;
          }
        }
      }
    }
  }
  loadUrls(); // Зарежда новите локали в таблицата (която показва Битие). Това в случай, че има записани редове в горния цикъл.

  // Проверява дали в списъка с URL-и има валидно изписани файлове и ако няма ще изведе съобщение:
  if (error)
  {
    teLog->append("<font color=#ff0000><b>" + MW->MO->TS->NoFileNames_v1 + "</b></font>");
    QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->NoFileNames_v1);
    return;
  }

  // Проверява дали в списъка с URL-и има нещо за сваляне:
  if (allDownloadUrlPathKeys.isEmpty())
  {
    teLog->append("<font color=#0080ff><b>" + MW->MO->TS->DownloadedFileCount_v1 + "</b></font>");
    teLog->append("<font color=#0080ff><b>0</b></font>");
    teLog->append("<font color=#008000><b>" + MW->MO->TS->DownloadDone_v1 + "</b></font>");
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->DownloadDone_v1);
    return;
  }

  // Прави бутона старт и другите контроли пасивни:
  enableEditFile(false);

  // Започва свалянето:
  prgBarAll->setMaximum(allDownloadUrlPathKeys.count());
  enableDownload = true;
  downloadTimer->start();
}

void AudioLocationFileEditor::slotStopDownload()
{
  enableDownload = false; // Това не спира свалянето на текущия файл, а само указва, че свалянето не трябва да продължи след сваляне на текущия файл.
  btnStop->setEnabled(false); // Другите бутони няма да станат активни сега, а когато приключи текущото сваляне.
}

void AudioLocationFileEditor::slotDownloadTimer()
{
  if (!currentDownloadDone) return; // Ако текущия файл още не е свален.

  currentDownloadChapter++;
  if (enableDownload && currentDownloadChapter < allDownloadUrlPathKeys.count())
  {
    currentDownloadDone = false;
    teLog->append("<font color=#000000>" + allDownloadLocalPaths[currentDownloadChapter] + "</font>");
    bool res = DM->downloadToFile(urlPathMap.value(allDownloadUrlPathKeys[currentDownloadChapter], ""), "", allDownloadLocalPaths[currentDownloadChapter], false);
    if (!res) // Това не би трябвало да се случва, но за всеки случай.
    {
      teLog->append("<font color=#ff0000><b>Download failure!</b></font>");
      teLog->append("<font color=#ff0000><b>Error:</b> unknown</font>");
      currentDownloadDone = true;
    }
  }
  else
  {
    if (downloadTimer != 0) downloadTimer->stop(); // Спира се сам (ако преди това не е убит в closeEvent).

    // Статистика:
    teLog->append(" ");
    teLog->append("<font color=#0080ff><b>" + MW->MO->TS->DownloadedFileCount_v1 + "</b></font>");
    teLog->append("<font color=#0080ff><b>" + QString("%1").arg(currentDownloadChapter) + "</b></font>");
    teLog->append("<font color=#008000><b>" + MW->MO->TS->DownloadDone_v1 + "</b></font>");
    QMessageBox::information(this, QCoreApplication::applicationName(), MW->MO->TS->DownloadDone_v1);

    // Изтрива списъците за да не заемат памет:
    allDownloadUrlPathKeys.clear();
    allDownloadLocalPaths.clear();
    currentDownloadChapter = -1;

    // Прави бутон старт и другите контроли активни:
    enableEditFile(true);
    loadUrls(); // Зарежда новите локали в таблицата (която показва Битие).
  }
}

void AudioLocationFileEditor::slotDownloadFinished(QString /*url*/, QString /*filePath*/, bool error, QString errorString)
{
  if (error)
  {
    teLog->append("<font color=#ff0000><b>Download failure!</b></font>");
    teLog->append("<font color=#ff0000><b>Error:</b> " + errorString + "</font>");
  }
  else
  {
    teLog->append("<font color=#000000><b>Download done.</b></font>");

    // Записва адреса на новоизтегления файл в таблицата и вдига флага за промяна на файла.
    if (chBoxAutoFillLocalPath->isChecked())
    {
      QString key = allDownloadUrlPathKeys[currentDownloadChapter];
      QString path = allDownloadLocalPaths[currentDownloadChapter];
      if (localPathMap.value(key, "") != path)
      {
        localPathMap.insert(key, path);
        isModified = true;
      }
    }
  }

  prgBarAll->setValue(currentDownloadChapter+1);
  currentDownloadDone = true;
}

void AudioLocationFileEditor::slotDelete()
{
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->DeleteALFQuestion_v1, QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
  if (ret == QMessageBox::Ok)
  {
    writeUrls(); // Това, в случай, че са направени промени да ги запише сега, а не след изтриване на файла.

    QString filePath = QString("%1/Audio/%2").arg(MW->MO->applicationDirPath).arg(currentFileName);
    QFile::remove(filePath);

    emit modified("");  // Това за да се обнови комбобоксът.
    isSaved = false;    // Тези за да се затвори формата без запис.
    isModified = false; //
    isRenamed = false;  //
    close();
  }
}

void AudioLocationFileEditor::slotShowDownloadPanel(bool checked)
{
  if (downloadTimer == 0)
  {
    downloadTimer = new QTimer(this);
    downloadTimer->setInterval(100);
    connect(downloadTimer, SIGNAL(timeout()), this, SLOT(slotDownloadTimer()));
  }

  if (DM == 0)
  {
    QNetworkProxy proxy;
    if (MW->MO->SVars.proxyType == PROXY__NO_PROXY)
      proxy.setType(QNetworkProxy::NoProxy);
    else if (MW->MO->SVars.proxyType == PROXY__HTTP_PROXY)
      proxy.setType(QNetworkProxy::HttpProxy);
    else if (MW->MO->SVars.proxyType == PROXY__SOCKS_5_PROXY)
      proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName(MW->MO->SVars.proxyHostName);
    proxy.setPort(MW->MO->SVars.proxyPort);

    DM = new HttpDownloadManager(proxy, prgBarChapter);
    connect(DM, SIGNAL(downloadFinished(QString, QString, bool, QString)), this, SLOT(slotDownloadFinished(QString, QString, bool, QString)));
  }

  grBoxDownload->setVisible(checked);
}

void AudioLocationFileEditor::slotSave()
{
  writeUrls();
  if (isModified || isRenamed) saveXML();
}
