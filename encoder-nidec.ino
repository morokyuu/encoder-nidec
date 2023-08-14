const int encA = 2;
const int encB = 3;
static int thisstate = 0;
static int oldstate = 0;
static long _position = 0;
const int8_t sttable[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

void tick_enc(void){
  int A = digitalRead(encA);
  int B = digitalRead(encB);

  thisstate = 0;
  if(A){ thisstate |= 0x02; }
  if(B){ thisstate |= 0x01; }
  int8_t st = oldstate<<2 | thisstate;
  _position += sttable[st];

  oldstate = thisstate;
  Serial.print((float)_position * 360.0 / (50.0 * 4));
  Serial.print(", ");
  Serial.println(_position);
}

void func_encA(void){
  tick_enc();
}

void func_encB(void){
  tick_enc();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(encA,INPUT);
  pinMode(encB,INPUT);
  digitalWrite(encA, INPUT_PULLUP);
  digitalWrite(encB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA),func_encA,CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB),func_encB,CHANGE);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

}
