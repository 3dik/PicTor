#include "Pic.hpp"

//Pic
Pic::Pic ()
{
  m_Pic.Create (100, 100);
  m_ConvertList.push_back (new ConvertBmp);
  m_ConvertList.push_back (new ConvertBit);
  m_ConvertList.push_back (new ConvertLamer);
}//Pic


//~Pic
Pic::~Pic ()
{
  while (!m_ConvertList.empty ())
  {
    delete m_ConvertList.back ();
    m_ConvertList.pop_back ();
  }
}//Pic


//GetBuf
const Buf &Pic::GetBuf () const
{
  return m_Pic;
}//GetBuf


//Load
void Pic::Load (string Path)
{
  GetConvert (Path).Load (Path, &m_Pic);
}//Load


//Save
void Pic::Save (string Path) const
{
  GetConvert (Path).Save (Path, m_Pic);
}//Save


//GetExtensions
std::vector<string> Pic::GetExtensions () const
{
  std::vector<string> List;
  for (size_t i = 0; i != m_ConvertList.size (); i++)
  {
    std::vector<string> Cur = m_ConvertList[i]->GetExtensions ();
    std::copy (Cur.begin (), Cur.end (), std::back_inserter (List));
  }
  return List;
}//GetExtensions


//GetConvert
const Convert &Pic::GetConvert (string Path) const
{
  std::vector<string> List = GetExtensions ();
  for (size_t i = 0; i != m_ConvertList.size (); i++)
  {
    if (m_ConvertList[i]->GoodExtension (Path)) return *m_ConvertList[i];
  }
  throw (Err ("Unbekannte Dateiendung"));
}//GetConvert
