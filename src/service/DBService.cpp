#include "service/DBService.h"


DBService::DBService(){
    
}

int DBService::Db_open(char name[]){
  strncpy(this->_db_name,name,MAX_FILE_NAME_LEN);

  if (this->_db != NULL)
    sqlite3_close(this->_db);
  this->rc = sqlite3_open(this->_db_name, &this->_db);
  if (this->rc)
  {
    Serial.print(F("Can't open database: "));
    Serial.print(sqlite3_extended_errcode(this->_db));
    Serial.print(" ");
    Serial.println(sqlite3_errmsg(this->_db));
    return this->rc;
  }
  else
    Serial.println(F("Opened database successfully"));
  return this->rc;

}