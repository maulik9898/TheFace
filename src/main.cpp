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
  StudentDetailService studentService("/sd/hell");
  studentService.CreateTable();
  if (studentService.rc == SQLITE_DONE)
  {
    Serial.println("Student table created !!");
    StudentDetail student(random(0,99999), "Maulik", "maulikp163@gmail.com", "Electrical", "faceid", "feature");
    StudentDetail student2(random(0,99999), "Chahil", "Chahil@gmail.com", "Computer", "faceid", "feature");
    if (studentService.InsertDetail(student) != SQLITE_DONE)
    {
      Serial.println("error 1 inserted row");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }
    if (studentService.InsertDetail(student2) != SQLITE_DONE)
    {
      Serial.println("error 2 inserted row");
      Serial.print(sqlite3_extended_errcode(studentService._db));
      Serial.print(" ");
      Serial.println(sqlite3_errmsg(studentService._db));
    }

    std::vector<StudentDetail> students = studentService.GetAllStudents();

    if (studentService.rc == SQLITE_DONE)
    {
      Serial.println("Id  Name      Email         Branch        Faceid    Feature");
      for (int i = 0; i < students.size(); i++)
      {
        StudentDetail s = students[i];
        Serial.print(student.id);
        Serial.print("  " + student.name);
        Serial.print("  " + student.email);
        Serial.print("  " + student.branch);
        Serial.print("  " + student.faceid);
        Serial.print("  " + student.feature);
      }
    }
    else
    {
      Serial.println("Error fetching data");
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
