#ifndef STUDENTDETAILSERVICE_H
#define STUDENTDETAILSERVICE_H
#include "config/config.h"
#include "service/DBService.h"
#include "model/StudentDetail.h"

class StudentDetailService : public DBService
{   
private:
    String _table_name = "STUDENTDETAIL";


public:
    StudentDetailService(char name[]);
    StudentDetailService();
    int InsertDetail(StudentDetail StudentDetail);
    void CreateTable();
    void DropTable();
    std::vector<StudentDetail> GetAllStudents();
};


#endif
