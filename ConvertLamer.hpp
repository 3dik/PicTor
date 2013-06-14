//Converter-Klasse für das Lamer-Bildformat

#pragma once

#include "ConvertFile.hpp"

class ConvertLamer : public ConvertFile
{
  public:

  ConvertLamer ();
  ~ConvertLamer ();
  std::vector<string> GetExtensions () const;

  private:

  void Load (Buf *fBuf, std::ifstream *File) const;
  void Save (const Buf &fBuf, std::ofstream *File) const;
};
