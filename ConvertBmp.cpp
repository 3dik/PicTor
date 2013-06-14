#include "ConvertBmp.hpp"


//ConvertBmp
ConvertBmp::ConvertBmp ()
{
}//ConvertBmp


//~ConvertBmp
ConvertBmp::~ConvertBmp ()
{
}//ConvertBmp


//GetExtensions
std::vector<string> ConvertBmp::GetExtensions () const
{
  std::vector<string> List;
  List.push_back ("bmp");
  return List;
}//GetExtensions


//Load
void ConvertBmp::Load (Buf *fBuf, std::ifstream *File) const
{
  File->exceptions (std::ifstream::eofbit | std::ifstream::failbit |
                    std::ifstream::badbit);
  int X, Y;
  try
  {
    if (File->get () != 'B' || File->get () != 'M') throw ErrConvert ();
    File->ignore (8);
    //Bilddaten-Position ermitteln
    char Offset[4];
    File->read (Offset, sizeof (Offset));

    //Info-Header einlesen
    char Info[40];
    File->read (Info, sizeof (Info));
    //Auflösung einlesen
    X = *reinterpret_cast<int32_t*> (&Info[INFO_WIDTH]);
    Y = *reinterpret_cast<int32_t*> (&Info[INFO_HEIGHT]);
    if (Y < 0) throw ("Es werden nur Bottom-Up-Bitmaps unterstützt");
    fBuf->Create (X, Y);
    if (*reinterpret_cast<uint16_t*> (&Info[INFO_DEPTH]) != 24)
    {
      throw Err ("Es werden nur 24-Bit-Bitmaps unterstützt");
    }
    if (*reinterpret_cast<uint32_t*> (&Info[INFO_COMPRESS]) != 0)
    {
      throw Err ("Es werden keine komprimierten Bitmaps unterstützt");
    }
    if (*reinterpret_cast<uint32_t*> (&Info[INFO_COLORTABLE]) != 0 ||
        *reinterpret_cast<uint32_t*> (&Info[INFO_NUMCOLORS]) != 0)
    {
      throw Err ("Es werden keine Farbtabellen unterstützt");
    }
    File->seekg (*reinterpret_cast<int32_t*> (&Offset));
  }
  catch (std::ios_base::failure)
  {
    throw ErrConvert ();
  }
  try
  {
    for (int Row = Y - 1; Row != -1; Row --) //Bitmaps fangen unten an
    {
      for (int Col = 0; Col != X; Col++)
      {
        char Pix[3];
        File->read (Pix, sizeof (Pix));
        fBuf->Get (Col, Row) = RGB (Pix[2], Pix[1], Pix[0]); //BGR-Format
      }
      //Den restlichen 4-Byte-Block ignorieren
      if (X % 4 == 0) continue;
      File->ignore (4 - (X % 4));
    }
  }
  catch (std::ios_base::failure)
  {
    throw BadConvert ();
  }
}//Load


//Save
void ConvertBmp::Save (const Buf &fBuf, std::ofstream *File) const
{
  //Siehe oben für das Dateiformat
  //Dateikopf
  uint32_t Offset = 54;
  int      NumPixel = fBuf.Width () * fBuf.Height ();
  uint32_t DataSize = NumPixel * 3;
  uint32_t FileSize = DataSize + Offset;
  uint32_t Empty = 0;
  File->write ("BM", 2).
        write (reinterpret_cast<char*> (&FileSize), 4).
        write (reinterpret_cast<char*> (&Empty), 4).
        write (reinterpret_cast<char*> (&Offset), 4);
  //Info-Header
  uint32_t InfoSize = 40;
  int32_t X = fBuf.Width ();
  int32_t Y = fBuf.Height ();
  int16_t Planes = 1;
  int16_t Depth = 24;
  File->write (reinterpret_cast<char*> (&InfoSize), 4).
        write (reinterpret_cast<char*> (&X), 4).
        write (reinterpret_cast<char*> (&Y), 4).
        write (reinterpret_cast<char*> (&Planes), 2).
        write (reinterpret_cast<char*> (&Depth), 2).
        write (reinterpret_cast<char*> (&Empty), 4).
        write (reinterpret_cast<char*> (&DataSize), 4).
        write (reinterpret_cast<char*> (&Empty), 4).
        write (reinterpret_cast<char*> (&Empty), 4).
        write (reinterpret_cast<char*> (&Empty), 4).
        write (reinterpret_cast<char*> (&Empty), 4);
  //Bilddaten
  for (int Row = fBuf.Height () - 1; Row != -1; Row--)
  {
    for (size_t Col = 0; Col != fBuf.Width (); Col++)
    {
      RGB Pix = fBuf.Get (Col, Row);
      File->put (Pix.B).put (Pix.G).put (Pix.R);
    }
    if (fBuf.Width () % 4 == 0) continue;
    for (size_t i = 0; i != 4 - (fBuf.Width () % 4); i++)
    {
      uint8_t Empty = 0;
      File->write (reinterpret_cast<char*> (&Empty), 1);
    }
  }
}//Save
