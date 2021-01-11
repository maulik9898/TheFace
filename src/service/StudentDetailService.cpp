#include "service/StudentDetailService.h"
#define FORMAT_SPIFFS_IF_FAILED true
#define MAX_FILE_NAME_LEN 100
#define MAX_STR_LEN 500
#define DEBUG_ON 1

bool firstTime;
StudentDetailService ::StudentDetailService(char name[]) : DBService(name)
{
}

void StudentDetailService ::DropTable()   
{   sqlite3_stmt *res;
    String sql = "DROP TABLE IF EXISTS " + this->_table_name;
    String debug = "DROPPING TABLE " + this->_table_name;
     this->rc = sqlite3_prepare_v2(this->_db, sql.c_str(), -1, &res, NULL);
    if (this->rc != SQLITE_OK)
    {
        Serial.print(F("Error Dropping table"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return ;
    }
    sqlite3_finalize(res);
    this->rc = sqlite3_step(res);
    sqlite3_finalize(res);
}

void StudentDetailService ::CreateTable()
{
    sqlite3_stmt *res;
    String student_detail_table = "CREATE TABLE IF NOT EXISTS STUDENTDETAIL("
                                  "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                                  "ENRID INT NOT NULL UNIQUE,"
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
    String sql = "INSERT INTO " + this->_table_name +  "(ENRID,NAME,EMAIL,BRANCH,FACEID,FEATURE) VALUES ( ? , ? , ? , ? , ? , ? );";
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
    sqlite3_bind_int(res,1,studentDetail.id);
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
        Serial.print(F("Error preparing insert stmt"));
        Serial.print(sqlite3_extended_errcode(this->_db));
        Serial.print(" ");
        Serial.println(sqlite3_errmsg(this->_db));
        return students;
    }
   
        while (this->rc == SQLITE_ROW)
        {
            int id = sqlite3_column_int(res, 0);
            int enrid = sqlite3_column_int(res, 1);
            String name = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 2)));
            String email = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 3)));
            String branch = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 4)));
            String faceid = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 5)));
            String feature = String(reinterpret_cast<const char *>(sqlite3_column_text(res, 6)));
            StudentDetail student(enrid, name, email, branch, faceid, feature);
            student.id = id;
            students.push_back(student);
            Serial.print(student.id);
        Serial.print("  " + student.name);
        Serial.print("  " + student.email);
        Serial.print("  " + student.branch);
        Serial.print("  " + student.faceid);
        Serial.print("  " + student.feature);
            this->rc = sqlite3_step(res);
        }
    
    sqlite3_finalize(res);

    return students;
}