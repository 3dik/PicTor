//Abstrakte Basisklasse für Bildformat-Konvertierungen
//Lädt oder speichert Bilddateien des eigenen Formats
//Objekte sind in der Regel Zustandslos

#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Err.hpp"
#include "Buf.hpp"

typedef std::vector<char> PicBuf;

using std::string;

class Convert
{
  public:

  virtual ~Convert ();
  //Bilddatei lesen und umwandeln
  virtual void Load (string Path, Buf *fBuf) const = 0;
  //Buffer in Bilddatei speichern
  virtual void Save (string Path, const Buf &fBuf) const = 0;
  //Liste der Dateiendungen dieses Formats zurückgeben
  virtual std::vector<string> GetExtensions () const = 0;

  //Prüfen, ob der übergebene Dateiname eine Dateiendung dieses Formats hat
  bool GoodExtension (string FileName) const;
};


//Ladefehler, wird geworfen, wenn Bilddatei nicht geladen worden konnte
class ErrConvert : public Err
{
  public:

  ErrConvert ();
};


//Reparatur-Ausnahme, wird geworfen, wenn die Bilddatei beschädigt ist, aber
//trotzdem halbwegs geladen werden konnte
class BadConvert : public Err
{
  public:

  BadConvert ();
};
