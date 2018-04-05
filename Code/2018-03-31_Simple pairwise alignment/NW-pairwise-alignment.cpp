#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <time.h>

using namespace std;

// Affine gap function
int gap_affinity (int gap, int gap_ext, int& length){
    int gap_aff = gap + (gap_ext * length);

    return gap_aff;
}

// Get maximal score and trace it
int  max_score (int up, int diag, int left, char * ptr, int& length){
    int  max = 0;

    if( diag >= up && diag >= left ){
        max = diag;
        *ptr = '\\';
        length = 0; // reset gap-length
    }
    else if( up > left){
        max = up;
        *ptr = '|';
        length++; // add 1 gap-length
    }
    else{
        max = left;
        *ptr = '-';
        length++; // add 1 gap-length
    }

    return  max;
}

// Initialise scoring matrix with first row and column
void  init (int** M, char** M_tb, int A_n, int B_n, int gap, int gap_ext){
    M[0][0] =  0;
    M_tb[0][0] = 'n';

    int i=0, j=0;

    for( j = 1; j <= A_n; j++ ){
        M[0][j] = - ( gap + ( gap_ext * (j - 1) ) ); // manually apply affine gap
        M_tb[0][j] =  '-';
    }
    for( i = 1; i <= B_n; i++ ){
        M[i][0] = - ( gap + ( gap_ext * (i - 1) ) ); // manually apply affine gap
        M_tb[i][0] =  '|';
    }
}

// Needleman and Wunsch algorithm
int alignment (int** M, char** M_tb, string A, string B, string& A_al, string& B_al, int A_n, int B_n, int a, int b, int c, int gap, int gap_ext){
    int x = 0, y = 0;
    int scU, scD, scL; // scores for respectively cell above, diagonal and left
    char ptr, nuc;
    int i = 0, j = 0;
    int length = 0; // initial gap length

    // create substitution scoring matrix
    const int  s[4][4] =   {{ a, b, c, c },
                            { b, a, c, c },
                            { c, c, a, b },
                            { c, c, b, a }};

    for( i = 1; i <= B_n; i++ ){
        for( j = 1; j <= A_n; j++ ){
            nuc = A[j-1];

            switch( nuc )
            {
                case 'C':  x = 0;  break;
                case 'T':  x = 1;  break;
                case 'A':  x = 2;  break;
                case 'G':  x = 3;
            }

            nuc = B[i-1];

            switch( nuc )
            {
                case 'C':  y = 0;  break;
                case 'T':  y = 1;  break;
                case 'A':  y = 2;  break;
                case 'G':  y = 3;
            }

            scU = M[i-1][j] - gap_affinity(gap, gap_ext, length); // get score if trace would go up
            scD = M[i-1][j-1] + s[x][y]; // get score if trace would go diagonal
            scL = M[i][j-1] - gap_affinity(gap, gap_ext, length); // get score if trace would go left

            M[i][j] = max_score (scU, scD, scL, &ptr, length); // get max score for current optimal global alignment

            M_tb[i][j] = ptr;
        }
    }
    i--; j--;

    while( i > 0 || j > 0 ){
        switch( M_tb[i][j] )
        {
            case '|' :      A_al += '-';
                            B_al += B[i-1];
                            i--;
                            break;

            case '\\':      A_al += A[j-1];
                            B_al += B[i-1];
                            i--;  j--;
                            break;

            case '-' :      A_al += A[j-1];
                            B_al += '-';
                            j--;
        }
    }

    reverse( A_al.begin(), A_al.end() );
    reverse( B_al.begin(), B_al.end() );

    return  0 ;
}

// Print the scoring matrix
void  print_mtx (int** M, string A, string B, int A_n, int B_n){
    cout << "        ";
    for( int j = 0; j < A_n; j++ ){
        cout << A[j] << "   ";
    }
    cout << "\n  ";

    for( int i = 0; i <= B_n; i++ ){
        if( i > 0 ){
            cout << B[i-1] << " ";
        }
        for( int j = 0; j <= A_n; j++ ){
            cout.width( 3 );
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Print the traceback matrix
void  print_tb (char** M_tb, string A, string B, int A_n, int B_n){
    cout << "        ";
    for( int j = 0; j < A_n; j++ ){
        cout << A[j] << "   ";
    }
    cout << "\n  ";

    for( int i = 0; i <= B_n; i++ ){
        if( i > 0 ){
            cout << B[i-1] << " ";
        }
        for( int j = 0; j <= A_n; j++ ){
            cout.width( 3 );
            cout << M_tb[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Initiate matrices, align and export
int** NW (string A, string B, string& A_al, string& B_al, int A_n, int B_n, int a, int b, int c, int gap, int gap_ext, bool print_align, bool print_mat, int align_nuc){
    // Create alignment matrix
    int** M = new int* [B_n+1];
    for( int i = 0; i <= B_n; i++ ){
        M[i] = new int [A_n+1];
    }

    // Create traceback matrix
    char** M_tb = new char* [B_n+1];
    for( int i = 0; i <= B_n; i++ ){
        M_tb[i] = new char [A_n+1];
    }

    clock_t t; // for timing execution
    t = clock(); // get time of start

    // Initialize traceback and F matrix (fill in first row and column)
    init (M, M_tb, A_n, B_n, gap, gap_ext);


    // Create alignment
    alignment (M, M_tb, A, B, A_al, B_al, A_n, B_n, a, b, c, gap, gap_ext);

    t = clock() - t; // get time when finished
    int score = M[B_n][A_n]; // get alignment score

    if(print_mat == 1){
        print_mtx(M, A, B, A_n, B_n);
        print_tb(M_tb, A, B, A_n, B_n);
    }

    if(print_align == 1){
        cout << endl << "Alignments:" << endl;
        int start = 0; // start of new line for printing alignments
        int cntr = 0; // iterator for printing alignments
        int Al_n = A_al.length(); // length of alignment
        do{
            cout << start+1 << " A: ";
            for (cntr = start; cntr < start+align_nuc; cntr++){
                if(cntr < Al_n){
                    cout << A_al[cntr];
                }else{
                    break;
                }
            }
            cout << " " << cntr << endl << start+1 << " B: ";
            for (cntr = start; cntr < start+align_nuc; cntr++){
                if(cntr < Al_n){
                    cout << B_al[cntr];
                }else{
                    break;
                }
            }
            cout << " " << cntr << endl << endl;
            start += align_nuc;
        }while(start <= Al_n);
    }

    // Show score and runtime
    cout << "Alignment score: " << score << endl;
    cout << "Alignment took " << t << "clicks (" << (t)/CLOCKS_PER_SEC << "seconds).\n";

    // Export alignment to file
    cout << "Exporting results..." << endl;
    ofstream myfile;
    myfile.open ("alignment.txt");
    myfile << "Used parameters:\n";
    myfile << "Match = " << a << "\n";
    myfile << "Mismatch = " << c << "\n";
    myfile << "Purine/purine or pyrimidine/pyrimidine = " << b << "\n";
    myfile << "Gap = -" << gap << "\n";
    myfile << "Extended gap = -" << gap_ext << "\n";
    myfile << "Average elapsed time = " << t << " - " << (t)/CLOCKS_PER_SEC << " [clicks - seconds]." << endl << endl;
    myfile << "Input A:\n" << A << "\n";
    myfile << "Input B:\n" << B << "\n";
    myfile << "\nAlignment:\n";
    int start = 0; // start of new line for printing alignments
    int cntr = 0; // iterator for printing alignments
    int Al_n = A_al.length(); // length of alignment
    do{
        myfile << start+1 << " A: ";
        for (cntr = start; cntr < start+align_nuc; cntr++){
            if(cntr < Al_n){
                myfile << A_al[cntr];
            }else{
                break;
            }
        }
        myfile << " " << cntr << "\n" << start+1 << " B: ";
        for (cntr = start; cntr < start+align_nuc; cntr++){
            if(cntr < Al_n){
                myfile << B_al[cntr];
            }else{
                break;
            }
        }
        myfile << " " << cntr << "\n\n";
        start += align_nuc;
    }while(start <= Al_n);
    myfile << "Alignment score: " << score << "\n";
    myfile.close();

    // Export scoring matrix to file
    myfile.open ("mtx_scoring.txt");
    myfile << "-\t-\t";
    for( int j = 0; j < A_n; j++ ){
        myfile << A[j] << "\t";
    }
    myfile << "\n-\t";
    for( int i = 0; i <= B_n; i++ ){
        int j = 0;
        if( i > 0){
            myfile << B[i-1] << "\t";
        }
        do{
            myfile << M[i][j] << "\t";
            j++;
        }while(j < A_n);
        myfile << M[i][j] << "\n";
    }
    myfile.close();

    // Export traceback matrix to file
    myfile.open ("mtx_trace.txt");
    myfile << "-\t-\t";
    for( int j = 0; j < A_n; j++ ){
        myfile << A[j] << "\t";
    }
    myfile << "\n-\t";
    for( int i = 0; i <= B_n; i++ ){
        int j = 0;
        if( i > 0){
            myfile << B[i-1] << "\t";
        }
        do{
            myfile << M_tb[i][j] << "\t";
            j++;
        }while(j < A_n);
        myfile << M_tb[i][j] << "\n";
    }
    myfile.close();
    cout << "Results exported!" << endl;

    // Free memory
    for( int i = 0; i <= B_n; i++ )  delete M[i];
    delete[] M;
    for( int i = 0; i <= B_n; i++ )  delete M_tb[i];
    delete[] M_tb;

    return 0;
}

int main (int argc, char** argv){
    string A, B; // sequence to be aligned A and B
    string A_al, B_al = ""; // aligned sequence A and B
    bool print_mat; // whether to print matrices etc or just the aligned sequence
    bool print_align; // if alignments should be printed
    int align_nuc = 150; // amount of nucleotides per row
    int a = 5; // match
    int b = -2; // purine-purine / pyrimidine-pyrimidine
    int c = -5; // mismatch
    int gap = 2; // initial gap penalty. Gap penalty is lower than mismatch: two sequences from same species assumed.
    float gap_ext = 1; // bigger gap penalties for affine gap penalty
    string line; // reading in data

    // User interface
    cout << endl << "Print matrices? [0/1]" << endl;
    cin >> print_mat;
    cout << "Print alignments? [0/1]" << endl;
    cin >> print_align;
    cout << "Nucleotides per row? (150 recommended)" << endl;
    cin >> align_nuc;

    cout << "==============================" << endl;

    // Read in the alignments
    ifstream myfile ("sequences.txt");
    if (myfile.is_open()){
        getline (myfile,line);
        A = line;
        A.erase( A.end()-1 ); // remove whitespace at end
        getline (myfile,line);
        B = line;
        myfile.close();
    }else{
        cout << "Unable to open file";
        return 1;
    }

    // Run the alignment script
    int A_n = A.length();
    int B_n = B.length();

    NW (A, B, A_al, B_al, A_n, B_n, a, b, c, gap, gap_ext, print_align, print_mat, align_nuc);

    // Output parameters
    cout << endl << "Used parameters:" << endl;
    cout << "Match = " << a << endl;
    cout << "Mismatch = " << c << endl;
    cout << "Purine/purine or pyrimidine/pyrimidine = " << b << endl;
    cout << "Gap = -" << gap << endl;
    cout << "Extended gap = -" << gap_ext << endl;

    return 0;
}
