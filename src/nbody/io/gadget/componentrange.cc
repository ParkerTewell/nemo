// ============================================================================
// Copyright Jean-Charles LAMBERT - 2008                                       
// e-mail:   Jean-Charles.Lambert@oamp.fr                                      
// address:  Dynamique des galaxies                                            
//           Laboratoire d'Astrophysique de Marseille                          
//           P�le de l'Etoile, site de Ch�teau-Gombert                         
//           38, rue Fr�d�ric Joliot-Curie                                     
//           13388 Marseille cedex 13 France                                   
//           CNRS U.M.R 6110                                                   
// ============================================================================
#include "componentrange.h"
#include <sstream>
#include <iostream>
#include "assert.h"
namespace glnemo {

// ============================================================================
// constructor                                                                 
ComponentRange::ComponentRange()
{
  n=0;
  first=last=-1;
  range="";
  type="";
}
// ============================================================================
// copy constructor                                                            
ComponentRange::ComponentRange(const ComponentRange&m)
{
  n     = m.n;
  first = m.first;
  last  = m.last;
  range = m.range;
  type  = m.type;
}
// ============================================================================
ComponentRange::~ComponentRange()
{
}
// ============================================================================
void ComponentRange::setData(const int _f, const int _l, const std::string _t)
{
  first=_f;
  last = _l;
  setType(_t);
  computeN();
  buildRange();
}
// ============================================================================
int ComponentRange::computeN()
{
  n=last-first+1;
  return n;
};
// ============================================================================
void ComponentRange::buildRange()
{
  std::ostringstream stm1,stm2;
  stm1 << first;
  stm2 << last;
  range = stm1.str()+":"+stm2.str();
};
// ============================================================================
int ComponentRange::getIndexMatchType(const ComponentRangeVector * crv, const std::string type)
{
  int status=-1;
  assert(crv);
  for (unsigned int i=0; i<crv->size()&&status==-1; i++)
    if ((*crv)[i].type == type)  status=i;
  return status;
}
// ============================================================================
void ComponentRange::list(const ComponentRangeVector * crv)
{
  for (unsigned int i=0; i<crv->size(); i++) {
    std::cerr << "-----------------------------------------------------------\n";
    std::cerr << "Component #"<<i<<"\n";
    std::cerr << "type  :"<<(*crv)[i].type<<"\n";
    std::cerr << "range :"<<(*crv)[i].range<<"\n";
    std::cerr << "nbody :"<<(*crv)[i].n<<"\n";
  }
}
// ============================================================================
int ComponentRange::print(const ComponentRangeVector * crv, std::string select)
{
  for (unsigned int i=0; i<crv->size(); i++) {
    if ((*crv)[i].type == select) return i;
  }
  return -1;
}
} // namespace
// ============================================================================
