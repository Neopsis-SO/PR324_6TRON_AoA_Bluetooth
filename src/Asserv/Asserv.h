#ifndef __ASSERV_H__
#define __ASSERV_H__

#include "6TRON_AoA_Bluetooth.h"

#define MAX_LIM_ERR_INTE 10000
#define MIN_LIM_ERR_INTE -10000
#define MAX_LIM_COMMANDE  100
#define MIN_LIM_COMMANDE -100

#define RA 0.11 //distance entre point milieu et la roue en mètre


#define KP_MG 0.58//0.6 //coefficient proportionnel Asserv Vitesse Moteur Gauche 
#define KI_MG 0.02///0.15  //coefficient intégral Asserv Vitesse Moteur Gauche
#define KD_MG 0//0.0045

#define KP_MD 0.58//0.6 //coefficient proportionnel Asserv Vitesse Moteur Droit
#define KI_MD 0.02//0.15 //coefficient intégral  Asserv Vitesse Moteur Droit
#define KD_MD 0//0.0045

#define KP_Pos 0 //0.0007 coefficient proportionnel Asserv Position (Distance)
#define KI_Pos 0//coefficient intégral Asserv Position (Distance)
#define KP_Angle 0.1// 0.00082 coefficient proportionnel Asserv Position (Angle)
#define KI_Angle 0//0.002// 0.000008 coefficient intégral Asserv Position (Angle)

#define PI 3.1415926535
float lissage(const float in,float tab[],int len);
class Asserv 
{
    public:
        Asserv(const float Te);
        void AsservMGMD(const float LectureAngle, const float  LectureDistance, 
        const float ConsAngle, const float ConsDistance, float * CommandeMG, float* CommandeMD,const int Reset);
        float get_vitesseMG();
        float get_vitesseMD();
        //float get_CommandeDistance();
        float get_CommandeAngle();
        float get_ConsingeMG();
        float get_ConsingeMD();
        float CommandeDistance;

    private:
        void range(float*commande, int max, int min); //limite la plage d'une valeur entre min et max
        float Asserv_V_MG(const float VG, const float ConsVG, int reset); //Asserv de Vitesse Moteur Gauche
        float Asserv_V_MD(const float VD, const float ConsVD, int reset); //Asserv de Vitesse Moteur Droit
        float Asserv_Distance(const float Distance, const float ConsDistance,int reset); //Asserv de Position Distance 
        float Asserv_Angle(const float Angle, const float ConsAngle,int reset); //Asserv de Position Angle
        void calcul_vd_vg(const float LectureAngle, const float  LectureDistance); //lectute de la vitesse du moteur gauche et droit 
        //void calcul_v_w(); //lecture de la vitesse et de la vitesse angulaire, en fonction des vitesse angulaire encodeur Wc1 et Wc2
        float Te;
        float vitesseMG;
        float vitesseMD;
        float CommandeAngle;
        float ConsingeMG;
        float ConsingeMD;
        
        
};







#endif // __ASSERV_VITESSE_ANGLE