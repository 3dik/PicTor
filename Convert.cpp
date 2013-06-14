#include "Convert.hpp"

//Convert
Convert::~Convert ()
{
}//Convert


//GoodExtension
bool Convert::GoodExtension (string Path) const
{
  size_t Pos = Path.rfind (".");
  if (Pos == string::npos) return false;
  std::vector<string> Extensions = GetExtensions ();
  if (std::find (Extensions.begin (), Extensions.end (),
                 Path.substr (Pos + 1)) == Extensions.end ())
  {
    return false;
  }
  return true;
}//GoodExtension


//ErrConvert
ErrConvert::ErrConvert () :
  Err ("Die Bilddatei ist beschädigt und konnte nicht geladen werden")
{
}//ErrConvert


//BadConvert
BadConvert::BadConvert () :
  Err ("Die Bilddatei ist beschädigt und wurde wohl fehlerhaft geladen")
{
}//BadConvert
