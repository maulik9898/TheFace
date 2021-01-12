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
    StudentDetailService();
    int InsertDetail(StudentDetail StudentDetail);
    void CreateTable();
    int DropTable();
    std::vector<StudentDetail> GetAllStudents();
    std::vector<StudentDetail> GetStudent(long enrid);
    std::vector<StudentDetail> GetFromQuery(const String &query);
};


#endif
