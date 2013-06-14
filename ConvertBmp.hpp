//Converter-Klasse für Bitmap-Dateien

#pragma once

#include <iostream>

#include "ConvertFile.hpp"

class ConvertBmp : public ConvertFile
{
  public:

  ConvertBmp ();
  ~ConvertBmp ();
  std::vector<string> GetExtensions () const;

  private:

  void Load (Buf *fBuf, std::ifstream *File) const;
  void Save (const Buf &fBuf, std::ofstream *File) const;

  enum
  {
    INFO_WIDTH = 4,
    INFO_HEIGHT = 8,
    INFO_DEPTH = 14,
    INFO_COMPRESS = 16,
    INFO_COLORTABLE = 32,
    INFO_NUMCOLORS = 36
  };
};
