#include "lib.h"

Party::Party(char* filename):size(0), currentWeek(NULL), nextWeek(NULL)
{
	outFile = fopen(filename, "w");
}

Party::~Party()
{
	destroyMatrices();
	fclose(outFile);
}

void Party::createMatrices()
{
	currentWeek = (int**)malloc(sizeof(int*) * size);
	nextWeek    = (int**)malloc(sizeof(int*) * size);

	for(int i = 0; i < size; ++i){
		currentWeek[i] = (int*)malloc(sizeof(int) * size);
		nextWeek[i] = (int*)malloc(sizeof(int) * size);
	}
}

void Party::destroyMatrices()
{
	
	for(int i = 0; i < size; ++i){
		free(currentWeek[i]);
		free(nextWeek[i]);
	}
}

void Party::loadFile(const char* filename)
{
	FILE *f = fopen(filename, "r");

	if(!f){
		printf("File could not be loaded");
		return;
	}
	fscanf(f, "%d", &size);

	int colourNr;
	fscanf(f, "%d", &colourNr);
	for(int i = 0; i < colourNr; ++i){
		colours.push_back(i);
		check.push_back(false);
	}

	createMatrices();

	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			fscanf(f, "%d", &currentWeek[i][j]);
		}
	}
	fclose(f);
	
}

void Party::resetCheck()
{
	for(int i = 0; i < (int)check.size(); ++i){
		check[i] = false;
	}
}

int Party::getMinDist(int c, int x, int y)
{
	int min_dist = size;

	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			if(x == i && y == j)
				continue;
			if(currentWeek[i][j] == c){
				int dist = getDist(x, y, i, j);
				if(dist < min_dist){
					min_dist = dist;
				}
			}
		}
	}

	if(min_dist == size)
		min_dist = 0;

	return min_dist;
}

int Party::getNextColour(int x, int y)
{
	int limit = 0;
	int color_limit = (int)check.size();
	for(int k = 0; k < (int)colours.size(); ++k){
		int dist = getMinDist(colours[k], x, y);
		if(dist > limit){
			limit = dist;
			color_limit = (int)check.size();
		}
		if(dist == limit){
			if(colours[k] < color_limit){
				color_limit = colours[k];
			}
		}
	}

	return color_limit;
}


void Party::exportSenators(std::vector<int> &s)
{
	for(int i = 0; i < (int)s.size(); ++i){
		fprintf(outFile, "%d ", s[i]);
	}
	fprintf(outFile, "\n");
}

int Party::getNextWeek()
{
	resetCheck();
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			int newColor = getNextColour(i, j);
			check[newColor] = true;
			nextWeek[i][j] = newColor;
		}
	}


	for(int i = 0; i < (int)check.size(); ++i){
		if(!check[i]){
			for(int j = 0; j < (int)colours.size(); ++j){
				if(i == colours[j]){
					colours.erase(colours.begin() + j);
				}
			}
		}
	}

	int** tmp_week = currentWeek;
	currentWeek = nextWeek;
	nextWeek = tmp_week;

	std::vector<int> s = senatorNumber();
	exportSenators(s);
	return 1;
}

std::vector<int> Party::senatorNumber()
{
	std::vector<int> s;
	for(int i = 0; i < (int)check.size(); ++i){
		s.push_back(0);
	}

	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			s[currentWeek[i][j]]++;
		}
	}
	return s;
}

int main(int argc, char** argv)
{
	if(argc < 4){
		printf("Not enough arguments");
	}

	Party *p = new Party(argv[3]);
	p->loadFile(argv[2]);


	int steps = (int)strtol(argv[1], NULL, 10);

	for(int i = 0; i < steps; ++i){
		p->getNextWeek();
	}
	for(int i = 0; i < p->size; ++i){
		for(int j = 0; j < p->size; ++j){
			fprintf(p->outFile, "%d ", p->currentWeek[i][j]);
		}
		fprintf(p->outFile, "\n");
	}

	delete p;
	return 0;
}