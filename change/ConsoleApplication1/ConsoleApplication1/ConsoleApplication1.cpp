
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <map>
#include <string>
#include <vector>

#include <regex>
using namespace std;
static map<string, string> a;
std::vector<std::string> stringSplit(const std::string& str, char delim);
static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    a[argv[0]] = argv[1];
    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
     char* sql;
   const char* data = "Callback function called";

    /* Open database */

    rc = sqlite3_open("D:\\baosteel\\thick_app\\app\\app\\bin\\Debug\\analysis\\thick.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    /* Create merged SQL statement */
    sql = (char*)"select rowid,toc from \"2021-11\";";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }

    map<string, string>::iterator ite = a.begin();
    for (; ite != a.end(); ite++)
    {


        string b = ite->second;
        if (b == "2021/11/10 0:16")
        {
            int a = 0;
        }
        std::vector<std::string> arrayb = stringSplit(b ,' ');
        string  month = stringSplit(arrayb[0], '/')[0]  +"/"+ stringSplit(arrayb[0], '/')[1];
       string  data = stringSplit(arrayb[0], '/')[2];
       string  hour = stringSplit(arrayb[1], ':')[0];
       string  minute = stringSplit(arrayb[1], ':')[1];
       if (data.size() == 1)data = "0" + data;
       if (hour.size() == 1)hour = "0" + hour;
       string newb = month + "/" + data + " " + hour + ":" + minute;
      
       if (newb != b) {
           string sqlstring = " UPDATE '2021-11' SET  toc ='" + newb + "' WHERE  rowid = " + ite->first + " ; ";
           sql = (char*)sqlstring.c_str();
           sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
       }
    }




    sqlite3_close(db);
    return 0;
}

std::vector<std::string> stringSplit(const std::string& str, char delim) {
    std::string s;
    s.append(1, delim);
    std::regex reg(s);
    std::vector<std::string> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
        std::sregex_token_iterator());
    return elems;
}