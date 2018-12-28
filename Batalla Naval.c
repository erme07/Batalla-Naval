#include <stdio.h>
#include <stdlib.h>			//librerias usadas para el proyecto
#include <time.h>

#define fil 10			//numeros de filas
#define col 36			//numero de columnas


//prototipos de las funciones usadas:
void iniciar(char tablero[fil][col]);     				//(en construccion)                 
void campo(char tablero[fil][col]);
void mostrar(char tablero[fil][col]);
int maquina(char tablero[fil][col],int mem_maquina[2],char ia[3][3]);   //(en construccion)
void colocar(char tablero[fil][col]);									//(en construccion)
void camp_enemigo(char tablero[fil][col]);     									
int x_derecha(char tablero[fil][col], int x, int y, int ocupado, int f);           
int x_izquierda(char tablero[fil][col], int x, int y, int ocupado, int f);
int y_abajo(char tablero[fil][col], int x, int y, int ocupado, int f);
int y_arriba(char tablero[fil][col], int x, int y, int ocupado, int f);
void misil(char tablero[fil][col]);

int main() {
	
	
	char tablero[fil][col];
	
	iniciar(tablero);
	
	return 0;
}

void iniciar(char tablero[fil][col]){   //funcion principal que llama a todas las funciones secundarias(incompleta)
	
	int i;
	
	campo(tablero);
	camp_enemigo(tablero);
	mostrar(tablero);
	for(i=0;i<20;i++){
		
		misil(tablero);
		system("cls");
		mostrar(tablero);
	}
}

void campo(char tablero[fil][col]){  //inicializa el tablero con los numeros y letras de referencia ,division de campo, etc
	
	int i,j,aux1=48,aux2=48;
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			if(i==0){
				if(aux1==58){
					aux1=aux1+39;
				}
				tablero[i][j]=aux1;
				
			}
			else if(j==0){
				tablero[i][j]=aux2;
				
			}
			else if(j==18 && i>=1){
				tablero[i][j]='|';
			}
			else{
				tablero[i][j]='.';
			}
			aux1++;
		}
		aux2++;
	}
	
	//vector[][];
}

void mostrar(char tablero[fil][col]){           //muestra el tablero de juego
	
	int i,j;
	printf("\n    ");
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			if(tablero[i][j]=='O'){
				printf(". ");                          //invisibiliza los buques enemigos
				//printf("%c ",tablero[i][j]);        //visibiliza los buques enemigos
				
			}
			else{
				printf("%c ",tablero[i][j]);
			}
			
		}
		printf("\n\n    ");
	}
}

int maquina(char tablero[fil][col],int mem_maquina[2],char ia[3][3]){    //define la direccion de misiiles de la maquina(incompleto)
	
		int co,fi;
	
	srand(time(NULL));
	co=1+rand()%19;
	fi=1+rand()%10;
	
	if(mem_maquina[0]==0 && mem_maquina[1]==0){
		if(tablero[fi][co]==' '){
		tablero[fi][co]='*';
		return mem_maquina;
		}
		else if(tablero[fi][co]=='O'){
			tablero[fi][co]='X';
			mem_maquina[0]=fi;
			mem_maquina[1]=co;
			return mem_maquina;
		}
	
	}else{
		
		
	}
	
}

void colocar(char tablero[fil][col]){     //selecciona la posicion de los buques aliados(incompleta)
	
	int x,y,opcion;
	
	printf("Colocar buques de 5 espacios\n");
	printf("ingrese las cordenadas iniciales del buque\n");
	printf("Cordenada X : ");
	scanf("%d",&x);
	printf("\nCordenada Y : ");
	scanf("%d",&y);
	printf("\nIzq = 1   Der = 2  Arriba=3   Abajo=4\n");
	printf("Escoja una opcion: ");
	scanf("%d",&opcion);
	
	
	
}	



	
void camp_enemigo(char tablero[fil][col]){    //selecciona aleatoriamente la posicion de los buques enemigos
	
	int i, j, x, y, aux, f=7, ocupado=0, var=0;
	
		srand(time(NULL));
		
		for(i=0;i<4;i++){       //bucle de 4 ciclos que graba 4 buques de f-1 numero de casillas (f=7)
			do{
				x = 19 + rand() % 17;      //valores aleatorios para definir una direccion en la matriz
				y = 1 + rand() % 9;
				
				aux = 1 + rand() % 2;      //valor aleatorio para seleccionar una opcion al azar dentro del switch
				
				switch(aux){
					case 1:{
						var = x_derecha(tablero, x, y, ocupado, f ); //llama a la funcion, si un bloque de 6 casillas cabe a la derecha de la direccion
						if(var == 0){                                // escogida al azar entonces la funcion devuelve 0, si no hay espacio a la derecha 
							break;                                   //o ya hay alguna casilla ocupada por un buque, devuelve 1
						}
						else if (var == 1){
							var = x_izquierda(tablero, x, y, ocupado, f );   //si la anterior llamada devolvio 1, prueba llamando a otra funcion
							if(var == 0){                                    //esta funcion verifica que quepa el bloque de 6 casillas a la izq. de
								break;                                       //la direccion aleatoria, devuelve 0 o 1 segun el resultado
							}
						}
					}
					case 2:{
						var = y_abajo(tablero, x, y, ocupado, f );      //si niguna de las llamadas anteriores funciona, automaticamente se activan las de abajo  
						if(var == 0){                                   //hasta que alguna encuentre  un lugar donde si haya lugar para el bloque de 6 casillas
							break;                                      //esta funcion verifica si cabe el bloque de 6 en direccion ascendente
						}else if (var == 1){
							var = y_arriba(tablero, x, y, ocupado, f );  //si no funciono la enterior esta funcion verifica si el bloque de 6 casillas
							if(var == 0){                                //cabe en direccion descendente a la posicion en la matriz escogida al azar
								break;                                   //si no funciona se acaba el switch con var valiendo 1
							}
						}
					}
				}		
			}while(var == 1);     //si var vale 1 significa que ninguna funcion anterior logro encontrar espacio para el bloque
		}                         //entonces el bucle se repite escogiendo nuevos valores aleatorio y comprobar si hay espacio
	                              //el ciclo se repetira hasta que encuentre lugar donde poner el bloque
	
	
		f=5;    //le cambio el valor a f para que ahora los bloques sean de 4 espacios;
	
		for(i=0;i<3;i++){    //vuekvo a inicar el mismo bucle anterior pero esta vez para ubicar 3 bloques de 4 espacios
			do{
				x = 19 + rand() % 17;
				y = 1 + rand() % 9;
				aux = 1 + rand() % 2;
			
				switch(aux){
					case 1:{
						var = x_derecha(tablero, x, y, ocupado, f );
						if(var == 0){
							break;
						}
						else if (var == 1){
							var = x_izquierda(tablero, x, y, ocupado, f );
							if(var == 0){
								break;
							}
						}
					
					}
					case 2:{
						var = y_abajo(tablero, x, y, ocupado, f );
						if(var == 0){
							break;
						}else if (var == 1){
							var = y_arriba(tablero, x, y, ocupado, f );
							if(var == 0){
								break;
							}
						}
					}
				}	
		}while(var == 1);
	}
	
	f=3; //estblezco un valor de 2 casillas para los bloques
	
	for(i=0;i<2;i++){       //	ahora el ciclo buscara lugar para 2 bloques de 2 espacios
		do{
			x=19 + rand()%17;
			y=1 + rand()%9;
			aux=1+rand()%2;
			
			switch(aux){
				case 1:{
					var= x_derecha(tablero,x,y,ocupado,f);
					if(var==0){
						break;
					}
					else if (var==1){
						var= x_izquierda(tablero,x,y,ocupado,f);
						if(var==0){
							break;
						}
					}
				}
				case 2:{
					var= y_abajo(tablero,x,y,ocupado,f);
					if(var==0){
						break;
					}
					else if (var==1){
						var= y_arriba(tablero,x,y,ocupado,f);
						if(var==0){
							break;
						}
					}
				}
			}		
		}while(var==1);
	}		
}


int x_derecha(char tablero[fil][col], int x, int y, int ocupado, int f){  //verifica si hay lugar para un bloque de f espacios a la derecha de la posicion [y][x] de la matriz
	int i,j,seteo=0;
	
		for(j=1;j<f;j++){                    
				if(seteo==0){
						for(i=1;i<f;i++){
							if(tablero[y][x+i]=='O'|| x+(f-1)>35){
								ocupado=1;
								return ocupado;   //si no encontro espacio o ya habia un buque en el lugar devuelve 1
							}
						}
					
				}

				seteo=1;
				tablero[y][x+j]='O';
				ocupado=0;
			}
	return ocupado;	 //si encontro espacio libre y asigno correctamente el lugar para el buque entonces devuelve 0
}

int x_izquierda(char tablero[fil][col], int x, int y, int ocupado, int f){  //verifica si hay lugar esta vez a la izquierda 
	int i,j,seteo=0;
	
	for(j=1;j<f;j++){                    // eje x izq
				if(seteo==0){
					for(i=1;i<f;i++){
						if(tablero[y][x-i]=='O'|| x-(f-1)<19){
							ocupado=1;
							return ocupado;
						}
					}
					
				}
				seteo=1;
				tablero[y][x-j]='O';
				ocupado=0;
			}
	
	return ocupado;
}

int y_abajo(char tablero[fil][col], int x, int y, int ocupado, int f){  //verifica si hay lugar en direccion vertical hacia abajo
	int i,j,seteo=0;
	for(j=1;j<f;j++){                    //eje y abajo
				if(seteo==0){
					for(i=1;i<f;i++){
						if(tablero[y+i][x]=='O'|| y+(f-1)>9){
							ocupado=1;
							return ocupado;
						}
					}
					
				}
				seteo=1;
				tablero[y+j][x]='O';
				ocupado=0;
			}
	
	return ocupado;
}

int y_arriba(char tablero[fil][col], int x, int y, int ocupado, int f){  //busca lugar en forma vertical hacia arriba
	int i,j,seteo=0;
	for(j=1;j<f;j++){                     //eje y arriba
				if(seteo==0){
					for(i=1;i<f;i++){
						if(tablero[y-i][x]=='O'|| y-(f-1)<1){
							ocupado=1;
							return ocupado;
						}
					}
				}
		seteo=1;
		tablero[y-j][x]='O';
		ocupado=0;
	}
	
	return ocupado;	
}



void misil(char tablero[fil][col]){     //establece la direccion y el resultado de los misiles propios en campo contrario
	
	int x,y,i,cont=0;
	char cx,cy;
	
	do{
		printf("\n    Direccion del misil\n\n");
		printf("    ingrese la coordenada X: ");
		fflush(stdin);
		cx=getche();
		
		for(i=19;i<col;i++){
			if(tablero[0][i]==cx){
				x=i;
				break;
			}else if(i==35){
				system("cls");
				mostrar(tablero);
				printf("\n    INGRESE UNA DIRECCION VALIDA!!\n");
				x=40;
			}
		}
		
	}while(x<19||x>36);
	
	
	do{
		if(cont==0){
			system("cls");
			mostrar(tablero);
		}
		printf("\n    Direccion del misil\n\n");
		printf("    ingrese la coordenada y: ");
		fflush(stdin);
		//scanf("%c",&cx);
		cy=getche();
		
		for(i=1;i<fil;i++){
			if(tablero[i][0]==cy){
				y=i;
				break;
			}else if(i==9){
				system("cls");
				mostrar(tablero);
				printf("\n    INGRESE UNA DIRECCION VALIDA!!\n");
				cont++;
			}
		}
		
	}while(y<1||y>9);
	
	
	if(tablero[y][x]=='O'){
		tablero[y][x]='X';
		printf("\a");
	}
	else{
		tablero[y][x]=' ';
	}
	
}


