//Bildpuffer
//2-Dimenionales RGB-Raster

#pragma once

#include <vector>
#include <iostream>

#include "Err.hpp"

//Ein RGB-Pixel
struct RGB
{
  RGB ();
  RGB (unsigned char R, unsigned char G, unsigned char B);
  RGB (unsigned char);
  unsigned char R;
  unsigned char G;
  unsigned char B;
};

bool operator== (RGB Left, RGB Right);
bool operator!= (RGB Left, RGB Right);

class Buf
{
  public:

  //Bild löschen
  void Clear ();
  //Prüfen, ob ein Bild geladen ist
  bool Empty () const;
  //Breite zurückgeben
  size_t Width () const;
  //Höhe zurückgeben
  size_t Height () const;
  //Erstellt ein neues Bild mit den übergebenen Maßen
  void Create (size_t X, size_t Y);
  //Gibt Pixel einer bestimmten Stelle zurück
  RGB &Get (size_t X, size_t Y);
  RGB Get (size_t X, size_t Y) const;
  //... anhand von Nummer. Reihenfolge: Reihenweise von oben nach unten
  RGB &Get (size_t N);
  RGB Get (size_t N) const;

  private:

  //Äußerer Vektor speichert die Zeilen. Der zweite Vektor speichert die
  //Pixel der Zeilen.
  std::vector<std::vector<RGB> > m_Data;
};
