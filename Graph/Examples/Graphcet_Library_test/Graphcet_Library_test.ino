#include <Graph.h>

/* Grafcet stats */
#define StatesLength 3 //Number of states
#define TransiLength 3 //Number of transitions 
#define ConnectionsSTT 3 //Number of connections State To Transi
#define ConnectionsTTS 3 //Number of connections Transi To State
/*memory*/
bool States[StatesLength*3]; //you need 3 
/*
function assing
Use NULL when you don't want to do anything
use void for States and Bool for Transitions
*/
TransiFunction Transi[TransiLength]={T1,T2,T3};					//transitions functions
StateFunction StatesAction[StatesLength] = {S1,S2,S3};			//State functions
StateFunction StatesFPAction[StatesLength] ={S1FP,NULL,S3FP};	//State setup functions
StateFunction StatesFNAction[StatesLength] ={NULL,NULL,NULL};	//State exit functions
	/*Optional*/
TransiFunction TransiMan = manT;								//Manual transition 
	
	/*Connections*/
ConectionStruct StateToTransi[ConnectionsSTT] ={
	{&States[0],&Transi[0]}, //from State 0 to Transi 0
	{&States[1],&Transi[1]}, //from State 1 to Transi 1
	{&States[2],&Transi[2]}	
};
ConectionStruct TransiToState[ConnectionsTTS] ={  /*Watch out here*/
	{&States[1],&Transi[0]}, //from transi 0 to State 1  
	{&States[2],&Transi[1]}, //from transi 1 to State 2
	{&States[0],&Transi[2]}		
};

/* Grafcet declaration*/
Graph graph(States, StatesFPAction , StatesAction ,StatesFNAction , StatesLength,Transi,TransiLength,StateToTransi,ConnectionsSTT,TransiToState,ConnectionsTTS );

#define botonPin 2
#define botonStepPin 3

void setup()
{
	pinMode(13,OUTPUT);
	pinMode(12,OUTPUT);
	pinMode(11,OUTPUT);	
	pinMode(botonPin,INPUT_PULLUP);	
	pinMode(botonStepPin,INPUT_PULLUP);		
	graph.setState(1);						//Grafcet initial State
	graph.manual(&TransiMan,true);			//Grafcet manual enabled with TransiMan transition
}
bool FPB = false;
bool FPB2 = false;
void loop()
{
	// FP calculate from b1 and b2
	static bool aux = false;
	bool b = !digitalRead(botonPin);
	FPB=aux!=b && aux==false;
	aux=b;
	static bool aux2 = false;
	bool b2 = !digitalRead(botonStepPin);
	FPB2= aux2!=b2 && aux2==false;
	aux2=b2;	
	
	graph.run(); //Execute the grafcet
}
unsigned long Ti0 = 0; //Timers
unsigned long Ti1 = 0;
void S1FP(){			
		digitalWrite(13,HIGH);
		Ti0 = millis();			//Reset the timer when we enter in state 1
}
void S3FP(){
		digitalWrite(13,LOW);
		Ti1 = millis();
}
void S1(){
		digitalWrite(11,LOW);
		digitalWrite(12,LOW);

}
void S2(){
	digitalWrite(11,LOW);	
	digitalWrite(12,HIGH);
		
}
void S3(){
	digitalWrite(11,HIGH);	
	digitalWrite(12,LOW);		

}
bool T1(){
	if (millis()-Ti0>1000){	// test the timer and return true when reach 1000ms
		return true;
	}
	return false;
}
bool T2(){
	if(FPB){
		return true;
	}
	return false;
}
bool T3(){
	if (millis()-Ti1>1000){
		return true;
	}
	return false;
}
bool manT(){
	return !digitalRead(botonStepPin);	 //Manual button configuration
}
