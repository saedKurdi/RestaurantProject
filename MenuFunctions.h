#pragma once


#include<iostream>

using namespace std;


inline void MainMenu() {
	cout << "\t\t\t<<<<<  R E S T A U R A N T   M A N A G M E N T   S Y S T E M  >>>>>" << endl << endl << endl;
	cout << "\t\t\t\t1. E N T E R   A S   A N   A D M I N " << endl << endl;
	cout << "\t\t\t\t2. E N T E R   A S   A   C L I E N T   " << endl << endl;
	cout << "\t\t\t\t3. E X I T   F R O M   R E S T A U R A N T  " << endl << endl;
}

inline void AdminMenu() {
	cout << "\t\t\t\t1. V I E W   K I T C H E N   " << endl << endl;
	cout << "\t\t\t\t2. V I E W   S T O C K  " << endl << endl;
	cout << "\t\t\t\t3. <--  B A C K   " << endl << endl ;
	cout << "\t\t\t\t4. V I E W   A L L   I N F O   A B O U T   R E S T A U R A N T " << endl << endl << endl;
}

inline void KitchenMenu() {
	cout << "\t\t\t\t1. V I E W   O R D E R S " << endl << endl;
	cout << "\t\t\t\t2. V I E W   A L L   M E A L   I N   T H E   K I T C H E N " << endl << endl;
	cout << "\t\t\t\t3. A D D   N E W   M E A L   T O   K I T C H E N " << endl << endl;
	cout << "\t\t\t\t4. D E L E T E   M E A L   F R O M   T H E   K I T C H E N " << endl << endl;
	cout << "\t\t\t\t5. <--- B A C K  " << endl << endl << endl;
}

inline void StockMenu() {
	cout << "\t\t\t\t1. V I E W   A L L   I N G R E D I E N T S   F R O M   S T O C K  " << endl << endl;
	cout << "\t\t\t\t2. A D D   N E W   I N G R E D I E N T   T O   S T O C K  " << endl << endl;
	cout << "\t\t\t\t3. D E L E T E   I N G R E D I E N T   F R O M   S T O C K " << endl << endl;
	cout << "\t\t\t\t4. <--- B A C K  " << endl << endl << endl;
}

inline void AddedClientMenu() {
	cout << "\t\t\t\t1. V I E W   Y O U R   O R D E R   " << endl << endl;
	cout << "\t\t\t\t2.	V I E W   M E S S A G E   F R O M   K I T C H E N  " << endl << endl;
	cout << "\t\t\t\t3. L E A V E   F R O M   R E S T A U R A N T  " << endl << endl;
	cout << "\t\t\t\t4. <--- B A C K  " << endl << endl << endl;
}