#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

const double IZP_E = 2.7182818284590452354;        // e
const double IZP_PI = 3.14159265358979323846;      // pi
const double IZP_2PI = 6.28318530717958647692;     // 2*pi
const double IZP_PI_2 = 1.57079632679489661923;    // pi/2
const double IZP_PI_4 = 0.78539816339744830962;    // pi/4

double toInterval(double cislo)
{
 while(cislo > IZP_2PI)
 {
  cislo -= IZP_2PI;
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
  vysledek += (mocnina(cislo, mocnitel) / faktorial(mocnitel));
  mocnitel += 2;
 }while(fabs(vysledek - pomocny) > epsilon);

 return vysledek;
}

int main(int argc, char *argv[])
{
 double epsilon = atof(argv[2]);
 double cislo = 0;
 
 if(!strcmp(argv[1], "-sin"))
 {
  scanf("%lf", &cislo);
  cislo = sinus(cislo, epsilon);
 }
 else
 {
  printf("CHYBA!");
  return 0;
 }
 
 printf("%.10le\n", cislo);

 return 0;
}
