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

#ifndef TRSTRINGS_H
#define TRSTRINGS_H

#include <QCoreApplication>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QLocale>
#include <QDate>

// Този клас съдържа всички стрингове, за цялото приложение, на избрания език.
class TrStrings : public QObject
{
  Q_OBJECT

private:
  QString trPath; // Път до директорията с преводите на интерфейса.
  QSettings *strSettings;

  void setBooksStr(); // За имената на книгите в различните варианти (пълно, късо, съкратено).
  void setStr(QString &str, QString key, QString trBg, QString trEn); // За всички останали стрингове.
  void initializeStrings();
  void createNewReadMeFile();
  // За вградените езици на книгите:
  void initBooksBulgarian();
  void initBooksCzech();
  void initBooksEnglish();
  void initBooksFrench();
  void initBooksGerman();
  void initBooksHungarian();
  void initBooksItalian();
  void initBooksPolish();
  void initBooksRomanian();
  void initBooksRussian();
  void initBooksSpanish();

public:
  Qt::LayoutDirection globalLayoutDirection;  // LayoutDirection на цялото приложение (ляво или дясно).
  QString currentAppTranslation;   // Име на файла (без разширението) на текущия превод.
  QStringList allAppTranslation;   // Списък с имената (без разширението) на всички файлове с преводи, които са открити в папката (ще се използва в комбобокса за избор на език).
  QStringList allBooksTranslation; // Списък с всички вградени езици, на които са преведени имената на книгите.
  bool isBulgarianAppTranslation;  // Флаг указващ дали текущият език е Български. Ще се използва на различни места в програмата за предоставяне на възможности само за българските потребители.

  TrStrings();
  void initEmbedBooksNames(QString language); // Инициализира имената на книгите с вградените езици.
  void setAllAppTranslation(); // Инициализира allAppTranslation списъка. Този метод се извиква и от Settings формата, след сваляне на нов TR файл.
  void saveCurrentAppTranslationToSettings(); // Този метод се извиква от настройките при смяна на езика.

  // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

  // BookNames:
  QString bookNameArr[77];
  QString bookShortNameArr[77];
  QString bookMinNameArr[77];
  QString bookFileNameArr[77];

  // Common:
  QString Yes_v1;
  QString No_v1;
  QString OK_v1;
  QString Cancel_v1;
  QString Close_v1;
  QString CloseWindow_v1;
  QString MaximizeNormalize_v1;
  QString HideToolBar_v1;
  QString DisabledDeuterocanonicalInfo_v1;
  QString Book_v1;
  QString Chapter_v1;

  // TMenu:
  QString NewDockWindow_v1;
  QString Books_v1;
  QString Bookmarks_v1;
  QString BookShort_v1;
  QString ChapterShort_v1;
  QString VerseShort_v1;
  QString DailyReadGroup_v1;
  QString DailyReadChapterInGroup_v1;
  QString GoBack_v1;
  QString GoForward_v1;
  QString PreviousBook_v1;
  QString NextBook_v1;
  QString NextPreviousBook_v1;
  QString PreviousChapter_v1;
  QString NextChapter_v1;
  QString NextPreviousChapter_v1;
  QString PreviousVerse_v1;
  QString NextVerse_v1;
  QString NextPreviousVerse_v1;
  QString PreviousChaptersDailyRead_v1;
  QString NextChaptersDailyRead_v1;
  QString PreviousChapterDailyRead_v1;
  QString NextChapterDailyRead_v1;
  QString DailyRead_v1;
  QString SearchInBible_v1;
  QString BibleTexts_v1;
  QString Audio_v1;
  QString ZoomInText_v1;
  QString ZoomOutText_v1;
  QString RestoreDefaultZoom_v1;
  QString SelectAll_v1;
  QString Copy_v1;
  QString Search_v1;
  QString SearchInTheTextPanel_v1;
  QString SearchInTheText_v1;
  QString FindPrevious_v1;
  QString FindNext_v1;
  QString CaseSensitive_v1;
  QString WholeWords_v1;
  QString StatisticsMenu_v1;
  QString CompareTwoTexts_v1;
  QString UniqueWordsInBible_v1;
  QString UniqueWordsInOT_v1;
  QString UniqueWordsInNT_v1;
  QString UniqueWordsInBook_v1;
  QString UniqueWordsInChapter_v1;
  QString Pad_v1;
  QString DictionaryCommentary_v1;
  QString ExternalImages_v1;
  QString Projector_v1;
  QString Links_v1;
  QString Settings_v1;
  QString Help_v1;
  QString About_v1;
  QString CheckNewAppVersion_v1;
  QString FileMenu_v1;
  QString ExportToText_v1;
  QString ExportToHTML_v1;
  QString ExportToPDF_v1;
  QString PrintPreview_v1;
  QString Print_v1;
  QString Session_v1;
  QString CloseDockWindow_v1;
  QString Exit_v1;

  // BibleTextsToolBar
  QString RearrangeBibletexts_v1;
  QString Info_v1;
  QString BibleTextsInfo_v1;
  QString More_v1;
  QString DownloadMoreBibleTexts_v1;
  QString MoreBibleTexts_v1;
  QString Convert_v1;
  QString ConvertBibleTexts_v1;
  QString ConvertCrossBgBibleFile_v1;
  QString ConvertTheWordFile_v1;
  QString ChooseFile_v1;
  QString ConvertFileToUTF8First_v1;
  QString AddNumbersToVerses_v1;
  QString UnknownFileFormat_v1;
  QString ConversionSuccessful_v1;

  // AudioToolBar
  QString NoAudioForThisChapter_v1;
  QString NoAudioForThisBook_v1;
  QString PlayChapter_v1;
  QString PlayChapterTT_v1;
  QString PlayBook_v1;
  QString PlayBookTT_v1;
  QString PlayGroup_v1;
  QString PlayGroupTT_v1;
  QString Stop_v1;
  QString Pause_v1;
  QString Repeat_v1;
  QString Seek_v1;
  QString Rate_v1;
  QString Volume_v1;
  QString Synchronize_v1;
  QString CurrentChapter_v1;
  QString AllChapters_v1;
  QString TargetAudioText_v1;
  QString IncorrectAudioLocationFile_v1;
  QString EditALF_v1;
  QString EditALFTT_v1;
  QString NewALF_v1;
  QString NewALFTT_v1;
  QString DeleteALF_v1;
  QString DeleteALFTT_v1;
  QString DeleteALFQuestion_v1;
  QString DownloadAudioBible_v1;
  QString DownloadAudioBibleTT_v1;
  QString TargetDirChoose_v1;
  QString AutoFillLocalPath_v1;
  QString TargetDirNotExist_v1;
  QString MakeDirProblem_v1;
  QString NoUrlPaths_v1;
  QString NoFileNames_v1;
  QString DownloadedFileCount_v1;
  QString ALFEditor_v1;
  QString ALFShortDescription_v1;
  QString ALFFileName_v1;

  // Session
  QString StandardSession_v1;
  QString SaveSession_v1;
  QString LoadSession_v1;
  QString CurrentSession_v1;

  // BookmarksWidget
  QString AddBookmark_v1;
  QString ShowBookmark_v1;
  QString DeleteBookmark_v1;
  QString DeleteBookmarkQuestion_v1;

  // ProjectorToolBar
  QString HideText_v1;
  QString LockScreen_v1;
  QString HideTheName_v1;
  QString TextColor_v1;
  QString CustomFont_v1;
  QString EnableCustomFont_v1;
  QString Left_v1;
  QString Center_v1;
  QString Right_v1;
  QString Top_v1;
  QString Bottom_v1;
  QString TextOutlineShadow_v1;
  QString OutlineShadowColor_v1;
  QString LeftTitleBar_v1;
  QString TopTitleBar_v1;
  QString RightTitleBar_v1;
  QString BottomTitleBar_v1;
  QString SemiTransparentTitleBar_v1;
  QString TransparentTitleBar_v1;
  QString PicFit_v1;
  QString PicFitEx_v1;
  QString PicStretch_v1;
  QString PicCenter_v1;
  QString EmbededPicture_v1;
  QString ExternalPicture_v1;
  QString Brightness_v1;
  QString Color_v1;
  QString SaveAsPic_v1;

  // SearchToolBar
  QString SearchInBibleTargetText_v1;
  QString ShowHideOptions_v1;
  QString OptSearchRandom_v1;
  QString OptSearchRandomTT_v1;
  QString OptSearchRoot_v1;
  QString OptSearchRootTT_v1;
  QString OptSearchWord_v1;
  QString OptSearchWordTT_v1;
  QString OptSearchAll_v1;
  QString OptSearchAllTT_v1;
  QString OptSearchAny_v1;
  QString OptSearchAnyTT_v1;
  QString OptSearchPhrase_v1;
  QString OptSearchPhraseTT_v1;
  QString OptSearchWildCard_v1;
  QString OptSearchWildCardTT_v1;
  QString OptSearchCaseSensitive_v1;
  QString OptSearchCaseInsensitive_v1;
  QString OptSearchCaseSensitivityTT_v1;
  QString OptSearchInChapter_v1;
  QString OptSearchInChapterTT_v1;
  QString VersesContainAllSearchedWords_v1;
  QString VersesContainAnySearchedWord_v1;
  QString VersesContainSearchedPhrase_v1;
  QString ChaptersContainAllSearchedWords_v1;
  QString ChaptersContainAnySearchedWord_v1;
  QString ChaptersContainSearchedPhrase_v1;
  QString TotalOf_v1;
  QString Total_v1;
  QString InTheFoundVerses_v1;
  QString InTheFoundChapters_v1;
  QString AllBooks_v1;
  QString TheOldTestament_v1;
  QString TheNewTestament_v1;
  QString OT_v1;
  QString NT_v1;
  QString Filter_v1;
  QString Results_v1;
  QString TooManyMatches_v1;
  QString UseFilter_v1;
  QString NoMatchesVerses_v1;
  QString NoMatchesChapters_v1;
  QString ChangeSearchOptions_v1;
  QString SearchError_v1;
  QString Map_v1;
  QString Deuterocanonical_v1;
  QString SearchMethodInfo1_v1;
  QString SearchMethodInfo2_v1;
  QString SearchMethodInfo31_v1;
  QString SearchMethodInfo32_v1;
  QString SearchMethodInfo33_v1;
  QString SearchMethodInfo41_v1;
  QString SearchMethodInfo42_v1;
  QString SearchMethodInfo51_v1;
  QString SearchMethodInfo52_v1;
  QString SearchMethodInfo61_v1;
  QString SearchMethodInfo62_v1;
  QString SearchMethodInfo71_v1;
  QString SearchMethodInfo72_v1;
  QString SearchMethodInfo81_v1;
  QString SearchMethodInfo82_v1;
  QString SearchMethodInfo9_v1;
  QString SearchMethodInfo10_v1;

  // Statistics
  QString TwoActiveBibleTextsNeeded_v1;
  QString OneActiveBibleTextNeeded_v1;
  QString Statistics_v1;
  QString MatchedWords_v1;
  QString AllWords_v1;
  QString PercentageMatch_v1;
  QString UniqueWordsOnly_v1;
  QString HapaxLegomenon_v1;
  QString SortByOccurrenceOrder_v1;
  QString SortByAlphabeticalOrder_v1;

  // ExTextWindow
  QString Save_v1;
  QString SaveChangesQuestion_v1;

  // FastAccessWidget
  QString FastAccess_v1;
  QString ValidExpression_v1;

  // HttpAccess
  QString Connecting_v1;
  QString ConnectingError_v1;
  QString Error_v1;
  QString OnlineMessages_v1;
  QString NoMessages_v1;
  QString InaccessibleInfo_v1;
  QString InaccessibleInfoFileError_v1;
  QString CheckNewAppVersionOnWEB_v1;
  QString CurrentVersion_v1;
  QString LastReleaseVersion_v1;
  QString HasNewReleaseVersion_v1;
  QString NoNewReleaseVersion_v1;
  QString DownloadNewAppVerFromWEB_v1;
  QString Download_v1;
  QString DownloadStop_v1;
  QString DownloadDone_v1;
  QString DownloadDoneNeedToResraer_v1;
  QString DownloadFailure_v1;
  QString FileDataError_v1;
  QString DownloadTextInfo1_v1;
  QString DownloadTextInfo2_v1;
  QString DownloadTextInfo3_v1;
  QString Language_v1;
  QString Text_v1;
  QString ShortDescription_v1;
  QString File_v1;
  QString Note_v1;
  QString Available_v1;
  QString ExpectRightToUse_v1;
  QString DownloadFailureInvalidLink_v1;
  QString AlternativeDownload_v1;
  QString GetMoreBibleTextsInfo1_v1;
  QString GetMoreBibleTextsInfo2_v1;
  QString GetMoreBibleTextsInfo3_v1;
  QString GetMoreBibleTextsInfo4_v1;
  QString GetMoreBibleTextsInfo5_v1;
  QString GetMoreBibleTextsInfo6_v1;
  QString GetMoreBibleTextsInfo7_v1;
  QString GetMoreBibleTextsInfo8_v1;
  QString MoreTRFiles_v1;
  QString DownloadTRFilesInfo1_v1;
  QString DownloadTRFilesInfo2_v1;
  QString Translator_v1;
  QString LastModify_v1;
  QString PartialTranslated_v1;
  QString GetMoreTRFilesInfo1_v1;
  QString GetMoreTRFilesInfo2_v1;
  QString GetMoreTRFilesInfo3_v1;
  QString GetMoreTRFilesInfo4_v1;
  QString GetMoreTRFilesInfo5_v1;

  // WWWResources:
  QString AddLink_v1;
  QString EditDelLink_v1;
  QString URL_v1;
  QString Description_v1;
  QString InsertLinkRow_v1;
  QString DeleteLinkRow_v1;
  QString FileReadError_v1;
  QString Row_v1;
  QString EditLinksInfo1_v1;
  QString EditLinksInfo2_v1;
  QString EditLinksInfo3_v1;
  QString EditLinksInfo4_v1;
  QString EditLinksInfo5_v1;

  // MainWindow:
  QString MainWindow_v1;
  QString CurrentView_v1;
  QString ToolbarPanels_v1;
  QString BibleTextsFileProblem1_v1;
  QString BibleTextsFileProblem2_v1;
  QString BibleTextsFileProblem3_v1;
  QString NoOpenText1_v1;
  QString NoOpenText2_v1;
  QString NoOpenText3_v1;
  QString NoOpenText4_v1;
  QString AboutMatCrossBible1_v1;
  QString AboutMatCrossBible2_v1;
  QString AboutMatCrossBible3_v1;
  QString AboutMatCrossBible4_v1;
  QString Open_v1;
  QString RestartNowQuestion_v1;
  QString TitleBarButtons_v1;

  // TextView:
  QString SearchTextInTheBible_v1;
  QString CustomHighlightAdd_v1;
  QString CustomHighlightDel_v1;
  QString TextNotFound_v1;
  QString MatchesToOccurrences_v1;
  QString ShowTextError_v1;
  QString CreateHTMLMatCrossBibleV1_v1;
  QString CreateHTMLMatCrossBibleV2_v1;
  QString HTMLMatCrossBibleCreatedIn_v1;

  // Dictionary/Commentary:
  QString Back_v1;
  QString Forward_v1;
  QString PreviousGroup_v1;
  QString NextGroup_v1;
  QString CatchCopyEvent_v1;
  QString CatchSelectEvent_v1;
  QString ChooseDictionaryOrCommentary_v1;
  QString DictionariesAndCommentaries_v1;
  QString NoFoundDictsOrComms_v1;
  QString PossibleDifferentVerseNumber_v1;
  QString Version_v1;
  QString Author_v1;
  QString FileName_v1;
  QString AllWordsPhrases_v1;
  QString AllCommentary_v1;
  QString IncorrectHeaderSection_v1;
  QString IncorrectDataSection_v1;
  QString EqualWordsExpressions_v1;

  // Settings:
  QString TabLanguage_v1;
  QString TabColors_v1;
  QString TabView_v1;
  QString TabText_v1;
  QString TabSearch_v1;
  QString TabAudio_v1;
  QString TabMisc_v1;
  QString EffectAfterChange_v1;
  QString EffectAfterRestart_v1;
  QString EffectAfterChangeOrRestart_v1;
  QString GetDefaultSettings_v1;
  QString GetDefaultSettingsQuestion_v1;
  QString PositionTop_v1;
  QString PositionBottom_v1;
  QString PositionLeft_v1;
  QString PositionRight_v1;
  QString WhiteTheme_v1;
  QString GreyTheme_v1;
  QString DarkTheme_v1;

  QString TCDock1TextColorF_v1;
  QString TCDock1TextColorB_v1;
  QString TCDock2TextColorF_v1;
  QString TCDock2TextColorB_v1;
  QString TCDockBGImage_v1;
  QString TCDockBGImageTT_v1;
  QString TCOldTestamentColorF_v1;
  QString TCOldTestamentAlphaFTT_v1;
  QString TCNewTestamentColorF_v1;
  QString TCNewTestamentAlphaFTT_v1;
  QString TCTextInBracketsColorF_v1;
  QString TCJesusWordsColorF_v1;
  QString TCCompareEqColorF_v1;
  QString TCCompareNoEqColorF_v1;
  QString TCAppColorF_v1;
  QString TCAppColorB_v1;
  QString TCShow3DTitleBarTT_v1;
  QString TCInfo_v1;

  QString TVDocks_v1;
  QString TVTMenu_v1;
  QString TVFontSize_v1;
  QString TVTMenuIconSize_v1;
  QString TVTMenuAutoIconColor_v1;
  QString TVBooksToolBar_v1;
  QString TVSearchToolBar_v1;
  QString TVSearchToolBarWidth_v1;
  QString TVProjectorToolBar_v1;
  QString TVProjectorPrevScreenWidth_v1;
  //QString TVGUIStyle_v1;
  //QString TVGUIStyleTT_v1;

  QString TTGlobalFontSize_v1;
  QString TTGlobalFontSizeTT_v1;
  QString TTAntialias_v1;
  QString TTTheHolyTextFont_v1;
  QString TTVerseNumberBold_v1;
  QString TTVerseNumberSup_v1;
  QString TTTheHolyTextFeatures_v1;
  QString TTVerseStruct_v1;
  QString TTNumeration1_v1;
  QString TTNumeration2_v1;
  QString TTNumerationTT_v1;
  QString TTBooksOrder1_v1;
  QString TTBooksOrder2_v1;
  QString TTBooksOrderTT_v1;
  QString TTShowDeuterocanonical_v1;
  QString TTShowAbsVerseNumber_v1;

  QString TSFoundWordsFormat_v1;
  QString TSWordsFormatBold_v1;
  QString TSWordsFormatUnderline_v1;
  QString TSWordsFormatColorF_v1;
  QString TSWordsFormatColorFTT_v1;
  QString TSWordsFormatColor1F_v1;
  QString TSWordsFormatColor2F_v1;
  QString TSWordsFormatColor3F_v1;
  QString TSWordsFormatColor4F_v1;
  QString TSWordsFormatColor5F_v1;
  QString TSWordsFormatColorB_v1;
  QString TSWordsFormatColorBTT_v1;
  QString TSWordsFormatColor1B_v1;
  QString TSWordsFormatColor2B_v1;
  QString TSWordsFormatColor3B_v1;
  QString TSWordsFormatColor4B_v1;
  QString TSWordsFormatColor5B_v1;
  QString TSExtraSelectionColor_v1;
  QString TSExtraSelectionColor1B_v1;
  QString TSExtraSelectionColor2B_v1;

  QString TOOpenTheFolder_v1;
  QString TOChoiceFolder_v1;
  QString TOFirstIniPath_v1;
  QString TOFirstIniPathH1_v1;
  QString TOFirstIniPathH2_v1;
  QString TOFirstIniPathH3_v1;
  QString TOFirstIniPathH4_v1;
  QString TOFirstIniPathL1_v1;
  QString TOFirstIniPathL2_v1;
  QString TOFirstIniPathL3_v1;
  QString TOFirstIniPathL4_v1;
  QString TOIniPath_v1;
  QString TOIniPathHome_v1;
  QString TOIniPathLocal_v1;
  QString TOIniPathOther_v1;
  QString TOOfficialMatCrossBibleWebSite_v1;
  QString TOProxyTypeTT_v1;
  QString TOProxyHostNameTT_v1;
  QString TOProxyPortTT_v1;
  QString TOMinimizeWindowToTray_v1;
  QString TOMinimizeWindowToTrayTT_v1;
  QString TOCreateDctCmtExampleFiles_v1;
  QString TOCreateDctCmtExampleFilesDone_v1;
};
#endif
