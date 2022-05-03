#include "exerciser.h"

void exercise(connection *C)
{
    query1(C, 1, 19, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 1, 19, 20, 1, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    query1(C, 1, 19, 20, 1, 5, 6, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0);
    query1(C, 1, 19, 20, 1, 5, 6, 0, 0, 0, 1, 1, 1, 1, 0, 0.5, 0, 0, 0);
    query1(C, 1, 19, 20, 1, 5, 6, 0, 0, 0, 1, 1, 1, 1, 0, 0.5, 1, 0.5, 0.7);
    query2(C, "LightBlue");
    query2(C, "Orange");
    query3(C, "BostonCollege");
    query4(C, "NC", "DarkBlue");
    query5(C, 11);
}
