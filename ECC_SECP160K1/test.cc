#include<iostream>
#include<sys/time.h>
#include"ECC_SECP160K1.h"

using namespace std;
using namespace NTL;

int main(){
	ECC_SECP160K1 ecc;
	ZZ r1,r2;
	Cxy result1,result2,result3;
	//获取两个随机数并生成两个点
	r1=ecc.getRandNum();
	r2=ecc.getRandNum();
	ecc.numMulCxy(result1,r1);
	ecc.numMulCxy(result2,r2);
	//进行1000次点加运算，并记录所需时间
	timeval t1,t2;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次点加运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		ecc.CxyAdd(result3,result1,result2);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;
	
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次数乘运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		ecc.numMulCxy(result3,r1,result2);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;

	return 0;
}
