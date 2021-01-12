#include "service/StudentDetailService.h"
#define FORMAT_SPIFFS_IF_FAILED true
#define MAX_FILE_NAME_LEN 100
#define MAX_STR_LEN 500
#define DEBUG_ON 1

bool firstTime;
StudentDetailService ::StudentDetailService()
{
}

int StudentDetailService ::DropTable()
{

    sqlite3_stmt *res;
    String sql = "DROP TABLE IF EXISTS STUDENTDETAIL";
    String debug = "DROPPING TABLE " + this->_table_name;
   
    this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, NULL);
    
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error Dropping table"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return this->rc;
    }
    this->rc = sqlite3_step(res);
    sqlite3_finalize(res);
    return this->rc;
}

void StudentDetailService ::CreateTable()
{
    sqlite3_stmt *res;
    String student_detail_table = "CREATE TABLE IF NOT EXISTS STUDENTDETAIL("
                                  "ID INTEGER PRIMARY KEY ,"
                                  "ENRID INTEGER NOT NULL UNIQUE,"
                                  "NAME VARCHAR(200),"
                                  "EMAIL VARCHAR(50),"
                                  "BRANCH VARCHAR(50),"
                                  "FACEID VARCHAR(100),"
                                  "FEATURE VARCHAR(200));";
    String debug = "CREATING TABLE " + this->_table_name;
    this->rc = sqlite3_prepare_v2(this->_db, student_detail_table.c_str(), -1, &res, NULL);
    if (this->rc == SQLITE_OK)
    {
        this->rc = sqlite3_step(res);
    }
    sqlite3_finalize(res);
}

int StudentDetailService ::InsertDetail(StudentDetail studentDetail)
{
    sqlite3_stmt *res;
    String sql = "INSERT INTO " + this->_table_name + "(ENRID,NAME,EMAIL,BRANCH,FACEID,FEATURE) VALUES ( ? , ? , ? , ? , ? , ? );";
    String debug = F("TABLE INSERT");
    this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, NULL);
    
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error preparing insert stmt"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return this->rc;
    }
    sqlite3_bind_int(res,1,studentDetail.enrid);
    sqlite3_bind_text(res,2,studentDetail.name.c_str(),studentDetail.name.length(),SQLITE_TRANSIENT);
    sqlite3_bind_text(res,3,studentDetail.email.c_str(),studentDetail.email.length(),SQLITE_TRANSIENT);
    sqlite3_bind_text(res,4,studentDetail.branch.c_str(),studentDetail.branch.length(),SQLITE_TRANSIENT);
    sqlite3_bind_text(res,5,studentDetail.faceid.c_str(),studentDetail.faceid.length(),SQLITE_TRANSIENT);
    sqlite3_bind_text(res,6,studentDetail.feature.c_str(),studentDetail.feature.length(),SQLITE_TRANSIENT);
    this->rc = sqlite3_step(res);
    sqlite3_finalize(res);
    return this->rc;
}

std::vector<StudentDetail> StudentDetailService ::GetAllStudents()
{
    sqlite3_stmt *res;
    std::vector<StudentDetail> students;
    firstTime = true;
    String sql = "SELECT * FROM " + this->_table_name;
    this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, 0);
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error preparing get all stmt"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return students;
    }
    this->rc = sqlite3_step(res);
    while (this->rc == SQLITE_ROW)
    {
        long  id = sqlite3_column_int(res, 0);
        long  enrid = sqlite3_column_int(res, 1);
        String name = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 2)));
        String email = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 3)));
        String branch = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 4)));
        String faceid = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 5)));
        String feature = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 6)));
        StudentDetail student(enrid, name, email, branch, faceid, feature);
        student.id = id;
        students.push_back(student);
        this->rc = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return students;
}

std::vector<StudentDetail> StudentDetailService ::GetStudent(long enrid)
{
    sqlite3_stmt *res;
    std::vector<StudentDetail> students;
    firstTime = true;
    String sql = "SELECT * FROM " + this->_table_name + " WHERE ENRID = "+enrid;
    this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, 0);
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error preparing get student stmt"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return students;
    }
    this->rc = sqlite3_step(res);
    while (this->rc == SQLITE_ROW)
    {
        long  id = sqlite3_column_int(res, 0);
        long  enrid = sqlite3_column_int(res, 1);
        String name = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 2)));
        String email = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 3)));
        String branch = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 4)));
        String faceid = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 5)));
        String feature = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 6)));
        StudentDetail student(enrid, name, email, branch, faceid, feature);
        student.id = id;
        students.push_back(student);
        this->rc = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return students;
}


std::vector<StudentDetail> StudentDetailService ::GetFromQuery(const String &query)
{
    sqlite3_stmt *res;
    std::vector<StudentDetail> students;
    String sql = "SELECT * FROM " + this->_table_name + " ";
    sql+=query;

    
    this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, 0);
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error preparing get student stmt"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        Serial.println(sql);
        return students;
    }
    this->rc = sqlite3_step(res);
    while (this->rc == SQLITE_ROW)
    {
        long  id = sqlite3_column_int(res, 0);
        long  enrid = sqlite3_column_int(res, 1);
        String name = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 2)));
        String email = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 3)));
        String branch = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 4)));
        String faceid = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 5)));
        String feature = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 6)));
        StudentDetail student(enrid, name, email, branch, faceid, feature);
        student.id = id;
        students.push_back(student);
        this->rc = sqlite3_step(res);
    }

    sqlite3_finalize(res);

    return students;
}