#include "ConvertFile.hpp"

//~ConvertFile
ConvertFile::~ConvertFile ()
{
}//~ConvertFile


//Load
void ConvertFile::Load (string Path, Buf *fBuf) const
{
  std::ifstream File (Path.c_str (), std::ios_base::binary);
  if (!File) throw Err ("Datei konnte nicht geöffnet werden");
  fBuf->Create (200, 200);
  Load (fBuf, &File);
}//Load


//Save
void ConvertFile::Save (string Path, const Buf &fBuf) const
{
  std::ofstream File (Path.c_str (), std::ios_base::binary);
  if (!File) throw Err ("Datei konnte nicht erstellt werden");
  Save (fBuf, &File);
}//Save
