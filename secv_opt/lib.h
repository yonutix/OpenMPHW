#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#define MAX(a, b) ((a > b)?a:b)


class Party;

class Party{
public:
	int size;
	int** currentWeek;
	int** nextWeek;

	std::vector<int> colours;
	std::vector<bool> check;

	FILE* outFile;

	Party(char* filename);
	~Party();

	void createMatrices();
	void destroyMatrices();

	/**
	 \brief Incarca fisierul de intrare in memorie
	*/
	void loadFile(const char* filename);

	/**
	 \brief Reseteaza vectorul cu culorile prezente in saptamana urmatoare
	*/
	void resetCheck();

	/**
	\brief Returneaza distanta conform cerintelor problemei
	*/
	inline int getDist(int x1, int y1, int x2, int y2)
	{ return MAX(abs(x1-x2), abs(y2-y1));}

	/**
		\brief Returneaza distanta minima pana la cea mai 
		apropiata culoare c
	*/
	int getMinDist(int c, int x, int y);

	/**
		\brief Returneaza culoarea care urmeaza sa o inlocuiasca pe 
		cea actuala
	 */
	int getNextColour(int x, int y);

	/**
	 * Pune in variabila nextWeek culorile pentru saptamana viitoare
	 */
	int getNextWeek();

	/**
	 \brief Returneaza numerul de senatori
	*/
	std::vector<int> senatorNumber();

	/**
	 \brief Scrie in fisier numarul de senatori pentru fiecare culaore
	*/
	void exportSenators(std::vector<int> &);


	/**
	 \brief Verifica daca o culoare exista la distanta d
	*/
	bool colorExistByDist(int c, int x, int y, int d);
};