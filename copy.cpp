#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//bool dentro(int,int);
int main () {
  char scacchi[8][8]=  {{'#','#','#','#','#','#','#','#'}, //scacchiera di partenza(vuota)
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'},
                        {'#','#','#','#','#','#','#','#'}};
int righe=8; //lunghezza colonne
int colonne=8; //lunghezza righe
int continuare=1; //variabile che determina se l'utente ha terminato di inserire i pezzi dentro la scacchiera o se vuole continuare a farlo
int x_inserita,y_inserita; //coordinate di righe e colonne nelle quali l'utente vule inserire il pezzo
while(continuare!=0){ //ciclo che permette di inserire i pezzi nella scacchiera, termina quando l'utente ha finito e preme 0
  cout<<"Lista corrispondente ai pezzi degli scacchi da inserire:"<<endl;
  cout<<"         Bianco   Nero"<<endl;
  cout<<"Torre      r        R"<<endl;
  cout<<"Cavallo    n        N"<<endl;
  cout<<"Alfiere    b        B"<<endl;
  cout<<"Re         q        Q"<<endl;
  cout<<"Regina     k        K"<<endl;
  cout <<"Inserire la coordinata x (righe) del pezzo:";
  cin>>x_inserita;
  cout <<"Inserire la coordinata y (colonne) del pezzo:";
  cin>>y_inserita;
  cout <<"Inserire il carattere corrispondente al pezzo che vuoi inserire:";
  cin>>scacchi[x_inserita][y_inserita];
  for(int i=0;i<righe;i++){ //stampa della scacchiera
    for(int j=0;j<colonne;j++){
      cout<<scacchi[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"Se vuoi inserire un altro pezzo premi 1, se hai finito premi 0   ";
  cin>>continuare;
  cout<<endl;
}
for(int i=0;i<righe;i++){ //stampa della scacchiera completata dall'utente tramite l'inserimento dei pezzi
  for(int j=0;j<colonne;j++){
    cout<<scacchi[i][j]<<" ";
  }
  cout<<endl;
}
cout<<"Le mosse possibili dell'alfiere bianco sono:"<<endl;
//ora controllo tramite 4 sequenze di istruzioni le possibili mosse dell'Alfiere
//controllo mosse sulla diagonale di destra verso il basso

int q,w;
int delta_x=1,delta_y=1;
int verifica;
for(int i=0;i<=3;i++){
  for(int r=0;r<righe;r++){
    for(int t=0;t<colonne;t++){
      if(scacchi[r][t]=='b'){
            //  verifica=dentro(q,w);
              for(q=r+delta_x,w=t+delta_y;q>=0 && q<8 && w>=0 && w<8;q=q+delta_x,w=w+delta_y){
                      if(scacchi[q][w]=='p'||scacchi[q][w]=='r'||scacchi[q][w]=='n'||scacchi[q][w]=='b'||scacchi[q][w]=='q'||scacchi[q][w]=='k'){
                        break;
                      }
                      else if(scacchi[q][w]=='#'){
                        cout<<"b ("<<r<<","<<t<<") ("<<q<<","<<w<<")"<<endl;
                      }
                      else if(scacchi[q][w]=='P'||scacchi[q][w]=='R'||scacchi[q][w]=='N'||scacchi[q][w]=='B'||scacchi[q][w]=='Q'||scacchi[q][w]=='K'){
                        cout<<"b ("<<r<<","<<t<<") * "<<scacchi[q][w]<<"("<<q<<","<<w<<")"<<endl;
                        break;
                      }
           }
        }
      }
    }
    if(delta_x==1&&delta_y==-1){
      delta_x=-1;
      delta_y=1;
    }
    if(delta_x==-1&&delta_y==-1){
      delta_x=1;
      delta_y=-1;
    }
    if(delta_x==1&&delta_y==1){
      delta_x=-1;
      delta_y=-1;
    }
}
return 0;
}
/*
bool dentro (int pos_x,int pos_y){
  if(pos_x>=0 && pos_x<8 && pos_y>=0 && pos_y<8){
    return true;
  }
  else {
    return false;
  }
}
*/
