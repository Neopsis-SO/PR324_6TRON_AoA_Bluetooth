#include "mbed.h"
#include "Asserv.h"




float lissage(const float in,float tab[],int len)
{ 
  float Sum=0;
  for(int i=0; i<5; i++){
    tab[i]=tab[i+1];
  }
  tab[len-1]=in;
  for(int i=0; i<len; i++){
    Sum=Sum+tab[i];
  }
  return  (Sum/len);
}
Asserv::Asserv(const float Te)
{
  this->Te =Te;
}
void Asserv::range(float*commande, int max, int min)
{
  if(*commande>max)
    {
      *commande=max;
    }
  if(*commande<min)
    {
      *commande=min;
    }
}

void Asserv::calcul_vd_vg(const float LectureAngle, const float LectureDistance)
{
    vitesseMG= (LectureDistance/Te)-(LectureAngle*(PI/180)/Te)*RA; //vitesse roue gauche m/s
    vitesseMD= (LectureAngle*(PI/180)/Te)*RA+(LectureDistance/Te); //vitesse roue droite m/s
}
/*
void Asserv::calcul_v_w()
{
    vitesseRobot=(vitesseMG+vitesseMD)/2;//vitesse du robot m/s
    viesseAngulaireRobot=(vitesseMD-vitesseMG)/RA*2; //vitesse angulaire robot rad/s
}
*/

float Asserv::Asserv_V_MG(const float VG, const float ConsVG, int reset)
{float Err=0;
  float static S_Err=0;
  float Commande=0;
  float static lastValue=0;
  if(reset==1){
    S_Err=0;
    Commande=0;
  }else{
    Err=(ConsVG-VG);
    float D_Err = (Err - lastValue)/Te;
    S_Err=S_Err+Err*Te;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_MG*Err+KI_MG*S_Err+KD_MG*D_Err;
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
    lastValue =Err;
  }
  return  Commande;
}

float Asserv::Asserv_V_MD(const float VD, const float ConsVD, int reset)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  float static lastValue=0;
  if(reset==1){
    S_Err=0;
    Commande=0;
  }else{
    Err=(ConsVD-VD);
    float D_Err = (Err - lastValue)/Te;
    S_Err=S_Err+Err*Te;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_MD*Err+KI_MD*S_Err+KD_MD*D_Err;
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
    lastValue =Err;
  }
  return  Commande;
}
float Asserv::Asserv_Distance(const float Distance, const float ConsDistance,int reset)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  if(reset==1){
      S_Err=0;
      Commande=0;
  }else{
    Err=ConsDistance-Distance;
    S_Err=S_Err+Err;
    range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
    Commande=KP_Pos*Err+KI_Pos*S_Err;
    range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  }
  return Commande;
}

float Asserv::Asserv_Angle(const float Angle, const float ConsAngle,int reset)
{
  float Err=0;
  float static S_Err=0;
  float Commande=0;
  Err=ConsAngle-Angle;
  S_Err=S_Err+Err;
  range(&S_Err,MAX_LIM_ERR_INTE, MIN_LIM_ERR_INTE);
  Commande=KP_Angle*Err+KI_Angle*S_Err;
  range((&Commande),MAX_LIM_COMMANDE,MIN_LIM_COMMANDE);
  return Commande;
}

float Asserv::get_vitesseMG(){return vitesseMG;}
float Asserv::get_vitesseMD(){return vitesseMD;}
float Asserv::get_CommandeDistance(){return CommandeDistance;}
float Asserv::get_CommandeAngle(){return CommandeAngle;}
float Asserv::get_ConsingeMG(){return ConsingeMG;}
float Asserv::get_ConsingeMD(){return ConsingeMD;}

void  Asserv::AsservMGMD(const float LectureAngle, const float  LectureDistance, 
const float ConsAngle, const float ConsDistance, float * CommandeMG, float* CommandeMD,const int Reset)
{
  calcul_vd_vg(LectureAngle,LectureDistance);
  CommandeDistance=Asserv_Distance(LectureDistance,ConsDistance,Reset); //0.1
  CommandeAngle =Asserv_Angle(LectureAngle,ConsAngle,Reset);
  ConsingeMG=((CommandeDistance/Te)-(CommandeAngle*(PI/180)/Te)*RA);
  ConsingeMD=((CommandeAngle*(PI/180)/Te)*RA)+((CommandeDistance/Te));
  *CommandeMG= Asserv_V_MD(vitesseMG,ConsingeMG,Reset);
  *CommandeMD=Asserv_V_MG(vitesseMD,ConsingeMD,Reset);
}




