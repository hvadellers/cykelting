/* 
   Gruppe 4
   Jeppe Winther Sørensen s072370
   Anton Werenberg        s147037 

   Programkode til Opgave 2
*/ 

#include <stdio.h>

#define TEAMNR 0
#define USERID 1
#define WEEK 2
#define DAYS 3
#define KM 4
#define DATASIZE 100
#define MAXTEAMS 50

void menu(void);
int read_menu_choice(int Min, int Max);
int read_data_input(int DataType);
void parse_data_input(int DataCounter, int Data[][DATASIZE]);
void print_team_info(int DataCounter, int Data[][DATASIZE]);
void print_km_info(int DataCounter, int Data[][DATASIZE]);
void print_leaderboard(int DataCounter, int Data[][DATASIZE]);

int main(void)
{
  menu();
  return(0);
}

void menu(void)
{
  int MenuChoice = -1;

  //Datastruktur. Data array holder Data, hvor kolonne
  //0 er TEAMNR
  //1 er USERID
  //2 er WEEK
  //3 er DAYS
  //4 er KM
  //DataCounter tæller hvor mange rækker med data der er puttet i Data
  int Data[5][DATASIZE] = {{0},{0}};
  int DataCounter = 0;


  //Print hovedmenuen, og bed om et menu valg.
  //Gentag indtil 0 er valgt.
    do
    {
      printf("[1: Leaderboard] [2: Indtast Data] [3: Kilometerinfo] [4: Holdinfo] [0: Luk]\n");
      printf("Vælg et menupunkt: ");

      MenuChoice = read_menu_choice(0, 4);

      if (MenuChoice == 2)
	{
	  //Bed brugeren om Data
	  parse_data_input(DataCounter, Data);
	  //Hvis vi modtager Data, så husk at vi har en linje Data mere.
	  DataCounter++;
	}
      //Ved udskrift inden der er Data, bed om Data
      else if ((MenuChoice == 1 || MenuChoice == 3 || MenuChoice == 4) && DataCounter == 0)
	printf("Fyld noget i Databasen først.\n");
      else if (MenuChoice == 1) print_leaderboard(DataCounter, Data);
      else if (MenuChoice == 3) print_km_info(DataCounter, Data);
      else if (MenuChoice == 4) print_team_info(DataCounter, Data);
      
    }while(MenuChoice != 0);
 }

int read_menu_choice(int Min, int Max)
{
  //Spørger brugeren om et input indtil det er
  //mellem Min og Max, og returnerer det.

  int Result = -1;
  scanf("%d", &Result);
  while(Result < Min || Result > Max)
    {
      printf("Valget ikke godtaget. Prøv igen: ");
      scanf("%d", &Result);
    }
  return(Result);
}

void print_team_info(int DataCounter, int Data[][DATASIZE])
{
  //Spørger brugeren om et HoldNr og printer al relevant information.
 
  int i;
  int Input;
  int Success = 0;

  printf("Vælg hold at printe Info for: ");
  Input = read_menu_choice(1, MAXTEAMS);
  for (i = 0; i < DataCounter; i++)
    {
      if (Data[TEAMNR][i] == Input)
	{
	  printf("[Bruger: %d\t Uge: %d\t Dage: %d\t KM: %d]\n",
		 Data[USERID][i], Data[WEEK][i], Data[DAYS][i], Data[KM][i]);
	  Success = 1;
	}
    }
  if (!Success) printf("Det hold nr findes ikke i databasen.\n");
}

int read_data_input(int DataType)
{
  //Beder brugeren om et input, og returnerer det.
  int Result = 0;
  switch (DataType)
    {
    case TEAMNR:
      printf("Indtast Holdnummer: ");
      break;
    case USERID:
      printf("Indtast BrugerID: ");
      break;
    case WEEK:
      printf("Indtast Uge Nr: ");
      break;
    case DAYS:
      printf("Indtast Antal Dage Kørt: ");
      break;
    case KM:
      printf("Indtast Antal KM: ");
      break;
    }
  scanf("%d", &Result);

  return(Result);
}

void parse_data_input(int DataCounter, int Data[][DATASIZE])
{
  //Evaluerer bruger input

  int i = 0;
  int Temp;
  while (i < 5)
    {
      Temp = read_data_input(i);
      int Error = 0;
      switch (i)
	{
	case TEAMNR:
	  if (Temp < 1 || Temp > MAXTEAMS)
	    {
	      printf("Tal mellem 1 og %d. Prøv igen.\n", MAXTEAMS);
	      Error = 1;
	    }
	  break;
	    
	case USERID:
	  if (Temp <= 99999 || Temp > 999999)
	    {
	      printf("Bruger ID er 6-cifre. Prøv igen.\n");
	      Error = 1;
	    }
	  break;

	case WEEK:
	  if (Temp < 1 || Temp > 52)
	    {
	      printf("Ugenummer er mellem 1 og 52. Prøv igen.\n");
	      Error = 1;
	    }
	  break;

	case DAYS:
	  if (Temp < 1 || Temp > 7)
	    {
	      printf("Dage er mellem 1 og 7. Prøv igen.\n");  
	      Error = 1;
	    }
	  break;

	}

      //Hvis, og kun hvis, brugeren har opført sig ordentligt
      //indlæser vi data, og spørger om næste data type.
      //Ellers prøver vi igen.
      if (!Error)
	{
	  Data[i][DataCounter] = Temp;
          i++;
	}
    }
}

void print_km_info(int DataCounter, int Data[][DATASIZE])
{
  //Løb Data arrayet igennem, læg alle KM tal sammen
  //og print resultatet.

  int i;
  int Km = 0;
  for (i = 0; i < DataCounter; i++)
    {
      Km += Data[KM][i];
    }
  printf("Antal km, total: %d\n", Km);
}
  
void print_leaderboard(int DataCounter, int Data[][DATASIZE])
{
  //Løb Data arrayet igennem, identificer index med 
  //mindste og største km værdi, og print al info for
  //dette index.
  
  int i;
  int SmallestIndex = 0;
  int BiggestIndex = 0;
  for (i = 0; i < DataCounter; i++)
    {
      if (Data[KM][i] > Data[KM][BiggestIndex]) BiggestIndex = i;
      if (Data[KM][i] < Data[KM][SmallestIndex]) SmallestIndex = i;
    }
  printf("Bruger %d fra hold %d har kørt mest. I uge %d kørte de %d Km.\n",
	 Data[USERID][BiggestIndex], Data[TEAMNR][BiggestIndex],
	 Data[WEEK][BiggestIndex],Data[KM][BiggestIndex]);
  printf("Bruger %d fra hold %d har kørt mindst. I uge %d kørte de %d Km.\n",
	 Data[USERID][SmallestIndex], Data[TEAMNR][SmallestIndex],
	 Data[WEEK][SmallestIndex],Data[KM][SmallestIndex]);
}
