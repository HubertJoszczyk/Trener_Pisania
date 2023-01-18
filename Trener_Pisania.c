#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define C 100
struct Zdanie
{
    char *Zdanie_z_Pliku;
    struct Zdanie *next;
};
typedef struct Zdanie Zdanie;

//Wczytanie zdania z pliku do listy
int Wczytaj_z_pliku(const char *nazwa,Zdanie **Zdanie_z_pliku){
    FILE *fp;
    char Zdanie_z_Pliku[C];
    fp=fopen(nazwa, "r");
    if(fp==NULL){
        printf("Nie mozna otworzyc pliku");
        return 1;
    }
    while(fgets(Zdanie_z_Pliku, C, fp)!=NULL){
        Zdanie *nowy =malloc(sizeof(Zdanie));
        nowy->Zdanie_z_Pliku = malloc(strlen(Zdanie_z_Pliku)+1);
        strcpy(nowy->Zdanie_z_Pliku, Zdanie_z_Pliku);
        nowy->next = *Zdanie_z_pliku;
        *Zdanie_z_pliku = nowy;
    }
    fclose(fp);
    return 0;
}

//Losowanie zdania z listy (tutaj program sie psuje)
void Losuj_Zdanie(Zdanie *Zdanie_z_pliku){
    int i=0;
    int los=rand()%100;
    Zdanie *tmp;
    tmp=Zdanie_z_pliku;
    while(tmp!=NULL){
        tmp=tmp->next;
        i++;
    }
    //tutaj się chyba psuje(bo jeśli wylosuje 80)
    if(los%i==0){
        printf("%s", Zdanie_z_pliku->Zdanie_z_Pliku);
    }
    else{
        for(int j=0; j<los%i; j++){
            Zdanie_z_pliku=Zdanie_z_pliku->next;
        }
    }
}
//Wczytanie zdania od uzytkownika
void Wczytaj_Zdanie(char *Zdanie_User){
    printf("Przepisz zdanie: ");
    char zdanie[C];
    int z=0;
    char znak;
    clock_t start_time, end_time;
    while((znak=_getch())!=13){
        if(z==0){
            start_time=clock();
            zdanie[z]=znak;
        }
        else if(znak==8){
            z--;
        }
        else{
            zdanie[z]=znak;
            z++;
        }
    }
    zdanie[z]='\0';
    end_time=clock();
    strcpy(Zdanie_User, zdanie);
}
//Porownanie zdania od uzytkownika z zdaniem z pliku
int Porownaj_Zdanie(char *Zdanie_User, char *Zdanie_z_pliku){
    int i=0;
    int wynik=0;
    while(Zdanie_User[i]!='\0'){
        if(Zdanie_User[i]==Zdanie_z_pliku[i]){
            wynik++;
        }
        i++;
    }
    return wynik;
}
//Wyswietlenie wyniku
void Wyswietl_Wynik(int wynik){
    printf("Wynik wynosi: %d", wynik);
}
//Wyswietlenie bledow
void Wyswietl_Bledy(char *Zdanie_User, char *Zdanie_Bledne){
    int i=0;
    while(Zdanie_User[i]!='\0'){
        if(Zdanie_User[i]!=Zdanie_Bledne[i]){
            printf("%c", Zdanie_User[i]);
        }
        else{
            printf(" ");
        }
        i++;
    }
}
//Czyszczenie listy
void Czyszczenie_Listy(Zdanie **Zdanie_z_pliku){
    Zdanie *tmp;
    while(*Zdanie_z_pliku!=NULL){
        tmp=*Zdanie_z_pliku;
        *Zdanie_z_pliku=(*Zdanie_z_pliku)->next;
        free(tmp->Zdanie_z_Pliku);
        free(tmp);
    }
}

int main(){
    char Zdanie_z_Pliku[C];
    char nazwa[]="Zdania.txt";
    char Zdanie_User[C];
    char Zdanie_Bledne[C];
    Zdanie *Zdanie_z_pliku = NULL;
    Zdanie_z_pliku=malloc(sizeof(Zdanie));
    Wczytaj_z_pliku(nazwa,&Zdanie_z_pliku);
    Losuj_Zdanie(Zdanie_z_pliku);
    //Wczytaj_Zdanie(Zdanie_User);
    //Wyswietl_Wynik(Porownaj_Zdanie(Zdanie_User, Zdanie_z_pliku->Zdanie_z_Pliku));
    //Czyszczenie_Listy(&Zdanie_z_pliku);      
    return 0;
}