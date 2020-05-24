typedef struct date
{
  int year;
  int month;
  int day;
} Date;

typedef struct album
{
  int id;
  char artist[128];
  char title[64];
  char genre[128];
  Date date;
  bool bought;
  bool listened;
  struct album *previous;
  struct album *next;
} albums;