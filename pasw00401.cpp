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

// inserisce i vari pezzi nella scacchiera
void inserisciPezzi(Scacchiera s);

// visualizza la scacchiera (formato di visualizzazione e a scelta)
void visualizzaScacchiera(Scacchiera s);

// converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p);

// converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p);

// converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord);

// converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord);

// verifica la correttezza delle coordinate scacchistiche
bool corretto(Ccoord);

// verifica la correttezza delle coordinate nella matrice
bool corretto(Mcoord);

int main () {
	Scacchiera s;
	vuotaScacchiera(s);
	inserisciPezzi(s);
	visualizzaScacchiera(s);
	// inserimento coordinate cella (formato scacchistico es. b,1)
	Ccoord c;
	do {
		cout << "inserire le coordinate (scacchistiche del pezzo da analizzare: ";
		cin >> c.col >> c.riga;
	} while(!corretto(c));
	Mcoord m;
	m = converti(c);
	cout << "le coordinate inserite sono: " << m.riga << " " << m.col << endl;
	cout << "il pezzo selezionato e': " << convertiInChar(s[m.riga][m.col]) << endl;

	ofstream mioFile;
	mioFile.open("mosse.txt");
	mioFile << "Riccardo Fava 287516 - Mattia Ricci 285237" << endl;
	Ccoord cord;
	Mcoord maffo;
	int incr_x;
	int incr_y;
	int righe = 8;   //lunghezza colonne
	int colonne = 8; //lunghezza righe
	int delta_x = 1,delta_y = 1;
	for(int r = 0; r < righe; r++){
    for(int c = 0; c < colonne; c++){
			maffo.riga = r;
			maffo.col = c;
			switch (s[r][c].pezzo) {
				case pawn:
					 	break;
				case rook:
					 	break;
				case bishop:
				if(s[r][c].colore == white){
					for(int i = 0 ; i <= 3; i++){
				    for(incr_x = r + delta_x, incr_y = c + delta_y; incr_x >= 0 && incr_x < righe &&
							 incr_y >= 0 && incr_y < 8; incr_x = incr_x + delta_x, incr_y = incr_y + delta_y){
				       if(s[incr_x][incr_y].colore == white){
				       break;
				       }
				       else if(s[incr_x][incr_y].pezzo == noPiece){
							 cout << s[r][c].pezzo << "-" << s[r][c].colore << "-" << maffo << maffo.riga << endl;
				       }
				       else if(s[incr_x][incr_y].colore == black){
				       break;
				       }
						 }
				    if(delta_x == 1 && delta_y == -1){
				      delta_x = -1;
				      delta_y = 1;
				    }
				    if(delta_x == -1 && delta_y == -1){
				      delta_x = 1;
				      delta_y = -1;
				    }
				    if(delta_x == 1 && delta_y == 1){
				      delta_x = -1;
				      delta_y = -1;
				         }
				      }
			      }
						break;
				case knight:
					 	break;
				case queen:
					 	break;
				case king:
					 	break;
			}
		mioFile.close();
		}
	}
	return 0;
}

// inserisce celle vuote in tutta la scacchiera
void vuotaScacchiera(Scacchiera s){
	Cella vuota;
	vuota.pezzo = noPiece;
	vuota.colore = noColor;
	for(int r = 0; r < 8; r++)
		for(int c = 0; c < 8; c++)
			s[r][c] = vuota;
}

// inserisce i vari pezzi nella scacchiera
void inserisciPezzi(Scacchiera s){
	// per il momento la situazione di partenza
	// e' definita mediante una stringa di 64 caratteri
	//  la codifica dei pezzi bianchi e' la seguente:
	// Pedone 	p
	// Torre	r
	// Cavallo	n
	// Alfiere	b
	// Regina	q
	// Re		k
	// per i pezzi neri stessi caratteri ma maiuscoli
	ifstream scacchi{"scacchiera.txt"};
	string riga1,riga2,riga3,riga4,riga5,riga6,riga7,riga8;
	if (scacchi.good()) {
		getline(scacchi, riga1);
		getline(scacchi, riga2);
		getline(scacchi, riga3);
		getline(scacchi, riga4);
		getline(scacchi, riga5);
		getline(scacchi, riga6);
		getline(scacchi, riga7);
		getline(scacchi, riga8);
	}
	scacchi.close();
	string sitIniziale;
	sitIniziale = riga1 + riga2 + riga3 + riga4 + riga5 + riga6 + riga7 + riga8;
	/*string sitIniziale;
	sitIniziale  = " b      ";
	sitIniziale += "  nq    ";
	sitIniziale += "p     P ";
	sitIniziale += "kr  pPp ";
	sitIniziale += "  B QK  ";
	sitIniziale += "     prp";
	sitIniziale += " P p n p";
	sitIniziale += " b      "; */

	// recupero dei caratteri dalla stringa
	// riga e colonna corrispondenti al carattere i-esimo della stringa
	int r,c;
	for(int i = 0; i < 64; i++) {	// per ogni carattere della stringa
		r = i / 8;
		c = i % 8;
		// inserimento pezzi corrispondenti in scacchiera
		s[r][c] = convertiInCella(sitIniziale[i]);
	}
}
// visualizza la scacchiera (formato di visualizzazione a scelta)
void visualizzaScacchiera(Scacchiera s){
	for(int r = 0; r < 8; r++) {
		cout << "-----------------" << endl;
		for(int c = 0; c < 8; c++)
			cout << "|" << convertiInChar(s[r][c]);
		cout << "|" << endl;
	}
	cout << "-----------------" << endl;
}

// converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p){
	Cella pc;
	pc.pezzo = noPiece; pc.colore = noColor;	// default vuoto
	if (p >= 'a' && p <= 'z') pc.colore = white;	// bianco
	if (p >= 'A' && p <= 'Z') pc.colore = black;	// nero
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

// verifica la correttezza delle coordinate scacchistiche
bool corretto(Ccoord c) {
	if (c.col < 'a' || c.col > 'h') return false;
	if (c.riga < 1 || c.riga > 8)	return false;
	return true;
}

// verifica la correttezza delle coordinate nella matrice
bool corretto(Mcoord m){
	if (m.riga < 0 || m.riga > 7) return false;
	if (m.col < 0 || m.col > 7) return false;
	return true;
}
