#ifndef __LEVENSHTEIN_H__
#define __LEVENSHTEIN_H__

#include <string>
#include <iostream>
//最小编辑距离
class levenshtein
{
public:
    static int compare( const std::string& s1, const std::string& s2 )
    {
        // create two work vectors of integer distances
        const int m = s1.size();
        const int n = s2.size();
        int* v1 = new int[n+1];
        int* v2 = new int[n+1];
        
        // initialize v1 (the previous row of distances)
        // this row is A[0][i]: edit distance for an empty s1
        // the distance is just the number of characters to delete from s2
        for( int i = 0; i <= n; ++i ) {
            v1[i] = i;
        }
        
        // calculate v2 (current row distances) from the previous row v1
        for( int i = 0; i < m; ++i ) {
            // first element of v2 is A[i+1][0]
            // edit distance is delete (i+1) chars from s to match empty s2
            v2[0] = i+1;
        
            // use formula to fill in the rest of the row
            for( int j = 0; j < n; ++j ) {
                // calculating costs for A[i+1][j+1]
                int deletionCost = v1[j+1] + 1;
                int insertionCost = v2[j] + 1;
                int substitutionCost = v1[j];
                if( s1[i] != s2[j] ) {
                    ++ substitutionCost;
                }
                v2[j+1] = min3( deletionCost, insertionCost, substitutionCost );
            }
            // copy v2 (current row) to v1 (previous row) for next iteration
            swap( v1, v2 );
        }
        
        // after the last swap, the results of v2 are now in v1
        int retval = v1[n];
        delete []v1;
        delete []v2;
        return retval;
    }
private:
    static int min3( int a, int b, int c )
    {
        if ( a < b ) {
            return a < c ? a : c ;
        }
        else {
            return b < c ? b : c ;
        }
    }
    static void swap( int*& a, int*& b )
    {
        int* tmp = a;
        a = b;
        b = tmp;
    }
};
#endif
