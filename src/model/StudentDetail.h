#ifndef STUDENTDETAIL_H
#define STUDENTDETAIL_H
#include<Arduino.h>

class StudentDetail
{
public:
    long  id;
    long  enrid;
    String name;
    String email;
    String branch;
    String faceid;
    String feature;

    StudentDetail(long  enrid,
                const String &name,
                const String &email,
                const String &branch,
                const String &faceid,
                const String &feature);
    
};

#endif