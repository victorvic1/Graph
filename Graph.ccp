#define NULL __null
#include "Graph.h"
#define StateFPPointer _StatePointer+_StateLength*2
#define StateAuxPointer _StatePointer+_StateLength

Graph::Graph(bool* StatePointer,StateFunction* StateFunctionPointerFP, StateFunction* StateFunctionPointer ,StateFunction* StateFunctionPointerFN, int StateLength ,	TransiFunction* TransPointer,int TransLength,ConectionStruct* StateToTransPointer,int StateToTransLength,ConectionStruct* TransToStatePointer,int TransToStateLength ){
	_StatePointer = StatePointer;
	_StateFunctionPointerFP = StateFunctionPointerFP;
	_StateFunctionPointer  = StateFunctionPointer;
	_StateFunctionPointerFN  = StateFunctionPointerFN;	
	_StateLength = StateLength ;
	_TransPointer = TransPointer;
	_TransLength = TransLength;
	_StateToTransPointer = StateToTransPointer;
	_StateToTransLength = StateToTransLength;
	_TransToStatePointer = TransToStatePointer;
	_TransToStateLength = TransToStateLength;	
	//Inicializa las variables auxiliares 
	clear();
}
void Graph::run(){
	int x;
	int y;
	for(x=0;x<_StateLength;x++){
		if (*(_StatePointer+x)!=*(StateFPPointer+x)){
			if(!*(_StatePointer+x)){								// Ejecuta el flanco de bajada
				if(*(_StateFunctionPointerFN+x)!=NULL){
					(*(_StateFunctionPointerFN+x))();
				}
			}
		}	
	}	
	for(x=0;x<_StateLength;x++){
		if (*(_StatePointer+x)!=*(StateFPPointer+x)){
			if(*(_StatePointer+x)){								//Ejecuta en el flanco de subida
				if(*(_StateFunctionPointerFP+x)!=NULL){
					(*(_StateFunctionPointerFP+x))();
				}
			}
		}
	}	
	for(x=0;x<_StateLength;x++){
		if (*(_StatePointer+x) && *(StateFPPointer+x)){ //ejecuta de manera continua
			if(*(_StateFunctionPointer+x)!=NULL){			
				(*(_StateFunctionPointer+x))();
			}
		}
		*(StateFPPointer+x)=*(_StatePointer+x);
	}


	
	
	//Ejecuta las transicciones, es un cristo, lo se
	for(x=0;x<_TransLength;x++){
				_ok=true;
			for(y=0;y<_StateToTransLength;y++){
				if(((_StateToTransPointer+y)->Transi)==(_TransPointer+x)){
					if(!*((_StateToTransPointer+y)->State)){
						_ok=false;
						break;
					}
				}
			}
			
			if(_ok){
				if((*(_TransPointer+x))() && (!_ManActive || *(_ManTransPointer)==NULL || ((*_ManTransPointer)()))){ //Comprueba la transiccion y si esta el modo manual tambien la transiccion del modo manual
					for(y=0;y<_StateToTransLength;y++){
						if(((_StateToTransPointer+y)->Transi)==(_TransPointer+x)){
							*((((_StateToTransPointer+y)->State)-_StatePointer)+StateAuxPointer)=false;
						}
					}
					for(y=0;y<_TransToStateLength;y++){
						if(((_TransToStatePointer+y)->Transi)==(_TransPointer+x)){
							*((((_TransToStatePointer+y)->State)-_StatePointer)+StateAuxPointer)=true;
						}
					}
				}
			}	
	}
	//Actualiza los estados segun la varible auxiliar
	for(x=0;x<_StateLength;x++){
		*(_StatePointer+x)=*(StateAuxPointer+x);
	}
}

void Graph::clear(){
	for(int x=0;x<_StateLength;x++){
		clearState(x);
	}		
}
void Graph::setState(int number){
	if(number<_StateLength){
		*(StateAuxPointer+number)=true;
		*(_StatePointer+number)=true;		
	}
}
void Graph::clearState(int number){
	if(number<_StateLength){
		*(StateAuxPointer+number)=false;
		*(_StatePointer+number)=false;		
	}		
}
bool Graph::getState(int number){	
	if(number<_StateLength){
		return *(_StatePointer+number);
	}
	return false;
}

void Graph::manual(TransiFunction* ManTransPointer, bool active){
		_ManTransPointer = ManTransPointer;
		_ManActive = active;	
}
