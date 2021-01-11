#include "StudentDetail.h"

StudentDetail::StudentDetail(int enrid,
                             const String &name,
                             const String &email,
                             const String &branch,
                             const String &faceid,
                             const String &feature)
{
    this->enrid = enrid;
    this->name = name;
    this->email=email;
    this->branch=branch;
    this->faceid=faceid;
    this->feature=feature;
}
