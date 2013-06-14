//Bildklasse
//Lädt und speichert Bilder verschiedener Formate

#pragma once

#include <string>
#include <algorithm>
#include <memory>

#include "Convert.hpp"
#include "Err.hpp"
#include "ConvertBmp.hpp"
#include "ConvertBit.hpp"
#include "ConvertLamer.hpp"

class Pic
{
  public:

  Pic ();
  ~Pic ();
  //Bilddatei laden
  void Load (string Path);
  //Bild speichern
  void Save (string Path) const;
  //Bildbuffer zurückgeben
  const Buf &GetBuf () const;
  //Liste der Dateiendungen aller verfügbaren Bildformate zurückgeben
  std::vector<string> GetExtensions () const;
  
  private:

  //Anhand des übergebenen Pfades und dessen Dateiendung ein passendes
  //Convert-Objekt auswählen und zurückgeben. Wirft Ausnahme, wenn
  //unbekanntes Format
  const Convert &GetConvert (string Path) const;

  std::vector<Convert*> m_ConvertList;
  Buf                   m_Pic;
};
