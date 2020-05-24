void swap(albums *a, albums *b);
void sortuj(albums **start, int w);

void swap(albums *a, albums *b)
{
  char tmp[128], tmp1[64];
  int tmp2;
  strcpy(tmp, a->artist);
  strcpy(a->artist, b->artist);
  strcpy(b->artist, tmp);
  strcpy(tmp, a->genre);
  strcpy(a->genre, b->genre);
  strcpy(b->genre, tmp);
  strcpy(tmp1, a->title);
  strcpy(a->title, b->title);
  strcpy(b->title, tmp1);
  tmp2 = a->date.day;
  a->date.day = b->date.day;
  b->date.day = tmp2;
  tmp2 = a->date.month;
  a->date.month = b->date.month;
  b->date.month = tmp2;
  tmp2 = a->date.year;
  a->date.year = b->date.year;
  b->date.year = tmp2;
}

void sortuj(albums **start, int w)
{
  int swapped, i;
  albums *ptr1;
  albums *lptr = NULL;

  if (start == NULL)
    return;

  do
  {
    swapped = 0;
    ptr1 = *start;
    while (ptr1->previous != lptr)
    {
      if (w == 1)
      {
        if (strcmp(ptr1->artist, ptr1->previous->artist) > 0)
        {
          swap(ptr1, ptr1->previous);
          swapped = 1;
        }
      }
      if (w == 2)
      {
        if (strcmp(ptr1->title, ptr1->previous->title) > 0)
        {
          swap(ptr1, ptr1->previous);
          swapped = 1;
        }
      }
      if (w == 3)
      {
        if (strcmp(ptr1->genre, ptr1->previous->genre) > 0)
        {
          swap(ptr1, ptr1->previous);
          swapped = 1;
        }
      }
      if (w == 4)
      {
        if (ptr1->date.year == ptr1->previous->date.year)
        {
          if (ptr1->date.month == ptr1->previous->date.month)
          {
            if (ptr1->date.day == ptr1->previous->date.day)
            {
              break;
            }
            else if (ptr1->date.day > ptr1->previous->date.day)
            {
              swap(ptr1, ptr1->previous);
              swapped = 1;
            }
          }
          else if (ptr1->date.month > ptr1->previous->date.month)
          {
            swap(ptr1, ptr1->previous);
            swapped = 1;
          }
        }
        else if (ptr1->date.year > ptr1->previous->date.year)
        {
          swap(ptr1, ptr1->previous);
          swapped = 1;
        }
      }
      ptr1 = ptr1->previous;
    }
    lptr = ptr1;
  } while (swapped);
}