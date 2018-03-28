//  
//  main.c  
//  Fourer1D  
//  
//  Created by Tony on 14/11/16.  
//  Copyright (c) 2017妤犵儑鎷穀uhao Wang. All rights reserved.
//  
#include "fft.h"
  
////////////////////////////////////////////////////////////////////  
//閻庤鐭粻鐔哥▔閿熶粙鍤嬪璺虹У閺嗙喓绱掗幘瀵革拷濞达綇鎷�
///////////////////////////////////////////////////////////////////  

////////////////////////////////////////////////////////////////////  
//閻庤鐭粻鐔哥▔閿熶粙鍤嬪璺虹У閺嗙喓鎷嬮敍鍕毈闁挎稑鑻�姗�箯椤戣法顔掓繛澶嬫穿缁辨繈宕濋悩宕囥�闁挎稑鑻崳鍝勨枖閿燂拷
///////////////////////////////////////////////////////////////////  
void Add_Complex(Complex * src1,Complex *src2,Complex *dst){  
    dst->imagin=src1->imagin+src2->imagin;  
    dst->real=src1->real+src2->real;  
}  
void Sub_Complex(Complex * src1,Complex *src2,Complex *dst){  
    dst->imagin=src1->imagin-src2->imagin;  
    dst->real=src1->real-src2->real;  
}  
void Multy_Complex(Complex * src1,Complex *src2,Complex *dst){  
    float r1=0.0,r2=0.0;
    float i1=0.0,i2=0.0;
    r1=src1->real;  
    r2=src2->real;  
    i1=src1->imagin;  
    i2=src2->imagin;  
    dst->imagin=r1*i2+r2*i1;  
    dst->real=r1*r2-i1*i2;  
}  
////////////////////////////////////////////////////////////////////  
//闁革腹锟紽T濞戞搩鍘藉﹢浣圭▔閿熶粙鍤媁N闁汇劌鍩栨繛鍡忓墲閺岀喐銇勯惂鍝ョ闁革负鍔忛崙顖涚閿濆嫯鍘ù鍏肩煯缁楀寮鐘虫殢闁告帒搴滅槐婵嬪礂閾氬倻绉奸悷娆庤兌閻ｈ鈻旈弴鈽嗗殯闁哄嫸鎷�
///////////////////////////////////////////////////////////////////  
void getWN(float n,float size_n,Complex * dst){
    float x=2.0*M_PI*n/size_n;
    dst->imagin=-sin(x);  
    dst->real=cos(x);  
}  

////////////////////////////////////////////////////////////////////  
//閻庤鐭粻鐑T闁汇劌瀚崹鍨叏鐎ｎ亜顕ч柡浣哄瀹撲線鏁嶇仦鑺ョ濞戞挾鐦濬T闁汇劌瀚弳鐔煎箲椤斿墽鐥呴弶鈺佹喘閸ｆ悂寮悧鍫熜侀悘蹇撳缁辨繈鏌呴幒鎴犵Ш缂備焦鎸婚悗锟�///////////////////////////////////////////////////////////////////
int FFT_remap(float * src,int size_n){
	int i;
    if(size_n==1)  
        return 0;  
    float temp[16] = {0};
    for(i=0;i<size_n;i++)
        if(i%2==0)  
            temp[i/2]=src[i];  
        else  
            temp[(size_n+i)/2]=src[i];  
    for(i=0;i<size_n;i++)
        src[i]=temp[i];  
//    free(temp);
    FFT_remap(src, size_n/2);  
    FFT_remap(src+size_n/2, size_n/2);  
    return 1;  
  
  
}  
////////////////////////////////////////////////////////////////////  
//閻庤鐭粻鐑T闁挎稑鑻崣鎸庢媴閹捐鐎紒鐘愁殱绾墎鎷犵�妯活瀽闁挎稑鏈弫鐐烘煂婵犲啫绔撮柣銊ュ濡绮堝ú顏勫姤闁告帒妫旂拹鐔煎极閻楀牆绁﹂柡鍕⒔閵囨岸鏁嶇仦钘夎濞寸姰鍎撮‖浣猴拷閻旇櫣娉㈤柡瀣舵嫹
///////////////////////////////////////////////////////////////////  
void FFT(float * src,Complex * dst,int size_n){
      
    FFT_remap(src, size_n); 
    printf("fft start \n"); 
    int i,j;
    int k=size_n;  
    int z=0;  
    while (k/=2) {  
        z++;  
    }  
    k=z;  
    if(size_n!=(1<<k))  
        exit(0);  
    Complex src_com[16];
    if(src_com==NULL)  
        exit(0);  
    for(i=0;i<size_n;i++){
        src_com[i].real=src[i];  
        src_com[i].imagin=0;  
    }  
    for(i=0;i<k;i++){
        z=0;  
        for(j=0;j<size_n;j++){
            if((j/(1<<i))%2==1){  
                Complex wn;  
                getWN(z, size_n, &wn);  
                Multy_Complex(&src_com[j], &wn,&src_com[j]);  
                z+=1<<(k-i-1);  
                Complex temp;  
                int neighbour=j-(1<<(i));  
                temp.real=src_com[neighbour].real;  
                temp.imagin=src_com[neighbour].imagin;  
                Add_Complex(&temp, &src_com[j], &src_com[neighbour]);  
                Sub_Complex(&temp, &src_com[j], &src_com[j]);  
            }  
            else  
                z=0;  
        }  
      
    }  
      
   for(i=0;i<size_n;i++)
   {
        if(src_com[i].imagin>=0.0){ 
            printf("%d+%dj\n",(int)(src_com[i].real * 1000000),(int)(src_com[i].imagin * 1000000));
        } 
        else 
            printf("%d%dj\n",(int)(src_com[i].real * 1000000),(int)(src_com[i].imagin * 1000000));
   }
        
    for(i=0;i<size_n;i++){
        dst[i].imagin=src_com[i].imagin;  
        dst[i].real=src_com[i].real;  
    }
}  
