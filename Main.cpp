#include "Main.hpp"

int main (int argc, char *argv[])
{
  Gtk::Main Entry (argc, argv);
  std::string Path;
  if (argc > 1) Path = argv[1];
  if (argc > 2)
  {
    try
    {
      Pic Converter;
      Converter.Load (Path);
      Converter.Save (argv[2]);
    }
    catch (Err fErr)
    {
      std::cout<<"Ein Fehler ist aufgetreten: "<<fErr.m_Msg<<std::endl;
    }
    return 0;
  }
  MainPanel Window (Path);
  Gtk::Main::run (Window);
  return 0;
}


//MainPanel
MainPanel::MainPanel (std::string Path) :
  m_ItemFile ("Datei"),
  m_ItemView ("Ansicht"),
  m_ItemOpen ("Öffnen"),
  m_ItemSave ("Speichern"),
  m_ItemSaveLoad ("Speichern und laden"),
  m_ItemQuit ("Beenden"),
  m_ItemIn ("Reinzoomen"),
  m_ItemOut ("Rauszoomen")
{
  set_title ("PicTor");
  set_resizable (false);

  //Datei
  m_MenuFile.append (m_ItemOpen);
  m_MenuFile.append (m_ItemSave);
  m_MenuFile.append (m_ItemSaveLoad);
  m_MenuFile.append (m_ItemQuit);
  m_ItemOpen.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::Open));
  m_ItemSave.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::Save));
  m_ItemSaveLoad.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::SaveLoad));
  m_ItemQuit.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::hide));
  m_ItemFile.set_submenu (m_MenuFile);
  m_MenuBar.append (m_ItemFile);
  //Ansicht
  m_MenuView.append (m_ItemIn);
  m_ItemIn.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::ZoomIn));
  m_ItemOut.signal_activate ().
    connect (sigc::mem_fun (*this, &MainPanel::ZoomOut));
  m_MenuView.append (m_ItemOut);
  m_ItemView.set_submenu (m_MenuView);
  m_MenuBar.append (m_ItemView);

  m_MainBox.add (m_MenuBar);
  m_MainBox.add (m_WidgetPic);
  add (m_MainBox);

  m_MenuBar.show ();
  m_ItemFile.show ();
  m_ItemView.show ();
  m_ItemOpen.show ();
  m_ItemSave.show ();
  m_ItemSaveLoad.show ();
  m_ItemQuit.show ();
  m_ItemIn.show ();
  m_ItemOut.show ();
  m_WidgetPic.show ();
  m_MainBox.show ();

  try
  {
    if (!Path.empty ()) m_Pic.Load (Path);
  }
  catch (Err Cur)
  {
    MsgErr (Cur.m_Msg);
  }
  Load ();
}//MainPanel


//Open
void MainPanel::Open ()
{
  string Path = FileDlg ("Öffnen", Gtk::FILE_CHOOSER_ACTION_OPEN);
  if (Path.empty ()) return;
  try
  {
    m_Pic.Load (Path);
    Load ();
  }
  catch (BadConvert CurErr)
  {
    Load ();
    MsgErr (CurErr.m_Msg);
  }
  catch (Err CurErr)
  {
    MsgErr (CurErr.m_Msg);
  }
}//Open


//Save
void MainPanel::Save ()
{
  SavePic (false);
}//Save


//SaveLoad
void MainPanel::SaveLoad ()
{
  SavePic (true);
}//SaveLoad


//SavePic
void MainPanel::SavePic (bool Autoload)
{
  if (m_Pic.GetBuf ().Empty ()) return MsgErr ("Kein Bild geladen");
  string Path = FileDlg ("Speichern", Gtk::FILE_CHOOSER_ACTION_SAVE);
  if (Path.empty ()) return;
  try
  {
    m_Pic.Save (Path);
    if (!Autoload) return;
    m_Pic.Load (Path);
    Load ();
  }
  catch (Err CurErr)
  {
    MsgErr (CurErr.m_Msg);
  }
}//SavePic


//FileDlg
string MainPanel::FileDlg (std::string Caption,
                                Gtk::FileChooserAction Action)
{
  Gtk::FileChooserDialog Dlg (Caption, Action);
  Dlg.add_button ("Abbrechen", 1);
  Dlg.add_button (Caption, 0);
  Dlg.set_default_response (0);
  std::vector<string> Extensions = m_Pic.GetExtensions ();
  Gtk::FileFilter All;
  All.set_name ("Alle");
  All.add_pattern ("*");
  Dlg.add_filter (All);
  for (size_t i = 0; i != Extensions.size (); i++)
  {
    string Name = "*." + Extensions[i];
    Gtk::FileFilter Filter;
    Filter.set_name (Name);
    Filter.add_pattern (Name);
    Dlg.add_filter (Filter);
  }
  if (Dlg.run ()) return "";
  return Dlg.get_filename ();
}//FileDlg


//Load
void MainPanel::Load ()
{
  const Buf &Pic = m_Pic.GetBuf ();
  const size_t Len = Pic.Width () * Pic.Height ();
  guint8 *Data = new guint8[Len * 3];
  for (size_t i = 0; i != Len; i++)
  {
    RGB Pixel = Pic.Get (i % Pic.Width (), i / Pic.Width ());
    size_t CurPixel = i * 3; //Weil das ein 1-Byte-Array ist (statt 3-)
    Data[CurPixel] = Pixel.R;
    Data[CurPixel + 1] = Pixel.G;
    Data[CurPixel + 2] = Pixel.B;
  }

  m_WidgetPic.set (Gdk::Pixbuf::create_from_data (Data,
                   Gdk::COLORSPACE_RGB, false, 8, Pic.Width (),
                   Pic.Height (), Pic.Width () * 3,
                   sigc::mem_fun (*this, &MainPanel::Clear)));
}//Load


//Clear
void MainPanel::Clear (const guint8 *Data)
{
  delete []Data;
}//Clear


//ZoomIn
void MainPanel::ZoomIn ()
{
  Zoom (true);
}//ZoomIn


//ZoomOut
void MainPanel::ZoomOut ()
{
  Zoom (false);
}//ZoomOut


//Zoom
void MainPanel::Zoom (bool In)
{
  int X = m_WidgetPic.property_pixbuf ().get_value ()->get_width ();
  int Y = m_WidgetPic.property_pixbuf ().get_value ()->get_height ();
  if (!In && (X < 10 || Y < 10)) return MsgErr ("Zu klein fürs Reinzoomen");
  float Factor = 0.5;
  if (In) Factor = 2;
  Load ();
  m_WidgetPic.set (m_WidgetPic.property_pixbuf ().get_value ()->
    scale_simple (X * Factor, Y * Factor, Gdk::INTERP_HYPER));
}//Zoom
