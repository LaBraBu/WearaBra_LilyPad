const int buzpin = 10;
const int Cfre   = 2093; // ドの周波数
const int Dfre   = 2349; // レの周波数
const int Efre   = 2637; // ミの周波数
const int Ffre   = 2794; // ファの周波数
const int Gfre   = 3136; // ソ
const int Afre   = 3520; // ラ
const int Bfre   = 3951; // シ

void setup() {
    pinMode(buzpin, OUTPUT);
}

/**
 * @param int  buzpin ポート番号
 * @param int  fre    音の周波数
 * @param long timel1 ならす時間[msec]
 */
void beep (int buzpin, int fre, long time){ // the sound producing 
    int x; 
    long delayHL = (long)(1000000/fre/2); 
    long loopn   = (long)((time*1000)/(2*delayHL));
    for (x=0;x<loopn;x++) {
        digitalWrite(buzpin,HIGH); 
        delayMicroseconds(delayHL); 
        digitalWrite(buzpin,LOW); 
        delayMicroseconds(delayHL);
    }
}

void loop(){
    beep(buzpin,Cfre,250); //C: 
    delay(590); 
    beep(buzpin,Dfre,250); //D 
    delay(590);
    beep(buzpin,Efre,250); //E 
    delay(590);
    beep(buzpin,Ffre,250);  //F
    delay(590);
}
