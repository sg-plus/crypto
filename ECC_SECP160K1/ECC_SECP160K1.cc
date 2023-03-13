#include"ECC_SECP160K1.h"
ECC_SECP160K1::ECC_SECP160K1(){
	NTL::conv(q,"1461501637330902918203684832716283019651637554291");
	NTL::conv(n,"1461501637330902918203686915170869725397159163571");
	NTL::conv(G.x,"338530205676502674729549372677647997389429898939");
	NTL::conv(G.y,"842365456698940303598009444920994870805149798382");
	ecc_a=0;
	ecc_b=7;
}
//点加运算
void ECC_SECP160K1::CxyAdd(Cxy &result,const Cxy &a,const Cxy &b){
	//假设x=y=0为单位元
	if(a.x==0 && a.y==0){
		result.x=b.x; result.y=b.y;
	}else if(b.x==0 && b.y==0){
		result.x=a.x; result.y=a.y;	
	}else if(a.x==b.x && NTL::AddMod(a.y,b.y,n)==0){//点与自身逆元相加
		result.x=0; result.y=0;		
	}else{
		NTL::ZZ m;	//斜率
		//a==y
		if(a.x==b.x && a.y==b.y){
			m=((3*a.x*a.x+ecc_a) * NTL::InvMod((2*a.y)%q,q)) % q;
		}else{
			m=((a.y-b.y) * NTL::InvMod((a.x-b.x)%q,q)) % q;
		}
		result.x=(m*m-a.x-b.x) % q;
		result.y=(m*(b.x-result.x)-b.y) % q;
	}
}
//数乘运算
void ECC_SECP160K1::numMulCxy(Cxy &result,const NTL::ZZ num,const Cxy &a){
	if(num!=0){
		long nBits=NTL::NumBits(num);	//获取num二进制长度
		Cxy tempCxy=a;

		result.x=0; result.y=0;
		for(long i=0;i<nBits;++i){		//获取numModn第i位bit
			if(NTL::bit(num,i)==1){
				if(result.x==0 && result.y==0){
					result.x=tempCxy.x; result.y=tempCxy.y;
				}else{
					CxyAdd(result,result,tempCxy);
				}
			}
			CxyAdd(tempCxy,tempCxy,tempCxy);
		}
	}
}
//数乘生成元
void ECC_SECP160K1::numMulCxy(Cxy &result,const NTL::ZZ num){
	numMulCxy(result,num,G);
}
