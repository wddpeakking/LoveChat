#ifndef _LoveChat_Type_H_
#define _LoveChat_Type_H_
/*  
wdd9590jj0414

040002760810
135246

*/
namespace FunType
{
	typedef std::list<int> ListInt;
	typedef std::list<std::string> ListStr;
	typedef std::map<int,std::string> MapIntStr;
	typedef std::pair<int,std::string> PairIntStr;
	typedef std::list<PairIntStr> ListPairIntStr;
};

namespace StructType
{
	struct CUser
	{
		int nID;  //
		std::string strName;
	};

	struct CGroup
	{
		int nID;
	};
};
#endif