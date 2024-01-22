#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

const int classSize = 35; // the maximum number of students in a single section class
const double bar = 60; // student needs to pass the minimum bar to enjoy the curve grade

const double POINTA = 93.0;
const double POINTAMINUS = 90.0;
const double POINTBPLUS = 87.0;
const double POINTB = 83.0;
const double POINTBMINUS = 80.0;
const double POINTCPLUS = 77.0;
const double POINTC = 73.0;
const double POINTCMINUS = 70.0;
const double POINTD = 60.0;

const double CURVEA = 85.0;
const double CURVEAMINUS = 70.0;
const double CURVEBPLUS = 58.3;
const double CURVEB = 46.6;
const double CURVEBMINUS = 35.0;
const double CURVECPLUS = 30.0;
const double CURVEC = 25.0;
const double CURVECMINUS = 20.0;
const double CURVED = 10.0;

enum Grade {F, D, CMINUS, C, CPLUS, BMINUS, B, BPLUS, AMINUS, A};

struct studentData{
    string lastName;
    string firstName;
    double score;
    double percentage;
    Grade pointGrade;
    Grade curveGrade;
    Grade finalGrade;
};

string letterGrade(Grade g) {
    switch (g) {
        case F: return "F";
        case D: return "D";
        case CMINUS: return "C-";
        case C: return "C";
        case CPLUS: return "C+";
        case BMINUS: return "B-";
        case B: return "B";
        case BPLUS: return "B+";
        case AMINUS: return "A-";
        case A: return "A";
        default: return "Error";
    }
}

bool insert(studentData** v, studentData n, int& z, int& s){
    
    studentData* w = *v;
    if(z < s){
        w[z] = n;
        //cout<< " "<<w[z].score << endl;
        z += 1;
        return true;
    }
    else{
        s += classSize;
        
        studentData* p = new studentData[s];
        for(int i = 0; i < z; i++){
            p[i] = w[i];
            //cout<< " "<<p[i].score << endl;
            //cout<< s<< endl;
        }
        p[z] = n;
        z += 1;
        
        delete [] w;
        *v = p;
        return false;
    }
};


void calcPercent(studentData* x[], int b) {
    studentData* v = *x;

    // Sort the students in descending order based on score
    for (int i = 0; i < b - 1; i++) {
        for (int j = 0; j < b - i - 1; j++) {
            if (v[j].score < v[j + 1].score) {
                swap(v[j], v[j + 1]);
            }
        }
    }

    // Assign percentage based on the position in the sorted array
    for (int i = 0; i < b; i++) {
        v[i].percentage = (1.0 - i / double(b)) * 100;
    }
}

void sortByLastName(studentData student[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (student[j].lastName > student[j + 1].lastName) {
                swap(student[j], student[j + 1]);
            }
        }
    }
}


void outputGradeBook(string ofileName, studentData student[], int size){
    ofstream outFile(ofileName);
    outFile << left << setw(15) <<"Last Name" << left << setw(15) <<"First Name" << setw(10) << "Points" << setw(10) << "Grade" << setw(10) << "Percent" << setw(10) << "Grade" << setw(10) << "Final" << endl;
    
    for(int j = 0; j < size; j++){
        
        if(student[j].lastName != ""){ // having trouble trying to get rid of the 0 values in my array
            
            outFile << left<< setw(15) << student[j].lastName << left << setw(15)<< student[j].firstName << setw(10)<< student[j].score<< setw(10)<<letterGrade(student[j].pointGrade) << setw(10)<< student[j].percentage<< setw(10)<< letterGrade(student[j].curveGrade) << setw(10)<< letterGrade(student[j].finalGrade) << endl;
        }
    }
};

int main(){
    int s = classSize;
    int b = 0;
    studentData* student = new studentData[s];
    
    string gradeData;
    cout <<"Enter the student grade data file: ";
    cin >> gradeData;
    
    string gradeBook;
    cout <<"\nEnter the gradebook filename: ";
    cin >> gradeBook;
    
    cout <<"Initial class size = " << classSize <<" students.\n";
    
    string h;
    fstream dataFile(gradeData, ios:: in);
    
    if (dataFile.is_open()){
        
        while (getline(dataFile, h)) {
            istringstream input(h);
            
            studentData n;
            string lastN, firstN;
            double score;
            
            input >> lastN >> firstN >> score; //appending the first 3 structure items
            //test to see if the input is working correctly
            //cout << "Read: " << lastN << " " << firstN << " " << score << endl;
            
            n.lastName = lastN;
            n.firstName = firstN;
            n.score = score;
            
            insert(&student, n, b, s); //the dynamic array size has been increased accordingly
            b++;
        }
    }
    else
        cout <<"Error opening input file!" << endl;
    
    cout <<"The class size has been increased to " << s << " students.\n";
    cout <<"The total enrollment = " << b << " students." << endl;
    
    calcPercent(&student, b);
        
        for(int k = 0; k < b; k++){
            if (student[k].score >= POINTA) {
                student[k].pointGrade = A;
            } else if (student[k].score >= POINTAMINUS) {
                student[k].pointGrade = AMINUS;
            } else if (student[k].score >= POINTBPLUS) {
                student[k].pointGrade = BPLUS;
            } else if (student[k].score >= POINTB) {
                student[k].pointGrade = B;
            } else if (student[k].score >= POINTBMINUS) {
                student[k].pointGrade = BMINUS;
            } else if (student[k].score >= POINTCPLUS) {
                student[k].pointGrade = CPLUS;
            } else if (student[k].score >= POINTC) {
                student[k].pointGrade = C;
            } else if (student[k].score >= POINTCMINUS) {
                student[k].pointGrade = CMINUS;
            } else if (student[k].score >= POINTD) {
                student[k].pointGrade = D;
            } else {
                student[k].pointGrade = F;
            }

            // Determine curve grade
            if (student[k].percentage >= CURVEA) {
                student[k].curveGrade = A;
            } else if (student[k].percentage >= CURVEAMINUS) {
                student[k].curveGrade = AMINUS;
            } else if (student[k].percentage >= CURVEBPLUS) {
                student[k].curveGrade = BPLUS;
            } else if (student[k].percentage >= CURVEB) {
                student[k].curveGrade = B;
            } else if (student[k].percentage >= CURVEBMINUS) {
                student[k].curveGrade = BMINUS;
            } else if (student[k].percentage >= CURVECPLUS) {
                student[k].curveGrade = CPLUS;
            } else if (student[k].percentage >= CURVEC) {
                student[k].curveGrade = C;
            } else if (student[k].percentage >= CURVECMINUS) {
                student[k].curveGrade = CMINUS;
            } else if (student[k].percentage >= CURVED) {
                student[k].curveGrade = D;
            } else {
                student[k].curveGrade = F;
            }
            
            //determine final grade
            if(student[k].score >= bar){
                if(student[k].curveGrade > student[k].pointGrade){
                    student[k].finalGrade = student[k].curveGrade;
                } else {
                    student[k].finalGrade = student[k].pointGrade;
                }
            } else {
                student[k].finalGrade = F;
            }
        }
    
    sortByLastName(student, s);
    
    outputGradeBook(gradeBook, student, s);
    
    delete[] student;
    dataFile.close();
    return 0;
}
