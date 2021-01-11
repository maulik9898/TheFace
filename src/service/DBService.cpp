#include "service/DBService.h"


DBService::DBService(char name[]){
    strncpy(this->_db_name,name,MAX_FILE_NAME_LEN);
    int rc;
    this->rc = this->Db_open();
}

int DBService::Db_open(){

  if (this->_db != NULL)
    sqlite3_close(this->_db);
  int rc = sqlite3_open(this->_db_name, &this->_db);
  if (rc)
  {
    Serial.print(F("Can't open database: "));
    Serial.print(sqlite3_extended_errcode(this->_db));
    Serial.print(" ");
    Serial.println(sqlite3_errmsg(this->_db));
    return rc;
  }
  else
    Serial.println(F("Opened database successfully"));
  return rc;

}