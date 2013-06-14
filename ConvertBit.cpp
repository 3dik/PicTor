#include "ConvertBit.hpp"

//ConvertBit
ConvertBit::ConvertBit ()
{
}//ConvertBit


//~ConvertBit
ConvertBit::~ConvertBit ()
{
}//~ConvertBit


//Load
void ConvertBit::Load (Buf *fBuf, std::ifstream *File) const
{
  char Res[4]; //Die ersten 4 Bytes für die Auflösung
  File->read (Res, 4);
  if (!File->good ()) throw ErrConvert ();

  //Die ersten beiden Byte-Paare als X- bzw. Y-Wert
  fBuf->Create (*reinterpret_cast<uint16_t*> (&Res[0]),
                *reinterpret_cast<uint16_t*> (&Res[2]));
  //Jedes Pixel einzeln einlesen
  for (size_t i = 0; i != fBuf->Width () * fBuf->Height (); i++)
  {
    unsigned char Val = File->get ();
    if (File->eof ()) throw (BadConvert ());
    fBuf->Get (i) = RGB (Val);
  }
}//Load


//Save
void ConvertBit::Save (const Buf &fBuf, std::ofstream *File) const
{
  //siehe oben für das Dateiformat
  uint16_t X = fBuf.Width ();
  uint16_t Y = fBuf.Height ();
  File->write (reinterpret_cast<char*> (&X), 2);
  File->write (reinterpret_cast<char*> (&Y), 2);
  for (int i = 0; i != X * Y; i++)
  {
    RGB Pix = fBuf.Get (i);
    File->put ((Pix.R + Pix.G + Pix.B) / 3);
  }
}//Save


//GetExtensions
std::vector<string> ConvertBit::GetExtensions () const
{
  std::vector<string> List;
  List.push_back ("bpic");
  return List;
}//GetExtensions
