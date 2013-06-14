//Abstrakte Convert-Klasse, die das File-Objekt verwaltet

#pragma once

#include <fstream>
#include "stdint.h"

#include "Convert.hpp"

class ConvertFile : public Convert
{
  public:

  virtual ~ConvertFile ();
  //Öffnet ein File-Objekt zur angegebenen Datei
  void Load (string Path, Buf *fBuf) const;
  //Öffnet ein File-Objekt zur angegebenen Datei
  void Save (string Path, const Buf &fBuf) const;

  private:

  virtual void Load (Buf *fBuf, std::ifstream *File) const = 0;
  virtual void Save (const Buf &fBuf, std::ofstream *File) const = 0;
};
