#include "AsservTask.h"
#include "moteur.h"
#include "Asserv.h"


// Timer timer;
// Ticker time_up;
float Te=0.001;



Moteur MoteurG(ICAPT1,PWM3_OUT);
Moteur MoteurD(PWM2_OUT,PWM1_OUT);
Asserv Asserv(Te);

void function_Asserv(void){

    static int  reset =0;
    static float LectureAngle=0;
    static float LectureDistance=0;
    static float LectureDistance2=0;
    

    static float ConsAngle=0;
    static float ConsDistance=0;//5

    static float CommandeMG=0;
    static float CommandeMD=0;
    static float CommandeDistance=0;
    static float CommandeAngle=0;
    static float ConsingeMG=0;
    static float ConsingeMD=0;
    static float VitesseMG=0;
    static float VitesseMD=0;

    if(xSemaphoreAsserv.try_acquire())
    {
        LectureAngle=globalMessageUBLOX.angle_azimuth;
        LectureDistance=globalMessageUBLOX.rssi_pol1;
        if(LectureDistance>-55){
            LectureDistance2 = 0;
        }
        if(LectureDistance<-65){
            LectureDistance2 = -0.1;
        }
        //LectureDistance=0;
        xSemaphoreAsserv.release();
    }
    Asserv.AsservMGMD(LectureAngle,LectureDistance2,ConsAngle,ConsDistance,&CommandeMG,&CommandeMD,reset);
    VitesseMG=Asserv.get_vitesseMG();
    VitesseMD=Asserv.get_vitesseMD();
    CommandeAngle=Asserv.get_CommandeAngle();
    CommandeDistance=Asserv.get_CommandeDistance();
    ConsingeMG=Asserv.get_ConsingeMG();
    ConsingeMD=Asserv.get_ConsingeMD();
    MoteurG.Speed(CommandeMG/100);
    MoteurD.Speed(CommandeMD/100);
    //printf(">LectureAngle:");
   // printf("%f\n",LectureAngle);
    printf(">LectureRSSI:");
    printf("%f\n",LectureDistance);
    printf(">LectureRSSI2:");
    printf("%f\n",LectureDistance2);
    /*printf(">ConsingeMG:");
    printf("%f\n",ConsingeMG);
    printf(">ConsingeMD:");
    printf("%f\n",ConsingeMD);
    printf(">VG:");
    printf("%f\n",VitesseMG);
    printf(">VD:");
    printf("%f\n",VitesseMD);*/
  
}

osStatus ASSERV_TaskInit (void)
{
    return osOK;
}

void ASSERV_Task()
{
    // timer.start();
    // time_up.attach(&function_Asserv, Te);
    while(true)
    {
        function_Asserv();
        // printf("AsservTask launched\n");
        
        ThisThread::sleep_for(ASSERV_SLEEP_TASK);
    }

}



