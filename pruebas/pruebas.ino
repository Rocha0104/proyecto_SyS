//

int pulsador=2; //colocar resistencia pull up

int u;

double xk=0;

double uk_1=0;

double xk_1=0;

double uk_2=0;

double xk_2=0; 

int i=1;



void setup() {

  Serial.begin(9600);

  pinMode(pulsador, INPUT);//colocar resistencia pull up

}

void loop() {

  xk=uk_1*0.05984 +uk_2*0.05787+ xk_1*1.787-xk_2*0.9048; //T=0.25 seg

  //xk=uk_1*0.2247 +uk_2*0.2099+ xk_1*1.384-xk_2*0.8187; //T=0.5 seg

  uk_1=10*u;

  uk_2=0;

  xk_2=0;

  if (i>1) {

    uk_2=uk_1;

    xk_2=xk_1; 

  }

  u=digitalRead(pulsador);

  xk_1=xk;

  i=i+1;

  Serial.println(xk);

  delay(250);   // segun T  

}