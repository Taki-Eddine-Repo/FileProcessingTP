#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Idha galkoum lzm creation wa7edha zidou hadh function
// w say ziada brk ya3ni hiya nrml
int CREATE_DATABASES()
{
	ofstream EMP("EMP.txt");
	ofstream DEPT("DEPT.txt");
	if (EMP.is_open())
	{
		EMP << "16712, MARTIN, directeur, 25717, 23 / 05 / 1990, 40000, NULL, 30,\n"
				"17574, DUPONT, administratif, 16712, 03 / 05 / 1995, 9000, NULL, 30,\n"
				"26691, DUPOND, commercial, 27047, 04 / 03 / 1988, 25000, 2500, 2,\n"
				"25012, LAMBERT, administratif, 27047, 14 / 04 / 1991, 12000, NULL, 20,\n"
				"25717, JOUBERT, president, NULL, 10 / 10 / 1982, 50000, NULL, 3,\n"
				"16034, LEBRETON, commercial, 27047, 01 / 06 / 1991, 15000, NULL, 20,\n"
				"17147, MARTIN, commercial, 27047, 10 / 12 / 1993, 20000, 500, 20,\n"
				"27546, PAQUEL, commercial, 27047, 03 / 09 / 1983, 22000, 2000, 20,\n"
				"25935, LEFEBVRE, commercial, 27047, 11 / 07 / 1984, 23500, 1500, 20,\n"
				"15155, GARDARIN, ingenieur, 24533, 22 / 02 / 1985, 24000, NULL, 10,\n"
				"26834, SIMON, ingenieur, 24533, 04 / 08 / 1988, 20000, NULL, 10,\n"
				"16278, DELOBEL, ingenieur, 24533, 16 / 01 / 1994, 21000, NULL, 10,\n"
				"25067, ADIBA, ingenieur, 24533, 05 / 12 / 1987, 30000, NULL, 10,\n"
				"24533, CODD, directeur, 25717, 12 / 11 / 1975, 55000, NULL, 10,\n"
				"27047, LAMERE, directeur, 25717, 07 / 09 / 1989, 45000, NULL, 20,\n"
				"17232, BALIN, administratif, 24533, 03 / 10 / 1987, 13500, NULL, 10,\n"
				"24831, BARA, administratif, 16712, 10 / 09 / 1988, 15000, NULL, 30,";
		DEPT << "10, recherche, Rennes,\n"
			"20, vente, Metz,\n"
			"30, direction, Gif,\n"
			"40, fabrication, Paris,";
		return 1;
		EMP.close();
		DEPT.close();
	}
	else {
		return -1;
	}
}


int EXPAND_ARRAY(string**& OLD_ARRAY, int& SIZE_OLD_ARRAY, char type)
{
	int SIZE = 8;
	if (type == 'D')
	{
		SIZE = 3;
	}
	SIZE_OLD_ARRAY++;
	string** NEW_ARRAY = new string * [SIZE_OLD_ARRAY];
	for (size_t i = 0; i < SIZE_OLD_ARRAY; i++)
	{
		NEW_ARRAY[i] = new string[SIZE];
	}

	switch (type)
	{
	case 'E':	
	{
		for (size_t i = 0; i < SIZE_OLD_ARRAY - 1; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				NEW_ARRAY[i][j] = OLD_ARRAY[i][j];
			}
		}
	}
	break;
	case 'D':
	{
		for (size_t i = 0; i < SIZE_OLD_ARRAY - 1; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				NEW_ARRAY[i][j] = OLD_ARRAY[i][j];
			}
		}
	}
	break;
	default:
		break;
	}
	delete[] OLD_ARRAY;
	OLD_ARRAY = NEW_ARRAY;
	return 1;
}

int main()
{
	string error = "0";
	ifstream EMPHandle("EMP.txt");
	ifstream DEPTHandle("DEPT.txt");
	string counterStream;
	int EMPlineCount = 0;
	int DEPTlineCount = 0;
	while (getline(EMPHandle, counterStream, '\n'))
	{
		EMPlineCount++;
	}
	while (getline(DEPTHandle, counterStream, '\n'))
	{
		DEPTlineCount++;
	}
	int choice = 5;
	// Reset file pointers back to the very top
	EMPHandle.clear();
	EMPHandle.seekg(0, ios::beg);

	DEPTHandle.clear();
	DEPTHandle.seekg(0, ios::beg);
	string** EMP = new string * [EMPlineCount];
	string** DEPT = new string * [DEPTlineCount];

	// we have how many records are in the files
	if (EMPHandle.is_open())
	{
		// Dynamic allocation of a 2D array
		for (size_t i = 0; i < EMPlineCount; i++)
		{
			// laoding the data storing it into arrays
			EMP[i] = new string[8];
			getline(EMPHandle, EMP[i][0], ',');
			EMP[i][0] = (EMP[i][0][0] == '\n') ? string(EMP[i][0].begin() + 1, EMP[i][0].end()) : EMP[i][0];
			getline(EMPHandle, EMP[i][1], ',');
			getline(EMPHandle, EMP[i][2], ','); // fking French DAWG l'accent maybanech ne7iweh w say
			getline(EMPHandle, EMP[i][3], ',');
			getline(EMPHandle, EMP[i][4], ',');
			getline(EMPHandle, EMP[i][5], ',');
			getline(EMPHandle, EMP[i][6], ',');
			getline(EMPHandle, EMP[i][7], ',');
		}

		if (DEPTHandle.is_open())
		{
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				// laoding the data storing it into arrays
				DEPT[i] = new string[3];
				getline(DEPTHandle, DEPT[i][0], ',');
				DEPT[i][0] = (DEPT[i][0][0] == '\n') 
					? string(DEPT[i][0].begin() + 1, DEPT[i][0].end()) 
					: DEPT[i][0];
				getline(DEPTHandle, DEPT[i][1], ',');
				getline(DEPTHandle, DEPT[i][2], ',');
			}
		}
		else
		{
			cout <<
				"FAILURE TO OPEN THE SECOND DATABASE, the system cannot function normally, Want to create one\n";
			// get input and integrate to MENU CHOICES later.
		}
	}
	else
	{
		cout <<
			"FAILURE TO OPEN THE FIRST DATABASE, the system cannot function normally, Want to create one\n";
		// get input and integrate to MENU CHOICES later.
	}
	/*
	* 1- Data has been LOADED successfully
	* 2- NO FATAL ERRORS DETECTED
	*/
	// WORKS FINE :) I AM JUST DUMB LOL
	while (choice > 0)
	{
		cout << "PLEASE SELECT ONE REQUEST FROM THE LIST BELOW. ENTER ANY NEGATIVE INTEGER TO QUIT"
			<< endl
			<< "1- Création de la base de données." << endl // the fucking fancy ass "ACCENT" JEEZ
			<< "2- Ajout d’un département." << endl
			<< "3- Ajout d’un employé." << endl
			<< "4- Suppression d’un employé." << endl
			<< "5- Recherche d’un département selon le numéro du département." << endl
			<< "6- Donner tous les n-uplets de DEPT." << endl
			<< "7- Donner tous les n-uplets de EMP." << endl
			<< "8- Donner les noms et les salaires des employés." << endl
			<< "9- Donner les professions des employés (après élimination des duplicatas)." << endl
			<< "10- Faire le produit cartésien entre EMP et DEPT." << endl
			<< "11- Donner les noms des employés et les noms de leur département." << endl
			<< "12- Donner les numéros des employés travaillant à Rennes." << endl
			<< "12- La liste de tous les employés dont le salaire est compris entre A et B (Par exemple A = 20000 et B = 30000)." << endl
			<< "13- Afficher le nom des employés qui travaillent pour le département recherche." << endl
			<< "14- Afficher le nom des départements qui n’ont pas des ingénieurs." << endl << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			// Well this is trippy AF, first, let's CHECK of the files already exist, if they do then well they do, 
			// if not then call CREATE_DATABASE
			if (DEPTHandle.is_open() && EMPHandle.is_open())
			{
				cout << "DATABASES ALREADY EXIST" << endl;
			}
			else 
			{
				int error = CREATE_DATABASES();
				if (error > 0)
				{
					cout << "CREATED SUCCESSFULLY";
				}
				else
				{
					cout << "ERROR, SOME ERROR OCCURED";
				}
			}
		}
		break;	
		case 2:
		{
			// hadhi t3ayef chwi 3labali matefehmouhash, li mafhamhash ygouli beh nachre7lou
			EXPAND_ARRAY(DEPT, DEPTlineCount, 'D');
			cout << "ENTER INFORMATION OF THE DEPARTMENT" << endl;
			cout << "Departmenet number: "; cin >> DEPT[DEPTlineCount - 1][0];
			cout << "Department Name: "; cin >> DEPT[DEPTlineCount - 1][1];
			cout << "Location: "; cin >> DEPT[DEPTlineCount - 1][2];

			// ajouti lel fichier dhrka (UPDATE DATABASE)
			DEPTHandle.close(); // saker fichier
			ofstream DEPTWRITE("DEPT.txt"); // 3awed 7elou in WRITE mode
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				if (i == DEPTlineCount - 1) // ila l7a9na lakher makalah najoutiw endl m3a lakher tfezed le7sab
				{
					DEPTWRITE << DEPT[i][0] << "," << DEPT[i][1] << "," << DEPT[i][2] << ",";
					continue; // skipi loop
				}
				DEPTWRITE << DEPT[i][0] << "," << DEPT[i][1] << "," << DEPT[i][2] << "," << endl;
			}
			DEPTWRITE.close(); // sakrou
			DEPTHandle.open("DEPT.txt"); // 3awed 3elou in READ mode
		}
		break;	
		case 3:
		{
			// hadhi t3ayef chwi 3labali matefehmouhash, li mafhamhash ygouli beh nachre7lou
			EXPAND_ARRAY(DEPT, DEPTlineCount, 'D');
			// Ya rbk 8 information li ne7tajouhom dhrka:) BZF nkhaliwhoum lghadwa wela nkemlou?
			cout << "ENTER INFORMATION OF THE DEPARTMENT" << endl;
			cout << "Departmenet number: "; cin >> DEPT[DEPTlineCount - 1][0];
			cout << "Department Name: "; cin >> DEPT[DEPTlineCount - 1][1];
			cout << "Location: "; cin >> DEPT[DEPTlineCount - 1][2];

			// ajouti lel fichier dhrka (UPDATE DATABASE)
			DEPTHandle.close(); // saker fichier
			ofstream DEPTWRITE("DEPT.txt"); // 3awed 7elou in WRITE mode
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				if (i == DEPTlineCount - 1) // ila l7a9na lakher makalah najoutiw endl m3a lakher tfezed le7sab
				{
					DEPTWRITE << DEPT[i][0] << "," << DEPT[i][1] << "," << DEPT[i][2] << ",";
					continue; // skipi loop
				}
				DEPTWRITE << DEPT[i][0] << "," << DEPT[i][1] << "," << DEPT[i][2] << "," << endl;
			}
			DEPTWRITE.close(); // sakrou
			DEPTHandle.open("DEPT.txt"); // 3awed 3elou in READ mode
		}
		break;	
		case 4:
		{

		}
		break;	
		case 5:
		{

		}
		break;	
		case 6:
		{

		}
		break;	
		case 7:
		{

		}
		break;	
		case 8:
		{

		}
		break;	
		case 9:
		{

		}
		break;	
		case 10:
		{

		}
		break;	
		case 11:
		{

		}
		break;	
		case 12:
		{

		}
		break;	
		case 13:
		{

		}
		break;	
		case 14:
		{

		}
		break;
		default:
			cout << "WRONG SELECTION. PLEASE SELECT AGAIN" << endl;
			break;
		}
	}
	EMPHandle.close();
	DEPTHandle.close();
}