#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define block 10

const double IZP_LN2 = 0.69314718055994530942;     // ln(2)
const double IZP_E = 2.7182818284590452354;        // e
const double IZP_PI = 3.14159265358979323846;      // pi
const double IZP_2PI = 6.28318530717958647692;     // 2*pi
const double IZP_PI_2 = 1.57079632679489661923;    // pi/2
const double IZP_PI_4 = 0.78539816339744830962;    // pi/4

double toInterval(double cislo)
{
 if(cislo == 0)
 {
  return 0;
 }
 else if(cislo < 0)
 {
  while(cislo < -IZP_2PI)
  {
   cislo += IZP_2PI;
  }

  if(cislo < -IZP_PI)
  {
   cislo += IZP_PI;
   cislo = -cislo;
  }
 }
 else
 {
  while(cislo > IZP_2PI)
  {
   cislo -= IZP_2PI;
  }

  if(cislo > IZP_PI)
  {
   cislo -= IZP_PI;
   cislo = -cislo;
  }
 }

 return cislo;
}

unsigned long long faktorial(int cislo)
{
 unsigned long long vysledek = 1;

 if(cislo == 0)
 {
  return 1;
 }
 else
 {
  for(int krok = cislo; krok > 0; krok--)
  {
   vysledek *= krok;
  }
 }

 return vysledek;
}

double mocnina(double cislo, int mocnitel)
{
 double vysledek = cislo;

 if(mocnitel == 0)
 {
  return 1;
 }
 else
 {
  for(int krok = 1; krok < mocnitel; krok++)
  {
   vysledek *= cislo;
  }
 }

 return vysledek;
}

double sinus(double cislo, double epsilon)
{
 cislo = toInterval(cislo);
 double vysledek = cislo;
 double pomocny = 0;
 int mocnitel = 3;

 do
 {
  pomocny = vysledek;
  vysledek -= (mocnina(cislo, mocnitel) / faktorial(mocnitel));
  mocnitel += 2;
  if((fabs(vysledek - pomocny) > epsilon) && vysledek == NAN && vysledek == INFINITY) break;
  vysledek += (mocnina(cislo, mocnitel) / faktorial(mocnitel));
  mocnitel += 2;
 }while((fabs(vysledek - pomocny) > epsilon) && vysledek != NAN && vysledek != INFINITY);

 return vysledek;
}

double _logaritmus(double cislo, double epsilon)
{
 double vysledek = cislo - 1;
 double pomocny = 0;
 int mocnitel = 2;

 do
 {
  pomocny = vysledek;
  vysledek -= (mocnina((cislo-1), mocnitel) / mocnitel);
  mocnitel++;
  if((fabs(vysledek - pomocny) > epsilon) && vysledek == NAN && vysledek == INFINITY) break;
  vysledek += (mocnina((cislo-1), mocnitel) / mocnitel);
  mocnitel++;
 }while((fabs(pomocny - vysledek) >= epsilon) && vysledek != NAN && vysledek != INFINITY);

 return vysledek;
}

double logaritmus(double cislo, double epsilon)
{
 double soucet = 0;
 //double ln2 = _logaritmus(2, epsilon);
 if(cislo == 0)
 {
  return NAN;
 }
 while(cislo >= 2){
  soucet += IZP_LN2;
  cislo /= 2;
 }

 if(cislo > 0) soucet += _logaritmus(cislo, epsilon);

 return soucet;
}

int nactiPole(double **pole)
{
 int pocetPrvku = 0;
 int velikost = 10;
 double *helper;

 if(!(helper = (double*)malloc(velikost*sizeof(double))))
 {
  printf("Nedostatek paměti!\n");
  return 0;
 }

 while(scanf("%lf", &helper[pocetPrvku]) != EOF)
 {
  pocetPrvku++;
  if((pocetPrvku%10) == 0){
   velikost += block;
   if(!realloc(helper, velikost*sizeof(double)))
   {
    printf("Nedostatek paměti!\n");
    return 0;
   }
  }
 }

 *pole = helper;

 return pocetPrvku;
}

void prumer()
{
 double soucet = 0;
 int pocet = 0;
 double pomocny = 0;

 while(scanf("%lf", &pomocny) != EOF)
 {
  soucet += pomocny;
  pocet++;
  printf("prumer: %.10le\n", soucet/pocet);
 }
}

int main(int argc, char *argv[])
{
 double *pole = NULL;
 int pocetPrvku = 0;
 double epsilon = 0;

if(argc > 1){
 if(!strcmp(argv[1], "-sin") && argc >= 3)
 {
  epsilon = atof(argv[2]);
  pocetPrvku = nactiPole(&pole);
  for(int index = 0; index < pocetPrvku; index++)
  {
   printf("%.10le\n", sinus(pole[index], epsilon));
  }
 }
 else if(!strcmp(argv[1], "-ln") && argc >= 3)
 {
  epsilon = atof(argv[2]);
  pocetPrvku = nactiPole(&pole);
  for(int index = 0; index < pocetPrvku; index++)
  {
   printf("%.10le\n", logaritmus(pole[index], epsilon));
  }
 }
 else if(!strcmp(argv[1], "-mv") && argc >= 2)
 {
  prumer();
 }
 else if(!strcmp(argv[1], "-stddev") && argc >= 2)
 {
  printf("odchylka\n");
 }
 else
 {
  printf("CHYBA!\n");
 }
}
 else
 {
  printf("CHYBA!\n");
 }

 if(pole != NULL) free(pole);

 return 0;
}
