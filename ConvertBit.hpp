//Konverterklasse für Schwarz-Weiß-Bilder
//Ein Pixel besteht aus einem Byte. Die Farben gehen von Weiß (0) bis
//Schwarz (255)

#pragma once

#include "ConvertFile.hpp"

class ConvertBit : public ConvertFile
{
  public:

  ConvertBit ();
  ~ConvertBit ();
  std::vector<string> GetExtensions () const;

  private:

  void Load (Buf *fBuf, std::ifstream *File) const;
  void Save (const Buf &fBuf, std::ofstream *File) const;
};
