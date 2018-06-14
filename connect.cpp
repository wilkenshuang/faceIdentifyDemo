#include <iostream>  
#include <sstream>  
#include <memory>  
#include <string>  
#include <stdexcept>  
      
using namespace std;  
#define MYSQLPP_MYSQL_HEADERS_BURIED

#include <mysql++.h>
using namespace mysqlpp;  

#define DBaddr "10.0.2.250"
#define User "aikq"
#define Password "gdexpress"
#define db "faces"

void searchFun(Query* pQuery)
{
	/* Now SELECT 
	cout << "selecting test:" << endl;
	*pQuery << g_szSearchFormat;
	StoreQueryResult ares = pQuery->store();
	cout << "ares.num_rows() = " << ares.num_rows() << endl;
	for (size_t i = 0; i < ares.num_rows(); i++)
	{
		cout << "id: " << ares[i]["id"] << "\t - Name: " << ares[i]["name"] \
			<< "\t - Status: " << ares[i]["status"] << "\t - Modified_at" << ares[i]["modified_at"] << endl;
	}
	*/
	/* Let's get a count of something */
	StoreQueryResult res = pQuery->store();
	StoreQueryResult::const_iterator it;
	for (it = res.begin(); it != res.end(); ++it) {
		Row row = *it;
		cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3] << " " << row[4] << " "
			<< row[5] << " " << row[6] << endl;
	}
}

void insertFun(Query* pQuery){

}
int main() {
      Connection conn(false);
      if(conn.connect(db,DBaddr,User,Password)){
		  cout<<"connect db succeed."<<endl;
		}
	  //Query query = conn.query("SELECT * FROM kq_camtask");
	  Query query = conn.query("SELECT * FROM kq_camtask");
	  //(void)insertFun(&query);
	  (void)searchFun(&query);
      return 0;  
}
