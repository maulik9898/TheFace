/*
  Open and execute SQL statements throught this console.
  Output is in tab-delimited format.
    Connections for SD Card in SPI Mode:
      * SD Card   | ESP32
      *  DAT2        -
      *  DAT3        SS (D5)
      *  CMD         MOSI (D23)
      *  VSS         GND
      *  VDD         3.3V
      *  CLK         SCK (D18)
      *  DAT0        MISO (D19)
      *  DAT1        -
    Connections for SD Card in SD_MMC Mode:
      * SD Card   | ESP32
      *  DAT2 (1)    D12
      *  DAT3 (2)    D13
      *  CMD  (3)    D15
      *  VDD  (4)    3.3V
      *  CLK  (5)    D14
      *  VSS  (6)    GND
      *  DAT0 (7)    D2
      *  DAT1 (8)    D4
*/

#include "config/config.h"
#include <vector>
#include "sqlite3.h"
#include "service/StudentDetailService.h"

#define FORMAT_SPIFFS_IF_FAILED true
#define MAX_FILE_NAME_LEN 100
#define MAX_STR_LEN 500
#define DEBUG_ON 1

using namespace std;
StudentDetailService studentService;


void setup()
{
  Serial.begin(115200);
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
  {
    Serial.println(F("Failed to mount file Serial"));
    return;
  }
  SPI.begin();
  SD.begin();
  sqlite3_initialize();
  studentService.Db_open("/sd/mm123");
  studentService.DropTable();
  if(studentService.rc != SQLITE_DONE)
  {
      Serial.println("error dropping table");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }
  studentService.CreateTable();
  if (studentService.rc == SQLITE_DONE)
  {
    Serial.println("Student table created !!");
    long n1 = random(0,99999);
    long n2 = random(0,99999);

    StudentDetail student(n1, "Chahil", "maulik@gmail.com", "Electrical", "faceid", "feature");
     if (studentService.InsertDetail(student) != SQLITE_DONE)
    {
      Serial.println("error 1 inserted row");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }
    StudentDetail student1(n2, "GGHGHH",  "GGHGHH@gmail.com", "Electrical", "faceid", "feature");
     if (studentService.InsertDetail(student1) != SQLITE_DONE)
    {
      Serial.println("error 2 inserted row");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }

    Serial.println();
    Serial.print("Getting All Students ");
    Serial.println();

    std::vector<StudentDetail> students = studentService.GetAllStudents();

    if (studentService.rc == SQLITE_DONE)
    {
      
      for (int i = 0; i < students.size(); i++)
      {
        Serial.println(students[i].id);
        Serial.println(students[i].enrid);
        Serial.println(students[i].name);
        Serial.println(students[i].email);
        Serial.println(students[i].branch);
        Serial.println(students[i].faceid);
        Serial.println(students[i].feature);
        Serial.println("     ");
      }
    }
    else
    {
      Serial.println("Error fetching data");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }
    Serial.println();
    Serial.print("Getting Student with ENRID = ");
    Serial.print(n1);
    Serial.println();

    students = studentService.GetStudent(n1);

    if (studentService.rc == SQLITE_DONE)
    {
      
      for (int i = 0; i < students.size(); i++)
      {
        Serial.println(students[i].id);
        Serial.println(students[i].enrid);
        Serial.println(students[i].name);
        Serial.println(students[i].email);
        Serial.println(students[i].branch);
        Serial.println(students[i].faceid);
        Serial.println(students[i].feature);
        Serial.println("     ");
      }
    }
    else
    {
      Serial.println("Error fetching student data");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }

    String query = "WHERE name = " + String("'GGHGHH'");

    Serial.println();
    Serial.print("Getting Student with Query");
    Serial.println();
    Serial.println(query);

    students = studentService.GetFromQuery(query);

    if (studentService.rc == SQLITE_DONE)
    {
      
      for (int i = 0; i < students.size(); i++)
      {
        Serial.println(students[i].id);
        Serial.println(students[i].enrid);
        Serial.println(students[i].name);
        Serial.println(students[i].email);
        Serial.println(students[i].branch);
        Serial.println(students[i].faceid);
        Serial.println(students[i].feature);
        Serial.println("     ");
      }
    }
    else
    {
      Serial.println("Error fetching query data");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }

    
  }
  else
  {
    Serial.println("Error creating table");
    Serial.print(sqlite3_extended_errcode(studentService._db));
    Serial.print(" ");
    Serial.println(sqlite3_errmsg(studentService._db));
  }
}

char str[MAX_STR_LEN];
void loop()
{
}
