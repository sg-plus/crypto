#ifndef ECC_SECP160K1_CC
#define ECC_SECP160K1_CC

#include<iostream>
#include<NTL/ZZ.h>
#include<cstdlib>

typedef struct Coordinate{
	NTL::ZZ x;//坐标x值
	NTL::ZZ y;//坐标y值
}Cxy;

class ECC_SECP160K1{
	NTL::ZZ q;//有限域q
	NTL::ZZ n;//椭圆曲线群阶
	NTL::ZZ ecc_a;//椭圆曲线参数a
	NTL::ZZ ecc_b;//椭圆曲线参数b
	Cxy G;
public:
	ECC_SECP160K1();
	//点加运算
	//param:
	//1、点加结果
	//2、点加参数1
	//3、点加参数2
	void CxyAdd(Cxy &,const Cxy &,const Cxy&);
	//数乘运算
	void numMulCxy(Cxy &,const NTL::ZZ,const Cxy &);
	void numMulCxy(Cxy &,const NTL::ZZ);//数乘生成元
	//生成一个0~n-1之间的随机数
	NTL::ZZ getRandNum(){
		NTL::SetSeed(NTL::ZZ(static_cast<unsigned>(time(nullptr))));
		return NTL::RandomBnd(n);	
	}

};

#endif
