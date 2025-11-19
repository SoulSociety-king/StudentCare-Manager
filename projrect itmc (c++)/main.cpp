#include <bits/stdc++.h>
#include<windows.h>

using namespace std;
struct student
{
    string id,name,carenote;
};
class studentcare
{
private:
    vector<student>studentlist;
    const string filename="Studentlist.txt";
    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            student s;
            while (file >> s.id) {
                file.ignore();
                getline(file, s.name);
                getline(file, s.carenote);
                studentlist.push_back(s);
            }
            file.close();
        }
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto& x : studentlist) {
            file << x.id << " " << x.name << "\n" << x.carenote << "\n";
        }
        file.close();
    }
public:
    studentcare()
    {
        loadFromFile();
    }
    ~ studentcare()
    {
        saveToFile();
    }
    void add(string& id,string& name,string& carenote)
    {
        studentlist.push_back({id,name,carenote});
        cout<<"Add successfully.\n";
    }
    void view() const
    {
        for(auto &x:studentlist)
        {
            cout<<"MSSV: "<<x.id<<", "<<"Full name: "<<x.name<<", "<<"Care Note: "<<x.carenote<<'\n';
        }
    }
    void searchstudent(string id)
    {
        auto it=find_if(studentlist.begin(),studentlist.end(),[id] (const student& x) {return x.id==id;});
        if(it!=studentlist.end())
        {
            cout<<"MSSV: "<<it->id<<", Full name: "<<it->name<<", Care Note: "<<it->carenote<<'\n';
        }
        else cout<<"MSSV errol.\n";
    }
    void deletestudent(const string &id) {
        auto it = remove_if(studentlist.begin(), studentlist.end(),
                            [id](const student &x) { return x.id == id;});
        if (it != studentlist.end()) {
            studentlist.erase(it, studentlist.end());
            cout << "Student deleted successfully.\n";
        } else {
            cout << "Student not found.\n";
        }
    }
    void exporttoexcel(const string& filenameExcel = "Studentlist.csv") {
    ofstream file(filenameExcel);
    if (!file.is_open()) {
        cout << "Cannot create file!\n";
        return;
    }
    file << "MSSV,Name,CareNote\n";
    for (auto &x : studentlist) {
        file << '"' << x.id << "\","
             << '"' << x.name << "\","
             << '"' << x.carenote << "\"\n";
    }
    file.close();
    cout<<"Data exported successfully to " << filenameExcel << "\n";
}
};
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printGradient(const string &text, int colorStart, int colorEnd) {
    int len = text.size();
    for (int i = 0; i < len; i++) {
        int color = colorStart + (colorEnd - colorStart) * i / len;
        setColor(color);
        cout << text[i];
    }
    setColor(7);
}

void showMenu() {
    system("cls");
    printGradient("=========================================\n", 9, 11);
    printGradient("           STUDENT CARE SYSTEM           \n", 11, 13);
    printGradient("=========================================\n\n", 13, 11);

    setColor(14);
    cout<<"  1. Add Student.\n";
    cout<<"  2. Student list.\n";
    cout<<"  3. Search Student by MSSV.\n";
    cout<<"  4. Delete Student.\n";
    cout<<"  5. Export to excel (.csv).\n";
    cout<<"  6. Exit.\n";
    printGradient("=========================================\n", 11, 9);
    setColor(7);
    cout<<"Enter your choice: ";
}
int main()
{
    studentcare system;
    int select;
    do{
        showMenu();
        cin>>select;
        cin.ignore();
        if(select == 1)
        {
            string id,name,carenote;
            cout<<"MSSV: ";cin>>id;
            cin.ignore();
            cout<<"Full name: ";getline(cin,name);
            cout<<"Care note of student: ";getline(cin,carenote);
            system.add(id,name,carenote);
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        if(select == 2)
        {
            system.view();
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        if(select == 3)
        {
            string id_find;
            cout<<"Enter the MSSV to find: ";cin>>id_find;
            system.searchstudent(id_find);
            cout << "\nPress Enter to continue...";
            cin.get();
        }

        if(select == 4)
        {
            string id_delete;
            cout<<"Enter the MSSV to delete: ";cin>>id_delete;
            system.deletestudent(id_delete);
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        if(select == 5)
        {
            system.exporttoexcel();
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    }while(select!=6);
}
