#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Idha galkoum lzm creation wa7edha zidou hadh function
// w say ziada brk ya3ni hiya nrml
int CREATE_DATABASES()
{
	ofstream EMP("EMP.txt");
	ofstream DEPT("DEPT.txt");
	if (EMP.is_open())
	{
		EMP << "16712,MARTIN,directeur,25717,23/05/1990,40000,NULL,30,"
			"17574,DUPONT,administratif,16712,03/05/1995,9000,NULL,30,"
			"26691,DUPOND,commercial, 7047,04/03/1988,25000,2500,2,"
			"25012,LAMBERT,administratif,27047,14/0/1991,12000,NULL,20,"
			"25717,JOUBERT,president,NULL,10/10/1982,50000,NULL,3,"
			"16034,LEBRETON,commercial,27047,01/06/1991,15000,NULL,20,"
			"17147,MARTIN,commercial,27047,10/12/1993,20000,500,20,"
			"27546,PAQUEL,commercial,27047,03/09/1983,22000,2000,20,"
			"25935,LEFEBVRE,commercial,27047,11/07/1984,23500,1500,20,"
			"15155,GARDARIN,ingenieur,24533,22/02/1985,24000,NULL,10,"
			"26834,SIMON,ingenieur,24533,04/ 08/1988,20000,NULL,10,"
			"16278,DELOBEL,ingenieur,24533,16/01/1994,21000,NULL,10,"
			"25067,ADIBA,ingenieur,24533,05/12/1987,30000,NULL,10,"
			"24533,CODD,directeur,25717,12/11/1975,55000,NULL,10,"
			"27047,LAMERE, irecteur,25717,07/09 /1989,45000,NULL,20,"
			"17232,BALIN,administratif,24533,03/10/1987,13500,NULL,10,"
			"24831,BARA,administratif,16712,10/09/1988,15000,NULL,30,";
		DEPT << "10,recherche,Rennes,\n"
			"20,vente,Metz,\n"
			"30,direction,Gif,\n"
			"40,fabrication,Paris,";
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

int SEARCH(string** DEPT, int SIZE, int number)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		if (stoi(DEPT[i][0]) == number)
		{
			return i;
		}
	}
	return -1;
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
			int pos = 0;
			bool found;
			// suppresion
			while (choice > 0)
			{
				if (EMPlineCount < 0 || EMPlineCount == 0)
				{
					cout << "You have no employees" << endl;
					goto END;
				}
				found = false;
				cout << "Donnez la cle: (entrez un nombre negative to exit) "; cin >> choice; // use the same choice so that we don't have to make a new variable
				for (size_t i = 0; i < EMPlineCount; i++)
				{
					if (EMP[i][0] == to_string(choice))
					{
						found = true;
						pos = i;
						break;
					}
				}
				if (found)
				{
					for (size_t i = pos; i < EMPlineCount; i++)
					{
						if (i == EMPlineCount - 1)
						{
							break;
						}
						for (size_t j = 0; j < 8; j++)
						{
							int shift = i + 1;
							EMP[i][j] = EMP[shift][j];
						}
					}
					delete[] EMP[EMPlineCount - 1];
					EMP[EMPlineCount - 1] = nullptr;
					EMPlineCount--;
					for (size_t i = 0; i < EMPlineCount; i++)
					{
						for (size_t j = 0; j < 8; j++)
						{
							cout << EMP[i][j] << " ";
						}
						cout << endl;
					}
				}
				else
				{
					cout << "RECORD NOT FOUND";
				}
			}
			cout << endl << endl;
			cout << "Are you sure you want to delete the record? (This can't be undone)[y=1/n=0] "; cin >> choice;
			if (choice == 1)
			{
				EMPHandle.close(); // saker fichier
				ofstream EMPWRITE("EMP.txt"); // 3awed 7elou in WRITE mode
				for (size_t i = 0; i < EMPlineCount; i++)
				{
					if (i == EMPlineCount - 1) // ila l7a9na lakher makalah najoutiw endl m3a lakher tfezed le7sab
					{
						EMPWRITE <<
							EMP[i][0]
							<< ","
							<< EMP[i][1]
							<< ","
							<< EMP[i][2]
							<< ","
							<< EMP[i][3]
							<< ","
							<< EMP[i][4]
							<< ","
							<< EMP[i][6]
							<< ","
							<< EMP[i][6]
							<< ","
							<< EMP[i][7]
							<< ","
							;
						continue; // skipi loop
					}
					EMPWRITE <<
						EMP[i][0]
						<< ","
						<< EMP[i][1]
						<< ","
						<< EMP[i][2]
						<< ","
						<< EMP[i][3]
						<< ","
						<< EMP[i][4]
						<< ","
						<< EMP[i][6]
						<< ","
						<< EMP[i][6]
						<< ","
						<< EMP[i][7]
						<< ",\n"
						;
				}
				EMPWRITE.close(); // sakrou
				EMPHandle.open("EMP.txt"); // 3awed 3elou in READ mode
			}
			else
			{
				// revert changes
				for (size_t i = 0; i < EMPlineCount; i++)
				{
					// laoding the data storing it into arrays
					EMP[i] = new string[8];
					getline(EMPHandle, EMP[i][0], ',');
					EMP[i][0] = (EMP[i][0][0] == '\n') ? string(EMP[i][0].begin() + 1, EMP[i][0].end()) : EMP[i][0];
					getline(EMPHandle, EMP[i][1], ',');
					getline(EMPHandle, EMP[i][2], ','); 
					getline(EMPHandle, EMP[i][3], ',');
					getline(EMPHandle, EMP[i][4], ',');
					getline(EMPHandle, EMP[i][5], ',');
					getline(EMPHandle, EMP[i][6], ',');
					getline(EMPHandle, EMP[i][7], ',');
				}
				cout << endl << "Changes have been reverted" << endl;
			}
		}
END:
		break;	
		case 5:
		{
SEARCH_AGAIN:
			cout << "Ara numero ta3 departement tchuf: "; cin >> choice;
			int res = SEARCH(DEPT, DEPTlineCount, choice);
			if (res)
			{
				cout << endl;
				cout << DEPT[res][0] << " " << DEPT[res][1] << " " << DEPT[res][2] << "\n";
				cout << endl;

			}
			else
			{
				cout << "\nMakash ya shkoupi t7aresh bina?\n\n";
				goto SEARCH_AGAIN;
			}
		}
		break;	
		case 6:
		{
			cout << "Hak w matzidesh t3awed" << endl;
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					cout << DEPT[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		break;	
		case 7:
		{
			cout << "7abibi wallahi 7abibi hak w okhrej 3liya\n" << endl;
			for (size_t i = 0; i < EMPlineCount; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					cout << EMP[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		break;	
		case 8:
		{
			cout << "3amer le9ra3 gedeh neselkou 7na thani 7asdina fel khobza\n" << endl;
			for (size_t i = 0; i < EMPlineCount; i++)
			{
				cout << EMP[i][1] << " yeslek 7bibna " << EMP[i][5] << " Allah Ybarek";
				cout << endl;
			}
			cout << endl;
		}
		break;	
		case 9:
		{
			// Hiya mlkhr, matlob hadha kayna tari9a tsakhef bsh tkhaf y3aresh
			// yekhi rana nshoufou f jedhoum tsema mlkhr na9edrou ndirou array w koul ma n7ebou
			// nzidou fiha 7aja nchekiw gbel idha kayen ou nn bsh tkhaf ygoulek sahla bzf
			string* professions = new string[EMPlineCount];
			string clean[5];
			for (size_t i = 0; i < EMPlineCount; i++)
			{
				professions[i] = EMP[i][2];
			}
			// Algorithm standard remove dulplicates
			// sort it
			sort(professions, professions+ EMPlineCount);
			int j = 0;
			for (size_t i = 0; i < EMPlineCount - 1; i++)
			{
				if (professions[i] != professions[i+ 1])
				{
					clean[j++] = professions[i];
				}
			}
			clean[j++] = professions[EMPlineCount - 1];
			for (size_t i = 0; i < 5; i++)
			{
				cout << clean[i] << endl;
			}
		}
		break;	
		case 10:
		{
			string** CROSS_JOIN = new string * [DEPTlineCount * EMPlineCount];
			int CROSS_ROW = 0, EMPCOUNTER = 0, DEPTCOUNTER = 0;
			for (size_t i = 0; i < DEPTlineCount * EMPlineCount; i++)
			{
				CROSS_JOIN[i] = new string[11];
			}
			int i = 0;
			int checkPoint = 0;
			while (i < DEPTlineCount * EMPlineCount)
			{
				for (size_t j = 0; j < DEPTlineCount; j++)
				{
					for (size_t k = 0; k < 8; k++)
					{
						CROSS_JOIN[i][k] = EMP[EMPCOUNTER][k];
					}
					i++;
				}
				EMPCOUNTER++;
				if (EMPCOUNTER == EMPlineCount)
					EMPCOUNTER = 0;


				for (size_t j = checkPoint; j < i; j++)
				{
					for (size_t k = 0; k < 3; k++)
					{
						CROSS_JOIN[j][k + 8] = DEPT[DEPTCOUNTER][k];
					}
				}
				checkPoint = i;
				DEPTCOUNTER++;
				if (DEPTCOUNTER == DEPTlineCount)
					DEPTCOUNTER = 0;
			}
			for (size_t i = 0; i < DEPTlineCount * EMPlineCount; i++)
			{
				for (size_t j = 0; j < 11; j++)
				{
					cout << CROSS_JOIN[i][j] << " ";
				}
				cout << endl;
			}
			delete[] CROSS_JOIN;
		}
		break;	
		case 11:
		{
			cout << endl;
			for (size_t i = 0; i < EMPlineCount; i++)
			{
				int res = SEARCH(DEPT, DEPTlineCount, stoi(EMP[i][7]));
				string DEPARTEMENT = res == -1 ? "NOT ASSIGNED" : DEPT[res][1];
				cout << EMP[i][1] << " " << DEPARTEMENT << endl;
			}
			cout << endl;
		}
		break;	
		case 12:
		{
			int A, B;
			cout << endl;
			cout << "A3tina linterval chuf dhrk khfif dhrif na7esboulek\n";
			cout << "Lewel ";
			cin >> A;
			cout << "Thani ";
			cin >> B;
			cout << endl;
			for (size_t i = 0; i < EMPlineCount; i++)
			{
				if (stoi(EMP[i][5]) > A && stoi(EMP[i][5]) < B)
				{
					cout << EMP[i][0] << " " << EMP[i][1] << " " << EMP[i][5] << endl;
				}
			}
			cout << endl;
		}
		break;	
		case 13:
		{
			int code = -1;
			// First search for la recherche
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				if (DEPT[i][1] == "recherche")
					code = stoi(DEPT[i][0]);
			}
			if (code > 0)
			{
				for (size_t i = 0; i < EMPlineCount; i++)
				{

					if (stoi(EMP[i][7]) == code)
						cout << EMP[i][0] << " " << EMP[i][1] << " " << EMP[i][7] << endl;
				}
			}
			else
				break;

		}
		break;	
		case 14:
		{
			int** departments = new int*[DEPTlineCount];
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				departments[i] = new int;
				departments[i][1] = false;
			}
			
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				departments[i][0] = stoi(DEPT[i][0]);
			}
			// we have the departments and their codes LOADED now let's find the thing

			for (size_t i = 0; i < EMPlineCount; i++)
			{
				if (EMP[i][2] == "ingenieur")
				{
					for (size_t i = 0; i < DEPTlineCount; i++)
					{
						if (stoi(EMP[i][7]) == departments[i][0])
							departments[i][1] = true;
					}
				}
			}
			for (size_t i = 0; i < DEPTlineCount; i++)
			{
				if (departments[i][1] == false)
					cout << DEPT[i][0] << " " << DEPT[i][1] << endl;
			}
			delete[] departments;
		}
		break;
		default:
			cout << "WRONG SELECTION. PLEASE SELECT AGAIN" << endl;
			break;
		}
	}
	delete[] EMP;
	delete[] DEPT;
	EMPHandle.close();
	DEPTHandle.close();
}