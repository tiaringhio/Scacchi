#include <iostream>
#include <string>
#include <fstream>

using namespace std;
typedef enum {pawn,rook,bishop,knight,queen,king,noPiece} Pezzo;
typedef enum {white,black,noColor} Colore;

struct Cella {
	Pezzo pezzo;
	Colore colore;
};

typedef Cella Scacchiera[8][8];

// coordinate scacchistiche
struct Ccoord {
	char col;	// 'a' .. 'h'	da sinistra
	int riga;	// 1 .. 8 		dal "basso"
};

// coordinate matrice
struct Mcoord {
	int riga;	// 0 .. 7		dall'alto
	int col;	// 0 .. 7 		da sinistra
};

// inserisce celle vuote in tutta la scacchiera
void vuotaScacchiera(Scacchiera s);

 //prendo in input da file di testo i pezzi da inserire nella scacchiera
void inserisciPezzi(Scacchiera s);

// converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p);

// converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p);

// converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord);

// converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord);

int main () {
	Scacchiera s; //creo una variabile di tipo Scacchiera
	char *pezzi[] ={"pawn","rook","bishop","knight","queen","king","NoPiece"}; //array che mi servirà per la stampa dei vari pezzi
	char *colori[] ={"white","black","NoColor"};//array per la stampa del Colore dei vari pezzi
	vuotaScacchiera(s); //inserisco nella scacchiera delle celle vuote
	inserisciPezzi(s); //prendo in input da file di testo i pezzi da inserire nella scacchiera
	cout<<"Mosse scritte sul file 'mosse.txt'"<<endl;
	std::ofstream f1; //creo l'ofstream per la scrittura sul file mosse.txt f1:nome logico
	f1.open("mosse.txt");//apro il file mosse.txt:nome fisico
	f1<<"Fava Riccardo 287516 - Ricci Mattia 285237"<<endl; //scrivo sul file
	Ccoord sc_coord,new_cord; //variabili coordinate scacchistiche
	Mcoord m_coord,old_cord;//variabili coordinate matriciali
	int incr_x;// incremento della x
	int incr_y;//incremento della y
	int righe=8; //lunghezza colonne matrice
	int colonne=8; //lunghezza righe matrice
	int delta_x,delta_y; // delta per lo spostamento di cella in cella, variano a seconda del pezzo
	bool move; //variabile booleana per verificare se il pezzo puo fare mosse o meno
	//inizio il procedimento prendendo in considerazione solo i pezzi bianchi
	for(int r=7;r>=0;r--){ //scorro la matrice di cella in cella
    for(int c=0;c<colonne;c++){
			m_coord.riga = r; //eguaglio le coordinate matriciali all'indice di riga corrispondente
			m_coord.col = c; //eguaglio le coordinate matriciali all'indice di colonna corrispondente
			switch (s[r][c].pezzo) { //verifico che pezzo è presente nella cella in considerazione
				case pawn://pedone
				delta_x=-1,delta_y=-1; //parto dalla digonale in alto a sx
				move=false;
				sc_coord = converti(m_coord); //converto le coordinate matriciali in scacchistiche
				if(s[r][c].colore==white){ //verifico che il pezzo sia bianco
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl; //scrivo sul file nome,colore e posizione del pezzo in considerazione
					incr_x=r-1; incr_y=c; //mi sposto in avandi di una casella sulle y
					if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){ //se trovo una casella vuota mi sposto
					old_cord.riga= incr_x;
					old_cord.col= incr_y;
					new_cord=converti(old_cord);
					f1 << new_cord.col << new_cord.riga<<endl;//scrivo sul file la posizione della mossa che posso fare
					move=true;
					}
				  incr_x=r+delta_x; incr_y=c+delta_y;
					if((s[incr_x][incr_y].colore==black)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){ //esamino le diagonali
							old_cord.riga= incr_x;
							old_cord.col= incr_y;
							new_cord=converti(old_cord);//nuove coordinate assumibili
							f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;// se c'è un avversario mi sposto e lo mangio
							move=true;
					    }
					delta_x=-1,delta_y=1;
					incr_x=r+delta_x; incr_y=c+delta_y;
					if((s[incr_x][incr_y].colore==black)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){//esamino l'altra diagonale e effettuo il medesimo procedimento
							old_cord.riga= incr_x;
							old_cord.col= incr_y;
							new_cord=converti(old_cord);
							f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							move=true;
						}
					if(move==false){ //se il pezzo non puo fare mosse scrivo no move
						f1<<"no move"<<endl;
					}
					}
					 	break;

				case rook: // torre
				delta_x=0; delta_y=1;
				move=false;
				sc_coord = converti(m_coord);
				if(s[r][c].colore==white){
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
					for(int i=0;i<=3;i++){ //ciclo che esamine le 4 direzioni che la torre puo percorrere
				    for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){ //incremento la x e la y nelle 4 direzioni
							 if(s[incr_x][incr_y].colore==white){ // se incontro un pezzo bianco esco dal ciclo
				       break;
				       }
				       else if(s[incr_x][incr_y].pezzo==noPiece){ //se incontro una cella vuote scrivo la posizione che il pezzo puo assumere
							 old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
               f1 << new_cord.col << new_cord.riga<<endl;
							 move=true;
				       }
				       else if(s[incr_x][incr_y].colore==black){//se incontro un pezzo nero lo mangio e scrivo la posizione che posso assumere
               old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
				       f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							 move=true;
							 break;
				       }
						 } //vario il delta x e il delta y a seconda delle direzioni che il pezzo puo percorrere
				    if(delta_x==1&&delta_y==0){
				      delta_x=-1; delta_y=0; }
				    if(delta_x==0&&delta_y==-1){
				      delta_x=1; delta_y=0; }
				    if(delta_x==0&&delta_y==1){
				      delta_x=0; delta_y=-1; }
				      }
						if(move==false){
							 f1<<"no move"<<endl;
						 }
						delta_x=0; delta_y=1; //ripristino il valore iniziale dei delta
			      }
					 	break;
//per l'alfiere eseguo lo stesso algoritmo usato per la torre percorrendo pero le 4 diagonali
				case bishop://alfiere
				delta_x=1,delta_y=1;
				move=false;
				sc_coord = converti(m_coord);
				if(s[r][c].colore==white){
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
					for(int i=0;i<=3;i++){
				    for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){
							 if(s[incr_x][incr_y].colore==white){
				       break;
				       }
				       else if(s[incr_x][incr_y].pezzo==noPiece){
							 old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
               f1 << new_cord.col << new_cord.riga<<endl;
							 move=true;
				       }
				       else if(s[incr_x][incr_y].colore==black){
               old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
				       f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							 move=true;
							 break;
				       }
						 }
				    if(delta_x==1&&delta_y==-1){
				      delta_x=-1; delta_y=1; }
				    if(delta_x==-1&&delta_y==-1){
				      delta_x=1; delta_y=-1; }
				    if(delta_x==1&&delta_y==1){
				      delta_x=-1; delta_y=-1; }
				      }
						if(move==false){
							 f1<<"no move"<<endl;
						 }
						delta_x=1; delta_y=1;
			      }
						break;

				case knight://cavallo
				delta_x=2,delta_y=-1;
				sc_coord = converti(m_coord);
				move=false;
				if(s[r][c].colore==white){
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
					for(int i=0;i<=7;i++){//ciclo che esamina gli 8 movimenti a L che puo fare il cavallo
				       incr_x=r+delta_x; incr_y=c+delta_y; //vario il delta x a ogni giro del ciclo
				         if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
							   old_cord.riga= incr_x;
	 						   old_cord.col= incr_y;
	 						   new_cord=converti(old_cord);
                 f1 << new_cord.col << new_cord.riga<<endl;
								 move=true;
				         }
				       else if((s[incr_x][incr_y].colore==black)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
               old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
				       f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							 move=true;
					 }//vario i delta per far variare i movimenti
						if(delta_x==-1&&delta_y==-2){
   				    delta_x=1; delta_y=-2;  }
 						if(delta_x==-2&&delta_y==-1){
  				    delta_x=-1; delta_y=-2; }
  				  if(delta_x==-2&&delta_y==1){
  				    delta_x=-2; delta_y=-1; }
  				  if(delta_x==-1&&delta_y==2){
  				    delta_x=-2; delta_y=1; }
 				    if(delta_x==1&&delta_y==2){
 				      delta_x=-1; delta_y=2; }
 				    if(delta_x==2&&delta_y==1){
 				      delta_x=1; delta_y=2; }
 				    if(delta_x==2&&delta_y==-1){
 				      delta_x=2; delta_y=1; }
 				      }
						if(move==false){
							 f1<<"no move"<<endl;
						 }
						delta_x=2; delta_y=-1;
			      }
					 	break;
//per la regina metto insieme le direzioni di alfiere e torre usando il medesimo algoritmo
				case queen://regina
				delta_x=1,delta_y=1;
				sc_coord = converti(m_coord);
				move=false;
				if(s[r][c].colore==white){
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
					for(int i=0;i<=7;i++){
				    for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){
							 if(s[incr_x][incr_y].colore==white){
				       break;
				       }
				       else if(s[incr_x][incr_y].pezzo==noPiece){
							 old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
               f1 << new_cord.col << new_cord.riga<<endl;
							 move=true;
				       }
				       else if(s[incr_x][incr_y].colore==black){
               old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
				       f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							 move=true;
				       break;
				       }
						 }
						if(delta_x==1&&delta_y==0){
  				    delta_x=-1; delta_y=0; }
						if(delta_x==0&&delta_y==-1){
 				      delta_x=1; delta_y=0; }
 				    if(delta_x==0&&delta_y==1){
 				      delta_x=0; delta_y=-1; }
 				    if(delta_x==-1&&delta_y==1){
 				      delta_x=0; delta_y=1; }
				    if(delta_x==1&&delta_y==-1){
				      delta_x=-1; delta_y=1; }
				    if(delta_x==-1&&delta_y==-1){
				      delta_x=1; delta_y=-1; }
				    if(delta_x==1&&delta_y==1){
				      delta_x=-1; delta_y=-1; }
				      }
						if(move==false){
							 f1<<"no move"<<endl;
						 }
						delta_x=1; delta_y=1;
			      }
					 	break;
//per il re uso lo stesso algoritmo del cavallo guardando tutte le celle circostanti il re in tutte le direzioni. il re puo fare pero un solo spostamento in una delle  celle che ha intorno
				case king://re
				delta_x=1,delta_y=1;
				move=false;
				sc_coord = converti(m_coord);
				if(s[r][c].colore==white){
					f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
					for(int i=0;i<=7;i++){
				       incr_x=r+delta_x; incr_y=c+delta_y;
				         if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
							   old_cord.riga= incr_x;
	 						   old_cord.col= incr_y;
	 						   new_cord=converti(old_cord);
                 f1 << new_cord.col << new_cord.riga<<endl;
								 move=true;
				         }
				       else if((s[incr_x][incr_y].colore==black)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
               old_cord.riga= incr_x;
	 						 old_cord.col= incr_y;
	 						 new_cord=converti(old_cord);
				       f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
							 move=true;
						  }
						if(delta_x==-1&&delta_y==0){
   				    delta_x=0; delta_y=-1; }
 						if(delta_x==0&&delta_y==1){
  				    delta_x=-1; delta_y=0; }
  				  if(delta_x==1&&delta_y==0){
  				    delta_x=0; delta_y=1; }
  				  if(delta_x==1&&delta_y==-1){
  				    delta_x=1; delta_y=0; }
 				    if(delta_x==-1&&delta_y==-1){
 				      delta_x=1; delta_y=-1; }
 				    if(delta_x==-1&&delta_y==1){
 				      delta_x=-1; delta_y=-1; }
 				    if(delta_x==1&&delta_y==1) {
 				      delta_x=-1; delta_y=1; }
 				      }
						if(move==false){
							 f1<<"no move"<<endl;
						 }
						delta_x=1; delta_y=1;
			      }
					 	break;
				}
			}
		}
//eseguo il medesimo procedimento svolto precedentemente stavolta prendendo in considerazione solo i pezzi neri
for(int r=0;r<righe;r++){
		for(int c=7;c>=0;c--){
			m_coord.riga = r;
			m_coord.col = c;
			switch (s[r][c].pezzo) {
			  case pawn:
			  delta_x=1,delta_y=1;
			  move=false;
			  sc_coord = converti(m_coord);
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    incr_x=r+1; incr_y=c;
			    if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			    old_cord.riga= incr_x;
			    old_cord.col= incr_y;
			    new_cord=converti(old_cord);
			    f1 << new_cord.col << new_cord.riga<<endl;
			    move=true;
			    }
			    incr_x=r+delta_x; incr_y=c+delta_y;
			    if((s[incr_x][incr_y].colore==white)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			        old_cord.riga= incr_x;
			        old_cord.col= incr_y;
			        new_cord=converti(old_cord);
			        f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			        move=true;
			        }
			    delta_x=1,delta_y=-1;
			    incr_x=r+delta_x; incr_y=c+delta_y;
			    if((s[incr_x][incr_y].colore==white)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			        old_cord.riga= incr_x;
			        old_cord.col= incr_y;
			        new_cord=converti(old_cord);
			        f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			        move=true;
			      }
			    if(move==false){
			      f1<<"no move"<<endl;
			    }
			    }
			      break;

			  case rook:
			  delta_x=0; delta_y=1;
			  move=false;
			  sc_coord = converti(m_coord);
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    for(int i=0;i<=3;i++){
			      for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){
			         if(s[incr_x][incr_y].colore==black){
			         break;
			         }
			         else if(s[incr_x][incr_y].pezzo==noPiece){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1 << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         }
			         else if(s[incr_x][incr_y].colore==white){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         break;
			         }
			       }
			      if(delta_x==1&&delta_y==0){
			        delta_x=-1; delta_y=0; }
			      if(delta_x==0&&delta_y==-1){
			        delta_x=1; delta_y=0; }
			      if(delta_x==0&&delta_y==1){
			        delta_x=0; delta_y=-1; }
			        }
			      if(move==false){
			         f1<<"no move"<<endl;
			       }
			      delta_x=0; delta_y=1;
			      }
			      break;

			  case bishop:
			  delta_x=1,delta_y=1;
			  move=false;
			  sc_coord = converti(m_coord);
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    for(int i=0;i<=3;i++){
			      for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){
			         if(s[incr_x][incr_y].colore==black){
			         break;
			         }
			         else if(s[incr_x][incr_y].pezzo==noPiece){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1 << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         }
			         else if(s[incr_x][incr_y].colore==white){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         break;
			         }
			       }
			      if(delta_x==1&&delta_y==-1){
			        delta_x=-1; delta_y=1; }
			      if(delta_x==-1&&delta_y==-1){
			        delta_x=1; delta_y=-1; }
			      if(delta_x==1&&delta_y==1){
			        delta_x=-1; delta_y=-1; }
			        }
			      if(move==false){
			         f1<<"no move"<<endl;
			       }
			      delta_x=1; delta_y=1;
			      }
			      break;

			  case knight:
			  delta_x=2,delta_y=-1;
			  sc_coord = converti(m_coord);
			  move=false;
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    for(int i=0;i<=7;i++){
			         incr_x=r+delta_x; incr_y=c+delta_y;
			           if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			           old_cord.riga= incr_x;
			           old_cord.col= incr_y;
			           new_cord=converti(old_cord);
			           f1 << new_cord.col << new_cord.riga<<endl;
			           move=true;
			           }
			         else if((s[incr_x][incr_y].colore==white)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			         move=true;
			     }
			      if(delta_x==-1&&delta_y==-2){
			        delta_x=1; delta_y=-2;  }
			      if(delta_x==-2&&delta_y==-1){
			        delta_x=-1; delta_y=-2; }
			      if(delta_x==-2&&delta_y==1){
			        delta_x=-2; delta_y=-1; }
			      if(delta_x==-1&&delta_y==2){
			        delta_x=-2; delta_y=1; }
			      if(delta_x==1&&delta_y==2){
			        delta_x=-1; delta_y=2; }
			      if(delta_x==2&&delta_y==1){
			        delta_x=1; delta_y=2; }
			      if(delta_x==2&&delta_y==-1){
			        delta_x=2; delta_y=1; }
			        }
			      if(move==false){
			         f1<<"no move"<<endl;
			       }
			      delta_x=2; delta_y=-1;
			      }
			      break;

			  case queen:
			  delta_x=1,delta_y=1;
			  sc_coord = converti(m_coord);
			  move=false;
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    for(int i=0;i<=7;i++){
			      for(incr_x=r+delta_x,incr_y=c+delta_y;incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8;incr_x=incr_x+delta_x,incr_y=incr_y+delta_y){
			         if(s[incr_x][incr_y].colore==black){
			         break;
			         }
			         else if(s[incr_x][incr_y].pezzo==noPiece){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1 << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         }
			         else if(s[incr_x][incr_y].colore==white){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			         move=true;
			         break;
			         }
			       }
			      if(delta_x==1&&delta_y==0){
			        delta_x=-1; delta_y=0; }
			      if(delta_x==0&&delta_y==-1){
			        delta_x=1; delta_y=0; }
			      if(delta_x==0&&delta_y==1){
			        delta_x=0; delta_y=-1; }
			      if(delta_x==-1&&delta_y==1){
			        delta_x=0; delta_y=1; }
			      if(delta_x==1&&delta_y==-1){
			        delta_x=-1; delta_y=1; }
			      if(delta_x==-1&&delta_y==-1){
			        delta_x=1; delta_y=-1; }
			      if(delta_x==1&&delta_y==1){
			        delta_x=-1; delta_y=-1; }
			        }
			      if(move==false){
			         f1<<"no move"<<endl;
			       }
			      delta_x=1; delta_y=1;
			      }
			      break;

			  case king:
			  delta_x=1,delta_y=1;
			  move=false;
			  sc_coord = converti(m_coord);
			  if(s[r][c].colore==black){
			    f1 << pezzi[s[r][c].pezzo] << "-" << colori[s[r][c].colore] << "-" << sc_coord.col << sc_coord.riga << endl;
			    for(int i=0;i<=7;i++){
			         incr_x=r+delta_x; incr_y=c+delta_y;
			           if((s[incr_x][incr_y].pezzo==noPiece)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			           old_cord.riga= incr_x;
			           old_cord.col= incr_y;
			           new_cord=converti(old_cord);
			           f1 << new_cord.col << new_cord.riga<<endl;
			           move=true;
			           }
			         else if((s[incr_x][incr_y].colore==white)&&(incr_x>=0 && incr_x<righe && incr_y>=0 && incr_y<8)){
			         old_cord.riga= incr_x;
			         old_cord.col= incr_y;
			         new_cord=converti(old_cord);
			         f1<<"*"<<pezzi[s[incr_x][incr_y].pezzo] << " - " << new_cord.col << new_cord.riga<<endl;
			         move=true;
			        }
			      if(delta_x==-1&&delta_y==0){
			        delta_x=0; delta_y=-1; }
			      if(delta_x==0&&delta_y==1){
			        delta_x=-1; delta_y=0; }
			      if(delta_x==1&&delta_y==0){
			        delta_x=0; delta_y=1; }
			      if(delta_x==1&&delta_y==-1){
			        delta_x=1; delta_y=0; }
			      if(delta_x==-1&&delta_y==-1){
			        delta_x=1; delta_y=-1; }
			      if(delta_x==-1&&delta_y==1){
			        delta_x=-1; delta_y=-1; }
			      if(delta_x==1&&delta_y==1) {
			        delta_x=-1; delta_y=1; }
			        }
			      if(move==false){
			         f1<<"no move"<<endl;
			       }
			      delta_x=1; delta_y=1;
			      }
			      break;
			  }
			}
		}
		f1.close();
		return 0;
	}


// inserisce celle vuote in tutta la scacchiera
void vuotaScacchiera(Scacchiera s){
	Cella vuota;
	vuota.pezzo = noPiece;
	vuota.colore = noColor;
	for(int r=0; r<8; r++)
		for(int c=0; c<8; c++)
			s[r][c] = vuota;
}

// inserisce i vari pezzi nella scacchiera
void inserisciPezzi(Scacchiera s){
	//  la codifica dei pezzi bianchi e' la seguente:
	// Pedone 	p
	// Torre	r
	// Cavallo	n
	// Alfiere	b
	// Regina	q
	// Re		k
	// per i pezzi neri stessi caratteri ma maiuscoli
	// Leggo i pezzi della scacchiera dal file di testo 'scaccchiera.txt'
	ifstream scacchi; //creo ifstream per l'input da file di testo scacchi:nome logico
	scacchi.open("scacchiera.txt"); //scacchiera.txt:nome fisico
	string riga1,riga2,riga3,riga4,riga5,riga6,riga7,riga8;
	if(scacchi.good()){ //leggo il file riga per riga
		getline(scacchi, riga1);
		getline(scacchi, riga2);
		getline(scacchi, riga3);
		getline(scacchi, riga4);
		getline(scacchi, riga5);
		getline(scacchi, riga6);
		getline(scacchi, riga7);
		getline(scacchi, riga8);
	}
	scacchi.close();//chiudo il file
	string sitIniziale; //creo una stringa dove mettere l'insieme delle righe prese in input
	sitIniziale = riga1+riga2+riga3+riga4+riga5+riga6+riga7+riga8;
	// recupero dei caratteri dalla stringa
	// riga e colonna corrispondenti al carattere i-esimo della stringa
	int r,c;
	for(int i=0;i<64;i++) {	// per ogni carattere della stringa
		r = i / 8;
		c = i % 8;
		// inserimento pezzi corrispondenti in scacchiera
		s[r][c] = convertiInCella(sitIniziale[i]);
	}
}

// converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p){
	Cella pc;
	pc.pezzo = noPiece; pc.colore = noColor;	// default vuoto
	if (p>='a' && p<='z') pc.colore = white;	// bianco
	if (p>='A' && p<='Z') pc.colore = black;	// nero
	p = tolower(p);
	switch (p) {
		case 'p':
			pc.pezzo = pawn; 	break;
		case 'r':
			pc.pezzo = rook; 	break;
		case 'b':
			pc.pezzo = bishop; 	break;
		case 'n':
			pc.pezzo = knight; 	break;
		case 'q':
			pc.pezzo = queen; 	break;
		case 'k':
			pc.pezzo = king; 	break;
	}
	return pc;
}

// converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p){
	string pChar = "prbnqk PRBNQK ";	// caratteri dei pezzi
	int pCharPos = p.pezzo;
	if (p.colore == black) pCharPos+=7;	// pezzi neri
	return pChar[pCharPos];
}

// converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord m){
	Ccoord c;
	c.col = 'a'+(m.col);
	c.riga = 8 - m.riga;
	return c;
}

// converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord c){
	Mcoord m;
	m.col = c.col - 'a';
	m.riga = 8 - c.riga;
	return m;
}
