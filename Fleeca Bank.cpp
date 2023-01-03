#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "windows.h" //funkcja sleep() wykorzystana w funkcji nap
#include <conio.h> //funkcja getch()
#include <fstream> //zapisywanie/wczytywanie do pliku

using namespace std;
int ilosc,menu,klient;
int tab[10000][5];//0- id,1 - wiek,2-plec,, 3-stan konta, 4-nr. konta, (plec 0 - facet,1 - kobita)
string tab1[10000][5];// 0 - imie, 1 - nazwisko,2-miasto, 3 - login, 4- haslo
string tab2[17]={"Piotr","Krzysztof","Andrzej","Tomasz","Pawel","Jan","Michal","Marcin","Jakub","Adam","Marek","Lukasz","Grzegorz","Mateusz","Wojciech","Mariusz","Dariusz"};
string tab3[16]={"Anna","Maria","Katarzyna","Malgorzata","Agnieszka","Barbara","Ewa","Krystyna","Magdalena","Elzbieta","Joanna","Aleksandra","Zofia","Monika","Teresa","Danuta"};
string tab4[22]={"Nowak","Wojcik","Kowalczyk","Wozniak","Mazur","Krawczyk","Kaczmarek","Krol","Zajac","Wieczorek","Wrobel","Adamczyk","stepein","Dudek","Pawlak","Sikora","Walczak","Michalak","Szewczyk","Baran","Pietrzak","Marciniak"};
string tab5[22]={"Warszawa","Krakow","Lodz","Wroclaw","Gdansk","Szczecin","Bydgoszcz","Lublin","Bialystok","Katowice","Gdynia","Radom","Torun","Sosnowiec","Rzeszow","Kielce","Gliwice","Olsztyn","Zabrze","Bielsko-Biala","Bytom","Opole"};
void symulacja()
{
	int pom;
	
	for(int i=0;i<1000;i++)
	{
		string napis="",nap;
		tab[i][0]=i;
		tab[i][1]=( rand() % 60 )+18;
		tab[i][2]=( rand() % 2 );
		tab[i][3]=( rand() % 10000 );
		tab[i][4]=( rand() %80000000)+10000000;
		if(tab[i][2]==0)
		{
			pom = (rand() % 17 );
			tab1[i][0]=tab2[pom];
		}
		if(tab[i][2]==1)
		{
			pom = (rand() % 16 );
			tab1[i][0]=tab3[pom];
		}
		pom = rand() % 22;
		tab1[i][1]=tab4[pom];
		pom = rand() % 22;
		tab1[i][2]=tab5[pom];
		nap=tab1[i][0][0];
		napis+=nap;
		nap=tab1[i][0][1];
		napis+=nap;
		nap=tab1[i][1][0];
		napis+=nap;
		nap=tab1[i][1][1];
		napis+=nap;
		tab1[i][3]=napis;
		napis="";
		nap=tab1[i][0][2];
		napis+=nap;
		nap=tab1[i][0][3];
		napis+=nap;
		nap=tab1[i][1][2];
		napis+=nap;
		nap=tab1[i][1][3];
		napis+=nap;
		tab1[i][4]=napis;
	}
}

void wczytywanie_danych()
{
	ilosc=0;
	ifstream plik;
	plik.open("dane.xdd");
	if( !plik.good() )
	{
		ilosc=1000;
		symulacja();
	}
	else
	{
		plik>>ilosc;
		for(int i =0;i<ilosc;i++)
		{
			plik>>tab[i][0];
			plik>>tab[i][1];
			plik>>tab[i][2];
			plik>>tab[i][3];
			plik>>tab[i][4];
			plik>>tab1[i][0];
			plik>>tab1[i][1];
			plik>>tab1[i][2];
			plik>>tab1[i][3];
			plik>>tab1[i][4];
		}
	}
	plik.close();
}

void zapisywanie_danych()
{
	ofstream plik;
	plik.open("dane.xdd");
	plik<<ilosc<<endl;
	for(int i=0;i<ilosc;i++)
	{
		plik<<tab[i][0]<<endl;
		plik<<tab[i][1]<<endl;
		plik<<tab[i][2]<<endl;
		plik<<tab[i][3]<<endl;
		plik<<tab[i][4]<<endl;
		plik<<tab1[i][0]<<endl;
		plik<<tab1[i][1]<<endl;
		plik<<tab1[i][2]<<endl;
		plik<<tab1[i][3]<<endl;
		plik<<tab1[i][4]<<endl;
	}
	plik.close();
}

void Ekran_glw()
{
	char wyb;
	cout<<"######################################################\n";
	cout<<"#                                                    #\n";
	cout<<"#               Witaj W FleecaBank!                  #\n";
	cout<<"#                                                    #\n";
	cout<<"######################################################\n";
	cout<<"\n";
	cout<<"1.Logowanie\n";
	cout<<"2.Zaloz konto\n";
	wyb=getch();
	if(wyb=='1')
		menu=1;
	if(wyb=='2')
		menu=5;
	system("cls");
}

void Ekran_logowania()
{
	int etap=0;
	string login,haslo;
	char pomo;
	if(etap == 0)
	{
		cout<<"Podaj login: ";
		cin>>login;
		system("cls");
		cout<<"Podaj Haslo: ";
		cin>>haslo;
		system("cls");
		for(int i=0;i<ilosc;i++)
			if(login==tab1[i][3])
				if(haslo==tab1[i][4])
				{
					menu=2;
					cout<<"Witaj, "<<tab1[i][0]<<" "<<tab1[i][1]<<"!";
					klient = i;
					pomo=getch();
					break;
				}
		if(menu==1)
		{
			cout<<"Niepoprawny login lub haslo!";
			menu=0;
			pomo=getch();
		}
			system("cls");
	}
}
void puste(int a)
{
	for(int i=0;i<a;i++)
		cout<<" ";
}
void Ekran_klientow()
{
	int licz=0,pom,strona=1;
	char znak;
	while(1)
	{
		system("cls");
		cout<<"################################\n";
		cout<<"#                              #\n";
		cout<<"#        FleecaKlienci!        #\n";
		cout<<"#                              #\n";
		cout<<"################################\n";
		cout<<"Imie:      Nazwisko:     Wiek:   Miasto:         nr. konta:"<<endl<<endl;
		for(int i=licz;i<licz+20;i++)
		{
			if(i+1>ilosc)
			break;
			cout<<tab1[i][0];
			puste(11-tab1[i][0].length());
			cout<<tab1[i][1];
			puste( 14 - tab1[i][1].length() );
			cout<<tab[i][1]<<"      ";
			cout<<tab1[i][2];
			puste(16-tab1[i][2].length());
			cout<<tab[i][4];
			cout<<endl;
		}
		cout<<endl<<"1. nastepna strona   2. poprzednia strona   3.Wyjdz     strona: "<<strona;
		znak = getch();
		if(znak=='1'&&licz<=ilosc)
		{
			licz+=20;
			strona++;
		}
		if(znak=='2'&&licz>0)
		{
			licz-=20;
			strona--;
		}
		if(znak=='3')
			break;
	}
}

void Ekran_przelewu()
{
	int zmienna,zmienna1=-1,zmienna2;
	char znak;
	while(1)
	{
		system("cls");
		cout<<"######################################################\n";
		cout<<"#                                                    #\n";
		cout<<"#                 FleecaPrzelewy!                    #\n";
		cout<<"#                                                    #\n";
		cout<<"######################################################\n";
		cout<<"\nStan konta: "<<tab[klient][3]<<"zl"<<endl<<endl;
		cout<<"Podaj kwote przelewu: ";
		cin>>zmienna;
		if(zmienna>tab[klient][3]||zmienna<1)
		{
			cout<<endl<<"Niewystarczajace srodki!";
			znak=getch();
			break;
		}
		else
		{
			cout<<endl<<"Podaj numer konta: ";
			cin>>zmienna2;
			for(int i=0;i<ilosc;i++)
				if(zmienna2==tab[i][4])
					zmienna1=i;
			if(zmienna1==-1)
			{
				cout<<endl<<"bledny numer konta!";
				znak=getch();
				break;
			}
			else
			{
				system("cls");
				cout<<"######################################################\n";
				cout<<"#                                                    #\n";
				cout<<"#                 FleecaPrzelewy!                    #\n";
				cout<<"#                                                    #\n";
				cout<<"######################################################\n";
				cout<<endl<<"Kwota: "<<zmienna<<endl;
				cout<<"nr konta: "<<tab[zmienna1][4]<<endl;
				cout<<"Imie i nazwisko odbiorcy: "<<tab1[zmienna1][0]<<" "<<tab1[zmienna1][1]<<endl<<endl<<"1.zatwierdz\n2.przerwij";
				while(1)
				{
					znak=getch();
					if(znak=='1')
					{
						tab[klient][3]-=zmienna;
						tab[zmienna1][3]+=zmienna;
						cout<<endl<<"przelew Wykonano!";
						znak=getch();
						zapisywanie_danych();
						break;
					}
					if(znak=='2')
					{
						break;
					}
				}
			}
		}
		break;
	}
}
void Ekran_banku()//0- id,1 - wiek,2-plec,, 3-stan konta, 4-nr. konta, (plec 0 - facet,1 - kobita)// 0 - imie, 1 - nazwisko,2-miasto, 3 - login, 4- haslo
{
	char wyb;
	while(1)
	{
		system("cls");
		cout<<"######################################################\n";
		cout<<"#                                                    #\n";
		cout<<"#                   FleecaBank!                      #\n";
		cout<<"#                                                    #\n";
		cout<<"######################################################\n";
		cout<<"\nStan konta: "<<tab[klient][3]<<"zl"<<endl<<endl;
		cout<<"Witaj, "<<tab1[klient][0]<<"!\nCo mozemy dla ciebie zrobic?\n\n";
		cout<<"1.Wykonaj przelew"<<endl;
		cout<<"2.Sprawdz innych klientow"<<endl;
		cout<<"3.Szczegoly konta"<<endl<<endl;
		cout<<"4.Wyloguj";
		wyb=getch();
		if(wyb=='1')
			Ekran_przelewu();
		if(wyb=='2')
			Ekran_klientow();
		if(wyb=='3')
			{
				system("cls");
				cout<<"\nStan konta: "<<tab[klient][3]<<"zl"<<endl<<endl;
				cout<<"Imie: "<<tab1[klient][0]<<endl;
				cout<<"Nazwisko: "<<tab1[klient][1]<<endl;
				cout<<"Wiek: "<<tab[klient][1]<<endl;
				cout<<"Nr. konta: "<<tab[klient][4]<<endl;
				cout<<"login: "<<tab1[klient][3]<<endl<<endl;
				cout<<"<Nacisnij dowolny klawisz aby kontynuowac>";
				wyb=getch();
			}
		if(wyb=='4')
		{
			system("cls");
			cout<<"######################################################\n";
			cout<<"#                                                    #\n";
			cout<<"#                   FleecaBank!                      #\n";
			cout<<"#                                                    #\n";
			cout<<"######################################################\n";
			cout<<"Wylogowano poprawnie!!";
			wyb=getch();
			menu=0;
			break;
		}
	}
}

string max_ch(string abc,int bc)
{
	while(abc.length()>bc)
	{
		int a=abc.length();
		abc.erase(a-1,a);
	}
	return abc;
}
void rejestracja()
{
	cout<<"######################################################\n";
	cout<<"#                                                    #\n";
	cout<<"#             Rejestracja W FleecaBank!              #\n";
	cout<<"#                                                    #\n";
	cout<<"######################################################\n\n";
}
void Ekran_rejestracji()
{
	string zmienna;int zmiennar,zm;
	tab[ilosc][0]=ilosc;
	tab[ilosc][3]=1000;
	tab[ilosc][4]=( rand() %80000000)+10000000;
	while(1)
	{
		rejestracja();
		cout<<"Podaj swoja plec:\n1.Mezczyzna\n2.kobieta";
		zmiennar = getch();
		if(zmiennar==49)
		{
			tab[ilosc][2]=0;
			system("cls");
			break;
		}
		if(zmiennar==50)
		{
			tab[ilosc][2]=1;
			system("cls");
			break;
		}
		system("cls");
	}
	while(1)
	{
		rejestracja();
		if(zm==1)
		{
			cout<<"Czy na pewno zostal podany poprawny wiek?\n";
		}
		cout<<"Podaj swoj wiek: ";
		cin>>zmiennar;
		if(zmiennar>99||zmiennar<19)
			zm=1;
		else
		{
			system("cls");
			tab[ilosc][1]=zmiennar;
			break;
		}
		system("cls");
	}
	rejestracja();//0- id,1 - wiek,2-plec,, 3-stan konta, 4-nr. konta, (plec 0 - facet,1 - kobita)// 0 - imie, 1 - nazwisko,2-miasto, 3 - login, 4- haslo
	cout<<"Podaj swoje imie: ";
	cin>>zmienna;
	zmienna =max_ch(zmienna,10);
	tab1[ilosc][0]=zmienna;
	system("cls");
	rejestracja();
	cout<<"Podaj swoje nazwisko: ";
	cin>>zmienna;
	zmienna= max_ch(zmienna,14);
	tab1[ilosc][1]=zmienna;
	system("cls");
	rejestracja();
	cout<<"W jakim miescie mieszkasz?\n";
	cin>>zmienna;
	zmienna= max_ch(zmienna,15);
	tab1[ilosc][2]=zmienna;
	system("cls");
	rejestracja();
	cout<<"Podaj swoj login ktorym bedziesz poslugiwal sie przy logowaniu(maks. 10 znakow):\n";
	cin>>zmienna;
	zmienna= max_ch(zmienna,10);
	tab1[ilosc][3]=zmienna;
	system("cls");
	rejestracja();
	cout<<"Podaj swoje haslo ktorym bedziesz poslugiwal sie przy logowaniu(maks. 10 znakow):\n";
	cin>>zmienna;
	zmienna= max_ch(zmienna,10);
	tab1[ilosc][4]=zmienna;
	system("cls");
	rejestracja();
	cout<<"Podsumowanie:\n";
	cout<<"Imie: "<<tab1[ilosc][0]<<endl;
	cout<<"Nazwisko: "<<tab1[ilosc][1]<<endl;
	cout<<"Wiek: "<<tab[ilosc][1]<<endl;
	cout<<"Nr. konta: "<<tab[ilosc][4]<<endl;
	cout<<"login: "<<tab1[ilosc][3]<<endl;
	cout<<"Haslo: "<<tab1[ilosc][4]<<endl<<endl;
	cout<<"<Nacisnij dowolny klawisz aby kontynuowac>";
	zm = getch();
	menu=0;
	ilosc++;
	zapisywanie_danych();
	system("cls");
}
int main()
{
	menu=0;
	srand (time(NULL));
	wczytywanie_danych();
	zapisywanie_danych();
	while(1)
	{
		if(menu==0)
			Ekran_glw();
		if(menu==1)
			Ekran_logowania();
		if(menu==2)
			Ekran_banku();
		if(menu==5)
			Ekran_rejestracji();
	}
	return 0;
}

/*
	ifstream plik;
    plik.open(save1.c_str());
    while( 1 ) //p\EAtla niesko\F1czona
    {
        plik >>z[i];
        plik>>imie;
        if( plik.good() );
        else
          break; //zako\F1cz wczytywanie danych - wyst\B9pi\B3 jaki\9C b\B3\B9d (np. nie ma wi\EAcej danych w pliku)
    }
    plik.close();
    
    ifstream plik1;
    plik1.open(save2.c_str());
    int cy=0,by=0;
    while( cy<13 ) 
    {
        char a;
        plik1 >> a;
			tab0[cy][by]=a;
		by++;
		if(by==48)
		{
			by=0;
			cy++;
		}
    } 
    cy=0;by=0;
    while( 1 ) 
    {
        
        plik1 >> a;
		
		
		
	
        if( plik1.good() );
        else
          break; //zakocz wczytywanie danych - wyst\B9pi\B3 jaki\9C b\B3\B9d (np. nie ma wi\EAcej danych w pliku)
    } 
    plik1.close();
    */
