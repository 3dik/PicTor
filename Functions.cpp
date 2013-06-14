#include "Functions.hpp"

//MsgErr
void MsgErr (std::string Message)
{
  Gtk::MessageDialog Box ("Omg ein Fehler ist aufgetreten:");
  Box.set_title ("Fehler :(");
  Box.set_secondary_text (Message);
  Box.run ();
}//MsgErr
