int portd_pins=255;
int ctr=0;
int sev_seg[13]={135,64,237,249,189,0,222,134,237,243,184,247,238};


void setup()
{
	DDRD=portd_pins;
}

void loop()
{
  for(ctr=0;ctr<=12;ctr++){
  	PORTD=sev_seg[ctr];
    delay(300);
  }
}