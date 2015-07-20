/*
Autor:Victor Perez Domingo


*/
#ifndef Graph_h
#define Graph_h
#define NULL __null

typedef void (*StateFunction)();
typedef bool (*TransiFunction)();
struct ConectionStruct{
	bool* State;
	TransiFunction* Transi;
};
	
	
class Graph
{
  public:	
	//Inicializa el graphcet
	Graph(bool* StatePointer,StateFunction* StateFunctionPointerFP, StateFunction* StateFunctionPointer ,StateFunction* StateFunctionPointerFN, int StateLength ,	TransiFunction* TransPointer,int TransLength,ConectionStruct* StateToTransPointer,int StateToTransLength,ConectionStruct* TransToStatePointer,int TransToStateLength );
	//Ejecuta el graphcet.
	void run();
	//Apaga todos los estados del graphcet
	void clear();
	//Permite encender un estado cualquiera
	void setState(int number);
	//Permite apagar un estado cualquiera
	void clearState(int number);
	//Permite conocer si un estado esta activo o no.
	bool getState(int number);
	//activa el modo manual para la transiccion entre estados.
	//simplemente permite añadir una nueva condicion a todas las transicciones.
	void manual(TransiFunction* ManTransPointer, bool active);
	
  private:
	bool _ok; //variable auxiliar;
    StateFunction* _StateFunctionPointer;
	StateFunction* _StateFunctionPointerFP;
	StateFunction* _StateFunctionPointerFN;
	bool* _StatePointer;
	int _StateLength;
	TransiFunction* _TransPointer;
	int _TransLength;
	ConectionStruct* _StateToTransPointer;
	int _StateToTransLength;		
	ConectionStruct* _TransToStatePointer;
	int _TransToStateLength;	
	TransiFunction* _ManTransPointer = NULL;
	bool _ManActive = false;
};
#endif
