const int buzpin = 10;
const int C   = 4186; // ド
const int B   = 3951; // シ
const int Bf  = 3729; // シb
const int A   = 3520; // ラ
const int G   = 3156; // ソ
const int F   = 2794; // ファ
const int Ef  = 2489; // ミb

void setup() {
    pinMode(buzpin, OUTPUT);
    Serial.begin(9600);
}

/**
 * @param int  buzpin ポート番号
 * @param int  fre    音の周波数
 * @param long timel1 msec
 */
 long t1,t2,t3,ta,tb;
void beep (int buzpin, int fre, long timel1){ // the sound producing 
    int x; 
    long delayHL = (long)(1000000/fre/2); 
    long loopn   = (long)((timel1*1000)/(2*delayHL));
    for (x=0;x<loopn;x++) {
        digitalWrite(buzpin,HIGH); 
        delayMicroseconds(delayHL); 
        digitalWrite(buzpin,LOW); 
        delayMicroseconds(delayHL);
    }
    delay(5);
}

void buzSuccess(){
    beep(buzpin,F,100);
    beep(buzpin,F,100);
    beep(buzpin,F,100);
    beep(buzpin,F,75);
    delay(125); 
    beep(buzpin,Ef,75); 
    delay(125);
    beep(buzpin,G,75); 
    delay(125);
    beep(buzpin,F,300);
    delay(400);
}
void loop(){
    buzSuccess();
}
