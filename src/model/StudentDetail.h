#ifndef STUDENTDETAIL_H
#define STUDENTDETAIL_H
#include<Arduino.h>

class StudentDetail
{
public:
    int id;
    int enrid;
    String name;
    String email;
    String branch;
    String faceid;
    String feature;

    StudentDetail(int enrid,
                const String &name,
                const String &email,
                const String &branch,
                const String &faceid,
                const String &feature);
    
};

#endif