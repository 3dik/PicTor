#include "Buf.hpp"

//RGB
RGB::RGB () :
  R (0), G (0), B (0)
{
}//RGB

//RGB
RGB::RGB (unsigned char R, unsigned char G, unsigned char B) :
  R (R), G (G), B(B)
{
}//RGB

//RGB
RGB::RGB (unsigned char Val) :
  R (Val), G (Val), B (Val)
{
}//RGB

//operator==
bool operator== (RGB Left, RGB Right)
{
  return Left.R == Right.R && Left.G == Right.G && Left.B == Right.B;
}//operator==

//operator!=
bool operator!= (RGB Left, RGB Right)
{
  return !operator== (Left, Right);
}//operator!=


//Clear
void Buf::Clear ()
{
  m_Data.clear ();
}//Clear


//Empty
bool Buf::Empty () const
{
  if (!m_Data.empty () && !m_Data[0].empty ()) return false;
  return true;
}//Empty


//Width
size_t Buf::Width () const
{
  if (!Height ()) return 0; //Dann gibt es eh kein Breiten-Vektor
  return m_Data[0].size ();
}//Width


//Height
size_t Buf::Height () const
{
  return m_Data.size ();
}//Height


//Create
void Buf::Create (size_t X, size_t Y)
{
  Clear ();
  m_Data.resize (Y);
  for (size_t i = 0; i != m_Data.size (); i++)
  {
    m_Data[i].resize (X);
  }
}//Create


//Get
RGB &Buf::Get (size_t X, size_t Y)
{
  try
  {
    return m_Data.at (Y).at (X);
  }
  catch (std::exception)
  {
    throw Err ("Konnte nicht auf Pixel zugreifen");
  }
}//Get


//Get
RGB Buf::Get (size_t X, size_t Y) const
{
  //Doppelter Code wegen "const"-Konflikt beim gegenseitigen Aufrufen der
  //beiden Funktionen
  try
  {
    return m_Data.at (Y).at (X);
  }
  catch (std::exception)
  {
    throw Err ("Konnte nicht auf Pixel zurückgreifen");
  }
}//Get


//Get
RGB &Buf::Get (size_t N)
{
  return Get (N % Width (), N / Width ());
}//Get


//Get
RGB Buf::Get (size_t N) const
{
  return Get (N % Width (), N / Width ());
}//Get
