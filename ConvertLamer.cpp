#include "ConvertLamer.hpp"


//ConvertLamer
ConvertLamer::ConvertLamer ()
{
}//ConvertLamer


//~ConvertLamer
ConvertLamer::~ConvertLamer ()
{
}//~ConvertLamer


//GetExtensions
std::vector<string> ConvertLamer::GetExtensions () const
{
  std::vector<string> List;
  List.push_back ("lamer");
  return List;
}//GetExtensions


//Load
void ConvertLamer::Load (Buf *fBuf, std::ifstream *File) const
{
  if (File->get () != '2' || File->get () != '3') throw ErrConvert ();
  char Res[4];
  File->read (Res, 4);
  if (!File->good ()) throw ErrConvert ();
  fBuf->Create (*reinterpret_cast<uint16_t*> (&Res[0]),
                *reinterpret_cast<uint16_t*> (&Res[2]));
  size_t Cur = 0;
  while (Cur < fBuf->Width () * fBuf->Height ())
  {
    char Block[4];
    File->read (Block, 4);
    size_t End = Cur + *reinterpret_cast<uint8_t*> (&Block[0]);
    for (; Cur != End; Cur++)
    {
      fBuf->Get (Cur) = RGB (Block[1], Block[2], Block[3]);
    }
  }
}//Load


//Save
void ConvertLamer::Save (const Buf &fBuf, std::ofstream *File) const
{
  //Header
  *File<<"23";
  uint16_t X = fBuf.Width ();
  uint16_t Y = fBuf.Height ();
  File->write (reinterpret_cast<char*> (&X), 2).
        write (reinterpret_cast<char*> (&Y), 2);

  int Pos = 0;
  RGB Old;
  const size_t Last = fBuf.Width () * fBuf.Height ();
  for (size_t i = 0; i <= Last; i++)
  {
    RGB Cur;
    if (i != Last) Cur = fBuf.Get (i);
    if (!i)
    {
      Old = Cur;
      continue;
    }
    uint8_t Len = i - Pos;
    if (Old != Cur || Len == 255 || i == Last)
    {
      File->put (*reinterpret_cast<char*> (&Len)).
            put (Old.R). put (Old.G). put (Old.B);
      Pos = i;
      Old = Cur;
    }
  }
}//Save
