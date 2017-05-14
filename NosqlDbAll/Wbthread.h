#pragma once
#include<thread>
#include "../NosqlDbAll/NosqlDbAll.h"

template<typename Dbt1, typename Dbt2, typename Dbt3>
class wbthread
{
public:
	bool startwb (NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3> dba);
private:
	std::thread wbthd;
};

template<typename Dbt1, typename Dbt2, typename Dbt3>
bool wbthread<typename Dbt1, typename Dbt2, typename Dbt3>::startwb(NosqldbAll<typename Dbt1, typename Dbt2, typename Dbt3> dba)
{
	wbthd(dba.toXmlfile);
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}