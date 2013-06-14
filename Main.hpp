//Einsprungspunkt und Hauptklasse
//Von hier aus wird alles In- und Externe verwaltet

#pragma once

#include <iostream>
#include "gtkmm/main.h"
#include "gtkmm/window.h"
#include "gtkmm/menubar.h"
#include "gtkmm/button.h"
#include "gtkmm/menu.h"
#include "gtkmm/filechooserdialog.h"
#include "gtkmm/image.h"
#include "gdkmm/pixbuf.h"

#include "Functions.hpp"
#include "Err.hpp"
#include "Pic.hpp"

int main (int argc, char *argv[]);

class MainPanel : public Gtk::Window
{
  public:

  MainPanel (std::string Path = "");

  private:

  void Open ();
  void Save ();
  void SaveLoad ();
  void SavePic (bool Autoload);
  //Öffnet Datei-Dialog
  string FileDlg (std::string Caption, Gtk::FileChooserAction);
  //Lädt aktuelles Bild in das Fenster und skaliert es entsprechend der
  //Fenstergröße
  void Load ();
  //Löscht die rohen Bilddaten vom Speicher. Wird nur von Gtk aufgerufen!
  //Das ist nötig, weil die rohen Bilddaten jedes mal an einer anderen
  //Adresse gespeichert werden.
  void Clear (const guint8 *Data);
  //Reinzoomen
  void ZoomIn ();
  //Rauszoomen
  void ZoomOut ();
  //Verändert die Größe der Ansicht
  void Zoom (bool In);

  Gtk::MenuBar  m_MenuBar;
  Gtk::Menu     m_MenuFile;
  Gtk::Menu     m_MenuView;
  Gtk::MenuItem m_ItemFile;
  Gtk::MenuItem m_ItemView;
  Gtk::MenuItem m_ItemOpen;
  Gtk::MenuItem m_ItemSave;
  Gtk::MenuItem m_ItemIn;
  Gtk::MenuItem m_ItemOut;
  Gtk::MenuItem m_ItemSaveLoad;
  Gtk::MenuItem m_ItemQuit;
  Gtk::Image    m_WidgetPic;
  Gtk::VBox     m_MainBox;

  Pic     m_Pic;
};
