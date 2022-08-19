
  
/**********************************************************************
 * 
 * A cube 'state' is a vector<int> with 40 entries, the first 20
 * are a permutation of {0,...,19} and describe which cubie is at
 * a certain position (regarding the input ordering). The first
 * twelve are for edges, the last eight for corners.
 * 
 * The last 20 entries are for the orientations, each describing
 * how often the cubie at a certain position has been turned
 * counterclockwise away from the correct orientation. Again the
 * first twelve are edges, the last eight are corners. The values
 * are 0 or 1 for edges and 0, 1 or 2 for corners.
 * 
 **********************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cassert>
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> cubestate;

int applicableMoves[] = {0, 262143, 259263, 74943, 74898};

int affectedCubies[][8] = {
    { 0, 1, 2, 3, 0, 1, 2, 3 },   // U
    { 4, 7, 6, 5, 4, 5, 6, 7 },   // D
    { 0, 9, 4, 8, 0, 3, 5, 4 },   // F
    { 2, 10, 6, 11, 2, 1, 7, 6 }, // B
    { 3, 11, 7, 9, 3, 2, 6, 5 },  // L
    { 1, 8, 5, 10, 1, 0, 4, 7 },  // R
};

cubestate applyMove(int move, cubestate state)
{
    int turns = move % 3 + 1;
    int face = move / 3;

    while (turns--) {
        cubestate oldState = state;

        for (int i = 0; i < 8; i++) {
            int isCorner = i > 3;
            int target = affectedCubies[face][i] + isCorner * 12;
            int killer = affectedCubies[face][(i & 3) == 3 ? i - 3 : i + 1] + isCorner * 12;
            int orientationDelta = (i < 4) ? (face > 1 && face < 4) : (face < 2) ? 0 : 2 - (i & 1);

            state[target] = oldState[killer];
            state[target + 20] = oldState[killer + 20] + orientationDelta;

            if (!turns)
                state[target + 20] %= 2 + isCorner;
        }
    }
    return state;
}

int inverse(int move)
{
    return move + 2 - 2 * (move % 3);
}

int phase = 0;

cubestate id(cubestate state)
{

    //--- Phase 1: Edge orientations.
    if (phase < 2)
        return cubestate(state.begin() + 20, state.begin() + 32);

    //-- Phase 2: Corner orientations, E slice edges.
    if (phase < 3) {
        cubestate result(state.begin() + 31, state.begin() + 40);
        for (int e = 0; e < 12; e++)
            result[0] |= (state[e] / 8) << e;
        return result;
    }

    //--- Phase 3: Edge slices M and S, corner tetrads, overall parity.
    if (phase < 4) {
        cubestate result(3,0);
        for (int e = 0; e < 12; e++)
            result[0] |= ((state[e] > 7) ? 0 : (state[e] & 1)) << (2 * e);
        for (int c = 0; c < 8; c++)
            result[1] |= ((state[c + 12] - 12) & 5) << (3 * c);
        for (int i = 12; i < 20; i++)
            for (int j = i + 1; j < 20; j++)
                result[2] ^= state[i] > state[j];
        return result;
    }

    //--- Phase 4: The rest.
    return state;
}


int main()
{

     ifstream scramble_file ;
       ofstream output_file ;
       output_file.open("SolverOutput.txt");

      scramble_file.open("RandomScramble.txt");

       int argc;
        char argv[100][2];

        string s ;
		getline(scramble_file,s);
		argc=s.length();
		int t=0;
		//cout<<argc<<"\n" ;
		

		for (int j=0;j<argc;j++){

		 
		 //cout<<"j="<<j<<"\n";
		 //cout<<"t="<<t<<"\n";


			if ((j%3)==0){

				argv[t+1][0]=s[j];



			}
			if ((j%3)==1){

				argv[t+1][1]=s[j];
				t++ ;


			}
		}
		argc=t+1 ;


   
    




    //cout<<"Starting Application\n";
    //--- Define the goal.
    string goal[] = { "UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL",
        "UFR", "URB", "UBL", "ULF", "DRF", "DFL", "DLB", "DBR" };

    //--- Prepare current (start) and goal state.
    cubestate currentState(40), goalState(40,0);
    //cout<<"Argc"<<" "<<argc<<"\n";
    
    for (int i = 0; i < 20; i++) {

    //cout<<"\n1st loop \n"<<i;
        //--- Goal state.
        goalState[i] = i;

    }
    //cout<<"\n";
    currentState = goalState;
    
    for(int i=1; i<argc; i++){
        //cout<<"\n Let's see\n";
        //cout<<"This\n"<<argv[i][0]<<"\n";
        
        if(argv[i][0] == 'U'){
            currentState = applyMove(argv[i][1] - '1', currentState);
        }
        else if(argv[i][0] == 'D'){
            currentState = applyMove(3 + argv[i][1] - '1', currentState);
        }
        else if(argv[i][0] == 'F'){
            
            currentState = applyMove(6 + argv[i][1] - '1', currentState);
        }
        else if(argv[i][0] == 'B'){
            currentState = applyMove(9 + argv[i][1] - '1', currentState);
        }
        else if(argv[i][0] == 'L'){
            currentState = applyMove(12 + argv[i][1] - '1', currentState);
        }
        else if(argv[i][0] == 'R'){
            currentState = applyMove(15 + argv[i][1] - '1', currentState);
        }
        //cout<<"\n Let's end\n"<<i;
        
    }
    
    /*for(auto i: currentState){
        cout<<i<<" ";
    }
    cout<<"\n";
    */

    //--- Dance the funky Thistlethwaite...
    while (++phase < 5) {

        //cout<<"\nphase "<<phase<<" ";

        //--- Compute ids for current and goal state, skip phase if equal.
        cubestate currentId = id(currentState), goalId = id(goalState);
        if (currentId == goalId)
            continue;

        //--- Initialize the BFS queue.
        queue<cubestate> q;
        q.push(currentState);
        q.push(goalState);

        //--- Initialize the BFS tables.
        map<cubestate, cubestate> predecessor;
        map<cubestate, int> direction, lastMove;
        direction[currentId] = 1;
        direction[goalId] = 2;

        //--- Dance the funky bidirectional BFS...
        while (1) {

            //--- Get state from queue, compute its ID and get its direction.
            cubestate oldState = q.front();
            //assert(q.size() != 0);
            q.pop();


            cubestate oldId = id(oldState);
            int& oldDir = direction[oldId];

            //--- Apply all applicable moves to it and handle the new state.
            for (int move = 0; move < 18; move++) {
                if (applicableMoves[phase] & (1 << move)) {

                    //--- Apply the move.
                    cubestate newState = applyMove(move, oldState);
                    cubestate newId = id(newState);
                    int& newDir = direction[newId];

                    //--- Have we seen this state (id) from the other direction already?
                    //--- I.e. have we found a connection?
                    if (newDir && newDir != oldDir) {

                        //--- Make oldId represent the forwards and newId the backwards search state.
                        if (oldDir > 1) {
                            swap(newId, oldId);
                            move = inverse(move);
                        }

                        //--- Reconstruct the connecting algorithm.
                        cubestate algorithm(1, move);
                        while (oldId != currentId) {
                            algorithm.insert(algorithm.begin(), lastMove[oldId]);
                            oldId = predecessor[oldId];
                        }
                        while (newId != goalId) {
                            algorithm.push_back(inverse(lastMove[newId]));
                            newId = predecessor[newId];
                        }

                        //--- Print and apply the algorithm.
                        for (int i = 0; i < (int)algorithm.size(); i++) {
                            output_file << "UDFBLR"[algorithm[i] / 3];
                            if((algorithm[i] % 3 + 1) == 3) output_file<<"3";
                            else if(algorithm[i] % 3 + 1 == 2) output_file<<"2";
                            else output_file<<"1";
                            output_file<<" ";
                            currentState = applyMove(algorithm[i], currentState);
                        }

                        //--- Jump to the next phase.
                        goto nextPhase;
                    }

                    //--- If we've never seen this state (id) before, visit it.
                    if (!newDir) {
                        q.push(newState);
                        newDir = oldDir;
                        lastMove[newId] = move;
                        predecessor[newId] = oldId;
                    }
                }
            }
        }
    nextPhase:;
    }
       scramble_file.close();
  output_file.close();
}
