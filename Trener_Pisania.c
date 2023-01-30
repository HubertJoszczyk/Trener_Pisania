#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define C 100
typedef struct zdania{
    char *dane;     //wskaznik na dane     
    struct zdania *next;        //wskaznik na nastepny element w liscie
}Zdania;
typedef struct timer{
    clock_t start_time;     
    clock_t end_time;       
    char Input_user[C];        
}Timer;
//Wczytanie zdania z pliku do listy
int Wczytaj_z_pliku(char *nazwa,Zdania **head){
    FILE *fp=fopen(nazwa, "r");       
    char Input_plik[C];     
    int liczba_linii=0;         
    if(fp==NULL){
        printf("Nie mozna otworzyc pliku");     
        exit(1);       
    }
        while(fgets(Input_plik,C,fp)!=NULL){ 
            if(Input_plik[strlen(Input_plik)-1]=='\n'){
                Input_plik[strlen(Input_plik)-1]='\0';
            }           
            if(*head==NULL){
                *head=(Zdania*)malloc(sizeof(Zdania));      //alokacja pamieci
                (*head)->dane=strdup(Input_plik);       //duplikowanie danych z pliku do stringa
                (*head)->next=NULL;         //ustawienie wskaznika na NULL
            }
            else{
                Zdania *current = *head;        //wskaznik na poczatek listy
                while(current->next !=NULL){    
                    current=current->next;      //przesuwa sie po liscie
                    }
            current->next=(Zdania*)malloc(sizeof(Zdania));      //alokacja pamieci
            current->next->dane=strdup(Input_plik);     //duplikowanie danych z pliku do stringa
            current->next->next=NULL;          //ustawienie wskaznika na NULL
            }
            liczba_linii++;     //zwiekszenie licznika elementow listy
        }    
    fclose(fp);     
    return liczba_linii;        
}
//Losowanie indexu
int Losuj_index(int liczba_linii){
    int liczba;     
    srand(time(NULL));      
    liczba=rand()%liczba_linii+1;       
    return liczba;      
}
//Wyswietlenie zdania z wylosowanym indexem z listy
char* Losuj_Zdanie(int liczba_losowa,Zdania *head){
    char losowa[C];     //deklaracja tymczasowej tablicy
    if(liczba_losowa==0){
        printf("%s", head->dane);       //wyswietla zdanie
        strcpy(losowa,head->dane);      //kopiuje do tymczasowej listy
        return strdup(losowa);      //zwraca tymczasowa tablice
    }
    else{
        Zdania *current =head;      //wskaznik na poczatek listy
        for(int z=0;z<liczba_losowa-1;z++){
            current=current->next;      //przesuwa sie po liscie
        }
        printf("%s",current->dane);     //wyswietla zdanie
        strcpy(losowa,current->dane);       //kopiuje do tymczasowej tablicy
        return strdup(losowa);      //zwraca tymczasowa tablice
    }
}
//Wczytanie zdania od uzytkownika           //13=enter  8=backspace
void Wczytaj_Zdanie(Timer tab[C]){
    char zdanie[C];     
    int z=0;        
    char znak;      
    clock_t start_time, end_time;       
    printf("\nBledy zostana zaznaczone na zielono\nPrzepisz zdanie\n");
    while((znak=_getch())!=13){
        if(z==0){
            start_time=clock();     
            tab[0].start_time=start_time;    
        }
        if((int)znak==8){
            z--;        
        }
        else{
            zdanie[z]=znak;     
            z++;        
        }
    }
    zdanie[z]='\0';     
    end_time=clock();       
    tab[0].end_time=end_time;       
    strcpy(tab[0].Input_user, zdanie);        
}
//Porownanie zdania od uzytkownika z zdaniem z pliku
float Porownaj_Zdanie(char *Zdanie_User,char *Zdanie_z_pliku){
    int i=0;        
    float wynik=0;        
    float dlugosc_slowa=(strlen(Zdanie_User));        
    while(Zdanie_User[i]!='\0'){
        if(Zdanie_User[i]==Zdanie_z_pliku[i]){
            wynik++;        
            printf("%c",Zdanie_User[i]);        //wyswietlenie litery w normalnym kolorze
        }
        else{
            printf("\033[0;32m%c\033[0m",Zdanie_User[i]);       //wyswietlenie litery w zielonym kolorze
        }
        i++;        
    }
    return (100-((wynik/dlugosc_slowa)*100));
}
//Czyszczenie listy
void WyczyscListe(Zdania **head)
{
   Zdania* current = *head;     //przypisanie head do current
   Zdania* next;        //deklaracja zmiennej next
   while (current != NULL)      
   {
       next = current->next;        //przypisanie next do current->next
       free(current);       //zwolnienie pamieci
       current = next;      //przypisanie current do next
   }
   *head = NULL;    //przypisanie head do NULL
}
int main(){
    SetConsoleTitle("Trener pisania");
    int liczba_linii,liczba_losowa;
    float ile_czasu;
    char Zdanie_z_Pliku[C];
    char nazwa[]="Zdania.txt";
    Timer tab[C];

    Zdania *head;       //deklaracja zmiennej head
    head=(Zdania*)malloc(sizeof(Zdania));       //alokacja pamieci
    head=NULL;      //przypisanie head do NULL

    liczba_linii=Wczytaj_z_pliku(nazwa,&head);      
    liczba_losowa=Losuj_index(liczba_linii);        
    strcpy(Zdanie_z_Pliku,Losuj_Zdanie(liczba_losowa,head));        //kopiowanie wylosowanego zdania do tablicy
    Wczytaj_Zdanie(tab);
    ile_czasu=(tab[0].end_time-tab[0].start_time)/(double)CLOCKS_PER_SEC;       
    printf("\nIlosc bledow: %.2f%c",Porownaj_Zdanie(tab[0].Input_user,Zdanie_z_Pliku),'%');
    printf("\nWpisanie zdania zajelo: %.2fs",ile_czasu);        
    WyczyscListe(&head);    
    return 0;
}