#include "map.h"
#include "Framework\console.h"
//void map();
//void pmap(char mapVector[28][79]);
int columnNo = 79;
int rowNo = 28;

void createMap()
{
    stageinfo();
    readmap();
    display();
}

void stageinfo()
{
    /*string line;
    int x = 0, y = 0;
    int row = 0, col = 0;
    char mapArray[2][79];
    ifstream myfile ("stageinfo.txt");
    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            for (int i = 0; i < line.length();++i)
            {
                if ( line[i] == '1' )
                {
                    line[i] = 49;
                }
                else if ( line[i] == '0' )
                {
                    line[i] = 48;
                }
            }
            for ( int x = 0; x < 79; ++x )
            {
                mapArray[y][x] = line[x];
            }
            ++y;      
        }

    }
    myfile.close();

    for (int i = 0; i < 2;)
    {
        for (int j = 0; j < 79; ++j)
        {
            g_Console.writetobuffer(j,i, mapArray[i][j],0);
        }
    cout << endl;
    i++;
    }*/
}

void readmap()
{
  string line;
  int x = 0, y = 0;
  int row = 0, col = 0;
  char mapArray[20][79];
  ifstream myfile ("map1.txt");
  if (myfile.is_open())
  {
      while (getline (myfile,line))
      {
          for (int i = 0; i < line.length();++i)
          {
              if ( line[i] == '1' )
              {
                  line[i] = 49;
              }
              else if ( line[i] == '0' )
              {
                  line[i] = 48;
              }
          }
          for ( int x = 0; x < 79; ++x )
          {
              mapArray[y][x] = line[x];
          }
          ++y;      
      }

  }
  myfile.close();

  for (int i = 0; i < 20;)
  {
    
    for (int j = 0; j < 79; ++j)
    {
        cout << mapArray[i][j];
    }
    cout << endl;
    i++;
  }

}

void display()
{
    string displayline;
  int x = 0, y = 0;
  int row = 0, col = 0;
  char mapdisplayArray[6][79];
  ifstream mydisplayfile ("display.txt");
  if (mydisplayfile.is_open())
  {
      while (getline (mydisplayfile,displayline))
      {
          for (int i = 0; i < displayline.length();++i)
          {
              if ( displayline[i] == '1' )
              {
                  displayline[i] = 49;
              }
              else if ( displayline[i] == '0' )
              {
                  displayline[i] = 48;
              }
          }
          for ( int x = 0; x < 79; ++x )
          {
              mapdisplayArray[y][x] = displayline[x];
          }
          ++y;      
      }

  }
  mydisplayfile.close();

  for (int i = 0; i < 6;)
  {
    
    for (int j = 0; j < 79; ++j)
    {
        cout << mapdisplayArray[i][j];
    }
    cout << endl;
    i++;
  }
}