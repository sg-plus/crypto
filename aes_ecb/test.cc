#include<iostream>
#include<NTL/ZZ.h>
#include<openssl/aes.h>
#include<sys/time.h>
using namespace std;
using namespace NTL;

int main(){
	ZZ keyZZ;
	unsigned char keyC[32],data[16]="hello world!",pText[16],cText[16];
	AES_KEY keyE,keyD;
	keyZZ = RandomBits_ZZ(256);
	BytesFromZZ(keyC,keyZZ,32);

	AES_set_encrypt_key(keyC,256,&keyE);
	AES_set_decrypt_key(keyC,256,&keyD);
	timeval t1,t2;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次aes加密运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		AES_ecb_encrypt(data,cText,&keyE,AES_ENCRYPT);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次aes解密运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		AES_ecb_encrypt(cText,pText,&keyD,AES_DECRYPT);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;

	//cout<<pText<<endl;


        return 0;
}
