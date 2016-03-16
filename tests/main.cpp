#include <QCoreApplication>
#include "../dbmodel.h"
#include <iostream>
using namespace std;

void assertTrue(string s,bool t1,bool t2){
    if(t1 == t2){
        cout << s + " - SUCCESS\n";
    }
    else{
        cout << s + " - FAIL\n";
    }
}
void testConnectDB(){
    dbmodel MainDb;
    bool res = MainDb.connect_db();
    assertTrue("testConnectDB",res,true);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testConnectDB();
    return 0;
}

