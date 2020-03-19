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

#include "extextwindow.h"

ExTextWindow::ExTextWindow(MainWindow *mainWindow, int Width, int Height, bool isPad, QWidget *parent) : QMainWindow(parent)
{
  setMinimumSize(10, 10);
  resize(Width, Height);

  MW = mainWindow;
  this->isPad = isPad;
  if (isPad) MW->padIsOpen = true;

  editor = new QTextBrowser;
  editor->setMinimumSize(30, 10);
  editor->setOpenExternalLinks(true); // За отваряне на линковете.
  editor->setOpenLinks(true);         // За отваряне на линковете. 
  editor->setWordWrapMode(QTextOption::WordWrap);
  editor->setFrameShape(QFrame::NoFrame);
  editor->setUndoRedoEnabled(true);
  if (isPad)
  {
    editor->setAcceptRichText(false);
    editor->setReadOnly(false);
  }
  else
  {
    editor->setAcceptRichText(true);
    editor->setReadOnly(true);
  }
  QPalette pal1;
  pal1.setBrush(QPalette::Window, MW->MO->SVars.dock1TextColorB);
  pal1.setBrush(QPalette::Button, MW->MO->SVars.dock1TextColorB);
  pal1.setBrush(QPalette::Base, MW->MO->SVars.dock1TextColorB);
  pal1.setBrush(QPalette::Text, MW->MO->SVars.dock1TextColorF);
  editor->setPalette(pal1);

  int TMenuIconSize = MW->MO->SVars.TMenuIconSize;

  toolBar = new QToolBar(this);
  toolBar->setContentsMargins(0, 0, 0, 0);
  toolBar->layout()->setMargin(1); // Марджини.
  toolBar->layout()->setSpacing(1); // Разстояние между обектите.
  toolBar->setIconSize(QSize(TMenuIconSize, TMenuIconSize));
  toolBar->setMovable(false);

  QPalette pal2;
  pal2.setBrush(QPalette::Window, MW->MO->SVars.appColorF);
  pal2.setBrush(QPalette::Button, MW->MO->SVars.appColorF);
  //pal2.setBrush(QPalette::Base, MW->MO->SVars.appColorF);
  toolBar->setPalette(pal2);
  toolBar->setAutoFillBackground(true);

  btnSelectAll = new QToolButton(toolBar);
  btnSelectAll->setToolTip(MW->MO->TS->SelectAll_v1);
  btnSelectAll->resize(TMenuIconSize + 8, TMenuIconSize + 8);
  btnSelectAll->setIconSize(QSize(TMenuIconSize, TMenuIconSize));
  btnSelectAll->setIcon( Icons::icon_SelectAll(TMenuIconSize, TMenuIconSize, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) ); // MW->iconColorForms
  connect(btnSelectAll, SIGNAL(clicked()), editor, SLOT(selectAll()));

  btnCopy = new QToolButton(toolBar);
  btnCopy->setToolTip(MW->MO->TS->Copy_v1);
  btnCopy->resize(TMenuIconSize + 8, TMenuIconSize + 8);
  btnCopy->setIconSize(QSize(TMenuIconSize, TMenuIconSize));
  btnCopy->setIcon( Icons::icon_Copy(TMenuIconSize, TMenuIconSize, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) ); // MW->iconColorForms
  connect(btnCopy, SIGNAL(clicked()), editor, SLOT(copy()));

  if (isPad)
  {
    btnSave = new QToolButton(toolBar);
    btnSave->setToolTip(MW->MO->TS->Save_v1);
    btnSave->resize(TMenuIconSize + 8, TMenuIconSize + 8);
    btnSave->setIconSize(QSize(TMenuIconSize, TMenuIconSize));
    btnSave->setIcon( Icons::icon_ExportTxt(TMenuIconSize, TMenuIconSize, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) ); // MW->iconColorForms
    connect(btnSave, SIGNAL(clicked()), this, SLOT(slotSave()));
  }

  btnClose = new QToolButton(toolBar);
  btnClose->setToolTip(MW->MO->TS->CloseWindow_v1);
  btnClose->resize(TMenuIconSize + 8, TMenuIconSize + 8);
  btnClose->setIconSize(QSize(TMenuIconSize, TMenuIconSize));
  btnClose->setIcon( Icons::icon_Close(TMenuIconSize, TMenuIconSize, MW->MO->SVars.appColorB, MW->MO->SVars.appColorB) ); // MW->iconColorForms
  connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
  
  toolBar->addWidget(btnClose);
  toolBar->addWidget(btnSelectAll);
  toolBar->addWidget(btnCopy);
  if (isPad) toolBar->addWidget(btnSave);

  addToolBar(Qt::TopToolBarArea, toolBar);
  setCentralWidget(editor);

  editor->setFocus();

  //connect(editor, SIGNAL(anchorClicked(const QUrl &)), this, SLOT(slotAnchorClicked(const QUrl &)));
}

ExTextWindow::~ExTextWindow()
{
  if (isPad) MW->padIsOpen = false;
  delete toolBar;
  delete editor;
}

void ExTextWindow::openFile(QString fileName, bool acceptRichText)
{
  this->fileName = fileName;
  QFile *file = new QFile(fileName);
  if (file->open(QFile::ReadWrite | QFile::Text)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    if (acceptRichText)    
      editor->setHtml(file->readAll());
    else
      editor->setPlainText(file->readAll());
  }
  file->close();
  delete file;
}

void ExTextWindow::setEditorFont(QFont font)
{
  editor->setFont(font);
}

void ExTextWindow::setEditorAcceptRichTextt(bool acceptRichText)
{
  editor->setAcceptRichText(acceptRichText);
}

void ExTextWindow::setWordWrapMode(bool wordWrap)
{
  editor->setWordWrapMode( (wordWrap) ? QTextOption::WordWrap : QTextOption::NoWrap );
}

void ExTextWindow::setReadOnly(bool readOnly)
{
  editor->setReadOnly(readOnly);
}

void ExTextWindow::setHtmlText(QString text)
{
  editor->setHtml(text);
}

void ExTextWindow::setPlainText(QString text)
{
  editor->setPlainText(text);
}

void ExTextWindow::setSearchPaths(const QStringList &paths)
{
  editor->setSearchPaths(paths);
}

bool ExTextWindow::maybeSave()
{
  if (!isPad) return true; // Ако не е бележник.
  if (!editor->document()->isModified()) return true; // Ако е бележник, но няма промяна в текста.
  QMessageBox::StandardButton ret;
  ret = QMessageBox::warning(this, QCoreApplication::applicationName(), MW->MO->TS->SaveChangesQuestion_v1,
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  if (ret == QMessageBox::Save)
    return fileSave();
  else if (ret == QMessageBox::Cancel)
    return false;
  return true;
}

bool ExTextWindow::fileSave()
{
  if (!isPad) return true; // Ако не е бележник.
  QFile *file = new QFile(fileName);
  if (file->open(QFile::ReadWrite | QFile::Text /*| QIODevice::Truncate*/)) // QIODevice::Text: When writing, the end-of-line terminators are translated to the local encoding, for example '\r\n' for Win32. -- Ако се махне QIODevice::Text записва като терминатор това, което е указано в текста, без да конвертира терминатора.
  {
    QTextStream out(file);
    out << editor->document()->toPlainText();
  }
  file->close();
  delete file;

  editor->document()->setModified(false);
  return true;
}

void ExTextWindow::keyPressEvent(QKeyEvent * event)
{
  QMainWindow::keyPressEvent(event);

  if (event->modifiers() == Qt::ControlModifier) // Ако е натиснат Ctrl.
  {
    if (event->key() == Qt::Key_S)
    {
      fileSave();
    }
  }
}

void ExTextWindow::closeEvent(QCloseEvent *e)
{
  if (maybeSave())
  {
    deleteLater(); // Това ще предизвика извикването на деконструктура, който по принцип не се извиква при натискане на бутона за затваряне на формата, а само при delete.
    e->accept();
  }
  else
  {
    e->ignore();
  }
}

void ExTextWindow::slotSave()
{
  fileSave();
}

//void ExTextWindow::slotAnchorClicked(const QUrl &link)
//{
//}
