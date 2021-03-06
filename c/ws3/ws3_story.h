#ifndef WS3_STORY_H
#define WS3_STORY_H

#include <assert.h>

void InitGenerals (int *generals, const int num_generals);
void ExecuteGenerals (int *generals, int starting_general, const int num_generals);
int GetLastGeneral (const int *generals);

#endif
